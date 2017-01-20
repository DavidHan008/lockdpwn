// MoveErrDlg.cpp : implementation file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "ContextEdit.h"
#include "MoveErrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CContextEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMoveErrDlg dialog


CMoveErrDlg::CMoveErrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveErrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoveErrDlg)
	m_intFix = 0;
	//}}AFX_DATA_INIT

	m_pFileType = NULL;
}


void CMoveErrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoveErrDlg)
	DDX_Control(pDX, IDC_lblWarning, m_lblWarning);
	DDX_Radio(pDX, IDC_optFix0, m_intFix);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoveErrDlg, CDialog)
	//{{AFX_MSG_MAP(CMoveErrDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveErrDlg message handlers

BOOL CMoveErrDlg::OnInitDialog() 
{
	CString strPrompt;

	CDialog::OnInitDialog();

	if (m_pFileType != NULL)
	{
		strPrompt.Format("The commands for the extension \"%s\" cannot be moved because the master file type \"%s\" does not exist.", m_pFileType->strType, m_pFileType->strFriendly);
		m_lblWarning.SetWindowText(strPrompt);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
