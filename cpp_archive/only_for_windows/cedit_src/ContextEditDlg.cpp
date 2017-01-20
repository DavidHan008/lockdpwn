// ContextEditDlg.cpp : implementation file
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "RegHelpers.h"
#include "ContextEdit.h"
#include "ContextEditDlg.h"
#include "CmdDlg.h"
#include "CmdNameDlg.h"
#include "MoveErrDlg.h"
#include "ChooseType.h"
#include "WarnBroken.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Default strings for command list.
char pszUndefined[] = "<Undefined>";
char pszSysDefault[] = "<System Default>";

extern CContextEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContextEditDlg dialog

CContextEditDlg::CContextEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CContextEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContextEditDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// Default = show warning for broken associations.
	m_bWarnBroken = TRUE;
	// NULL pointer to the tooltip control.
	m_pToolTip = NULL;
}

// Class destructor
CContextEditDlg::~CContextEditDlg()
{
	// If the tooltip object exists,
	if (m_pToolTip != NULL)
		// delete it.
		delete m_pToolTip;
}



void CContextEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContextEditDlg)
	DDX_Control(pDX, ID_HELP, m_cmdHelp);
	DDX_Control(pDX, IDC_cmdAbout, m_cmdAbout);
	DDX_Control(pDX, IDOK, m_cmdOK);
	DDX_Control(pDX, IDC_cmdRefresh, m_cmdRefresh);
	DDX_Control(pDX, IDC_lblInternal, m_lblInternal);
	DDX_Control(pDX, IDC_lblHandlers, m_lblHandlers);
	DDX_Control(pDX, IDC_lblExtensions, m_lblExtensions);
	DDX_Control(pDX, IDC_lblCommands, m_lblCommands);
	DDX_Control(pDX, IDC_cmdMoveTo, m_cmdMoveTo);
	DDX_Control(pDX, IDC_cmdNewCommand, m_cmdNewCommand);
	DDX_Control(pDX, IDC_cmdEditCommand, m_cmdEditCommand);
	DDX_Control(pDX, IDC_cmdDeleteCommand, m_cmdDeleteCommand);
	DDX_Control(pDX, IDC_cmdFindType, m_cmdFindType);
	DDX_Control(pDX, IDC_lblInternalName, m_lblInternalName);
	DDX_Control(pDX, IDC_cmbExtensions, m_cmbExtensions);
	DDX_Control(pDX, IDC_lstTypes, m_lstTypes);
	DDX_Control(pDX, IDC_cmdSetDefault, m_cmdSetDefault);
	DDX_Control(pDX, IDC_lstHandlers, m_lstHandlers);
	DDX_Control(pDX, IDC_lstCommands, m_lstCommands);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CContextEditDlg, CDialog)
	//{{AFX_MSG_MAP(CContextEditDlg)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_lstCommands, OnGetdispinfolstCommands)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_lstHandlers, OnGetdispinfolstHandlers)
	ON_NOTIFY(NM_CLICK, IDC_lstCommands, OnClicklstCommands)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_lstCommands, OnItemchangedlstCommands)
	ON_BN_CLICKED(IDC_cmdSetDefault, OncmdSetDefault)
	ON_BN_CLICKED(IDC_cmdAbout, OncmdAbout)
	ON_LBN_SELCHANGE(IDC_lstTypes, OnSelchangelstTypes)
	ON_BN_CLICKED(IDC_cmdRefresh, OncmdRefresh)
	ON_BN_CLICKED(IDC_cmdDeleteCommand, OncmdDeleteCommand)
	ON_BN_CLICKED(IDC_cmdEditCommand, OncmdEditCommand)
	ON_BN_CLICKED(IDC_cmdNewCommand, OncmdNewCommand)
	ON_BN_CLICKED(IDC_cmdFindType, OncmdFindType)
	ON_NOTIFY(LVN_KEYDOWN, IDC_lstCommands, OnKeydownlstCommands)
	ON_NOTIFY(NM_DBLCLK, IDC_lstCommands, OnDblclklstCommands)
	ON_BN_CLICKED(IDC_cmdMoveTo, OncmdMoveTo)
	ON_NOTIFY(NM_CLICK, IDC_lstHandlers, OnClicklstHandlers)
	ON_LBN_DBLCLK(IDC_lstTypes, OnDblclklstTypes)
	ON_NOTIFY(LVN_KEYDOWN, IDC_lstHandlers, OnKeydownlstHandlers)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContextEditDlg message handlers

