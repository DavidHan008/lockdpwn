// ContextEdit.cpp : Defines the class behaviors for the application.
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "ContextEdit.h"
#include "ContextEditDlg.h"
#include "ProgressDlg.h"
#include "RegHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SYSTEM_TYPE_COUNT 11
const char * pszSystemTypes[SYSTEM_TYPE_COUNT] =
{
	".exe",
	"exefile",
	".dll",
	"dllfile",
	".com",
	"comfile",
	".vxd",
	".386",
	"vxdfile",
	".drv",
	"drvfile",
};


/////////////////////////////////////////////////////////////////////////////
// CContextEditApp

BEGIN_MESSAGE_MAP(CContextEditApp, CWinApp)
	//{{AFX_MSG_MAP(CContextEditApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContextEditApp construction

CContextEditApp::CContextEditApp()
{
	m_pFileTypeArray = NULL;
	m_intTypeArrayCount = 0;
	m_intTypeArraySize = 0;
	m_pShellCommands = NULL;
	m_intShellCommandCount = 0;
	m_pShellExtArray = NULL;
	m_intExtArrayCount = 0;
	m_bAllowExpansion = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CContextEditApp object

CContextEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CContextEditApp initialization

BOOL CContextEditApp::InitInstance()
{
	HWND	hWnd;
	HKEY	hKey;
	BOOL	bAllowExpansion = TRUE;
	DWORD	dwDisp;
	LRESULT	lResult;

	// Create mutex so installer know's we're running.
	CreateMutex(NULL, FALSE, "ContextEditIsRunning");

	// First, check for the proper version of COMCTL32.DLL
	if (!Check_DLL_Version())
		return FALSE;
	
	
	// See if we're already running.
	// Look for the load status dialog.
	hWnd = ::FindWindow("#32770", "Reading file type data...");
	
	
	// If not found,
	if (hWnd == NULL)
		// Look for the main dialog.
		hWnd = ::FindWindow("#32770", "ContextEdit");
	
	
	// If either dialog exists,
	if (hWnd != NULL)
	{
		// bring it to the foreground
		::SetForegroundWindow(hWnd);
		// and we're done.
		return FALSE;
	}
	
	
	// Build the file type array.
	if (!GetFileTypes())
	{
		::MessageBox(NULL, "Initialization failed.", "ContextEdit", MB_ICONSTOP);
		return FALSE;
	}
	
	
	// Check to see if system supports the REG_EXPAND_SZ data type
	// for unnamed data values.
	// Create a dummy test key.
	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, "ContextEdit Test", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, &dwDisp);
	
	
	if (lResult == ERROR_SUCCESS)
	{
		// Try to set its default value to a REG_EXPAND_SZ string.
		lResult = RegSetValueEx(hKey, NULL, 0, REG_EXPAND_SZ, (BYTE *) "Test", 5);
		// Set flag according to success or failure.
		m_bAllowExpansion = (lResult == ERROR_SUCCESS);
		// Close the key.
		RegCloseKey(hKey);
		// Delete the key.
		RegZapKey(HKEY_CLASSES_ROOT, "ContextEdit Test");
	};
	
	
	// Create main dialog.
	CContextEditDlg dlg;
	
	
	// Set it as the main window.
	m_pMainWnd = &dlg;
	
	
	// Launch the dialog.
	dlg.DoModal();
	
	
	// Done when dialog terminates.
	return FALSE;
}


