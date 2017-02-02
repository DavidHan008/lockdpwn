#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 크롬의 History 파일을 sqlite3를 사용해 키워드를 분석해본 예제 코드
'''
import os
import sys
import sqlite3

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


