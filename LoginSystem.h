#pragma once
#ifndef _LOGINSYSTEM_H_
#define _LOGINSYSTEM_H_
#include "UserMgr.h"
#include <string>
extern CUserMgr g_UserMgr;
extern CDB g_DB;
class CLoginSystem
{
public:
	CLoginSystem();
	~CLoginSystem();
	bool Login(std::string _strAccount);/*参数为登入的account,调用CUserMgrSearchInMap&SearchInDB功能，若不存在返回登入失败*/ 
	bool Register(std::string _strAccount, std::string _strName);/*参数为account,调用CUserMgr的SearchInMap&SearchInDB功能，若不存在则调用数据库接口查询数据，并将其保存在map中*/
	bool Logout(std::string _strAccount);/*删除map中的指定对象*/
};

#endif //!_LOGINSYSTEM_H_