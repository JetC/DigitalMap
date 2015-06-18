// GeoMap.cpp: implementation of the CGeoMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "GeoMap.h"
#include "Grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoMap::CGeoMap()
{
	m_LayerNum=0;
	m_strMapName="";
	m_GridLayer=new CGrid;


}

CGeoMap::~CGeoMap()
{
	delete m_GridLayer;

}
void CGeoMap::SetLayerNum(int LayerNum)
{
	m_LayerNum=LayerNum;
}

void CGeoMap::SetRect(long Xmin,long Ymin,long Xmax,long Ymax)
{
	m_MinRect.left=Xmin;
	m_MinRect.bottom=Ymin;
	m_MinRect.right=Xmax;
	m_MinRect.top=Ymax;//给最小外接矩形
}
void CGeoMap::SetMapName(CString MapName)//给地图赋名称
{
	m_strMapName=MapName;
} 
void CGeoMap::GetMinRect(CRect &mRect)
{
	mRect.left=m_MinRect.left;
    mRect.bottom=m_MinRect.bottom;
    mRect.right=m_MinRect.right;
    mRect.top=m_MinRect.top;
}            
void CGeoMap::DrawMap(CDC *pDC)
{
   
	for(int i=0;i<m_parLayers.GetSize();i++)
	{
      m_parLayers.GetAt(i)->DrawLayer(pDC);
    } 
 
     m_GridLayer->DrawGrid(pDC);

}

int CGeoMap::GetLayerNum()
{
	return m_LayerNum;
}

void CGeoMap::SetLayerVisible(CRect rect)
{ 
	double width=(double)rect.Width()/(double)1000;
  double height=(double)rect.Height()/(double)1000;

   double w=(double)m_MinRect.Width()/(double)1000;
   double h=(double)m_MinRect.Height()/(double)1000;
   double bl=(w*h)/(width*height);//(;//(double)(rect.Width()*rect.Height())/(double)(m_MinRect.Width()*m_MinRect.Height());
	for(int i=0;i<m_parLayers.GetSize();i++)
	{
		//if((double)(rect.Width()*rect.Height())/(double)(m_MinRect.Width()*m_MinRect.Height())<m_parLayers.GetAt(i)->GetView())
		if(bl<m_parLayers.GetAt(i)->GetView())
		{
			m_parLayers.GetAt(i)->SetViewVisible(false);
		}
		else
		{
			
        	m_parLayers.GetAt(i)->SetViewVisible(true);
		
		}
	}
}

	