BOOL CContextEditDlg::OnInitDialog()
{
	CRect rectClient;
	CDialog::OnInitDialog();

	// Set extended properties of the list controls
	::SendMessage(m_lstCommands.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE,
		LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE);
	::SendMessage(m_lstHandlers.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE,
		LVS_EX_FULLROWSELECT | LVS_EX_TWOCLICKACTIVATE);
	// Create the image lists for the list controls.
	m_imgCheck.Create(IDB_CHECKBOXES, 16, 4, 0x0000FF00);
	m_imgState.Create(IDB_LIST_ICONS, 32, 2, 0x0000FF00);
	// Attach the image lists to the controls.
	m_lstCommands.SetImageList(&m_imgCheck, LVSIL_SMALL);
	m_lstCommands.SetImageList(&m_imgState, LVSIL_STATE);
	m_lstHandlers.SetImageList(&m_imgCheck, LVSIL_SMALL);
	// Tell the command list control to use callbacks for state information.
	m_lstCommands.SetCallbackMask(LVIS_STATEIMAGEMASK);
	// Create list control columns.
	m_lstCommands.InsertColumn(0, "Internal Name", LVCFMT_LEFT, 100, 0);
	m_lstCommands.InsertColumn(1, "Menu Text", LVCFMT_LEFT, 100, 1);
	m_lstHandlers.InsertColumn(0, "Friendly Name", LVCFMT_LEFT, 100, 0);
	m_lstHandlers.InsertColumn(1, "Internal Name", LVCFMT_LEFT, 100, 1);
	m_lstHandlers.InsertColumn(2, "Code Module", LVCFMT_LEFT, 100, 2);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// Try to create the tool tip control object.
	m_pToolTip = new CToolTipCtrl;
	if (m_pToolTip != NULL)
	{
		// Initialize the tooltip control.
		if (m_pToolTip->Create(this))
		{
			// Add dialog controls and their associated text to the tooltip control.
			m_pToolTip->AddTool(&m_lstTypes, "Shows the extensions and file types defined on your system. The rest of this dialog is filled in based on your current selection in this list.");
			m_pToolTip->AddTool(&m_cmdFindType, "Locates and selects the master file type to which this extension is linked. You can also locate an extension's master file type (if there is one) by double-clicking that extension.");
			m_pToolTip->AddTool(&m_cmdRefresh, "Reloads the file type list with current information. Use this command whenever you think that your system's file associations may have been changed by another program while ContextEdit is running.");
			m_pToolTip->AddTool(&m_cmdSetDefault, "Sets the currently selected command as the default for this file type. Windows does not require you to set an explicit default command, but doing so will ensure that Explorer will always carry out the desired action when you double-click a file of this type.");
			m_pToolTip->AddTool(&m_cmdNewCommand, "Create a new shell command for the current extension or file type.");
			m_pToolTip->AddTool(&m_cmdEditCommand, "Edit the currently selected shell command. You may also edit a command by selecting it in the list and pressing Enter or by double-clicking its name.");
			m_pToolTip->AddTool(&m_cmdDeleteCommand, "Delete the currently selected shell command. You may also delete a command by selecting it in the list and pressing Del. Since this action cannot be undone, you will be asked for confirmation before the command is deleted.");
			m_pToolTip->AddTool(&m_cmdMoveTo, "Moves all commands from this extension to its associated master file type.");
			m_pToolTip->AddTool(&m_cmbExtensions, "Shows the file extensions (if any) that are associated with the current file type.");
			// Use callbacks for the list controls so we can provide text
			// based on what part of the list the user is pointing to.
			m_pToolTip->AddTool(&m_lstCommands, LPSTR_TEXTCALLBACK);
			m_pToolTip->AddTool(&m_lstHandlers, LPSTR_TEXTCALLBACK);
			m_pToolTip->AddTool(&m_cmdAbout, "Display ContextEdit's version and copyright information.");
			m_pToolTip->AddTool(&m_cmdHelp, "Display on-line help for this program. Help is available for all of ContextEdit's dialogs by either clicking the Help button or pressing the F1 key.");
			m_pToolTip->AddTool(&m_cmdOK, "Click this button (or press Esc) to exit the program.");
			// Set maximum tooltip width to half the width of the client area.
			GetClientRect(rectClient);
			m_pToolTip->SetMaxTipWidth(rectClient.Width() / 2);
			// Activate the tooltips.
			m_pToolTip->Activate(TRUE);
		}
	}
	// Initialize the file type list.
	BuildTypeList();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CContextEditDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

void CContextEditDlg::OnSize(UINT nType, int cx, int cy) 
{
	CRect	rectClient,
			rectList,
			rectWork,
			rectWork2,
			rectWork3,
			rectWork4,
			rectWork5;
	int		iMidpoint,
			iLeftMargin,
			iTopMargin,
			iVertMidpoint;

	// Call parent class to set client area.
	CDialog::OnSize(nType, cx, cy);
	// Nothing to do if we're minimized.
	if (IsIconic())
		return;
	// Nothing else to do if controls don't exist yet.
	if (m_lblCommands.m_hWnd == NULL)
		return;
	// Get size of client area.
	GetClientRect(&rectClient);
	// If the tooltip control exists,
	if (m_pToolTip != NULL)
		// Set the maximum with to half the width of the client area.
		m_pToolTip->SetMaxTipWidth(rectClient.Width() / 2);
	// Get other rectangles & dimensions
	m_lblExtensions.GetWindowRect(&rectWork);
	ScreenToClient(&rectWork);
	iTopMargin = rectWork.top;
	m_cmdOK.GetWindowRect(&rectWork);
	m_lstTypes.GetWindowRect(&rectList);
	ScreenToClient(&rectList);
	// Horizonatl "midpoint" is just a bit over 1/3 the width of the client area.
	iMidpoint = (rectClient.Width() / 3) + 20;
	iLeftMargin = rectList.left;
	// "Internal" static label
	m_lblInternal.GetWindowRect(&rectWork);
	ScreenToClient(&rectWork);
	// Moves to the right of the midpoint, stays in same vertical position.
	rectWork.OffsetRect(iMidpoint + 4 - rectWork.left, 0);
	m_lblInternal.MoveWindow(rectWork);
	// "Internal name" static label
	m_lblInternalName.GetWindowRect(&rectWork2);
	ScreenToClient(&rectWork2);
	// Moves 2 pixels to the right of the right edge of the "Internal" label.
	rectWork2.OffsetRect(rectWork.right + 2 - rectWork2.left, 0);
	m_lblInternalName.MoveWindow(rectWork2);
	// "Extensions" combo box
	m_cmbExtensions.GetWindowRect(&rectWork);
	ScreenToClient(&rectWork);
	// Moves to the right margin.
	rectWork.OffsetRect(rectClient.right - iLeftMargin - rectWork.right, 0);
	m_cmbExtensions.MoveWindow(rectWork);
	// "Extensions" label.
	m_lblExtensions.GetWindowRect(&rectWork2);
	ScreenToClient(&rectWork2);
	// Move its right edge 2 pixels to the left of the combo box.
	rectWork2.OffsetRect(rectWork.left - 2 - rectWork2.Width() - rectWork2.left, 0);
	m_lblExtensions.MoveWindow(rectWork2);
	// Refresh button
	m_cmdRefresh.GetWindowRect(&rectWork);
	ScreenToClient(&rectWork);
	// Moves to bottom left corner of client area.
	rectWork.OffsetRect(0, rectClient.bottom - iTopMargin - rectWork.bottom);
	m_cmdRefresh.MoveWindow(rectWork);
	// "Find Master File Type" button.
	m_cmdFindType.GetWindowRect(&rectWork);
	ScreenToClient(&rectWork);
	// Moves to bottom of client area with its right edge to the left of the midpoint.
	rectWork.OffsetRect(iMidpoint - 4 - rectWork.right, rectClient.bottom - iTopMargin - rectWork.bottom);
	m_cmdFindType.MoveWindow(rectWork);
	// "File Type" list.
	// Right edge aligned with right edge of "Find..." button.
	rectList.right = rectWork.right;
	// Bottom edge 8 pixes above the top edge of the "Find..." button.
	rectList.bottom = rectWork.top - 8;
	m_lstTypes.MoveWindow(rectList);
	// Calculate midpoint for the right-hand side of the dialog.
	iVertMidpoint = (rectList.Height() / 2) + rectList.top + 10;
	// "Commands" label
	m_lblCommands.GetWindowRect(rectWork);
	ScreenToClient(rectWork);
	// Moves to the right of the midpoint horizontally, stays in place vertically.
	rectWork.OffsetRect(iMidpoint + 4 - rectWork.left, 0);
	m_lblCommands.MoveWindow(rectWork);
	// "Set Default" button.
	m_cmdSetDefault.GetWindowRect(rectWork2);
	ScreenToClient(rectWork2);
	// Align bottom edge with vertical midpoint, left edge to the right of the horizontal midpoint.
	rectWork2.OffsetRect(rectWork.left - rectWork2.left, iVertMidpoint - rectWork2.bottom);
	m_cmdSetDefault.MoveWindow(rectWork2);
	// "Move to...." button
	m_cmdMoveTo.GetWindowRect(rectWork3);
	ScreenToClient(rectWork3);
	// Move to the right of the client area, bottom edge at vertical midpoint.
	rectWork3.OffsetRect(rectClient.right - iLeftMargin - rectWork3.right, iVertMidpoint - rectWork3.bottom);
	m_cmdMoveTo.MoveWindow(rectWork3);
	// "New" button
	m_cmdNewCommand.GetWindowRect(rectWork4);
	ScreenToClient(rectWork4);
	// Center it between the "Set Default" and "Move to..." buttons.
	rectWork4.OffsetRect(rectWork2.right + ((rectWork3.left - rectWork2.right) / 2) - (rectWork4.Width() / 2) - rectWork4.left, iVertMidpoint - rectWork4.bottom);
	m_cmdNewCommand.MoveWindow(rectWork4);
	// "Edit" button goes 8 pixels to the left of the "New" button.
	rectWork5 = rectWork4;
	rectWork5.OffsetRect(-(rectWork4.Width() + 8), 0);
	m_cmdEditCommand.MoveWindow(rectWork5);
	// "Delete" button goes 8 pixels to the right of the "New" button.
	rectWork5 = rectWork4;
	rectWork5.OffsetRect(rectWork4.Width() + 8, 0);
	m_cmdDeleteCommand.MoveWindow(rectWork5);
	// "Shell Commands" list.
	m_lstCommands.GetWindowRect(rectWork2);
	ScreenToClient(rectWork2);
	// Left edge aligned with the "Command" label.
	rectWork2.left = iMidpoint + 4;
	// Right edge at the right margin.
	rectWork2.right = rectClient.right - iLeftMargin;
	// Bottom edge 8 pixels above the buttons.
	rectWork2.bottom = rectWork3.top - 8;
	m_lstCommands.MoveWindow(rectWork2);
	// "Context Menu Handlers" label
	m_lblHandlers.GetWindowRect(rectWork);
	ScreenToClient(rectWork);
	// Moves to the right of the horizonatl midpoint and just below the vertical midpoint.
	rectWork.OffsetRect(iMidpoint + 4 - rectWork.left, iVertMidpoint + 4 - rectWork.top);
	m_lblHandlers.MoveWindow(rectWork);
	// Save top edge of Context Menu Handlers list box.
	rectWork5.top = rectWork.bottom + 4;
	// "About" button
	m_cmdAbout.GetWindowRect(rectWork);
	ScreenToClient(rectWork);
	// To the right of the horizontal midpoint, at bottom of client area.
	rectWork.OffsetRect(iMidpoint + 4 - rectWork.left, rectClient.bottom - iTopMargin - rectWork.bottom);
	m_cmdAbout.MoveWindow(rectWork);
	// Save bottom edge of Context Menu Handlers list.
	rectWork5.bottom = rectWork.top - 8;
	// "Exit" button
	m_cmdOK.GetWindowRect(rectWork2);
	ScreenToClient(rectWork2);
	// Moves to bottom right corner of client area.
	rectWork2.OffsetRect(rectClient.right - iLeftMargin - rectWork2.right, rectClient.bottom - iTopMargin - rectWork2.bottom);
	m_cmdOK.MoveWindow(rectWork2);
	// "Help" button
	m_cmdHelp.GetWindowRect(rectWork3);
	ScreenToClient(rectWork3);
	// Centered between the "About" and "Exit" buttons
	rectWork3.OffsetRect(rectWork.right + ((rectWork2.left - rectWork.right) / 2) - (rectWork3.Width() / 2) - rectWork3.left,  rectClient.bottom - iTopMargin - rectWork3.bottom);
	m_cmdHelp.MoveWindow(rectWork3);
	// Set left & right edges of ContextMenuHandlers list.
	rectWork5.left = iMidpoint + 4;
	rectWork5.right = rectClient.right - iLeftMargin;
	m_lstHandlers.MoveWindow(rectWork5);
	// Force redraw to clean up "scraps" left over from moving static labels around.
	InvalidateRect(NULL);
}

// Set minimum allowable window size.
void CContextEditDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMinTrackSize.x = 600;
	lpMMI->ptMinTrackSize.y = 360;
	
	CDialog::OnGetMinMaxInfo(lpMMI);
}

// This override is required for tooltip processing.
BOOL CContextEditDlg::PreTranslateMessage(MSG* pMsg) 
{
	// If the tooltip control exists,
	if (m_pToolTip != NULL)
		// Make sure it sees the message.
		m_pToolTip->RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

//////////////////////////////////
// Control notification handlers.

// Callback for command list text and icons.
void CContextEditDlg::OnGetdispinfolstCommands(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem = &pDispInfo->item;
	PSHELLCOMMAND pCommand = (PSHELLCOMMAND) pItem->lParam;
	// TODO: Add your control notification handler code here
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		if (pItem->mask & LVIF_TEXT)
		{
			pItem->pszText = (char *) (LPCTSTR) pCommand->strCommand;
		}
		if (pItem->mask & LVIF_IMAGE)
		{
			pItem->iImage = pCommand->bIsEnabled ? 2 : 1;
		}
		if (pItem->mask & LVIF_STATE)
		{
			pItem->state |= INDEXTOSTATEIMAGEMASK(pCommand->bIsDefault ? 2 : 1);
		}
		break;
	case 1:
		if (pItem->mask & LVIF_TEXT)
		{
			// If menu text is not specified,
			if (pCommand->strMenuText.IsEmpty())
			{
				// Check for pre-defined commands.
				if (pCommand->strCommand.CompareNoCase("open") == 0 ||
					pCommand->strCommand.CompareNoCase("print") == 0 || 
					pCommand->strCommand.CompareNoCase("printto") == 0 || 
					pCommand->strCommand.CompareNoCase("openas") == 0)
					pItem->pszText = pszSysDefault;
				else
					pItem->pszText = pszUndefined;
			}
			else
			{
				pItem->pszText = (char *) (LPCTSTR) pCommand->strMenuText;
			}
		}
		break;
	}
	*pResult = 0;
}

