#if !defined(AFX_MOVEERRDLG_H__6F81F5E3_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_)
#define AFX_MOVEERRDLG_H__6F81F5E3_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_

#include "ContextEdit.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoveErrDlg.h : header file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

/////////////////////////////////////////////////////////////////////////////
// CMoveErrDlg dialog

class CMoveErrDlg : public CDialog
{
// Construction
public:
	PFTELEMENT m_pFileType;
	CMoveErrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMoveErrDlg)
	enum { IDD = IDD_MOVE_ERROR };
	CStatic	m_lblWarning;
	int		m_intFix;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoveErrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMoveErrDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEERRDLG_H__6F81F5E3_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_)
