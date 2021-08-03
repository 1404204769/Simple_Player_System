#pragma once
#ifndef _DB_H_
#define _DB_H_
#include <string>
#include <iostream>
#include <mysql++.h>
class CDB {
public:
	CDB();
	~CDB();
	bool InitConnect(const std::string& strDB, const std::string& strServer, const std::string& strUser, const std::string& strPassword, const int& nPort);/*建立数据库连接*/
	bool Search(mysqlpp::UseQueryResult& res, const std::string& _strColumn,const std::string& _strAccount);/*查询d_user表内的指定信息*/
	bool Insert(std::string _strAccount, std::string _strName);/*插入一条新的值到d_user中*/
	bool Update(long long int _i64Id, std::string _strAccount, std::string _strName, long long int _i64Exp, unsigned int _unLev);/*更新值到d_user中*/
private:
	std::string m_strDB, m_strServer, m_strUser, m_strPassword;
	int m_nPort=0;
	mysqlpp::Connection m_Conn;
};

#endif // !_DB_H_
