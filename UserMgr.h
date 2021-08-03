#pragma once
#ifndef _USERMGR_H_
#define _USERMGR_H_
#include <map>
#include "DB.h"
#include "User.h"
#include <windows.h>
#include <mysql++.h>
extern CDB g_DB;
class CUserMgr {
public://内部的逻辑函数
	CUserMgr();
	~CUserMgr();
	bool AddUser(mysqlpp::UseQueryResult& res);/*将准备新增的用户的数据保存在Map中*/
	bool DeleteUser(std::string& _strAccount);/*根据Account删除对应的User*/ 
	CUser* getUser(long long int _i64Id);/*从map里面查询，返回查询对象指针*/ 
	long long int getId(std::string _strAccount);/*根据账户返回ID*//*如果返回一个负数说明该用户不在线*/
	bool SearchInDB(mysqlpp::UseQueryResult& res,std::string _strAccount);/*调用CDB函数查找指定对象,返回查询结果*/
	void Free();/*在析构函数中调用，释放还在内存中的数据，防止内存泄漏以及数据丢失*/
private:
	std::map<long long int,CUser*>m_mapById;/*每一个都代表目前登入的在线用户*/
	std::map<std::string, long long int>m_mapByAccount;/*记录Account与用户ID之间的关系*/
};
#endif // !_USERMGR_H_

