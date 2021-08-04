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
	bool AddUser(mysqlpp::Row& row);/*���������û�����*/
	bool DeleteUser(const std::string& _strAccount);/*����Accountɾ����Ӧ��User*/ 
	CUser* getUser(const long long int _i64Id);/*��map�����ѯ�����ز�ѯ����ָ��*/ 
	long long int getId(const std::string& _strAccount);/*�����˻�����ID*//*�������һ������˵�����û�������*/
	bool SearchInDB(mysqlpp::UseQueryResult& res,const std::string& _strAccount);/*����CDB��������ָ������,���ز�ѯ���*/
	void Free();/*�����������е��ã��ͷŻ����ڴ��е����ݣ���ֹ�ڴ�й©�Լ����ݶ�ʧ*/
private:
	bool AddToMap(CUser* _pUser);/*�������Map����������*/
	bool DeleteFromMap(const std::string& _strAccount);/*�������Map������ɾ��*/
	using MapById = std::map<long long int, CUser*>;
	using MapByIdIter = MapById::iterator;
	MapById m_mapById;/*ÿһ��������Ŀǰ����������û�*/
	using MapByAccount = std::map<std::string, long long int>;
	using MapByAccountIter = MapByAccount::iterator;
	MapByAccount m_mapByAccount;/*��¼Account���û�ID֮��Ĺ�ϵ*/
};
#endif // !_USERMGR_H_

