// Defintions of Registry "helper" functions.
//
// ContextEdit version 1.2
// Copyright ?2001 Ziff-Davis Media, Inc.
// First published in PC Magazine, US Edition, Februbary 6, 2001
// Written by Gregory A. Wolking.

#include "stdafx.h"
#include "RegHelpers.h"

// Copies all data values from one registry key to another.
// IMPORTANT: CALLER MUST ENSURE THAT SOURCE AND DESTINATION
//            ARE NOT THE SAME KEY!
// Source key must be opened with at least KEY_READ access.
// Destination key must be opened with at least KEY_SET_VALUE access.
// Existing data values in the destination key that do not have
// corresponding values in the source key will not be affected.
BOOL RegCopyKeyData(HKEY hDest, HKEY hSource)
{
	DWORD	dwIndex,				// Index for value enumeration.
			dwType,					// Value data type.
			dwNameLen,				// Length of current item's name.
			dwDataLen,				// Length of current item's data.
			dwMaxNameSize,			// Length of longest value name.
			dwMaxDataSize;			// Size of largest data item.
	BYTE	*pDataBuffer = NULL;	// Pointer to buffer for value data.
	char	*pNameBuffer = NULL;	// Pointer to buffer for value names.
	LRESULT lResult;

	// Get maximum size for value names and data.
	lResult = RegQueryInfoKey(hSource, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &dwMaxNameSize, &dwMaxDataSize, NULL, NULL);
	if (lResult != ERROR_SUCCESS)
		return FALSE;
	++dwMaxNameSize;	// Value returned for name length does not include terminating NUL.
	// Allocate buffers accordingly.
	if ((pDataBuffer = (BYTE *) malloc(dwMaxDataSize)) == NULL)
		return FALSE;
	if ((pNameBuffer = (char *) malloc(dwMaxNameSize)) == NULL)
	{
		free(pDataBuffer);
		return FALSE;
	}
	dwIndex = 0;	// Initialize index for enumerating values.
	while (TRUE)
	{
		// Set buffer sizes.
		dwDataLen = dwMaxDataSize;
		dwNameLen = dwMaxNameSize;
		// Retrieve the current value's name and data.
		lResult = RegEnumValue(hSource, dwIndex, pNameBuffer, &dwNameLen, NULL, &dwType, pDataBuffer, &dwDataLen);
		if (lResult == ERROR_SUCCESS)	// If enumeration succeeds:
		{
			// Create corresponding data value in the destination key.
			lResult = RegSetValueEx(hDest, pNameBuffer, 0, dwType, pDataBuffer, dwDataLen);
			if (lResult != ERROR_SUCCESS)	// If that failed,
			{
				free(pNameBuffer);			// Free the buffers.
				free(pDataBuffer);
				return FALSE;				// Signal failure to caller.
			}
		}
		else if (lResult == ERROR_NO_MORE_ITEMS)	// No values left?
		{
			break;									// Yes .. we're done.
		}
		else		// Any other result from querying the value?
		{
			free (pNameBuffer);	// Free the buffers.
			free (pDataBuffer);
			return FALSE;		// Signal failure to caller.
		}
		++dwIndex;	// Next item from source key.
	}
	// Free the buffers.
	free(pNameBuffer);
	free(pDataBuffer);
	// Signal success to caller.
	return TRUE;
}