// Callback for handler list text and icons.
void CContextEditDlg::OnGetdispinfolstHandlers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem = &pDispInfo->item;
	PSHELLEXT pShell = (PSHELLEXT) pItem->lParam;
	// TODO: Add your control notification handler code here
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		if (pItem->mask & LVIF_TEXT)
		{
			pItem->pszText = (char *) (LPCTSTR) pShell->strFriendly;
		}
		if (pItem->mask & LVIF_IMAGE)
		{
			pItem->iImage = pShell->bEnabled ? 2 : 1;
		}
		break;
	case 1:
		if (pItem->mask & LVIF_TEXT)
		{
			pItem->pszText = (char *) (LPCTSTR) pShell->strKeyName;
		}
		break;
	case 2:
		if (pItem->mask & LVIF_TEXT)
		{
			pItem->pszText = (char *) (LPCTSTR) pShell->strModuleName;
		}
	}
	*pResult = 0;
}

// Handles selection change in the Command list.
// Note: Since our list control only allows a single selection,
// when the user selects a different item the list control automatically
// forces all other items in the list to be deselected first.
// Therefore, the last state change notification we receive will
// be for the new item becoming selected.
void CContextEditDlg::OnItemchangedlstCommands(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	PSHELLCOMMAND pCommand;

	pCommand = (PSHELLCOMMAND) pNMListView->lParam;
	// Was the change to the item's state?
	if (pNMListView->uChanged & LVIF_STATE)
	{
		// Yes .. Has the item has become selected?
		if (pNMListView->uNewState & LVIS_SELECTED)
		{
			// Yes .. Enable command buttons accordingly.
			// "Set Default" button is enabled only if an enabled command
			// is selected and it is not already the default command.
			m_cmdSetDefault.EnableWindow(!(pCommand->bIsDefault || !pCommand->bIsEnabled));
			// "Edit" and "Delete" buttons are always available when an
			// item is selected.
			m_cmdEditCommand.EnableWindow(TRUE);
			m_cmdDeleteCommand.EnableWindow(TRUE);
		}
		else
		{
			// No .. the item has become deselected.
			// Was this item previously selected?
			// Note: This test prevents us from disabling the buttons
			// repeatedly for each non-selected item in the list.
			if (pNMListView->uOldState & LVIS_SELECTED)
			{
				// Yes .. Disable all buttons except "New".
				m_cmdSetDefault.EnableWindow(FALSE);
				m_cmdEditCommand.EnableWindow(FALSE);
				m_cmdDeleteCommand.EnableWindow(FALSE);
			}
		}
	}
	*pResult = 0;
}

// Handles selection change in the file type list.
void CContextEditDlg::OnSelchangelstTypes() 
{
	int			i,
				iIndex;
	HKEY		hKey;
	BOOL		bAdded;
	LVITEM		lvi;
	LRESULT		lResult;
	PFTELEMENT	pThis,
				pThat;
	CWarnBroken dlgWarn;
	CChooseType dlgChoose;

	// Get pointer to current file type entry.
	iIndex = m_lstTypes.GetCurSel();
	pThis = (PFTELEMENT) m_lstTypes.GetItemDataPtr(iIndex);
	// Reset the drop list and list controls.
	m_cmbExtensions.ResetContent();
	m_lstCommands.DeleteAllItems();
	m_lstHandlers.DeleteAllItems();
	// Build array of context menu handlers for this file type.
	theApp.GetMenuHandlers(pThis->strType);
	// Build array of shell commands for this file type
	theApp.GetMenuCommands(pThis->strType);
	// If there are any handlers,
	if (theApp.m_intExtArrayCount > 0)
	{
		// Populate the Context Menu Handler list.
		// We'll be supplying text, image, and parameter data.
		lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		// Use callbacks for text and image.
		lvi.pszText = LPSTR_TEXTCALLBACK;
		lvi.iImage = I_IMAGECALLBACK;
		// We're inserting a "base" item.
		lvi.iSubItem = 0;
		for (i = 0; i < theApp.m_intExtArrayCount; i++)
		{
			// Insertion point == array index.
			lvi.iItem = i;
			// Parameter == pointer to handler array item.
			lvi.lParam = (LPARAM) theApp.m_pShellExtArray[i];
			m_lstHandlers.InsertItem(&lvi);
		}
		// Make sure the first item in the list is selected.
		lvi.iItem = 0;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_STATE;
		lvi.stateMask = LVIS_SELECTED;
		lvi.state = LVIS_SELECTED;
		m_lstHandlers.SetItem(&lvi);
	}
	// If there are any commands,
	if (theApp.m_intShellCommandCount > 0)
	{
		// Populate the Shell Commands list.
		lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lvi.pszText = LPSTR_TEXTCALLBACK;
		lvi.iImage = I_IMAGECALLBACK;
		lvi.iSubItem = 0;
		for (i = 0; i < theApp.m_intShellCommandCount; i++)
		{
			lvi.iItem = i;
			lvi.lParam = (LPARAM) theApp.m_pShellCommands[i];
			m_lstCommands.InsertItem(&lvi);
		}
		lvi.iItem = 0;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_STATE;
		lvi.stateMask = LVIS_SELECTED;
		lvi.state = LVIS_SELECTED;
		m_lstCommands.SetItem(&lvi);
	}
	// Populate the "Extensions" drop-list.
	bAdded = FALSE;
	if (pThis->bIsExt)
	{
		// If this is an extension key, just add the extension.
		m_cmbExtensions.AddString(pThis->strType.Mid(1));
		bAdded = TRUE;
	}
	else
	{
		// Otherwise, search the file type array.
		for (i = 0; i < theApp.m_intTypeArrayCount; i++)
		{
			// Get pointer to array element.
			pThat = theApp.m_pFileTypeArray[i];
			// If it's the current element, skip it.
			if (pThis == pThat)
				continue;
			// If it's not an extension key, skip it.
			if (!pThat->bIsExt)
				continue;
			// If its master file type is the same as the current type,
			if (pThis->strType.CompareNoCase(pThat->strFriendly) == 0)
			{
				// Strip the leading "." and add the extension to the list.
				m_cmbExtensions.AddString(pThat->strType.Mid(1));
				bAdded = TRUE;
			}
		}
	}
	// If any items were added to the extension list,
	if (bAdded)
		// make sure the first one is selected.
		m_cmbExtensions.SetCurSel(0);
	// Enable/disable remaining controls accordingly.
	SetButtonStatus();
	// If warning has not been disabled,
	if (m_bWarnBroken)
	{
		// If current type is an extension key that is broken and
		// not a "system" file type,
		if (pThis->bIsExt && pThis->bIsBroken && !pThis->bIsSystemType)
		{
			// Warn user about the broken association & let him decide
			// what (if anything) to do about it.
			// Did the user acknowledge the dialog with "OK"?
			dlgWarn.m_pFileType = pThis;
			if (dlgWarn.DoModal() == IDOK)
			{
				// Yes .. branch based on the option chosen.
				switch (dlgWarn.m_intRepair)
				{
				case 0:	// Remove the link to the non-existent master file type.
					// Open the extension key.
					lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, pThis->strType, 0, KEY_SET_VALUE, &hKey);
					if (lResult == ERROR_SUCCESS)
					{
						// Delete its (default) value.
						lResult = RegDeleteValue(hKey, NULL);
						RegCloseKey(hKey);
						if (lResult == ERROR_SUCCESS)
						{
							// Update file type element.
							pThis->strFriendly.Empty();
							pThis->bIsBroken = FALSE;
						}
					}
					if (lResult == ERROR_SUCCESS)
					{
						// Update dialog controls.
						m_cmdFindType.EnableWindow(FALSE);
						m_cmdMoveTo.EnableWindow(FALSE);
					}
					else
					{
						ReportRegError();
					}
					break;
				case 1:	// Choose a valid type and link this extension key to it.
					if (dlgChoose.DoModal() != IDOK)
						break;
					pThat = dlgChoose.m_pChosenType;
					lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, pThis->strType, 0, KEY_SET_VALUE, &hKey);
					if (lResult == ERROR_SUCCESS)
					{
						// Link to the chosen file type
						lResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) pThat->strType, pThat->strType.GetLength() + 1);
						RegCloseKey(hKey);
						if (lResult == ERROR_SUCCESS)
						{
							// Update file type element.
							pThis->strFriendly = pThat->strType;
							pThis->bIsBroken = FALSE;
						}
					}
					if (lResult == ERROR_SUCCESS)
					{
						m_cmdFindType.EnableWindow(TRUE);
						m_cmdMoveTo.EnableWindow(theApp.m_intShellCommandCount > 0);
					}
					else
					{
						ReportRegError();
					}
					break;
				case 2:	// Delete the extension key altogether.
					// Ask for confirmation first.
					if (AfxMessageBox("This operation cannot be undone.\n"
						"Are you sure you wish to delete this extension key?",
						MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
						break;
					// Try to remove the key from the registry.
					if (RegZapKey(HKEY_CLASSES_ROOT, pThis->strType))
					{
						// If key was deleted from the registry,
						// delete the string from the list box.
						m_lstTypes.DeleteString(iIndex);
						// Delete the type entry from the file type array.
						theApp.DeleteFileType(pThis);
						// Adjust the list index if needed.
						if (iIndex >= m_lstTypes.GetCount())
							--iIndex;
						// Set selection to the item following the one we just deleted.
						m_lstTypes.SetCurSel(iIndex);
						// Listbox doesn't notify us when its selection is forced, so we have to call it directly.
						OnSelchangelstTypes();
					}
					else
						ReportRegError();
					break;
				case 3:	// Do nothing.
					break;
				case 4:	// Do nothing and disable further warnings.
					m_bWarnBroken = FALSE;
				}
			}
		}
	}
}

