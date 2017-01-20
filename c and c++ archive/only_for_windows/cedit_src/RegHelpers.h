// Declarations for Registry "Helper" functions in RegHelpers.cpp
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

BOOL RegZapKey(HKEY hKeyParent, LPCTSTR pszSubKey);
BOOL RegCopyKeyData(HKEY hDest, HKEY hSource);
BOOL RegCopyKey(HKEY hDest, LPCTSTR pszDest, HKEY hSource, LPCTSTR pszSource);
BOOL RegMoveKey(HKEY hDest, LPCTSTR pszDest, HKEY hSource, LPCTSTR pszSource);
