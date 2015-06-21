// CG: This file was added by the Splash Screen component.
// Splash.cpp : implementation file
//

#include "stdafx.h"  // e. g. stdafx.h
#include "resource.h"  // e.g. resource.h

#include "Splash.h"  // e.g. splash.h
#include "MapManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class

BOOL CSplashWnd::c_bShowSplashWnd;
CSplashWnd* CSplashWnd::c_pSplashWnd;

STEPFUN GloabStepFun;

void GetStatusCode(int iStepCode) 
{
	Sleep(300);
	CSplashWnd::Guage(iStepCode); 
}

void CSplashWnd::Guage(int iStep) 
{// 自己绘制进度条  
	CDC *pdc = c_pSplashWnd->GetDC(); 
	int a= pdc->SetBkMode(TRANSPARENT);  

	CFont font;  
	font.CreateFont(14,6,0,0,FW_BOLD,0,0,NULL,NULL,NULL,NULL,NULL,NULL,"黑体");  

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_SPLASH);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	int w = bmp.bmWidth;
	int h = bmp.bmHeight;
	int step= w/6;   // 注意：进度条宽/步进次数  

	CFont* oldfont = pdc->SelectObject(&font);
	switch(iStep)  
	{
	case 1: {
        pdc->Rectangle(&CRect(0,h-20,w,h)); 
        pdc->FillRect(&CRect(0,h-20,step*1,h),&CBrush(RGB(128,255,255)));
        pdc->TextOut(42,h-19,"初始化设备环境............");
			}break;
	case 2:{
        pdc->Rectangle(&CRect(0,h-20,w,h)); 
        pdc->FillRect(&CRect(0,h-20,step*2,h),&CBrush(RGB(128,255,255)));
        pdc->TextOut(42,h-19,"系统运行预设置............");
		   }break;
	case 3:{
        pdc->Rectangle(&CRect(0,h-20,w,h)); 
        pdc->FillRect(&CRect(0,h-20,step*3,h),&CBrush(RGB(128,255,255)));
		pdc->TextOut(42,h-19,"系统预设置成功............");
		   }break;
	case 4:{
        pdc->Rectangle(&CRect(0,h-20,w,h)); 
        pdc->FillRect(&CRect(0,h-20,step*4,h),&CBrush(RGB(128,255,255)));
        pdc->TextOut(42,h-19,"完成文件系统初始化............");
		   }break;
	case 5:{
        pdc->Rectangle(&CRect(0,h-20,w,h)); 
        pdc->FillRect(&CRect(0,h-20,step*5,h),&CBrush(RGB(128,255,255)));
        pdc->TextOut(42,h-19,"正在启动MapManager系统............");
		   }break;
	case 6:{
        pdc->Rectangle(&CRect(0,h-20,w,h)); 
        pdc->FillRect(&CRect(0,h-20,step*6+1.2,h),&CBrush(RGB(169,40,90)));
        pdc->TextOut(42,h-19,"公告：MapManager系统由地信四班第一小组荣誉出品!");
		   }break;
	case 7:{
			}break;

	default:;  
	}
	pdc->SelectObject(oldfont);
	font.DeleteObject();
	pdc->SetBkMode(a);
	c_pSplashWnd->ReleaseDC(pdc); 
}

CSplashWnd::CSplashWnd()
{
	GloabStepFun = (STEPFUN)(long)(&GetStatusCode);
}

CSplashWnd::~CSplashWnd()
{
	// Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd /*= NULL*/)
{
	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
		return;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CSplashWnd;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}

BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;	// message handled here
	}

	return FALSE;	// message not handled
}

BOOL CSplashWnd::Create(CWnd* pParentWnd /*= NULL*/)
{
	if (!m_bitmap.LoadBitmap(IDB_SPLASH))
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);
}

void CSplashWnd::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();
}

void CSplashWnd::PostNcDestroy()
{
	// Free the C++ class.
	delete this;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Center the window.
	CenterWindow();

	// Set a timer to destroy the splash screen.
	SetTimer(1, 300, NULL);

	return 0;
}

void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
}

void CSplashWnd::OnTimer(UINT nIDEvent)
{
	// Destroy the splash screen window.
	HideSplashScreen();
}
