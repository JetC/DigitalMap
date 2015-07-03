// Grid.h: interface for the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRID_H__B3B9F1F2_E82F_405D_988E_6929DF341391__INCLUDED_)
#define AFX_GRID_H__B3B9F1F2_E82F_405D_988E_6929DF341391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Index.h"
#include "GeoMap.h"

class CGrid  
{
public:
	CGrid();
	virtual ~CGrid();
public:
	CIndex Index[256];  //256个索引块
    double m_LeftBottom_X; //左下角x坐标
	double m_LeftBottom_Y;//左下角y坐标
	double m_Grid; //索引块边长
	BOOL m_bIsVisible;  //格网可见性
public:
   
	void SetVisible(BOOL IsVisible);
	BOOL GetVisible()
	{
		return m_bIsVisible;
	} 
    //画出格网
	void DrawGrid(CDC *pDC);
    //构造格网
	void BuildIndex(CGeoMap *map);
	
    BOOL JudgeSelect(CPoint point,int *GridNum); //判断是否选中格网，若选中，值传入GridNum
   
	//设置网格是否突出显示
    void SetHot(int GridSelect,BOOL IsSelected)
    {
	   Index[GridSelect].m_IsSelected=IsSelected;
    }

};

#endif // !defined(AFX_GRID_H__B3B9F1F2_E82F_405D_988E_6929DF341391__INCLUDED_)
