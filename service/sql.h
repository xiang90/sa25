#ifndef _SQL_H_
#define _SQL_H_

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

int sql_init(void);
void sql_close(void);

int query_id(char *, int);
int update_id(char *, unsigned);

extern char sql_server_host[20];
extern char sql_usrname[20];
extern char sql_pwd[20];
extern char sql_db_name[20];
extern int sql_host_port;
extern int sql_flags;

#endif
