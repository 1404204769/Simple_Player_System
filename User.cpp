#include "User.h"
using namespace std;
CUser::~CUser()
{
	g_DB.Update(m_i64Id,m_strAccount,m_strName,m_i64Exp,m_unLev);
	cout << "调用了CUser的析构函数" << endl;
}

CUser::CUser(mysqlpp::Row & row) {
	try {
		if (!row) {
			cout << "CUser 构造函数发生错误，没有找到Row对象" << endl;
			return;
		}
		m_strAccount = row["account"];
		m_strCreateTime = row["create_time"];
		m_strName = row["name"];
		m_i64Exp = row["exp"];
		m_unLev = row["lev"];
		cout << "调用了CUser的构造函数" << endl;
		cout << "增加了(ID:" << m_i64Id << ",Account:" << m_strAccount << ",CreateTime:" << m_strCreateTime << ",Name:" << m_strName << ",Exp:" << m_i64Exp << ",Lev:" << m_i64Exp << ")" << endl;

	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return ;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return ;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return ;
	}

}
//CUser::CUser(const long long int _i64Id, const string& _strAccount, const string& _strTime, const string& _strName, const long long int _i64Exp, const unsigned int _unLev) {
//	m_i64Id = _i64Id;
//	m_strAccount = _strAccount;
//	m_strCreateTime = _strTime;
//	m_strName = _strName;
//	m_i64Exp = _i64Exp;
//	m_unLev = _unLev;
//	cout << "调用了CUser的构造函数" << endl;
//	cout << "增加了(ID:"<<m_i64Id<<",Account:"<<m_strAccount<<",CreateTime:"<<m_strCreateTime<<",Name:"<<m_strName<<",Exp:"<<m_i64Exp<<",Lev:"<<m_i64Exp<<")" << endl;
//}

const std::string& CUser::getAccount() {
	return m_strAccount;
}

const std::string& CUser::getCreateTime() {
	return m_strCreateTime;
}

const std::string& CUser::getName() {
	return m_strName;
}

const long long int CUser::getId() {
	return m_i64Id;
}

const long long int CUser::getExp() {
	return m_i64Exp;
}

const unsigned int CUser::getLev() {
	return m_unLev;
}

void CUser::setLev(const unsigned int _unLev) {
	m_unLev = _unLev;
}
void CUser::setName(const string& _strName) {
	m_strName = _strName;
}
void CUser::setExp(const long long int _i64Exp) {
	m_i64Exp = _i64Exp;
}