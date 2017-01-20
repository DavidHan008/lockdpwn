// ContextEditDlg.h : header file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#if !defined(AFX_MNUASSTDLG_H__62F4BA07_A9B4_11D4_A4C7_00A0CC307F9C__INCLUDED_)
#define AFX_MNUASSTDLG_H__62F4BA07_A9B4_11D4_A4C7_00A0CC307F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CContextEditDlg dialog

class CContextEditDlg : public CDialog
{
// Construction
public:
	BOOL m_bAllowExpansion;
	CToolTipCtrl* m_pToolTip;
	CContextEditDlg(CWnd* pParent = NULL);	// standard constructor
	~CContextEditDlg();

	BOOL		m_bWarnBroken;	// Flag for broken association warning.
	// Image lists for the list controls.
	CImageList m_imgCheck;
	CImageList m_imgState;

// Dialog Data
	//{{AFX_DATA(CContextEditDlg)
	enum { IDD = IDD_CONTEXTEDIT_DIALOG };
	CButton	m_cmdHelp;
	CButton	m_cmdAbout;
	CButton	m_cmdOK;
	CButton	m_cmdRefresh;
	CStatic	m_lblInternal;
	CStatic	m_lblHandlers;
	CStatic	m_lblExtensions;
	CStatic	m_lblCommands;
	CButton	m_cmdMoveTo;
	CButton	m_cmdNewCommand;
	CButton	m_cmdEditCommand;
	CButton	m_cmdDeleteCommand;
	CButton	m_cmdFindType;
	CStatic	m_lblInternalName;
	CComboBox	m_cmbExtensions;
	CListBox	m_lstTypes;
	CButton	m_cmdSetDefault;
	CListCtrl	m_lstHandlers;
	CListCtrl	m_lstCommands;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContextEditDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetButtonStatus();
	// Member variables.
	HICON m_hIcon;

	// Member functions.
	BOOL InstallDDEField(HKEY hKeyParent, LPCTSTR pszFieldName, CString& strContent);
	BOOL InstallCommand(PSHELLCOMMAND pCommand, PFTELEMENT pType);
	BOOL ToggleHandler(int iItem);
	void BuildTypeList(void);
	void ReportRegError(LPCTSTR strExtraText = NULL);
	void ToggleCommand(int iItem);

	// Generated message map functions
	//{{AFX_MSG(CContextEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnGetdispinfolstCommands(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfolstHandlers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClicklstCommands(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedlstCommands(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OncmdSetDefault();
	afx_msg void OncmdAbout();
	afx_msg void OnSelchangelstTypes();
	afx_msg void OncmdRefresh();
	afx_msg void OncmdDeleteCommand();
	afx_msg void OncmdEditCommand();
	afx_msg void OncmdNewCommand();
	afx_msg void OncmdFindType();
	afx_msg void OnKeydownlstCommands(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnDblclklstCommands(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OncmdMoveTo();
	afx_msg void OnClicklstHandlers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclklstTypes();
	afx_msg void OnKeydownlstHandlers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	afx_msg BOOL OnNeedText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MNUASSTDLG_H__62F4BA07_A9B4_11D4_A4C7_00A0CC307F9C__INCLUDED_)
