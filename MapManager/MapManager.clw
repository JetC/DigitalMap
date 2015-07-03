; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MapManager.h"
LastPage=0

ClassCount=14
Class1=CMapManagerApp
Class2=CMapManagerDoc
Class3=CMapManagerView
Class4=CMainFrame

ResourceCount=14
Resource1=IDD_CHANGEFORMATDLG1
Resource2=IDD_LINESYM_DLG
Class5=CAboutDlg
Class6=CChangeFormat
Resource3=IDD_ANNOSYM_DLG
Class7=CInfoDisplayDlg
Class8=CMyTree
Resource4=IDR_TOOLBAR
Class9=CLayerChooseDlg
Resource5=IDR_MAINFRAME
Resource6=IDD_GONSYM_DLG
Resource7=IDR_FLOATMENU
Resource8=IDR_MENUTREE
Class10=CPointSymbolDlg
Class11=CLineSymbolDlg
Class12=CPolySymbolDlg
Class13=CAnnoSymbolDlg
Resource9=IDD_LAYERCHOOSE
Class14=HawkeyeDlg
Resource10=IDD_INFODISPLAY
Resource11=IDD_POINTSYM_DLG
Resource12=IDD_ABOUTBOX
Resource13=IDR_TOOLBAR1
Resource14=IDD_HawkDlg

[CLS:CMapManagerApp]
Type=0
HeaderFile=MapManager.h
ImplementationFile=MapManager.cpp
Filter=N

[CLS:CMapManagerDoc]
Type=0
HeaderFile=MapManagerDoc.h
ImplementationFile=MapManagerDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMapManagerDoc

[CLS:CMapManagerView]
Type=0
HeaderFile=MapManagerView.h
ImplementationFile=MapManagerView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CMapManagerView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CAutoHideFrame
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=MapManager.cpp
ImplementationFile=MapManager.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILESAVE
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_ZOOMINPOINT
Command10=ID_ZOOMOUTPOINT
Command11=ID_ZOOMIN
Command12=ID_ZOOMOUT
Command13=ID_PAN
Command14=ID_FULLWINDS
Command15=ID_MEASUREDISTANCE
Command16=ID_MEASUREAREA
Command17=ID_REFRESH
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_SHOW_LAYER
Command21=ID_SHOW_HawkeyeDLG
Command22=ID_LAYERSELECT
Command23=ID_BMPSAVE
Command24=ID_FILESAVE
Command25=ID_CHANGEFORMAT
Command26=ID_APP_ABOUT
Command27=ID_HELP
CommandCount=27

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_CHANGEFORMATDLG1]
Type=1
Class=CChangeFormat
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_SOURCE,button,1342242816
Control6=IDC_GOAL,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342177283
Control13=IDC_STATIC,static,1342177283
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287

[CLS:CChangeFormat]
Type=0
HeaderFile=ChangeFormat.h
ImplementationFile=ChangeFormat.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_INFODISPLAY]
Type=1
Class=CInfoDisplayDlg
ControlCount=1
Control1=IDOK,button,1342242817

[CLS:CInfoDisplayDlg]
Type=0
HeaderFile=InfoDisplayDlg.h
ImplementationFile=InfoDisplayDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CMyTree]
Type=0
HeaderFile=MyTree.h
ImplementationFile=MyTree.cpp
BaseClass=CTreeCtrl
Filter=W

[DLG:IDD_LAYERCHOOSE]
Type=1
Class=CLayerChooseDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LAYER_INFO,static,1342308352
Control4=IDC_STATIC,button,1342177287

[CLS:CLayerChooseDlg]
Type=0
HeaderFile=LayerChooseDlg.h
ImplementationFile=LayerChooseDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLayerChooseDlg

