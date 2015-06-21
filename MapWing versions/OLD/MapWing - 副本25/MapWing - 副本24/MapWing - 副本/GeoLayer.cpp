// GeoLayer.cpp: implementation of the CGeoLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "GeoLayer.h"
#include "GeoPoint.h"
#include "GeoLine.h"
#include "GeoPolygon.h"
#include "GeoAnno.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoLayer::CGeoLayer()
{
   m_CurObjNum=0;
   m_bIsDisp=true;
    m_bViewVisible=true;
   m_LayerID=-1;
   m_LayerType=-1;
   m_strLayerName="";
    m_ViewScale=0;
}

CGeoLayer::~CGeoLayer()
{

}

void CGeoLayer::AddObject(CGeoObject *Object)
{   
	m_CurObjNum++;

    m_parGeoObject.Add(Object);
}


void CGeoLayer::SetLayerName(CString LayerName)
{
   m_strLayerName=LayerName;

}
CString CGeoLayer::GetLayerName()
{
	return m_strLayerName;

}

void CGeoLayer::DrawLayer(CDC *pDC)
{
	if(m_bIsDisp==true&&m_bViewVisible==true)
	{
		for(int i=0;i<m_parGeoObject.GetSize();i++)
		{
		    m_parGeoObject.GetAt(i)->Draw(pDC);
		}
	}

}

void CGeoLayer::SetLayerID(int id_only)
{
	m_LayerID=id_only;
}

int CGeoLayer::GetLayerID()
{
	return m_LayerID;
}

void CGeoLayer::SetLayerType(int LayerType)
{
     m_LayerType=LayerType;
}

void CGeoLayer::SetVisible(BOOL IsVisible)
{
	m_bIsDisp=IsVisible;
}
	  
BOOL CGeoLayer::GetVisible()
{
	return m_bIsDisp;
}
int CGeoLayer::GetLayerType()
{
    return m_LayerType;
}

void CGeoLayer::SetPointParameter(int PointType,long PointColor,long PointRadius)
{
	for(int i=0;i<m_parGeoObject.GetSize();i++)
	{
	    ((CGeoPoint *)(m_parGeoObject.GetAt(i)))->SetSymbol(PointType,PointColor,PointRadius);
	}
}

void CGeoLayer::SetLineParameter(int LineType,long LineColor,long LineWidth)
{
	for(int i=0;i<m_parGeoObject.GetSize();i++)
	{
	     ((CGeoLine *)(m_parGeoObject.GetAt(i)))->SetSymbol(LineType,LineColor,LineWidth);
	}
 }

void CGeoLayer::SetPolygonParameter(long BondColor,long FillColor)
{
	for(int i=0;i<m_parGeoObject.GetSize();i++)
	{
	     ((CGeoPolygon *)(m_parGeoObject.GetAt(i)))->SetSymbol(BondColor,FillColor);
	}
}

void CGeoLayer::SetTextParameter(long TextColor,CString TextFont)
{
	for(int i=0;i<m_parGeoObject.GetSize();i++)
	{
	     ((CGeoAnno *)(m_parGeoObject.GetAt(i)))->SetSymbol(TextColor,TextFont);
	}
}



void CGeoLayer::GetPointParameter(int *PointType,long *PointColor,long *PointRadius)
{
	 ((CGeoPoint *)(m_parGeoObject.GetAt(0)))->GetSymbol(*PointType,*PointColor,*PointRadius);
}

void CGeoLayer::GetLineParameter(int *LineType,long *LineColor,long *LineWidth)
{

	 ((CGeoLine *)(m_parGeoObject.GetAt(0)))->GetSymbol(*LineType,*LineColor,*LineWidth);
}

void CGeoLayer::GetPolygonParameter(long *BondColor,long *FillColor)
{

    ((CGeoPolygon *)(m_parGeoObject.GetAt(0)))->GetSymbol(*BondColor,*FillColor);
}

void  CGeoLayer::GetTextParameter(long *TextColor,CString *TextFont)
{
   ((CGeoAnno *)(m_parGeoObject.GetAt(0)))->GetSymbol(*TextColor,*TextFont);
}