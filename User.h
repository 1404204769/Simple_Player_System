#pragma once
#ifndef _USER_H_
#define _USER_H_
#include <string>
#include "DB.h"
extern CDB g_DB;
class CUser
{
public:
	CUser()=delete;
	CUser(const long long int _i64Id, const std::string& _strAccount, const std::string& _strTime, const std::string& _strName, const long long int _i64Exp, const unsigned int _unLev);
	~CUser();/*当用户退出时调用此析构函数，并调用CDB::UpdateData函数将数据保存在数据库中*/
	const std::string& getAccount();
	const std::string& getCreateTime();
	const std::string& getName();
	const long long int getId();
	const long long int getExp();
	const unsigned int getLev();
	void setLev(const unsigned int _unLev);
	void setExp(const long long int _i64Exp);
	void setName(const std::string& _strName);

private:
	unsigned int m_unLev=0;
	long long int m_i64Id=0, m_i64Exp=0;
	std::string m_strAccount="wrong", m_strCreateTime="now()", m_strName = "wrong";
};

#endif //!_USER_H_