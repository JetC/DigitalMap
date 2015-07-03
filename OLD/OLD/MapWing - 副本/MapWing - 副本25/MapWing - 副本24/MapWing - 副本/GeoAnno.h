// GeoAnno.h: interface for the CGeoAnno class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOANNO_H__C3933326_299F_4BDC_8BEE_2D870E8ECA50__INCLUDED_)
#define AFX_GEOANNO_H__C3933326_299F_4BDC_8BEE_2D870E8ECA50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeoObject.h"

class CGeoAnno : public CGeoObject  
{
public:
	CGeoAnno();
	virtual ~CGeoAnno();
private:
	CString m_Content;   //注记内容
	CPoint m_Position;   //注记定位点

	long m_TextHeight;   //注记高
	long m_TextWidth;    //注记宽
	CPoint m_EndPosition;  //注记末定位点
    long m_TextColor;    //注记颜色
	CString m_TextFont;   //注记字体


public:
	//设置注记相关参数
	void SetTextContent(CString Content);
	
	void SetTextHeight(long TextHeight);
	void SetTextPosition(long x,long y);
	void SetTextEndPosition(long x,long y);
	void SetTextWidth(long TextWidth);
    

	//得到注记相关参数
	void GetTextContent(CString &Content);
	long GetTextHeight();
	void GetTextPosition(long *x,long *y);
	void GetTextEndPosition(long *x,long *y);

    //计算注记宽
	void CaculateTextWidth();

	virtual void Draw(CDC *pDC);
	virtual double GetDistance(CPoint MousePoint)
	{
		return 40000000;
	}
    //设置注记颜色字体
    void SetSymbol(long TextColor,CString TextFont)
    {
	
	  m_TextColor=TextColor;
	 
	  m_TextFont=TextFont;
   }
	//得到注记颜色字体
   void GetSymbol(long &TextColor,CString &TextFont)
   {
	   TextColor=m_TextColor;
	   TextFont=m_TextFont;
   }

    virtual CRect GetMaxRect()
	{
		CRect rect;
		return rect;
	}
  
};

#endif // !defined(AFX_GEOANNO_H__C3933326_299F_4BDC_8BEE_2D870E8ECA50__INCLUDED_)
