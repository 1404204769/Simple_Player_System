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
public://�ڲ����߼�����
	CUserMgr();
	~CUserMgr();
	bool AddUser(mysqlpp::UseQueryResult& res);/*��׼���������û������ݱ�����Map��*/
	bool DeleteUser(std::string& _strAccount);/*����Accountɾ����Ӧ��User*/ 
	CUser* getUser(long long int _i64Id);/*��map�����ѯ�����ز�ѯ����ָ��*/ 
	long long int getId(std::string _strAccount);/*�����˻�����ID*//*�������һ������˵�����û�������*/
	bool SearchInDB(mysqlpp::UseQueryResult& res,std::string _strAccount);/*����CDB��������ָ������,���ز�ѯ���*/
	void Free();/*�����������е��ã��ͷŻ����ڴ��е����ݣ���ֹ�ڴ�й©�Լ����ݶ�ʧ*/
private:
	std::map<long long int,CUser*>m_mapById;/*ÿһ��������Ŀǰ����������û�*/
	std::map<std::string, long long int>m_mapByAccount;/*��¼Account���û�ID֮��Ĺ�ϵ*/
};
#endif // !_USERMGR_H_

