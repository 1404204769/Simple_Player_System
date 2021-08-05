#include "UserMgr.h"
using namespace std;
using namespace mysqlpp;
CUserMgr::CUserMgr() {
	cout << "调用了CUserMgr的构造函数" << endl;
	m_mapById.clear();
	m_mapByAccount.clear();
}
CUserMgr::~CUserMgr() {
	cout << "调用了CUserMgr的析构函数" << endl;
	Free();
}
bool CUserMgr::AddUser(Row& row) {
	/*将准备新增的用户的数据保存在Map中*/
	try {
		if (!row)return false;
		string strAccount(row["account"]);
		long long int i64Id = row["id"];
		if (getId(strAccount) || getUser(i64Id)) {
			DeleteUser(strAccount);
			//cout << "上一个用户已被强制下线" << endl;
		}
		CUser *pUser=new CUser(row);
		if (!pUser) {
			cout << "用户登入失败" << endl;
			return false;
		}
		return AddToMap(pUser);
	}
	catch (const BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return false;
	}
	catch (const BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return false;
	}
	catch (const Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return false;
	}

}
bool CUserMgr::AddToMap(CUser* _pUser) {
	if (!_pUser)return false;
	m_mapByAccount[_pUser->getAccount()]= _pUser->getId();
	m_mapById[_pUser->getId()]= _pUser;
	if (m_mapByAccount.count(_pUser->getAccount()) == 0 || m_mapById.count(_pUser->getId())==0) {
		cout << "用户登入失败" << endl;
		DeleteUser(_pUser->getAccount());
		return false;
	}
	return true;
}
bool CUserMgr::Register(const string& _strAccount, const string& _strName) {
	/*参数为account,name,调用CDB的insert接口保存在数据库内*/
	if (!g_DB.Insert(_strAccount, _strName)) {
		cout << "用户注册成功" << endl;
		return false;
	}
	return true;
}
bool CUserMgr::DeleteFromMap(const string& _strAccount) {
	/*根据Account删除对应的User*/
	MapByAccountIter iterByAccount = m_mapByAccount.find(_strAccount);
	if (iterByAccount == m_mapByAccount.end()) {
		cout << "用户不在线 Account:" << _strAccount << endl;
		return false;
	}
	long long int i64Id = iterByAccount->second;
	m_mapByAccount.erase(iterByAccount);
	MapByIdIter iterById = m_mapById.find(i64Id);
	if (iterById == m_mapById.end()) {
		cout << "用户不在线 ID:" << iterByAccount->second << endl;
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
	/*从map里面查询，返回查询对象指针*/
	MapByIdIter iterById = m_mapById.find(_i64Id);
	if (iterById == m_mapById.end()) {
		cout << "Do not Find ID:" << _i64Id << endl;
		return nullptr;
	}
	return iterById->second;
}
long long int CUserMgr::getId(const std::string& _strAccount) {/*如果返回一个0说明该用户不在线*/
	MapByAccountIter iterByAccount = m_mapByAccount.find(_strAccount);
	if (iterByAccount == m_mapByAccount.end())return 0;
	return iterByAccount->second;
}
bool CUserMgr::SearchInDB(UseQueryResult& res,const string& _strAccount) {
	/*调用CDB函数查找指定对象,返回查询结果*/
	if (!g_DB.Search(res, "account", _strAccount))
		return false;
	return true;
}
void CUserMgr::Free() {
	/*在析构函数中调用，释放还在内存中的数据，防止内存泄漏以及数据丢失*/
	MapByAccountIter iterByAccount = m_mapByAccount.begin();
	MapByIdIter iterById = m_mapById.begin();
	while (iterById != m_mapById.end()) {
		delete iterById->second;//先释放内存
		iterById->second = nullptr;//置空
		iterById++;
	}
	m_mapByAccount.clear();
	m_mapById.clear();
}