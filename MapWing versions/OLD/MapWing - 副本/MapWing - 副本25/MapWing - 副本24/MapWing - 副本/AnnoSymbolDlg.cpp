// AnnoSymbolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapWing.h"
#include "AnnoSymbolDlg.h"
#include "MapWingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnnoSymbolDlg dialog


CAnnoSymbolDlg::CAnnoSymbolDlg(int CurSeleLayer,CWnd* pParent /*=NULL*/)
	: CDialog(CAnnoSymbolDlg::IDD, pParent)
{
	m_CurSeleLayer=CurSeleLayer;
    m_TextFont="隶书";
    m_CurSelect=1;
	//{{AFX_DATA_INIT(CAnnoSymbolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAnnoSymbolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	 DDX_Control(pDX,IDC_TEXTR, m_REdit);
     DDX_Control(pDX,IDC_TEXTG, m_GEdit);
	 DDX_Control(pDX,IDC_TEXTB, m_BEdit);
	 DDX_Control(pDX, IDC_TEXTFONT_LIST, m_Combo_Show);
	//{{AFX_DATA_MAP(CAnnoSymbolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnnoSymbolDlg, CDialog)
	//{{AFX_MSG_MAP(CAnnoSymbolDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnnoSymbolDlg message handlers

void CAnnoSymbolDlg::OnOK() 
{
	// TODO: Add extra validation here
	char  buffer[80];
    m_REdit.GetWindowText(buffer,10);
	int R=atoi(buffer);
	 m_GEdit.GetWindowText(buffer,10);
	int G=atoi(buffer);
    m_BEdit.GetWindowText(buffer,10);
	int B=atoi(buffer);

    m_CurSelect=m_Combo_Show.GetCurSel();
	if(m_CurSelect==0)
	{
		m_TextFont="宋体";
	}
	if(m_CurSelect==1)
	{
		m_TextFont="隶书";
	}

	if(m_CurSelect==2)
	{
		m_TextFont="黑体";
	}

	CFrameWnd *pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMapWingView *pView = (CMapWingView *) pFrame->GetActiveView();
	pView->GetDocument()->map1->m_parLayers.GetAt(m_CurSeleLayer)
 		           ->SetTextParameter(RGB(R,G,B),m_TextFont);
    pView->Invalidate();
	
	CDialog::OnOK();
}

int CAnnoSymbolDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	CClientDC dc(this);
	CRect TempRect;
	TEXTMETRIC metric;
	int CharHeight,CharX,CharY;
		CharHeight=-((dc.GetDeviceCaps(LOGPIXELSY)*8/72));
	dc.GetTextMetrics(&metric);
	CharX=metric.tmAveCharWidth;
	CharY=metric.tmHeight+metric.tmExternalLeading;
	TempRect.SetRect(CharX*5,CharY*4,CharX*25,CharY*25);
   
	m_Combo_Show.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_SORT|WS_BORDER|WS_VSCROLL,TempRect,this,IDC_TEXTFONT_LIST);

	 m_Combo_Show.InsertString(0,"宋体");
	 m_Combo_Show.InsertString(1,"隶书");
	 m_Combo_Show.InsertString(2,"黑体");
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
