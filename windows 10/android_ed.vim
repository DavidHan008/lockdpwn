<안드로이드 명령어>

$$ DUMPSYS
	# 현재 시스템의 방대한 정보를 전부 확인합니다	
	$ dumpsys

	# cpu 관련 정보만 확인합니다
	$ dumpsys cpuinfo

	# wifi 정보를 확인합니다
	$ dumpsys wifi

	# 메모리 관련 정보만 확인합니다
	$ dumpsys meminfo






$$ ADB (android debugger)
	
	# 인식이 잘안될 경우 해당 서버를 종료합니다
	$ adb kill-server

	# 연결된 기기들을 봅니다
	$ adb devices

	# 쉘을 띄웁니다
	$ adb -d shell

	# apk를 설치합니다
	$ adb -d install test.apk









$$ PM (package manager)

	# 설치된 앱들을 봅니다
	$ pm list package -f

	# 사용자의 이름을 확인합니다
	$ pm list users
		
	# 모든 시스템 패키지들의 권한을 확인합니다
	$ pm list permissions -d -g 




	# 특정 앱을 삭제합니다
	$ pm uninstall com.example.MyApp















$$ AM (activity manager)

	$ START		
		# 환경설정 실행
		$ am start -a android.intent.action.MAIN -n com.android.settings/.Settings

		# 페이스북 앱 실행
		$am start -a android.intent.action.VIEW -d facebook://facebook.com/inbox  

		# sd카드 
		$ am start -a android.intent.action.VIEW -d file:///sdcard/me.vcard -t text/x-vcard  

		# 갤러리 실행 
		$ am start -a android.intent.action.GET_CONTENT -t image/jpeg  

		# 카메라 실행 
		$ am start -a android.media.action.IMAGE_CAPTURE
			





		# 환경설정 실행
		$ am start -a android.intent.action.MAIN -n com.android.settings/.Settings

		# 브라우저로 구글띄우기
		$ am start -a android.intent.action.VIEW http://www.google.com

		# 전화걸기 다이얼 입력 
		$ am start -a android.intent.action.DIAL tel:010XXXXXXX

		# 전화걸기 
		$ am start -a android.intent.action.CALL tel:010XXXXXXX


		# 문자전송 내용은 test message!! 입니다
		$ am start -a android.intent.action.SENDTO -d sms:"010XXXXXXXX" --es sms_body "test message!!" --ez exit_on_sent true
		 

		# 구글맵 실행 GPS
		$ am start -a android.intent.action.VIEW geo:37.111111-222.333333


		# 달력실행
		$ am start -n com.android.calendar/com.android.calendar.LaunchActivity

		# 비디오파일 f-16.mp4 실행
		$ am start -a android.intent.action.VIEW -d file:///sdcard/Download/F-16.mp4  -t video/mp4 -n com.sec.android.app.videoplayer/.activity.MoviePlayer

		# 그냥 비디오 플레이어만 실행
		$ am start -n com.sec.android.app.videoplayer/.activity.MoviePlayer


		# HOME 버튼
		$ am start -a android.intent.action.MAIN -c android.intent.category.HOME








 	$ STARTSERVICE # am startservice -n 패키지명/서비스경로명
 		
		$ am startservice -n com.example.echo/com.example.echo.echoservice

		





	$ BROADCAST # am broadcast -a "브로드캐스트명"
 
		$ am broadcast -a android.accounts.LOGIN_ACCOUNTS_CHANGED
 








	$ MONITOR
		# 현재 작동하는 프로세스들을 모니터링합니다
		$ am monitor 














$$ INPUT (키입력)
	
	# 카메라를 엽니다
	$ input keyevent 27

	# volume up/down 버튼입니다
	$ input keyevent 24
	$ input keyevent 25


	# 옆으로 커서 한칸 이동
	$ input keyevent 22

	# phone 창을 띄웁니다
	$ input keyevent 5

	# 화면 끄기  (26)과 같은듯
	$ input keyevent 6



	# 카메라 실행 후 사진 찍기 (2번 연속 실행)
	$ input keyevent KEYCODE_CAMERA


