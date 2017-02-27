#if !defined(AFX_CMDNAMEDLG_H__6F81F5E1_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_)
#define AFX_CMDNAMEDLG_H__6F81F5E1_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CmdNameDlg.h : header file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

/////////////////////////////////////////////////////////////////////////////
// CCmdNameDlg dialog

class CCmdNameDlg : public CDialog
{
// Construction
public:
	CCmdNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCmdNameDlg)
	enum { IDD = IDD_CMD_NAME };
	CEdit	m_txtCommand;
	CString	m_strCommand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCmdNameDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDNAMEDLG_H__6F81F5E1_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_)
