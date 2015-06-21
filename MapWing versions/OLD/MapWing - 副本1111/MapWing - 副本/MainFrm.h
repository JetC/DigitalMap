// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__C836198B_2FE7_4AF6_ABC0_77679F4BE0FB__INCLUDED_)
#define AFX_MAINFRM_H__C836198B_2FE7_4AF6_ABC0_77679F4BE0FB__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"StdAfx.h"
#include "MapTree.h"
#include "HawkeyeDlg.h"
#include "AutoHideBar.h"
#include "CoolTabCtrl.h"
#include "TrueColorToolBar.h"
#include "MapManagerDockPageBar.h"

class CMainFrame : public  CAutoHideFrame
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	BOOL			m_ShowEye;
	BOOL			m_ShowLayer;
	CHawkeyeDlg		m_wndHawkeyeDlg;
	HICON			m_hIcon;
	CImageList		m_imgState;
	CImageList		m_imgList;
	CMapTree		m_wndTree;
	CStatusBar		m_wndStatusBar;
	CCoolTabCtrl	m_TabCtrl;  //”•—€«–ªª

	CMapManagerDockPageBar	m_wndMyBar1;//Õº≤„øÿ÷∆
	CMapManagerDockPageBar	m_wndMyBar2;//”•—€ ”Õº
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DockControlBarRightOf(CToolBar *Bar, CToolBar *RightOf);
	virtual ~CMainFrame();
	void InitToolBar();
    void InitToolBar2();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatic				m_str;
	bool				m_bIns;
	CToolBar			m_wndToolBar;
	CTrueColorToolBar	m_wndToolBar1;
	CTrueColorToolBar	m_wndToolBar2;
	

	CToolBar    m_myToolBar;

	CImageList    m_imageToolBar;
    CImageList    m_imageToolBarDisable;
    CImageList    m_imageToolBarHot;
	CImageList    m_imageToolBar1;
    CImageList    m_imageToolBar1Disable;
    CImageList    m_imageToolBar1Hot;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSHOWHawkeyeDLG();
	afx_msg void OnShowLayer();
	afx_msg void OnUpdateSHOWHawkeyeDLG(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowLayer(CCmdUI* pCmdUI);
	afx_msg void OnHelp();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg void OnUpdateKeyInsert(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C836198B_2FE7_4AF6_ABC0_77679F4BE0FB__INCLUDED_)
