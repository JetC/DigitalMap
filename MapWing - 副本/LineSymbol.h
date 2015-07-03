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
	int m_LineSymbolType;   //线符号类型
	int m_LineSymbolWidth;   //线符号宽度
	long  m_LineSymbolColor;   //线符号颜色
	CPoint *pt;           //假定数组pt，有n个元素
	int m_ptnum;          //结点数
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
