// MapWingView.cpp : implementation of the CMapWingView class
//

#include "stdafx.h"
#include "MapWing.h"

#include "MapWingDoc.h"
#include "MapWingView.h"
#include "MainFrm.h"
#include "math.h"
#include "Grid.h"
#include "GeoLayer.h"
#include "GeoMap.h"
#include "GeoLine.h"
#include "GeoPolygon.h"
#include "GeoPoint.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapWingView

IMPLEMENT_DYNCREATE(CMapWingView, CView)

BEGIN_MESSAGE_MAP(CMapWingView, CView)
	//{{AFX_MSG_MAP(CMapWingView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ZOOMIN, OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, OnZoomout)
	ON_COMMAND(ID_PAN, OnPan)
	ON_COMMAND(ID_FULLWINDS, OnFullwinds)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_ZOOMOUTPOINT, OnZoomoutpoint)
	ON_COMMAND(ID_ZOOMINPOINT, OnZoominpoint)
	ON_COMMAND(ID_MEASUREDISTANCE, OnMeasuredistance)
	ON_COMMAND(ID_MEASUREAREA, OnMeasurearea)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapWingView construction/destruction

CMapWingView::CMapWingView()
{
	// TODO: add construction code here
	m_IsLoadMap=false;
	PushNumb=0;
	PointXyz=new CPoint[200];
    m_PrevLayer=-1;
    m_PrevObject=-1;
    m_LayerID=-1;
    m_ObjectID=-1;;
    m_TimerTag=false;
    ID_TIMER=0;
}

CMapWingView::~CMapWingView()
{
    if(NULL!=PointXyz)
	{
	    delete []PointXyz;
	    PointXyz=NULL;
	}
}

BOOL CMapWingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapWingView drawing

void CMapWingView::OnDraw(CDC* pDC)
{
	CMapWingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (m_IsLoadMap==TRUE)
	{
		pDoc->map1->SetLayerVisible(m_CurWinScope);
		pDoc->map1->DrawMap(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapWingView printing

BOOL CMapWingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapWingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapWingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMapWingView diagnostics

#ifdef _DEBUG
void CMapWingView::AssertValid() const
{
	CView::AssertValid();
}

void CMapWingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapWingDoc* CMapWingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapWingDoc)));
	return (CMapWingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapWingView message handlers

void CMapWingView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	if (m_IsLoadMap)
	{
		CRect scrRect;//定义屏幕范围
		GetClientRect(&scrRect);//得到屏幕窗口客户区范围大小
		pDC->SetMapMode(MM_ISOTROPIC);//设置映射模式
		if (m_CurWinScope.top>m_CurWinScope.bottom)//如果地图范围合理
		{
			pDC->SetViewportOrg((scrRect.left+scrRect.right)/2,(scrRect.bottom+scrRect.top)/2);//设置视口原点
			pDC->SetWindowOrg((m_CurWinScope.left+m_CurWinScope.right)/2,(m_CurWinScope.bottom+m_CurWinScope.top)/2);//设置窗口原点
			
			//计算当前地图范围的长度和宽度
			long dx = labs(m_CurWinScope.right-m_CurWinScope.left);
			long dy = labs(m_CurWinScope.top-m_CurWinScope.bottom);
			
			pDC->SetWindowExt(dx,dy);//设置窗口范围
			pDC->SetViewportExt((scrRect.right-scrRect.left-20),(scrRect.top-scrRect.bottom+20));//设置视口范围

		}
	}
	else
	{
		CView::OnPrepareDC(pDC, pInfo);
	}

}

BOOL CMapWingView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	COLORREF BACKCOLOR = RGB(255,255,255);
	CBrush brush(BACKCOLOR);
	CBrush *pOldBrush=pDC->SelectObject(&brush);
	
	CRect rc;
	pDC->GetClipBox(&rc);
	pDC->PatBlt(rc.left,rc.top,rc.Width(),rc.Height(),PATCOPY );
	pDC->SelectObject(pOldBrush); 
	return FALSE;	
	return CView::OnEraseBkgnd(pDC);
}

void CMapWingView::OnZoomin() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMIN;
}

void CMapWingView::OnZoomout() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMOUT;
	
}

void CMapWingView::OnZoominpoint() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMINPOINT;
	
}


void CMapWingView::OnZoomoutpoint() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMOUTPOINT;
	
}

void CMapWingView::OnPan() 
{
	// TODO: Add your command handler code here
	m_CurOper = ID_PAN;
}

void CMapWingView::OnFullwinds() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_FULLWINDS;
	m_CurWinScope=m_rtMapRange;
	Invalidate();
	((CMainFrame*)AfxGetMainWnd())->m_wndHawkeyeDlg.Invalidate();
	
}


