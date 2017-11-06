#ifndef _ACCTSQL_H_
#define _ACCTSQL_H_

#include "version.h"
#ifdef _ACNT_LOGIN

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <mysql.h>

#ifdef _SQL_PING
void acctsql_ping(void);
#endif
int acctsql_init(void);
void acctsql_close(void);
int acctsql_query(char *, char *, char *);

extern char acct_server_host[20];
extern char acct_usrname[20];
extern char acct_pwd[20];
extern char acct_db_name[20];
extern int acct_host_port;
extern int acct_flags;

#endif
#endif
