#include "UserLevelSystem.h"
using namespace std;

CUserLevelSystem::CUserLevelSystem() {
	cout << "调用了CUserLevelSystem的构造函数" << endl;
}
CUserLevelSystem::~CUserLevelSystem() {
	cout << "调用了CUserLevelSystem的析构函数" << endl;
}
bool CUserLevelSystem::LevelUp(const long long int _i64Id,const  unsigned int _unLev) {
	/*传入ID和要升的等级，直接在m_UserMgr的map内调用set函数修改数据*/
	CUser* pUser = g_UserMgr.getUser(_i64Id);
	if (!pUser) {
		cout << "此用户不在线" << endl;
		return false;
	}
	unsigned int unNewLev = pUser->getLev()+_unLev;
	pUser->setLev(unNewLev);
	return true;
}