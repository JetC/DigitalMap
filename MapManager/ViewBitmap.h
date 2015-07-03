// ViewBitmap.h: interface for the CViewBitmap class.
//
//////////////////////////////////////////////////////////////////////
#ifndef VIEWBITMAP_H
#define VIEWBITMAP_H
#if !defined(AFX_VIEWBITMAP_H__892CBDB0_B2F6_4022_9C8C_A49CD7A86B1A__INCLUDED_)
#define AFX_VIEWBITMAP_H__892CBDB0_B2F6_4022_9C8C_A49CD7A86B1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CViewBitmap : public CBitmap  
{
public:
	CViewBitmap();
	virtual ~CViewBitmap();
    void Capture(CRect &rect);

	CPalette * GetPalette(){return m_pPalette;}
    void SaveBitmapEx( CString sFile );
    HANDLE CreateDIB( int *pbmData =NULL);
private:
	CPalette * m_pPalette;

public:

	int m_width;
	int m_heighth;
    
};

#endif // !defined(AFX_VIEWBITMAP_H__892CBDB0_B2F6_4022_9C8C_A49CD7A86B1A__INCLUDED_)
#endif // !defined(AFX_VIEWBITMAP_H__892CBDB0_B2F6_4022_9C8C_A49CD7A86B1A__INCLUDED_)
