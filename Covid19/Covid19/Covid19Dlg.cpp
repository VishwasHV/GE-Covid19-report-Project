
// Covid19Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Covid19.h"
#include "Covid19Dlg.h"
#include "PieChartWnd.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define  IDT_TIMER  WM_USER + 200 


// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCovid19Dlg dialog



CCovid19Dlg::CCovid19Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCovid19Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bTimer = false;
}

void CCovid19Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COUNTRY, m_Country);
	DDX_Control(pDX, IDC_FROMDATE, m_cFromDate);
	DDX_Control(pDX, IDC_TODATE, m_cToDate);
}

BEGIN_MESSAGE_MAP(CCovid19Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCovid19Dlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_COUNTRY, &CCovid19Dlg::OnSelchangeComboCountry)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_FROMDATE, &CCovid19Dlg::OnDatetimechangeFromdate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TODATE, &CCovid19Dlg::OnDatetimechangeTodate)
END_MESSAGE_MAP()


// CCovid19Dlg message handlers

BOOL CCovid19Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	Initialize();



	pData = APICall(Database::GetInstance()->pPieDetais, SHAPES::PIE);


	CreateClientArea();

	SetTimer(IDT_TIMER, 1000*60, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCovid19Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CCovid19Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CCovid19Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCovid19Dlg::CreateClientArea()
{
	try
	{
		GetClientRect(rect);
		rect.left = 30;
		rect.top = 100;
		rect.bottom -= 10;
		rect.right -= 10;
		m_pieChart.Create(L"Pie Chart", rect, this, 1, pData);
	}
	catch (exception &e){}
}



void CCovid19Dlg::FillCountries()
{
	try
	{
		vector<CString>* countries;
		countries = Database::GetInstance()->GetCountriesName();
		vector<CString>::iterator itr = countries->begin();

		m_Country.AddString(L"All");
		for (; itr != countries->end(); itr++)
		{
			m_Country.AddString(*itr);
		}
	}
	catch (exception &e){}
}


void CCovid19Dlg::OnBnClickedOk()
{
	
	CDialogEx::OnOK();
}


BOOL CCovid19Dlg::Initialize()
{
	struct tm newtime;
	time_t now = time(NULL);
	now = now - (24 * 90 * 60 * 60);
	localtime_s(&newtime, &now);
	int year = (newtime.tm_year - 100) + 2000;
	COleDateTime oletime(year, newtime.tm_mon + 1, newtime.tm_mday, 0, 0, 0);
	m_cFromDate.SetTime(oletime);

	
	if (!Database::GetInstance()->IntializeDatabase()) return false;

	CTime tmStartDate, tmEndDate;
	m_cFromDate.GetTime(tmStartDate);
	m_cToDate.GetTime(tmEndDate);

	CString FromDate = tmStartDate.Format(_T("%m/%d/%Y"));

	CString EndDate = tmEndDate.Format(_T("%m/%d/%Y"));

	
	this->FillCountries();
	m_Country.SetCurSel(0);
	Database::GetInstance()->GetPieDetails(L"All", FromDate, EndDate);
	return true;
}



void CCovid19Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_bTimer = true;
	UpdatePieData();
	m_bTimer = false;
	CDialogEx::OnTimer(nIDEvent);
}


void CCovid19Dlg::OnSelchangeComboCountry()
{
	// TODO: Add your control notification handler code here
	UpdatePieData();
	
}


void CCovid19Dlg::OnDatetimechangeFromdate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdatePieData();
}


void CCovid19Dlg::OnDatetimechangeTodate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdatePieData();
}

void CCovid19Dlg::UpdatePieData()
{
	try
	{
		CTime tmStartDate, tmEndDate;
		m_cFromDate.GetTime(tmStartDate);
		m_cToDate.GetTime(tmEndDate);

		if (tmEndDate < tmStartDate) { AfxMessageBox(L"Invalid date range"); return; }

		if (m_Country.GetCurSel() == -1) { if (!m_bTimer)AfxMessageBox(L"Invalid country"); return; }


		m_pieChart.RemoveItem();
		CString FromDate = tmStartDate.Format(_T("%m/%d/%Y"));

		CString EndDate = tmEndDate.Format(_T("%m/%d/%Y"));


		CString country;
		m_Country.GetLBText(m_Country.GetCurSel(), country);


		Database::GetInstance()->GetPieDetails(country, FromDate, EndDate);

		pData = APICall(Database::GetInstance()->pPieDetais, SHAPES::PIE);
		m_pieChart.Copydata(pData);

	}
	catch (exception &e){}

}