// Adds a file type to the array.
BOOL CContextEditApp::AddFileType(LPCTSTR pszType, BOOL bForce)
{
	int			i;
	char		szBuffer[MAX_PATH];
	BOOL		bIsExt = FALSE,
				bHasCommand = FALSE,
				bHasDisabledCommand = FALSE,
				bHasHandler = FALSE,
				bIsSystemType = FALSE;
	HKEY		hKey,
				hKey2;
	DWORD		dwLen,
				dwType;
	LRESULT		lResult;
	PFTELEMENT	*pTemp;
	PFTELEMENT	pNew;
	CString		strDebugMessage;

	// Exclude the CLSID key:
	if (stricmp(pszType, "CLSID") == 0)
		return TRUE;
	
	
	// Check for "system" file types
	for (i = 0; i < SYSTEM_TYPE_COUNT; i++)
	{
		if (stricmp(pszType, pszSystemTypes[i]) == 0)
		{
			bIsSystemType = TRUE;
			break;
		}
	}
	
	
	// If first character of key name is a ".", it is an "extension key".
	bIsExt = pszType[0] == '.';
	
	
	// Error if the specified key does not exist.
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, pszType, 0, KEY_QUERY_VALUE, &hKey);
	
	
	if (lResult != ERROR_SUCCESS)
	{
		// This is only a problem on the first pass, while enumerating the
		// keys under HCKR.
		if (!bForce)
		{
			strDebugMessage.Format("Could not obtain KEY_QUERY_VALUE access to\n"
				"HKEY_CLASSES_ROOT\\%s\n"
				"Error code %u.\n"
				"Your registry may be damaged, or another program\n"
				"may have been modifying the registry as ContextEdit\n"
				"was trying to read it.", pszType, lResult, bForce);
			::MessageBox(NULL, strDebugMessage, "ContextEdit", MB_ICONSTOP);
		}
		return FALSE;
	}
	
	
	dwLen = MAX_PATH;
	
	
	// Retrieve the key's default value.
	lResult = RegQueryValueEx(hKey, NULL, NULL, &dwType, (LPBYTE) szBuffer, &dwLen);
	if (lResult != ERROR_SUCCESS)
		szBuffer[0] = '\0';
	
	
	// Try to open the "shell" subkey.
	lResult = RegOpenKeyEx(hKey, "shell", 0, KEY_QUERY_VALUE, &hKey2);
	if (lResult == ERROR_SUCCESS)
	{
		// If it's there, this type probabably has enabled commands.
		bHasCommand = TRUE;
		RegCloseKey(hKey2);
	}
	
	
	// Try to open the "-shell" subkey.
	lResult = RegOpenKeyEx(hKey, "-shell", 0, KEY_QUERY_VALUE, &hKey2);
	if (lResult == ERROR_SUCCESS)
	{
		// If it's there, this type probably has disabled shell commands.
		bHasDisabledCommand = TRUE;
		RegCloseKey(hKey2);
	}
	
	
	// Open the ContextMenuHandlers subkey.
	lResult = RegOpenKeyEx(hKey, "shellex\\ContextMenuHandlers", 0, KEY_QUERY_VALUE, &hKey2);
	if (lResult == ERROR_SUCCESS)
	{
		// If it's there, this file type probably has handlers attached.
		bHasHandler = TRUE;
		RegCloseKey(hKey2);
	}
	
	
	RegCloseKey(hKey);
	
	
	// Unless we're being forced (e.g, due to an existing reference to this file type),
	if (!bForce)
		// Don't add master file types that have no commands or handlers attached.
		if (!bIsExt && !(bHasCommand || bHasDisabledCommand || bHasHandler))
			return TRUE;
	
	
	// If needed, expand the file type array.
	if (m_intTypeArraySize == m_intTypeArrayCount)
	{
		m_intTypeArraySize += FT_ARRAY_INCREMENT;
		pTemp = (PFTELEMENT*) realloc(m_pFileTypeArray, m_intTypeArraySize * sizeof(PFTELEMENT));
		if (pTemp == NULL)
		{
			::MessageBox(NULL, "Memory allocation failed.", "ContextEdit", MB_ICONSTOP);
			return FALSE;
		}
		m_pFileTypeArray = pTemp;
		for (i = m_intTypeArrayCount; i < m_intTypeArraySize; i++)
			m_pFileTypeArray[i] = NULL;
	}
	
	
	// Create a new array element.
	if ((pNew = new FTELEMENT) == NULL)
	{
		::MessageBox(NULL, "FTELEMENT object creation failed.", "ContextEdit", MB_ICONSTOP);
		return FALSE;
	}
	
	
	// Copy data into the new element.
	pNew->bIsExt = bIsExt;
	pNew->bIsSystemType = bIsSystemType;
	pNew->bHasCommand = bHasCommand;
	pNew->bHasDisabledCommand = bHasDisabledCommand;
	pNew->bHasHandler = bHasHandler;
	pNew->strType = pszType;
	pNew->strFriendly = szBuffer;
	
	
	// Add the new element to the array.
	m_pFileTypeArray[m_intTypeArrayCount] = pNew;
	
	
	// Update the array count.
	++m_intTypeArrayCount;
	
	
	return TRUE;
}

