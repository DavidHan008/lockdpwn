<POWERSHELL 활용>


## GET-...

    " PROCESS 프로세스 정보를 확인합니다
(gps)# get-process 


	" PROCESS [s] 로 시작하는 모든 프로세스를 확인합니다
	#  get-process [s]*


	" PROCESS 어떤 프로세스가 700개 이상의 핸들을 점유하고 있는 지 확인합니다
	# get-process | where handles -gt 700 | sort cpu -descending


	" PROCESS workingset 메모리가 100M 이상인 프로세스를 확인합니다
	# get-process | where-object {$_.workingset -gt 100mb} | sort pm -descending


	" PROCESS 프로세스 중 마지막 10개만 정렬해서 htm 문서화합니다
	# get-process | select-object -last 10 | select-object name, handle, cpu, id, workingset | convertto-html | out-file c:\process.htm


	" PROCESS 프로세스 이름이 sv로 시작하는 프로세스를 확인합니다
	# get-process | where ProcessName -Like sv*


	" PROCESS gvim 프로세스의 자세한 정보를 확인합니다
	# get-process gvim | format-list *



	"" PROCESS wmi*로 시작하는 프로세스를 전부 종료합니다
	# get-process | where processname -like wmi*  | kill


	"" PROCESS vmw*로 시작하는 프로세스를 전부 종료합니다
	# get-process | where processname -like vmw* | stop-process -Force











	" WMIOBJECT win32_pingstatus를 이용해 IP를 확인합니다
	# get-wmiobject win32_pingstatus -filter "address='localhost'"

	"" WMIOBJECT win32_logicaldisk를 이용해 c:\ 정보를 확인합니다
	# get-wmiobject win32_logicaldisk


	"" WMIOBJECT 설치된 프로그램 중 sql이 포함된 프로그램을 확인합니다
	# get-wmiobject win32_product | where-object -filterscript { $_.tostring() -match "sql"}











	" CHILDITEM dir 과 비슷한 명령어입니다
(dir)# get-childitem 

	
	"" CHILDITEM 현재 폴더에서 *.html 파일 중 100mb 이하인 파일을 모두 삭제합니다
	# get-childitem .\* -include *.html | where-object -filterscript { $_.length -lt 100mb}  | remove-item -force


	"" CHILDITEM 해당 폴더에서 .jpg 파일을 전부 찾은 다음 이름순에 따라 겹치는 항목 없이 정렬합니다
	# get-childitem c:\users\gyurs\desktop\edward\ -include *.jpg -recurse | sort-object -property directoryname -unique



	"" CHILDITEM 현재 폴더에 있는 .jpg 파일들 중 20160101 이후에 수정되거나 생성된 파일만 해당 경로로 강제로 복사합니다 (백업시 사용)
	# get-childitem .\* -recurse -include *.jpg | where-object {($_.lastwritetime -gt 2016-01-01) -and ($_.creationtime -gt 2016-01-01)} | copy-item -destination c:\users\gyurs\downloads\ -force


	"" CHILDITEM c드라이브 전체에서 최근 7일동안 수정된 모든 파일을 확인합니다
	# get-childitem -recurse c:\ | ? {$_.lastwritetime -gt (get-date).adddays(-7)}






	" PSDRIVE 현재  드라이브 정보를 조회할 수 있습니다
	# get-psdrive

	




    " COMMAND 특정 명령어의 커맨드 리스트를 보여줍니다
    # get-command get-member
	
    
    " COMMAND form이라는 동사 커맨드가 들어간 커맨드를 찾을 때 사용합니다
    # get-command -verb *form*






    " HELP 특정 커맨드의 사용법을 알려줍니다 
    # get-help get-member


    " HELP GET-MEMBER의 상세한 설명을 확인합니다
    # get-help get-member -detailed 	


    " HELP GET-MEMBER의 모든 설명을 봅니다
    # get-help get-member -full

	
	

    " ALIAS 모든 별칭의 리스트를 볼 수 있습니다 
    # get-alias




    " DATE 현재의 시간을 구합니다
    # get-date 







	" ITEM c:\Windows 폴더에 가장 최근 접근한 시간을 보여줍니다
	# (get-item C:\Windows).LastAccessTime

	" ITEM c:\Windows\의 모든 파일을 w를 제외하고 보여줍니다
	# get-item c:\Windows\*.* -exclude w*






	" HISTORY 지금까지 입력한 command의 목록을 볼 수 있습니다
	# get-history






	"" SCHEDULEDTASK ashley라는 이름의 예약작업 정보를 확인합니다
	# Get-ScheduledTask | where taskname -like *ashley* | fl * 








	" EVENTLOG 이벤트로그 목록을 확인합니다
	# get-eventlog -list


	" EVENTLOG 이벤트로그를 20160805 이후에 생성된 installer 구문이 들어간 로그를 10개만 확인합니다
	# get-eventlog -logname application -message *installer* -after 2016-08-05 -newest 10 


	"" EVENTLOG 이벤트로그(6009)로 시스템 부팅 시 발생한 로그를 확인합니다
	# get-eventlog system | Where-Object {$_.eventid -eq 6009} | more


	"" EVENTLOG 이벤트로그를 통해 에러가 났던 로그를 확인합니다 (format-table형식으로)
	# get-eventlog system | Where-Object {$_.entrytype -match "error"} | format-table eventid, source, timewritten -autosize | more










	"" SERVICE 현재 running 상태인 서비스 목록을 확인합니다
