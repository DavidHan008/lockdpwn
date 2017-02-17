
// StickyNotesBackupDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include <list>
#include <string>

using namespace std;

// CStickyNotesBackupDlg dialog
class CStickyNotesBackupDlg : public CDialog
{
// Construction
public:
	CStickyNotesBackupDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STICKYNOTESBACKUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	list<string> _backupFiles;

	bool IsCurrentNotesBackuped ();
	void ReloadBackupList ();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBackup();
	CListCtrl _backupList;
	afx_msg void OnBnClickedButtonRestore();
	afx_msg void OnBnClickedButtonDelete();
};
