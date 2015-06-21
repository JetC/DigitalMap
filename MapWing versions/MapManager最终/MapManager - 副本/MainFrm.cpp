// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MapManager.h"

#include "Splash.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame,  CAutoHideFrame)

BEGIN_MESSAGE_MAP(CMainFrame,  CAutoHideFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_SHOW_HawkeyeDLG, OnSHOWHawkeyeDLG)
	ON_COMMAND(ID_SHOW_LAYER, OnShowLayer)
	ON_UPDATE_COMMAND_UI(ID_SHOW_HawkeyeDLG, OnUpdateSHOWHawkeyeDLG)
	ON_UPDATE_COMMAND_UI(ID_SHOW_LAYER, OnUpdateShowLayer)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_INSERT,OnUpdateKeyInsert)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
	ID_INDICATOR_TIME,
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_INSERT,
	

};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_ShowEye=1;
	m_ShowLayer=1;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	InitToolBar2();    //设置真彩工具栏


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
  

	if (!m_myToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_myToolBar.LoadToolBar(IDR_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    InitToolBar();    //设置真彩工具栏

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_myToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_myToolBar);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////状态栏
	//设置第一个窗格风格
	m_wndStatusBar.SetPaneInfo(0,0,SBPS_NORMAL,180);
	//设置第二个窗格风格
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,300);
	SetTimer(1,1000,NULL);//设置定时器
	
	m_bIns=true;
	CString str="欢迎使用MapManager系统！";
	CString str2="";
	CClientDC dc(this);
	CSize sz=dc.GetTextExtent(str);
	m_wndStatusBar.SetPaneInfo(3,ID_MOVEWEL,SBPS_STRETCH,sz.cx*2);
	m_wndStatusBar.SetPaneText(3,str2);
	SetTimer(3,200,NULL);
	CRect rect;
	m_wndStatusBar.GetItemRect(3,&rect);//获得窗格位置
	m_str.Create(str,WS_CHILD|WS_VISIBLE,rect,&m_wndStatusBar,80);//添加一个CStatic静态控件
	
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////分割子窗体
	CSplashWnd::ShowSplashScreen(this);
	for(int i = 1;i < 12;i++)
	{
		if(GloabStepFun != NULL) GloabStepFun(i);   //发送进度值i
	}

	// 图层信息
	if (!m_wndMyBar1.Create(_T("图层信息"), this, CSize(230,300), TRUE, 123))
	{
		TRACE0("Failed to create DockPageBar.\n");
		return -1;
	}
	m_wndMyBar1.SetBarStyle(m_wndMyBar1.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndMyBar1.EnableDocking (CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);//允许停靠
	DockControlBar(&m_wndMyBar1, AFX_IDW_DOCKBAR_RIGHT);// 图层位置

	//加载图层
     if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
		TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
		CRect(0, 0, 0, 0), &m_wndMyBar1, 100))
	{
		TRACE0("Failed to create instant bar child\n");
		return -1;
	}

	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	////往树型控件添加内容///	
	m_imgList.Create(IDB_BITMAP3,20, 1, RGB(255,255,255));
	m_imgState.Create(IDB_BITMAP2,25, 1, RGB(255,255,255));
	m_wndTree.SetImageList(&m_imgList,TVSIL_NORMAL);
    m_wndTree.SetImageList(&m_imgState,TVSIL_STATE);
	
	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent=NULL;
	tvinsert.hInsertAfter=TVI_LAST;
	tvinsert.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
	tvinsert.item.hItem=NULL;

	tvinsert.item.stateMask=TVIS_STATEIMAGEMASK;
	tvinsert.item.cchTextMax=6;
	tvinsert.item.iSelectedImage=0;
	tvinsert.item.cChildren=0;
	tvinsert.item.lParam=0;
    HTREEITEM hti = m_wndTree.InsertItem(_T("图层信息"));

	m_wndMyBar1.AddPage(&m_wndTree,"图层管理",IDR_MAP);
	m_wndTree.ShowWindow(SW_SHOW);
	
	// 鹰眼视图
	if (!m_wndMyBar2.Create(_T("鹰眼视图"), this, CSize(230,120), TRUE, 1234))
	{		
		TRACE0("Failed to create DockPageBar.\n");
		return -1;
	}
	m_wndMyBar2.SetBarStyle(m_wndMyBar2.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndMyBar2.EnableDocking (CBRS_ALIGN_ANY);

	// 鹰眼位置
	CRect rect2;
	int nEyeHeight = 30;
	GetWindowRect(&rect2);
	rect2.left -= 230;
	rect2.bottom -= nEyeHeight;
	DockControlBar(&m_wndMyBar1, AFX_IDW_DOCKBAR_RIGHT, rect2);
	rect2.bottom += nEyeHeight;
	rect2.top = rect2.bottom - nEyeHeight;
	DockControlBar(&m_wndMyBar2, AFX_IDW_DOCKBAR_RIGHT, rect2);
	
	// 添加鹰眼对话框
	m_wndHawkeyeDlg.Create(IDD_HawkDlg,&m_wndMyBar2);
	m_wndMyBar2.AddPage(&m_wndHawkeyeDlg, "鹰眼视图", IDR_EYE);
	m_wndHawkeyeDlg.ShowWindow(SW_SHOW);
	
	m_bCreated=FALSE;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CTime tmCurr;
	CString strTime;
	tmCurr=CTime::GetCurrentTime();
	strTime=tmCurr.Format("当前时间：%H:%M:%S");
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME),strTime);
	
	CRect rect;
	CString str="Hello! Welcome my friends!";
	CClientDC dc(this);
	CSize sz=dc.GetTextExtent(str);
	m_wndStatusBar.GetItemRect(3,&rect);
	static CRect CurRect=rect;
	CurRect.right=CurRect.left+sz.cx;
	if (CurRect.right>=rect.right)
	{
		CurRect=rect;
	}
	else
	{
		CurRect.left+=10;
		CurRect.right+=10;
	}
	m_str.MoveWindow(CurRect);
	CFrameWnd::OnTimer(nIDEvent);
}
void CMainFrame::OnUpdateKeyInsert(CCmdUI *pCmdUI) 
{
	if (::GetKeyState(VK_INSERT)<0)//判断Insert键是否被按下
	{
		m_bIns=!m_bIns;
		pCmdUI->Enable(m_bIns);//设置状态栏对应窗格可见
	}
}

