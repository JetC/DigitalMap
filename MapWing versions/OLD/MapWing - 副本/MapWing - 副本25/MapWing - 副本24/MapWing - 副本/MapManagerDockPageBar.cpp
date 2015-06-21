// MapManagerDockPageBar.cpp : implementation file
//

#include "stdafx.h"
#include "MapManagerDockPageBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapManagerDockPageBar

CMapManagerDockPageBar::CMapManagerDockPageBar()
{
}

CMapManagerDockPageBar::~CMapManagerDockPageBar()
{
}


BEGIN_MESSAGE_MAP(CMapManagerDockPageBar, CDockPageBar)
	//{{AFX_MSG_MAP(CMapManagerDockPageBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMapManagerDockPageBar message handlers

int CMapManagerDockPageBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockPageBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

BOOL CMapManagerDockPageBar::AddPage(CRuntimeClass *pClass, 
						UINT nIDTemplate, LPCTSTR sText, UINT IconID)
{
	CDialog *pDlg = (CDialog*)pClass->CreateObject();
	if(pDlg != NULL)
	{
		if(pDlg->Create(nIDTemplate,this))
		{
			return AddPage(pDlg, sText, IconID);
		}
	}

	return FALSE;
}

void CMapManagerDockPageBar::SetActivePage(int nIndex)
{
	CDockPageBar::SetActivePage(nIndex);
}


bool CMapManagerDockPageBar::HideFloatWindow(CFrameWnd *pFrmame)
{
	ASSERT(pFrmame);

	CAutoHideBar *pHideBar = (CAutoHideBar *)pFrmame->GetControlBar(AHBRS_LEFT);
	if (HideFloatWindow(pHideBar))
	{  return true;  }

	pHideBar = (CAutoHideBar *)pFrmame->GetControlBar(AHBRS_RIGHT);
	if (HideFloatWindow(pHideBar))
	{  return true;  }

	pHideBar = (CAutoHideBar *)pFrmame->GetControlBar(AHBRS_TOP);
	if (HideFloatWindow(pHideBar))
	{  return true;  }

	pHideBar = (CAutoHideBar *)pFrmame->GetControlBar(AHBRS_BOTTOM);
	if (HideFloatWindow(pHideBar))
	{  return true;  }

	return false;
}

bool CMapManagerDockPageBar::HideFloatWindow(CAutoHideBar *pHideBar)
{
	POSITION         pos = pHideBar->m_listBars.GetHeadPosition();
	CHideItem* pHideItem = NULL;

	while (pos)
	{
		pHideItem = (CHideItem*)pHideBar->m_listBars.GetNext(pos);
		if (pHideItem && pHideItem->m_pDockPageBar == this)
		{
			pHideItem->m_wndFloat.OnStudClick();
			return true;
		}
	}
	return false;
}
