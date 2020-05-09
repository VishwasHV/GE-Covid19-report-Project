
// Covid19Dlg.h : header file
//
#include "PieChartWnd.h"
#include "Database.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include <vector>
using namespace Gdiplus;
#pragma once


//

vector<pair<int, string>>  _declspec(dllimport)  APICall(vector<pair<string,string>>&,int);
// CCovid19Dlg dialog
class CCovid19Dlg : public CDialogEx
{
// Construction
public:
	CCovid19Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_Covid19_DIALOG };


private:

	BOOL Initialize();
	void UpdatePieData();
	bool m_bTimer;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	CPieChartWnd m_pieChart;
	CRect rect;

	void FillCountries();
	vector<pair<int, string>> pData;

	enum SHAPES
	{
		PIE,
		BAR
	};
	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void CreateClientArea();
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_Country;
	CDateTimeCtrl m_cFromDate;
	CDateTimeCtrl m_cToDate;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSelchangeComboCountry();
	afx_msg void OnDatetimechangeFromdate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDatetimechangeTodate(NMHDR *pNMHDR, LRESULT *pResult);
};
