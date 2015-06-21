#if !defined(AFX_CHANGEFORMAT_H__5A78686A_3A5E_4178_BCBD_4C55C8EBFC06__INCLUDED_)
#define AFX_CHANGEFORMAT_H__5A78686A_3A5E_4178_BCBD_4C55C8EBFC06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeFormat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeFormat dialog

class CChangeFormat : public CDialog
{
// Construction
public:
	CChangeFormat(CWnd* pParent = NULL);   // standard constructor
	CString m_strSourcePath;
	CString m_strOutPath;
	CString strExt;
	CEdit m_Edit1;
	CEdit m_Edit2;
// Dialog Data
	//{{AFX_DATA(CChangeFormat)
	enum { IDD = IDD_CHANGEFORMATDLG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeFormat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeFormat)
	virtual void OnOK();
	afx_msg void OnSource();
	afx_msg void OnGoal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEFORMAT_H__5A78686A_3A5E_4178_BCBD_4C55C8EBFC06__INCLUDED_)
