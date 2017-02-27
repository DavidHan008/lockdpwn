#if !defined(AFX_WARNBROKEN_H__6F81F5E5_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_)
#define AFX_WARNBROKEN_H__6F81F5E5_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarnBroken.h : header file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

/////////////////////////////////////////////////////////////////////////////
// CWarnBroken dialog

class CWarnBroken : public CDialog
{
// Construction
public:
	PFTELEMENT m_pFileType;
	CWarnBroken(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWarnBroken)
	enum { IDD = IDD_WARN_BROKEN };
	CStatic	m_lblWarning;
	int		m_intRepair;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarnBroken)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWarnBroken)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNBROKEN_H__6F81F5E5_C731_11D4_A4C8_00A0CC307F9C__INCLUDED_)
