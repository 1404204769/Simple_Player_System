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
	bool InitConnect(const std::string& strDB, const std::string& strServer, const std::string& strUser, const std::string& strPassword, const int nPort);/*�������ݿ�����*/
	bool Search(mysqlpp::UseQueryResult& res, const std::string& _strColumn,const std::string& _strAccount);/*��ѯd_user���ڵ�ָ����Ϣ*/
	bool Insert(const std::string& _strAccount, const std::string& _strName);/*����һ���µ�ֵ��d_user��*/
	bool Update(const long long int _i64Id, const std::string& _strAccount, const std::string& _strName, const long long int _i64Exp, const unsigned int _unLev);/*����ֵ��d_user��*/
private:
	std::string m_strDB="test", m_strServer="localhost", m_strUser="root", m_strPassword="root";
	int m_nPort=0;
	mysqlpp::Connection m_Conn;
};

#endif // !_DB_H_
