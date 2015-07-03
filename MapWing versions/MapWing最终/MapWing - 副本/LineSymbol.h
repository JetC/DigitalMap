// LineSymbol.h: interface for the CLineSymbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINESYMBOL_H__8393B236_8936_4C0E_843E_13698E47FA06__INCLUDED_)
#define AFX_LINESYMBOL_H__8393B236_8936_4C0E_843E_13698E47FA06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLineSymbol  
{

public:
	int m_LineSymbolType;   //�߷�������
	int m_LineSymbolWidth;   //�߷��ſ��
	long  m_LineSymbolColor;   //�߷�����ɫ
	CPoint *pt;           //�ٶ�����pt����n��Ԫ��
	int m_ptnum;          //�����
public:
	CLineSymbol();
	CLineSymbol(CPoint *points,long PtNum,int LineSymbolType, int LineSymbolWidth,long LineSymbolColor);
	virtual ~CLineSymbol();
public:
	void DrawSymbol(CDC *pDC);
	void DrawSolidLine(CDC *pDC);
	void DrawVirtualLine(CDC *pDC);
	void DrawDotLine(CDC *pDC);
	void DrawDoubleLine(CDC *pDC);
    void DrawRailwayLine(CDC *pDC);
};

#endif // !defined(AFX_LINESYMBOL_H__8393B236_8936_4C0E_843E_13698E47FA06__INCLUDED_)