void CContextEditDlg::OnClicklstCommands(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	UINT flags;
	int iItem;

	*pResult = 0;
	GetCursorPos(&point);
	m_lstCommands.ScreenToClient(&point);
	iItem = m_lstCommands.HitTest(point, &flags);
	if (flags == LVHT_ONITEMICON)
	{
		ToggleCommand(iItem);
	}
}

// Handles keystoke input for the Context Menu Hanlders list.
void CContextEditDlg::OnKeydownlstHandlers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int				iItem;
	BOOL			bGotItem = FALSE;
	POSITION		pos;
	NMLVKEYDOWN		*pLVKeyDown = (NMLVKEYDOWN*)pNMHDR;

	// If key pressed was the spacebar,
	if (pLVKeyDown->wVKey == VK_SPACE)	// Branch based on keystroke.
	{
		// Find the first (and only) selected item.
		pos = m_lstCommands.GetFirstSelectedItemPosition();
		if (pos != NULL)			// If there is an item selected,
		{
			// Get its index.
			iItem = m_lstCommands.GetNextSelectedItem(pos);
			// Toggle the associated handler.
			ToggleHandler(iItem);
		}
		else	// No item selected
		{
			// Just make a default beep.
			MessageBeep(MB_OK);
		}
	}
	*pResult = 0;
}

// Handles keyboard input for the Shell Commands list.
void CContextEditDlg::OnKeydownlstCommands(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int				iItem;
	BOOL			bGotItem = FALSE;
	POSITION		pos;
	LV_KEYDOWN		*pLVKeyDown = (LV_KEYDOWN*)pNMHDR;

	// Find the first (and only) selected item.
	pos = m_lstCommands.GetFirstSelectedItemPosition();
	if (pos != NULL)			// If there is an item selected,
	{
		// Get its index.
		iItem = m_lstCommands.GetNextSelectedItem(pos);
		bGotItem = TRUE;
	}
	switch (pLVKeyDown->wVKey)	// Branch based on keystroke.
	{
	case VK_SPACE:		// Spacebar -- toggle current command.
		if (bGotItem)
			ToggleCommand(iItem);
		else
			MessageBeep(MB_OK);
		break;
	case VK_DELETE:		// Del -- delete current command.
		if (bGotItem)
			OncmdDeleteCommand();
		else
			MessageBeep(MB_OK);
		break;
	case VK_RETURN:		// Enter -- edit current commmand.
		if (bGotItem)
			OncmdEditCommand();
		else
			MessageBeep(MB_OK);
		break;
	}
	*pResult = 0;
}

// Handle mouse clicks in the Context Menu Handler list.
void CContextEditDlg::OnClicklstHandlers(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int		iItem;
	UINT	flags;
	CPoint	point;

	// Get the mouse position.
	GetCursorPos(&point);
	// Convert to client coordinates.
	m_lstHandlers.ScreenToClient(&point);
	// See where in the control it was.
	iItem = m_lstHandlers.HitTest(point, &flags);
	// If it was on the item icon,
	if (flags == LVHT_ONITEMICON)
	{
		// Toggle the corresponding handler.
		ToggleHandler(iItem);
	}
	*pResult = 0;
}

// Handle double-click in the File Type list.
void CContextEditDlg::OnDblclklstTypes() 
{
	PFTELEMENT pType;

	// Get pointer to the type that was clicked.
	pType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// If it's an extension key,
	if (pType->bIsExt)
		// Try to locate its master file type.
		OncmdFindType();
}

// Handles TTN_NEEDTEXT notification from the ToolTip contrl.
// Used to provides tooltip text for the list controls.
// Note that for this notification message, the "id" and "pResult" parameters are not used.
BOOL CContextEditDlg::OnNeedText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult )
{
	int				iItem,
					iColLeft,
					iColRight;
	UINT			nID;
	TOOLTIPTEXT		*pTTT = (TOOLTIPTEXT *) pTTTStruct;
	LVHITTESTINFO	lvht;

	// Get the control identifier.
	nID = pTTTStruct->idFrom;
	// If the identifier is the controls HWND,
	if (pTTT->uFlags & TTF_IDISHWND)
		// Get its control ID.
		nID = ::GetDlgCtrlID((HWND)nID);

	// If it's the Shell Command List,
	if (nID == IDC_lstCommands)
	{
		// Get position of the mouse pointer.
		::GetCursorPos(&lvht.pt);
		// Convert to client coordinates relative to the list control.
		m_lstCommands.ScreenToClient(&lvht.pt);
		// See where in the control the user is pointing.
		iItem = m_lstCommands.HitTest(&lvht);
		// Pointing at the state icon (the "default" indicator).
		if (lvht.flags == LVHT_ONITEMSTATEICON)
			pTTT->lpszText = "This column indicates which command (if any) is the default "
								"command for this file type.";
		// Pointing at the item icon (the checkbox).
		else if (lvht.flags == LVHT_ONITEMICON)
			pTTT->lpszText = "This checkbox indicates whether or not a command is enabled. "
							"To enable (or disable) a command, set (or clear) its checkbox "
							"with either the mouse or the spacebar.";
		// Pointing at the first column.
		else if (lvht.flags == LVHT_ONITEMLABEL)
			pTTT->lpszText = "This column indicates the internal name for this command. "
							"If to edit this command, double-click this name.";
		else
		{
			// See if he's pointing at the first sub-item (the second colun).
			iItem = m_lstCommands.SubItemHitTest(&lvht);
			if (lvht.iSubItem == 1)
				pTTT->lpszText = "This column shows the menu text for this command. "
								"<Undefined> means that there is no menu text specified. "
								"<System Default> means Explorer is providing default "
								"menu text based on the commmand's internal name.";
			else
				pTTT->lpszText = "This list shows the shell commands defined for the current file type.";
		}
		// Since we're providing explicit text and not a string resource,
		// set the instance handle to NULL.
		pTTT->hinst = NULL;
		return TRUE;
	}
	// User is pointing at the Context Menu Handler list.
	else if (nID == IDC_lstHandlers)
	{
		// Set default tooltip text for this list.
		pTTT->lpszText = "This list shows the context menu handers for the current file type. "
						"To enable (or disable) a handler, set (or clear) its check box with "
						"either the mouse or the spacebar.";
		// Get the mouse position.
		::GetCursorPos(&lvht.pt);
		// Convert to client coordinates relative to the list control.
		m_lstHandlers.ScreenToClient(&lvht.pt);
		// See where the pointer is within the control
		iItem = m_lstHandlers.HitTest(&lvht);
		// User is pointing at the checkbox icon.
		if (lvht.flags == LVHT_ONITEMICON)
			pTTT->lpszText = "This checkbox indicates whether or not a handler is enabled. "
							"To enable (or disable) a handler, set (or clear) its checkbox "
							"with either the mouse or the spacebar.";
		// User is pointing at an item in the first column.
		else if (lvht.flags == LVHT_ONITEMLABEL)
			pTTT->lpszText = "This column indicates the \"friendly\" name for this handler, "
							"which may help you determine which menu commands it provides.";
		else
		{
			// See if user is pointing at the first sub-item (the second column).
			// Note: For some reason, this call fails to identify the third column,
			// even though it is defined as sub-item #2.
			iItem = ListView_SubItemHitTest(m_lstCommands.m_hWnd, &lvht);
			if (lvht.iSubItem == 1)
				pTTT->lpszText = "This column shows the name of the registry key for this handler.";
			else
			{
				// See if user is pointing somewhere within the 3rd column.
				iColLeft = m_lstHandlers.GetColumnWidth(0) + m_lstHandlers.GetColumnWidth(1);
				iColRight = iColLeft + m_lstHandlers.GetColumnWidth(2);
				if (lvht.pt.x >= iColLeft && lvht.pt.x <= iColRight)
					pTTT->lpszText = "This column shows the name of the executable file which contains "
									"the code that implements this handler. Locating this file in Explorer "
									"and viewing its version information may help you determine "
									"whicn commands this handler provides.";
			}
		}
		pTTT->hinst = NULL;
		return TRUE;
	}
	// User isn't pointing at either list control, so we provide no text.
	return FALSE;
}

