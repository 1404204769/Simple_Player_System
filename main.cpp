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
	cout << "请输入要执行的功能" << endl;
	cout << "0.退出程序" << endl;
	cout << "1.登入" << endl;
	cout << "2.升级" << endl;
	cout << "3.登出" << endl;
	int nChoice = 0;
	string strAccount("");
	cin >> nChoice;
	switch (nChoice)
	{
	case 1:
		cout << "请输入要登入的账号" << endl;
		cin >> strAccount;
		if (!g_LoginSystem.Login(strAccount)) {
			cout << "登入失败，请重新登入" << endl;
			return nChoice;
		}
		cout << "登入成功，欢迎您！" << endl;
		break;
	case 2: {
		cout << "请输入要升级的账号ID以及要升的等级" << endl;
		long long int i64Id = 0;
		unsigned int unLev = 0;
		cin >> i64Id;
		cin >> unLev;
		if (!g_UserLevelSystem.LevelUp(i64Id,unLev)) {
			cout << "升级失败，请重试" << endl;
			return nChoice;
		}
		cout << "升级成功" << endl;
		CUser *pUser=g_UserMgr.getUser(i64Id);
		if (!pUser) {
			cout << "发生错误,未找到升级后的账户" << endl;
			return nChoice;
		}
		cout << "升级后属性为了(ID:" << pUser->getId() << ",Account:" << pUser->getAccount() << ",CreateTime:" << pUser->getCreateTime() << ",Name:" << pUser->getName() << ",Exp:" << pUser->getExp() << ",Lev:" << pUser->getLev() << ")" << endl;
	}break;
	case 3: {
		cout << "请输入要登出的账号" << endl;
		cin >> strAccount;
		if (!g_LoginSystem.Logout(strAccount)) {
			cout << "登出失败，请重试" << endl;
			return nChoice;
		}cout << "登出成功，欢迎下次再来！" << endl;
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
		cout << "欢迎使用李志诚的通讯录" << endl;
		if (Choice() == 0)
			break;
		system("pause");
	}
}