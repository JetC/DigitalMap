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
	int m_LayerID;  //��id
	CString m_strLayerName;//ͼ������
	int m_CurObjNum; //��ǰӵ�е�Ŀ����
	BOOL m_bIsDisp;//ͼ����ʾ״̬
	int m_LayerType; //ͼ������ 1���� 3���� 5���� 7���ı�
	float m_ViewScale; //�����Ұ����
    BOOL m_bViewVisible; //�����Ұ�ɼ���
public:
    CTypedPtrArray<CPtrArray,CGeoObject*> m_parGeoObject;
public:	
	void SetLayerID(int id_only); //���ò�id
	void SetLayerType(int LayerType);  //���ò�����
    void SetLayerName(CString LayerName); //���ò���
    void SetVisible(BOOL IsVisible); //���ò�ɼ���
     
	CString GetLayerName(); //�õ�����
	int GetLayerID();//�õ�id
    BOOL GetVisible();//�õ���ǰ�ɼ���
	int GetLayerType(); //�õ�����

    void SetPointParameter(int PointType,long PointColor,long PointRadius);
    void SetLineParameter(int LineType,long LineColor,long LineWidth);
    void SetPolygonParameter(long BondColor,long FillColor);
    void SetTextParameter(long TextColor,CString TextFont);

    void GetPolygonParameter(long *BondColor,long *FillColor);
	void GetLineParameter(int *LineType,long *LineColor,long *LineWidth);
	void GetPointParameter(int *PointType,long *PointColor,long *PointRadius);
    void GetTextParameter(long *TextColor,CString *TextFont);
 
  
 	void AddObject(CGeoObject *Object);  //��ӿռ�Ŀ��
	void DrawLayer(CDC *pDC);  //�����ò�
	
	
	void SetView(float Scale)  //������Ұ��Χ
	{
		m_ViewScale=Scale;
	}
    float GetView()  //�õ���Ұ��Χ
	{
		return m_ViewScale;
	}

    void SetViewVisible(BOOL viewVisible)  //������Ұ�ɼ���
	{
		m_bViewVisible=viewVisible;
	}


};

#endif // !defined(AFX_GEOLAYER_H__CF012FE8_A6C3_449F_87FF_81F00D8C860D__INCLUDED_)
