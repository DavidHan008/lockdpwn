// ChooseType.cpp : implementation file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "ContextEdit.h"
#include "ChooseType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CContextEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CChooseType dialog


CChooseType::CChooseType(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChooseType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseType)
	DDX_Control(pDX, IDC_lstMaster, m_lstMaster);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseType, CDialog)
	//{{AFX_MSG_MAP(CChooseType)
	ON_LBN_SELCHANGE(IDC_lstMaster, OnSelchangelstMaster)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseType message handlers

BOOL CChooseType::OnInitDialog() 
{
	int i, iItem;
	CDialog::OnInitDialog();
	PFTELEMENT pTarget;

	for (i = 0; i < theApp.m_intTypeArrayCount; i++)
	{
		pTarget = theApp.m_pFileTypeArray[i];
		if (pTarget->bIsExt || pTarget->bIsSystemType)
			continue;
		if (pTarget->strType == "*")
			continue;
		if (pTarget->strFriendly.IsEmpty())
			iItem = m_lstMaster.AddString(pTarget->strType);
		else
			iItem = m_lstMaster.AddString(pTarget->strFriendly);
		m_lstMaster.SetItemDataPtr(iItem, pTarget);
	}
	m_lstMaster.SetCurSel(0);
	OnSelchangelstMaster();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseType::OnSelchangelstMaster() 
{
	m_pChosenType = (PFTELEMENT) m_lstMaster.GetItemDataPtr(m_lstMaster.GetCurSel());
}
