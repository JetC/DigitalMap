// GeoPolygon.cpp: implementation of the CGeoPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapManager.h"
#include "GeoPolygon.h"
#include "PolygonSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoPolygon::CGeoPolygon()
{

}

CGeoPolygon::~CGeoPolygon()
{

}
void CGeoPolygon::AddPoint(CPoint point)
{

	CPoint *tempPoint=NULL;
	tempPoint=new CPoint(point);
	m_parPoints.Add(tempPoint);

}

void CGeoPolygon::Draw(CDC *pDC)
{
	CPoint *points;
	int PtNum;
	PtNum=m_parPoints.GetSize();
	points=new CPoint[PtNum];
    for(int i=0;i<PtNum;i++)
	{
		points[i].x=m_parPoints.GetAt(i)->x ;
        points[i].y=m_parPoints.GetAt(i)->y ;
	}
	CPolygonSymbol PolySymbol(points,PtNum,m_BondColor,m_FillColor);
    
	PolySymbol.DrawSymbol(pDC);
	delete []points;
	

}	
    

void CGeoPolygon::SetSymbol(long BondColor,long FillColor)
{
	m_BondColor=BondColor;
	m_FillColor=FillColor;

}

void CGeoPolygon::GetSymbol(long &BondColor,long &FillColor)
{
	BondColor=m_BondColor;
	FillColor=m_FillColor;

}


CRect CGeoPolygon::GetMaxRect()
{
	CRect result;
	memset(&result,0x00,sizeof(RECT));

	result.left = LONG_MAX;
	result.right = LONG_MIN;
	result.bottom = LONG_MAX;
	result.top = LONG_MIN;	

	for(int i=0;i<m_parPoints.GetSize();i++)
	{
		if( m_parPoints.GetAt(i)->x <= result.left )
		{
			result.left = m_parPoints.GetAt(i)->x;
		}

		if( m_parPoints.GetAt(i)->x >= result.right )
		{
			result.right = m_parPoints.GetAt(i)->x;
		}

		if( m_parPoints.GetAt(i)->y <= result.bottom )
		{
			result.bottom = m_parPoints.GetAt(i)->y;
		}
		
		if( m_parPoints.GetAt(i)->y >= result.top )
		{
			result.top = m_parPoints.GetAt(i)->y;
		}

	}
	
	return result;
}