// Enumerates the HKEY_CLASSES_ROOT section of the registry
// to build the file type array.
BOOL CContextEditApp::GetFileTypes(void)
{
	char			szBuffer[MAX_PATH];
	BOOL			bResult;
	DWORD			dwLen,
					dwKeyCount,
					dwCount;
	LRESULT			lResult;
	CString			strPrompt;
	CProgressDlg	*pDlg = NULL;

	// If the array already exists, delete it.
	DeleteFileTypeArray();
	// Get number of keys present for the progress display.
	lResult = RegQueryInfoKey(HKEY_CLASSES_ROOT, NULL, NULL, NULL, &dwKeyCount, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		::MessageBox(NULL, "Could not open HKEY_CLASSES_ROOT", "ContextEdit Debug", MB_ICONINFORMATION);
		return FALSE;
	}
	
	// Show "busy" status.
	BeginWaitCursor();
	
	
	// Create the progress dialog object.
	pDlg = new CProgressDlg;
	if (pDlg != NULL)
	{
		// Create the progress dialog window.
		pDlg->Create(IDD_PROGRESS_DLG);
		// Set the range for the status indicator.
		pDlg->m_Progress.SetRange32(1, dwKeyCount);
		pDlg->SetWindowText("Reading file type data...");
		// Make sure the window is centered on the screen.
		pDlg->CenterWindow(NULL);
		// Make sure the window is displayed.
		pDlg->ShowWindow(SW_SHOW);
	}
	
	// Initialize count for enumerating subkeys.
	dwCount = 0;
	
	// Set default result
	bResult = TRUE;
	
	while (TRUE)
	{
		// Retrieve the name of the current key.
		dwLen = MAX_PATH;
		lResult = RegEnumKeyEx(HKEY_CLASSES_ROOT, dwCount, szBuffer, &dwLen, NULL, NULL, NULL, NULL);
		
		// Done if no more keys to enumerate.
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;
		
		// Error if RegEnumKeyEx() failed.
		if (lResult != ERROR_SUCCESS)
		{
			strPrompt.Format("RegEnumKeyEx failed in CContextEditApp::GetFileTypes\n"
								"Result code 0x%08X", lResult);
			::MessageBox(NULL, strPrompt, "ContextEdit Error", MB_ICONSTOP);
			bResult = FALSE;
			break;
		}
		
		// Otherwise, add the new file type to the array.
		if (!AddFileType(szBuffer))
		{
			bResult = FALSE;
			break;
		}
		
		// Update count to enumerate the next key.
		++dwCount;
		
		// Update status display once every 16 passes.
		if ((dwCount & 0x0F) == 0)
		{
			if (pDlg != NULL)
			{
				pDlg->m_Progress.SetPos(dwCount);
			}
		}
	}

	// Clear busy status.
	EndWaitCursor();
	
	// If created, destroy and delete the progress dialog.
	if (pDlg != NULL)
	{
		pDlg->DestroyWindow();
		delete pDlg;
	}
	
	// If no fatal errors occurred,
	if (bResult)
		// Double-check for broken extension keys.
		CheckExtensionLinks();


	return bResult;
}


// Erases the file type array.
void CContextEditApp::DeleteFileTypeArray(void)
{
	int i;

	if (m_pFileTypeArray != NULL)
	{
		for (i = 0; i < m_intTypeArrayCount; i++)
		{
			if (m_pFileTypeArray[i] != NULL)
				delete m_pFileTypeArray[i];
		}
		free (m_pFileTypeArray);
	}
	m_pFileTypeArray = NULL;
	m_intTypeArrayCount = 0;
	m_intTypeArraySize = 0;
}

// Performs clean-up at termination.
int CContextEditApp::ExitInstance() 
{
	DeleteFileTypeArray();
	DeleteCommandArray();
	DeleteShellExtArray();
	return CWinApp::ExitInstance();
}

// Builds the shell command array for the specified file type.
BOOL CContextEditApp::GetMenuCommands(LPCTSTR pszType)
{
	char	szDefaultCommand[MAX_PATH];
	BOOL	bSuccess = TRUE;
	HKEY	hKeyMaster,
			hKeyParent,
			hKeyChild;
	DWORD	dwType,
			dwLen,
			dwCount,
			dwDisabledCount,
			dwArraySize;
	LRESULT	lResult;

	// Make sure the array is reset.
	DeleteCommandArray();
	szDefaultCommand[0] = '\0';
	// Open the "master key" for this file type.
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, pszType, 0, KEY_READ, &hKeyMaster);
	if (lResult != ERROR_SUCCESS)
		return FALSE;
	// Try to open the "shell" subkey.
	lResult = RegOpenKeyEx(hKeyMaster, "shell", 0, KEY_READ, &hKeyParent);
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(hKeyMaster);
		return FALSE;
	}
	// Get number of subkeys under "shell"
	lResult = RegQueryInfoKey(hKeyParent, NULL, NULL, NULL, &dwCount, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(hKeyParent);
		RegCloseKey(hKeyMaster);
		return FALSE;
	}
	// Try to open the "-shell" subkey (where we store disabled commands)
	lResult = RegOpenKeyEx(hKeyMaster, "-shell", 0, KEY_QUERY_VALUE, &hKeyChild);
	if (lResult == ERROR_SUCCESS)
	{
		// Get number of subkeys under "-shell"
		lResult = RegQueryInfoKey(hKeyChild, NULL, NULL, NULL, &dwDisabledCount, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		RegCloseKey(hKeyChild);
	}
	else
	{
		// If the key doesn't exist, there are no disabled commands.
		dwDisabledCount = 0;
	}
	// Get total number of commands.
	dwArraySize = dwCount + dwDisabledCount;
	// Create new array of appropriate size.
	m_pShellCommands = (PSHELLCOMMAND*) malloc(dwArraySize * sizeof(PSHELLCOMMAND));
	// Report failure if unable to create the array.
	if (m_pShellCommands == NULL)
	{
		RegCloseKey(hKeyParent);
		RegCloseKey(hKeyMaster);
		return FALSE;
	}
	// Initialize the array.
	for (dwCount = 0; dwCount < dwArraySize; m_pShellCommands[dwCount++] = NULL);
	// Retrieve the default shell command.
	dwLen = MAX_PATH;
	lResult = RegQueryValueEx(hKeyParent, NULL, NULL, &dwType, (LPBYTE) szDefaultCommand, &dwLen);
	// Retrieve the enabled commands.
	bSuccess = GetCommands(hKeyParent, szDefaultCommand, TRUE);
	// If there are any disabled commands:
	if (dwDisabledCount != 0)
	{
		// Close the "shell" subkey.
		RegCloseKey(hKeyParent);
		// Open the "-shell" subkey
		lResult = RegOpenKeyEx(hKeyMaster, "-shell", 0, KEY_READ, &hKeyParent);
		if (lResult == ERROR_SUCCESS)
		{
			// Retrieve the disabled commands.
			bSuccess = GetCommands(hKeyParent, szDefaultCommand, FALSE);
		}
	}
	RegCloseKey(hKeyParent);
	RegCloseKey(hKeyMaster);
	return bSuccess;
}