void CMapWingView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CMapWingDoc* pDoc = GetDocument();
    //如果图形已打开
	if(m_IsLoadMap)
	{ 
		CClientDC dc(this);
		dc.SetROP2(R2_NOTXORPEN);
		OnPrepareDC(&dc);
		//记录鼠标点击的位置（设备坐标）
		POINT mousepoint = point;
		//由设备坐标（客户区坐标）转换为逻辑坐标（窗口坐标）
		dc.DPtoLP(&mousepoint);

        //如果点漫游操作
        if(m_CurOper == ID_PAN)
		{
			//记录开始点
			m_rtZoom.left = mousepoint.x;
			m_rtZoom.top = mousepoint.y;
	        //捕获鼠标
			::SetCapture(this->GetSafeHwnd( ));
		}	


		//点放大操作
		if(m_CurOper == ID_ZOOMINPOINT)
		{
			ZoomIn(0.25,mousepoint);
			Invalidate();
      
		}

		//点击缩小
		if(m_CurOper == ID_ZOOMOUTPOINT)
		{
			
               ZoomOut(1,mousepoint);
			   Invalidate();
      
		}

		//点矩形放大
		if(m_CurOper == ID_ZOOMIN)
		{
			//记录开始点
			m_rtZoom.left = m_rtZoom.right = mousepoint.x;
			m_rtZoom.top = m_rtZoom.bottom = mousepoint.y;

			//绘制拉框矩形
			dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
			//捕获鼠标
			::SetCapture(this->GetSafeHwnd( ));
		}
		if (m_CurOper==ID_ZOOMOUT)
		{
			m_rtZoom.left = m_rtZoom.right = mousepoint.x;
			m_rtZoom.top = m_rtZoom.bottom = mousepoint.y;

			//绘制拉框矩形
			dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
			//捕获鼠标
			::SetCapture(this->GetSafeHwnd( ));
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CMapWingView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMapWingDoc* pDoc = GetDocument();

	//如果图形已打开
	if(m_IsLoadMap)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOTXORPEN);
		OnPrepareDC(&dc);
		
		//记录鼠标点击的位置（设备坐标）
		POINT mousepoint = point;
		
		//由设备坐标（客户区坐标）转换为逻辑坐标（窗口坐标）
		dc.DPtoLP(&mousepoint);
	    //点漫游操作
		if(m_CurOper == ID_PAN)
		{
			//记录结束点
			m_rtZoom.right = mousepoint.x;
			m_rtZoom.bottom = mousepoint.y;

			ZoomMove();
    	    //释放鼠标捕获状态
			::ReleaseCapture();
            Invalidate();
	        ((CMainFrame*)AfxGetMainWnd())->m_wndHawkeyeDlg.DrawRect();
			
		}	

		//矩形放大
		if(m_CurOper == ID_ZOOMIN)
		{
	        m_rtZoom.right = mousepoint.x;
			m_rtZoom.bottom = mousepoint.y;
			if(m_rtZoom.right==m_rtZoom.left||m_rtZoom.top==m_rtZoom.bottom)
			{
			}
			else
			{
			    //清除
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
		     	//记录结束点
		     	m_rtZoom.right = mousepoint.x;
			    m_rtZoom.bottom = mousepoint.y;
			
		    	//重新绘制
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);

			    //交换矩形两个顶点 避免倒拉框的情况
			    if(m_rtZoom.left-m_rtZoom.right > 0 && m_rtZoom.top-m_rtZoom.bottom > 0)
				{
			       	RECT tmpRect;
				    memset(&tmpRect,0x00,sizeof(RECT));
				
				    tmpRect.left = m_rtZoom.right;
				    tmpRect.right = m_rtZoom.left;
				    tmpRect.top = m_rtZoom.bottom;
				    tmpRect.bottom = m_rtZoom.top;
				
				    m_rtZoom.left = tmpRect.left;
				    m_rtZoom.top = tmpRect.top;
				    m_rtZoom.right = tmpRect.right;
				    m_rtZoom.bottom = tmpRect.bottom;
				}		
			    //调用矩形放大函数
			    ZoominRect();
			}
		}
		if(m_CurOper == ID_ZOOMOUT)
		{
	        m_rtZoom.right = mousepoint.x;
			m_rtZoom.bottom = mousepoint.y;
			if(m_rtZoom.right==m_rtZoom.left||m_rtZoom.top==m_rtZoom.bottom)
			{
			}
			else
			{
			    //清除
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
		     	//记录结束点
		     	m_rtZoom.right = mousepoint.x;
			    m_rtZoom.bottom = mousepoint.y;
			
		    	//重新绘制
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);

			    //交换矩形两个顶点 避免倒拉框的情况
			    if(m_rtZoom.left-m_rtZoom.right > 0 && m_rtZoom.top-m_rtZoom.bottom > 0)
				{
			       	RECT tmpRect;
				    memset(&tmpRect,0x00,sizeof(RECT));
				
				    tmpRect.left = m_rtZoom.right;
				    tmpRect.right = m_rtZoom.left;
				    tmpRect.top = m_rtZoom.bottom;
				    tmpRect.bottom = m_rtZoom.top;
				
				    m_rtZoom.left = tmpRect.left;
				    m_rtZoom.top = tmpRect.top;
				    m_rtZoom.right = tmpRect.right;
				    m_rtZoom.bottom = tmpRect.bottom;
				}		
			    //调用矩形放大函数
			    ZoomaxRect();
			}
		}
			
		//释放鼠标捕获状态
		::ReleaseCapture();
		Invalidate();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CMapWingView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMapWingDoc* pDoc=GetDocument();
	//判断是否打开图形文件
	if(m_IsLoadMap)
	{	
         CClientDC dc(this);
		
		 dc.SetROP2(R2_NOTXORPEN);//设置绘图异或模式
		 OnPrepareDC(&dc);				
		 POINT mousepoint = point;	//记录鼠标点击的位置（设备坐标）			 
		 dc.DPtoLP(&mousepoint);//由设备坐标（客户区坐标）转换为逻辑坐标（窗口坐标）	     		
		 FillStatusCoord(mousepoint); //状态栏显示
        //捕获鼠标状态
		if(GetCapture()==this)
		{
			//矩形放大
			if(m_CurOper == ID_ZOOMIN)
			{
				HCURSOR hcurHand;
				hcurHand= AfxGetApp()->LoadCursor(IDC_ZOOMIN);
				SetCapture();
				::SetCursor(hcurHand);//调用光标资源
				//清除先前的矩形
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
				
				m_rtZoom.right = mousepoint.x;
				m_rtZoom.bottom = mousepoint.y;				
				//绘制新矩形
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			}

			if (m_CurOper==ID_ZOOMOUT)
			{
				HCURSOR hcurHand;
				hcurHand= AfxGetApp()->LoadCursor(IDC_ZOOMOUT);
				SetCapture();
				::SetCursor(hcurHand);//调用光标资源
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
				
				m_rtZoom.right = mousepoint.x;
				m_rtZoom.bottom = mousepoint.y;
				
				//绘制新矩形
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);

			}

          //点漫游操作
	       if(m_CurOper == ID_PAN)
		   {
		   		HCURSOR hcurHand;
				hcurHand= AfxGetApp()->LoadCursor(IDC_PAN1);
				SetCapture();
				::SetCursor(hcurHand);//调用光标资源
		       //记录结束点
			    m_rtZoom.right = mousepoint.x;
		        m_rtZoom.bottom = mousepoint.y;

			    ZoomMove();
	    		hcurHand= AfxGetApp()->LoadCursor(IDC_PAN2);
	    		SetCursor(hcurHand);
			    Invalidate();
	    
		   }
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}

