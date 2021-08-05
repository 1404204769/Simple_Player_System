#include "LoginSystem.h"
using namespace std;
using namespace mysqlpp;
CLoginSystem::CLoginSystem() {
	cout << "������CLoginSystem�Ĺ��캯��" << endl;
}
CLoginSystem::~CLoginSystem() {
	cout << "������CLoginSystem����������" << endl;
}
bool CLoginSystem::Login(const string& _strAccount) {
	/*����Ϊ�����account,����CUserMgrSearchInMap&SearchInDB���ܣ��������ڷ��ص���ʧ��*/
	UseQueryResult res;
	g_UserMgr.SearchInDB(res, _strAccount);
	Row row;
	if(! (row = res.fetch_row())) {
		cout << "û�ҵ����û��ļ�¼\n���Զ�Ϊ���û�ע��һ���˺�" << endl;
		cout << "�������û���(���ܰ����ո�)" << endl;
		string strName;
		cin >> strName;
		if (!g_UserMgr.Register(_strAccount, strName)) {
			cout << "ע��ʧ��" << endl;
			return false;
		}
		if (!g_UserMgr.SearchInDB(res, _strAccount)) {
			cout << "ע��ɹ�&&ϵͳ�����޷��ҵ�ע���ļ�¼" << endl;
			return false;
		}
		row = res.fetch_row();
	}
	long long int i64Id = g_UserMgr.getId(_strAccount);
	if (i64Id != 0) {
		cout << "����ʧ��,���û��ѵ��룡" << endl;
		return false;
	}
	if (!g_UserMgr.AddUser(row)) {
		cout << "����ʧ��" << endl;
		return false;
	}
	cout << "����ɹ�" << endl;
	return true;
}

bool CLoginSystem::Logout(const string& _strAccount) {
	/*ɾ��map�е�ָ������*/
	if (!g_UserMgr.DeleteUser(_strAccount)) {
		cout << "�ǳ�ʧ��" << endl;
		return false;
	}
	return true;
}