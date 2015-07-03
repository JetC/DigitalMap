// ViewBitmap.cpp: implementation of the CViewBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapWing.h"
#include "MapWingView.h"
#include "ViewBitmap.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//IMPLEMENT_DYNAMIC(CViewBitmap,CBitmap)
CViewBitmap::CViewBitmap()
{m_pPalette=NULL;

}

CViewBitmap::~CViewBitmap()
{
  if(m_pPalette)
  { 
	  delete m_pPalette;
  }
}
void CViewBitmap::Capture(CRect &rect)
{ 
 if(m_pPalette)
 { DeleteObject();
   delete m_pPalette;
 }
 m_width=rect.Width();
 m_heighth=rect.Height();
 double wid=rect.left/1024;
 double hei=rect.top/768;

 CDC dcscreen;
 dcscreen.CreateDC("DISPLAY",NULL,NULL,NULL);
 CDC dcMem;
 dcMem.CreateCompatibleDC( &dcscreen );
 CreateCompatibleBitmap( &dcscreen, m_width, m_heighth );
 dcMem.SelectObject( this );

 dcMem.BitBlt(0,0,m_width, m_heighth,&dcscreen,rect.left,rect.top,SRCCOPY);
// create an empty logical palette that¡¯s big enough to hold all the colors
 int nColors = ( 1 << ( dcscreen.GetDeviceCaps( BITSPIXEL ) *dcscreen.GetDeviceCaps( PLANES ) ) );
 LOGPALETTE *pLogpal=(LOGPALETTE*) new BYTE[sizeof(LOGPALETTE)+(nColors * sizeof(PALETTEENTRY))];
 pLogpal -> palVersion = 0x300;
 pLogpal -> palNumEntries = nColors;
// load this empty palette with the system palette's colors
 GetSystemPaletteEntries( dcscreen.m_hDC, 0, nColors,(LPPALETTEENTRY)(pLogpal->palPalEntry));
 m_pPalette = new CPalette;
 m_pPalette -> CreatePalette( pLogpal );
 delete []pLogpal;
 dcMem.DeleteDC();
 dcscreen.DeleteDC();
}
void CViewBitmap::SaveBitmapEx( CString sFile )
{
// create a DIB bitmap
 int bmData;
 HANDLE hDIB = CreateDIB( &bmData );
// get a memory pointer to it
 LPBYTE lpBitmap = (LPBYTE)::GlobalLock(hDIB);
 int bmSize = ::GlobalSize( hDIB );
 // create file
 CFile file;
 file.Open( sFile, CFile::modeCreate|CFile::modeWrite );
 // write the bitmap header
 BITMAPFILEHEADER bmfh;
 bmfh.bfType ='MB'; // (actually 'BM' for bitmap)
 bmfh.bfSize = sizeof(BITMAPFILEHEADER) + bmSize;
 bmfh.bfReserved1 = 0;
 bmfh.bfReserved2 = 0;
 bmfh.bfOffBits =bmData;
 file.Write( &bmfh,sizeof( BITMAPFILEHEADER ) );
 // write the bitmap body
 file.Write(lpBitmap,bmSize );
// cleanup
 file.Close();
 ::GlobalUnlock( hDIB );
 ::GlobalFree( hDIB);
}
HANDLE CViewBitmap::CreateDIB(int *pbmData)
{
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
// create DIB header from our BITMAP header
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
 BITMAPINFOHEADER bi;
 memset( &bi, 0, sizeof( bi ) );
 bi.biSize = sizeof( BITMAPINFOHEADER );
 bi.biPlanes = 1;
 bi.biCompression = BI_RGB;
// get and store dimensions of bitmap
 BITMAP bm;
 GetObject( sizeof( bm ),( LPSTR )&bm );
 bi.biWidth = bm.bmWidth ;
 bi.biHeight = bm.bmHeight;
// get number of bits required per pixel
 int bits = bm.bmPlanes * bm.bmBitsPixel;
 if ( bits <= 1 )
 bi.biBitCount = 1;
 else if ( bits <= 4 )
 bi.biBitCount = 4;
 else if ( bits <= 8 )
 bi.biBitCount = 8;
 else
 bi.biBitCount = 24;
// calculate color table size
 int biColorSize = 0;
 if ( bi.biBitCount!=24)
	 biColorSize = (1 << bi.biBitCount );
 biColorSize*=sizeof( RGBQUAD);
// calculate picture data size
 bi.biSizeImage = ( DWORD )bm.bmWidth * bi.biBitCount; // bits per row
 bi.biSizeImage = ( ( ( bi.biSizeImage ) + 31 ) / 32 ) * 4;
// DWORD aligned 
 bi.biSizeImage*=bm.bmHeight; // bytes required for whole bitmap
// return size to caler in case they want to save to file
 if ( pbmData )
 *pbmData = bi.biSize + biColorSize;
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
// get DIB color table and picture data
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
// allocate a hunk of memory to hold header, color table and picture data
 HANDLE hDIB = GlobalAlloc( GHND, bi.biSize + biColorSize +bi.biSizeImage );
// get a memory pointer to this hunk by locking it
 LPBITMAPINFOHEADER lpbi = ( LPBITMAPINFOHEADER )GlobalLock( hDIB );
// copy our header structure into hunk
 *lpbi = bi;
// get a device context and select our bitmap's palette into it
 CDC dc;
 dc.Attach( ::GetDC( NULL ) );
 CPalette *pPal = dc.SelectPalette( m_pPalette,FALSE );
 dc.RealizePalette() ;
// load our memory hunk with the color table and picture data
 GetDIBits( dc.m_hDC, ( HBITMAP )m_hObject, 0, ( UINT )bi.biHeight,( LPSTR )lpbi + ( WORD )lpbi -> biSize + biColorSize,( LPBITMAPINFO )lpbi, DIB_RGB_COLORS );
// clean up
 GlobalUnlock( hDIB );
 dc.SelectPalette( pPal,FALSE );
 dc.RealizePalette();
// return handle to the DIB
 return hDIB;
}

