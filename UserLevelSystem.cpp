#include "UserLevelSystem.h"
using namespace std;

CUserLevelSystem::CUserLevelSystem() {
	cout << "������CUserLevelSystem�Ĺ��캯��" << endl;
}
CUserLevelSystem::~CUserLevelSystem() {
	cout << "������CUserLevelSystem����������" << endl;
}
bool CUserLevelSystem::LevelUp(const long long int _i64Id,const  unsigned int _unLev) {
	/*����ID��Ҫ���ĵȼ���ֱ����m_UserMgr��map�ڵ���set�����޸�����*/
	CUser* pUser = g_UserMgr.getUser(_i64Id);
	if (!pUser) {
		cout << "���û�������" << endl;
		return false;
	}
	unsigned int unNewLev = pUser->getLev()+_unLev;
	pUser->setLev(unNewLev);
	return true;
}