#include "User.h"
using namespace std;
CUser::~CUser()
{
	g_DB.Update(m_i64Id,m_strAccount,m_strName,m_i64Exp,m_unLev);
	cout << "调用了CUser的析构函数" << endl;
}
CUser::CUser(long long int _id, std::string _account, std::string _time, std::string _name, long long int _exp, unsigned int _lev) {
	m_i64Id = _id;
	m_strAccount = _account;
	m_strCreateTime = _time;
	m_strName = _name;
	m_i64Exp = _exp;
	m_unLev = _lev;
	cout << "调用了CUser的构造函数" << endl;
	cout << "增加了(ID:"<<m_i64Id<<",Account:"<<m_strAccount<<",CreateTime:"<<m_strCreateTime<<",Name:"<<m_strName<<",Exp:"<<m_i64Exp<<",Lev:"<<m_i64Exp<<")" << endl;
}

std::string& CUser::getAccount() {
	return m_strAccount;
}
void CUser::setAccount(std::string _strAccount) {
	m_strAccount = _strAccount;
}

std::string& CUser::getCreateTime() {
	return m_strCreateTime;
}


std::string& CUser::getName() {
	return m_strName;
}
void CUser::setName(std::string _strName) {
	m_strName = _strName;
}


long long int CUser::getId() {
	return m_i64Id;
}
void CUser::setId(long long int _i64Id) {
	m_i64Id = _i64Id;
}


long long int CUser::getExp() {
	return m_i64Exp;
}
void CUser::setExp(long long int _i64Exp) {
	m_i64Exp = _i64Exp;
}

unsigned int CUser::getLev() {
	return m_unLev;
}
void CUser::setLev(unsigned int _unLev) {
	m_unLev = _unLev;
}