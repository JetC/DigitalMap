// MapTree.cpp : implementation file
//

#include "stdafx.h"
#include "MapWing.h"
#include "MapTree.h"
#include "MapWingView.h"
#include "MainFrm.h"
#include "Grid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapTree

CMapTree::CMapTree()
{
}

CMapTree::~CMapTree()
{
}


BEGIN_MESSAGE_MAP(CMapTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CMapTree)
	ON_WM_LBUTTONDOWN()
     ON_NOTIFY_REFLECT(NM_CLICK, OnStateIconClick)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapTree message handlers

void CMapTree::OnLButtonDown(UINT nFlags, CPoint point) 
{  
	HTREEITEM hItem =HitTest(point, &m_uFlags);
	if ( (m_uFlags&TVHT_ONITEMSTATEICON ))
	{ 

		//nState: 0->无选择钮 1->没有选择 2->选择 
		UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
		nState=(nState==2)?1:2;
		SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
		if(nState==2)
		  SetItemImage( hItem,1,true );
		
		else
          SetItemImage( hItem,0,false );

        CMapWingView * pView = (CMapWingView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
		for(int i=0;i<pView->GetDocument()->map1->m_parLayers.GetSize();i++)
		{ 
			int k;	
		   k=strcmp(pView->GetDocument()->map1->m_parLayers.GetAt(i)->GetLayerName(),GetItemText(hItem));
		   if(k==0)
		   {  
			   if(nState==2)
			   {    
				   pView->GetDocument()->map1->m_parLayers.GetAt(i)->SetVisible(1);
		           pView->Invalidate();
			   }
		       else
			   {    
				   pView->GetDocument()->map1->m_parLayers.GetAt(i)->SetVisible(0);
			       pView->Invalidate();
			   }
		   }
		}
       if(strcmp(GetItemText(hItem),"格网层")==0)
	   {
		    if(nState==2)
			   {    
				   pView->GetDocument()->map1->m_GridLayer->SetVisible(1);
		           pView->Invalidate();
			   }
		       else
			   {    
				   pView->GetDocument()->map1->m_GridLayer->SetVisible(0);
			       pView->Invalidate();
			   }

	   }

	}
	

	CTreeCtrl::OnLButtonDown(nFlags, point);
}


void CMapTree::OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(m_uFlags&TVHT_ONITEMSTATEICON) *pResult=1;
	else *pResult = 0;
	
}

BOOL CMapTree::SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch)
{
	BOOL bReturn=CTreeCtrl::SetItemState( hItem, nState, nStateMask );
	return bReturn;
}

void CMapTree::OnRButtonDown(UINT nFlags, CPoint point) 
{
HTREEITEM hItem =HitTest(point, &m_uFlags);
	if ((m_uFlags&TVHT_ONITEMLABEL ))
	{
 
       
		SelectDropTarget(hItem);

	CMenu menu,*pSubMenu;
	
   
	menu.LoadMenu(IDR_MENUTREE);
   pSubMenu= menu.GetSubMenu(0);

  //	CBitmap bitmap1,bitmap2;//设置位图
	//bitmap1.LoadBitmap(IDB_BITMAP1);
  //	bitmap2.LoadBitmap(IDB_BITMAP2);
	//menu.GetSubMenu(0)->SetMenuItemBitmaps(1,MF_BYPOSITION,&bitmap1,&bitmap2);
    m_CurLayer=-1;

    CMapWingView * pView = (CMapWingView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	if(pView->m_IsLoadMap)
	{
		for(int i=0;i<pView->GetDocument()->map1->m_parLayers.GetSize();i++)
		{  
		   int k=1;	
		   k=strcmp(pView->GetDocument()->map1->m_parLayers.GetAt(i)->GetLayerName(),GetItemText(hItem));
		   if(k==0)
		   {  
			   m_CurLayer=i;

		   }
		}
	    if(m_CurLayer!=-1)
		{
	   pSubMenu->TrackPopupMenu(0,point.x,point.y+100,AfxGetMainWnd());
		}
	}

 
	}

	// TODO: Add your message handler code here and/or call default
	
   //	CTreeCtrl::OnRButtonDown(nFlags, point);
}
