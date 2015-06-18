#if !defined(AFX_LINESYMBOLDLG_H__D0E94552_0C47_4C55_B619_7EFF8B2A0C08__INCLUDED_)
#define AFX_LINESYMBOLDLG_H__D0E94552_0C47_4C55_B619_7EFF8B2A0C08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineSymbolDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLineSymbolDlg dialog

class CLineSymbolDlg : public CDialog
{
// Construction
public:
	CLineSymbolDlg(int CurSeleLayer,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineSymbolDlg)
	enum { IDD = IDD_LINESYM_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineSymbolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int m_CurSeleLayer;   //当前符号化图层
	long m_LineColor;  //线色彩
	CEdit m_WidthEdit;  //线宽
	int m_LineType;    //线类型，共5种
	CEdit m_REdit,m_GEdit,m_BEdit;
	long m_LineWidth;   //线宽
    void EnableLineType(BOOL bEnable1,BOOL bEnable2,BOOL bEnable3,BOOL bEnable4,BOOL bEnable5);  //控制单选框

	// Generated message map functions
	//{{AFX_MSG(CLineSymbolDlg)
	afx_msg void OnLt1();
	afx_msg void OnLt2();
	afx_msg void OnLt3();
	afx_msg void OnLt4();
	afx_msg void OnLt5();
	virtual void OnOK();
	afx_msg void OnChangelinecolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINESYMBOLDLG_H__D0E94552_0C47_4C55_B619_7EFF8B2A0C08__INCLUDED_)
