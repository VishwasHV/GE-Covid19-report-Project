
// Covid19.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCovid19App:
// See Covid19.cpp for the implementation of this class
//

class CCovid19App : public CWinApp
{
public:
	CCovid19App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCovid19App theApp;
