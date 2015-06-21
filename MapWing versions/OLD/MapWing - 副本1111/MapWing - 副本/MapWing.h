// MapWing.h : main header file for the MAPWING application
//

#if !defined(AFX_MAPWING_H__EDD6A977_3765_4807_A717_4A969AD69953__INCLUDED_)
#define AFX_MAPWING_H__EDD6A977_3765_4807_A717_4A969AD69953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapWingApp:
// See MapWing.cpp for the implementation of this class
//

typedef   void   (* STEPFUN)(int  iStep); 
extern STEPFUN GloabStepFun;


class CMapWingApp : public CWinApp
{
public:
	CToolTipCtrl m_tooltip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMapWingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapWingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMapWingApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPWING_H__EDD6A977_3765_4807_A717_4A969AD69953__INCLUDED_)
