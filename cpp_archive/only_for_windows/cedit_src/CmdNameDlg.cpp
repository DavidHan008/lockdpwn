// CmdNameDlg.cpp : implementation file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "ContextEdit.h"
#include "CmdNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CContextEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCmdNameDlg dialog


CCmdNameDlg::CCmdNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCmdNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCmdNameDlg)
	m_strCommand = _T("");
	//}}AFX_DATA_INIT
}


void CCmdNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCmdNameDlg)
	DDX_Control(pDX, IDC_txtCommand, m_txtCommand);
	DDX_Text(pDX, IDC_txtCommand, m_strCommand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCmdNameDlg, CDialog)
	//{{AFX_MSG_MAP(CCmdNameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdNameDlg message handlers

void CCmdNameDlg::OnOK() 
{
	UpdateData(TRUE);
	m_strCommand.TrimLeft();
	m_strCommand.TrimRight();
	if (m_strCommand.IsEmpty())
	{
		AfxMessageBox("Name cannot be blank.", MB_ICONINFORMATION);
		return;
	}
	if (m_strCommand.Find('\\') >= 0)
	{
		AfxMessageBox("Name cannot include backslashes", MB_ICONINFORMATION);
		return;
	}
	if (theApp.CommandExists(m_strCommand, 2))
	{
		AfxMessageBox("The name you specified is already in use.", MB_ICONINFORMATION);
		return;
	}
	CDialog::OnOK();
}
