#include "UserLevelSystem.h"
using namespace std;

CUserLevelSystem::CUserLevelSystem() {
	cout << "������CUserLevelSystem�Ĺ��캯��" << endl;
}
CUserLevelSystem::~CUserLevelSystem() {
	cout << "������CUserLevelSystem����������" << endl;
}
bool CUserLevelSystem::LevelUp(long long int _i64Id, unsigned int _unLev) {
	/*����ID��Ҫ���ĵȼ���ֱ����m_UserMgr��map�ڵ���set�����޸�����*/
	CUser* user = g_UserMgr.getUser(_i64Id);
	if (!user) {
		cout << "���û�������" << endl;
		return false;
	}
	unsigned int _unNewLev = user->getLev()+_unLev;
	user->setLev(_unNewLev);
	return true;
}