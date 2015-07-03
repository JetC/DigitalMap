// PointSymbol.cpp: implementation of the CPointSymbol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "PointSymbol.h"
#include "math.h"
#define PI 3.1415926

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CPointSymbol::CPointSymbol()
{
    m_Location=CPoint(0,0);
    m_PointType=0;
    m_PointColor=0;
    m_PointRadius=0;
}

CPointSymbol::~CPointSymbol()
{

}
CPointSymbol::CPointSymbol(CPoint Location,int Type,long Color,double Radius)
{
	m_Location=Location;
    m_PointType=Type;
    m_PointColor=Color;
    m_PointRadius=Radius;
}
void CPointSymbol::GetValue(CPoint *Location,int *Type,long *Color,double *Radius)
{
	Location=&m_Location;
    Type=&m_PointType;
    Color=&m_PointColor;
    Radius=&m_PointRadius;
}
void CPointSymbol::DrawSymbol(CDC *pDC)
{ 

    CPen pen,*OldPen;
    pen.CreatePen(PS_SOLID,1,m_PointColor);
	CBrush brush,*oldbrush;
    brush.CreateSolidBrush(m_PointColor);
    OldPen=pDC->SelectObject(&pen);
	oldbrush=pDC->SelectObject(&brush);
	switch(m_PointType)
	{
    case 1:
		{
	       
		    pDC->Ellipse(m_Location.x-m_PointRadius,m_Location.y-m_PointRadius,m_Location.x+m_PointRadius,m_Location.y+m_PointRadius);
            break;
        }   //ÅäÔ²ÐÎ·ûºÅ
	case 2:
		{ 
			CPoint *pt;
			pt=new CPoint[4];
     	    pt[0]=CPoint(m_Location.x,m_Location.y+m_PointRadius);
            pt[1]=CPoint(m_Location.x-m_PointRadius*sin(PI/3.0),m_Location.y-m_PointRadius*cos(PI/3.0));
            pt[2]=CPoint(m_Location.x+m_PointRadius*sin(PI/3.0),m_Location.y-m_PointRadius*cos(PI/3.0));
            pt[3]=CPoint(m_Location.x,m_Location.y+m_PointRadius);
            pDC->Polygon(pt,4);
            break;
		}  //ÅäÈý½ÇÐÎ·ûºÅ
	case 3:
		{   
			int i=0;
		    double r=0,Radius=0;
			CPoint pt[11];
			r=m_PointRadius*sin(PI/10.0)/sin(7.0*PI/10.0);
			for(i=0;i<10;i++)
            {   Radius=((i%2==0)?m_PointRadius:r);
			    pt[i].x=m_Location.x-Radius*sin(i*36.0*PI/180.0);
				pt[i].y=m_Location.y+Radius*cos(i*36.0*PI/180.0);
			}
			pt[10]=pt[0];
		    pDC->Polygon(pt,11);
	        break;
        }   //ÅäÎå½ÇÐÇ·ûºÅ
    default:break;
	}

    pDC->SelectObject(oldbrush);
	pDC->SelectObject(pen);

}
