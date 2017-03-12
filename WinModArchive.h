// WinModArchive.h : main header file for the WINMODARCHIVE application
//

#if !defined(AFX_WINMODARCHIVE_H__0F2FADE8_C472_4CBF_80EC_C3BC797E24D8__INCLUDED_)
#define AFX_WINMODARCHIVE_H__0F2FADE8_C472_4CBF_80EC_C3BC797E24D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinModArchiveApp:
// See WinModArchive.cpp for the implementation of this class
//

class CWinModArchiveApp : public CWinApp
{
public:
	CWinModArchiveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinModArchiveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinModArchiveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINMODARCHIVE_H__0F2FADE8_C472_4CBF_80EC_C3BC797E24D8__INCLUDED_)