///////////////////////////////
// Command button handlers.
void CContextEditDlg::OncmdSetDefault() 
{
	int				i,
					iCount,
					iThis;
	HKEY			hKey;
	CString			strKeyName;
	LRESULT			lResult;
	POSITION		pos;
	PFTELEMENT		pElement;
	PSHELLCOMMAND	pCommand,
					pThis;

	// Get the number of items in the list.
	iCount = m_lstCommands.GetItemCount();
	// Find the first selected item.
	// Note: List control is set to allow only a single selection.
	if ((pos = m_lstCommands.GetFirstSelectedItemPosition()) == NULL)
		return;
	// Get the item's index.
	iThis = m_lstCommands.GetNextSelectedItem(pos);
	// Get pointer to the item's command.
	pCommand = (PSHELLCOMMAND) m_lstCommands.GetItemData(iThis);
	// Get pointer to current file type.
	pElement = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// Build registry key name.
	strKeyName.Format("%s\\shell", pElement->strType);
	// Open the key.
	if ((lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, strKeyName, 0, KEY_SET_VALUE, &hKey)) == ERROR_SUCCESS)
	{
		// Set the key's (default) string to the internal name of the selected command.
		lResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) pCommand->strCommand, pCommand->strCommand.GetLength() + 1);
		RegCloseKey(hKey);
	}
	// If registry access failed,
	if (lResult != ERROR_SUCCESS)
	{
		ReportRegError();			// Report the error.
		OnSelchangelstTypes();		// Refresh the command list.
		return;						// Done.
	}
	// Mark the new default command.
	pCommand->bIsDefault = TRUE;
	// Make sure no other commands are marked as the default.
	for (i = 0; i < iCount; i++)
	{
		pThis = theApp.m_pShellCommands[i];
		if (pCommand != pThis)
			pThis->bIsDefault = FALSE;
	}
	m_lstCommands.RedrawItems(0, iCount - 1);	// Update the list.
	m_cmdSetDefault.EnableWindow(FALSE);		// Disable the Set Default button.
}

void CContextEditDlg::OncmdAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();	
}

void CContextEditDlg::OncmdRefresh() 
{
	int		iResult;

	m_lstTypes.ResetContent();
	m_lstCommands.DeleteAllItems();
	m_lstHandlers.DeleteAllItems();
	m_lstCommands.RedrawWindow();
	m_lstHandlers.RedrawWindow();
	m_cmbExtensions.ResetContent();
TryAgain:
	if (!theApp.GetFileTypes())
	{
		iResult = MessageBox("Error while reading the registry.\n"
			"This could be caused by another program modifying\n"
			"the registry while ContextEdit was trying to read it.\n"
			"Do you wish to try again?\n\n"
			"(If you answer \"No\", ContextEdit will terminate since\n"
			"any data retrieved may be incomplete or inaccurate.)",
			"ContextEdit", MB_ICONQUESTION | MB_YESNO);
		if (iResult == IDYES)
			goto TryAgain;
		EndDialog(IDOK);
		return;
	}
	BuildTypeList();
}

