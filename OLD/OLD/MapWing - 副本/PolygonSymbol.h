// PolygonSymbol.h: interface for the CPolygonSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGONSYMBOL_H__A7AB2870_0503_44E3_A0B1_875510A2098A__INCLUDED_)
#define AFX_POLYGONSYMBOL_H__A7AB2870_0503_44E3_A0B1_875510A2098A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPolygonSymbol  
{
public:
	CPolygonSymbol(CPoint *points,long PtNum,long BondColor,long FillColor);
	virtual ~CPolygonSymbol();
private:
	long m_BondColor;  //�߽�ɫ��
	long m_FillColor;   //���ɫ��
	CPoint *m_points;    //����������
	long m_PtNum;     //����

public:
	void DrawSymbol(CDC *pDC);  //�������

};

#endif // !defined(AFX_POLYGONSYMBOL_H__A7AB2870_0503_44E3_A0B1_875510A2098A__INCLUDED_)
