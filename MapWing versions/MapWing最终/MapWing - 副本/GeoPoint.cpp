// GeoPoint.cpp: implementation of the CGeoPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "GeoPoint.h"
#include "PointSymbol.h"
#include "MapWingView.h"
#include "MainFrm.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoPoint::CGeoPoint()
{

}

CGeoPoint::~CGeoPoint()
{

}
void CGeoPoint::SetPoint(long x,long y)
{
	location.x=x;
	location.y=y;
}

void CGeoPoint::GetPoint(long &x,long &y)
{
	x=location.x;
	y=location.y;
}

void CGeoPoint::Draw(CDC *pDC)
{
	if(m_bBlink==false)
	{
		CPointSymbol symbol(location,m_PointType,m_PointColor,m_PointRadius);
     	symbol.DrawSymbol(pDC);
	}
	else
	{
		COLORREF color;
		color=m_PointColor;
	    long newColor=RGB(255-GetRValue(color),255-GetGValue(color),255-GetBValue(color));
		CPointSymbol symbol(location,m_PointType,newColor,1.5*m_PointRadius);
     	symbol.DrawSymbol(pDC);
	}


}

void CGeoPoint::SetSymbol(int PointType,long PointColor,long PointRadius)
{
	m_PointType=PointType;
	m_PointColor=PointColor;
	m_PointRadius=PointRadius;
}
void CGeoPoint::GetSymbol(int &PointType,long &PointColor,long &PointRadius)
{
	PointType=m_PointType;
	PointColor=m_PointColor;
	PointRadius=m_PointRadius;
}


double CGeoPoint::GetDistance(CPoint MousePoint)
{
	double distance;
	distance=sqrt(pow((float)(MousePoint.x-location.x),2)+pow((float)(MousePoint.y-location.y),2));
    return distance;

}