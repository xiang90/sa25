#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include "asocket.h"
#include "service.h"
#include "sql.h"

int port = 9987;

static void default_term_func(void)
{
  sql_close();
}

static void (*term_func)(void) = default_term_func;

static void sig_proc(int sn)
{
  int i;
  static int is_called = 0;
  if(is_called++) {
    return ;
  }
  switch(sn){
  case SIGINT:
  case SIGTERM:
    if(term_func)
      term_func();
    for(i = 0; i < fd_max; i++){
      if(!session[i])
		continue;
      if(session[i]->func_destroy)
		session[i]->func_destroy(i);
    }
    exit(0);
    break;
  }
}

static struct option long_options[] =
  {
    {"port" , 1, 0,'p'},
    {"help" , 0, 0,'h'},
    {0,0,0,0}
  };

static void parseOpt( int argc , char **argv )
{
  int c;
  int option_index;

  if( argc == 1 ){
    fprintf( stderr , "Argument error: print usage with --help\n" );
    exit(0);
  }

  while(1){
    c = getopt_long ( argc, argv, "p:h:", long_options, &option_index );
    if( c == -1 )
      break;
    switch(c )
      {
      case 'p' :
	port = atoi( optarg );
	break;
      case 'h':
	fprintf( stderr,
		 "Usage: gwserv [-p port|--port port] [-a address] [-h|--help]\n"
		 "              [-g gwport|--gport gwport]\n\n"
		 );
	exit(0);
	break;
      }
  }
}

int main(int argc, char **argv)
{
  parseOpt(argc, argv);

  signal(SIGPIPE, SIG_IGN);
  signal(SIGTERM, sig_proc);
  signal(SIGINT, sig_proc);

  sql_init();
  init_service();
  init_serv_socket(port);

  while(1){
    do_sendrecv(1);
    do_parsepacket();
  }
  
  return 0;
}
