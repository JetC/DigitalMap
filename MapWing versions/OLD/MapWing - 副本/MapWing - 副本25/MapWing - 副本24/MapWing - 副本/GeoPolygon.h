// GeoPolygon.h: interface for the CGeoPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOPOLYGON_H__672EA1FE_6FE3_40D3_9DBD_B095D72AFB6A__INCLUDED_)
#define AFX_GEOPOLYGON_H__672EA1FE_6FE3_40D3_9DBD_B095D72AFB6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"
#include "GeoObject.h"
class CGeoPolygon : public CGeoObject  
{
public:
	CGeoPolygon();
	virtual ~CGeoPolygon();
public:
	CTypedPtrArray<CPtrArray,CPoint*> m_parPoints;
	
public:
	void SetSymbol(long BondColor,long FillColor);
   void GetSymbol(long &BondColor,long &FillColor);

	void AddPoint(CPoint point);
	virtual void Draw(CDC *pDC);
	long m_BondColor;  //�����ı߽���ɫ

	long m_FillColor;  //�����������ɫ
	virtual double GetDistance(CPoint MousePoint)
	{
		return LONG_MAX;
	}
 virtual CRect GetMaxRect();
};

#endif // !defined(AFX_GEOPOLYGON_H__672EA1FE_6FE3_40D3_9DBD_B095D72AFB6A__INCLUDED_)
