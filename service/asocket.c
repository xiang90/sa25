#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "asocket.h"
#include "amalloc.h"

fd_set readfds;
int fd_max;
int rbuf_size = 65535;
int wbuf_size = 65535;

struct socket_data *session[FD_SETSIZE];

static int null_parse(int);
static int def_func_destroy(int);
static int (*default_func_parse)(int) = null_parse;
static int (*default_func_destroy)(int) = def_func_destroy;
static int recv_to_buf(int);
static int send_from_buf(int);

void process_fdset(fd_set *, fd_set *);

void set_defaultparse(int (*defaultparse)(int))
{
  default_func_parse = defaultparse;
}

void set_defaultdestroy(int (*defaultdestroy)(int))
{
  default_func_destroy = defaultdestroy;
}

static int null_parse(int fd)
{
  printf("null parse: %d\n", fd);
  session[fd]->rdata_pos = session[fd]->rdata_size;
  return 0;
}

static int def_func_destroy(int fd)
{
  FD_CLR(fd, &readfds);
  close(fd);
  if(session[fd])
  {
  	if(session[fd]->rdata)
    	free(session[fd]->rdata);
  	if(session[fd]->wdata)
    	free(session[fd]->wdata);
  	free(session[fd]);
  }
  session[fd] = NULL;

  return 0;
}

int put_into_buf(int fd, const char *b, int len)
{
  if(fd<0 || session[fd]==NULL)
    return -2;
  
  if(len <= WFIFOSPACE(fd))
  {
    memcpy(session[fd]->wdata_size, b, len);
    session[fd]->wdata_size += len;
  }
  else{
    return -1;
  }

  return 0;
}

static int accept_client(int listen_fd)
{
  int fd;
  struct sockaddr_in client_addr;
  int len;
  int result;

  len = sizeof(client_addr);
  fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
  if(fd == -1)
  {
    fprintf(stderr,"accepting failure.\n");
    return -1;
  }
  else
  {
    FD_SET(fd, &readfds);
  }
  
  result = fcntl(fd, F_SETFL, O_NONBLOCK);

  session[fd] = (struct socket_data *)aCalloc(1, sizeof(*session[fd]));
  session[fd]->rdata = (unsigned char *)aCalloc(1, rbuf_size);
  session[fd]->wdata = (unsigned char *)aCalloc(1, wbuf_size);
  session[fd]->max_rdata = session[fd]->rdata + rbuf_size;
  session[fd]->max_wdata = session[fd]->wdata + wbuf_size;
  session[fd]->rdata_pos = session[fd]->rdata;
  session[fd]->rdata_size = session[fd]->rdata;
  session[fd]->wdata_pos = session[fd]->wdata;
  session[fd]->wdata_size = session[fd]->wdata;
  session[fd]->func_recv = recv_to_buf;
  session[fd]->func_send = send_from_buf;
  session[fd]->func_parse = default_func_parse;
  session[fd]->func_destroy = default_func_destroy;
  session[fd]->client_addr = client_addr;
	
  if(fd_max <= fd)
    fd_max = fd + 1;

  return fd;
}

int init_serv_socket(int port)
{
  struct sockaddr_in server_addr;
  int fd;
  int result;

  fd_max = 0;
  FD_ZERO(&readfds);
  for(result = 0; result < FD_SETSIZE; result++){
    session[result] = NULL;
  }

  fd = socket(AF_INET, SOCK_STREAM, 0);
  
  result = fcntl(fd, F_SETFL, O_NONBLOCK);
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons((unsigned short)port);

  result = bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(result == -1)
  {
    fprintf(stderr,"binding failure.\n");
    exit(1);
  }
  result = listen(fd, 5);
  if(result == -1)
  {
    fprintf(stderr,"listening port failure.\n");
    exit(1);
  }
  
  FD_SET(fd, &readfds);
  
  session[fd] = (struct socket_data *)aCalloc(1, sizeof(*session[fd]));
  session[fd]->func_recv = accept_client;

  if(fd_max <= fd)
    fd_max = fd + 1;
    
  return fd;
}

