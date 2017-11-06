#ifndef _SERVICE_H
#define _SERVICE_H

typedef struct _NPC
{
  int use;// is using?
  int index; //npc index
  unsigned sqlindex; //index in database
  char gmsvname[32]; //gmsv name
  char username[32]; //usr name
  int  buyflag; //does the man have goods?
  char goodsname[32]; //goods name
  int  type; //goods type;
  int  amount; //goods amount;
  int  code; //goods code;
  char param[32]; //goods params;
}NPC, PNPC;

enum _AP_CLIENT_MESSAGE
  {
    Cli_CHECKPLAYER,  //要求AP对玩家是否有购买产品的确认  0
    AP_CHECKPLAYER,   //AP回应玩家是否有购买产品
    Cli_YES,          //玩家确定要将奖品拿走
    Cli_CANCEL,       //通知AP把lock栏位清为0             
    Cli_GET,          //通知AP给物品
    AP_GET,           //AP回应物品5
    Cli_CONNECT,      //测试是否有连到AP
    AP_CONNECT,       //AP回应
    AP_ERROR          //AP有错误
  };

enum _BUYORNOT
  {
    DIDNOT_BUY = 0,
    DID_BUY,
    ANOTHER_USING,
    ALL_TAKEN,
  };

enum _GOODS_TYPE
  {
    GOLD = 0,
    ITEM,
    PET,
  };

#define ARRY_NUM 128
extern NPC npc_arry[ARRY_NUM];

int init_service(void);
int do_service(int);

#endif
