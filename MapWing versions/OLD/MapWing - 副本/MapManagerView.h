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
	CToolTipCtrl m_ToolTip;//工具提示对象
	int m_GridSelected;//当前选中的空间索引格网
	int m_PrevGrid;//上一次选中的格网
	CPoint m_pt;

public:
	CRect m_rtMapRange;//地图原始范围
	BOOL  m_IsLoadMap;//是否加载地图
	BOOL  m_IsLoadDem;//是否加载Dem

	CRect m_CurWinScope;//现在范围
	long  m_CurOper;//当前操作

	//记录距离量测时折线拐点坐标
	
	CPoint *PointXyz;
    //鼠标点记录（实现橡皮条效果）
	 int PushNumb;

	 
    CPoint mPointOrign,mPointOrign1,mPointOld;
   
	//拉框放大和漫游时矩形范围
    RECT m_rtZoom;
    //OnTimer用到的标记
	BOOL m_TimerTag;
    //记时器
    long ID_TIMER;

    //上次选中的层号
	int m_PrevLayer;
	//上次选中的层号
	long m_PrevObject;
	//当前选中的层号
	int m_LayerID;
	//当前中的目标号
   long  m_ObjectID;
   	CArray<CPoint,CPoint> CountArray;
	CPoint m_PointOrign;//用来记录源点与当前点的前一点
	CPoint m_PointOld;
	BOOL m_bCountDis;//用来标志是否处在计算长度和计算面积状态
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
