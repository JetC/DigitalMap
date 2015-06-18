// GeoAnno.cpp: implementation of the CGeoAnno class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "GeoAnno.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoAnno::CGeoAnno()
{
   m_TextFont="隶书";
}

CGeoAnno::~CGeoAnno()
{

}
void CGeoAnno::Draw(CDC *pDC)
{

	CFont font;//创建字模
	CaculateTextWidth();
	
		
    font.CreateFont(m_TextHeight,m_TextWidth,0,0,100,0,0,0,DEFAULT_CHARSET,0,0,2,DEFAULT_PITCH,m_TextFont);
	
	CFont *pOldFont=pDC->SelectObject(&font);
    pDC->SetBkMode(TRANSPARENT);  //设背景透明
	pDC->SetTextColor(m_TextColor);

	pDC->TextOut(m_Position.x,m_Position.y,m_Content);
    pDC->SelectObject(pOldFont);

}
void CGeoAnno::SetTextContent(CString Content)
{
	m_Content=Content;
}
void CGeoAnno::SetTextHeight(long TextHeight)
{
	m_TextHeight=TextHeight;
}

void CGeoAnno::SetTextPosition(long x,long y)
{
	m_Position.x=x;
	m_Position.y=y;
}

void CGeoAnno::SetTextEndPosition(long x,long y)
{
	m_EndPosition.x=x;
	m_EndPosition.y=y;
}

void CGeoAnno::SetTextWidth(long TextWidth)
{
	m_TextWidth=TextWidth;
}
void CGeoAnno::CaculateTextWidth()
{
	long width=m_EndPosition.x-m_Position.x;

    int length=m_Content.GetLength();
	
	SetTextWidth(width/length);
}

	void CGeoAnno::GetTextContent(CString &Content)
	{
		Content=m_Content;
	}

	long CGeoAnno::GetTextHeight()
	{
		return m_TextHeight;
	}
	void CGeoAnno::GetTextPosition(long *x,long *y)
	{
		*x=m_Position.x;
		*y=m_Position.y;
	}

	void CGeoAnno::GetTextEndPosition(long *x,long *y)
	{
		*x=m_EndPosition.x;
		*y=m_EndPosition.y;
	}


