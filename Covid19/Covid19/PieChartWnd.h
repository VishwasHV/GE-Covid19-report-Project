#ifndef _H_PIEWND_
#define _H_PIEWND_

#include <gdiplus.h>
#include <vector>
using namespace Gdiplus;
using namespace std;
// CPieChartWnd


//extern map<int, string> pData;
class CPieChartWnd : public CWnd
{
	DECLARE_DYNAMIC(CPieChartWnd)

public:
	CPieChartWnd();
	virtual ~CPieChartWnd();

private:
	

	struct label_size{
		int wdth;
		int hght;
		int xGapLeft;
		int xGapRight;	//can b removed
		int yGap;
		CString sFont;
		INT fStyle;
	};
	struct	label_rect_info{
		int lbRctHght;
		int lbIndex;
		int lbVisibleRectHght;
		Color lbTextColor;
		Color lbValueRectColor;
		CString sMaxLenString;
	};

private:

	CScrollBar m_VscrollBar;
	float fl_startAngle;
	double d_totalVal;	//Set this color to paint the outline of the window in the same color of parent
	label_size lb_param;
	label_rect_info lb_info;

	Color cr_HighlightColor;
	ULONG_PTR m_gdiplusToken;
	Graphics* m_graphics;

protected:
	DECLARE_MESSAGE_MAP()
	
private: //internal functions//
	
	void DrawLabels(Graphics* graphics);	
	void GetBoundRect(LPRECT rect);	
	void CalculateLabelRect(void);	
	void DrawRect();

public: 

	vector<pair<int, string>> pData;
	void DrawPieChart(CDC* pDc);
	void RemoveItem();


	void Copydata(vector<pair<int, string>> pdata);
	
	//Remove item functions
	virtual BOOL Create(LPCTSTR lpCaption, const RECT& rect, CWnd* pParentWnd, UINT nID,vector<pair<int,string>>);
private:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#endif // 


