#include "DB.h"
using namespace std;
using namespace mysqlpp;
CDB::CDB() :m_Conn(true), m_strDB(""), m_strServer(""), m_strUser(""), m_strPassword(""), m_nPort(0) 
{ 
	cout << "调用了CDB的构造函数" << endl; 
}
CDB::~CDB() 
{ 
	cout << "调用了CDB的析构函数" << endl; 
}
bool CDB::InitConnect(const string& strDB, const string& strServer, const string& strUser, const string& strPassword, const int& nPort) {
	try {
		/*建立数据库连接*/
		m_strDB = strDB;
		m_strServer = strServer;
		m_strUser = strUser;
		m_strPassword = strPassword;
		m_nPort = nPort;
		if (!m_Conn.set_option(new mysqlpp::SetCharsetNameOption("latin1")))return false;//设置字符编码为uft8
		if (!m_Conn.set_option(new mysqlpp::ReconnectOption(true)))return false;
		if (!m_Conn.connect(m_strDB.c_str(), m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_nPort)) {
			//cout << m_Conn.error() << endl;
			cout << "数据库链接失败" << endl;
			return false;
		}
		Query query = m_Conn.query("set names latin1");
		if (!query)return false;
		if (!query.exec())
			cout << "设置latin1格式失败" << endl;
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return false;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return false;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return false;
	}
	return true;
}
bool CDB::Search(UseQueryResult& res, const string& _strColumn, const string& _strVal) {
	/*查询d_user表内的指定信息*/
	try {
		/*根据输入的数据库项和对应的值查询是否存在*/
		Query query = m_Conn.query();
		if (!query) {
			cout << "Query失效，请重新连接" << endl;
			return false;
		}
		query << "select * from d_user where %0:column = %1q:value;";
		query.parse();
		query.template_defaults["column"] = _strColumn.c_str();
		query.template_defaults["value"] = _strVal.c_str();
		cout << "Query:" << query << endl;
		if (!query)return false;
		res = query.use();
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
	return true;      
}
bool CDB::Insert(string _strAccount, string _strName) {
	/*插入一条新的值到数据库中*/
	try {
		Query query = m_Conn.query();
		if (!query) {
			cout << "Query失效，请重新连接" << endl;
			return false;
		}
		query << "insert into d_user(account,name) values(%0q:account, %1q:name)";
		query.parse();
		query.template_defaults["account"] = _strAccount.c_str();
		query.template_defaults["name"] = _strName.c_str();
		//cout << "Query:" << query.str() << endl;
		if (!query)return false;
		if (!query.exec()) {
			//cout << "插入失败" << endl;
			return false;
		}
		//cout << "插入成功" << endl;
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
	return true;
}
bool CDB::Update(long long int _i64Id, string _strAccount, string _strName, long long int _i64Exp, unsigned int _unLev) {
	/*将数据库中对应的数据修改*/
	try {
		Query query = m_Conn.query();
		if (!query) {
			cout << "Query失效，请重新连接" << endl;
			return false;
		}
		query << "update `d_user` set account=%0q:account,`name`=%1q:name,exp=%2:exp,lev=%3:lev where id=%4:id;";
		query.parse();
		query.template_defaults["account"] = _strAccount.c_str();
		query.template_defaults["name"] = _strName.c_str();
		query.template_defaults["exp"] = _i64Exp;
		query.template_defaults["lev"] = _unLev;
		query.template_defaults["id"] = _i64Id;
		//cout << "Query:" << query.str() << endl;
		if (!query)return false;
		if (!query.exec()) {
			//cout << 更新失败" << endl;
			return false;
		}
		//cout << "更新成功" << endl;
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
	return true;
}