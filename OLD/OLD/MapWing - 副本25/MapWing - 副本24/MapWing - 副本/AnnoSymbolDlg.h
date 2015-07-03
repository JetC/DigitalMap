#if !defined(AFX_ANNOSYMBOLDLG_H__B765A563_2929_455B_A89B_A508E30F6A45__INCLUDED_)
#define AFX_ANNOSYMBOLDLG_H__B765A563_2929_455B_A89B_A508E30F6A45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnnoSymbolDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnnoSymbolDlg dialog

class CAnnoSymbolDlg : public CDialog
{
// Construction
public:
	CAnnoSymbolDlg(int CurSeleLayer,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnnoSymbolDlg)
	enum { IDD = IDD_ANNOSYM_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnnoSymbolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	 int m_CurSeleLayer;  //��ǰ���Ż���ͼ��
     CString  m_TextFont;   //��¼�û����������
     CComboBox	m_Combo_Show;  
     int m_CurSelect;       //��¼��ǰѡ�е�����
	 CEdit m_REdit,m_GEdit,m_BEdit;

	// Generated message map functions
	//{{AFX_MSG(CAnnoSymbolDlg)
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANNOSYMBOLDLG_H__B765A563_2929_455B_A89B_A508E30F6A45__INCLUDED_)
