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
	CIndex Index[256];  //256��������
    double m_LeftBottom_X; //���½�x����
	double m_LeftBottom_Y;//���½�y����
	double m_Grid; //������߳�
	BOOL m_bIsVisible;  //�����ɼ���
public:
   
	void SetVisible(BOOL IsVisible);
	BOOL GetVisible()
	{
		return m_bIsVisible;
	} 
    //��������
	void DrawGrid(CDC *pDC);
    //�������
	void BuildIndex(CGeoMap *map);
	
    BOOL JudgeSelect(CPoint point,int *GridNum); //�ж��Ƿ�ѡ�и�������ѡ�У�ֵ����GridNum
   
	//���������Ƿ�ͻ����ʾ
    void SetHot(int GridSelect,BOOL IsSelected)
    {
	   Index[GridSelect].m_IsSelected=IsSelected;
    }

};

#endif // !defined(AFX_GRID_H__B3B9F1F2_E82F_405D_988E_6929DF341391__INCLUDED_)
