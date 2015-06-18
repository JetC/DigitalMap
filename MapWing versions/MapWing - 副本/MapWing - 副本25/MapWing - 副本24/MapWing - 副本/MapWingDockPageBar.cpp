// MapWingDockPageBar.cpp : implementation file
//

#include "stdafx.h"
#include "MapWingDockPageBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapWingDockPageBar

CMapWingDockPageBar::CMapWingDockPageBar()
{
}

CMapWingDockPageBar::~CMapWingDockPageBar()
{
}


BEGIN_MESSAGE_MAP(CMapWingDockPageBar, CDockPageBar)
	//{{AFX_MSG_MAP(CMapWingDockPageBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMapWingDockPageBar message handlers

int CMapWingDockPageBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockPageBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

BOOL CMapWingDockPageBar::AddPage(CRuntimeClass *pClass, 
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

void CMapWingDockPageBar::SetActivePage(int nIndex)
{
	CDockPageBar::SetActivePage(nIndex);
}


bool CMapWingDockPageBar::HideFloatWindow(CFrameWnd *pFrmame)
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

bool CMapWingDockPageBar::HideFloatWindow(CAutoHideBar *pHideBar)
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