// Erases the shell command array.
void CContextEditApp::DeleteCommandArray(void)
{
	if (m_pShellCommands != NULL)
	{
		for (int i = 0; i < m_intShellCommandCount; i++)
		{
			if (m_pShellCommands[i] != NULL)
				delete m_pShellCommands[i];
		}
		free(m_pShellCommands);
	}
	m_pShellCommands = NULL;
	m_intShellCommandCount = 0;
	m_intEnabledCommands = 0;
	m_intDisabledCommands = 0;
}

// Ensures that we get master file types for
// all extension keys.
void CContextEditApp::CheckExtensionLinks(void)
{
	int			i,
				j;
	BOOL		bFound;
	FTELEMENT	*pThis,
				*pThat;
	CString		strPrompt;

	for (i = 0; i < m_intTypeArrayCount; i++)	// Loop through file type array.
	{
		pThis = m_pFileTypeArray[i];		// Get element pointer.
		if (!pThis->bIsExt)					// Not an extension key?
			continue;						// Yes .. Next element.
		if (pThis->strFriendly.IsEmpty())	// Not linked to another key?
		{
			pThis->bIsBroken = FALSE;		// Yes .. link is not "broken".
			continue;						// Next element.
		}
		// Check for key that refers to itself
		if (pThis->strFriendly.CompareNoCase(pThis->strType) == 0)
		{
			pThis->bIsBroken = FALSE;
			continue;
		}
		bFound = FALSE;						// Reset search flag.
		for (j = 0; j < m_intTypeArrayCount; j++)	// Loop through the array again.
		{
			if (j == i)							// Skip the current extension key.
				continue;
			pThat = m_pFileTypeArray[j];		// Get pointer to element to test.
			if (pThat->bIsExt)					// Is it an extension key?
				continue;						// Yes .. continue with next element.
			// Does it match the link?
			if (pThis->strFriendly.CompareNoCase(pThat->strType) == 0)
			{
				bFound = TRUE;	// Yes .. set flag.
				break;			// Done looking.
			}
		}
		if (!bFound)								// Was linked file type found?
		{
			pThis->bIsBroken = !AddFileType(pThis->strFriendly, TRUE);	// No ... add it to the array, if possible.
		}
		else
			pThis->bIsBroken = FALSE;
	}
}

