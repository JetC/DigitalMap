// GeoLine.h: interface for the CGeoLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOLINE_H__FDB9CE53_2FEF_4576_A07F_DBCC3CB7F557__INCLUDED_)
#define AFX_GEOLINE_H__FDB9CE53_2FEF_4576_A07F_DBCC3CB7F557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"
#include "GeoObject.h"

class CGeoLine : public CGeoObject  
{
public:
	CGeoLine();
	virtual ~CGeoLine();
public:
	
    CTypedPtrArray<CPtrArray,CPoint*> m_parPoints;

private:
	int m_LineType;  //线对象的符号类型代号
	long m_LineColor;  //线对象的符号颜色
    long m_LineWidth;  //线符号宽度
	
public:
	void AddPoint(CPoint point);
	virtual void Draw(CDC *pDC);
	void SetSymbol(int LineType,long LineColor,long LineWidth);
	void GetSymbol(int &LineType,long &LineColor,long &LineWidth);
	virtual double GetDistance(CPoint MousePoint);
    CRect GetMaxRect();
   
};

#endif // !defined(AFX_GEOLINE_H__FDB9CE53_2FEF_4576_A07F_DBCC3CB7F557__INCLUDED_)
