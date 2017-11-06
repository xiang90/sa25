#ifndef __VERSION_H__
#define __VERSION_H__

void Log( char *msg );
//#define _DEBUG_WORK
//#define _OFFICIAL_WGS //do not use it
#define _FIX_WORKS					//wk修改

#define _DYNAMIC_PORT //use dynamic port with saac
#define _ACNT_LOGIN //mysql account support
//#define _SQL_RECONECT //mysql server reconnect
//#define _SQL_PING //ping sql server every 10sec

// -------------------------------------------------------------------
// 专案：(新付费机制)
#define _AP_CHECK_3_TIMES        // (可开) WON ADD 减少认证次数 (北京&韩国不必开)
#define _FIX_MESSAGE             // (可开) WON ADD 修改封包内容 (北京&韩国不必开)
//#define _ADD_AC_IP			 // (测试中) WON ADD 加AC_IP至通讯协定中 (北京&韩国不必开)
//#define _TIMEOUTKICK // Robin 时段制

#endif


