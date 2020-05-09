#include "stdafx.h"
#include "Database.h"




Database::Database()
{
	m_database = NULL;
}

Database::~Database()
{
	m_database->Close();
}

Database* Database::GetInstance()
{
	static Database* pInstance = NULL;

	if (pInstance == NULL)
		return pInstance = new Database();

	else return pInstance;
}


bool Database::IntializeDatabase()
{
	
	CString SqlString;
	CString strID, strName, strAge;
	CString sDriver = L"MICROSOFT ACCESS DRIVER (*.mdb)";
	CString sDsn;
	CString sFile = L"Covid.mdb";
	bool bStatus = false;
	int iRec = 0;
	 m_database = new CDatabase();
	sDsn.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	try{
		m_database->Open(NULL, false, false, sDsn);
		//m_database->Close();
		bStatus = true;
	}
	catch(CDBException e) 
	{
		AfxMessageBox(L"Database error: "+e.m_strError );
		long dd = GetLastError();
		bStatus = false;	
	}
	catch(...)
	{
		long dd = GetLastError();
		bStatus = false;
	}
	return bStatus;
}

//
vector<CString>* Database::GetCountriesName()
{
	CString SqlString = L"select distinct Country from Covid19";
	CRecordset recset(m_database);
	CString sCountry;

	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	if (countries.size() > 0){ countries.clear(); }
	while (!recset.IsEOF())
	{
		recset.GetFieldValue(L"Country", sCountry);
		countries.push_back(sCountry);
		recset.MoveNext();
	}
	recset.Close();
	return &countries;
}


void Database::GetPieDetails(CString Country, CString FromDate, CString ToDate)
{
	CString sqlQuery;
	if (Country == "All")
	{
		sqlQuery.Format(L"SELECT Affected, Recovered, Death from covid19 where Date BETWEEN #%s# And #%s#", FromDate, ToDate);
	}
	else
	{
		sqlQuery.Format(L"SELECT Affected, Recovered, Death from covid19 where Date BETWEEN #%s# And #%s# AND Country = '%s'", FromDate, ToDate, Country);
	}

	CRecordset recset(m_database);
	CString sAffected,sRecovered,sDeath;

	int nAffected=0, nRecovered =0, nDeath =0;
	recset.Open(CRecordset::forwardOnly, sqlQuery, CRecordset::readOnly);
	while (!recset.IsEOF())
	{
		recset.GetFieldValue(L"Affected", sAffected);
		recset.GetFieldValue(L"Recovered", sRecovered);
		recset.GetFieldValue(L"Death", sDeath);
		nAffected += _ttoi(sAffected);
		nRecovered += _ttoi(sRecovered);
		nDeath += _ttoi(sDeath);
		recset.MoveNext();
	}
	recset.Close();
	string sAff, sRec, sDea;
	sAff = to_string(nAffected);
	sRec = to_string(nRecovered);
	sDea = to_string(nDeath);
	pPieDetais.clear();
	pPieDetais.push_back(make_pair("Affected", sAff));
	pPieDetais.push_back(make_pair("Recovered", sRec));
	pPieDetais.push_back(make_pair("Death", sDea));


}