BOOL CMapWingView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_IsLoadMap) 
	{	
		CPoint centerpoint ;
		centerpoint.x=(m_CurWinScope.left+m_CurWinScope.right)/2;
		centerpoint.y=(m_CurWinScope.top+m_CurWinScope.bottom)/2;
		if(zDelta>0)
		{
         ZoomIn(0.4,centerpoint);
		}
		if(zDelta<0)
		{
          ZoomIn(0.7,centerpoint);
		}
	}
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMapWingView::ZoomIn(double k,POINT mousepoint)
{
	//计算当前窗口的大小
	double dx = labs(m_CurWinScope.right - m_CurWinScope.left);
	double dy = labs(m_CurWinScope.top - m_CurWinScope.bottom);
    double limitx=(double)(m_rtMapRange.right-m_rtMapRange.left)/(double)500;
	double limity=(double)(m_rtMapRange.top-m_rtMapRange.bottom)/(double)500;

	if((dx<limitx||dy<limity)&&(m_CurOper == ID_ZOOMIN||m_CurOper == ID_ZOOMINPOINT))
	{	MessageBox("已达到最大显示比例");
		return;
	}
  
	CRect rect;
	GetClientRect(&rect);
	if(dx/(m_rtMapRange.right-m_rtMapRange.left)>rect.Width()||dy/(m_rtMapRange.top-m_rtMapRange.bottom)>rect.Height())
	{
		MessageBox("已到最小显示比例");
		return;
	}

   //得到当前视口客户区域的矩形范围
	CRect rcEnd;
	GetClientRect(&rcEnd);
	//得到视图客户区域大小
	long nHScreen = rcEnd.Height();
	long nWScreen = rcEnd.Width();
	
	//调整缩放窗口范围与视图客户区域范围相似
	if(dx - dy >= 0.0)
	{  
		dy = nHScreen*dx/nWScreen;
	}
	else if(dx - dy < 0.0)
	{
		dx = nWScreen*dy/nHScreen;
	}
	
	//得到新的窗口范围
	RECT Result;
	Result.left=(long)(mousepoint.x - dx * k);
	Result.right=(long)(mousepoint.x + dx * k);
	Result.top=(long)(mousepoint.y + dy * k);
	Result.bottom=(long)(mousepoint.y - dy * k);
   
    m_CurWinScope = Result;

    ((CMainFrame*)AfxGetMainWnd())->m_wndHawkeyeDlg.DrawRect();
}
void CMapWingView::ZoomOut(double k,POINT mousepoint)
{
	ZoomIn(k,mousepoint);
}


