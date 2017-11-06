#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "service.h"
#include "sql.h"
#include "utils.h"

#define SERVICE_CONF "service.conf"
char sql_server_host[20]="localhost";
char sql_usrname[20]="service";
char sql_pwd[20]="123456";
char sql_db_name[20]="service";
int sql_host_port=0;
int sql_flags=0;

MYSQL *sql;
MYSQL_RES *sql_result;
MYSQL_ROW sqlrow;

int sql_init(void)
{
#define MAXLINE 1024
	char cmd[20];
	char param[20];
	char line[MAXLINE];
	FILE *fp = fopen (SERVICE_CONF, "r");
	if (fp == NULL) {
		fprintf (stderr, "service conf file not found\n");
			return -1;
	}
	
	while (fgets (line, MAXLINE, fp) != NULL) {
		if ((line[0] == '/' && line[1] == '/') || line[0] == '#')
			continue;
		
		chop (line);
		easyGetTokenFromString (line, 1, cmd, sizeof (cmd));
		easyGetTokenFromString (line, 2, param, sizeof (param));
		
		if (strcmp (cmd, "service_host") == 0) {
			snprintf (sql_server_host, sizeof (sql_server_host), param);
		} else if (strcmp (cmd, "service_port") == 0) {
			sql_host_port = atoi (param);
		} else if (strcmp (cmd, "usrname") == 0) {
			snprintf (sql_usrname, sizeof (sql_usrname), param);
		} else if (strcmp (cmd, "pwd") == 0 ) {
			snprintf (sql_pwd, sizeof (sql_pwd), param);
		} else if (strcmp (cmd, "db_name") == 0) {
			snprintf (sql_db_name, sizeof (sql_db_name), param);
		}
	}
	
	fclose (fp);


  sql = mysql_init(NULL);
  if(sql == NULL){
    fprintf(stderr,"service sql init err\n");
    return -1;
  }
  else
    fprintf(stderr,"service sql init ok\n");

  if(mysql_real_connect( sql,
			 sql_server_host,
			 sql_usrname,
			 sql_pwd,
			 sql_db_name,
			 sql_host_port,
			 NULL,
			 sql_flags) == NULL)
    {
      fprintf(stderr, "service sql failed\nError %u\n", mysql_errno(sql));
      return -1;
    }
  else
    {
      fprintf(stderr, "service sql ok\n");
    }

  return 0;
}

void sql_close(void)
{
  fprintf(stderr, "service sql closed.\n");
  mysql_close(sql);
}

int update_id(char *username, unsigned sqlindex)
{
  char buf[1024];
  int res;

  if(username == NULL || strlen(username) < 1)
    return -1;

  sprintf(buf, "update goods set istaken='1',take_date=now() where id = '%u'", sqlindex);
  res = mysql_query(sql, buf);
  if(res)
    return -2;

  return 0;
}

/*
  0   npc struct is filled
  -1  err
  -2  did not buy anything
*/
int query_id(char *username, int index)
{
  char sqlbuf[1024];
  int res;
  unsigned long num;
  unsigned int num_fields;

  if(username == NULL || strlen(username) < 1)
    return -1;

  //fprintf(stderr, "Query id func params:\nCDKEY: %s\t Array index:%d\n", username, index);

  sprintf(sqlbuf, "select binary(goodsname),type,amount,code,param,id from goods where username='%s' and istaken='0' order by give_date limit 1", username);
  res = mysql_query(sql, sqlbuf);
  if(res)
    {
      fprintf(stderr, "No result found.\n");
      return -2;
    }
  
  sql_result = mysql_store_result(sql);
  if(!sql_result)
    {
      mysql_free_result(sql_result);
      fprintf(stderr, "Store result err.\n");
      return -1;
    }

  num = (unsigned long)mysql_num_rows(sql_result);
  num_fields = mysql_num_fields(sql_result);
  if(num != 1)
    {
      mysql_free_result(sql_result);
      fprintf(stderr, "Found %d line(s).\n", (int)num);
      return -1;
    }
  if(num_fields != 6)
    {
      mysql_free_result(sql_result);
      fprintf(stderr, "Found fields err. %d fields.\n", num_fields);
      return -1;
    }
  
  sqlrow = mysql_fetch_row(sql_result);

  memset(&npc_arry[index], 0, sizeof(npc_arry[index]));
  
  npc_arry[index].use = 1;
  npc_arry[index].buyflag = DID_BUY;
  strcpy(npc_arry[index].username, username);
  strcpy(npc_arry[index].goodsname, sqlrow[0]);
  npc_arry[index].type = atoi(sqlrow[1]);
  npc_arry[index].amount = atoi(sqlrow[2]);
  npc_arry[index].code = atoi(sqlrow[3]);
  strcpy(npc_arry[index].param, sqlrow[4]);
  npc_arry[index].sqlindex = atoi(sqlrow[5]);
  
  mysql_free_result(sql_result);

  return 0;
}