// Retrieves the commands from the specified key and adds them to the
// shell command array.
BOOL CContextEditApp::GetCommands(HKEY hKeyParent, char *pszDefaultCommand, BOOL bEnabled)
{
	char			szCommandKey[MAX_PATH],
					szCommand[MAX_PATH],
					szMenuText[MAX_PATH],
					szDDEString[MAX_PATH];
	BOOL			bSuccess = TRUE;
	BOOL			bExpandCmdLine = FALSE;
	HKEY			hKeyChild,
					hKeyCommand,
					hKeyDDEmaster,
					hKeyDDEchild;
	DWORD			dwType,
					dwLen,
					dwThis;
	LRESULT			lResult;
	CString			strDDEexec,
					strDDEapp,
					strDDEnotrunning,
					strDDEtopic;
	PSHELLCOMMAND	pNew;

	// Begin enumerating with a zero index.
	dwThis = 0;
	while (TRUE)	// Loop until there are no more keys left.
	{
		// Reset all string fields.
		strDDEexec.Empty();
		strDDEapp.Empty();
		strDDEnotrunning.Empty();
		strDDEtopic.Empty();
		szCommandKey[0] = '\0';
		szMenuText[0] = '\0';
		szCommand[0] = '\0';
		szDDEString[0] = '\0';
		// Get name of next subkey.
		dwLen = MAX_PATH;
		lResult = RegEnumKeyEx(hKeyParent, dwThis, szCommandKey, &dwLen, NULL, NULL, NULL, NULL);
		// No subkeys left?
		if (lResult == ERROR_NO_MORE_ITEMS)
			// We're done.
			break;
		// Call failed completely?
		if (lResult != ERROR_SUCCESS)
		{
			// Report the error and bail.
			bSuccess = FALSE;
			break;
		}
		// Open the subkey.
		lResult = RegOpenKeyEx(hKeyParent, szCommandKey, 0, KEY_READ, &hKeyChild);
		if (lResult != ERROR_SUCCESS)
		{
			bSuccess = FALSE;
			break;
		}
		// Get menu text, if any.
		dwLen = MAX_PATH;
		// Note: It's not a problem if the (default) value is either blank or undefined.
		lResult = RegQueryValueEx(hKeyChild, NULL, NULL, &dwType, (LPBYTE) szMenuText, &dwLen);
		// Open the "command" sub key
		lResult = RegOpenKeyEx(hKeyChild, "command", 0, KEY_READ, &hKeyCommand);
		// If there is no "command" subkey, it's not a fatal error...
		if (lResult != ERROR_SUCCESS)
		{
			goto NonFatalError;
		}
		// Retrieve the command line
		dwLen = MAX_PATH;
		lResult = RegQueryValueEx(hKeyCommand, NULL, NULL, &dwType, (LPBYTE) szCommand, &dwLen);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyCommand);
			goto NonFatalError;
		}
		// Preserve data type for the command line string.
		// Under Win 95, the REG_EXPAND_SZ data type is not suppported,
		// but other versions (NT in particular) do use it.
		bExpandCmdLine = (dwType == REG_EXPAND_SZ);
		// Retrieve DDE info
		// Open the "ddexec" sub key
		lResult = RegOpenKeyEx(hKeyChild, "ddeexec", 0, KEY_READ, &hKeyDDEmaster);
		if (lResult == ERROR_SUCCESS)
		{
			// Retrieve the DDE command string
			dwLen = MAX_PATH;
			lResult = RegQueryValueEx(hKeyDDEmaster, NULL, NULL, &dwType, (LPBYTE) szDDEString, &dwLen);
			if (lResult == ERROR_SUCCESS)
				strDDEexec = szDDEString;
			// Remaining DDE data may or may not be defined, so it's not a problem
			// if any of these keys are missing.
			lResult = RegOpenKeyEx(hKeyDDEmaster, "application", 0, KEY_READ, &hKeyDDEchild);
			if (lResult == ERROR_SUCCESS)
			{
				dwLen = MAX_PATH;
				lResult = RegQueryValueEx(hKeyDDEchild, NULL, NULL, &dwType, (LPBYTE) szDDEString, &dwLen);
				if (lResult == ERROR_SUCCESS)
					strDDEapp = szDDEString;
				RegCloseKey(hKeyDDEchild);
			}
			lResult = RegOpenKeyEx(hKeyDDEmaster, "topic", 0, KEY_READ, &hKeyDDEchild);
			if (lResult == ERROR_SUCCESS)
			{
				dwLen = MAX_PATH;
				lResult = RegQueryValueEx(hKeyDDEchild, NULL, NULL, &dwType, (LPBYTE) szDDEString, &dwLen);
				if (lResult == ERROR_SUCCESS)
					strDDEtopic = szDDEString;
				RegCloseKey(hKeyDDEchild);
			}
			lResult = RegOpenKeyEx(hKeyDDEmaster, "ifexec", 0, KEY_READ, &hKeyDDEchild);
			if (lResult == ERROR_SUCCESS)
			{
				dwLen = MAX_PATH;
				lResult = RegQueryValueEx(hKeyDDEchild, NULL, NULL, &dwType, (LPBYTE) szDDEString, &dwLen);
				if (lResult == ERROR_SUCCESS)
					strDDEnotrunning = szDDEString;
				RegCloseKey(hKeyDDEchild);
			}
			RegCloseKey(hKeyDDEmaster);
		}
NonFatalError:
		pNew = new SHELLCOMMAND;
		if (pNew == NULL)
		{
			bSuccess = FALSE;
			RegCloseKey(hKeyChild);
			break;
		}
		pNew->bIsEnabled = bEnabled;
		pNew->bExpandCmdLine = bExpandCmdLine;
		pNew->strCommand = szCommandKey;
		pNew->strCommandLine = szCommand;
		pNew->strMenuText = szMenuText;
		pNew->strDDEexec = strDDEexec;
		pNew->strDDEapp = strDDEapp;
		pNew->strDDEnotrunning = strDDEnotrunning;
		pNew->strDDEtopic = strDDEtopic;
		pNew->bUseDDE = !(strDDEexec.IsEmpty());
		if (bEnabled)
			pNew->bIsDefault = stricmp(szCommandKey, pszDefaultCommand) == 0;
		else
			pNew->bIsDefault = FALSE;
		m_pShellCommands[m_intShellCommandCount] = pNew;
		++m_intShellCommandCount;
		if (bEnabled)
			++m_intEnabledCommands;
		else
			++m_intDisabledCommands;
		RegCloseKey(hKeyChild);
		RegCloseKey(hKeyCommand);
		++dwThis;
	}
	return bSuccess;
}


