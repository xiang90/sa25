#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "asocket.h"
#include "service.h"
#include "sql.h"

NPC npc_arry[ARRY_NUM];

void do_checkplayer(int, int, int, char *, char *);
void do_getgoods(int, int, int, char *, char *);
void do_taken(int, int, int, char *, char *);
void do_canceltake(int, int, int, char *, char *);
void do_connect(int, int, int, char *, char *);

int init_service(void)
{
  set_defaultparse(do_service);
  memset(npc_arry, 0, sizeof(npc_arry));

  return 0;
}

int do_service(int fd)
{
  char buf[128];
  int nAid = 0, nIndex = 0, nLen = 0;
  char temp[5][128];
  int i = 0, j;
  char *p, usrname[128], gmsvname[128];

  if(RFIFOREST(fd) < sizeof(buf))
    return -1;

  memcpy(buf, session[fd]->rdata_pos, sizeof(buf));
  session[fd]->rdata_pos += sizeof(buf);

  buf[sizeof(buf) - 1] = '\0';
  fprintf(stderr, "From GMSV: %s\n", buf);
  
  if(buf[i] == '&')
    {
      if(buf[++i] == ';')
	{
	  bzero(temp[0], sizeof(temp[0]));
	  bzero(temp[1], sizeof(temp[1]));
	  bzero(temp[2], sizeof(temp[2]));
	  bzero(temp[3], sizeof(temp[3]));
	  bzero(temp[4], sizeof(temp[4]));
	  
	  for(j = 0; j < 5; j++)
	    {
	      p = strchr(&buf[i+1] , ';');
	      strncpy(temp[j] , &buf[i+1] , p - (&buf[i+1]));
	      i += strlen(temp[j]) + 1;
	    }

	  nAid   = atoi(temp[0]);
	  nIndex = atoi(temp[1]);
	  nLen   = atoi(temp[2]);
	  memcpy(usrname, temp[3], sizeof(usrname));
	  memcpy(gmsvname, temp[4], sizeof(gmsvname));
	}
    }
  else
    return -1;
  
  switch(nAid % 10)
    {
    case Cli_CHECKPLAYER:
      do_checkplayer(fd, nAid, nIndex, usrname, gmsvname);
      break;
    case Cli_GET:
      do_getgoods(fd, nAid, nIndex, usrname, gmsvname);
      break;
    case Cli_YES:
      do_taken(fd, nAid, nIndex, usrname, gmsvname);
      break;
    case Cli_CANCEL:
      do_canceltake(fd, nAid, nIndex, usrname, gmsvname);
      break;
    case Cli_CONNECT:
      do_connect(fd, nAid, nIndex, usrname, gmsvname);
      break;
    }

  return 0;
}

