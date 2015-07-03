#if !defined(AFX_POINTSYMBOLDLG_H__184D9E78_B8D6_4433_A811_03C2FFC6D6B2__INCLUDED_)
#define AFX_POINTSYMBOLDLG_H__184D9E78_B8D6_4433_A811_03C2FFC6D6B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PointSymbolDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPointSymbolDlg dialog

class CPointSymbolDlg : public CDialog
{
// Construction
public:
	CPointSymbolDlg(int CurSeleLayer,CWnd* pParent = NULL);   // standard constructor
    void EnablePointType(BOOL bEnable1,BOOL bEnable2,BOOL bEnable3);  //单选框控制函数

// Dialog Data
	//{{AFX_DATA(CPointSymbolDlg)
	enum { IDD = IDD_POINTSYM_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPointSymbolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int m_CurSeleLayer;  //当前符号化图层号

	long m_PointColor;   //记录用户输入的参数
	int  m_PointType;
	long m_PointRadius;

	CEdit m_RadiusEdit;
	CEdit m_REdit,m_GEdit,m_BEdit;

	// Generated message map functions
	//{{AFX_MSG(CPointSymbolDlg)
	virtual void OnOK();
	afx_msg void OnPt1();
	afx_msg void OnPt2();
	afx_msg void OnPt3();
	afx_msg void OnChoosepointcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POINTSYMBOLDLG_H__184D9E78_B8D6_4433_A811_03C2FFC6D6B2__INCLUDED_)
