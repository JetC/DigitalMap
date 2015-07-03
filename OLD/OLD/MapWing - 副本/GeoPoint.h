// GeoPoint.h: interface for the CGeoPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOPOINT_H__66A9626B_355C_44FE_8C9D_2C8287974A5E__INCLUDED_)
#define AFX_GEOPOINT_H__66A9626B_355C_44FE_8C9D_2C8287974A5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeoObject.h"

class CGeoPoint : public CGeoObject  
{
public:
	CGeoPoint();
	virtual ~CGeoPoint();
	
private:
	CPoint location; //���������

	int  m_PointType;  //�����ķ������ʹ���
	long  m_PointColor;  //�����ķ�����ɫ
	int m_PointRadius; //�����ķ��Ű뾶(����Ļ���ص�λ��)
public: 
	void SetPoint(long x,long y);
	void GetPoint(long &x,long &y);

	void SetSymbol(int PointType,long PointColor,long PointRadius); //���õ�״����
	void GetSymbol(int &PointType,long &PointColor,long &PointRadius);
   
	virtual void Draw(CDC *pDC);
    virtual double GetDistance(CPoint MousePoint);
    virtual CRect GetMaxRect()
	{
		RECT rect;
		rect.left=(long)(location.x-1.5*m_PointRadius);
		rect.right=(long)(location.x+1.5*m_PointRadius);
		rect.top=(long)(location.y+1.5*m_PointRadius);
		rect.bottom=(long)(location.y-1.5*m_PointRadius);
		return rect;

	};

};

#endif // !defined(AFX_GEOPOINT_H__66A9626B_355C_44FE_8C9D_2C8287974A5E__INCLUDED_)
