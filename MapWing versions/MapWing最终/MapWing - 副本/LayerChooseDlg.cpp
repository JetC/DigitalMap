// LayerChooseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapWing.h"
#include "LayerChooseDlg.h"
#include "MapWingView.h"
#include "MainFrm.h"
#include "LineSymbol.h"
#include "PointSymbol.h"
#include "GeoAnno.h"
#include "PolygonSymbol.h"
#include "PointSymbol.h"
#include "PointSymbolDlg.h"
#include "LineSymbolDlg.h"
#include "AnnoSymbolDlg.h"
#include "PolySymbolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerChooseDlg dialog


CLayerChooseDlg::CLayerChooseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLayerChooseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLayerChooseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLayerChooseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_Combo_Show);
    DDX_Control(pDX,IDC_LAYER_INFO, m_Edit);
	//{{AFX_DATA_MAP(CLayerChooseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayerChooseDlg, CDialog)
	//{{AFX_MSG_MAP(CLayerChooseDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayerChooseDlg message handlers

void CLayerChooseDlg::OnOK() 
{
	// TODO: Add extra validation here
 switch (m_LayerType)
   {
	case 1:
		{
		  CPointSymbolDlg dlg(m_CurSelect);
		  dlg.DoModal();
		  break;
		}

     case 3:

		 { 

		   CLineSymbolDlg dlg(m_CurSelect);
		   dlg.DoModal();
		   break;
		 }
			 
	 case 5:
		 {
			 CPolySymbolDlg dlg(m_CurSelect);
			 dlg.DoModal();
			 break;
		 }

	 case 7:
		{
			CAnnoSymbolDlg dlg(m_CurSelect);
			dlg.DoModal();
		   break;
		}

     default: break;
   }

	//调用父类的OK
	CDialog::OnOK();
}
int CLayerChooseDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	TempRect.SetRect(CharX*5,CharY*4,CharX*30,CharY*25);//设定Combo的宽度和位置
   
	m_Combo_Show.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_SORT|WS_BORDER|WS_VSCROLL,TempRect,this,IDC_COMBO1);
	CFrameWnd *pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMapWingView *pView = (CMapWingView *) pFrame->GetActiveView();
	CString str;
  
	if(pView->m_IsLoadMap)
	{
	   int LayerNum=pView->GetDocument()->map1->GetLayerNum();
	 
	   for(int i=0;i<LayerNum;i++)
	  {
         str=pView->GetDocument()->map1->m_parLayers.GetAt(i)->GetLayerName();
	  
         m_Combo_Show.InsertString(i,str);
	  }
	}
	return 0;
}

void CLayerChooseDlg::OnSelchangeCombo1() 
{

	// TODO: Add your control notification handler code here
	

	m_CurSelect=m_Combo_Show.GetCurSel();
   

	CFrameWnd *pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMapWingView *pView = (CMapWingView *) pFrame->GetActiveView();

    
    m_LayerType=pView->GetDocument()->map1->m_parLayers.GetAt(m_CurSelect)->GetLayerType();
   
	switch (m_LayerType)
	{
	case 1:
        m_Edit.SetWindowText("你选择的为点状目标图层");
		break;
    case 3:
        m_Edit.SetWindowText("你选择的为线状目标图层");
		break;
	case 5:
        m_Edit.SetWindowText("你选择的为面状目标图层");
		break;
	case 7:
        m_Edit.SetWindowText("你选择的为注记图层");
		break;
	default :
		break;
	}
		
}
