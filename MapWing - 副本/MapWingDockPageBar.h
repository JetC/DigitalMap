#if !defined(AFX_MapWingDOCKPAGEBAR_H__INCLUDED_)
#define AFX_MapWingDOCKPAGEBAR_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapWingDockPageBar.h : header file
//

#include "DockPageBar.h"
#include "StdAfx.h"
#include "AutoHideBar.h"
/////////////////////////////////////////////////////////////////////////////
// CMapWingDockPageBar window

class CMapWingDockPageBar : public CDockPageBar
{
// Construction
public:
	CMapWingDockPageBar();
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
	//{{AFX_VIRTUAL(CMapWingDockPageBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL AddPage(CRuntimeClass* pClass,UINT nIDTemplate, LPCTSTR sText, UINT IconID);
	void SetActivePage(int nIndex);
	virtual ~CMapWingDockPageBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMapWingDockPageBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MapWingDOCKPAGEBAR_H__INCLUDED_)
