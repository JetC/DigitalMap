// MapManager.h : main header file for the MAPManager application
//

#if !defined(AFX_MAPManager_H__EDD6A977_3765_4807_A717_4A969AD69953__INCLUDED_)
#define AFX_MAPManager_H__EDD6A977_3765_4807_A717_4A969AD69953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapManagerApp:
// See MapManager.cpp for the implementation of this class
//

typedef   void   (* STEPFUN)(int  iStep); 
extern STEPFUN GloabStepFun;


class CMapManagerApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMapManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMapManagerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPManager_H__EDD6A977_3765_4807_A717_4A969AD69953__INCLUDED_)
