#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os
import sys
import sqlite3
import _winreg

'''
print "======== Chrome Histroy Viewer ============\n"

os.system("taskkill /f /im chrome.exe")

con = sqlite3.connect('C:\\Users\\vdl\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\History')
cursor = con.cursor()
cursor.execute("SELECT * FROM keyword_search_terms ORDER BY url_id DESC")

count = 0

while count <= 5:
    count += 1
    data = cursor.fetchone()
    covdata = "".join(str(data))

    print "\n", covdata

    if count == 15:
        print ("\nComplete Histroy DB load - ",count ," Search keywords ")


_reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)
_key = _winreg.OpenKey(_reg, r"Software\\HNC\\Hwp\\9.0\\HwpFrame_KOR\\RecentFile", 0, _winreg.KEY_ALL_ACCESS)

try:
    count = 0
    while True:
        name, value, type = _winreg.EnumValue(_key, count)

        if isinstance(value, int):
            print ""
        else:
            print name + " : " + value.decode('UTF-16').encode('cp949')

        count += 1

except WindowsError:
    pass


'''

def Word():
    _reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)
    _key = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\14.0\\Word\\File MRU", 0, _winreg.KEY_ALL_ACCESS)

    try:
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key, count)
            print  unicode(value,'euc-kr')
            count += 1 
    except  WindowsError:
        pass


def Excel():
    _reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)
    _key = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\14.0\\Excel\\File MRU", 0, _winreg.KEY_ALL_ACCESS)

    try:
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key, count)
            print value
            count += 1
    except  WindowsError:
        pass



def PowerPoint( ):
    _reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)
    _key = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\14.0\\PowerPoint\\File MRU", 0, _winreg.KEY_ALL_ACCESS)

    try:
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key, count)
            print  value
            count += 1 
    except  WindowsError:
        pass
 


Word()
Excel()
PowerPoint()







































