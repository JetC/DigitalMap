// MapManagerView.cpp : implementation of the CMapManagerView class
//

#include "stdafx.h"
#include "MapManager.h"

#include "MapManagerDoc.h"
#include "MapManagerView.h"
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
// CMapManagerView

IMPLEMENT_DYNCREATE(CMapManagerView, CView)

BEGIN_MESSAGE_MAP(CMapManagerView, CView)
	//{{AFX_MSG_MAP(CMapManagerView)
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
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapManagerView construction/destruction

CMapManagerView::CMapManagerView()
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
	m_Ismouseup=TRUE;
}

CMapManagerView::~CMapManagerView()
{
    if(NULL!=PointXyz)
	{
	    delete []PointXyz;
	    PointXyz=NULL;
	}
}

BOOL CMapManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapManagerView draManager

void CMapManagerView::OnDraw(CDC* pDC)
{
	CMapManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (m_IsLoadMap==TRUE)
	{
		pDoc->map1->SetLayerVisible(m_CurWinScope);
		pDoc->map1->DrawMap(pDC);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CMapManagerView printing

BOOL CMapManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMapManagerView diagnostics

#ifdef _DEBUG
void CMapManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CMapManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapManagerDoc* CMapManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapManagerDoc)));
	return (CMapManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapManagerView message handlers

void CMapManagerView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
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
			
			//���㵱ǰ��ͼ��Χ�ĳ��ȺͿ���
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

BOOL CMapManagerView::OnEraseBkgnd(CDC* pDC) 
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

void CMapManagerView::OnZoomin() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMIN;
}

void CMapManagerView::OnZoomout() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMOUT;
	
}

void CMapManagerView::OnZoominpoint() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMINPOINT;
	
}


void CMapManagerView::OnZoomoutpoint() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_ZOOMOUTPOINT;
	
}

void CMapManagerView::OnPan() 
{
	// TODO: Add your command handler code here
	m_CurOper = ID_PAN;
}

void CMapManagerView::OnFullwinds() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_FULLWINDS;
	m_CurWinScope=m_rtMapRange;
	Invalidate();
	((CMainFrame*)AfxGetMainWnd())->m_wndHawkeyeDlg.Invalidate();
	
}


void CMapManagerView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CMapManagerDoc* pDoc = GetDocument();
    //���ͼ���Ѵ�
	if(m_IsLoadMap)
	{ 
		m_Ismouseup=FALSE;
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
		//�������
		if(m_CurOper==ID_MEASUREDISTANCE)
		{
			m_PointOrign=mousepoint;
			m_PointOld=mousepoint;
			m_bCountDis=1;
			CountArray.Add(mousepoint);
			
			CPen pen(PS_SOLID,10,RGB(255,0,0));
			CPen pen1(PS_SOLID,1,RGB(255,0,0));
			CPen *pOldPen=dc.SelectObject(&pen);
			if(CountArray.GetSize()>1)
			{
				dc.MoveTo(CountArray.GetAt(CountArray.GetSize()-2));
				dc.LineTo(CountArray.GetAt(CountArray.GetSize()-1));
			}
			pOldPen=dc.SelectObject(&pen1);
			CDC *pDC1=GetDC();
			int r=3;
			pOldPen=pDC1->SelectObject(&pen1);
			pDC1->Rectangle(point.x-r,point.y-r,point.x+r,point.y+r);
		}
		//�������
		if(m_CurOper == ID_MEASUREAREA)
		{
			m_bCountArea=1;
			m_PointOrign=mousepoint;
			m_PointOld=mousepoint;
			CountArray.Add(mousepoint);
			CPen pen(PS_DASHDOT,1,RGB(0,0,255));
			CPen pen1(PS_SOLID,1,RGB(255,0,0));
			CPen *pOldPen=dc.SelectObject(&pen);
			if(CountArray.GetSize()>1)
			{
				dc.MoveTo(CountArray.GetAt(CountArray.GetSize()-2));
				dc.LineTo(CountArray.GetAt(CountArray.GetSize()-1));
			}
			pOldPen=dc.SelectObject(&pen1);
			CDC *pDC1=GetDC();
			int r=3;
			pOldPen=pDC1->SelectObject(&pen1);
			pDC1->Rectangle(point.x-r,point.y-r,point.x+r,point.y+r);			
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CMapManagerView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMapManagerDoc* pDoc = GetDocument();

	//���ͼ���Ѵ�
	if(m_IsLoadMap)
	{
		m_Ismouseup=TRUE;
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
			//�ͷ���겶��״̬
			::ReleaseCapture();
			Invalidate();
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
				//�ͷ���겶��״̬
				::ReleaseCapture();
				Invalidate();
			}
		}
			
	}
	CView::OnLButtonUp(nFlags, point);
}

