#include "acctsql.h"
#include "util.h"
#include <errmsg.h>

#ifdef _ACNT_LOGIN
#define ACCT_CONF "acnt.conf"
char acct_server_host[20]="localhost";
char acct_usrname[20]="dbuser";
char acct_pwd[20]="123456";
char acct_db_name[20]="database";
int acct_host_port=0;
int acct_flags=0;

MYSQL *acctsql;
MYSQL_RES *acctsql_result;
MYSQL_ROW sqlrow;

#ifdef _SQL_RECONECT
int restflg = 0;
#endif

int acctsql_init(void)
{
#define MAXLINE 1024
	char cmd[20];
	char param[20];
	char line[MAXLINE];
	FILE *fp = fopen (ACCT_CONF, "r");
	if (fp == NULL) {
		fprintf (stderr, "acnt conf file not found\n");
		//return -1;
		exit(0);
	}
	
	while (fgets (line, MAXLINE, fp) != NULL) {
		if ((line[0] == '/' && line[1] == '/') || line[0] == '#')
			continue;
		
		chop (line);
		easyGetTokenFromString (line, 1, cmd, sizeof (cmd));
		easyGetTokenFromString (line, 2, param, sizeof (param));
		
		if (strcmp (cmd, "acct_host") == 0) {
			snprintf (acct_server_host, sizeof (acct_server_host), param);
		} else if (strcmp (cmd, "acct_port") == 0) {
			acct_host_port = atoi (param);
		} else if (strcmp (cmd, "usrname") == 0) {
			snprintf (acct_usrname, sizeof (acct_usrname), param);
		} else if (strcmp (cmd, "pwd") == 0 ) {
			snprintf (acct_pwd, sizeof (acct_pwd), param);
		} else if (strcmp (cmd, "db_name") == 0) {
			snprintf (acct_db_name, sizeof (acct_db_name), param);
		}
	}
	
	fclose (fp);
	
	acctsql = mysql_init(NULL);
	if(acctsql == NULL){
		fprintf(stderr,"\nmysql_init() failed (probably out of memory)\n");
		//return -1;
		exit(0);
	}else
		fprintf(stderr,"\nmysql_init() ok\n");

	if(mysql_real_connect( acctsql,
						   acct_server_host,
						   acct_usrname,
						   acct_pwd,
						   acct_db_name,
						   acct_host_port,
						   NULL,
						   acct_flags) == NULL)
    {
		fprintf(stderr,"mysql_real_connect() failed\nError %u\n",mysql_errno(acctsql));
		return -1;
    } else {
		fprintf(stderr,"mysql_real_connect() ok\n");
    }

	return 0;
}

void acctsql_close(void)
{
	mysql_close(acctsql);
}

#ifdef _SQL_PING
void acctsql_ping(void)
{
	int r = mysql_ping (acctsql);
	if (r) {
		fprintf(stderr, "Reinit acctsql!!\n");
		acctsql_close ();
		acctsql_init ();
	}
}
#endif

int acctsql_query(char *usrname, char *pwd, char *gid)
{
	int res,res_update;
	int isalive;
	int sql_errno;
#ifdef _EXP_DATE
	char exp_date[25];
	char now_date[25];
	time_t rawtime;
	struct tm *timeinfo;
#endif
	unsigned long num;
	unsigned int num_fields;
	char sql[1024];

#ifdef _SQL_RECONECT
////reset the acctsql connection
	if(restflg == 1) {
		fprintf(stderr, "Reinit acctsql!!\n");
		acctsql_close();
		acctsql_init();
		restflg = 0;
	}
#endif

	if(usrname==NULL || pwd==NULL || usrname[0] == '\0' \
	   || pwd[0] == '\0' || gid == NULL || gid[0] == '\0')
    {
		fprintf(stderr,"\nusrname or pwd err.\n");
		return -1;
    }
#ifdef _EXP_DATE
	sprintf(sql,"select alive,exp_date from account where username='%s' and password='%s'",usrname,pwd);
#else
	sprintf(sql,"select alive from account where username='%s' and password='%s'",usrname,pwd);
#endif
	res = mysql_query(acctsql, sql);
	if(res)
    {
		sql_errno = mysql_errno(acctsql);

		fprintf(stderr,"\ndump sql: %s\nselect error: %u (%s)\n", sql, sql_errno, mysql_error(acctsql));

#ifdef _SQL_RECONECT
		if (sql_errno == CR_SERVER_GONE_ERROR
			|| sql_errno == CR_SERVER_LOST)
			restflg = 1;
#endif

		return -1;
    }
  
	acctsql_result = mysql_store_result(acctsql);
	if(!acctsql_result)
    {
		fprintf(stderr,"\nmysql_store_result 'acctsql_query' is null\n");
		mysql_free_result(acctsql_result);
		return -1;
    }

	res = -1;
	num = (unsigned long)mysql_num_rows(acctsql_result);
	num_fields = mysql_num_fields(acctsql_result);
	if(num!=1)
    {
		fprintf(stderr,"\nget rows error. actual num_rows is:%lu\n",num);
		mysql_free_result(acctsql_result);
		return -1;
    }
#ifdef _EXP_DATE
  if(num_fields!=2)
#else
  if(num_fields!=1)
#endif
    {
      fprintf(stderr,"\nget fields error. actual num_fields is:%ud\n",num_fields);
      mysql_free_result(acctsql_result);
      return -1;
    }
  
  {
	  sqlrow=mysql_fetch_row(acctsql_result);
	  if(!sqlrow[0]
#ifdef _EXP_DATE
		 || !sqlrow[1]
#endif
		  ) {
		  mysql_free_result(acctsql_result);
		  return -1;
	  }

	  isalive = 0;
	  isalive = atoi(sqlrow[0]);
#ifdef _EXP_DATE
	  exp_date[0]='\0';
	  strncpy(exp_date, sqlrow[1], sizeof(exp_date));
#endif
	  mysql_free_result(acctsql_result);

	  if(isalive != 1) {
		  return 0;
	  }
     
#ifdef _EXP_DATE
	  time(&rawtime);
	  timeinfo=localtime(&rawtime);
	  memset(now_date,0,sizeof(now_date));
	  
	  sprintf(now_date,"%04d-%02d-%02d %02d:%02d:%02d",
			  timeinfo->tm_year+1900,timeinfo->tm_mon+1,\
			  timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,\
			  timeinfo->tm_sec);
	  
#ifdef _USING_GID
	  int gs_id = atoi(gid);
	  int check_exp = 1;
	  if(gs_id >= 12 && gs_id <= 15)
		  check_exp = 0;
#endif
	  //expired
	  if(
#ifdef _FREETIME_PLAY
		  (timeinfo->tm_wday==0 || (timeinfo->tm_wday%2)==0) &&
#endif
#ifdef _USING_GID
		  check_exp &&
#endif
		  strncmp(now_date,exp_date,22) >=0 ) {
		  res=0;
	  } else {
#endif    
		  sprintf(sql,"update account set last_date=now(), total_login=total_login+1 where username='%s'",usrname);
		  res_update=mysql_query(acctsql,sql);
		  if(res_update != 0) {
			  fprintf(stderr,"\nUpdate error %d: \n",mysql_errno(acctsql));
		  }
       
		  res=1;
#ifdef _EXP_DATE
	  }
#endif
  }
  
  return res;
}

#endif