void CMapWingView::ZoomMove()
{
	//计算移动的位移量
	double detX=0,detY=0;
	detX = m_rtZoom.right - m_rtZoom.left;
	detY = m_rtZoom.top - m_rtZoom.bottom;
	
	//计算位移后的地图显示范围
	RECT tmp_Rt;
	tmp_Rt.left = long(m_CurWinScope.left -detX);
	tmp_Rt.right = long(m_CurWinScope.right -detX);
	tmp_Rt.top = long(m_CurWinScope.top + detY);
	tmp_Rt.bottom = long(m_CurWinScope.bottom + detY);
	
	//重新设置当前矩形的范围
	m_CurWinScope = tmp_Rt;
}

void CMapWingView::ZoominRect() 
{
	//求出拉框矩形中心点的逻辑坐标
	POINT center;
	center.x = (m_rtZoom.left+m_rtZoom.right)/2;
	center.y = (m_rtZoom.top+m_rtZoom.bottom)/2;
	
	//计算相似系数
	unsigned long dx = labs(m_CurWinScope.right - m_CurWinScope.left);
	unsigned long dy = labs(m_CurWinScope.top - m_CurWinScope.bottom);
	double kx = double(fabs((double)m_rtZoom.right - m_rtZoom.left)/dx);
	double ky = double(fabs((double)m_rtZoom.top - m_rtZoom.bottom)/dy);
	double k = (kx- ky)>0?kx:ky;

    ZoomIn(k/2,center);
}


void CMapWingView::ZoomAdjust()
{
	//调整放大窗口范围与原始窗口范围的关系
	if ( m_CurWinScope.right > m_rtMapRange.right ) 
	{
		int dx = m_rtMapRange.right - m_CurWinScope.right;
		m_CurWinScope.right = m_rtMapRange.right;
		m_CurWinScope.left += dx;
	}
	if ( m_CurWinScope.left < m_rtMapRange.left  ) 
	{
		int dx = m_rtMapRange.left - m_CurWinScope.left;
		m_CurWinScope.left = m_rtMapRange.left;
		m_CurWinScope.right += dx;
	}
	if ( m_CurWinScope.top > m_rtMapRange.top  ) 
	{
		int dy = m_rtMapRange.top - m_CurWinScope.top;
		m_CurWinScope.top = m_rtMapRange.top;
		m_CurWinScope.bottom += dy;
	}
	if ( m_CurWinScope.bottom < m_rtMapRange.bottom  )
	{
		int dy = m_rtMapRange.bottom - m_CurWinScope.bottom;
		m_CurWinScope.bottom = m_rtMapRange.bottom;
		m_CurWinScope.top += dy; 
	}
}


void CMapWingView::ZoomaxRect()
{
	//求出拉框矩形中心点的逻辑坐标
	POINT center;
	center.x = (m_rtZoom.left+m_rtZoom.right)/2;
	center.y = (m_rtZoom.top+m_rtZoom.bottom)/2;
	
	//计算相似系数
	unsigned long dx = labs(m_CurWinScope.right - m_CurWinScope.left);
	unsigned long dy = labs(m_CurWinScope.top - m_CurWinScope.bottom);
	double kx = double(fabs((double)m_rtZoom.right - m_rtZoom.left)/dx);
	double ky = double(fabs((double)m_rtZoom.top - m_rtZoom.bottom)/dy);
	double k = (kx- ky)>0?kx:ky;

    ZoomIn(2*k,center);
}



void CMapWingView::FillStatusCoord(POINT point)
{
	if(m_IsLoadMap )
	{
		//地图坐标
		char map_coortext[120];
		memset(map_coortext,0x00,sizeof(char)*120);
		sprintf(map_coortext," 当前坐标:【X】%9d 【Y】%9d",point.x,point.y);	
		//得到主窗口的子窗口——状态栏
		CStatusBar *p_map_status=(CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
		p_map_status->SetPaneText(1,map_coortext);
	}
	
}

void CMapWingView::OnMeasuredistance() 
{
	// TODO: Add your command handler code here
}

void CMapWingView::OnMeasurearea() 
{
	// TODO: Add your command handler code here
	
}

void CMapWingView::OnRefresh() 
{
	// TODO: Add your command handler code here
	
}
