
// StickyNotesBackupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StickyNotesBackup.h"
#include "StickyNotesBackupDlg.h"

#include "ProcessManagement.h"

#include <vector>
#include <algorithm>
#include <functional> 
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStickyNotesBackupDlg dialog

static const char *stickyNotes = "StickyNotes.snt";
static const char *stickyNotesExe = "StikyNot.exe";


CStickyNotesBackupDlg::CStickyNotesBackupDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CStickyNotesBackupDlg::IDD, pParent)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStickyNotesBackupDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST_BACKUP, _backupList);
}

BEGIN_MESSAGE_MAP(CStickyNotesBackupDlg, CDialog)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
//}}AFX_MSG_MAP
ON_BN_CLICKED(IDC_BUTTON_BACKUP, &CStickyNotesBackupDlg::OnBnClickedButtonBackup)
ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CStickyNotesBackupDlg::OnBnClickedButtonRestore)
ON_BN_CLICKED(IDC_BUTTON_DELETE, &CStickyNotesBackupDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()

list<string> MakeFileList(const char *pathName)
{
  list<string> fileList;

  WIN32_FIND_DATA  findFileData;
  HANDLE hFileHandle = FindFirstFile(pathName, &findFileData);
  if (hFileHandle != INVALID_HANDLE_VALUE) {
    do {
      if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
      fileList.push_back (string(findFileData.cFileName));
    } while(FindNextFile(hFileHandle, &findFileData));
    FindClose(hFileHandle);
  }
  return fileList;
}

// CStickyNotesBackupDlg message handlers
BOOL CStickyNotesBackupDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon

  // TODO: Add extra initialization here
  char notePath[MAX_PATH];

  SHGetSpecialFolderPath(NULL, notePath, CSIDL_APPDATA, 0);
  strcat (notePath, "\\Microsoft\\Sticky Notes");

  SetCurrentDirectory (notePath);

  _backupList.SetExtendedStyle(_backupList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
  _backupList.InsertColumn(0,	"File", LVCFMT_LEFT, 300);
  // _backupList.InsertColumn(1,	"Date Time", LVCFMT_LEFT, 150);

  ReloadBackupList ();

  return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStickyNotesBackupDlg::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStickyNotesBackupDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}

bool string_greater (string &elem1, string &elem2)
{
  return elem1 > elem2;
}

void CStickyNotesBackupDlg::ReloadBackupList ()
{
  _backupList.DeleteAllItems ();

  _backupFiles = MakeFileList ("*.backup");
  _backupFiles.sort (string_greater);

  int i = 0;
  for (list<string>::iterator it = _backupFiles.begin(); it != _backupFiles.end(); ++it) {
    _backupList.InsertItem (LVIF_TEXT, i, (*it).c_str(), 0, 0, 0, 0);
    _backupList.SetItemData (i, (unsigned long)(*it).c_str());
    _backupList.SetCheck (i, false);
    ++i;
  }
}

bool CStickyNotesBackupDlg::IsCurrentNotesBackuped ()
{
  if (_backupFiles.empty ()) {
    return false;
  }

  const char *backupNotes = _backupFiles.begin()->c_str();

  struct _stat buf1;
  struct _stat buf2;

  if (_stat(backupNotes, &buf1) == 0 && _stat(stickyNotes, &buf2) == 0 ){
    if (buf1.st_mtime < buf2.st_mtime) {
      return false;
    }
  }
  return true;
}

void CStickyNotesBackupDlg::OnBnClickedButtonBackup()
{
  if (IsCurrentNotesBackuped ()) {
    AfxMessageBox ("Current StickyNotes are already backuped.", MB_ICONINFORMATION);
    return;
  }

  char timeStr[64];
  GetTimeStr (timeStr);

  char backupName[MAX_PATH];
  sprintf (backupName, "StickyNotes-%s.backup", timeStr);

  CopyFile(stickyNotes, backupName, FALSE);

  _backupFiles.push_front (string(backupName));

  int i = 0;
  list<string>::iterator it = _backupFiles.begin();
  _backupList.InsertItem (LVIF_TEXT, i, (*it).c_str(), 0, 0, 0, 0);
  _backupList.SetItemData (i, (unsigned long)(*it).c_str());
  _backupList.SetCheck (i, false);
}

void CStickyNotesBackupDlg::OnBnClickedButtonRestore()
{
  UINT count = _backupList.GetSelectedCount();

  if (count == 0) {
    AfxMessageBox ("Select backup files.", MB_ICONINFORMATION);
    return;
  }

  int item = _backupList.GetNextItem (-1, LVNI_SELECTED);
  const char *backupName = (const char *)_backupList.GetItemData (item);

  KillProcess (stickyNotesExe);

  while (FindProcess (stickyNotesExe)) {
    Sleep (10);
  }

  CopyFile(backupName, stickyNotes, FALSE);
	
  //StartProcess (stickyNotesExe);
  WinExec (stickyNotesExe, SW_SHOW);
}

void CStickyNotesBackupDlg::OnBnClickedButtonDelete()
{
  UINT count = _backupList.GetSelectedCount();

  if (count == 0) {
    AfxMessageBox ("Select backup files.", MB_ICONINFORMATION);
    return;
  }

  int  item = -1;

  for (UINT i=0; i<count; ++i) {
    item = _backupList.GetNextItem(item, LVNI_SELECTED);

    const char *backupName = (const char *)_backupList.GetItemData (item);
    DeleteFile (backupName);
  }
	
  ReloadBackupList ();
}