void CContextEditDlg::OncmdDeleteCommand() 
{
	int iItem, iCount;
	POSITION pos;
	PSHELLCOMMAND pCommand;
	PFTELEMENT pType;
	CString strKey, strPrompt;

	// Get index of the selected item.
	pos = m_lstCommands.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		iItem = m_lstCommands.GetNextSelectedItem(pos);
	}
	else
	{
		AfxMessageBox("Internal error!");
		return;
	}
	// Get pointer to the command.
	pCommand = (PSHELLCOMMAND) m_lstCommands.GetItemData(iItem);
	// Prompt for confirmation.
	strPrompt.Format("This operation cannot be undone!\n\n"
		"Are you sure you wish to delete the \"%s\" command?", pCommand->strCommand);
	if (AfxMessageBox(strPrompt, MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) != IDYES)
		return;
	// Get pointer to the current file type.
	pType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// Build name of the key to be removed.
	if (pCommand->bIsEnabled)
		strKey.Format("%s\\shell\\%s", pType->strType, pCommand->strCommand);
	else
		strKey.Format("%s\\-shell\\%s", pType->strType, pCommand->strCommand);
	// Delete the key.
	if (!RegZapKey(HKEY_CLASSES_ROOT, strKey))
		ReportRegError();
	else
	{
		// If the default command was deleted
		if (pCommand->bIsDefault)
		{
			// And there is at least one other command left,
			if (theApp.m_intShellCommandCount > 1)
			{
				// remind the user to select a new default.
				MessageBox("Since you have deleted the default command for this file type,\n"
					"you may wish to select a new default command to ensure that\n"
					"the proper action is taken when you launch a file of this type\n",
					"ContextEdit", MB_ICONINFORMATION);
			}
		}
	}
	// Remove the command from the list.
	m_lstCommands.DeleteItem(iItem);
	// Delete the command from the array.
	// Note: The list refers to its commands using pointers to
	// the commands themselves, not their array indices, so it
	// doesn't matter if commands change position within the array.
	theApp.DeleteShellCommand(pCommand);
	// If there are no disabled commands left,
	if (theApp.m_intDisabledCommands == 0)
	{
		// Delete our "-shell" key.
		strKey.Format("%s\\-shell", pType->strType);
		RegZapKey(HKEY_CLASSES_ROOT, strKey);
		pType->bHasDisabledCommand = FALSE;
	}
	// If there are no enabled commands left,
	if (theApp.m_intEnabledCommands == 0)
	{
		// Delete the "shell" key.
		strKey.Format("%s\\shell", pType->strType);
		RegZapKey(HKEY_CLASSES_ROOT, strKey);
		pType->bHasCommand = FALSE;
	}
	// If there are no commands left,
	if (theApp.m_intShellCommandCount == 0)
	{
		// Make sure the "Delete" and "Move To" buttons are disabled.
		m_cmdMoveTo.EnableWindow(FALSE);
		m_cmdDeleteCommand.EnableWindow(FALSE);
	}
	// Get # of items in the list.
	iCount = m_lstCommands.GetItemCount();
	// If there are any items left,
	if (iCount > 0)
	{
		// If index is beyond the end of the list,
		if (iItem >= iCount)
			// make it the last item.
			iItem = iCount - 1;
		// Select the item following the one that was deleted.
		m_lstCommands.SetItemState(iItem, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CContextEditDlg::OncmdEditCommand() 
{
	CCmdDlg dlg;
	int				iThis;
	POSITION		pos;
	PSHELLCOMMAND	pCommand;
	PFTELEMENT		pType;

	// Find the first selected item.
	// Note: List control is set to allow only a single selection.
	if ((pos = m_lstCommands.GetFirstSelectedItemPosition()) == NULL)
		return;
	// Get the item's index.
	iThis = m_lstCommands.GetNextSelectedItem(pos);
	// Get pointer to the item's command.
	pCommand = (PSHELLCOMMAND) m_lstCommands.GetItemData(iThis);
	pType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	dlg.m_strMenuText = pCommand->strMenuText;
	dlg.m_strCommandLine = pCommand->strCommandLine;
	dlg.m_strDDEexec = pCommand->strDDEexec;
	dlg.m_strDDEapp = pCommand->strDDEapp;
	dlg.m_strDDEnotrunning = pCommand->strDDEnotrunning;
	dlg.m_strDDEtopic = pCommand->strDDEtopic;
	dlg.m_bUseDDE = pCommand->bUseDDE;
	dlg.m_bMode = FALSE;
	dlg.m_strInternal = pCommand->strCommand;
	dlg.m_bExpandCmdLine = pCommand->bExpandCmdLine;
	if (dlg.DoModal() == IDOK)
	{
		pCommand->strMenuText = dlg.m_strMenuText;
		pCommand->strCommandLine = dlg.m_strCommandLine;
		pCommand->bUseDDE = dlg.m_bUseDDE;
		pCommand->strDDEexec = dlg.m_strDDEexec;
		pCommand->strDDEapp = dlg.m_strDDEapp;
		pCommand->strDDEnotrunning = dlg.m_strDDEnotrunning;
		pCommand->strDDEtopic = dlg.m_strDDEtopic;
		pCommand->bExpandCmdLine = dlg.m_bExpandCmdLine;
		if (!InstallCommand(pCommand, pType))
		{
			ReportRegError("\n\nContextEdit may not have been able to apply\n"
				"all of the changes you requested.");
			OnSelchangelstTypes();
			return;
		}
	}
	m_lstCommands.RedrawItems(iThis, iThis);
}


void CContextEditDlg::OncmdNewCommand() 
{
	int				iIndex, iCount;
	CCmdDlg			dlgEdit;
	CCmdNameDlg		dlgName;
	PSHELLCOMMAND	pCommand = NULL;
	PFTELEMENT		pType, pTarget;
	LVITEM			lvi;
	CString			strKeyName;

TryAgain:
	// Get pointer to current file type.
	pType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// Is the current type an extension?
	if (pType->bIsExt)
	{
		// Yes ... is it linked to a master file type?
		if (!pType->strFriendly.IsEmpty())
		{
			// Yes ... does the master file type exist?
			if (!pType->bIsBroken)
			{
				// Ask user what to do.
				if (AfxMessageBox(
					"The current file type is an extension key which\n"
					"is linked to a master file type. Any commands\n"
					"you add to this key will be ignored; you should\n"
					"add them to the master file type instead. If you'd\n"
					"like me to locate the master file type for you,\n"
					"click OK (or press Enter), otherwise click Cancel\n"
					"or press {Escape) to cancel this operation.",
					MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
				{
					// If he says OK, locate the master file type
					iCount = m_lstTypes.GetCount();
					for (iIndex = 0; iIndex < iCount; iIndex++)
					{
						pTarget = (PFTELEMENT) m_lstTypes.GetItemDataPtr(iIndex);
						if (pTarget->strType.CompareNoCase(pType->strFriendly) == 0)
						{
							m_lstTypes.SetCurSel(iIndex);
							OnSelchangelstTypes();
							goto TryAgain;
						}
					}
				}
				else
				{
					return;
				}
			}
		}
	}
	// Prompt user for new command name.
	if (dlgName.DoModal() != IDOK)
		return;
	// Create a new SHELLCOMMAND object.
	pCommand = new SHELLCOMMAND;
	// Set its name, enabled, and default flags.
	pCommand->strCommand = dlgName.m_strCommand;
	pCommand->bIsEnabled = TRUE;
	pCommand->bIsDefault = FALSE;
	pCommand->bExpandCmdLine = FALSE;
	// Set command editor dialog to "new" mode.
	dlgEdit.m_bMode = TRUE;
	// Give it the internal name of the command.
	dlgEdit.m_strInternal = dlgName.m_strCommand;
	// Let user edit the fields.
	if (dlgEdit.DoModal() != IDOK)
	{
		delete pCommand;
		return;
	}
	// If edit was successful, transfer values to the new element.
	pCommand->strMenuText = dlgEdit.m_strMenuText;
	pCommand->strCommandLine = dlgEdit.m_strCommandLine;
	pCommand->bUseDDE = dlgEdit.m_bUseDDE;
	pCommand->strDDEexec = dlgEdit.m_strDDEexec;
	pCommand->strDDEapp = dlgEdit.m_strDDEapp;
	pCommand->strDDEnotrunning = dlgEdit.m_strDDEnotrunning;
	pCommand->strDDEtopic = dlgEdit.m_strDDEtopic;
	pCommand->bExpandCmdLine = dlgEdit.m_bExpandCmdLine;
	// Try to add the command to the Registry.
	if (!InstallCommand(pCommand, pType))
	{
		// Failure: make sure the command key is removed.
		strKeyName.Format("%s\\shell\\%s", pType->strType, pCommand->strCommand);
		RegZapKey(HKEY_CLASSES_ROOT, strKeyName);
		delete pCommand;
		ReportRegError("\n\nYour new command was not created.");
		return;
	}
	// Since we just added a new command to this file type,
	// make sure its flag is set.
	pType->bHasCommand = TRUE;
	// Add the new command to the array.
	theApp.AddShellCommand(pCommand);
	// Add new entry to the list.
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.iImage = I_IMAGECALLBACK;
	lvi.stateMask = LVIS_SELECTED;
	lvi.state = LVIS_SELECTED;
	lvi.iSubItem = 0;
	lvi.iItem = theApp.m_intShellCommandCount - 1;
	lvi.lParam = (LPARAM) pCommand;
	m_lstCommands.InsertItem(&lvi);
}

void CContextEditDlg::OncmdFindType() 
{
	int		i, iIndex, iCount;
	CString strTarget, strPrompt;
	PFTELEMENT pElement;

	iIndex = m_lstTypes.GetCurSel();
	pElement = (PFTELEMENT) m_lstTypes.GetItemDataPtr(iIndex);
	strTarget = pElement->strFriendly;
	if (strTarget.IsEmpty())
	{
		MessageBox("This extension is not linked to a master file type", "ContextEdit", MB_ICONINFORMATION);
		return;
	}
	if (pElement->strType.CompareNoCase(pElement->strFriendly) == 0)
	{
		strPrompt.Format("This extension key is linked to itself, producing a circular reference.\n"
					"This represents a logical error in the registry which ContextEdit\n"
					"cannot repair for you.\n\n"
					"Experienced users who are familiar with the Registry Editor\n"
					"may repair this error by either deleting the\n"
					"HKEY_CLASSES_ROOT\\%s key altogether,\n"
					"or by editing its default value so that the extension key is\n"
					"linked to a valid file type key.", pElement->strType);
		MessageBox(strPrompt, "ContextEdit", MB_OK);
		return;
	}
	iCount = m_lstTypes.GetCount();
	for (i = 0; i < iCount; i++)
	{
		if (i == iIndex)
			continue;
		pElement = (PFTELEMENT) m_lstTypes.GetItemDataPtr(i);
		if (pElement->bIsExt)
			continue;
		if (pElement->strType.CompareNoCase(strTarget) == 0)
		{
			m_lstTypes.SetCurSel(i);
			m_lstTypes.SetFocus();
			OnSelchangelstTypes();
			return;
		}
	}
	strPrompt.Format("The master file type \"%s\" to which this extension\n"
		"is linked does not exist.", strTarget);
	MessageBox(strPrompt, "ContextEdit", MB_ICONINFORMATION);
	m_lstTypes.SetFocus();
}

// Special case for the {Enter} key.
void CContextEditDlg::OnOK() 
{
	if (GetFocus()->m_hWnd == m_lstCommands.m_hWnd)
		OncmdEditCommand();
	else
		CDialog::OnOK();
}

///////////////////////////////
// "Helper" functions.

// Rebuilds the file type list.
void CContextEditDlg::BuildTypeList()
{
	int			i,
				iIndex;
	PFTELEMENT	pElement;

	// Empty the file type listbox.
	m_lstTypes.ResetContent();
	// Loop through the file type array.
	for (i = 0; i < theApp.m_intTypeArrayCount; i++)
	{
		// Get pointer to current element.
		pElement = theApp.m_pFileTypeArray[i];
		// Is it an extension key?
		if (pElement->bIsExt)
		{
			// Yes .. add it to the list.
			iIndex = m_lstTypes.AddString(pElement->strType);
		}
		else
		{
			// No .. it's a file type key.
			// Check for special file type keys
			if (pElement->strType == "*")
				iIndex = m_lstTypes.AddString("* All files, regardless of extension");
			else if (pElement->strType.CompareNoCase("Unknown") == 0)
				iIndex = m_lstTypes.AddString("* All unassociated extensions");
			// Not a special file type, does it have a friendly name?
			else if (pElement->strFriendly.IsEmpty())
				// No, put its key name in the list.
				iIndex = m_lstTypes.AddString(pElement->strType);
			else
				// Yes, put its friendly name in the list.
				iIndex = m_lstTypes.AddString(pElement->strFriendly);
		}
		// Give listbox item a copy of the array pointer.
		m_lstTypes.SetItemDataPtr(iIndex, pElement);
	}
	// Make sure the first item is selected.
	m_lstTypes.SetCurSel(0);
	// Ensure that other controls and fields are set accordingly.
	// (The SetCurSel member function does not fire an OnSelchange event)
	OnSelchangelstTypes();
}

// Generic "gagged on the registry" error message.
void CContextEditDlg::ReportRegError(LPCTSTR strExtraText)
{
	CString strPrompt("Error accessing the registry.");

	if (strExtraText != NULL)
	{
		strPrompt += strExtraText;
	}
	AfxMessageBox(strPrompt, MB_ICONSTOP);
}

// Toggle the enabled/disabled status of a command.
void CContextEditDlg::ToggleCommand(int iItem)
{
	BOOL			bResult;
	HKEY			hKey;
	CString			strEnabled,
					strDisabled,
					strNewName;
	LRESULT			lResult;
	PFTELEMENT		pType;
	PSHELLCOMMAND	pThisCommand;

	// Get pointer to the command.
	pThisCommand = (PSHELLCOMMAND) m_lstCommands.GetItemData(iItem);
	// Get pointer to the current file type.
	pType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// Build subkey names for enabled/disabled commands.
	// Check for internal name conflict.
	if (theApp.CommandExists(pThisCommand->strCommand, pThisCommand->bIsEnabled ? 1 : 0))
	{
		// Create a new internal name.
		theApp.GenerateCommandName(pThisCommand->strCommand, strNewName);
		// Build registry key names based on whether we're enabling or disabling this command.
		if (pThisCommand->bIsEnabled)
		{
			// If command is to be disabled, the new name is for the -shell subkey.
			strEnabled.Format("%s\\shell\\%s", pType->strType, pThisCommand->strCommand);
			strDisabled.Format("%s\\-shell\\%s", pType->strType, strNewName);
		}
		else
		{
			// If command is being enabled, new name is for its shell subkey.
			strEnabled.Format("%s\\shell\\%s", pType->strType, strNewName);
			strDisabled.Format("%s\\-shell\\%s", pType->strType, pThisCommand->strCommand);
		}
	}
	else
	{
		// If there's no name conflict, both shell and -shell subkeys will have the same name.
		strEnabled.Format("%s\\shell\\%s", pType->strType, pThisCommand->strCommand);
		strDisabled.Format("%s\\-shell\\%s", pType->strType, pThisCommand->strCommand);
		// Command name has not changed.
		strNewName = pThisCommand->strCommand;
	}
	// Is command currently enabled?
	if (pThisCommand->bIsEnabled)
		// Move its key from enabled to disabled status.
		bResult = RegMoveKey(HKEY_CLASSES_ROOT, strDisabled, HKEY_CLASSES_ROOT, strEnabled);
	else
		// Otherwise move its key from disabled to enabled status.
		bResult = RegMoveKey(HKEY_CLASSES_ROOT, strEnabled, HKEY_CLASSES_ROOT, strDisabled);
	if (bResult)	// If the key move was successful,
	{
		// Update the command's status.
		pThisCommand->bIsEnabled = !pThisCommand->bIsEnabled;
		// Update the command's internal name, just in case we had to rename it.
		pThisCommand->strCommand = strNewName;
		// Update enabled/disabled command counts.
		if (pThisCommand->bIsEnabled)
		{
			++theApp.m_intEnabledCommands;
			--theApp.m_intDisabledCommands;
		}
		else
		{
			++theApp.m_intDisabledCommands;
			--theApp.m_intEnabledCommands;
		}
		// Handle special case when the default command is disabled
		if (!pThisCommand->bIsEnabled && pThisCommand->bIsDefault)
		{
			strEnabled.Format("%s\\shell", pType->strType);
			// Clear the default command string so it doesn't point to a non-existent command.
			lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, strEnabled, 0, KEY_WRITE, &hKey);
			if (lResult == ERROR_SUCCESS)
			{
				lResult = RegDeleteValue(hKey, NULL);
				RegCloseKey(hKey);
			}
			// Clear the command's "default" flag.
			pThisCommand->bIsDefault = FALSE;
			// If there are at least two enabled commands remaining,
			if (theApp.m_intEnabledCommands > 1)
			{
				// Remind user to select a new default command.
				MessageBox("Since you have disabled the default command for this file type,\n"
					"you may wish to select a new default command to ensure that\n"
					"the proper action is taken when you launch a file of this type\n",
					"ContextEdit", MB_ICONINFORMATION);
			}
		}
		if (theApp.m_intDisabledCommands == 0)	// If there are no disabled commands left,
		{
			// Remove our "-shell" key.
			strEnabled.Format("%s\\-shell", pType->strType);
			// Note: if removal fails, it's not a critical error.
			RegZapKey(HKEY_CLASSES_ROOT, strEnabled);
		}
		// Enable/Disable the "Set Default" button accordingly.
		m_cmdSetDefault.EnableWindow(!pThisCommand->bIsDefault && pThisCommand->bIsEnabled);
		// Redraw the list entry.
		m_lstCommands.RedrawItems(iItem, iItem);
	}
	else
	{
		// Otherwise, report the error.
		ReportRegError();
	}
}

void CContextEditDlg::OnDblclklstCommands(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	UINT flags;
	int iItem;

	GetCursorPos(&point);
	m_lstCommands.ScreenToClient(&point);
	iItem = m_lstCommands.HitTest(point, &flags);
	if ((flags & LVHT_ONITEMLABEL) != 0)
	{
		OncmdEditCommand();
	}
	*pResult = 0;
}

BOOL CContextEditDlg::InstallCommand(PSHELLCOMMAND pCommand, PFTELEMENT pType)
{
	int			iResult = 0;	// Default result = success.
	HKEY		hKeyParent, hKeyChild;
	DWORD		dwDisp;
	LRESULT		lResult;
	CString		strKeyName, strDDEKeyName;
	BOOL		bSuccess;

	strKeyName.Format("%s\\%shell\\%s",
		pType->strType,
		pCommand->bIsEnabled ? "s" : "-s",
		pCommand->strCommand);
	// Open (or create) the parent key for this command.
	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, strKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyParent, &dwDisp);
	if (lResult != ERROR_SUCCESS)
		return FALSE;
	// Is menu text defined for this command?
	if (!pCommand->strMenuText.IsEmpty())
	{
		// Yes .. install it.
		lResult = RegSetValueEx(hKeyParent, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) pCommand->strMenuText, pCommand->strMenuText.GetLength() + 1);
	}
	else
	{
		// No ... make sure it is removed.
		RegDeleteValue(hKeyParent, NULL);
	}
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(hKeyParent);
		return FALSE;
	}
	// Open (or create) the "command" subkey.
	lResult = RegCreateKeyEx(hKeyParent, "command", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyChild, &dwDisp);
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(hKeyParent);
		return FALSE;
	}
	// Install the command line
	lResult = RegSetValueEx(hKeyChild,
				NULL,
				0,
				pCommand->bExpandCmdLine ? REG_EXPAND_SZ : REG_SZ,
				(CONST BYTE *) (LPCTSTR) pCommand->strCommandLine,
				pCommand->strCommandLine.GetLength() + 1);
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(hKeyChild);
		RegCloseKey(hKeyParent);
		return FALSE;
	}
	// Now to deal with DDE info....
	RegCloseKey(hKeyChild);
	if (pCommand->bUseDDE)		// If DDE is enabled,
	{
		// Open/create the "ddexec" subkey.
		lResult = RegCreateKeyEx(hKeyParent, "ddeexec", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyChild, &dwDisp);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyParent);
			return FALSE;
		}
		// Install the DDE command string.
		lResult = RegSetValueEx(hKeyChild, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) pCommand->strDDEexec, pCommand->strDDEexec.GetLength() + 1);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyChild);
			RegCloseKey(hKeyParent);
			return FALSE;
		}
		// Handle remaining DDE fields:
		if ((bSuccess = InstallDDEField(hKeyChild, "Application", pCommand->strDDEapp)))
			if ((bSuccess = InstallDDEField(hKeyChild, "ifexec", pCommand->strDDEnotrunning)))
				bSuccess = InstallDDEField(hKeyChild, "Topic", pCommand->strDDEtopic);
		RegCloseKey(hKeyChild);
		if (!bSuccess)
		{
			RegCloseKey(hKeyParent);
			return FALSE;
		}
	}
	else
	{
		// Not using DDE, so make sure the "ddexec" subkey is removed.
		RegZapKey(hKeyParent, "ddeexec");
	}
	RegCloseKey(hKeyParent);
	return TRUE;
}