// Searches for a command with the specified name.
// pszCommand = name of command to search for.
// iSearchType = type of search to perform:
// 0 = match only enabled commands.
// 1 = match only disabled commands.
// 2 = match any command.
BOOL CContextEditApp::CommandExists(LPCTSTR pszCommand, int iSearchType)
{
	int				i;
	PSHELLCOMMAND	pCommand;

	for (i = 0; i < m_intShellCommandCount; i++)
	{
		pCommand = m_pShellCommands[i];
		if (pCommand->strCommand.CompareNoCase(pszCommand) == 0)
		{
			switch (iSearchType)
			{
			case 0:
				if (pCommand->bIsEnabled)
					return TRUE;
				else
					continue;
			case 1:
				if (pCommand->bIsEnabled)
					continue;
				else
					return TRUE;
			case 2:
				return TRUE;
			}
		}
	}
	return FALSE;
}

// Generates a unique internal command name by appending a numeric suffix
// to the provided command name.
void CContextEditApp::GenerateCommandName(LPCTSTR pszOldName, CString &strNewName)
{
	int		iCount = 1;
	char	*p;
	CString strBaseName;

	// Find last non-digit character in the name.
	for (iCount = strlen(pszOldName) - 1; iCount >= 0; iCount--)
	{
		if (pszOldName[iCount] < '0' || pszOldName[iCount] > '9')
			break;
	}
	// Include the last non-digit character and allow for a terminating NULL.
	iCount += 2;
	// Copy string, excluding any numeric suffix.
	p = strBaseName.GetBuffer(iCount);
	lstrcpyn(p, pszOldName, iCount);
	// Let the CSting clean up its internals.
	strBaseName.ReleaseBuffer();
	iCount = 0;
	while (TRUE)
	{
		strNewName.Format("%s%u", strBaseName, iCount);
		if (!CommandExists(strNewName, 2))
			return;
		++iCount;
	}
}

// Adds a shell command to the array.
// Calling function is responsible for allocating and
// initializing the element pointed to by pCommand.
BOOL CContextEditApp::AddShellCommand(PSHELLCOMMAND pCommand)
{
	PSHELLCOMMAND *pNewArray = NULL;

	pNewArray = (PSHELLCOMMAND *) realloc(m_pShellCommands, (m_intShellCommandCount + 1) * sizeof(PSHELLCOMMAND));
	if (pNewArray == NULL)
		return FALSE;
	m_pShellCommands = pNewArray;
	m_pShellCommands[m_intShellCommandCount] = pCommand;
	++m_intShellCommandCount;
	if (pCommand->bIsEnabled)
		++m_intEnabledCommands;
	else
		++m_intDisabledCommands;
	return TRUE;
}

// Erases the shell extension array.
void CContextEditApp::DeleteShellExtArray(void)
{
	if (m_pShellExtArray != NULL)
	{
		for (int i = 0; i < m_intExtArrayCount; i++)
		{
			if (m_pShellExtArray[i] != NULL)
				delete m_pShellExtArray[i];
		}
		free (m_pShellExtArray);
	}
	m_intExtArrayCount = 0;
	m_pShellExtArray = NULL;
}

