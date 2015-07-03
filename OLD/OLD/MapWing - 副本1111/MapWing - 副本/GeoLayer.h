// GeoLayer.h: interface for the CGeoLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOLAYER_H__CF012FE8_A6C3_449F_87FF_81F00D8C860D__INCLUDED_)
#define AFX_GEOLAYER_H__CF012FE8_A6C3_449F_87FF_81F00D8C860D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxtempl.h"
#include "GeoObject.h"

class CGeoLayer  
{
public:
	CGeoLayer();
	virtual ~CGeoLayer();
private:
	int m_LayerID;  //层id
	CString m_strLayerName;//图层名称
	int m_CurObjNum; //当前拥有的目标数
	BOOL m_bIsDisp;//图层显示状态
	int m_LayerType; //图层类型 1：点 3：线 5：面 7：文本
	float m_ViewScale; //层的视野比例
    BOOL m_bViewVisible; //层的视野可见性
public:
    CTypedPtrArray<CPtrArray,CGeoObject*> m_parGeoObject;
public:	
	void SetLayerID(int id_only); //设置层id
	void SetLayerType(int LayerType);  //设置层类型
    void SetLayerName(CString LayerName); //设置层名
    void SetVisible(BOOL IsVisible); //设置层可见性
     
	CString GetLayerName(); //得到层名
	int GetLayerID();//得到id
    BOOL GetVisible();//得到当前可见性
	int GetLayerType(); //得到类型

    void SetPointParameter(int PointType,long PointColor,long PointRadius);
    void SetLineParameter(int LineType,long LineColor,long LineWidth);
    void SetPolygonParameter(long BondColor,long FillColor);
    void SetTextParameter(long TextColor,CString TextFont);

    void GetPolygonParameter(long *BondColor,long *FillColor);
	void GetLineParameter(int *LineType,long *LineColor,long *LineWidth);
	void GetPointParameter(int *PointType,long *PointColor,long *PointRadius);
    void GetTextParameter(long *TextColor,CString *TextFont);
 
  
 	void AddObject(CGeoObject *Object);  //添加空间目标
	void DrawLayer(CDC *pDC);  //画出该层
	
	
	void SetView(float Scale)  //设置视野范围
	{
		m_ViewScale=Scale;
	}
    float GetView()  //得到视野范围
	{
		return m_ViewScale;
	}

    void SetViewVisible(BOOL viewVisible)  //设置视野可见性
	{
		m_bViewVisible=viewVisible;
	}


};

#endif // !defined(AFX_GEOLAYER_H__CF012FE8_A6C3_449F_87FF_81F00D8C860D__INCLUDED_)
