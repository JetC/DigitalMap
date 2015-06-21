// EagleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapManager.h"
#include "HawkeyeDlg.h"
#include "MapManagerView.h"
#include "MainFrm.h"
#include "GeoPoint.h"
#include "GeoLine.h"
#include "GeoPolygon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHawkeyeDlg dialog
IMPLEMENT_DYNCREATE(CHawkeyeDlg, CDialog)

CHawkeyeDlg::CHawkeyeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHawkeyeDlg::IDD, pParent)
{
	m_SmallMap=NULL;
	m_PrevRect.top=m_PrevRect.bottom=m_PrevRect.left=m_PrevRect.right=0;
	//{{AFX_DATA_INIT(CHawkeyeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHawkeyeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHawkeyeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHawkeyeDlg, CDialog)
	//{{AFX_MSG_MAP(CHawkeyeDlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHawkeyeDlg message handlers

void CHawkeyeDlg::OnPaint() 
{
	CPaintDC dc(this);
	CBrush  drawbrush;
	drawbrush.CreateSolidBrush(RGB(255,255,255));
	CBrush* pOldBrush =dc.SelectObject(&drawbrush); 
	CRect rect;
	GetClientRect(&rect);

	dc.Rectangle(&rect);

	dc.SelectObject(&pOldBrush);
	CMapManagerView * pView =(CMapManagerView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());

	
	if(pView->m_IsLoadMap)
	{
	

     ChangeMap(pView->GetDocument()->map1,pView->m_rtMapRange,rect);
	 m_SmallMap->DrawMap(&dc);  

	}
}

void CHawkeyeDlg::ChangeMap(CGeoMap *BigMap,CRect BigRect,CRect SmallRect)
{

	if(m_SmallMap=NULL)
	{
	  delete m_SmallMap;
	}
     m_SmallMap=new CGeoMap;

	CGeoLayer *tempLayer;
	int LayerNum=BigMap->GetLayerNum();
	for(int i=0;i<LayerNum;i++)
	{
        CPoint *points=NULL;
        tempLayer=new CGeoLayer;
        int LayerType=BigMap->m_parLayers.GetAt(i)->GetLayerType();
		//如果是点状图层
	    if(LayerType==1)
		{
			int PointType;
			long PointColor;
			long PointRadius;
	    	BigMap->m_parLayers.GetAt(i)->GetPointParameter(&PointType,&PointColor,&PointRadius);
		    int num=BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();
            for(int j=0;j<num;j++)
			 { 
			      CGeoPoint *pGeoPoint=NULL;
		          pGeoPoint=new CGeoPoint;
				  CPoint point1,point2;
			      ((CGeoPoint *)(BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->GetPoint(point1.x,point1.y);
				  point2.x=(point1.x-BigRect.left)*SmallRect.Width()/BigRect.Width()+SmallRect.left;
			    point2.y=SmallRect.Height()+(point1.y-BigRect.bottom)*SmallRect.Height()/BigRect.Height();
                  pGeoPoint->SetPoint(point2.x,point2.y);
		          tempLayer->AddObject(pGeoPoint);
	           
			 }
           tempLayer->SetPointParameter(PointType,PointColor,2);

		}
	
		if(LayerType==3)
		{
         	int LineType;
			long LineColor;
			long LineWidth;
			
			BigMap->m_parLayers.GetAt(i)->GetLineParameter(&LineType,&LineColor,&LineWidth);
      
            for(int j=0;j<BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();j++)
			{  
			     CGeoLine *pGeoLine=NULL;
                 pGeoLine=new CGeoLine;
                 int PtNum=((CGeoLine *)(BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetSize();
                 points=new CPoint[2000];
				  CPoint *points2=NULL;
                  points2=new CPoint[2000];
				 for(int k=0;k<PtNum;k++)
				 {   
                      points[k].x =((CGeoLine *)(BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->x;
				      points[k].y=((CGeoLine *)(BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->y;
				     
				  }
			   	
                 for(k=0;k<PtNum;k++)
				 {	 
					 points2[k].x=(points[k].x-BigRect.left)*SmallRect.Width()/BigRect.Width()+SmallRect.left;
					 points2[k].y=SmallRect.Height()+(points[k].y-BigRect.bottom)*SmallRect.Height()/BigRect.Height();
				     pGeoLine->AddPoint(points2[k]);
				 }
                 tempLayer->AddObject(pGeoLine);
                 delete []points;
				 points=NULL;
                  delete []points2;
				 points2=NULL;

			}

            tempLayer->SetLineParameter(LineType,LineColor,1);
		
		}

	
	
     	 if(LayerType==5)
		 { 
			
			long BondColor;
			long FillColor;
			
			BigMap->m_parLayers.GetAt(i)->GetPolygonParameter(&BondColor,&FillColor);
      
            for(int j=0;j<BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetSize();j++)
			{  
			     CGeoPolygon *pGeoPolygon=NULL;
                 pGeoPolygon=new CGeoPolygon;

                 int PtNum=((CGeoPolygon *)(BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetSize();
                 points=new CPoint[2000];
				  CPoint *points2=NULL;
                  points2=new CPoint[2000];
				 for(int k=0;k<PtNum;k++)
				 {   
                      points[k].x =((CGeoPolygon *)(BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->x;
				      points[k].y=((CGeoPolygon *)(BigMap->m_parLayers.GetAt(i)->m_parGeoObject.GetAt(j)))->m_parPoints.GetAt(k)->y;
				     
				  }
			   	
                 for(k=0;k<PtNum;k++)
				 {	 
					 points2[k].x=(points[k].x-BigRect.left)*SmallRect.Width()/BigRect.Width()+SmallRect.left;
					 points2[k].y=SmallRect.Height()+(points[k].y-BigRect.bottom)*SmallRect.Height()/BigRect.Height();
				     pGeoPolygon->AddPoint(points2[k]);
				 }
                 tempLayer->AddObject(pGeoPolygon);
                 delete []points;
				 points=NULL;
                  delete []points2;
				 points2=NULL;

			}

            tempLayer->SetPolygonParameter(BondColor,FillColor);
		



		}
     	if(LayerType==7)
		{



		}
    	m_SmallMap->m_parLayers.Add(tempLayer);

	}
}


void CHawkeyeDlg::OnSize(UINT nType, int cx, int cy) 
{

	//Invalidate();
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CHawkeyeDlg::ChangeRect(CRect rect)
{
	CRect SmallRect;
	GetClientRect(&SmallRect);

	CMapManagerView * pView =(CMapManagerView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());

	m_curWinRect.left=(double)(rect.left-pView->m_rtMapRange.left)*(double)SmallRect.Width()/(double)(pView->m_rtMapRange.Width())+SmallRect.left-1;
    m_curWinRect.right=(double)(rect.right-pView->m_rtMapRange.left)*(double)SmallRect.Width()/(double)(pView->m_rtMapRange.Width())+SmallRect.left+1;

    m_curWinRect.top=SmallRect.Height()+(double)(rect.top-pView->m_rtMapRange.bottom)*(double)SmallRect.Height()/(double)(pView->m_rtMapRange.Height())-1;
    m_curWinRect.bottom=SmallRect.Height()+(double)(rect.bottom-pView->m_rtMapRange.bottom)*(double)SmallRect.Height()/(double)(pView->m_rtMapRange.Height())+1;
	

}


void CHawkeyeDlg::DrawRect()
{


 	CClientDC dc(this);
	CRect SmallRect;
   
 	GetClientRect(&SmallRect);

	CMapManagerView * pView =(CMapManagerView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
 	if(pView->m_IsLoadMap)
	{
     
		dc.SetROP2(R2_NOT );
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(m_PrevRect);

		CPen pen,*oldPen;
		pen.CreatePen(1,1,RGB(0,0,0));
		oldPen=dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);
 		ChangeRect(pView->m_CurWinScope);
		m_PrevRect=m_curWinRect;
		dc.Rectangle(m_curWinRect);
		dc.SelectObject(oldPen);
	}

}

void CHawkeyeDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN );
	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(m_PrevRect);
	m_PrevRect.top=m_PrevRect.bottom=m_PrevRect.left=m_PrevRect.right=0;

	CMapManagerView * pView =(CMapManagerView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	if(pView->m_IsLoadMap)
	{
	CRect SmallRect;
	GetClientRect(&SmallRect);


	long width=pView->m_CurWinScope.Width();
	long height=pView->m_CurWinScope.Height();

	CPoint center;
	center.x=(point.x-SmallRect.left)*pView->m_rtMapRange.Width()/SmallRect.Width()+pView->m_rtMapRange.left;
	center.y=(point.y-SmallRect.Height())*pView->m_rtMapRange.Height()/SmallRect.Height()+pView->m_rtMapRange.bottom;


	pView->m_CurWinScope.left=center.x-width/2;
	pView->m_CurWinScope.right=center.x+width/2;
	pView->m_CurWinScope.top=center.y-height/2;
	pView->m_CurWinScope.bottom=center.y+height/2;


     pView->Invalidate();  
	}

		
	CDialog::OnLButtonDown(nFlags, point);
}
