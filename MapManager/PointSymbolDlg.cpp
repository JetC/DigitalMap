// PointSymbolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapManager.h"
#include "PointSymbolDlg.h"
#include "MapManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointSymbolDlg dialog


CPointSymbolDlg::CPointSymbolDlg(int CurSeleLayer,CWnd* pParent /*=NULL*/)
	: CDialog(CPointSymbolDlg::IDD, pParent)
{
	m_CurSeleLayer=CurSeleLayer;
	m_PointType=1;
	//{{AFX_DATA_INIT(CPointSymbolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPointSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX,IDC_POINT_R ,m_REdit);
     DDX_Control(pDX,IDC_POINT_G, m_GEdit);
	 DDX_Control(pDX,IDC_POINT_B, m_BEdit);
	 DDX_Control(pDX,IDC_POINT_RADIUS, m_RadiusEdit);
	//{{AFX_DATA_MAP(CPointSymbolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointSymbolDlg, CDialog)
	//{{AFX_MSG_MAP(CPointSymbolDlg)
	ON_BN_CLICKED(IDC_PT1, OnPt1)
	ON_BN_CLICKED(IDC_PT2, OnPt2)
	ON_BN_CLICKED(IDC_PT3, OnPt3)
	ON_BN_CLICKED(IDC_CHOOSEPOINTCOLOR, OnChoosepointcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointSymbolDlg message handlers

void CPointSymbolDlg::EnablePointType(BOOL bEnable1,BOOL bEnable2,BOOL bEnable3)
{
   
	((CButton*)GetDlgItem (IDC_PT1))->SetCheck (bEnable1);

    ((CButton*)GetDlgItem (IDC_PT2))->SetCheck (bEnable2);
    ((CButton*)GetDlgItem (IDC_PT3))->SetCheck (bEnable3);
    
	
}

void CPointSymbolDlg::OnOK() 
{
	// TODO: Add extra validation here
	char  buffer[80];
    m_REdit.GetWindowText(buffer,10);
	int R=atoi(buffer);
	 m_GEdit.GetWindowText(buffer,10);
	int G=atoi(buffer);
    m_BEdit.GetWindowText(buffer,10);
	int B=atoi(buffer);
	m_RadiusEdit.GetWindowText(buffer,10);
	m_PointRadius=atoi(buffer);

	CFrameWnd *pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMapManagerView *pView = (CMapManagerView *) pFrame->GetActiveView();

    CClientDC dc(pView);
    pView->OnPrepareDC(&dc);
	CPoint point1;
	CPoint point2;
	point1.x=100;
	point1.y=200;
	point2.x=100+m_PointRadius;
	point2.y=200;
	dc.DPtoLP(&point1);
	dc.DPtoLP(&point2);



	pView->GetDocument()->map1->m_parLayers.GetAt(m_CurSeleLayer)
		    ->SetPointParameter(m_PointType,RGB(R,G,B),point2.x-point1.x);
	
	pView->Invalidate();
	
	CDialog::OnOK();
}

void CPointSymbolDlg::OnPt1() 
{
	// TODO: Add your control notification handler code here
	EnablePointType(true,false,false);
	m_PointType=1;
	
}

void CPointSymbolDlg::OnPt2() 
{
	// TODO: Add your control notification handler code here
	EnablePointType(false,true,false);
	m_PointType=2;
	
}

void CPointSymbolDlg::OnPt3() 
{
	// TODO: Add your control notification handler code here
	EnablePointType(false,false,true);
	m_PointType=3;
	
}

void CPointSymbolDlg::OnChoosepointcolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		COLORREF color;
		color=dlg.GetColor();
		int R=GetRValue(color);
		int G=GetGValue(color);
		int B=GetBValue(color);

		m_REdit.Clear();
		m_REdit.Clear();
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
