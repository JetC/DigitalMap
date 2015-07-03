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
	CString m_Content;   //ע������
	CPoint m_Position;   //ע�Ƕ�λ��

	long m_TextHeight;   //ע�Ǹ�
	long m_TextWidth;    //ע�ǿ�
	CPoint m_EndPosition;  //ע��ĩ��λ��
    long m_TextColor;    //ע����ɫ
	CString m_TextFont;   //ע������


public:
	//����ע����ز���
	void SetTextContent(CString Content);
	
	void SetTextHeight(long TextHeight);
	void SetTextPosition(long x,long y);
	void SetTextEndPosition(long x,long y);
	void SetTextWidth(long TextWidth);
    

	//�õ�ע����ز���
	void GetTextContent(CString &Content);
	long GetTextHeight();
	void GetTextPosition(long *x,long *y);
	void GetTextEndPosition(long *x,long *y);

    //����ע�ǿ�
	void CaculateTextWidth();

	virtual void Draw(CDC *pDC);
	virtual double GetDistance(CPoint MousePoint)
	{
		return 40000000;
	}
    //����ע����ɫ����
    void SetSymbol(long TextColor,CString TextFont)
    {
	
	  m_TextColor=TextColor;
	 
	  m_TextFont=TextFont;
   }
	//�õ�ע����ɫ����
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
