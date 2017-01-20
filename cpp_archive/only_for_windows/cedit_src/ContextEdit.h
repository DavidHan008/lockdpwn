// ContextEdit.h : main header file for the ContextEdit application
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#if !defined(AFX_MENUASSISTANT_H__62F4BA05_A9B4_11D4_A4C7_00A0CC307F9C__INCLUDED_)
#define AFX_MENUASSISTANT_H__62F4BA05_A9B4_11D4_A4C7_00A0CC307F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define	FT_ARRAY_INCREMENT 32
#define EXT_ARRAY_INCREMENT 32

// Structure for file type array.
typedef struct
{
	CString strType;				// Registry key name.
	CString strFriendly;			// Master file type (for extensions) or description (for master file types)
	BOOL	bIsExt;					// TRUE = this is an "extension" key.
	BOOL	bHasCommand;			// TRUE = this key has shell commmands registered.
	BOOL	bHasDisabledCommand;	// TRUE = this key has disabled shell commands.
	BOOL	bHasHandler;			// TRUE = this key has context menu handlers.
	BOOL	bIsSystemType;			// TRUE = this is a "system" file type.
	BOOL	bIsBroken;				// TRUE = this extension key refers to a master file type that does not exist.
} FTELEMENT;
// Pointer to file type structure.
typedef FTELEMENT* PFTELEMENT;

// Structure for shell commands
typedef struct
{
	CString strCommand;			// Command name/registry key name.
	CString strCommandLine;		// Command line.
	CString strMenuText;		// Menu text.
	CString strDDEexec;			// DDE command
	CString strDDEnotrunning;	// DDE "app not running" command.
	CString strDDEapp;			// DDE application name.
	CString strDDEtopic;		// DDE topic.
	BOOL	bIsEnabled;			// TRUE = this command is currently enabled.
	BOOL	bIsDefault;			// TRUE = this command is currently the default command.
	BOOL	bUseDDE;			// TRUE = this command uses DDE.
	BOOL	bExpandCmdLine;		// TRUE = command line is of type REG_EXPAND_SZ
} SHELLCOMMAND;
// Pointer to shell command structure.
typedef SHELLCOMMAND* PSHELLCOMMAND;

// Structure for context menu handler information.
typedef struct
{
	CString		strKeyName;		// Name of HKCR\[file type]\ShellEx\ContextMenuHandlers\ subkey.
	CString		strCLSID;		// (default) value of the pstrKeyName subkey.
	CString		strModuleName;	// Name of code module.
	CString		strFriendly;	// "Friendly name" of this handler.
	BOOL		bEnabled;		// Handler status.
} SHELLEXT;
// Pointer to context menu handler structure.
typedef SHELLEXT* PSHELLEXT;

/////////////////////////////////////////////////////////////////////////////
// CContextEditApp:
// See ContextEdit.cpp for the implementation of this class
//

class CContextEditApp : public CWinApp
{
public:
	// Member variables
	int				m_intExtArrayCount;
	int				m_intTypeArraySize;
	int				m_intTypeArrayCount;
	int				m_intShellCommandCount;
	int				m_intDisabledCommands;
	int				m_intEnabledCommands;
	BOOL			m_bAllowExpansion;
	PSHELLEXT		*m_pShellExtArray;
	PFTELEMENT		*m_pFileTypeArray;
	PSHELLCOMMAND	*m_pShellCommands;
	// Member functions
	CContextEditApp();
	BOOL	AddFileType(LPCTSTR pszType, BOOL bForce = FALSE);
	BOOL	AddShellCommand(PSHELLCOMMAND pCommand);
	BOOL	CommandExists(LPCTSTR pszCommand, int iSearchType);
	BOOL	GetFileTypes(void);
	BOOL	GetMenuCommands(LPCTSTR pszType);
	void	DeleteFileType(PFTELEMENT pTarget);
	void	DeleteShellCommand(PSHELLCOMMAND pTarget);
	void	GenerateCommandName(LPCTSTR pszOldName, CString& strNewName);
	void	GetMenuHandlers(LPCTSTR pszType);

protected:
	BOOL	AddShellExt(LPCTSTR pszName, LPCTSTR pszCLSID);
	BOOL	Check_DLL_Version(void);
	BOOL	GetCommands(HKEY hKeyParent, char *pszDefaultCommand, BOOL bEnabled);
	void	CheckExtensionLinks(void);
	void	DeleteCommandArray(void);
	void	DeleteFileTypeArray(void);
	void	DeleteShellExtArray(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContextEditApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CContextEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUASSISTANT_H__62F4BA05_A9B4_11D4_A4C7_00A0CC307F9C__INCLUDED_)
