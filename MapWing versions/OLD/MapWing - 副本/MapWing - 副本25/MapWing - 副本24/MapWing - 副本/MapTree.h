#if !defined(AFX_MapTree_H__5D0308D8_1D7D_4C69_BCEF_DF97CE913582__INCLUDED_)
#define AFX_MapTree_H__5D0308D8_1D7D_4C69_BCEF_DF97CE913582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapTree window


class CMapTree : public CTreeCtrl   //CMapTree为CTreeCtrl派生类，重载了基类一些方法
{
// Construction
public:
	CMapTree();

// Attributes
public:
   UINT m_uFlags;
   int m_CurLayer;  //记录选中的层号

// Operations
public:
	//设置树中项目的状态
   BOOL SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch=TRUE); 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMapTree)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MapTree_H__5D0308D8_1D7D_4C69_BCEF_DF97CE913582__INCLUDED_)
