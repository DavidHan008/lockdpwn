#if !defined(AFX_PROGRESSDLG_H__8CE87D74_A761_11D4_A4C7_00A0CC307F9C__INCLUDED_)
#define AFX_PROGRESSDLG_H__8CE87D74_A761_11D4_A4C7_00A0CC307F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : header file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

class CProgressDlg : public CDialog
{
// Construction
public:
	CProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS_DLG };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLG_H__8CE87D74_A761_11D4_A4C7_00A0CC307F9C__INCLUDED_)
