; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCmdDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ContextEdit.h"

ClassCount=8
Class1=CContextEditApp
Class2=CContextEditDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CMD_NAME
Resource4=IDD_COMMAND_DLG
Class4=CCmdDlg
Resource5=IDD_CONTEXTEDIT_DIALOG
Class5=CCmdNameDlg
Resource6=IDD_PROGRESS_DLG
Class6=CMoveErrDlg
Resource7=IDD_CHOOSE_TYPE
Class7=CChooseType
Resource8=IDD_MOVE_ERROR
Class8=CWarnBroken
Resource9=IDD_WARN_BROKEN

[CLS:CContextEditApp]
Type=0
HeaderFile=ContextEdit.h
ImplementationFile=ContextEdit.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CContextEditApp

[CLS:CContextEditDlg]
Type=0
HeaderFile=ContextEditDlg.h
ImplementationFile=ContextEditDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CContextEditDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ContextEditDlg.h
ImplementationFile=ContextEditDlg.cpp
Filter=D

[DLG:IDD_PROGRESS_DLG]
Type=1
Class=?
ControlCount=1
Control1=IDC_PROGRESS1,msctls_progress32,1350565889

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_COMMAND_DLG]
Type=1
Class=CCmdDlg
ControlCount=19
Control1=IDC_STATIC,static,1342308352
Control2=IDC_txtMenuText,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_txtCommandLine,edit,1350631552
Control5=IDC_cmdBrowse,button,1342242816
Control6=IDC_chkExpandCmdLine,button,1342242819
Control7=IDC_STATIC,button,1342177287
Control8=IDC_chkUseDDE,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_txtDDEMessage,edit,1484849280
Control11=IDC_STATIC,static,1342308352
Control12=IDC_txtApplication,edit,1484849280
Control13=IDC_STATIC,static,1342308352
Control14=IDC_txtNotRunning,edit,1484849280
Control15=IDC_STATIC,static,1342308352
Control16=IDC_txtTopic,edit,1484849280
Control17=IDOK,button,1342242817
Control18=ID_HELP,button,1342242816
Control19=IDCANCEL,button,1342242816

[CLS:CCmdDlg]
Type=0
HeaderFile=CmdDlg.h
ImplementationFile=CmdDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_chkExpandCmdLine

[DLG:IDD_CMD_NAME]
Type=1
Class=CCmdNameDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_txtCommand,edit,1350631552
Control3=IDOK,button,1342242817
Control4=ID_HELP,button,1342242816
Control5=IDCANCEL,button,1342242816

[CLS:CCmdNameDlg]
Type=0
HeaderFile=CmdNameDlg.h
ImplementationFile=CmdNameDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_MOVE_ERROR]
Type=1
Class=CMoveErrDlg
ControlCount=7
Control1=IDC_lblWarning,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_optFix0,button,1342373897
Control4=IDC_optFix1,button,1342177289
Control5=IDOK,button,1342373889
Control6=ID_HELP,button,1342242816
Control7=IDCANCEL,button,1342242816

[CLS:CMoveErrDlg]
Type=0
HeaderFile=MoveErrDlg.h
ImplementationFile=MoveErrDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMoveErrDlg
VirtualFilter=dWC

[DLG:IDD_CHOOSE_TYPE]
Type=1
Class=CChooseType
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_lstMaster,listbox,1352728835
Control3=IDOK,button,1342242817
Control4=ID_HELP,button,1342242816
Control5=IDCANCEL,button,1342242816

[CLS:CChooseType]
Type=0
HeaderFile=ChooseType.h
ImplementationFile=ChooseType.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CChooseType

[DLG:IDD_WARN_BROKEN]
Type=1
Class=CWarnBroken
ControlCount=10
Control1=IDC_lblWarning,static,1342177408
Control2=IDC_STATIC,static,1342308352
Control3=IDC_optRepair0,button,1342382089
Control4=IDC_optRepair1,button,1342177289
Control5=IDC_optRepair2,button,1342185481
Control6=IDC_optRepair3,button,1342177289
Control7=IDC_optRepair4,button,1342185481
Control8=IDOK,button,1342373889
Control9=ID_HELP,button,1342242816
Control10=IDCANCEL,button,1342242816

[CLS:CWarnBroken]
Type=0
HeaderFile=WarnBroken.h
ImplementationFile=WarnBroken.cpp
BaseClass=CDialog
Filter=D
LastObject=CWarnBroken
VirtualFilter=dWC

[DLG:IDD_CONTEXTEDIT_DIALOG]
Type=1
Class=CContextEditDlg
ControlCount=20
Control1=IDC_STATIC,static,1342308352
Control2=IDC_lstTypes,listbox,1353777411
Control3=IDC_cmdRefresh,button,1342242816
Control4=IDC_cmdFindType,button,1342242816
Control5=IDC_lblInternal,static,1342308352
Control6=IDC_lblInternalName,static,1342308352
Control7=IDC_lblExtensions,static,1342308352
Control8=IDC_cmbExtensions,combobox,1344340227
Control9=IDC_lblCommands,static,1342308352
Control10=IDC_lstCommands,SysListView32,1350664269
Control11=IDC_cmdSetDefault,button,1342242816
Control12=IDC_cmdEditCommand,button,1342242816
Control13=IDC_cmdNewCommand,button,1342242816
Control14=IDC_cmdDeleteCommand,button,1342242816
Control15=IDC_cmdMoveTo,button,1342242816
Control16=IDC_lblHandlers,static,1342308352
Control17=IDC_lstHandlers,SysListView32,1350664269
Control18=IDC_cmdAbout,button,1342242816
Control19=ID_HELP,button,1342242816
Control20=IDOK,button,1342242817

