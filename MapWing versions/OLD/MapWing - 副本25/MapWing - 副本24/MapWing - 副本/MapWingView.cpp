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
		CRect scrRect;//������Ļ��Χ
		GetClientRect(&scrRect);//�õ���Ļ���ڿͻ�����Χ��С
		pDC->SetMapMode(MM_ISOTROPIC);//����ӳ��ģʽ
		if (m_CurWinScope.top>m_CurWinScope.bottom)//�����ͼ��Χ����
		{
			pDC->SetViewportOrg((scrRect.left+scrRect.right)/2,(scrRect.bottom+scrRect.top)/2);//�����ӿ�ԭ��
			pDC->SetWindowOrg((m_CurWinScope.left+m_CurWinScope.right)/2,(m_CurWinScope.bottom+m_CurWinScope.top)/2);//���ô���ԭ��
			
			//���㵱ǰ��ͼ��Χ�ĳ��ȺͿ��
			long dx = labs(m_CurWinScope.right-m_CurWinScope.left);
			long dy = labs(m_CurWinScope.top-m_CurWinScope.bottom);
			
			pDC->SetWindowExt(dx,dy);//���ô��ڷ�Χ
			pDC->SetViewportExt((scrRect.right-scrRect.left-20),(scrRect.top-scrRect.bottom+20));//�����ӿڷ�Χ

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
    //���ͼ���Ѵ�
	if(m_IsLoadMap)
	{ 
		CClientDC dc(this);
		dc.SetROP2(R2_NOTXORPEN);
		OnPrepareDC(&dc);
		//��¼�������λ�ã��豸���꣩
		POINT mousepoint = point;
		//���豸���꣨�ͻ������꣩ת��Ϊ�߼����꣨�������꣩
		dc.DPtoLP(&mousepoint);

        //��������β���
        if(m_CurOper == ID_PAN)
		{
			//��¼��ʼ��
			m_rtZoom.left = mousepoint.x;
			m_rtZoom.top = mousepoint.y;
	        //�������
			::SetCapture(this->GetSafeHwnd( ));
		}	


		//��Ŵ����
		if(m_CurOper == ID_ZOOMINPOINT)
		{
			ZoomIn(0.25,mousepoint);
			Invalidate();
      
		}

		//�����С
		if(m_CurOper == ID_ZOOMOUTPOINT)
		{
			
               ZoomOut(1,mousepoint);
			   Invalidate();
      
		}

		//����ηŴ�
		if(m_CurOper == ID_ZOOMIN)
		{
			//��¼��ʼ��
			m_rtZoom.left = m_rtZoom.right = mousepoint.x;
			m_rtZoom.top = m_rtZoom.bottom = mousepoint.y;

			//�����������
			dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
			//�������
			::SetCapture(this->GetSafeHwnd( ));
		}
		if (m_CurOper==ID_ZOOMOUT)
		{
			m_rtZoom.left = m_rtZoom.right = mousepoint.x;
			m_rtZoom.top = m_rtZoom.bottom = mousepoint.y;

			//�����������
			dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
			//�������
			::SetCapture(this->GetSafeHwnd( ));
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CMapWingView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMapWingDoc* pDoc = GetDocument();

	//���ͼ���Ѵ�
	if(m_IsLoadMap)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOTXORPEN);
		OnPrepareDC(&dc);
		
		//��¼�������λ�ã��豸���꣩
		POINT mousepoint = point;
		
		//���豸���꣨�ͻ������꣩ת��Ϊ�߼����꣨�������꣩
		dc.DPtoLP(&mousepoint);
	    //�����β���
		if(m_CurOper == ID_PAN)
		{
			//��¼������
			m_rtZoom.right = mousepoint.x;
			m_rtZoom.bottom = mousepoint.y;

			ZoomMove();
    	    //�ͷ���겶��״̬
			::ReleaseCapture();
            Invalidate();
	        ((CMainFrame*)AfxGetMainWnd())->m_wndHawkeyeDlg.DrawRect();
			
		}	

		//���ηŴ�
		if(m_CurOper == ID_ZOOMIN)
		{
	        m_rtZoom.right = mousepoint.x;
			m_rtZoom.bottom = mousepoint.y;
			if(m_rtZoom.right==m_rtZoom.left||m_rtZoom.top==m_rtZoom.bottom)
			{
			}
			else
			{
			    //���
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
		     	//��¼������
		     	m_rtZoom.right = mousepoint.x;
			    m_rtZoom.bottom = mousepoint.y;
			
		    	//���»���
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);

			    //���������������� ���⵹��������
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
			    //���þ��ηŴ���
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
			    //���
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			
		     	//��¼������
		     	m_rtZoom.right = mousepoint.x;
			    m_rtZoom.bottom = mousepoint.y;
			
		    	//���»���
			    dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);

			    //���������������� ���⵹��������
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
			    //���þ��ηŴ���
			    ZoomaxRect();
			}
		}
			
		//�ͷ���겶��״̬
		::ReleaseCapture();
		Invalidate();
	}
	CView::OnLButtonUp(nFlags, point);
}