// Adds a shell extension to the array for the current file type.
// pszName == name of the handler's ContextMenuHandler's subkey.
// pszCLSID == default value of the pszName subkey (usually the CLSID).
BOOL CContextEditApp::AddShellExt(LPCTSTR pszName, LPCTSTR pszCLSID)
{
	char		pszModuleName[_MAX_PATH],
				pszExpanded[_MAX_PATH];
	BOOL		bEnabled;
	HKEY		hKeyParent,
				hKeyChild;
	DWORD		dwLen,
				dwType;
	CString		strName,
				strCLSID,
				strTargetKey, strFriendly;
	LRESULT		lResult;
	PSHELLEXT	*pTemp = NULL;
	PSHELLEXT	pNewEntry = NULL;

	// Is CLSID string blank?
	if (pszCLSID[0] == '\0')
	{
		// Then the CLSID must be the name of the subkey.
		if (pszName[0] == '-')		// Is first character a "-"?
		{
			strName = &pszName[1];	// Yes .. strip it off
			bEnabled = FALSE;		// Handler is disabled;
		}
		else
		{
			strName = pszName;
			bEnabled = TRUE;
		}
		// Build path to the handler's CLSID subkey.
		strTargetKey.Format("CLSID\\%s", strName);
	}
	else	// If pszCLSID is not blank, so it must contain the CLSID.
	{
		// Store key name verbatim.
		strName = pszName;
		// If this handler is disabled,
		if (pszCLSID[0] == '-')
		{
			// Strip off our leading "-".
			strCLSID = &pszCLSID[1];
			bEnabled = FALSE;
		}
		else
		{
			strCLSID = pszCLSID;
			bEnabled = TRUE;
		}
		// Build path to the handler's CLSID subkey.
		strTargetKey.Format("CLSID\\%s", strCLSID);
	}
	// Open the CLSID key.
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, strTargetKey, 0, KEY_READ, &hKeyParent);
	// Try to retrieve the handler's "friendly" name and module filename.
	if (lResult == ERROR_SUCCESS)
	{
		// "Friendly" name is the default value of the CLSID subkey.
		dwLen = _MAX_PATH;
		pszModuleName[0] = '\0';
		lResult = RegQueryValueEx(hKeyParent, NULL, 0, &dwType, (LPBYTE) pszModuleName, &dwLen);
		// If successful, save the friendly name.
		if (lResult == ERROR_SUCCESS)
			strFriendly = pszModuleName;
		// Reset the buffer to an empty string.
		pszModuleName[0] = '\0';
		// Try to open the InProcServer32 subkey.
		lResult = RegOpenKeyEx(hKeyParent, "InProcServer32", 0, KEY_QUERY_VALUE, &hKeyChild);
		if (lResult == ERROR_SUCCESS)
		{
			dwLen = _MAX_PATH;
			// Module filename is the default value of the InProcServer32 subkey.
			RegQueryValueEx(hKeyChild, NULL, 0, &dwType, (LPBYTE) pszModuleName, &dwLen);
			// Expand environment strings if necessary
			if (dwType == REG_EXPAND_SZ)
			{
				// If call succeeded, copy the (possibly expanded) path back to the source buffer.
				if (ExpandEnvironmentStrings(pszModuleName, pszExpanded, _MAX_PATH))
					lstrcpy(pszExpanded, pszModuleName);
			}
			RegCloseKey(hKeyChild);
		}
		RegCloseKey(hKeyParent);
	}
	// Create new array element.
	pNewEntry = new SHELLEXT;
	if (pNewEntry == NULL)
		return FALSE;
	// Copy data into the new element.
	pNewEntry->strKeyName = strName;
	pNewEntry->strCLSID = strCLSID;
	pNewEntry->bEnabled = bEnabled;
	pNewEntry->strModuleName = pszModuleName;
	pNewEntry->strFriendly = strFriendly;
	// Expand the array to hold the new element.
	pTemp = (PSHELLEXT *) realloc(m_pShellExtArray, (m_intExtArrayCount + 1) * sizeof(PSHELLEXT));
	if (pTemp == NULL)
	{
		delete pNewEntry;
		return FALSE;
	}
	// Save (possibly changed) pointer to the expanded array.
	m_pShellExtArray = pTemp;
	// Store pointer to the new element.
	m_pShellExtArray[m_intExtArrayCount] = pNewEntry;
	// Update array count.
	++m_intExtArrayCount;
	// Signal success to caller.
	return TRUE;
}

// Rebuilds the context menu array with information
// for the specified file type.
void CContextEditApp::GetMenuHandlers(LPCTSTR pszType)
{
	char		pszKeyName[MAX_PATH],
				pszCLSID[MAX_PATH];
	HKEY		hKey1,
				hKeyParent;
	DWORD		dwIndex = 0,
				dwLen,
				dwType;
	LRESULT		lResult;
	CString		strKeyName;

	DeleteShellExtArray();
	strKeyName.Format("%s\\shellex\\ContextMenuHandlers", pszType);
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, strKeyName, 0, KEY_READ, &hKeyParent);
	if (lResult != ERROR_SUCCESS)
		return;
	while (TRUE)
	{
		dwLen = MAX_PATH;
		lResult = RegEnumKeyEx(hKeyParent, dwIndex, pszKeyName, &dwLen, NULL, NULL, NULL, NULL);
		if (lResult != ERROR_SUCCESS)
			break;
		lResult = RegOpenKeyEx(hKeyParent, pszKeyName, 0, KEY_READ, &hKey1);
		if (lResult != ERROR_SUCCESS)
			break;
		dwLen = MAX_PATH;
		lResult = RegQueryValueEx(hKey1, NULL, NULL, &dwType, (LPBYTE) pszCLSID, &dwLen);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(hKey1);
			break;
		}
		if (!AddShellExt(pszKeyName, pszCLSID))
			break;
		++dwIndex;
	}
	RegCloseKey(hKeyParent);
}

