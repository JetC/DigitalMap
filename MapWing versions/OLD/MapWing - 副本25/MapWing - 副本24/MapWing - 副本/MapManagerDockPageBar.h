#if !defined(AFX_MapManagerDOCKPAGEBAR_H__INCLUDED_)
#define AFX_MapManagerDOCKPAGEBAR_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapManagerDockPageBar.h : header file
//

#include "DockPageBar.h"
#include "StdAfx.h"
#include "AutoHideBar.h"
/////////////////////////////////////////////////////////////////////////////
// CMapManagerDockPageBar window

class CMapManagerDockPageBar : public CDockPageBar
{
// Construction
public:
	CMapManagerDockPageBar();
	using CDockPageBar::AddPage;
// Attributes
public:
	
// Operations
public:
	bool HideFloatWindow(CFrameWnd *pFrmame);

protected:
	bool HideFloatWindow(CAutoHideBar *pHideBar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapManagerDockPageBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL AddPage(CRuntimeClass* pClass,UINT nIDTemplate, LPCTSTR sText, UINT IconID);
	void SetActivePage(int nIndex);
	virtual ~CMapManagerDockPageBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMapManagerDockPageBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MapManagerDOCKPAGEBAR_H__INCLUDED_)
