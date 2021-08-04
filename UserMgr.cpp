#include "UserMgr.h"
using namespace std;
using namespace mysqlpp;
CUserMgr::CUserMgr() {
	cout << "������CUserMgr�Ĺ��캯��" << endl;
	m_mapById.clear();
	m_mapByAccount.clear();
}
CUserMgr::~CUserMgr() {
	cout << "������CUserMgr����������" << endl;
	Free();
}
bool CUserMgr::AddUser(Row& row) {
	/*��׼���������û������ݱ�����Map��*/
	if (!row)return false;
	string strAccount(row["account"]);
	long long int i64Id = row["id"];
	if (getId(strAccount) || getUser(i64Id)) {
		DeleteUser(strAccount);
		//cout << "��һ���û��ѱ�ǿ������" << endl;
	}
	string strTime(row["create_time"]);
	string strName(row["name"]);
	long long int i64Exp = row["exp"];
	unsigned int unLev = row["lev"];
	CUser *pUser=new CUser(i64Id,strAccount,strTime,strName, i64Exp, unLev);
	if (!pUser) {
		cout << "�û�����ʧ��" << endl;
		return false;
	}
	return AddToMap(pUser);

}
bool CUserMgr::AddToMap(CUser* _pUser) {
	m_mapByAccount[_pUser->getAccount()]= _pUser->getId();
	m_mapById[_pUser->getId()]= _pUser;
	if (m_mapByAccount.count(_pUser->getAccount()) == 0 || m_mapById.count(_pUser->getId())==0) {
		cout << "�û�����ʧ��" << endl;
		DeleteUser(_pUser->getAccount());
		return false;
	}
	return true;
}
bool CUserMgr::DeleteFromMap(const string& _strAccount) {
	/*����Accountɾ����Ӧ��User*/
	MapByAccountIter iterByAccount = m_mapByAccount.find(_strAccount);
	if (iterByAccount == m_mapByAccount.end()) {
		cout << "�û������� Account:" << _strAccount << endl;
		return false;
	}
	long long int i64Id = iterByAccount->second;
	m_mapByAccount.erase(iterByAccount);
	MapByIdIter iterById = m_mapById.find(i64Id);
	if (iterById == m_mapById.end()) {
		cout << "�û������� ID:" << iterByAccount->second << endl;
		return false;
	}
	delete iterById->second;
	iterById->second = nullptr;
	m_mapById.erase(iterById);
	return true;
}
bool CUserMgr::DeleteUser(const string& _strAccount) {
	return DeleteFromMap(_strAccount);
}
CUser* CUserMgr::getUser(const long long int _i64Id) {
	/*��map�����ѯ�����ز�ѯ����ָ��*/
	MapByIdIter iterById = m_mapById.find(_i64Id);
	if (iterById == m_mapById.end()) {
		cout << "Do not Find ID:" << _i64Id << endl;
		return nullptr;
	}
	return iterById->second;
}
long long int CUserMgr::getId(const std::string& _strAccount) {/*�������һ��0˵�����û�������*/
	MapByAccountIter iterByAccount = m_mapByAccount.find(_strAccount);
	if (iterByAccount == m_mapByAccount.end())return 0;
	return iterByAccount->second;
}
bool CUserMgr::SearchInDB(UseQueryResult& res,const string& _strAccount) {
	/*����CDB��������ָ������,���ز�ѯ���*/
	if (!g_DB.Search(res, "account", _strAccount))
		return false;
	return true;
}
void CUserMgr::Free() {
	/*�����������е��ã��ͷŻ����ڴ��е����ݣ���ֹ�ڴ�й©�Լ����ݶ�ʧ*/
	MapByAccountIter iterByAccount = m_mapByAccount.begin();
	MapByIdIter iterById = m_mapById.begin();
	while (iterById != m_mapById.end()) {
		delete iterById->second;//���ͷ��ڴ�
		iterById->second = nullptr;//�ÿ�
		iterById++;
	}
	m_mapByAccount.clear();
	m_mapById.clear();
}