void CMapManagerView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMapManagerDoc* pDoc=GetDocument();
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
				SetCursor(hcurHand);//���ù����Դ
		       //��¼������
			    m_rtZoom.right = mousepoint.x;
		        m_rtZoom.bottom = mousepoint.y;

			    ZoomMove();
	    		hcurHand= AfxGetApp()->LoadCursor(IDC_PAN2);
	    		SetCursor(hcurHand);
			    Invalidate();
	    
		   }
		 }
	       if (m_CurOper==ID_MEASUREDISTANCE && (m_bCountDis==1))
		   {
			   if (m_PointOld!=point)
			   {
				   	dc.SetROP2(R2_NOTXORPEN);
					CPen pen1(PS_SOLID,3,RGB(0,0,255));
					CPen *pOldPen1=dc.SelectObject(&pen1);
					CBrush brush1(HS_DIAGCROSS,RGB(3,200,200));
					CBrush *pOldBrush1=dc.SelectObject(&brush1);
					//������ǰ�Ķ����
					CPoint *pPolyPoint=new CPoint[CountArray.GetSize()+1];
					for(int i=0;i<CountArray.GetSize();i++)
					{
						pPolyPoint[i]=CountArray.GetAt(i);
					}
					//��������߲�ȥԭ���ľ��Σ�
					pPolyPoint[CountArray.GetSize()]=m_PointOld;
					dc.Polyline(pPolyPoint,CountArray.GetSize()+1);
				
					pPolyPoint[CountArray.GetSize()]=mousepoint;
					dc.Polyline(pPolyPoint,CountArray.GetSize()+1);
					m_PointOld=mousepoint;
					delete [] pPolyPoint;

			   }
		   }
		 
		   if(m_CurOper == ID_MEASUREAREA && (m_bCountArea==1))
			{
				if(m_PointOld!=point)
				{
				
					dc.SetROP2(R2_NOTXORPEN);
					CPen pen1(PS_DOT,1,RGB(0,0,255));
					CPen *pOldPen1=dc.SelectObject(&pen1);
					CBrush brush1(HS_DIAGCROSS,RGB(3,200,200));
					CBrush *pOldBrush1=dc.SelectObject(&brush1);
					//������ǰ�Ķ����
					CPoint *pPolyPoint=new CPoint[CountArray.GetSize()+1];
					for(int i=0;i<CountArray.GetSize();i++)
					{
						pPolyPoint[i]=CountArray.GetAt(i);
					}
					//��������߲�ȥԭ���ľ��Σ�
					pPolyPoint[CountArray.GetSize()]=m_PointOld;
					dc.Polygon(pPolyPoint,CountArray.GetSize()+1);
				
					pPolyPoint[CountArray.GetSize()]=mousepoint;
					dc.Polygon(pPolyPoint,CountArray.GetSize()+1);
					m_PointOld=mousepoint;
					delete [] pPolyPoint;
				}	
			}
		
	}
	
	CView::OnMouseMove(nFlags, point);
}

BOOL CMapManagerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
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


