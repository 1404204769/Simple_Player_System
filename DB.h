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
	bool InitConnect(const std::string& strDB, const std::string& strServer, const std::string& strUser, const std::string& strPassword, const int& nPort);/*�������ݿ�����*/
	bool Search(mysqlpp::UseQueryResult& res, const std::string& _strColumn,const std::string& _strAccount);/*��ѯd_user���ڵ�ָ����Ϣ*/
	bool Insert(std::string _strAccount, std::string _strName);/*����һ���µ�ֵ��d_user��*/
	bool Update(long long int _i64Id, std::string _strAccount, std::string _strName, long long int _i64Exp, unsigned int _unLev);/*����ֵ��d_user��*/
private:
	std::string m_strDB, m_strServer, m_strUser, m_strPassword;
	int m_nPort=0;
	mysqlpp::Connection m_Conn;
};

#endif // !_DB_H_
