#ifndef _ASOCKET_H
#define _ASOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct socket_data{
  int eof;
  unsigned char *rdata, *wdata;
  unsigned char *max_rdata, *max_wdata;
  unsigned char *rdata_pos, *rdata_size;
  unsigned char *wdata_pos, *wdata_size;
  int (*func_recv)(int);
  int (*func_send)(int);
  int (*func_parse)(int);
  int (*func_destroy)(int);
  struct sockaddr_in client_addr;
};

#define RFIFOSPACE(fd) (session[fd]->max_rdata - session[fd]->rdata_size)
#define RFIFOREST(fd) (session[fd]->rdata_size - session[fd]->rdata_pos)
#define WFIFOSPACE(fd) (session[fd]->max_wdata - session[fd]->wdata_size)
#define WFIFOREST(fd) (session[fd]->wdata_size - session[fd]->wdata_pos)

extern struct socket_data *session[FD_SETSIZE];
extern int rbuf_size, wbuf_size;
extern int fd_max;

void set_defaultparse(int (*defaultparse)(int));
void set_defaultdestroy(int (*defaultdestroy)(int));

int put_into_buf(int, const char*, int);
int do_sendrecv(int);
int do_parsepacket(void);
int init_serv_socket(int);

#endif
