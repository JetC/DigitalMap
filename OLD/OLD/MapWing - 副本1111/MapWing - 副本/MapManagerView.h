// MapManagerView.h : interface of the CMapManagerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPManagerVIEW_H__848396B0_A3BE_4E24_A948_812E60E8D487__INCLUDED_)
#define AFX_MAPManagerVIEW_H__848396B0_A3BE_4E24_A948_812E60E8D487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapManagerDoc.h"


class CMapManagerView : public CView
{
protected: // create from serialization only
	CMapManagerView();
	DECLARE_DYNCREATE(CMapManagerView)

// Attributes
public:
	CMapManagerDoc* GetDocument();
// Operations


protected:
	CToolTipCtrl m_ToolTip;//������ʾ����
	int m_GridSelected;//��ǰѡ�еĿռ���������
	int m_PrevGrid;//��һ��ѡ�еĸ���
	CPoint m_pt;

public:
	CRect m_rtMapRange;//��ͼԭʼ��Χ
	BOOL  m_IsLoadMap;//�Ƿ���ص�ͼ
	BOOL  m_IsLoadDem;//�Ƿ����Dem

	CRect m_CurWinScope;//���ڷ�Χ
	long  m_CurOper;//��ǰ����

	//��¼��������ʱ���߹յ�����
	
	CPoint *PointXyz;
    //�����¼��ʵ����Ƥ��Ч����
	 int PushNumb;

	 
    CPoint mPointOrign,mPointOrign1,mPointOld;
   
	//����Ŵ������ʱ���η�Χ
    RECT m_rtZoom;
    //OnTimer�õ��ı��
	BOOL m_TimerTag;
    //��ʱ��
    long ID_TIMER;

    //�ϴ�ѡ�еĲ��
	int m_PrevLayer;
	//�ϴ�ѡ�еĲ��
	long m_PrevObject;
	//��ǰѡ�еĲ��
	int m_LayerID;
	//��ǰ�е�Ŀ���
   long  m_ObjectID;
   	CArray<CPoint,CPoint> CountArray;
	CPoint m_PointOrign;//������¼Դ���뵱ǰ���ǰһ��
	CPoint m_PointOld;
	BOOL m_bCountDis;//������־�Ƿ��ڼ��㳤�Ⱥͼ������״̬
	BOOL m_bCountArea;
	BOOL m_Ismouseup;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	void ZoomIn(double k,POINT mousepoint);
	void ZoomOut(double k,POINT mousepoint);
	void ZoomMove();
	void ZoominRect();
	void ZoomaxRect();
	void ZoomAdjust();
	void  FillStatusCoord(POINT point);	
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapManagerView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnPan();
	afx_msg void OnFullwinds();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnZoomoutpoint();
	afx_msg void OnZoominpoint();
	afx_msg void OnMeasuredistance();
	afx_msg void OnMeasurearea();
	afx_msg void OnRefresh();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MapManagerView.cpp
inline CMapManagerDoc* CMapManagerView::GetDocument()
   { return (CMapManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPManagerVIEW_H__848396B0_A3BE_4E24_A948_812E60E8D487__INCLUDED_)