[DLG:IDD_POINTSYM_DLG]
Type=1
Class=CPointSymbolDlg
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_POINT_R,edit,1350631552
Control13=IDC_POINT_G,edit,1350631552
Control14=IDC_POINT_B,edit,1350631552
Control15=IDC_PT1,button,1342177289
Control16=IDC_PT2,button,1342177289
Control17=IDC_PT3,button,1342177289
Control18=IDC_STATIC,static,1342177294
Control19=IDC_STATIC,static,1342177294
Control20=IDC_STATIC,static,1342177294
Control21=IDC_POINT_RADIUS,edit,1350631552
Control22=IDC_SPIN1,msctls_updown32,1342177312
Control23=IDC_CHOOSEPOINTCOLOR,button,1342242816

[DLG:IDD_LINESYM_DLG]
Type=1
Class=CLineSymbolDlg
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_LT1,button,1342177289
Control7=IDC_LT2,button,1342177289
Control8=IDC_LT3,button,1342177289
Control9=IDC_LT4,button,1342177289
Control10=IDC_LT5,button,1342177289
Control11=IDC_LINE_WIDTH,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_LINE_R,edit,1350631552
Control16=IDC_LINE_G,edit,1350631552
Control17=IDC_LINE_B,edit,1350631552
Control18=IDC_STATIC,static,1342177294
Control19=IDC_STATIC,static,1342177294
Control20=IDC_STATIC,static,1342177294
Control21=IDC_STATIC,static,1342177294
Control22=IDC_STATIC,static,1342177294
Control23=IDC_CHANGELINECOLOR,button,1342242816

[DLG:IDD_GONSYM_DLG]
Type=1
Class=CPolySymbolDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BOND_R,edit,1350631552
Control12=IDC_BOND_G,edit,1350631552
Control13=IDC_BOND_B,edit,1350631552
Control14=IDC_FILL_R,edit,1350631552
Control15=IDC_FILL_G,edit,1350631552
Control16=IDC_FILL_B,edit,1350631552
Control17=IDC_CHANGELINECOLOR,button,1342242816
Control18=IDC_CHANGEFILLCOLOR,button,1342242816

[DLG:IDD_ANNOSYM_DLG]
Type=1
Class=CAnnoSymbolDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TEXTR,edit,1350631552
Control9=IDC_TEXTG,edit,1350631552
Control10=IDC_TEXTB,edit,1350631552
Control11=IDC_CHANGEANNOCOLOR,button,1342242816

[CLS:CPointSymbolDlg]
Type=0
HeaderFile=PointSymbolDlg.h
ImplementationFile=PointSymbolDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPointSymbolDlg

[CLS:CLineSymbolDlg]
Type=0
HeaderFile=LineSymbolDlg.h
ImplementationFile=LineSymbolDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CPolySymbolDlg]
Type=0
HeaderFile=PolySymbolDlg.h
ImplementationFile=PolySymbolDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CAnnoSymbolDlg]
Type=0
HeaderFile=AnnoSymbolDlg.h
ImplementationFile=AnnoSymbolDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAnnoSymbolDlg

[DLG:IDD_HawkDlg]
Type=1
Class=HawkeyeDlg
ControlCount=0

[CLS:HawkeyeDlg]
Type=0
HeaderFile=HawkeyeDlg.h
ImplementationFile=HawkeyeDlg.cpp
BaseClass=CDialog
Filter=D

[MNU:IDR_MENUTREE]
Type=1
Class=?
CommandCount=0

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILESAVE
Command4=ID_LAYERSELECT
Command5=ID_REFRESH
Command6=ID_FILE_PRINT
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=ID_PAN
Command2=ID_ZOOMINPOINT
Command3=ID_ZOOMIN
Command4=ID_ZOOMOUTPOINT
Command5=ID_ZOOMOUT
Command6=ID_FULLWINDS
Command7=ID_MEASUREDISTANCE
Command8=ID_MEASUREAREA
Command9=ID_LAYERSELECT
Command10=ID_CHANGEFORMAT
Command11=ID_BMPSAVE
CommandCount=11

[MNU:IDR_FLOATMENU]
Type=1
Class=?
Command1=ID_PAN
Command2=ID_ZOOMINPOINT
Command3=ID_ZOOMIN
Command4=ID_ZOOMOUTPOINT
Command5=ID_ZOOMOUTPOINT
Command6=ID_FULLWINDS
Command7=ID_HELP
CommandCount=7

