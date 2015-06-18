#if !defined(AFX_HawkeyeDlg_H__1EDA3727_B230_492C_85EE_7C907AF9FDB3__INCLUDED_)
#define AFX_HawkeyeDlg_H__1EDA3727_B230_492C_85EE_7C907AF9FDB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HawkeyeDlg.h : header file
//
#include "GeoMap.h"
/////////////////////////////////////////////////////////////////////////////
// CHawkeyeDlg dialog

class CHawkeyeDlg : public CDialog
{
// Construction
public:
	CHawkeyeDlg(CWnd* pParent = NULL);   // standard constructor

  DECLARE_DYNCREATE(CHawkeyeDlg)
   
 // Dialog Data
	//{{AFX_DATA(CHawkeyeDlg)
	enum { IDD = IDD_HawkDlg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

protected:

	CRect m_PrevRect;

    CGeoMap *m_SmallMap;
	CRect m_curWinRect;
   

public:
	 void ChangeMap(CGeoMap *BigMap,CRect BigRect,CRect SmallRect);
     void ChangeRect(CRect rect);
	 void DrawRect();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHawkeyeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHawkeyeDlg)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HawkeyeDlg_H__1EDA3727_B230_492C_85EE_7C907AF9FDB3__INCLUDED_)