void make_response(int fd, int cmd, int arry_index, int nAid, int nIndex)
{
  char buf[128];
  char tmp[128];
  int len;
  char token[128];
  int LV = 0, HP = 0, STR = 0, TGH = 0, DEX = 0;

  memset(buf, 0, sizeof(buf));
  memset(tmp, 0, sizeof(tmp));

  sprintf(buf, "&;%d;%d;", ((nAid/10)*10 + cmd), nIndex);

  switch(cmd)
    {
    case AP_CHECKPLAYER:
      if(arry_index == -1)
	{
	  strcpy(tmp, "1;0;");
	}
      else
	{
	  if(npc_arry[arry_index].buyflag == DID_BUY)
	    {
	      sprintf(tmp, "2;1;%s;", npc_arry[arry_index].goodsname);
	    }
	  else
	    {
	      sprintf(tmp, "1;%d;", npc_arry[arry_index].buyflag);
	    }
	}
      break;
    case AP_GET:
      switch(npc_arry[arry_index].type)
	{
	case GOLD:
	  sprintf(tmp, "3;0;%d;0;", npc_arry[arry_index].amount);
	  break;
	case ITEM:
	  sprintf(tmp, "3;%d;%d;1;", npc_arry[arry_index].code, npc_arry[arry_index].amount);
	  break;
	case PET:
	  easyGetTokenFromString(npc_arry[arry_index].param, 1, token, sizeof(token));
	  LV = atoi(token);
	  easyGetTokenFromString(npc_arry[arry_index].param, 2, token, sizeof(token));
	  HP = atoi(token);
	  easyGetTokenFromString(npc_arry[arry_index].param, 3, token, sizeof(token));
	  STR = atoi(token);
	  easyGetTokenFromString(npc_arry[arry_index].param, 4, token, sizeof(token));
	  TGH = atoi(token);
	  easyGetTokenFromString(npc_arry[arry_index].param, 5, token, sizeof(token));
	  DEX = atoi(token);

	  sprintf(tmp, "8;%d;%d;2;%d;%d;%d;%d;%d;", npc_arry[arry_index].code, npc_arry[arry_index].amount, 
		  LV, HP, STR, TGH, DEX);
	  break;
	default:
	  return;
	  break;
	}
      break;
    }

  strcat(buf, tmp);
  len = strlen(buf);
  memset(&buf[len], '&', sizeof(buf) - len);

  put_into_buf(fd, buf, sizeof(buf));

  buf[sizeof(buf) - 1] = '\0';
  fprintf(stderr, "To GMSV: %s\n", buf);
}

void do_checkplayer(int fd, int nAid, int nIndex, char *usrname, char *gmsvname)
{
  int i;
  int ret;
  
  for(i = 0; i < ARRY_NUM; i++)
    {
      if(npc_arry[i].use)
	continue;
      else
	break;
    }
  if(i >= ARRY_NUM) //full
    {
      fprintf(stderr, "Array is full.\n");
      //make_response(fd, AP_CHECKPLAYER, -1, nAid, nIndex);
      return;
    }

  ret = query_id(usrname, i);
  if(ret == 0)//ok
    {
      strcpy(npc_arry[i].gmsvname, gmsvname);
      npc_arry[i].index = nIndex;
      make_response(fd, AP_CHECKPLAYER, i, nAid, nIndex);
    }
  else
    {
      make_response(fd, AP_CHECKPLAYER, -1, nAid, nIndex);
    }
}

void do_getgoods(int fd, int nAid, int nIndex, char *usrname, char *gmsvname)
{
  int i;
  
  for(i = 0; i < ARRY_NUM; i++)
    {
      if(npc_arry[i].use
	 && nIndex == npc_arry[i].index
	 && strcmp(usrname, npc_arry[i].username) == 0 
	 && strcmp(gmsvname, npc_arry[i].gmsvname) == 0) // found
	{
	  make_response(fd, AP_GET, i, nAid, nIndex);
	  break;
	}
    }
}

void do_taken(int fd, int nAid, int nIndex, char *usrname, char *gmsvname)
{
  int i;
  
  for(i = 0; i < ARRY_NUM; i++)
    {
      if(npc_arry[i].use
	 && nIndex == npc_arry[i].index
	 && strcmp(usrname, npc_arry[i].username) == 0 
	 && strcmp(gmsvname, npc_arry[i].gmsvname) == 0) // found
	{
	  update_id(usrname, npc_arry[i].sqlindex);
	  memset(&npc_arry[i], 0, sizeof(npc_arry[i]));
	  break;
	}
    }
}

void do_canceltake(int fd, int nAid, int nIndex, char *usrname, char *gmsvname)
{
  int i;
  
  for(i = 0; i < ARRY_NUM; i++)
    {
      if(npc_arry[i].use
	 && nIndex == npc_arry[i].index
	 && strcmp(usrname, npc_arry[i].username) == 0 
	 && strcmp(gmsvname, npc_arry[i].gmsvname) == 0) // found
	{
	  memset(&npc_arry[i], 0, sizeof(npc_arry[i]));
	}
    }
}

void do_connect(int fd, int nAid, int nIndex, char *usrname, char *gmsvname)
{
}