// Deletes the specified registry subkey.
// hKeyParent is the parent of the key to be removed.
//            It must be either a root key (HKEY_LOCAL_MACHINE, etc.)
//            or a subkey opened with at least KEY_READ access.
// pszSubKey  is the name of the key to be removed, which must exist.
//
// This function is necessary for compatibility with Windows NT, in which
// the RegDeleteKey function cannot delete a key that contains subkeys.
// If the specified key has subkeys, this function calls itself recursively
// to delete each "branch" from the bottom up.
BOOL RegZapKey(HKEY hKeyParent, LPCTSTR pszSubKey)
{
	HKEY		hKeyTarget;				// Handle to specified subkey.
	BOOL		bResult = TRUE;			// Function result (default == success)
	char		*pszNameBuffer = NULL;	// Buffer for subkey names.
	DWORD		dwLen,					// Length of current subkey name.
				dwMaxNameLen,			// Maximum buffer size.
				dwSubkeyCount;			// Number of subkeys.
	LRESULT		lResult;				// Return value for Registry functions.

	// Open the target key.
	lResult = RegOpenKeyEx(hKeyParent, pszSubKey, 0, KEY_READ, &hKeyTarget);
	if (lResult != ERROR_SUCCESS)
		return FALSE;
	// See if the key contains any subkeys, and get the length of the longest subkey name.
	lResult = RegQueryInfoKey(hKeyTarget, NULL, NULL, NULL, &dwSubkeyCount, &dwMaxNameLen, NULL, NULL, NULL, NULL, NULL, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(hKeyTarget);
		return FALSE;
	}
	// If there are any subkeys,
	if (dwSubkeyCount > 0)
	{
		++dwMaxNameLen; // Length returned by RegQueryInfoKey does not include terminating NULL.
		// Allocate buffer to hold subkey names.
		pszNameBuffer = (char *) malloc(dwMaxNameLen);
		if (pszNameBuffer == NULL)	// Report error if unable to create the buffer.
		{
			RegCloseKey(hKeyTarget);
			return FALSE;
		}
		while (TRUE)
		{
			// Set size of buffer.
			dwLen = dwMaxNameLen;
			// Get name of first subkey.
			lResult = RegEnumKeyEx(hKeyTarget, 0, pszNameBuffer, &dwLen, NULL, NULL, NULL, NULL);
			if (lResult == ERROR_NO_MORE_ITEMS)	// No subkeys left?
			{
				break;							// We're done.
			}
			else if (lResult == ERROR_SUCCESS)		// If we got a subkey name,
			{
				if (!RegZapKey(hKeyTarget, pszNameBuffer))	// Call ourself to zap that subkey.
				{
					bResult = FALSE;
					break;
				}
			}
			else
			{
				bResult = FALSE;
				break;
			}
		}
	}
	RegCloseKey(hKeyTarget);	// Close the target key.
	free(pszNameBuffer);		// Free the name buffer.
	if (bResult)				// If successful so far,
	{
		lResult = RegDeleteKey(hKeyParent, pszSubKey);	// Try to delete the specified key.
		if (lResult != ERROR_SUCCESS)					// Signal ultimate sucess or failure.
			bResult = FALSE;
	}
	return bResult;
}

