#include "LoginSystem.h"
using namespace std;
using namespace mysqlpp;
CLoginSystem::CLoginSystem() {
	cout << "调用了CLoginSystem的构造函数" << endl;
}
CLoginSystem::~CLoginSystem() {
	cout << "调用了CLoginSystem的析构函数" << endl;
}
bool CLoginSystem::Login(string _strAccount) {
	/*参数为登入的account,调用CUserMgrSearchInMap&SearchInDB功能，若不存在返回登入失败*/
	UseQueryResult res;
	g_UserMgr.SearchInDB(res, _strAccount);
	UseQueryResult resNumTest = res;
	int nNum = res.num_fields();
	if(nNum==0){
		cout << "没找到该用户的记录\n已自动为新用户注册一个账号" << endl;
		cout << "请输入用户名(不能包含空格)" << endl;
		string _strName;
		cin >> _strName;
		if (!Register(_strAccount, _strName)) {
			cout << "注册失败" << endl;
			return false;
		}
		if (!g_UserMgr.SearchInDB(res, _strAccount)) {
			cout << "注册成功&&系统错误：无法找到注册后的记录" << endl;
			return false;
		}
	}
	else {
		long long int _i64Id = g_UserMgr.getId(_strAccount);
		if (_i64Id > 0){
			cout << "登入失败,该用户已登入！" << endl;
			return false;
		}
	}
	if (!g_UserMgr.AddUser(res)) {
		cout << "登入失败" << endl;
		return false;
	}
	cout << "登入成功" << endl;
	return true;
}
bool CLoginSystem::Register(string _strAccount, string _strName) {
	/*参数为account,name,调用CDB的insert接口保存在数据库内*/
	if (!g_DB.Insert(_strAccount, _strName)) {
		cout << "用户注册成功" << endl;
		return false;
	}
	return true;
}
bool CLoginSystem::Logout(string _strAccount) {
	/*删除map中的指定对象*/
	if (!g_UserMgr.DeleteUser(_strAccount)) {
		cout << "登出失败" << endl;
		return false;
	}
	return true;
}