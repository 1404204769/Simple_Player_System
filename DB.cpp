#include "DB.h"
using namespace std;
using namespace mysqlpp;
CDB::CDB() :m_Conn(true), m_strDB(""), m_strServer(""), m_strUser(""), m_strPassword(""), m_nPort(0) 
{ 
	cout << "������CDB�Ĺ��캯��" << endl; 
}
CDB::~CDB() 
{ 
	cout << "������CDB����������" << endl; 
}
bool CDB::InitConnect(const string& strDB, const string& strServer, const string& strUser, const string& strPassword, const int& nPort) {
	try {
		/*�������ݿ�����*/
		m_strDB = strDB;
		m_strServer = strServer;
		m_strUser = strUser;
		m_strPassword = strPassword;
		m_nPort = nPort;
		if (!m_Conn.set_option(new mysqlpp::SetCharsetNameOption("latin1")))return false;//�����ַ�����Ϊuft8
		if (!m_Conn.set_option(new mysqlpp::ReconnectOption(true)))return false;
		if (!m_Conn.connect(m_strDB.c_str(), m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_nPort)) {
			//cout << m_Conn.error() << endl;
			cout << "���ݿ�����ʧ��" << endl;
			return false;
		}
		Query query = m_Conn.query("set names latin1");
		if (!query)return false;
		if (!query.exec())
			cout << "����latin1��ʽʧ��" << endl;
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
	/*��ѯd_user���ڵ�ָ����Ϣ*/
	try {
		/*������������ݿ���Ͷ�Ӧ��ֵ��ѯ�Ƿ����*/
		Query query = m_Conn.query();
		if (!query) {
			cout << "QueryʧЧ������������" << endl;
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
	/*����һ���µ�ֵ�����ݿ���*/
	try {
		Query query = m_Conn.query();
		if (!query) {
			cout << "QueryʧЧ������������" << endl;
			return false;
		}
		query << "insert into d_user(account,name) values(%0q:account, %1q:name)";
		query.parse();
		query.template_defaults["account"] = _strAccount.c_str();
		query.template_defaults["name"] = _strName.c_str();
		//cout << "Query:" << query.str() << endl;
		if (!query)return false;
		if (!query.exec()) {
			//cout << "����ʧ��" << endl;
			return false;
		}
		//cout << "����ɹ�" << endl;
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
	/*�����ݿ��ж�Ӧ�������޸�*/
	try {
		Query query = m_Conn.query();
		if (!query) {
			cout << "QueryʧЧ������������" << endl;
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
			//cout << ����ʧ��" << endl;
			return false;
		}
		//cout << "���³ɹ�" << endl;
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