void CMainFrame::DockControlBarRightOf(CToolBar *Bar, CToolBar *RightOf)
{
	

}

void CMainFrame::OnSHOWHawkeyeDLG() 
{
	// TODO: Add your command handler code here
	ShowControlBar(&m_wndMyBar2,!m_wndMyBar2.IsVisible(),false);
	if(	m_ShowEye==0)		m_ShowEye=1;
	else		m_ShowEye=0;

}

void CMainFrame::OnShowLayer() 
{
	// TODO: Add your command handler code here
	ShowControlBar(&m_wndMyBar1,!m_wndMyBar1.IsVisible(),false);
	if (m_ShowLayer==0)		m_ShowLayer=1;
	else		m_ShowLayer=0;
}

void CMainFrame::OnUpdateSHOWHawkeyeDLG(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_ShowEye);
}

void CMainFrame::OnUpdateShowLayer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_ShowLayer);
}

void CMainFrame::InitToolBar()
{
    CBitmap bm;

    //左工具栏
	//活动的工具
    m_imageToolBar.Create( 50, 50, TRUE | ILC_COLOR32, 12, 0 );
    bm.LoadBitmap( IDB_TOOLBARCOLOR );
    m_imageToolBar.Add( &bm,(CBitmap*)NULL );
    bm.Detach();
    m_myToolBar.GetToolBarCtrl().SetImageList( &m_imageToolBar );

    //禁止的工具
    m_imageToolBarDisable.Create( 50, 50, TRUE | ILC_COLOR32, 12, 0 );
    bm.LoadBitmap( IDB_TOOLBARDISABLE );
    m_imageToolBarDisable.Add( &bm,(CBitmap*)NULL );
    bm.Detach();
    m_myToolBar.GetToolBarCtrl().SetDisabledImageList( &m_imageToolBarDisable );

    //当前的工具
    m_imageToolBarHot.Create( 50, 50, TRUE | ILC_COLOR32, 12, 0 ); 
    bm.LoadBitmap( IDB_TOOLBARHOT );
    m_imageToolBarHot.Add( &bm,(CBitmap*)NULL );
    bm.Detach();
    m_myToolBar.GetToolBarCtrl().SetHotImageList( &m_imageToolBarHot );


}

void CMainFrame::InitToolBar2()
{
    CBitmap bm;

	//上工具栏
	//活动的工具
    m_imageToolBar1.Create( 30, 30, TRUE | ILC_COLOR32, 8, 0 );
    bm.LoadBitmap( IDB_TOOLBAR1COLOR );
    m_imageToolBar1.Add( &bm,(CBitmap*)NULL );
    bm.Detach();
    m_wndToolBar.GetToolBarCtrl().SetImageList( &m_imageToolBar1 );

    //禁止的工具
    m_imageToolBar1Disable.Create( 30, 30, TRUE | ILC_COLOR32, 8, 0 );
    bm.LoadBitmap( IDB_TOOLBAR1DISABLE );
    m_imageToolBar1Disable.Add( &bm,(CBitmap*)NULL );
    bm.Detach();
    m_wndToolBar.GetToolBarCtrl().SetDisabledImageList( &m_imageToolBar1Disable );

    //当前的工具
    m_imageToolBar1Hot.Create( 30, 30, TRUE | ILC_COLOR32, 8, 0 ); 
    bm.LoadBitmap( IDB_TOOLBAR1HOT );
    m_imageToolBar1Hot.Add( &bm,(CBitmap*)NULL );
    bm.Detach();
    m_wndToolBar.GetToolBarCtrl().SetHotImageList( &m_imageToolBar1Hot );

}

void CMainFrame::OnHelp() 
{
	ShellExecute(NULL,"open",".\\help.chm",NULL,NULL,SW_SHOWMAXIMIZED);
}



void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
	menu.LoadMenu(IDR_FLOATMENU);//加上弹出菜单资源
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
	TPM_RIGHTBUTTON,point.x,point.y,this); 

}
