// PolygonSymbol.cpp: implementation of the CPolygonSymbol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "PolygonSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygonSymbol::CPolygonSymbol(CPoint *points,long PtNum,long BondColor,long FillColor)
{
	m_points=new CPoint[PtNum];
	for(int i=0;i<PtNum;i++)
	{
		m_points[i].x=points[i].x;
	    m_points[i].y=points[i].y;

	}
	m_PtNum=PtNum;
	m_BondColor=BondColor;
	m_FillColor=FillColor;

	

}

CPolygonSymbol::~CPolygonSymbol()
{
	delete []m_points;

}
void CPolygonSymbol::DrawSymbol(CDC *pDC)
{
	CPen pen,*OldPen;
    pen.CreatePen(PS_SOLID,1,m_BondColor);

	OldPen=pDC->SelectObject(&pen);
	//CBrush brush(HS_BDIAGONAL,m_FillColor),*OldBrush;
	CBrush brush,*OldBrush;
    brush.CreateSolidBrush(m_FillColor);
	OldBrush=pDC->SelectObject(&brush);
    
	pDC->Polygon(m_points,m_PtNum);
	pDC->SelectObject(OldBrush);
    pDC->SelectObject(OldPen);
}
