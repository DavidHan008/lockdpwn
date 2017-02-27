
$$ 리눅스 명령어

	$ ls 
	$ grep
	$ mv
	$ cp
	$ mkdir
	$ nautilus
	$ apt-get



	$ gcc



	
	$ gdb



	
	$ objdump
				attackme 파일의 어셈블리 명령어 중 ret 명령어를 검색한다
				$ objdump -d attackme | grep ret -B 2

	
				bof3 파일을 PLT 섹션을 intel cpu 방식으로 확인합니다
				$ objdump -d -M intel -j .plt --no ./bof3
	





	$ nm
				libc.so.7 라이브러리내에 system 함수의 주소를 확인해본다
				$ nm -D /lib32/libc.so.6 | grep system








	$ ldd 		
				bof3 프로그램 안에 공유라이브러리의 주소를 확인합니다
				$ ldd bof3

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



-----------------------------------------------------------------
# 설치해야 되는 프로그램
-----------------------------------------------------------------

	$ nmap
				$ nmap -T4 -PN --script=default koradb.iptime.org

				$ nmap -T4 -PN 172.30.1.48
				




	$ socat
				bof3 프로그램을 4000번 포트에서 엽니다
				$ socat TCP-LISTEN:4000,reuseaddr,fork EXEC:./bof3 2>/dev/null &





	$ rp 
				bof3 프로그램 안에서 pop가 들어가 있는 ROP Gadget을 검색합니다
				$ rp -f bof3 | grep pop
	
				
				bof3 파일에서 Gadget 크기가 3인 unique한? 코드를 검색합니다
				$ rp -f bof3 -r 3 --unique | grep pop






	$ snort 
				snort를 조용히 실행해서 경고로그를 생성합니다
				$ snort -q -A console -i wlp1s0 -c /etc/snort/snort.conf



