//do send and recv
int do_sendrecv(int next)
{
  fd_set rfd, wfd;
  struct timeval timeout;
  int ret, i;

  memmove(&rfd, &readfds, sizeof(fd_set));
  FD_ZERO(&wfd);
  for(i = 0; i < fd_max; i++){
    if(!session[i])
      continue;
    if(WFIFOREST(i) > 0)
      FD_SET(i, &wfd);
  }

  timeout.tv_sec = 0;
  timeout.tv_usec = 100;
  ret = select(fd_max, &rfd, &wfd, NULL, &timeout);
  if(ret <= 0){
    return 0;
  }
  
  process_fdset(&rfd, &wfd);
  
  return 0;
}


int do_parsepacket(void)
{
  int i;

  for(i = 0; i < fd_max; i++){
    if(!session[i])
      continue;
    if(session[i]->eof)
    {
      if(session[i]->func_destroy)
		session[i]->func_destroy(i);
    }
    else
    {
      if(session[i]->func_parse && session[i]->rdata_size != session[i]->rdata_pos)
		session[i]->func_parse(i);
      if(session[i]->rdata_size == session[i]->rdata_pos)
      {
		session[i]->rdata_size = session[i]->rdata;
		session[i]->rdata_pos = session[i]->rdata;
      }
      if((session[i]->rdata_pos - session[i]->rdata) * 4 > rbuf_size)
      {
		memmove(session[i]->rdata, session[i]->rdata_pos, RFIFOREST(i));
		session[i]->rdata_size = session[i]->rdata + RFIFOREST(i);
		session[i]->rdata_pos = session[i]->rdata;
      }
    }
  }
  
  return 0;
}

//recv to buf
static int recv_to_buf(int fd)
{
  int len;

  if(session[fd]->eof){
    return -1;
  }
  len = recv(fd, session[fd]->rdata_size, RFIFOSPACE(fd), 0);
  if(len > 0)
  {
    session[fd]->rdata_size += len;
#ifdef __LOG
    printf("fd: %d rdata_size=%d\n", fd, RFIFOREST(fd));
#endif
  }
  else
  {
#ifdef __LOG
    printf("fd: %d socket disconnected or some errors happened.\n", fd);
#endif
    session[fd]->eof=1;
  }
  return 0;
}

//send from buf
static int send_from_buf(int fd)
{
  int len;
  if(session[fd]->eof || WFIFOREST(fd) <= 0)
    return -1;

  len = send(fd, session[fd]->wdata_pos, WFIFOREST(fd), 0);
  if(len > 0)
  {
    session[fd]->wdata_pos += len;
    if(session[fd]->wdata_pos == session[fd]->wdata_size)
    {
      session[fd]->wdata_size = session[fd]->wdata;
      session[fd]->wdata_pos = session[fd]->wdata;
    }
    else if((session[fd]->wdata_pos - session[fd]->wdata) * 4 > wbuf_size)
    {
      memmove(session[fd]->wdata, session[fd]->wdata_pos, WFIFOREST(fd));
      session[fd]->wdata_size = session[fd]->wdata + WFIFOREST(fd);
      session[fd]->wdata_pos = session[fd]->wdata;
    }
  }
  else
  {
    session[fd]->eof = 1;
  }
  
  return 0;
}

//process fd_set
void process_fdset(fd_set *rfd, fd_set *wfd)
{
  int i;
  for(i = 0; i < fd_max; i++){
    if(!session[i])
      continue;
    if(FD_ISSET(i, rfd) && session[i]->func_recv)
      session[i]->func_recv(i);
    if(FD_ISSET(i, wfd) && session[i]->func_send)
      session[i]->func_send(i);
  }
}
