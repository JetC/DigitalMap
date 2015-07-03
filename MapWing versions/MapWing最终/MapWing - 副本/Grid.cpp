// Grid.cpp: implementation of the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "Grid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGrid::CGrid()
{
   m_bIsVisible=false;


}

CGrid::~CGrid()
{

}

void CGrid::BuildIndex(CGeoMap *map)
{
    CRect mRect;
	map->GetMinRect(mRect); 
    double total;
	if((mRect.Width())>=(-mRect.Height()))
	{
		total=mRect.Width();
		m_Grid=total/16;
        m_LeftBottom_Y=mRect.bottom-(mRect.Width()-(-mRect.Height()))/2;
		m_LeftBottom_X=mRect.left;
	}
   if((mRect.Width())<(-mRect.Height()))
	{
		total=-mRect.Height();
		m_Grid=total/16;
        m_LeftBottom_X=mRect.left-((-mRect.Height())-mRect.Width())/2;
		m_LeftBottom_Y=mRect.bottom;
	}
   int num=0;
   for(int i=0;i<16;i++)
	 for(int j=0;j<16;j++)
	  {
		   Index[num].m_IndexRect.left=m_LeftBottom_X+m_Grid*j;
		   Index[num].m_IndexRect.right=m_LeftBottom_X+m_Grid*(j+1);
	       Index[num].m_IndexRect.bottom=m_LeftBottom_Y+m_Grid*i;
		   Index[num].m_IndexRect.top=m_LeftBottom_Y+m_Grid*(i+1);
           int n=0;

		   int LayerNum=map->m_parLayers.GetSize();
		   for(int k=0;k<LayerNum;k++)
		   {
			   int ObjectNum=map->m_parLayers.GetAt(k)->m_parGeoObject.GetSize();
			   for(int m=0;m<ObjectNum;m++)
			   {
				   CRect ObjectRect=map->m_parLayers.GetAt(k)->m_parGeoObject.GetAt(m)->GetMaxRect();
				   if(ObjectRect.right<Index[num].m_IndexRect.left||ObjectRect.left>Index[num].m_IndexRect.right||ObjectRect.bottom >Index[num].m_IndexRect.top||ObjectRect.top<Index[num].m_IndexRect.bottom);
				 
				   else
				   {
					   //int sd=0;
				     Index[num].LayerID[n]=k;
				     Index[num].ObjectID[n++]=m;
					 
				   }
			   }   
		   }
		   Index[num].m_RecordNum=n;
		   num++;
		   
	  }


}

void CGrid::DrawGrid(CDC *pDC)
{
	if(m_bIsVisible)
	{
     	for(int i=0;i<256;i++)
		{
		  Index[i].DrawRect(pDC);
		}
	}



}




BOOL CGrid::JudgeSelect(CPoint point,int *GridNum)
{
	for(int i=0;i<256;i++)
	{
		if(point.x>Index[i].m_IndexRect.left&&point.x<Index[i].m_IndexRect.right &&point.y>Index[i].m_IndexRect.bottom&&point.y<Index[i].m_IndexRect.top)
		{
			*GridNum=i;
			return TRUE;
		}
	}
}

void CGrid::SetVisible(BOOL IsVisible)
{
	m_bIsVisible=IsVisible;

}