// Helper function installs (or removes) the specified DDE subkey.
BOOL CContextEditDlg::InstallDDEField(HKEY hKeyParent, LPCTSTR pszFieldName, CString &strContent)
{
	HKEY hKeyChild;
	LRESULT lResult;
	DWORD	dwDisp;

	// If the field is defined,
	if (!strContent.IsEmpty())
	{
		// Create the specified subkey.
		lResult = RegCreateKeyEx(hKeyParent, pszFieldName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyChild, &dwDisp);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyChild);
			return FALSE;
		}
		// Install the specified value.
		lResult = RegSetValueEx(hKeyChild, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) strContent, strContent.GetLength() + 1);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyChild);
			return FALSE;
		}
	}
	else
	{
		// Otherwise make sure the specified subkey is removed.
		RegZapKey(hKeyParent, pszFieldName);
	}
	return TRUE;
}

// Moves all commands from the current extension key
// to its associated master file type key.
void CContextEditDlg::OncmdMoveTo() 
{
	int				iThis,
					iSrcCount;
	BOOL			bFound;
	HKEY			hKey;
	DWORD			dwKeyCount,
					dwValueCount;
	CString			strPrompt,
					strDestCmdName,
					strSourceKey,
					strDestKey;
	LRESULT			lResult;
	CChooseType		dlgChoose;
	PFTELEMENT		pSourceType,
					pDestType = NULL;
	PSHELLCOMMAND	*pSrcArray;
	PSHELLCOMMAND	pSrcCmd;

	// Get pointer to the current file type.
	pSourceType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// Find the associated master file type.
	bFound = FALSE;
	for (iThis = 0; iThis < theApp.m_intTypeArrayCount; iThis++)
	{
		pDestType = theApp.m_pFileTypeArray[iThis];
		if (pSourceType->strFriendly.CompareNoCase(pDestType->strType) == 0)
		{
			bFound = TRUE;
			break;
		}
	}
	if (!bFound)
	{
		CMoveErrDlg dlg;
		dlg.m_pFileType = pSourceType;
		if (dlg.DoModal() != IDOK)
			return;
		switch (dlg.m_intFix)
		{
		case 0:	// Remove association to non-existent file type.
			// Open the extension key.
			lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, pSourceType->strType, 0, KEY_SET_VALUE, &hKey);
			if (lResult == ERROR_SUCCESS)
			{
				// Delete its (default) value.
				lResult = RegDeleteValue(hKey, NULL);
				RegCloseKey(hKey);
				if (lResult == ERROR_SUCCESS)
					// Update file type element.
					pSourceType->strFriendly.Empty();
			}
			if (lResult == ERROR_SUCCESS)
				// Update dialog controls.
				OnSelchangelstTypes();
			else
				ReportRegError();
			return;
		case 1:	// Select existing file type.
		default:
			if (dlgChoose.DoModal() != IDOK)
				return;
			pDestType = dlgChoose.m_pChosenType;
			lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, pSourceType->strType, 0, KEY_SET_VALUE, &hKey);
			if (lResult == ERROR_SUCCESS)
			{
				// Delete its (default) value.
				lResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) pDestType->strType, pDestType->strType.GetLength() + 1);
				RegCloseKey(hKey);
				if (lResult == ERROR_SUCCESS)
				{
					// Update file type element.
					pSourceType->strFriendly = pDestType->strType;
					pSourceType->bIsBroken = FALSE;
				}
			}
			if (lResult == ERROR_SUCCESS)
			{
				// Update dialog controls.
				OnSelchangelstTypes();
			}
			else
			{
				ReportRegError();
				return;
			}
		}
	}
	// If we got this far, we have a valid destination file type
	// so we can move the commands.
	// Copy current command array info.
	pSrcArray = theApp.m_pShellCommands;
	iSrcCount = theApp.m_intShellCommandCount;
	// Tell the app its array is empty.
	theApp.m_pShellCommands = NULL;
	theApp.m_intShellCommandCount = 0;
	theApp.m_intEnabledCommands = 0;
	theApp.m_intDisabledCommands = 0;
	// Get list of commands for destination file type
	theApp.GetMenuCommands(pDestType->strType);
	// Move commmands one at a time
	bFound = TRUE;
	for (iThis = 0; bFound && (iThis < iSrcCount); iThis++)
	{
		pSrcCmd = pSrcArray[iThis];
		// If a command with the same name exists,
		if (theApp.CommandExists(pSrcCmd->strCommand, pSrcCmd->bIsEnabled ? 0 : 1))
			// Create a new command name.
			theApp.GenerateCommandName(pSrcCmd->strCommand, strDestCmdName);
		else
			// Otherwise use the existing name.
			strDestCmdName = pSrcCmd->strCommand;
		// Build names of source and destination registry keys.
		strSourceKey.Format("%s\\%s\\%s",
			pSourceType->strType,
			(pSrcCmd->bIsEnabled ? "shell" : "-shell"),
			pSrcCmd->strCommand);
		strDestKey.Format("%s\\%s\\%s",
			pDestType->strType,
			(pSrcCmd->bIsEnabled ? "shell" : "-shell"),
			strDestCmdName);
		// Move the key.
		bFound = RegMoveKey(HKEY_CLASSES_ROOT, strDestKey, HKEY_CLASSES_ROOT, strSourceKey);
	}
	// If all commands were moved
	if (bFound)
	{
		// Clear source type flags.
		pSourceType->bHasCommand = FALSE;
		pSourceType->bHasDisabledCommand = FALSE;
		// Delete the source shell key's default value
		strSourceKey.Format("%s\\shell", pSourceType->strType);
		lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, strSourceKey, 0, KEY_SET_VALUE, &hKey);
		if (lResult == ERROR_SUCCESS)
		{
			RegDeleteValue(hKey, NULL);
			// Get number of subkeys and values under the source "shell" key.
			lResult = RegQueryInfoKey(hKey, NULL, NULL, NULL, &dwKeyCount, NULL, NULL, &dwValueCount, NULL, NULL, NULL, NULL);
			// Close the key.
			RegCloseKey(hKey);
			// If values were retrieved,
			if (lResult == ERROR_SUCCESS)
			{
				// And there are no subkeys or values left,
				if (dwKeyCount == 0 && dwValueCount == 0)
				{
					// Remove the source "shell" key.
					RegZapKey(HKEY_CLASSES_ROOT, strSourceKey);
				}
			}
		}
		// Delete our source "-shell" key, if it's there
		strDestKey.Format("%s\\-shell", pSourceType->strType);
		RegZapKey(HKEY_CLASSES_ROOT, strDestKey);
	}
	// Empty the command list.
	m_lstCommands.DeleteAllItems();
	// Erase the command array.
	for (iThis = 0; iThis < iSrcCount; iThis++)
	{
		if (pSrcArray[iThis] != NULL)
			delete pSrcArray[iThis];
	}
	free(pSrcArray);
	// If any commmands were not moved,
	if (!bFound)
	{
		// Leave the listbox selection where it is
		// and refresh the command list.
		OnSelchangelstTypes();
		ReportRegError();
	}
	else
	{
		// Find the target file type in the list
		iSrcCount = m_lstTypes.GetCount();
		for (iThis = 0; iThis < iSrcCount; iThis++)
		{
			if (pDestType == (PFTELEMENT) m_lstTypes.GetItemDataPtr(iThis))
			{
				// Select the destination file type.
				m_lstTypes.SetCurSel(iThis);
				// Refresh the dialog.
				OnSelchangelstTypes();
				break;
			}
		}
	}
}

