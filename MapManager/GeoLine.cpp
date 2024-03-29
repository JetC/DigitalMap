// GeoLine.cpp: implementation of the CGeoLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapManager.h"
#include "GeoLine.h"
#include "LineSymbol.h"
#include "MapManagerView.h"
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

CGeoLine::CGeoLine()
{
   
}

CGeoLine::~CGeoLine()
{

}
void CGeoLine::AddPoint(CPoint point)
{

	CPoint *tempPoint=NULL;
	tempPoint=new CPoint(point);
	m_parPoints.Add(tempPoint);

}

void CGeoLine::Draw(CDC *pDC)
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
	 
	if(m_LineWidth<100)
	{
	CLineSymbol LineSymbol(points,PtNum,1,m_LineWidth,m_LineColor);
	LineSymbol.DrawSymbol(pDC);
	delete []points;
	}
	else
	{
	  
	CLineSymbol LineSymbol(points,PtNum,m_LineType,m_LineWidth,m_LineColor);
	LineSymbol.DrawSymbol(pDC);
	delete []points;
	}
	


}	
  
void CGeoLine::SetSymbol(int LineType,long LineColor,long LineWidth)
{
	m_LineType=LineType;
	m_LineColor=LineColor;
	m_LineWidth=LineWidth;
}

void CGeoLine::GetSymbol(int &LineType,long &LineColor,long &LineWidth)
{
	LineType=m_LineType;
	LineColor=m_LineColor;
	LineWidth=m_LineWidth;
}


CRect CGeoLine::GetMaxRect()
{
	RECT result;
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


double CGeoLine::GetDistance(CPoint MousePoint)
{
   
	  return LONG_MAX;
	
				

}


