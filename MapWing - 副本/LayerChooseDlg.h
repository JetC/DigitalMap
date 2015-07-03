#if !defined(AFX_LAYERCHOOSEDLG_H__4F65871D_029A_4BEB_84DA_02BBF4410D2D__INCLUDED_)
#define AFX_LAYERCHOOSEDLG_H__4F65871D_029A_4BEB_84DA_02BBF4410D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayerChooseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLayerChooseDlg dialog

class CLayerChooseDlg : public CDialog
{
// Construction
public:
	CLayerChooseDlg(CWnd* pParent = NULL);   // standard constructor
    int m_LayerType;
    CComboBox	m_Combo_Show;  //下拉列表框
    int m_CurSelect;   //当前选中图层号
    CEdit m_Edit;    

// Dialog Data
	//{{AFX_DATA(CLayerChooseDlg)
	enum { IDD = IDD_LAYERCHOOSE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerChooseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLayerChooseDlg)
	afx_msg void OnSelchangeCombo1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERCHOOSEDLG_H__4F65871D_029A_4BEB_84DA_02BBF4410D2D__INCLUDED_)
