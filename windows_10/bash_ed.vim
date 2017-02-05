
$$ 리눅스 명령어

	$ ls 
	$ grep
	$ mv
	$ cp
	$ mkdir
	$ nautilus
	$ apt-get

	
	$ objdump
				attackme 파일을 덤프해서 어셈블리 명령어 중 ret 명령어를 검색한다
				$ objdump -d attackme | grep ret -B 2




	$ ldd 		
				grep 파일이 어떤 라이브러리를 사용하는지 출력합니다(ASLR 사용을 확인할 수 있다고 한다)
				$ ldd /bin/grep



	$ ipcs
				공유메모리 영역을 확인합니다
				$ ipcs -m



	$ ack
				파일 내용 중 hello_world가 들어간 내용을 검색합니다
				$ ack -k hello_world




	$ systemctl
				강제로 절전모드로 전환합니다
				$ systemctl suspend -i
				
		


	$ shutdown
				시스템을 바로 종료합니다
				$ shutdown -H now			






	$ poweroff
	$ reboot
		





	$ tcpdump





	$ nmap
				$ nmap -T4 -PN --script=default koradb.iptime.org

				
				$ nmap -T4 -PN 172.30.1.48
				




	$ snort 
				snort를 조용히 실행해서 경고로그를 생성합니다
				$ snort -q -A console -i wlp1s0 -c /etc/snort/snort.conf



















