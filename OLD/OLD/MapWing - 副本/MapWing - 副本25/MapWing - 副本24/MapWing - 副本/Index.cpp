// Index.cpp: implementation of the CIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapManager.h"
#include "Index.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndex::CIndex()
{
	m_IsSelected=false;
	LayerID=new int[200];
	ObjectID=new long[200];
	m_RecordNum=0;

}

CIndex::~CIndex()
{
	delete []LayerID;
	delete []ObjectID;

}
void CIndex::DrawRect(CDC *pDC)
{
	CPen pen,*pOldPen;
	pen.CreatePen(0,0,RGB(210,210,210));
	pOldPen=pDC->SelectObject(&pen);

	if(m_IsSelected==false)
	{ 
		pDC->SelectStockObject(NULL_BRUSH);
		CPoint pt[5];
		
		pt[0]=CPoint(m_IndexRect.left,m_IndexRect.top);
        pt[1]=CPoint(m_IndexRect.left,m_IndexRect.bottom);
        pt[2]=CPoint(m_IndexRect.right,m_IndexRect.bottom);
        pt[3]=CPoint(m_IndexRect.right,m_IndexRect.top);
		pt[4]=pt[0];
        pDC->Polyline(pt,5);


	}
	else
	{
		CBrush brush,*pOldBrush;
		brush.CreateSolidBrush(RGB(0,0,255));
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Rectangle(&m_IndexRect);
		pDC->SelectObject(pOldBrush);
	}
	pDC->SelectObject(pOldPen);
}

