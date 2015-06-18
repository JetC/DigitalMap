// GeoMap.h: interface for the CGeoMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMAP_H__F3ADE51D_ECD0_4185_AF5D_214C44BFD5E0__INCLUDED_)
#define AFX_GEOMAP_H__F3ADE51D_ECD0_4185_AF5D_214C44BFD5E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxtempl.h"
#include "GeoLayer.h"


class CGrid;
class CGeoMap  
{
public:
	CGeoMap();
	virtual ~CGeoMap();  

	CString m_strMapName;  //��ͼ����
    int m_LayerNum; //ͼ����
 	CRect m_MinRect;//��С��Ӿ���
  
public:
    CTypedPtrArray<CPtrArray,CGeoLayer*> m_parLayers; //����
	CGrid  *m_GridLayer; //������

public:
	void SetLayerNum(int LayerNum);
    void SetRect(long Xmin,long Ymin,long Xmax,long Ymax);   //����С��Ӿ���
	void SetMapName(CString MapName);//����ͼ������
    void GetMinRect(CRect &mRect);  //�õ������
    void DrawMap(CDC *pDC);//��ͼ����
    int GetLayerNum();  //�õ�����
	void SetLayerVisible(CRect rect);  //���ø������Ұ�ɼ���

};

#endif // !defined(AFX_GEOMAP_H__F3ADE51D_ECD0_4185_AF5D_214C44BFD5E0__INCLUDED_)
