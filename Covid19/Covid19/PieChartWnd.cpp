// PieChartWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PieChartWnd.h"
#include <math.h>
#include <limits>
#include <string>
#define MAX_LABELHEIGHT		25
#define MAX_LABELGAP		18
#define PI			3.14159265
#define MAX_PIECHARTPARAMS	150

// CPieChartWnd

IMPLEMENT_DYNAMIC(CPieChartWnd, CWnd)

CPieChartWnd::CPieChartWnd()
{
	
}

CPieChartWnd::~CPieChartWnd()
{
	
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
}


BEGIN_MESSAGE_MAP(CPieChartWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CPieChartWnd message handlers



void CPieChartWnd::OnPaint()
{

	CPaintDC dc(this);
	DrawPieChart(&dc);
}



int CPieChartWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//This is to stop the flickering effects on scrollbar on resizing and painting.
	ModifyStyle(0, WS_CLIPCHILDREN);
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	
	CRect rect;
	GetClientRect(rect);
	m_VscrollBar.Create(WS_CHILD | SBS_VERT, 
		CRect(rect.right -40, rect.top + 10, rect.right -20, rect.bottom - 10), 
		this, 
		1);
	return 0;
}
void CPieChartWnd::GetBoundRect(LPRECT rect){

	try
	{
		CRect rectWn;
		GetClientRect(rectWn);
		
		rectWn.right = lb_param.xGapLeft;
		rectWn.top += 100;
		rectWn.left += 30;
		rectWn.bottom -= 30;

		if (rectWn.Height() > rectWn.Width()){
			rectWn.right = max(rectWn.right, (rectWn.left + MAX_PIECHARTPARAMS));
			rectWn.bottom = rectWn.top + rectWn.Width();
		}
		else{
			rectWn.bottom = max(rectWn.bottom, (rectWn.top + MAX_PIECHARTPARAMS));
			rectWn.right = rectWn.left + rectWn.Height();
		}


		CopyRect(rect, &rectWn);
	}
	catch (...)
	{
		DWORD dw = GetLastError();
	}
}