// Makes an exact copy of a registry key, including all subkeys and data.
// IMPORTANT: CALLER MUST ENSURE THAT SOURCE AND DESTINATION
//            ARE NOT THE SAME KEY!
// hDest =      Handle to parent under which the copy to be placed.
//				Must be either a root key or a subkey opened with at least KEY_WRITE access.
// pszDest =	Name of destinaion subkey.
//              If the specified subkey does not exist, it will be created.
//				If it does exist, it will be deleted before the copy is made.
//				This ensures that the contents of the copied key will be an exact
//				duplicate of the original.
// hSource =    Handle to the parent of the key be copied.
//				Must be either a root key or a subkey opened with at least KEY_READ access.
// pszSource =  Name of the subkey to be copied.
//              Must be an existing subkey of the specified parent.
BOOL RegCopyKey(HKEY hDest, LPCTSTR pszDest, HKEY hSource, LPCTSTR pszSource)
{
	char	*pNameBuffer = NULL,
			*pClassBuffer = NULL;
	HKEY	hSubSource,
			hSubDest;
	DWORD	dwNameLen,
			dwMaxNameLen,
			dwClassLen,
			dwMaxClassLen,
			dwDisp,
			dwIndex,
			dwSubKeyCount;
	LRESULT	lResult;

	if (pszSource == NULL || pszDest == NULL)
		return FALSE;
	if (pszSource[0] == '\0' || pszDest[0] == '\0')
		return FALSE;
	// Open the source key.
	lResult = RegOpenKeyEx(hSource, pszSource, 0, KEY_READ, &hSubSource);
	if (lResult != ERROR_SUCCESS)
		return FALSE;
	// Retrieve # of subkeys and required lenght for subkey name and class buffers.
	lResult = RegQueryInfoKey(hSubSource,
								NULL,
								NULL,
								NULL,
								&dwSubKeyCount,
								&dwMaxNameLen,
								&dwMaxClassLen,
								NULL, NULL, NULL, NULL, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(hSubSource);
		return FALSE;
	}
	// Returned buffer lengths do not include terminating NULL.
	++dwMaxNameLen;
	++dwMaxClassLen;
	// Allocate name and class buffers.
	pNameBuffer = (char *) malloc(dwMaxNameLen);
	if (pNameBuffer == NULL)
	{
		RegCloseKey(hSubSource);
		return FALSE;
	}
	pClassBuffer = (char *) malloc(dwMaxClassLen);
	if (pClassBuffer == NULL)
	{
		free(pNameBuffer);
		RegCloseKey(hSubSource);
		return FALSE;
	}
	// Retrieve the source key's class name.
	dwClassLen = dwMaxClassLen;
	lResult = RegQueryInfoKey(hSubSource, pClassBuffer, &dwClassLen, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (lResult != ERROR_SUCCESS)
	{
		free(pClassBuffer);
		free(pNameBuffer);
		RegCloseKey(hSubSource);
		return FALSE;
	}
	// Try to create/open the destination key.
	lResult = RegCreateKeyEx(hDest, pszDest, 0, pClassBuffer, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hSubDest, &dwDisp);
	if (lResult != ERROR_SUCCESS)
	{
		free(pClassBuffer);
		free(pNameBuffer);
		RegCloseKey(hSubSource);
		return FALSE;
	}
	if (dwDisp == REG_OPENED_EXISTING_KEY)	// If the destination key already exists,
	{
		RegCloseKey(hSubDest);				// Close it.
		if (!RegZapKey(hDest, pszDest))		// Delete it.
		{
			free(pClassBuffer);
			free(pNameBuffer);
			RegCloseKey(hSubSource);
			return FALSE;
		}
		// Create it again.
		lResult = RegCreateKeyEx(hDest, pszDest, 0, pClassBuffer, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hSubDest, &dwDisp);
		if (lResult != ERROR_SUCCESS)
		{
			free(pClassBuffer);
			free(pNameBuffer);
			RegCloseKey(hSubSource);
			return FALSE;
		}
	}
	// Copy the key's data values, if any:
	if (!RegCopyKeyData(hSubDest, hSubSource))
	{
		free(pClassBuffer);			// Free the buffers.
		free(pNameBuffer);
		RegCloseKey(hSubSource);	// Close the keys.
		RegCloseKey(hSubDest);
		RegZapKey(hDest, pszDest);	// Delete the incomplete copy.
		return FALSE;
	}
	if (dwSubKeyCount > 0)			// If the source key has any subkeys,
	{
		dwIndex = 0;
		while (TRUE)
		{
			dwNameLen = dwMaxNameLen;
			dwClassLen = dwMaxClassLen;
			lResult = RegEnumKeyEx(hSubSource, dwIndex, pNameBuffer, &dwNameLen, NULL, NULL, NULL, NULL);
			if (lResult == ERROR_NO_MORE_ITEMS)
			{
				break;
			}
			else if (lResult != ERROR_SUCCESS)
			{
				free(pClassBuffer);			// Free the buffers.
				free(pNameBuffer);
				RegCloseKey(hSubSource);	// Close the keys.
				RegCloseKey(hSubDest);
				RegZapKey(hDest, pszDest);	// Delete the incomplete copy.
				return FALSE;
			}
			if (!RegCopyKey(hSubDest, pNameBuffer, hSubSource, pNameBuffer))
			{
				free(pClassBuffer);			// Free the buffers.
				free(pNameBuffer);
				RegCloseKey(hSubSource);	// Close the keys.
				RegCloseKey(hSubDest);
				RegZapKey(hDest, pszDest);	// Delete the incomplete copy.
				return FALSE;
			}
			++dwIndex;
		}
	}
	free(pClassBuffer);			// Free the buffers.
	free(pNameBuffer);
	RegCloseKey(hSubSource);	// Close the keys.
	RegCloseKey(hSubDest);
	return TRUE;
}

// Moves a Registry subkey from one parent key to another.
// IMPORTANT: CALLER MUST ENSURE THAT SOURCE AND DESTINATION
//            ARE NOT THE SAME KEY!
BOOL RegMoveKey(HKEY hDest, LPCTSTR pszDest, HKEY hSource, LPCTSTR pszSource)
{
	if (!RegCopyKey(hDest, pszDest, hSource, pszSource))
		return FALSE;
	return RegZapKey(hSource, pszSource);
}