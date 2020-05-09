#pragma once


#include "afxdb.h"
#include <string>
#include<vector>

using namespace std;
class Database
{
private:
	Database();
	CDatabase* m_database;

	vector<CString> countries;
public:
	~Database();
	bool IntializeDatabase();
	static Database* GetInstance();

//	void GetPieDetails();

	void GetPieDetails(CString Country, CString FromDate, CString ToDate);

	

	vector<pair<string,string>> pPieDetais;


	vector<CString>* GetCountriesName();
};