void CMapWingView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMapWingDoc* pDoc=GetDocument();
	//�ж��Ƿ��ͼ���ļ�
	if(m_IsLoadMap)
	{	
         CClientDC dc(this);
		
		 dc.SetROP2(R2_NOTXORPEN);//���û�ͼ���ģʽ
		 OnPrepareDC(&dc);				
		 POINT mousepoint = point;	//��¼�������λ�ã��豸���꣩			 
		 dc.DPtoLP(&mousepoint);//���豸���꣨�ͻ������꣩ת��Ϊ�߼����꣨�������꣩	     		
		 FillStatusCoord(mousepoint); //״̬����ʾ
        //�������״̬
		if(GetCapture()==this)
		{
			//���ηŴ�
			if(m_CurOper == ID_ZOOMIN)
			{
				HCURSOR hcurHand;
				hcurHand= AfxGetApp()->LoadCursor(IDC_ZOOMIN);
				SetCapture();
				::SetCursor(hcurHand);//���ù����Դ
				//�����ǰ�ľ���
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
				
				m_rtZoom.right = mousepoint.x;
				m_rtZoom.bottom = mousepoint.y;				
				//�����¾���
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
			}

			if (m_CurOper==ID_ZOOMOUT)
			{
				HCURSOR hcurHand;
				hcurHand= AfxGetApp()->LoadCursor(IDC_ZOOMOUT);
				SetCapture();
				::SetCursor(hcurHand);//���ù����Դ
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);
				
				m_rtZoom.right = mousepoint.x;
				m_rtZoom.bottom = mousepoint.y;
				
				//�����¾���
				dc.Rectangle(m_rtZoom.left,m_rtZoom.top,m_rtZoom.right,m_rtZoom.bottom);

			}

          //�����β���
	       if(m_CurOper == ID_PAN)
		   {
		   		HCURSOR hcurHand;
				hcurHand= AfxGetApp()->LoadCursor(IDC_PAN1);
				SetCapture();
				::SetCursor(hcurHand);//���ù����Դ
		       //��¼������
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
	//���㵱ǰ���ڵĴ�С
	double dx = labs(m_CurWinScope.right - m_CurWinScope.left);
	double dy = labs(m_CurWinScope.top - m_CurWinScope.bottom);
    double limitx=(double)(m_rtMapRange.right-m_rtMapRange.left)/(double)500;
	double limity=(double)(m_rtMapRange.top-m_rtMapRange.bottom)/(double)500;

	if((dx<limitx||dy<limity)&&(m_CurOper == ID_ZOOMIN||m_CurOper == ID_ZOOMINPOINT))
	{	MessageBox("�Ѵﵽ�����ʾ����");
		return;
	}
  
	CRect rect;
	GetClientRect(&rect);
	if(dx/(m_rtMapRange.right-m_rtMapRange.left)>rect.Width()||dy/(m_rtMapRange.top-m_rtMapRange.bottom)>rect.Height())
	{
		MessageBox("�ѵ���С��ʾ����");
		return;
	}

   //�õ���ǰ�ӿڿͻ�����ľ��η�Χ
	CRect rcEnd;
	GetClientRect(&rcEnd);
	//�õ���ͼ�ͻ������С
	long nHScreen = rcEnd.Height();
	long nWScreen = rcEnd.Width();
	
	//�������Ŵ��ڷ�Χ����ͼ�ͻ�����Χ����
	if(dx - dy >= 0.0)
	{  
		dy = nHScreen*dx/nWScreen;
	}
	else if(dx - dy < 0.0)
	{
		dx = nWScreen*dy/nHScreen;
	}
	
	//�õ��µĴ��ڷ�Χ
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
	//�����ƶ���λ����
	double detX=0,detY=0;
	detX = m_rtZoom.right - m_rtZoom.left;
	detY = m_rtZoom.top - m_rtZoom.bottom;
	
	//����λ�ƺ�ĵ�ͼ��ʾ��Χ
	RECT tmp_Rt;
	tmp_Rt.left = long(m_CurWinScope.left -detX);
	tmp_Rt.right = long(m_CurWinScope.right -detX);
	tmp_Rt.top = long(m_CurWinScope.top + detY);
	tmp_Rt.bottom = long(m_CurWinScope.bottom + detY);
	
	//�������õ�ǰ���εķ�Χ
	m_CurWinScope = tmp_Rt;
}

void CMapWingView::ZoominRect() 
{
	//�������������ĵ���߼�����
	POINT center;
	center.x = (m_rtZoom.left+m_rtZoom.right)/2;
	center.y = (m_rtZoom.top+m_rtZoom.bottom)/2;
	
	//��������ϵ��
	unsigned long dx = labs(m_CurWinScope.right - m_CurWinScope.left);
	unsigned long dy = labs(m_CurWinScope.top - m_CurWinScope.bottom);
	double kx = double(fabs((double)m_rtZoom.right - m_rtZoom.left)/dx);
	double ky = double(fabs((double)m_rtZoom.top - m_rtZoom.bottom)/dy);
	double k = (kx- ky)>0?kx:ky;

    ZoomIn(k/2,center);
}


void CMapWingView::ZoomAdjust()
{
	//�����Ŵ󴰿ڷ�Χ��ԭʼ���ڷ�Χ�Ĺ�ϵ
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
	//�������������ĵ���߼�����
	POINT center;
	center.x = (m_rtZoom.left+m_rtZoom.right)/2;
	center.y = (m_rtZoom.top+m_rtZoom.bottom)/2;
	
	//��������ϵ��
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
		//��ͼ����
		char map_coortext[120];
		memset(map_coortext,0x00,sizeof(char)*120);
		sprintf(map_coortext," ��ǰ����:��X��%9d ��Y��%9d",point.x,point.y);	
		//�õ������ڵ��Ӵ��ڡ���״̬��
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
