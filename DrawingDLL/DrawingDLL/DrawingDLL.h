// DrawingDLL.h : main header file for the DrawingDLL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDrawingDLLApp
// See DrawingDLL.cpp for the implementation of this class
//

class CDrawingDLLApp : public CWinApp
{
public:
	CDrawingDLLApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