+ whole list of all keyevent names in android
0 -->  "KEYCODE_UNKNOWN"
1 -->  "KEYCODE_MENU"
2 -->  "KEYCODE_SOFT_RIGHT"
3 -->  "KEYCODE_HOME"
4 -->  "KEYCODE_BACK"
5 -->  "KEYCODE_CALL"
6 -->  "KEYCODE_ENDCALL"
7 -->  "KEYCODE_0"
8 -->  "KEYCODE_1"
9 -->  "KEYCODE_2"
10 -->  "KEYCODE_3"
11 -->  "KEYCODE_4"
12 -->  "KEYCODE_5"
13 -->  "KEYCODE_6"
14 -->  "KEYCODE_7"
15 -->  "KEYCODE_8"
16 -->  "KEYCODE_9"
17 -->  "KEYCODE_STAR"
18 -->  "KEYCODE_POUND"
19 -->  "KEYCODE_DPAD_UP"
20 -->  "KEYCODE_DPAD_DOWN"
21 -->  "KEYCODE_DPAD_LEFT"
22 -->  "KEYCODE_DPAD_RIGHT"
23 -->  "KEYCODE_DPAD_CENTER"
24 -->  "KEYCODE_VOLUME_UP"
25 -->  "KEYCODE_VOLUME_DOWN"
26 -->  "KEYCODE_POWER"
27 -->  "KEYCODE_CAMERA"
28 -->  "KEYCODE_CLEAR"
29 -->  "KEYCODE_A"
30 -->  "KEYCODE_B"
31 -->  "KEYCODE_C"
32 -->  "KEYCODE_D"
33 -->  "KEYCODE_E"
34 -->  "KEYCODE_F"
35 -->  "KEYCODE_G"
36 -->  "KEYCODE_H"
37 -->  "KEYCODE_I"
38 -->  "KEYCODE_J"
39 -->  "KEYCODE_K"
40 -->  "KEYCODE_L"
41 -->  "KEYCODE_M"
42 -->  "KEYCODE_N"
43 -->  "KEYCODE_O"
44 -->  "KEYCODE_P"
45 -->  "KEYCODE_Q"
46 -->  "KEYCODE_R"
47 -->  "KEYCODE_S"
48 -->  "KEYCODE_T"
49 -->  "KEYCODE_U"
50 -->  "KEYCODE_V"
51 -->  "KEYCODE_W"
52 -->  "KEYCODE_X"
53 -->  "KEYCODE_Y"
54 -->  "KEYCODE_Z"
55 -->  "KEYCODE_COMMA"
56 -->  "KEYCODE_PERIOD"
57 -->  "KEYCODE_ALT_LEFT"
58 -->  "KEYCODE_ALT_RIGHT"
59 -->  "KEYCODE_SHIFT_LEFT"
60 -->  "KEYCODE_SHIFT_RIGHT"
61 -->  "KEYCODE_TAB"
62 -->  "KEYCODE_SPACE"
63 -->  "KEYCODE_SYM"
64 -->  "KEYCODE_EXPLORER"
65 -->  "KEYCODE_ENVELOPE"
66 -->  "KEYCODE_ENTER"
67 -->  "KEYCODE_DEL"
68 -->  "KEYCODE_GRAVE"
69 -->  "KEYCODE_MINUS"
70 -->  "KEYCODE_EQUALS"
71 -->  "KEYCODE_LEFT_BRACKET"
72 -->  "KEYCODE_RIGHT_BRACKET"
73 -->  "KEYCODE_BACKSLASH"
74 -->  "KEYCODE_SEMICOLON"
75 -->  "KEYCODE_APOSTROPHE"
76 -->  "KEYCODE_SLASH"
77 -->  "KEYCODE_AT"
78 -->  "KEYCODE_NUM"
79 -->  "KEYCODE_HEADSETHOOK"
80 -->  "KEYCODE_FOCUS"
81 -->  "KEYCODE_PLUS"
82 -->  "KEYCODE_MENU"
83 -->  "KEYCODE_NOTIFICATION"
84 -->  "KEYCODE_SEARCH"
85 -->  "TAG_LAST_KEYCODE"















$$ SVC (service)

	# 와이파이 켜기/끄기
	$ svc wifi enable
	$ svc wifi disable



	# 시스템 전원끄기, 재부팅
	svc power shutdown
	svc power reboot



	# 데이터 통신 설정/해제
	svc data enable
	svc data disable







$$ SCREENCAP (화면 캡처)
	# 현재화면을 캡처해서 hello.png 파일로 저장합니다
	$ screencap /sdcard/Download/hello.png




$$ SCREENRECORD (화면 녹화)

	# 화면을 녹화해서 test.mp4 파일로 저장합니다
	$ screenrecord --verbose /sdcard/Download/test.mp4












# 해당 파일의 syntax를 sshdconfig로 설정합니다
# vim:ft=sshdconfig

