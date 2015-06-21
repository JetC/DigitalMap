#if !defined(AFX_POLYSYMBOLDLG_H__C12E2CF8_BC40_41E6_9107_E8DB5AABEB0B__INCLUDED_)
#define AFX_POLYSYMBOLDLG_H__C12E2CF8_BC40_41E6_9107_E8DB5AABEB0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PolySymbolDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPolySymbolDlg dialog

class CPolySymbolDlg : public CDialog
{
// Construction
public:
	CPolySymbolDlg(int CurSeleLayer,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPolySymbolDlg)
	enum { IDD = IDD_GONSYM_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolySymbolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   int m_CurSeleLayer;   //当前图层号

   CEdit m_BondREdit,m_BondGEdit,m_BondBEdit;  //对应编辑框
   CEdit m_FillREdit,m_FillGEdit,m_FillBEdit;

	// Generated message map functions
	//{{AFX_MSG(CPolySymbolDlg)
	virtual void OnOK();
	afx_msg void OnChangelinecolor();
	afx_msg void OnChangefillcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLYSYMBOLDLG_H__C12E2CF8_BC40_41E6_9107_E8DB5AABEB0B__INCLUDED_)
