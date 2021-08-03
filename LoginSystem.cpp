#include "LoginSystem.h"
using namespace std;
using namespace mysqlpp;
CLoginSystem::CLoginSystem() {
	cout << "������CLoginSystem�Ĺ��캯��" << endl;
}
CLoginSystem::~CLoginSystem() {
	cout << "������CLoginSystem����������" << endl;
}
bool CLoginSystem::Login(string _strAccount) {
	/*����Ϊ�����account,����CUserMgrSearchInMap&SearchInDB���ܣ��������ڷ��ص���ʧ��*/
	UseQueryResult res;
	g_UserMgr.SearchInDB(res, _strAccount);
	UseQueryResult resNumTest = res;
	int nNum = res.num_fields();
	if(nNum==0){
		cout << "û�ҵ����û��ļ�¼\n���Զ�Ϊ���û�ע��һ���˺�" << endl;
		cout << "�������û���(���ܰ����ո�)" << endl;
		string _strName;
		cin >> _strName;
		if (!Register(_strAccount, _strName)) {
			cout << "ע��ʧ��" << endl;
			return false;
		}
		if (!g_UserMgr.SearchInDB(res, _strAccount)) {
			cout << "ע��ɹ�&&ϵͳ�����޷��ҵ�ע���ļ�¼" << endl;
			return false;
		}
	}
	else {
		long long int _i64Id = g_UserMgr.getId(_strAccount);
		if (_i64Id > 0){
			cout << "����ʧ��,���û��ѵ��룡" << endl;
			return false;
		}
	}
	if (!g_UserMgr.AddUser(res)) {
		cout << "����ʧ��" << endl;
		return false;
	}
	cout << "����ɹ�" << endl;
	return true;
}
bool CLoginSystem::Register(string _strAccount, string _strName) {
	/*����Ϊaccount,name,����CDB��insert�ӿڱ��������ݿ���*/
	if (!g_DB.Insert(_strAccount, _strName)) {
		cout << "�û�ע��ɹ�" << endl;
		return false;
	}
	return true;
}
bool CLoginSystem::Logout(string _strAccount) {
	/*ɾ��map�е�ָ������*/
	if (!g_UserMgr.DeleteUser(_strAccount)) {
		cout << "�ǳ�ʧ��" << endl;
		return false;
	}
	return true;
}