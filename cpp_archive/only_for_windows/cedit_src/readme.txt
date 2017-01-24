________________________________________________________________ 

ContextEdit, Version 1.2
Copyright (c) 2001 Ziff Davis Media, Inc.
Written by Gregory A. Wolking
First Published in PC Magazine, US Edition, February 6, 2001, v20n03
http://www.pcmag.com/utilities/
________________________________________________________________ 

PLATFORMS:
Windows 95/NT4 with the WDU, and Windows 98/ME/2000.

DESCRIPTION:
ContextEdit lets you control which items appear on your context menu--the menu that appears when you right-click on an item in Windows Explorer. The context menu often contains numerous rarely-used commands. These commands come from one of two places: shell commands stored within the system Registry, and context menu handlers. The source of the menu item is transparent to the end-user, but still has an impact. Windows Explorer lets you add or remove simple shell commands, but gives you no control over context menu handlers. ContextEdit lets you control both types of context menu items. It also allows you to disable context menu items without removing them entirely. Another unique feature is the ability to add shell commands to all files regardless of type, or to all files without an associated program.

REVISION HISTORY:
Changes in Version 1.2:
- Fixed a bug that caused the program to get stuck in an endless loop when reading the registry if it encountered a circular reference (specifically, an extension key whose default value contains the name of the same key). The program also presents a warning message when you select such a key in the master list. This rare situation doesn't cause any problems for Windows itself, so ContextEdit doesn't offer to repair it.

Changes in Version 1.1:
- If a critical error occurs during its initial scan of the registry, the program now presents an error message before shutting down.
- Fixed "Unable to access the registry" error when attempting to edit existing Shell Commands or create new ones on Win95 systems.
- Added "Expand environment variables" checkbox to the Command Editor dialog. This box will be enabled only if the system supports this feature (Win95 does not).
- Fixed problem with program continuing to report associations as "broken" even after they had been repaired by the "Move to master file type" procedure.

THANKS TO OUR BETA TESTERS:
Alec Burgess
David Bookbinder
Dennis Cummins
Josh Fitzgerald
Edward Mendelson
David Morse

INSTALLATION:
ContextEdit requires the Windows Desktop Update, which is distributed with recent versions of Windows. Under Windows 95 and Windows NT 4, you must install Internet Explorer 4 to obtain the WDU. If you have already installed Internet Explorer 5, you must remove this installation, install IE4 with the WDU, and then upgrade to IE5.
	To install ContextEdit, place the component files (ContextEdit.exe, ContextEdit.hlp, and ContextEdit.cnt) in the folder of your choice, then create a shortcut to ContextEdit.exe. To remove ContextEdit, simply delete the component files.
	The only changes ContextEdit makes to your system are those shell commands and context menu handlers that you disable. ContextEdit stores the information for those disabled items in the Registry. Thus as long as your Registry is intact, even if you uninstall and reinstall ContextEdit, you will still be able to restore these items.

FILE LIST:
setup.exe       - ContextEdit installation program
readme.txt      - the file you are reading
license.txt     - PC Magazine Utilities license agreement
cedit_src.zip   - ContextEdit source code (for programmers)

SUPPORT:
Help for PC Magazine's free utilities can be obtained in our online discussion area on the World Wide Web (www.pcmag.com/utilities/support.html). You may find an answer to your question simply by reading the posted messages. The authors of current utilities generally visit this forum daily. If the author is not available and the forum sysops can't answer your question, the Utilities column editor, who also checks the forum each day, will contact the author for you.

LICENSE INFORMATION:
PC Magazine programs are copyrighted and cannot be distributed, whether modified or unmodified. Use is subject to the terms and conditions of the license agreement distributed with the programs.

----

Gregory A. Wolking, author of ContextEdit, is the primary sysop in PC Magazine's Utilities discussion area on the Web, and a frequent contributor to PC Magazine. Sheryl Canter is editor of the Utilities column and a Contributing Editor of PC Magazine.

