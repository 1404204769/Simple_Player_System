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
	bool AddUser(mysqlpp::Row& row);/*新增登入用户数据*/
	bool DeleteUser(const std::string& _strAccount);/*根据Account删除对应的User*/ 
	CUser* getUser(const long long int _i64Id);/*从map里面查询，返回查询对象指针*/ 
	long long int getId(const std::string& _strAccount);/*根据账户返回ID*//*如果返回一个负数说明该用户不在线*/
	bool SearchInDB(mysqlpp::UseQueryResult& res,const std::string& _strAccount);/*调用CDB函数查找指定对象,返回查询结果*/
	void Free();/*在析构函数中调用，释放还在内存中的数据，防止内存泄漏以及数据丢失*/
private:
	bool AddToMap(CUser* _pUser);/*负责管理Map容器的增加*/
	bool DeleteFromMap(const std::string& _strAccount);/*负责管理Map容器的删除*/
	using MapById = std::map<long long int, CUser*>;
	using MapByIdIter = MapById::iterator;
	MapById m_mapById;/*每一个都代表目前登入的在线用户*/
	using MapByAccount = std::map<std::string, long long int>;
	using MapByAccountIter = MapByAccount::iterator;
	MapByAccount m_mapByAccount;/*记录Account与用户ID之间的关系*/
};
#endif // !_USERMGR_H_

