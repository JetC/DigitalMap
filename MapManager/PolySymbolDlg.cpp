// PolySymbolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapManager.h"
#include "PolySymbolDlg.h"
#include "MapManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolySymbolDlg dialog


CPolySymbolDlg::CPolySymbolDlg(int CurSeleLayer,CWnd* pParent /*=NULL*/)
	: CDialog(CPolySymbolDlg::IDD, pParent)
{
	m_CurSeleLayer=CurSeleLayer;
	//{{AFX_DATA_INIT(CPolySymbolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPolySymbolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
     DDX_Control(pDX,IDC_BOND_R, m_BondREdit);
     DDX_Control(pDX,IDC_BOND_G, m_BondGEdit);
	 DDX_Control(pDX,IDC_BOND_B, m_BondBEdit);
	 DDX_Control(pDX,IDC_FILL_R, m_FillREdit);
	 DDX_Control(pDX,IDC_FILL_G, m_FillGEdit);
     DDX_Control(pDX,IDC_FILL_B, m_FillBEdit);
	//{{AFX_DATA_MAP(CPolySymbolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPolySymbolDlg, CDialog)
	//{{AFX_MSG_MAP(CPolySymbolDlg)
	ON_BN_CLICKED(IDC_CHANGELINECOLOR, OnChangelinecolor)
	ON_BN_CLICKED(IDC_CHANGEFILLCOLOR, OnChangefillcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolySymbolDlg message handlers

void CPolySymbolDlg::OnOK() 
{
	// TODO: Add extra validation here
	char  buffer[80];
    m_BondREdit.GetWindowText(buffer,10);
	int R1=atoi(buffer);
	 m_BondGEdit.GetWindowText(buffer,10);
	int G1=atoi(buffer);
    m_BondBEdit.GetWindowText(buffer,10);
	int B1=atoi(buffer);
	
    m_FillREdit.GetWindowText(buffer,10);
	int R2=atoi(buffer);
	 m_FillGEdit.GetWindowText(buffer,10);
	int G2=atoi(buffer);
    m_FillBEdit.GetWindowText(buffer,10);
	int B2=atoi(buffer);

	CFrameWnd *pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMapManagerView *pView = (CMapManagerView *) pFrame->GetActiveView();
    pView->GetDocument()->map1->m_parLayers.GetAt(m_CurSeleLayer)
		    ->SetPolygonParameter(RGB(R1,G1,B1),RGB(R2,G2,B2));
	
	pView->Invalidate();
	
	CDialog::OnOK();
}

void CPolySymbolDlg::OnChangelinecolor() 
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

	    m_BondREdit.Clear();
		m_BondGEdit.Clear();
	    m_BondBEdit.Clear();
		CString str;
		str.Format("%d",R);
		m_BondREdit.SetWindowText(str);
		str.Format("%d",G);
		m_BondGEdit.SetWindowText(str);
        str.Format("%d",B);
		m_BondBEdit.SetWindowText(str);
	}
}

void CPolySymbolDlg::OnChangefillcolor() 
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

	    m_FillREdit.Clear();
		m_FillREdit.Clear();
	    m_FillREdit.Clear();
		CString str;
		str.Format("%d",R);
		m_FillREdit.SetWindowText(str);
		str.Format("%d",G);
		m_FillGEdit.SetWindowText(str);
        str.Format("%d",B);
		m_FillBEdit.SetWindowText(str);
	}
}
