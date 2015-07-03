// PointSymbol.h: interface for the CPointSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTSYMBOL1_H__1B2254D3_A15B_4E62_82C7_2FFE8E7CDBDE__INCLUDED_)
#define AFX_POINTSYMBOL1_H__1B2254D3_A15B_4E62_82C7_2FFE8E7CDBDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPointSymbol  
{
private:
	CPoint m_Location;  //定位点坐标
    int m_PointType;    //点类型
	long m_PointColor;  //点颜色
	double m_PointRadius;  //点半径
public:
    CPointSymbol();
	virtual ~CPointSymbol();
    CPointSymbol(CPoint Location,int Type,long Color,double Radius);
	void GetValue(CPoint *Location,int *Type,long *Color,double *Radius);
	void DrawSymbol(CDC *pDC);  //画出点状符号

};

#endif // !defined(AFX_POINTSYMBOL1_H__1B2254D3_A15B_4E62_82C7_2FFE8E7CDBDE__INCLUDED_)
