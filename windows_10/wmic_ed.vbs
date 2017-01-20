
<WMIC 명령어 활용>

	' OS 관련정보 출력 (간략하게)
	# wmic os list brief /format:list  

	' OS 정보를 html 형식으로 출력해서 확인합니다
	# wmic /output:osinfo.html os get /format:hform  

	'' OS 시스템을 종료하거나 리부팅합니다 
	# wmic os where "status='ok'" call shutdown
	# wmic os where "status='ok'" call reboot







	'' LOGON 모든 로그온 세션의 목록을 확인합니다
	# wmic logon list full /format:list | more




	'' ENVIRONMENT 환경설정 목록을 확인합니다
	# wmic environment list full /format:list | more




	'' DESKTOP 데스크탑 화면 설정을 확인합니다
	# wmic desktop list full /format:list | more






	' CPU 관련정보 출력 (간략하게)
	# wmic cpu list brief /format:list






	' LOGICALDISK 관련정보를 확인합니다
	# wmic logicaldisk where drivetype=3 get name,size,freespace,systemname /format:list  




	' VOLUME 볼륨 정보를 확인합니다
	# wmic volume list brief /format:list 





	' SERVICE 정보를 확인합니다
	# wmic service list brief /format:list

	' SERVICE 정보를 html table 형식으로 출력해서 확인합니다
	# wmic /output:service.html service list brief /format:htable 

	'' SERVICE %ora% 구문이 들어가있는 이름의 서비스를 확인합니다
	# wmic service where "name like '%ora%'" list brief

	
	'' SERVICE 특정 서비스를 시작하거나 중지합니다
	# wmic service where name="service_name" call startservice
	# wmic service where name="service_name" call stopservice








	' COMPUTERSYSTEM 정보를 html 형식으로 출력해서 확인합니다
	# wmic /output:compsystem.html computersystem get /format:hform 




			

	'  BIOS 컴퓨터 s/n 넘버 확인하기
	# wmic bios get serialnumber 



	' MEMORYCHIP 메모리 확인하기
	# wmic memorychip get banklabel, capacity


	
	' PATH 프로세스 시작 (생성)시간 확인하기
	# wmic path win32_processor get numberofcores, numberoflogicalprocessors, processorid






	' PROCESS processid가 7332인 프로세스의 정보를 간략하게 확인합니다
	# wmic process where processid=7332 list brief /format:list


	' PROCESS 해당 프로세스를 종료합니다
	# wmic process where processid=7836 delete


	' PROCESS 해당 프로세스를 디버깅합니다
	# wmic process where processid=5256 call attachdebugger


	'' PROCESS 해당 cmd 명령을 실행합니다 
	# wmic process call create "cmd.exe /c ipconfig" >> result.txt


	'' PROCESS iexplore.exe 를 종료합니다
	# wmic process where name="iexplore.exe" call terminate


	'' PROCESS notepad.exe 의 우선순위를 64로 설정합니다 
	# wmic process where name="notepad.exe" call setpriority 64








	'' CSPRODUCT 장비의 사양을 확인합니다
	# wmic csproduct list brief /format:list





	'' DISKDRIVE 디스크 모델명을 확인합니다 
	# wmic diskdrive list brief /format:list






	'' STARTUP 시작프로그램 목록을 확인합니다
	# wmic startup list brief



	'' PRODUCT 설치된 프로그램 리스트를 확인합니다
	# wmic product get name 


	'' PRODUCT  설치된 프로그램을 삭제합니다
	# wmic product where name="Adobe Reader 9" call uninstall




	'' USERACCOUNT 이름에 ad가 포함된 계정을 확인합니다
	# wmic useraccount where "name like '%ad%'" list full
	

	'' USERACCOUNT 관리자(administrator)의 이름을 edward로 바꿉니다
	# wmic useraccount where name="administrator" call rename name="edward"







	'' SYSDRIVER 시스템 드라이버를 간략하게 확인합니다
	# wmic sysdriver list brief /format:list






---------------------------------------------------------------------------------------------------------------------------------

<Batch 스크립트>

'' OS, COMPUTERSYSTEM, SERVICE 관련 정보를 수집하는 스크립트입니다
# getsysteminfo.bat

	@echo off
	if %1$==$ (
	 rem use the localcomputername if nothing is specified
		set computer=%computername%
	) else (
		rem use the computername passed as a parameter
		set computer=%1
	)

	rem  Creating report for %computer%
	set htmlfile=%computer%.html

	rem redirect wmic output to NULL since we don't really need to see it
	wmic OS get /format:hform   > "%htmlfile%"
	wmic computersystem get /format:hform  >> "%htmlfile%"
	wmic service where state="running" get caption,name,pathname,state,status,acceptpause,acceptstop,processid,systemname,startname  /format:htable >> "%htmlfile%"
	wmic service where state="stopped" get caption,name,pathname,state,status,acceptpause,acceptstop,processid,systemname,startname  /format:htable >> "%htmlfile%"
	wmic csproduct list brief /format:htable >> "%htmlfile%"
	wmic cpu list brief /format:htable >>"%htmlfile%"
	wmic diskdrive list brief /format:htable >>"%htmlfile%"
	wmic logicaldisk list brief /format:htable >>"%htmlfile%"
	wmic volume list brief /format:htable >>"%htmlfile%"
	wmic NICCONFIG list brief /format:htable >>"%htmlfile%"



















----------------------------------------------------------------------------------------------------------------------------------

<여러가지 옵션들>

	# /format : csv, list ...
	
	# list full, brief, free, status, system...


	'' OS의 속성을 확인할 수 있습니다 (컬럼)
	# wmic os get /?





----------------------------------------------------------------------------------------------------------------------------------

<WMI란 무엇인가?>


## Windows Management Instrumentation 
	# WMI는 네트워크에서 관리정보를 액세스하고 공유하는 표준을 만들기 위해 Microsoft에서 구현한 프로그램입니다

	# WMIC(Windows Management Instrumentation Command-line) 이란
		# WMI에 대한 간단한 명령줄 프로그램입니다


	# 


















''http://blog.naver.com/diadld2?Redirect=Log&logNo=30157625015
''참고사이트
''http://www.simpleisbest.net/archive/2005/10/18/260.aspx
''WMI 고수
''http://www.seobangnim.com/zbxe/?document_srl=1415&mid=Etc
''WMI란 무엇인가?
