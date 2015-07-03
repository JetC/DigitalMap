// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__111A6ED9_0CA5_4EA5_80D5_7E94AE95EC65__INCLUDED_)
#define AFX_STDAFX_H__111A6ED9_0CA5_4EA5_80D5_7E94AE95EC65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include "afxtempl.h"
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



#ifdef WIN32

//屏蔽对4244的警告
#pragma warning (disable: 4244)

// 屏蔽对类型名超过255字符时的警告
#pragma warning (disable: 4514 4786)

#endif


#define WM_AUTOHIDE_ON		WM_USER+1

#include "sizecbar.h"
#include "AutoHideBar.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__111A6ED9_0CA5_4EA5_80D5_7E94AE95EC65__INCLUDED_)
