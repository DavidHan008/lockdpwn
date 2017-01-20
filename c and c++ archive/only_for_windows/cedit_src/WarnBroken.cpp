// WarnBroken.cpp : implementation file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "ContextEdit.h"
#include "WarnBroken.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWarnBroken dialog


CWarnBroken::CWarnBroken(CWnd* pParent /*=NULL*/)
	: CDialog(CWarnBroken::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWarnBroken)
	m_intRepair = 3;
	//}}AFX_DATA_INIT
}


void CWarnBroken::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarnBroken)
	DDX_Control(pDX, IDC_lblWarning, m_lblWarning);
	DDX_Radio(pDX, IDC_optRepair0, m_intRepair);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWarnBroken, CDialog)
	//{{AFX_MSG_MAP(CWarnBroken)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarnBroken message handlers

BOOL CWarnBroken::OnInitDialog() 
{
	CString strPrompt;

	CDialog::OnInitDialog();
	if (m_pFileType != NULL)
	{
		strPrompt.Format("The extension \"%s\" is linked to the master file type \"%s\", which does not exist.", m_pFileType->strType, m_pFileType->strFriendly);
		m_lblWarning.SetWindowText(strPrompt);
	}

	return TRUE;
}

