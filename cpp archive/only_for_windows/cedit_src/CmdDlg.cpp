// CmdDlg.cpp : implementation file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "ContextEdit.h"
#include "CmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CContextEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCmdDlg dialog


CCmdDlg::CCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCmdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCmdDlg)
	m_bUseDDE = FALSE;
	m_strDDEexec = _T("");
	m_strMenuText = _T("");
	m_strDDEnotrunning = _T("");
	m_strDDEtopic = _T("");
	m_strDDEapp = _T("");
	m_strCommandLine = _T("");
	m_bExpandCmdLine = FALSE;
	//}}AFX_DATA_INIT
	m_pToolTip = NULL;
}

CCmdDlg::~CCmdDlg()
{
	if (m_pToolTip != NULL)
		delete m_pToolTip;
}


void CCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCmdDlg)
	DDX_Control(pDX, IDC_chkExpandCmdLine, m_chkExpandCmdLine);
	DDX_Control(pDX, IDOK, m_cmdOK);
	DDX_Control(pDX, IDCANCEL, m_cmdCancel);
	DDX_Control(pDX, ID_HELP, m_cmdHelp);
	DDX_Control(pDX, IDC_cmdBrowse, m_cmdBrowse);
	DDX_Control(pDX, IDC_chkUseDDE, m_chkUseDDE);
	DDX_Control(pDX, IDC_txtMenuText, m_txtMenuText);
	DDX_Control(pDX, IDC_txtCommandLine, m_txtCommandLine);
	DDX_Control(pDX, IDC_txtTopic, m_txtTopic);
	DDX_Control(pDX, IDC_txtNotRunning, m_txtNotRunning);
	DDX_Control(pDX, IDC_txtDDEMessage, m_txtDDEmessage);
	DDX_Control(pDX, IDC_txtApplication, m_txtApplication);
	DDX_Check(pDX, IDC_chkUseDDE, m_bUseDDE);
	DDX_Text(pDX, IDC_txtDDEMessage, m_strDDEexec);
	DDX_Text(pDX, IDC_txtMenuText, m_strMenuText);
	DDX_Text(pDX, IDC_txtNotRunning, m_strDDEnotrunning);
	DDX_Text(pDX, IDC_txtTopic, m_strDDEtopic);
	DDX_Text(pDX, IDC_txtApplication, m_strDDEapp);
	DDX_Text(pDX, IDC_txtCommandLine, m_strCommandLine);
	DDX_Check(pDX, IDC_chkExpandCmdLine, m_bExpandCmdLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CCmdDlg)
	ON_BN_CLICKED(IDC_chkUseDDE, OnchkUseDDE)
	ON_BN_CLICKED(IDC_cmdBrowse, OncmdBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdDlg message handlers

BOOL CCmdDlg::OnInitDialog() 
{
	CString strTitle;
	CRect	rectClient;
	CDialog::OnInitDialog();

	if (m_bMode)
		strTitle.Format("Creating New Command: %s", m_strInternal);
	else
		strTitle.Format("Editing Command: %s", m_strInternal);
	SetWindowText(strTitle);
	EnableDDEFields(m_bUseDDE);
	m_pToolTip = new CToolTipCtrl;
	if (m_pToolTip != NULL)
	{
		if (m_pToolTip->Create(this))
		{
			m_pToolTip->AddTool(&m_txtMenuText, "Determines how this command will appear in Explorer's context menu. If omitted, Explorer builds menu text based on the command's internal name.");
			m_pToolTip->AddTool(&m_txtCommandLine, "Specifies the command line that Explorer will execute for this command. (This field is required)");
			m_pToolTip->AddTool(&m_cmdBrowse, "Choose an executable file and build a default command using its filename.");
			m_pToolTip->AddTool(&m_chkExpandCmdLine, "Enables expansion of environment variables in your command line. If disabled, your system does not support this feature.");
			m_pToolTip->AddTool(&m_chkUseDDE, "Determines whether or not Explorer will use Dynamic Data Exchange to execute this command.");
			m_pToolTip->AddTool(&m_txtDDEmessage, "Specifies the DDE command that Explorer will send to the target application. (Required if the Use DDE box is checked).");
			m_pToolTip->AddTool(&m_txtApplication, "Specifies the internal name of the application used to establish a DDE conversation. If omitted, Explorer uses the name of the executable file specified in the Command Line.");
			m_pToolTip->AddTool(&m_txtTopic, "Specifies the topic used to establish the DDE conversation with the target application. If omitted, Explorer uses the \"system\" topic.");
			m_pToolTip->AddTool(&m_txtNotRunning, "Specifies the command that Explorer will use to launch the target program if it is not already running. If omitted, Explorer uses the contents of the Command Line field.");
			m_pToolTip->AddTool(&m_cmdOK, "Save your changes and return to the main dialog.");
			m_pToolTip->AddTool(&m_cmdHelp, "Display help information for this dialog.");
			if (m_bMode)
				m_pToolTip->AddTool(&m_cmdCancel, "Return to the main dialog without creating a new shell command.");
			else
				m_pToolTip->AddTool(&m_cmdCancel, "Discard your changes and return to the main dialog.");
			GetClientRect(rectClient);
			m_pToolTip->SetMaxTipWidth(rectClient.Width() / 2);
			m_pToolTip->Activate(TRUE);
		}
	}
	m_chkExpandCmdLine.EnableWindow(theApp.m_bAllowExpansion);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCmdDlg::OnchkUseDDE() 
{
	UpdateData(TRUE);
	EnableDDEFields(m_bUseDDE);
}

void CCmdDlg::OncmdBrowse() 
{
	CString		strTemp;

	// Create a standard File/Open dialog
	CFileDialog dlg(TRUE,
					".exe",
					NULL,
					OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
					"Applications (*.exe)|*.exe|DOS Applications (*.com)|*.com|Batch files (*.bat)|*.bat|All Files (*.*)|*.*||",
					this);

	// Set dialog box title
	dlg.m_ofn.lpstrTitle = "Choose Application";


	// Launch the file dialog. If user chose a file,
	if (dlg.DoModal() == IDOK)
	{
		// Build a default command line based on that filename
		strTemp.Format("\"%s\" \"%%1\"", dlg.GetPathName());
		// and plug it into the field.
		m_txtCommandLine.SetWindowText(strTemp);
	}
}


// Enables/disables the DDE edit controls.
void CCmdDlg::EnableDDEFields(BOOL bEnable)
{
	m_txtDDEmessage.EnableWindow(bEnable);
	m_txtApplication.EnableWindow(bEnable);
	m_txtNotRunning.EnableWindow(bEnable);
	m_txtTopic.EnableWindow(bEnable);
}


void CCmdDlg::OnOK() 
{
	UpdateData(TRUE);

	// Remove leading/trailing blanks from command line.
	m_strCommandLine.TrimLeft();
	m_strCommandLine.TrimRight();


	// Don't accept if command line is blank.
	if (m_strCommandLine.IsEmpty())
	{
		AfxMessageBox("Command line cannot be blank.", MB_ICONEXCLAMATION);
		m_txtCommandLine.SetFocus();
		UpdateData(FALSE);
		return;
	}

	// Remove leading/trailing blanks from menu text.
	m_strMenuText.TrimLeft();
	m_strMenuText.TrimRight();


	// Not a critical error if menu text is blank, so let user decide.
	if (m_strMenuText.IsEmpty())
	{
		if (AfxMessageBox("Warning: There is no menu text defined.\n"
			"This will not prevent the command from functioning,\n"
			"but the command may not appear in the context\n"
			"menu as you expect.\n\n"
			"Do you wish to leave the menu text undefined?",
			MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			m_txtMenuText.SetFocus();
			UpdateData(FALSE);
			return;
		}
	}


	// Clean leading/trailing blanks from DDE fields.
	m_strDDEexec.TrimLeft();
	m_strDDEexec.TrimRight();
	m_strDDEnotrunning.TrimLeft();
	m_strDDEnotrunning.TrimRight();
	m_strDDEapp.TrimLeft();
	m_strDDEapp.TrimRight();
	m_strDDEtopic.TrimLeft();
	m_strDDEtopic.TrimRight();
	UpdateData(FALSE);
	
	
	// Can't enable DDE without an explicit DDE command.
	if (m_bUseDDE && m_strDDEexec.IsEmpty())
	{
		MessageBox("DDE message string cannot be blank.\n"
			"If you do not wish to use DDE to execute\n"
			"this command, clear the Use DDE checkbox.");
		m_txtDDEmessage.SetFocus();
		return;
	}
	CDialog::OnOK();
}


BOOL CCmdDlg::PreTranslateMessage(MSG* pMsg) 
{

	if (m_pToolTip != NULL)
		m_pToolTip->RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}
