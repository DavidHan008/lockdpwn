@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by CONTEXTEDIT.HPJ. >"hlp\MenuAssistant.hm"
echo. >>"hlp\ContextEdit.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ContextEdit.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ContextEdit.hm"
echo. >>"hlp\ContextEdit.hm"
echo // Prompts (IDP_*) >>"hlp\ContextEdit.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ContextEdit.hm"
echo. >>"hlp\ContextEdit.hm"
echo // Resources (IDR_*) >>"hlp\ContextEdit.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ContextEdit.hm"
echo. >>"hlp\ContextEdit.hm"
echo // Dialogs (IDD_*) >>"hlp\ContextEdit.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ContextEdit.hm"
echo. >>"hlp\ContextEdit.hm"
echo // Frame Controls (IDW_*) >>"hlp\ContextEdit.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ContextEdit.hm"
REM -- Make help for Project ContextEdit


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ContextEdit.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ContextEdit.hlp" goto :Error
if not exist "hlp\ContextEdit.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ContextEdit.hlp" Debug
if exist Debug\nul copy "hlp\ContextEdit.cnt" Debug
if exist Release\nul copy "hlp\ContextEdit.hlp" Release
if exist Release\nul copy "hlp\ContextEdit.cnt" Release
echo.
goto :done

:Error
echo hlp\ContextEdit.hpj(1) : error: Problem encountered creating help file

:done
echo.
