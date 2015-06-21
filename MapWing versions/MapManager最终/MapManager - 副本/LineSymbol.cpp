// LineSymbol.cpp: implementation of the CLineSymbol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapManager.h"
#include "LineSymbol.h"
#include"MainFrm.h"
#include"MapManagerView.h"
#include"math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineSymbol::CLineSymbol()
{

}

CLineSymbol::~CLineSymbol()
{

}

CLineSymbol::CLineSymbol(CPoint *points,long PtNum,int LineSymbolType, int LineSymbolWidth,long LineSymbolColor)
{
	pt=new CPoint[PtNum];
	for(int i=0;i<PtNum;i++)
	{
		pt[i].x=points[i].x;
	    pt[i].y=points[i].y;

	}
	m_ptnum=PtNum;
	m_LineSymbolType = LineSymbolType;
	m_LineSymbolWidth = LineSymbolWidth;
	m_LineSymbolColor = LineSymbolColor;
}
void CLineSymbol::DrawSymbol(CDC *pDC)
{

	if(m_LineSymbolType == 1)
		DrawSolidLine(pDC);//绘制实体线状目标
	if(m_LineSymbolType == 2)
		DrawVirtualLine(pDC);//绘制虚体线状目标（主要用于绘制铁路）
	if(m_LineSymbolType == 3)
		DrawDotLine(pDC);//绘制点体线状目标
	if(m_LineSymbolType == 4)
		DrawDoubleLine(pDC);//绘制双线路
	if(m_LineSymbolType == 5)
		DrawRailwayLine(pDC);//绘制铁路
   //void CLineSymbol::DrawRailwayLine(CDC *pDC);

}
void CLineSymbol::DrawSolidLine(CDC *pDC)
{ 


	CPen pen;
	pen.CreatePen(PS_ENDCAP_FLAT|PS_GEOMETRIC|PS_SOLID,m_LineSymbolWidth,m_LineSymbolColor);
	

	CPen *pOldPen = pDC->SelectObject(&pen);
	pDC->Polyline(pt,m_ptnum);
	pDC->SelectObject(pOldPen); 
	

}			
void CLineSymbol::DrawVirtualLine(CDC *pDC)
{
    CBrush *brush = NULL;
	CBrush *oldBrush = NULL;
	CPen *pen = NULL;
	CPen *oldPen = NULL;
	DWORD *lineStyle = NULL;

    int PS = PS_USERSTYLE ;  
    lineStyle = new DWORD[2];
	for(int i=0;i<2;i++)
		lineStyle[i] = (DWORD)(2*m_LineSymbolWidth); 
				
		
		LOGBRUSH logBrush;
		memset(&logBrush,0,sizeof(LOGBRUSH));
		logBrush.lbColor = m_LineSymbolColor;
		
		pen = new CPen(PS|PS_ENDCAP_FLAT|PS_GEOMETRIC,
						m_LineSymbolWidth,
						&logBrush,
						2,
						lineStyle);
		
		oldPen = pDC->SelectObject(pen);
		oldBrush = pDC->SelectObject(brush);

      pDC->Polyline(pt,m_ptnum);
	
      pDC->SelectObject(oldPen);
	  pDC->SelectObject(oldBrush);
	 if( pen != NULL) delete pen;
	 if( brush != NULL) delete brush;
	 if(lineStyle != NULL) delete lineStyle;

}
void CLineSymbol::DrawDotLine(CDC *pDC)
{
	float r;
	float d,dt=0;
	float dx,dy,de,sn,cs;
	float dp;
	long k=0;
	r = m_LineSymbolWidth/2;//点的半径
	d = 2*r;//一个图元的跨度为2d

	//创建画笔
	CPen pen;
	pen.CreatePen(0,1,m_LineSymbolColor);
	CPen *pOldPen = pDC->SelectObject(&pen);
	//创建画刷
	CBrush brush;
	brush.CreateSolidBrush(m_LineSymbolColor);
	CBrush *pOldBrush = pDC->SelectObject(&brush);

	for(long i=0;i<m_ptnum-1;i++)
	{
		dt +=  sqrt(pow((float)((pt[i+1].x- pt[i].x)),2)+pow((float)((pt[i+1].y-pt[i].y)),2));
	}
	//计算图元数
	long n;
	n = (long)(dt/d);
	// 申请变量空间
	CPoint *npt;
	npt = new CPoint [n*2];
	
	if(n%2 != 0)
		d = dt/n;
	else 
		d = dt/(n+1);
	dp = r;
	for(int i=0;i<m_ptnum-1;i++)
	{
		dx = pt[i+1].x-pt[i].x;
		dy = pt[i+1].y-pt[i].y;
		de = sqrt(pow(dx,2)+pow(dy,2));
		sn = dy/de;
		cs = dx/de;
		while(dp<=de)
		{
			npt[k].x = pt[i].x+cs*dp;
			npt[k].y = pt[i].y+sn*dp;
			k++;
			dp = dp+d*2;
		}
		dp = dp-de;
	}
	//绘制以npt[]为圆心的圆,个数为k
	for(int i = 0;i<k;i++)
		pDC->Ellipse(npt[i].x+r,npt[i].y+r,npt[i].x-r,npt[i].y-r);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldPen);
	
	delete []npt;
}
void CLineSymbol::DrawDoubleLine(CDC *pDC)
{
	long k=0;
	double t=m_LineSymbolWidth/2;
	double dx,dy,de,sn,cs;
	CPoint tpt[4000],bpt[4000],ntpt[2000],nbpt[2000];
   

	for(long i = 0;i<m_ptnum-1;i++)
	{
		dx = pt[i+1].x-pt[i].x;
		dy = pt[i+1].y-pt[i].y;
		de = sqrt(pow(dx,2)+pow(dy,2));
		sn = -dy/de;
		cs = dx/de;
		tpt[k].x = (pt[i].x+sn*t);
		tpt[k].y = pt[i].y+cs*t;
		bpt[k].x = pt[i].x-sn*t;
		bpt[k].y = pt[i].y-cs*t;
		tpt[k+1].x = pt[i+1].x+sn*t;
		tpt[k+1].y = pt[i+1].y+cs*t;
		bpt[k+1].x = pt[i+1].x-sn*t;
		bpt[k+1].y = pt[i+1].y-cs*t;
		k = k+2;
	}

	ntpt[0] = tpt[0];
	nbpt[0] = bpt[0];
	double D,Du,u;
	long nn=1;//处理后的点数
	long nn2=1;//处理后的点数
	for(int i = 0;i<k-2;)
	{
   
     D=((double)(tpt[i+3].x-tpt[i+2].x)/(double)100)*((double)(tpt[i+1].y-tpt[i].y)/(double)100)
         -((double)(tpt[i+1].x-tpt[i].x)/(double)100)*((double)(tpt[i+3].y-tpt[i+2].y)/(double)100);
     Du=((double)(tpt[i+3].x-tpt[i+2].x)/(double)100)*((double)(tpt[i+2].y-tpt[i].y)/(double)100)
		-((double)(tpt[i+3].y-tpt[i+2].y)/(double)100)*((double)(tpt[i+2].x-tpt[i].x)/(double)100);
		
	
		u = Du/D;
		ntpt[nn].x = (long)(tpt[i].x+u*(tpt[i+1].x-tpt[i].x));
		ntpt[nn].y = (long)(tpt[i].y+u*(tpt[i+1].y-tpt[i].y));
		nn++;
		i += 2;
	}
	ntpt[nn] = tpt[k-1];
 //	pDC->Polyline(ntpt,m_ptnum);
	for(int i = 0;i<k-2;)
	{
     	D = ((double)(bpt[i+3].x-bpt[i+2].x)/(double)100)*((double)(bpt[i+1].y-bpt[i].y)/(double)100)-((double)(bpt[i+1].x-bpt[i].x)/(double)100)*((double)(bpt[i+3].y-bpt[i+2].y)/(double)100);
		Du =((double)(bpt[i+3].x-bpt[i+2].x)/(double)100)*((double)(bpt[i+2].y-bpt[i].y)/(double)100)-((double)(bpt[i+3].y-bpt[i+2].y)/(double)100)*((double)(bpt[i+2].x-bpt[i].x)/(double)100);
		u = Du/D;
		nbpt[nn2].x = (long)(bpt[i].x+u*(bpt[i+1].x-bpt[i].x));
		nbpt[nn2].y = (long)(bpt[i].y+u*(bpt[i+1].y-bpt[i].y));
		nn2++;
		i += 2;
	}
	nbpt[nn] = bpt[k-1];
//	pDC->Polyline(nbpt,m_ptnum);
    //pDC->SelectObject(pOldPen);
	CPen pen;
	    pen.CreatePen(0,1,RGB(255,255,255));
       CPen *pOldPen = pDC->SelectObject(&pen);
	   CBrush brush;
	   brush.CreateSolidBrush(RGB(255,255,255));
	   CBrush *pOldBrush=pDC->SelectObject(&brush);
	for(int j=0;j<m_ptnum-1;j++)
	{
		CPoint pt[5];
		pt[0]=ntpt[j];
		pt[1]=nbpt[j];
		pt[2]=nbpt[j+1];
		pt[3]=ntpt[j+1];
		pt[4]=pt[0];
    
    	pDC->Polygon(pt,5);
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	CPen pen1;
	pen1.CreatePen(0,1,m_LineSymbolColor);
	CPen *pOldPen1 = pDC->SelectObject(&pen1);

	pDC->Polyline(nbpt,m_ptnum);
    pDC->Polyline(ntpt,m_ptnum);
		pDC->SelectObject(pOldPen1);
}

void CLineSymbol::DrawRailwayLine(CDC *pDC)
{

	CPen pen1;
	pen1.CreatePen(PS_ENDCAP_FLAT|PS_GEOMETRIC|PS_SOLID,m_LineSymbolWidth,RGB(0,0,0));
	CPen *pOldPen = pDC->SelectObject(&pen1);
	pDC->Polyline(pt,m_ptnum);
	pDC->SelectObject(pOldPen); 

    CBrush *brush = NULL;
	CBrush *oldBrush = NULL;
	CPen *pen = NULL;
	CPen *oldPen = NULL;
	DWORD *lineStyle = NULL;


	CFrameWnd *pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
    CMapManagerView *pView = (CMapManagerView *) pFrame->GetActiveView();

	CClientDC dc(pView);
    pView->OnPrepareDC(&dc);
	CPoint point1;
	CPoint point2;
	point1.x=100;
	point1.y=200;
	point2.x=102;
	point2.y=200;
	dc.DPtoLP(&point1);
	dc.DPtoLP(&point2);




    int PS = PS_USERSTYLE ;  
    lineStyle = new DWORD[2];
	for(int i=0;i<2;i++)
		lineStyle[i] = (DWORD)(2*m_LineSymbolWidth); 
				
		
		LOGBRUSH logBrush;
		memset(&logBrush,0,sizeof(LOGBRUSH));
		logBrush.lbColor = RGB(255,255,255);
		
		pen = new CPen(PS|PS_ENDCAP_FLAT|PS_GEOMETRIC,
						m_LineSymbolWidth-(point2.x-point1.x),
						&logBrush,
						2,
						lineStyle);
		
		oldPen = pDC->SelectObject(pen);
		oldBrush = pDC->SelectObject(brush);

      pDC->Polyline(pt,m_ptnum);

      pDC->SelectObject(oldPen);
	  pDC->SelectObject(oldBrush);
	 if( pen != NULL) delete pen;
	 if( brush != NULL) delete brush;
	 if(lineStyle != NULL) delete lineStyle;
}