void CContextEditApp::DeleteFileType(PFTELEMENT pTarget)
{
	int			i,
				j,
				iEndMinusOne;
	PFTELEMENT	*pNew = NULL;

	iEndMinusOne = m_intTypeArrayCount - 1;
	for (i = 0; i <= iEndMinusOne; i++)
	{
		if (m_pFileTypeArray[i] == pTarget)
		{
			delete m_pFileTypeArray[i];
			for (j = i; j < iEndMinusOne; j++)
				m_pFileTypeArray[j] = m_pFileTypeArray[j + 1];
			break;
		}
	}
	--m_intTypeArrayCount;
	pNew = (PFTELEMENT*) realloc(m_pFileTypeArray, m_intTypeArrayCount * sizeof(PFTELEMENT));
	if (pNew != NULL)
		m_pFileTypeArray = pNew;
}

// Function ensures that system has correct version of COMCTL32.DLL
// Input: None.
// Return value: TRUE if DLL is found and is correct version, otherwise FALSE.
// Function displays its own error messages when appropriate, so caller only
// needs to worry about the return value.
BOOL CContextEditApp::Check_DLL_Version(void)
{
	DLLVERSIONINFO		dvi;		// Structure to hold DLL version info
	HINSTANCE			hDLL;		// Instance handle for COMCTL32.DLL
	DLLGETVERSIONPROC	pFunc;		// Pointer to DllGetVersion() function.
	CString				strPrompt;

	dvi.cbSize = sizeof(DLLVERSIONINFO);			// Initialize structure.
	hDLL = LoadLibrary("COMCTL32.DLL");				// Attempt to load an instance of COMCTL32.DLL
	if (hDLL == NULL)								// Signal error if failure.
	{
		::MessageBox(NULL, "Unable to load COMCTL32.DLL", m_pszAppName, MB_OK | MB_ICONSTOP);
		return FALSE;		// Report failure to caller.
	}
	// Try to get pointer to exported "DllGetVersion" function.
	pFunc = (DLLGETVERSIONPROC) GetProcAddress(hDLL, "DllGetVersion");
	if (pFunc == NULL)		// Report error if function not found.
	{
		FreeLibrary(hDLL);
		::MessageBox(NULL, "Unable to access COMCTL32.DLL", m_pszAppName, MB_OK | MB_ICONSTOP);
		return FALSE;		// Report failure to caller.
	}
	pFunc(&dvi);			// Call DLLGetVersion to fill in the version info structure.
	FreeLibrary(hDLL);		// Done with the COMCTL32.DLL, so release it.
	if ((dvi.dwMajorVersion > 4) ||				// DLL version must be 4.70 or later.
		((dvi.dwMajorVersion == 4) && (dvi.dwMinorVersion >= 70)))
		return TRUE;		// If it is, report success to caller.
	else					// If it's not, display appropriate message.
	{
		strPrompt.Format("This program requires version 4.70 or later of COMCTL32.DLL.\n"
						"The version currently on your system is %u.%u.%u.\n\n"
						"At the time this program was written, version 5.80.2614.3600\n"
						"of this DLL was available from the Microsoft Download Center at\n\n"
						"http://www.microsoft.com/downloads/release.asp?ReleaseID=11916",
						dvi.dwMajorVersion,
						dvi.dwMinorVersion,
						dvi.dwBuildNumber);
		::MessageBox(NULL, strPrompt, m_pszAppName, MB_OK | MB_ICONSTOP);
		return FALSE;		// Report failure to caller.
	}
}

// Removes the specified shell command from the array.
void CContextEditApp::DeleteShellCommand(PSHELLCOMMAND pTarget)
{
	int				i,
					j,
					iEndMinusOne;
	BOOL			bDeleted = FALSE;
	PSHELLCOMMAND	pThis;

	iEndMinusOne = m_intShellCommandCount - 1;
	for (i = 0; i <= iEndMinusOne; i++)
	{
		// Get pointer to the current array element.
		pThis = m_pShellCommands[i];
		// Is it the one to be deleted?
		if (pThis == pTarget)
		{
			// Yes ... update enabled/disabled command count accordingly.
			if (pThis->bIsEnabled)
				--m_intEnabledCommands;
			else
				--m_intDisabledCommands;
			// Delete the command.
			delete pThis;
			bDeleted = TRUE;
			// Compact the array.
			for (j = i; j < iEndMinusOne; j++)
				m_pShellCommands[j] = m_pShellCommands[j + 1];
			break;
		}
	}
	// If command was actually deleted,
	if (bDeleted)
	{
		// Reduce the array size.
		--m_intShellCommandCount;
		// Reallocate the array accordingly.
		m_pShellCommands = (PSHELLCOMMAND*) realloc(m_pShellCommands, m_intShellCommandCount * sizeof(PSHELLCOMMAND));
	}
}
