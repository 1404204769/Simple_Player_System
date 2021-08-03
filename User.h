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
	CUser(long long int _i64Id, std::string _strAccount, std::string _strTime, std::string _strName, long long int _i64Exp, unsigned int _unLev);
	~CUser();/*当用户退出时调用此析构函数，并调用CDB::UpdateData函数将数据保存在数据库中*/
	std::string& getAccount();
	void setAccount(std::string _strAccount);
	std::string& getCreateTime();
	std::string& getName();
	void setName(std::string _strName);
	long long int getId();
	void setId(long long int _i64Id);
	long long int getExp();
	void setExp(long long int _i64Exp);
	unsigned int getLev();
	void setLev(unsigned int _unLev);

private:
	unsigned int m_unLev;
	long long int m_i64Id, m_i64Exp;
	std::string m_strAccount, m_strCreateTime, m_strName;
};

#endif //!_USER_H_