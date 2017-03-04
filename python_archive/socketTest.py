#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 해킹침투코딩 p100, koradb.iptime.org의 코드를 읽어와 커맨드창에 뿌리는 코드
'''
import socket

# Build a socket and connect to google.com
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("www.google.com",80))

#send a basic http request
s.send("GET / HTTP/1.0\nHost: www.koradb.iptime.org\n\n")
page = ""

# while data is still coming back, append to our page variable
while 1:
    data = s.recv(1024)
    if data =="":
        break
    page += data

# close out socket snd print the results
s.close()
print page

