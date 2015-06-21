# Microsoft Developer Studio Project File - Name="MapManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MapManager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MapManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MapManager.mak" CFG="MapManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MapManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MapManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MapManager - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MapManager - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MapManager - Win32 Release"
# Name "MapManager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnnoSymbolDlg.cpp
# End Source File
# Begin Source File

SOURCE="D:\Program Files\Microsoft Visual Studio\VC98\MFC\SRC\APPMODUL.CPP"
# End Source File
# Begin Source File

SOURCE=.\AutoHideBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DockPageBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoAnno.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoLine.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoMap.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoObject.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid.cpp
# End Source File
# Begin Source File

SOURCE=.\HawkeyeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Index.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerChooseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LineSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\LineSymbolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MapManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MapManager.rc
# End Source File
# Begin Source File

SOURCE=.\MapManagerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MapManagerDockPageBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MapManagerView.cpp
# End Source File
# Begin Source File

SOURCE=.\PointSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\PointSymbolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PolygonSymbol.cpp
# End Source File
# Begin Source File

SOURCE=.\PolySymbolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewBitmap.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnnoSymbolDlg.h
# End Source File
# Begin Source File

SOURCE=.\AutoHideBar.h
# End Source File
# Begin Source File

SOURCE=.\ChangeFormat.h
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DockPageBar.h
# End Source File
# Begin Source File

SOURCE=.\GeoAnno.h
# End Source File
# Begin Source File

SOURCE=.\GeoLayer.h
# End Source File
# Begin Source File

SOURCE=.\GeoLine.h
# End Source File
# Begin Source File

SOURCE=.\GeoMap.h
# End Source File
# Begin Source File

SOURCE=.\GeoObject.h
# End Source File
# Begin Source File

SOURCE=.\GeoPoint.h
# End Source File
# Begin Source File

SOURCE=.\GeoPolygon.h
# End Source File
# Begin Source File

SOURCE=.\Grid.h
# End Source File
# Begin Source File

SOURCE=.\HawkeyeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Index.h
# End Source File
# Begin Source File

SOURCE=.\LayerChooseDlg.h
# End Source File
# Begin Source File

SOURCE=.\LineSymbol.h
# End Source File
# Begin Source File

SOURCE=.\LineSymbolDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapTree.h
# End Source File
# Begin Source File

SOURCE=.\MapManager.h
# End Source File
# Begin Source File

SOURCE=.\MapManagerDoc.h
# End Source File
# Begin Source File

SOURCE=.\MapManagerDockPageBar.h
# End Source File
# Begin Source File

SOURCE=.\MapManagerView.h
# End Source File
# Begin Source File

SOURCE=.\PointSymbol.h
# End Source File
# Begin Source File

SOURCE=.\PointSymbolDlg.h
# End Source File
# Begin Source File

SOURCE=.\PolygonSymbol.h
# End Source File
# Begin Source File

SOURCE=.\PolySymbolDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tool.h
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.h
# End Source File
# Begin Source File

SOURCE=.\ViewBitmap.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Donate.ico
# End Source File
# Begin Source File

SOURCE=".\res\Downloads-Folder-Icon.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Eject Blue Button.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Eye.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainframe.ico
# End Source File
# Begin Source File

SOURCE=.\res\Map.ico
# End Source File
# Begin Source File

SOURCE=.\res\MapManager.ico
# End Source File
# Begin Source File

SOURCE=.\res\MapManager.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MapManagerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\pan1.cur
# End Source File
# Begin Source File

SOURCE=".\res\Smiley Blue.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Smiley.ico
# End Source File
# Begin Source File

SOURCE=.\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1hot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbarcolor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbardisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbarhot.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Video-Folder-Icon.ico"
# End Source File
# Begin Source File

SOURCE=".\res\放大缩小.cur"
# End Source File
# Begin Source File

SOURCE=".\res\漫游1.cur"
# End Source File
# Begin Source File

SOURCE=".\res\漫游2.cur"
# End Source File
# Begin Source File

SOURCE=".\res\全屏显示.cur"
# End Source File
# Begin Source File

SOURCE=".\res\指针.cur"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
