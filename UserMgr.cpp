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
bool CUserMgr::AddUser(UseQueryResult& res) {
	/*��׼���������û������ݱ�����Map��*/
	if (!res)return false;
	int nNum = 0;
	if(Row row = res.fetch_row())
	{
		nNum++;
		long long int _i64Id=row["id"];
		string _strAccount(row["account"]);
		string _strTime(row["create_time"]);
		string _strName(row["name"]);
		long long int _i64Exp = row["exp"];
		unsigned int _unLev = row["lev"];
		CUser *user=new CUser(_i64Id,_strAccount,_strTime,_strName, _i64Exp, _unLev);
		if (!user)return false;
		pair<map<string,long long int>::iterator, bool> _pairByAccount;
		_pairByAccount = m_mapByAccount.insert(pair<string, long long int>(user->getAccount(), user->getId()));
		if (!_pairByAccount.second) {
			cout << "���û�����ϵͳ�е���" << endl;
			return false;
		}
		pair<map<long long int, CUser*>::iterator, bool> _pairById;
		_pairById=m_mapById.insert(pair<long long int, CUser*>(user->getId(), user));
		if (!_pairById.second) {
			cout << "���û�����ϵͳ�е���" << endl;
			return false;
		}
	}
	else
		return false;
	if (nNum == 0)return false;

	return true;
}
bool CUserMgr::DeleteUser(string& _strAccount) {
	/*����Accountɾ����Ӧ��User*/
	map<string, long long int>::iterator _iterByAccount=m_mapByAccount.find(_strAccount);
	if (_iterByAccount == m_mapByAccount.end()) {
		cout << "Do not Find Account:"<<_strAccount << endl;
		return false;
	}
	map<long long int, CUser*>::iterator _iterById=m_mapById.find(_iterByAccount->second);
	if (_iterById == m_mapById.end()) {
		cout << "Do not Find ID:" << _iterByAccount->second << endl;
		return false;
	}
	m_mapByAccount.erase(_iterByAccount);
	delete _iterById->second;
	_iterById->second = nullptr;
	m_mapById.erase(_iterById);
	return true;
}
CUser* CUserMgr::getUser(long long int _i64Id) {
	/*��map�����ѯ�����ز�ѯ����ָ��*/
	map<long long int, CUser*>::iterator _iterById = m_mapById.find(_i64Id);
	if (_iterById == m_mapById.end()) {
		cout << "Do not Find ID:" << _i64Id << endl;
		return nullptr;
	}
	return _iterById->second;
}
long long int CUserMgr::getId(std::string _strAccount) {/*�������һ������˵�����û�������*/
	map<string, long long int>::iterator _iterByAccount = m_mapByAccount.find(_strAccount);
	if (_iterByAccount == m_mapByAccount.end())return -1;
	return _iterByAccount->second;
}
bool CUserMgr::SearchInDB(UseQueryResult& res,string _strAccount) {
	/*����CDB��������ָ������,���ز�ѯ���*/
	if (!g_DB.Search(res, "account", _strAccount))
		return false;
	return true;
}
void CUserMgr::Free() {
	/*�����������е��ã��ͷŻ����ڴ��е����ݣ���ֹ�ڴ�й©�Լ����ݶ�ʧ*/
	map<string, long long int>::iterator _iterByAccount = m_mapByAccount.begin();
	map<long long int, CUser*>::iterator _iterById = m_mapById.begin();
	while (_iterById != m_mapById.end()) {
		delete _iterById->second;//���ͷ��ڴ�
		_iterById->second = nullptr;//�ÿ�
		m_mapById.erase(_iterById++);//ɾ��
	}
	m_mapByAccount.clear();
}