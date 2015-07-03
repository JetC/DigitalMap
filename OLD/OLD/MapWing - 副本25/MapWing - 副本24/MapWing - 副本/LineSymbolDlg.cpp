// LineSymbolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapManager.h"
#include "LineSymbolDlg.h"
#include "MapManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineSymbolDlg dialog


CLineSymbolDlg::CLineSymbolDlg(int CurSeleLayer,CWnd* pParent /*=NULL*/)
	: CDialog(CLineSymbolDlg::IDD, pParent)
{
	m_CurSeleLayer=CurSeleLayer;
	m_LineType=1;
	//{{AFX_DATA_INIT(CLineSymbolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLineSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
     DDX_Control(pDX,IDC_LINE_R, m_REdit);
     DDX_Control(pDX,IDC_LINE_G, m_GEdit);
	 DDX_Control(pDX,IDC_LINE_B, m_BEdit);
	 DDX_Control(pDX,IDC_LINE_WIDTH, m_WidthEdit);
	//{{AFX_DATA_MAP(CLineSymbolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineSymbolDlg, CDialog)
	//{{AFX_MSG_MAP(CLineSymbolDlg)
	ON_BN_CLICKED(IDC_LT1, OnLt1)
	ON_BN_CLICKED(IDC_LT2, OnLt2)
	ON_BN_CLICKED(IDC_LT3, OnLt3)
	ON_BN_CLICKED(IDC_LT4, OnLt4)
	ON_BN_CLICKED(IDC_LT5, OnLt5)
	ON_BN_CLICKED(IDC_CHANGELINECOLOR, OnChangelinecolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineSymbolDlg message handlers

void CLineSymbolDlg::OnLt1() 
{
	// TODO: Add your control notification handler code here
	EnableLineType(true,false,false,false,false);
	m_LineType=1;
	
}

void CLineSymbolDlg::OnLt2() 
{
	// TODO: Add your control notification handler code here
	EnableLineType(false,true,false,false,false);
	m_LineType=2;
	
}

void CLineSymbolDlg::OnLt3() 
{
	// TODO: Add your control notification handler code here
	EnableLineType(false,false,true,false,false);
	m_LineType=3;
	
}

void CLineSymbolDlg::OnLt4() 
{
	// TODO: Add your control notification handler code here
	EnableLineType(false,false,false,true,false);
	m_LineType=4;
}

void CLineSymbolDlg::OnLt5() 
{
	// TODO: Add your control notification handler code here
	EnableLineType(false,false,false,false,true);
	m_LineType=5;
}

void CLineSymbolDlg::OnOK() 
{
	// TODO: Add extra validation here
	char  buffer[80];
    m_REdit.GetWindowText(buffer,10);
	int R=atoi(buffer);
	 m_GEdit.GetWindowText(buffer,10);
	int G=atoi(buffer);
    m_BEdit.GetWindowText(buffer,10);
	int B=atoi(buffer);
	m_WidthEdit.GetWindowText(buffer,10);
	m_LineWidth=atoi(buffer);

	CFrameWnd *pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMapManagerView *pView = (CMapManagerView *) pFrame->GetActiveView();

	CClientDC dc(pView);
    pView->OnPrepareDC(&dc);
	CPoint point1;
	CPoint point2;
	point1.x=100;
	point1.y=200;
	point2.x=100+m_LineWidth;
	point2.y=200;
	dc.DPtoLP(&point1);
	dc.DPtoLP(&point2);




	pView->GetDocument()->map1->m_parLayers.GetAt(m_CurSeleLayer)
		    ->SetLineParameter(m_LineType,RGB(R,G,B),point2.x-point1.x);
	
	pView->Invalidate();
	
	CDialog::OnOK();
}

void CLineSymbolDlg::EnableLineType(BOOL bEnable1,BOOL bEnable2,BOOL bEnable3,BOOL bEnable4,BOOL bEnable5)
{
	((CButton*)GetDlgItem (IDC_LT1))->SetCheck (bEnable1);
    ((CButton*)GetDlgItem (IDC_LT2))->SetCheck (bEnable2);
    ((CButton*)GetDlgItem (IDC_LT3))->SetCheck (bEnable3);
    ((CButton*)GetDlgItem (IDC_LT4))->SetCheck (bEnable4);
    ((CButton*)GetDlgItem (IDC_LT5))->SetCheck (bEnable5);
}

void CLineSymbolDlg::OnChangelinecolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDialog;
	if(ColorDialog.DoModal() == IDOK)
	{
	
		COLORREF color;
		//m_LineColor = ColorDialog.GetColor();
		color= ColorDialog.GetColor();
		int R=GetRValue(color);
		int G=GetGValue(color);
		int B=GetBValue(color);

	    m_REdit.Clear();
		m_GEdit.Clear();
	    m_BEdit.Clear();
		CString str;
		str.Format("%d",R);
		m_REdit.SetWindowText(str);
		str.Format("%d",G);
		m_GEdit.SetWindowText(str);
        str.Format("%d",B);
		m_BEdit.SetWindowText(str);
	}
}
