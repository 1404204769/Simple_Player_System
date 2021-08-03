#include "DB.h"
#include "User.h"
#include "UserMgr.h"
#include "LoginSystem.h"
#include "UserLevelSystem.h"
using namespace std;
using namespace mysqlpp;
const string strDB("test");
const string strServer("localhost");
const string strUser("root");
const string strPassword("root");
const int nPort = 3306;
CDB g_DB;
CUserMgr g_UserMgr;
CLoginSystem g_LoginSystem;
CUserLevelSystem g_UserLevelSystem;
int Choice() {
	cout << "������Ҫִ�еĹ���" << endl;
	cout << "0.�˳�����" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	cout << "3.�ǳ�" << endl;
	int nChoice = 0;
	string _strAccount("");
	cin >> nChoice;
	switch (nChoice)
	{
	case 1:
		cout << "������Ҫ������˺�" << endl;
		cin >> _strAccount;
		if (!g_LoginSystem.Login(_strAccount)) {
			cout << "����ʧ�ܣ������µ���" << endl;
			return nChoice;
		}
		cout << "����ɹ�����ӭ����" << endl;
		break;
	case 2: {
		cout << "������Ҫ�������˺�ID�Լ�Ҫ���ĵȼ�" << endl;
		long long int _i64Id = 0;
		unsigned int _unLev = 0;
		cin >> _i64Id;
		cin >> _unLev;
		if (!g_UserLevelSystem.LevelUp(_i64Id,_unLev)) {
			cout << "����ʧ�ܣ�������" << endl;
			return nChoice;
		}
		cout << "�����ɹ�" << endl;
		CUser *user=g_UserMgr.getUser(_i64Id);
		if (!user) {
			cout << "��������,δ�ҵ���������˻�" << endl;
			return nChoice;
		}
		cout << "����������Ϊ��(ID:" << user->getId() << ",Account:" << user->getAccount() << ",CreateTime:" << user->getCreateTime() << ",Name:" << user->getName() << ",Exp:" << user->getExp() << ",Lev:" << user->getLev() << ")" << endl;
	}break;
	case 3: {
		cout << "������Ҫ�ǳ����˺�" << endl;
		cin >> _strAccount;
		if (!g_LoginSystem.Logout(_strAccount)) {
			cout << "�ǳ�ʧ�ܣ�������" << endl;
			return nChoice;
		}cout << "�ǳ��ɹ�����ӭ�´�������" << endl;
		break;
		//g_CUsermgr.showName();
	}break;
	default:
		return 0;
		break;
	}
	return nChoice;
}
int main() {
	g_DB.InitConnect(strDB, strServer, strUser, strPassword, nPort);
	while (1) {
		system("cls");
		cout << "��ӭʹ����־�ϵ�ͨѶ¼" << endl;
		if (Choice() == 0)
			break;
		system("pause");
	}
}