(gsv)# get-service  | where-object {$_.status -eq "running"}


	"" SERVICE running 서비스 중에서 sql 글자가 들어간 서비스를 검색합니다
	# get-service  | where-object {$_.status -eq "running"} | where Name -like *sql*	


	"" SERVICE sql*로 시작하는 프로세스 중 동작 중인 프로세스를 종료합니다
	# get-service | where Name -like sql* |where status -eq running | Stop-Service -Force








	"" APPXPACKAGE 파워쉘을 이용해 microsoft EDGE를 설치합니다
	# get-appxpackage -allusers -name microsoft.microsoftedge | foreach {add-appxpackage -disabledevelopmentmode -register "$($_.installlocation)\appxmanifest.xml" -verbose}


	"" APPXPACKAGE get started 윈도우 10 app을 삭제합니다
	# get-appxpackage *getstarted* | remove-appxpackage






	"" CIMINSTANCE 현재 동작 중인 서비스 정보를 확인합니다
	$ get-ciminstance win32_service -filter "startmode ='auto'"
















## STOP-...


	" PROCESS lmgrd 프로세스를 종료하면 어떤 결과가 발생할 지 예측합니다
	# stop-process -name lmgrd -whatif


	" PROCESS lmgrd 프로세스를 종료할 때 확인 프롬프트를 띄웁니다
	# stop-process -name lmgrd -confirm
















	
## SET-...
	" EXECUTIONPOLICY 스크립트 실행 보안을 해제합니다
	# set-executionpolicy remotesigned 


	" EXECUTIONPOLICY 공유폴더에 위치한 서명안된 스크립트를 실행합니다
	# set-executionpolicy unrestricted










## EXPORT-..., IMPORT-...
		
	
	" CSV process 목록을 csv로 저장시킨 후 정렬해서 불러옵니다
	# ps | export-csv pslist.csv
	# import-csv pslist.csv | select-object starttime | sort processname -Descending
	
	
	






## NEW-... 


	" ITEM mkdir과 비슷하게 폴더를 만듭니다
(ni)# new-item -type directory -path "path_name"

	


	"" ITEM 새로운 txt 파일을 내용을 갖춘채로 만듭니다
	# new-item .\new_file.txt -type file -force -value "this is text added to the file" 




	" ITEM 디렉토리를 만들면 어떤 결과물이 나올지를 확인합니다(whatif)
	# new-item -path c:\ -name dirtest -itemtype directory -whatif	

        








## REMOVE-...

	"" ITEM alias로 등록되어 있는 get_event를 지웁니다
	# remove-item alias::get_event













## .NET FRAMEWORK
	
	" MATH::POW  .net에서 함수를 가져와 2의 3승을 계산합니다
	# [math]::pow(2,3)









===================================================================================================



<POWERSHELL 스크립트>




## show_uptime.ps1 { $Machine }

    " 지정 한 서버의 uptime 을 출력합니다.
    param([string] $Machine = ".")

    " Win32_OperationSystem 오브젝트를 변수에 저장.
    $OS = Get-WmiObject Win32_OperatingSystem -ComputerName $Machine

    " 시스템 관리용 시간 값을 일반적인 시간 값으로 변경하여 변수에 저장.
    $LastBootUpTime = [System.Management.ManagementDateTimeconverter]::ToDateTime($OS.LastBootUpTime)


    " 현재 시간을 구함.
    $Now = Get-Date

    " Uptime 계산.
    $UpTime = $Now - $LastBootUpTime

    " 각 값을 계산하여 string 형식으로 변환 후 출력
    [string]$UpTime.Days + " Days, " + [string]$UpTime.Hours + " Hours, " + [string]$UpTime.Minutes + " Minutes."













===================================================================================================



<$ 변수의 활용>


## $ Variables

	# $PSVersionTable  " PowerShell 버전을 확인할 수 있습니다

	# $env:computername " ComputerName 컴퓨터 이름을 확인합니다





## EXAMPLES
	
	# 1
    	
	$a = 5
    $a.gettype()   " .net 내장타입을 알 수 있습니다 
    $a.gettype().name   " .net의 내장타입을 알 수 있습니다2






	# 2 (iexplore 프로세스를 여는 예제코드)
	
	$ie = new-object -comobject "internetexplorer.application"
	$ie | get-member -membertype method
	$ie.navigate("http://www.naver.com")
	$ie.visible = $true



	# 3 (%userprofile% 로 이동합니다)
		
	cd $env:userprofile




	# 4 (schtasks에서 ashley 글자가 들어간  예약내용을 확인합니다)

	$tasks = schtasks.exe /query /fo csv | ConvertFrom-Csv
	$tasks | Where-Object {$_.taskname -like "*ashley*"}












===================================================================================================

<POWERSHELL 함수>



## Variable Functions 


	"" 핑을 날려 서버상태를 확인합니다
	# pingsrv "ip_adrress" 

	function pingsrv ([string] $srv )
	{
    $wmiobj=get-wmiobject win32_pingstatus -filter "address='$srv'" 
    if($wmiobj.statuscode -eq 0)
   {
        write-host $srv "연결 옥헤이~!!"
   }
   else
   {
        write-host $srv " 묵비권을 행사 중..."
   }
	}



	"" POWERSHELL 프롬프트 형식을 바꿉니다
	# Prompt  

	function prompt
	{
	$historyList = @(get-history)
	if($historyList.count -gt 0)
	{
	$lastcommand = $historyList[$historyList.count - 1]
	$lastid = $lastcommand.id   }
	write-host ("PS(" + ($lastid+1) + ") " + $(get-location) +">") -nonewline
	return " "
	}	














