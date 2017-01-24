#if !defined(AFX_CMDDLG_H__A8DD1CE1_BEDD_11D4_A4C8_00A0CC307F9C__INCLUDED_)
#define AFX_CMDDLG_H__A8DD1CE1_BEDD_11D4_A4C8_00A0CC307F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CmdDlg.h : header file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

/////////////////////////////////////////////////////////////////////////////
// CCmdDlg dialog

class CCmdDlg : public CDialog
{
// Construction
public:
	CString m_strInternal;
	BOOL m_bMode;
	CCmdDlg(CWnd* pParent = NULL);   // standard constructor
	~CCmdDlg();

// Dialog Data
	//{{AFX_DATA(CCmdDlg)
	enum { IDD = IDD_COMMAND_DLG };
	CButton	m_chkExpandCmdLine;
	CButton	m_cmdOK;
	CButton	m_cmdCancel;
	CButton	m_cmdHelp;
	CButton	m_cmdBrowse;
	CButton	m_chkUseDDE;
	CEdit	m_txtMenuText;
	CEdit	m_txtCommandLine;
	CEdit	m_txtTopic;
	CEdit	m_txtNotRunning;
	CEdit	m_txtDDEmessage;
	CEdit	m_txtApplication;
	BOOL	m_bUseDDE;
	CString	m_strDDEexec;
	CString	m_strMenuText;
	CString	m_strDDEnotrunning;
	CString	m_strDDEtopic;
	CString	m_strDDEapp;
	CString	m_strCommandLine;
	BOOL	m_bExpandCmdLine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCmdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnchkUseDDE();
	afx_msg void OncmdBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolTipCtrl *m_pToolTip;
	void EnableDDEFields(BOOL bEnable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDDLG_H__A8DD1CE1_BEDD_11D4_A4C8_00A0CC307F9C__INCLUDED_)
