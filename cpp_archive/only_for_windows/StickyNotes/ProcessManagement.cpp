
#include "StdAfx.h"
#include "ProcessManagement.h"

#include <sys/timeb.h>
#include <time.h>

#include <Tlhelp32.h>

#pragma warning (disable:4996)

int GetTimeStr (char timeStr[])
{
	struct _timeb timebuffer;
	struct tm tt;

	_ftime (&timebuffer);
	tt = *localtime(&timebuffer.time);
	return sprintf (timeStr, "%04d.%02d.%02d %02d.%02d.%02d", 
		1900 + (int)tt.tm_year, 1 + (int)tt.tm_mon, (int)tt.tm_mday, 
		(int)tt.tm_hour, (int)tt.tm_min, (int)tt.tm_sec);
}

bool FindProcess(CString processName)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	if (hProcessSnap == (HANDLE)-1) {
		return false;
	}

	PROCESSENTRY32 pe; 
	memset (&pe, 0, sizeof(pe));
	pe.dwSize = sizeof(PROCESSENTRY32); 

	bool find = false;
	//프로세스를 검색한다
	for (BOOL ret = Process32First(hProcessSnap, &pe); ret; ret = Process32Next(hProcessSnap, &pe)) {
		if(_stricmp (pe.szExeFile, processName) == 0) { 
			find = true;
			break;
		} 
	}
	CloseHandle (hProcessSnap); 

	return find;
}

bool KillProcess(CString processName)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	if (hProcessSnap == (HANDLE)-1) {
		return false;
	}

	PROCESSENTRY32 pe; 
	memset (&pe, 0, sizeof(pe));
	pe.dwSize = sizeof(PROCESSENTRY32); 

	//프로세스를 검색한다
	for (BOOL ret = Process32First(hProcessSnap, &pe); ret; ret = Process32Next(hProcessSnap, &pe)) {
		if(_stricmp (pe.szExeFile, processName) == 0) { 
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID); 
			if(hProcess) {
				TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);
			}
		} 
	}
	CloseHandle (hProcessSnap); 
	return true;
}

bool StartProcess(CString m_Process)
{
	STARTUPINFO suInfo;
	memset (&suInfo, 0, sizeof(suInfo));
	suInfo.cb = sizeof(suInfo);

	PROCESS_INFORMATION procInfo;
	return CreateProcess(m_Process, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &suInfo, &procInfo) != 0;

	//procInfo.dwThreadId;
	//procInfo.dwProcessId;
}

