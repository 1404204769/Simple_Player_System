#include "User.h"
using namespace std;
CUser::~CUser()
{
	g_DB.Update(m_i64Id,m_strAccount,m_strName,m_i64Exp,m_unLev);
	cout << "������CUser����������" << endl;
}
CUser::CUser(const long long int _i64Id, const string& _strAccount, const string& _strTime, const string& _strName, const long long int _i64Exp, const unsigned int _unLev) {
	m_i64Id = _i64Id;
	m_strAccount = _strAccount;
	m_strCreateTime = _strTime;
	m_strName = _strName;
	m_i64Exp = _i64Exp;
	m_unLev = _unLev;
	cout << "������CUser�Ĺ��캯��" << endl;
	cout << "������(ID:"<<m_i64Id<<",Account:"<<m_strAccount<<",CreateTime:"<<m_strCreateTime<<",Name:"<<m_strName<<",Exp:"<<m_i64Exp<<",Lev:"<<m_i64Exp<<")" << endl;
}

std::string& CUser::getAccount() {
	return m_strAccount;
}

std::string& CUser::getCreateTime() {
	return m_strCreateTime;
}

std::string& CUser::getName() {
	return m_strName;
}
void CUser::setName(const string& _strName) {
	m_strName = _strName;
}

long long int CUser::getId() {
	return m_i64Id;
}

long long int CUser::getExp() {
	return m_i64Exp;
}
void CUser::setExp(const long long int _i64Exp) {
	m_i64Exp = _i64Exp;
}

unsigned int CUser::getLev() {
	return m_unLev;
}
void CUser::setLev(const unsigned int _unLev) {
	m_unLev = _unLev;
}