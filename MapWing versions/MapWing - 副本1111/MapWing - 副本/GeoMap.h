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

	CString m_strMapName;  //地图名称
    int m_LayerNum; //图层数
 	CRect m_MinRect;//最小外接矩形
  
public:
    CTypedPtrArray<CPtrArray,CGeoLayer*> m_parLayers; //各层
	CGrid  *m_GridLayer; //格网层

public:
	void SetLayerNum(int LayerNum);
    void SetRect(long Xmin,long Ymin,long Xmax,long Ymax);   //给最小外接矩形
	void SetMapName(CString MapName);//给地图赋名称
    void GetMinRect(CRect &mRect);  //得到外矩形
    void DrawMap(CDC *pDC);//绘图函数
    int GetLayerNum();  //得到层数
	void SetLayerVisible(CRect rect);  //设置各层的视野可见性

};

#endif // !defined(AFX_GEOMAP_H__F3ADE51D_ECD0_4185_AF5D_214C44BFD5E0__INCLUDED_)