void CPieChartWnd::DrawLabels(Graphics* graphics){
	CRect rect;
	CRect rectBnd;
	StringFormat strFormat;
	REAL iValueRectPos = 0;
	REAL iTextBoundLen = 0;
	RectF labelTextRect;
	RectF textArea;	
	SolidBrush brRect(Color::Black);;
	Pen pnRect(Color::Black, 2);
	SolidBrush brText(lb_info.lbTextColor); 
	SolidBrush brValueRect(lb_info.lbValueRectColor); 
	Color crRectLight;
	
	GetBoundRect(rectBnd);
	GetClientRect(rect);
	//Color to paint the seperators in % value boxes
	Color crLight =Color::Blue;	
	Pen pnVal(crLight, 1);	
	
	rect.top = rectBnd.top;
	rect.bottom = rectBnd.bottom;

	strFormat.SetFormatFlags(StringFormatFlagsLineLimit);
	
	int iFontSize = min(rectBnd.Height() / 25, 11);

	Gdiplus::Font textF(L"Helvetica", (REAL)iFontSize, 3, UnitPoint, NULL);
	
	int iStartHght = max(rectBnd.CenterPoint().y - ((lb_param.hght + lb_param.yGap) * pData.size())/2, //The starting height calculated by deviding elements to 
							  rectBnd.top);															//upper and lower halfs taken from the center point.
					
	
	int iLabelTextSt =  lb_param.wdth + 6 * rectBnd.right / 5; //The horizontal starting position for the label text
	
	graphics->MeasureString(lb_info.sMaxLenString,							
							lb_info.sMaxLenString.GetLength(),				
							&textF, 
							RectF((REAL)iLabelTextSt,0, 0, 0), 
							&labelTextRect); 
		
	if (labelTextRect.GetRight() > rect.right - lb_param.xGapRight)
		labelTextRect.Width =  rect.right - (labelTextRect.X + lb_param.xGapRight);

	iValueRectPos = (REAL)iLabelTextSt + labelTextRect.Width + rectBnd.right / 30;		


	iTextBoundLen = textArea.Width;			
	
	if (iValueRectPos + iTextBoundLen > rect.right - lb_param.xGapRight)
		iTextBoundLen =  (REAL)rect.right - ((REAL)lb_param.xGapRight + iValueRectPos);
	


	graphics->FillRectangle(&brValueRect,		//Fill the value showing rectangle area
							RectF(iValueRectPos, 
								  (REAL)iStartHght, 
								  iTextBoundLen, 
								  (REAL)(min(lb_info.lbRctHght, lb_info.lbVisibleRectHght))
								  ));
	int iStartH = iStartHght;

	//Draw each color label, item label and the value on corresponding offsets.
	int index = 0;
	while (iStartH + lb_param.hght <= rectBnd.bottom && pData.size()>0 && index < pData.size() - 1){
		Color col;
		CString name,sPer;
		float fperc;
		if (index == 0) 
		{ 
			col = Color::Green; 
			name = pData[index].second.c_str(); 
			sPer = pData[index + 2].second.c_str();
			fperc = _ttof(sPer);
			fperc = fperc * 100;
			sPer.Format(L"%.2f", fperc);
		
		}
		if (index == 4) 
		{ 
			col = Color::Red; 
			name = pData[index].second.c_str();
			sPer = pData[index + 2].second.c_str();
			fperc = _ttof(sPer);
			fperc = fperc * 100;
			sPer.Format(L"%.2f", fperc);
		}
		if (index == 8) 
		{ 
			col = Color::Blue; 
			name = pData[index].second.c_str();
			sPer = pData[index + 2].second.c_str();
			fperc = _ttof(sPer);
			fperc = fperc * 100;
			sPer.Format(L"%.2f", fperc);
		}
		brRect.SetColor(col);
		//crRectLight = CalculateGradientLight(ele->cr_Base, 200);
		pnRect.SetColor(crRectLight);
		graphics->FillRectangle(&brRect,
			RectF(REAL(rectBnd.right + rectBnd.right / 10),
			(REAL)iStartH,
			(REAL)lb_param.wdth,
			(REAL)lb_param.hght));
		graphics->DrawRectangle(&pnRect,
			RectF(REAL(rectBnd.right + rectBnd.right / 10),
			(REAL)iStartH,
			(REAL)lb_param.wdth,
			(REAL)lb_param.hght));
		graphics->DrawString(name+ " - " +sPer+"%",
			name.GetLength() + sPer.GetLength()+4,
			&textF,
			RectF(REAL(iLabelTextSt),
			(REAL)(iStartH),
			labelTextRect.Width,
			(REAL)lb_param.hght),
			&strFormat,
			&brText);
		REAL yPos = (REAL)iStartH + lb_param.hght + REAL(lb_param.yGap / 2);

		PointF ptStart(REAL(iValueRectPos), yPos);
		PointF ptEnd(REAL(iValueRectPos + iTextBoundLen), yPos);

		if (yPos - iStartHght < lb_info.lbVisibleRectHght && iTextBoundLen > 0)
			graphics->DrawLine(&pnVal, ptStart, ptEnd);

		CString sValue;
		if (pData.size() > 3)
		{
			sValue.Format(L"%.2f", stof(pData[index + 2].second) * 100);
			sValue.Append(L"%");
		}
		if (pData.size() > 3)
		{
			if (stof(pData[index + 2].second) * 100 < 10)
				sValue = L"0" + sValue;
		}

			if(iTextBoundLen > 0)
				graphics->DrawString(sValue, 
									 sValue.GetLength() + 8, 
									 &textF, 
									 RectF(REAL(iValueRectPos + 1), 
										   (REAL)iStartH, 
										   (REAL)iTextBoundLen, 
										   (REAL)textArea.Height), 
									 &strFormat, 
									 &brText);
			iStartH += (lb_param.hght + lb_param.yGap);
			index = index + 4;
	}
	
	
}
void CPieChartWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	CRect rect;
	CRect rectBnd;
	GetClientRect(rect);
	lb_param.xGapLeft =  max(2 * rect.Width() / 3, MAX_PIECHARTPARAMS + 30);
	lb_param.xGapRight = rect.Width() / 20;

	GetBoundRect(rectBnd);
	//Reset the label sizes on sizing the client area
	lb_param.hght = min(rectBnd.Height() / 15, MAX_LABELHEIGHT);
	lb_param.wdth = min(rectBnd.Width() , MAX_LABELHEIGHT * 15) / 8;
	lb_param.yGap = min (rectBnd.Height() / 20, MAX_LABELGAP);
	
}