// Enables/disables the specified context menu handler.
// Called by OnClicklstHandlers
BOOL CContextEditDlg::ToggleHandler(int iItem)
{
	HKEY		hKeyParent,
				hKeyChild;
	BOOL		bResult;
	LRESULT		lResult;
	CString		strNewID,
				strKeyName,
				strEnabled,
				strDisabled;
	PSHELLEXT	pInfo;
	PFTELEMENT	pType;

	// Get pointer to current handler info.
	pInfo = (PSHELLEXT) m_lstHandlers.GetItemData(iItem);
	// Get pointer to current file type info.
	pType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// Build name of this file type's ContextMenuHandlers subkey.
	strKeyName = pType->strType + "\\ShellEx\\ContextMenuHandlers";
	// Open the key.
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, strKeyName, 0, KEY_ALL_ACCESS, &hKeyParent);
	if (lResult != ERROR_SUCCESS)
	{
		ReportRegError();
		return FALSE;
	}
	// Is the CLSID string empty?
	if (pInfo->strCLSID.IsEmpty())
	{
		// Yes ... the handler's CLSID is stored in the name
		// of its subkey instead of that key's default value.
		// Therefore, we need to rename the key. Unfortunately,
		// the Registry APIs don't provide a "rename" function for
		// either values or keys, so we have to accomplish the rename
		// by moving the key from its old name to the new one.
		// Build names for enabled and disabled keys.
		strEnabled = pInfo->strKeyName;
		strDisabled = '-';
		strDisabled += strEnabled;
		// Is currently enabled?
		if (pInfo->bEnabled)
			// Yes .. move its key from enabled to disabled.
			bResult = RegMoveKey(hKeyParent, strDisabled, hKeyParent, strEnabled);
		else
			// No ... Move its key from disabled to enabled.
			bResult = RegMoveKey(hKeyParent, strEnabled, hKeyParent, strDisabled);
		// If the move succeeded,
		if (bResult)
			// Toggle the handler's status flag.
			pInfo->bEnabled = !pInfo->bEnabled;
		else
		{
			// Otherwise, report the error and return to caller.
			ReportRegError();
			RegCloseKey(hKeyParent);
			return FALSE;
		}
		RegCloseKey(hKeyParent);
	}
	else
	{
		// pszCLSID is not blank, so it does contain the handler's CLSID,
		// which is stored as its subkey's {Default} value. Therefore,
		// all we have to do is rewrite the value.
		// Build strings for enabled and disabled handler.
		strEnabled = pInfo->strCLSID;
		strDisabled = '-';
		strDisabled += strEnabled;
		// Open the handler's subkey.
		lResult = RegOpenKeyEx(hKeyParent, pInfo->strKeyName, 0, KEY_SET_VALUE, &hKeyChild);
		if (lResult == ERROR_SUCCESS)
		{
			// If handler is currently enabled,
			if (!pInfo->bEnabled)
				// Replace CLSID with the "disabled" CLSID.
				lResult = RegSetValueEx(hKeyChild, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) strEnabled, strEnabled.GetLength());
			else	// Otherwise, 
				// install the "enabled" CLSID.
				lResult = RegSetValueEx(hKeyChild, NULL, 0, REG_SZ, (CONST BYTE *) (LPCTSTR) strDisabled, strDisabled.GetLength());
			// If the value write succeeded,
			if (lResult == ERROR_SUCCESS)
			{
				// Toggle the handler's status flag.
				pInfo->bEnabled = !pInfo->bEnabled;
			}
			else
			{
				// Otherwise, report the error and return to caller.
				RegCloseKey(hKeyChild);
				RegCloseKey(hKeyParent);
				ReportRegError();
				return FALSE;
			}
			RegCloseKey(hKeyChild);
		}
		else	// Unable to open the handler's subkey.
		{
			RegCloseKey(hKeyParent);
			ReportRegError();
			return FALSE;
		}
		RegCloseKey(hKeyParent);
	}
	// If we got this far, the handler was enabled/disabled successfully.
	// Redraw its list item.
	m_lstHandlers.RedrawItems(iItem, iItem);
	// Indicate success to caller.
	return TRUE;
}

// Sets control status after the selection in the
// file type list has changed.
void CContextEditDlg::SetButtonStatus()
{
	int				iPos;
	BOOL			bHasMaster;
	POSITION		pos;
	PFTELEMENT		pFileType;
	PSHELLCOMMAND	pCommand;

	// Get pointer to the current file type.
	pFileType = (PFTELEMENT) m_lstTypes.GetItemDataPtr(m_lstTypes.GetCurSel());
	// Set the internal type name field.
	m_lblInternalName.SetWindowText(pFileType->strType);
	// Set flag if this is an extension key whose default value is not blank.
	bHasMaster = pFileType->bIsExt && !pFileType->strFriendly.IsEmpty();
	// If the extensions drop-list is empty, disable it.
	m_cmbExtensions.EnableWindow(m_cmbExtensions.GetCount() > 0);
	// Set flag if this is an extension key whose default value is not blank.
	bHasMaster = pFileType->bIsExt && !pFileType->strFriendly.IsEmpty();
	// Enable/disable the "Find master file type" button accordingly.
	m_cmdFindType.EnableWindow(bHasMaster /* && !pFileType->bIsBroken*/);
	// Disable all other controls if this is a "system" file type.
	if (pFileType->bIsSystemType)
	{
		m_cmdMoveTo.EnableWindow(FALSE);
		m_cmdNewCommand.EnableWindow(FALSE);
		m_cmdEditCommand.EnableWindow(FALSE);
		m_cmdDeleteCommand.EnableWindow(FALSE);
		m_cmdSetDefault.EnableWindow(FALSE);
		m_lstCommands.EnableWindow(FALSE);
		m_lstHandlers.EnableWindow(FALSE);
		return;
	}
	// Make sure the lists themselves are enabled.
	m_lstCommands.EnableWindow(TRUE);
	m_lstHandlers.EnableWindow(TRUE);
	// Enable/disable the "Move to master file type button" accordingly.
	m_cmdMoveTo.EnableWindow(bHasMaster && (pFileType->bHasCommand || pFileType->bHasDisabledCommand));
	// "New" button is always enabled.
	m_cmdNewCommand.EnableWindow(TRUE);
	// Handle the "Edit", "Delete", and "Set Default" buttons.
	// Get current command list selection.
	pos = m_lstCommands.GetFirstSelectedItemPosition();
	if (pos != NULL)	// Is any item selected?
	{
		// Yes ... get its index.
		iPos = m_lstCommands.GetNextSelectedItem(pos);
		// Get pointer to its command.
		pCommand = (PSHELLCOMMAND) m_lstCommands.GetItemData(iPos);
		// Enable the "Set Default" button only if the current item is an enabled
		// command and not already set as the default.
		m_cmdSetDefault.EnableWindow(pCommand->bIsEnabled && !pCommand->bIsDefault);
		// Enable the "Edit" and "Delete" buttons.
		m_cmdEditCommand.EnableWindow(TRUE);
		m_cmdDeleteCommand.EnableWindow(TRUE);
	}
	else	// No list item selected so
	{
		// Disable all three buttons.
		m_cmdEditCommand.EnableWindow(FALSE);
		m_cmdDeleteCommand.EnableWindow(FALSE);
		m_cmdSetDefault.EnableWindow(FALSE);
	}
}
