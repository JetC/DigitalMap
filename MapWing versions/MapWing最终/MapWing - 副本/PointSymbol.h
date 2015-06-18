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
	CPoint m_Location;  //��λ������
    int m_PointType;    //������
	long m_PointColor;  //����ɫ
	double m_PointRadius;  //��뾶
public:
    CPointSymbol();
	virtual ~CPointSymbol();
    CPointSymbol(CPoint Location,int Type,long Color,double Radius);
	void GetValue(CPoint *Location,int *Type,long *Color,double *Radius);
	void DrawSymbol(CDC *pDC);  //������״����

};

#endif // !defined(AFX_POINTSYMBOL1_H__1B2254D3_A15B_4E62_82C7_2FFE8E7CDBDE__INCLUDED_)