void CMapManagerView::ZoomIn(double k,POINT mousepoint)
{
	//���㵱ǰ���ڵĴ�С
	double dx = labs(m_CurWinScope.right - m_CurWinScope.left);
	double dy = labs(m_CurWinScope.top - m_CurWinScope.bottom);
    double limitx=(double)(m_rtMapRange.right-m_rtMapRange.left)/(double)500;
	double limity=(double)(m_rtMapRange.top-m_rtMapRange.bottom)/(double)500;

	if(dx<limitx||dy<limity)
	{	
		MessageBox("�ﵽ�����ʾ������ϵͳ�Զ�Ϊ���ָ�����ʼ������");
		OnFullwinds();
		return;
	}
	OnFullwinds();
	CRect rect;
	GetClientRect(&rect);
	
	if(dx/(m_rtMapRange.right-m_rtMapRange.left)>rect.Width()||dy/(m_rtMapRange.top-m_rtMapRange.bottom)>rect.Height())
	{
		MessageBox("�ﵽ��С��ʾ����,ϵͳ�Զ�Ϊ���ָ���ԭʼ������");
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
void CMapManagerView::ZoomOut(double k,POINT mousepoint)
{
	ZoomIn(k,mousepoint);
}


void CMapManagerView::ZoomMove()
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

void CMapManagerView::ZoominRect() 
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


void CMapManagerView::ZoomAdjust()
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


void CMapManagerView::ZoomaxRect()
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



void CMapManagerView::FillStatusCoord(POINT point)
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

void CMapManagerView::OnMeasuredistance() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_MEASUREDISTANCE;
}

void CMapManagerView::OnMeasurearea() 
{
	// TODO: Add your command handler code here
	m_CurOper=ID_MEASUREAREA;
}

void CMapManagerView::OnRefresh() 
{
	// TODO: Add your command handler code here
	Invalidate();
	
}

void CMapManagerView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_CurOper == ID_MEASUREDISTANCE)
	{
		m_bCountDis=0;
		CDC *pDC=GetDC();
		pDC->SetBkMode(TRANSPARENT);
		CPen pen(PS_SOLID,2,RGB(0,255,0));
        CPen *pOldPen=pDC->SelectObject(&pen);
		CBrush brush(RGB(200,255,200));
		CFont font;
		font.CreateFont(15,0,0,0,0,0,0,0,0,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS 
			,DEFAULT_QUALITY,DEFAULT_PITCH&FF_SWISS,"����");
		CFont *pOldFont=pDC->SelectObject(&font);
		CBrush *pOldBrush=pDC->SelectObject(&brush);
		pDC->Rectangle(point.x+5,point.y+5,point.x+208,point.y+60);
		
		float disX,disY,DisXY;
		float TempResult=0.0;
		for(int i=0;i<CountArray.GetSize()-1;i++)
		{
			disX=CountArray.GetAt(i+1).x-CountArray.GetAt(i).x;
			disY=CountArray.GetAt(i+1).y-CountArray.GetAt(i).y;
			DisXY=sqrt(disX*disX+disY*disY);
			TempResult+=DisXY;
		}
		
		TempResult = TempResult/1000;
		CString ss;
		TempResult=labs(TempResult);
		ss.Format("%f",TempResult);
		ss="ֱ�߾���"+ss+"��";
		
		pDC->TextOut(point.x+15,point.y+15,ss);
		
		
		CountArray.RemoveAll();//�����ǰ��¼��켣���괮����
	}
	if(m_CurOper == ID_MEASUREAREA)
	{
		m_bCountArea=0;
		CDC *pDC1=GetDC(); 			
		OnPrepareDC(pDC1);
		pDC1->SetBkMode(TRANSPARENT);//ʹ��ǰ�����ޱ���ɫ
		CPen pen1(PS_DOT,1,RGB(0,0,255));
		CBrush brush1(HS_DIAGCROSS,RGB(3,200,200));
		CPen *pOldPen1=pDC1->SelectObject(&pen1);
		CBrush *pOldBrush1=pDC1->SelectObject(&brush1);
		int m_Number=CountArray.GetSize();
		CPoint *p_Point=new CPoint[m_Number];
		for(int i=0;i<m_Number;i++)
		{
			p_Point[i]=CountArray.GetAt(i);//��һ����������
		}
		pDC1->Polygon(p_Point,m_Number);
		delete []p_Point;
		
	
		CDC *pDC=GetDC();
		pDC->SetBkMode(TRANSPARENT);
		CPen pen(PS_DOT,1,RGB(250,0,0));
        CPen *pOldPen=pDC->SelectObject(&pen);
		CBrush brush(RGB(200,255,200));
		CFont font;
		font.CreateFont(15,0,0,0,0,0,0,0,0,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS 
			,DEFAULT_QUALITY,DEFAULT_PITCH&FF_SWISS,"����");
		CFont *pOldFont=pDC->SelectObject(&font);
		CBrush *pOldBrush=pDC->SelectObject(&brush);
		pDC->Rectangle(point.x+5,point.y+5,point.x+200,point.y+50);
		
		float Result=0.0;
		float Area;
		if(CountArray.GetSize()>2)
		{
			CountArray.Add(CountArray.GetAt(0));
			for(int i=0;i<CountArray.GetSize()-1;i++)
			{
				CPoint Point1=CountArray.GetAt(i+1);
				CPoint Point0=CountArray.GetAt(i);
				

				Area=(-1)*(Point0.x*Point1.y-Point1.x*Point0.y)/2;
				Result+=Area;
			}
		}
		
		Result = Result/30000;
		CString pp;
		Result=labs(Result);
		pp.Format("%f",Result);
		pp="���"+pp+"ƽ����";
		pDC->TextOut(point.x+15,point.y+15,pp);
		
		CountArray.RemoveAll();//�����ǰ��¼��켣���괮����
	}
	CView::OnLButtonDblClk(nFlags, point);
}

