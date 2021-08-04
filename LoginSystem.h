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
	bool Login(const std::string& _strAccount);/*����Ϊ�����account,����CUserMgrSearchInMap&SearchInDB���ܣ��������ڷ��ص���ʧ��*/ 
	bool Register(const std::string& _strAccount, const std::string& _strName);/*����Ϊaccount,����CUserMgr��SearchInMap&SearchInDB���ܣ�����������������ݿ�ӿڲ�ѯ���ݣ������䱣����map��*/
	bool Logout(const std::string& _strAccount);/*ɾ��map�е�ָ������*/
};

#endif //!_LOGINSYSTEM_H_