void CPieChartWnd::DrawPieChart(CDC* pDc)
{
	
	CRect rect;	
	CRect rectBnd;
	Bitmap* mBtmap;
	//Graphics* graphics;
	float totalAngle = fl_startAngle;

	
	GetBoundRect(rectBnd);
	GetClientRect(rect);
	mBtmap = new Bitmap(rect.Width(), rect.Height());
	m_graphics = Graphics::FromImage(mBtmap);

	m_graphics->SetSmoothingMode(SmoothingModeHighQuality);
	
	LinearGradientBrush brBkgndInner(PointF((REAL)rect.left, (REAL) rect.top), 
								 PointF((REAL)rect.right, (REAL)rect.bottom), 
								 Color::White, 
								 Color::White);
	
	REAL penWidth = REAL(lb_param.xGapLeft / 150);
	Pen penOutLine(&brBkgndInner, penWidth);

//	DrawBackGround(graphics);

	REAL rRatio = (REAL)rectBnd.Width() / 25;

	LinearGradientBrush crGradient(Point(rectBnd.right/2, rectBnd.top), 
								   Point(rectBnd.right/2, rectBnd.bottom), 
								   Color(0,0,0), 
								   Color(0,0,0));
	

		SolidBrush brValueRect(Color::White);
		Gdiplus::Rect rr(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		m_graphics->FillRectangle(&brValueRect, rr); 
		

	
	SolidBrush brHighLight(Color(100, cr_HighlightColor.GetR(), cr_HighlightColor.GetG(), cr_HighlightColor.GetB()));
	Pen pnHighLight(cr_HighlightColor);



	string sAngle;
	double dAngle;
	for (int i = 0; i < pData.size();i=i+4)
	{
		sAngle = pData[i + 3].second;
		dAngle = stof(sAngle);
		Color col;
		if (i == 0) { col = Color::Green; }
		if (i == 4) { col = Color::Red; }
		if (i == 8) { col = Color::Blue; }
		crGradient.SetLinearColors(Color::Black, col);
		m_graphics->FillPie(&crGradient,
							  RectF((REAL)rectBnd.left, 
									(REAL)rectBnd.top, 
									(REAL)rectBnd.Width(), 
									(REAL)rectBnd.Height()), 
							  (REAL)totalAngle, 
							  (REAL)dAngle);
			
		crGradient.SetLinearColors(col, Color::Black);
			
			m_graphics->FillPie(&crGradient,
							  RectF(REAL(rectBnd.left + rRatio), 
							  REAL(rectBnd.top + rRatio), 
							  REAL(rectBnd.Width() - rRatio * 2), 
							  REAL(rectBnd.Height()- rRatio * 2)), 
							  (REAL)totalAngle, 
							  (REAL)dAngle);

		
			totalAngle += dAngle;
	}
	totalAngle = fl_startAngle;
	for (int i = 0; i < pData.size(); i = i + 4)
	{
		sAngle = pData[i + 3].second;
		dAngle = stof(sAngle);
		
		REAL xPoint = REAL(rectBnd.CenterPoint().x + 
			(rectBnd.Width() / 2) * cos(PI * (totalAngle + dAngle) / 180));
		REAL yPoint = REAL(rectBnd.CenterPoint().y + 
			(rectBnd.Height() / 2) * sin(PI * (totalAngle + dAngle) / 180));

		m_graphics->DrawLine(&penOutLine, PointF(REAL(rectBnd.CenterPoint().x), REAL(rectBnd.CenterPoint().y)),
										PointF(xPoint, yPoint));
		Gdiplus::Font textF(L"", (REAL)12, 1, UnitPoint, NULL);

		totalAngle += dAngle;
	}
	
	DrawLabels(m_graphics);

	Graphics gr(pDc->m_hDC);
	CachedBitmap* btmp = new CachedBitmap(mBtmap, &gr);

	if (mBtmap){
		delete mBtmap;
		mBtmap = NULL;
	}
	gr.DrawCachedBitmap(btmp, rect.left, rect.top);	
	if (btmp){
		delete btmp;
		btmp = NULL;
	}

}



BOOL CPieChartWnd::Create(LPCTSTR lpCaption, const RECT& rect, CWnd* pParentWnd, UINT nID, vector<pair<int, string>> pdata)
{
	pData = pdata;
	return CWnd::Create(NULL, NULL, WS_VISIBLE, rect, pParentWnd, nID, NULL);
}


void CPieChartWnd::RemoveItem()
{
	try
	{
		
		pData.clear();
		
	}
	catch (exception &ex){}
}

void CPieChartWnd::Copydata(vector<pair<int, string>> pdata)
{
	pData = pdata;
	Invalidate();
}