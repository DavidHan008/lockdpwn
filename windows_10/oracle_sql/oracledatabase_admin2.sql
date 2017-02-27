
--------------------------------------------------------------------------------------------------

	$$ 폴더 ORACLE_HOME/RDBMS/ADMIN/
		$ 여기 폴더의 1594개 파일은 절대 수정되거나 삭제되면 안됩니다
		$ 삭제되면 DBCA로 DB를 만들 때 안만들어진다고 합니다
		$ 이 폴더 안에 catalog.sql, catproc.sql 
   		$ 두 파일이 메인파일로 나머지 1300개의 sql 구문을 로딩합니다
   		$ utl* 로 시작하는 69개 파일은 사용자가 편집해도 가능하다고 하지만 (오라클 의견) 왠만하면 안거드는게 낫습니다



<SYS 사용자 관리>


## 'SYSDBA'와 'SYSOPER' 그리고 'SYS' 계정
	# SYSDBA : DB 관리자 기능을 가진 권한입니다
	# SYSOPER : DB 기동/중지만 가능한 권합입니다
	# 두 권한 모두 SYS 계정에만 부여되어 있습니다


	# 'LINUX'는 oinstall, dba를 통해 관리자 그룹을 설정할 수 있습니다
		# oinstall 그룹 : 소프트웨어 설치/삭제를 책임지는 그룹입니다
		# dba 그룹 : 데이터베이스 관리를 하는 그룹입니다

	# 'WINDOWS'는 자동으로 ora_dba 그룹을 생성해 운영체제 계정을 등록시킵니다



	# SYS 계정의 인증방식 2개
		# OS 인증
			# conn / as sysdba : 많이 써왔던 로그인 방식으로 계정명/패스워드를 확인하지 않습니다 
			# 로컬접속의 경우에만 사용가능합니다
			# sqlnet.ora 파일에서 (NTS)를 (NONE)으로 바꾸면 OS 인증방식이 더이상 작동하지 않습니다 



		# PASSWORD-FILE 인증
			# 원격접속시 리스너가 별도로 저장한 PASSWORD-FILE을 사용해 계정명/패스워드를 확인 후 접속을 허용합니다
			# ORACLE_HOME\database\PWDorlc.ora 파일을 통해 관리합니다 
			
			# REMOTE_LOGIN_PASSWORDFILE 초기화 파라미터
				# EXCLUSIVE : PASSWORD-FILE 을 쓰지만 공유하지 않습니다 (DEFAULT)
				# SHARED : PASSWORD-FILE 인증방식을 공유합니다
					# PWDorcl.ora 파일 수정을 할 수 없습니다.



				# PWDorcl.ora 파일이 없을 경우 (장애조치)
					# 더 이상 원격접속이 안됩니다 conn sys/oracle4U@orcl as sysdba 에러!
					# orapwd를 사용해 패스워드 파일을 생성합니다


orapwd file=C:\app\buk213\product\11.2.0\dbhome_1\database\PWDorcl.ora 
entries=3 password=oracle4U








	# 원격접속
		# 동적(DYNAMIC) 서비스 등록 : MOUNT, OPEN 상태에서만 SYSDBA로 접속할 수 있습니다
		
		# 고정(STATIC) 서비스 등록 : SHUTDOWN, NOMOUNT, MOUNT, OPEN 상태 모두 SYSDBA 접속 가능합니다
		


SELECT sys_context('USERENV','OS_USER') FROM dual;  -- 현재 사용자 정보를 봅니다







	# 일반 데이터베이스 유저에게 SYS 권한을 부여한 경우	


GRANT sysdba TO hr ; -- hr 유저에게 SYSDBA 권한을 줍니다

conn hr/oracle4U@orcl  -- 그냥 hr 계정으로 접속합니다

conn hr/oracle4U@orcl as sysdba  -- SYSDBA 권한을 가진 계정으로 접속합니다

SELECT * FROM v$pwfile_users ; -- SYSDBA 권한을 가진 계정 정보를 볼 수 있습니다 

REVOKE sysdba FROM hr ; -- hr 유저의 sysdba 권한을 해제합니다 






	

	# WITH ADMIN OPTION 사용
		# 만약 sysdba ==> devuser01 에게 with admin option 을 주면
		# devuser01 ==> devuser02 에게도 with admin option 을 줄 수 있습니다
		# 이는 sysdba가 devuser01 의 권한을 박탈해도 devuser02는 계속 유지됩니다

GRANT create table, connect
TO devuser01
WITH ADMIN OPTION ;  -- devuser01에게 시스템 권한을 같이 부여합니다

		








	# 데이터베이스에 미리 정의된 롤 (Predefined ROLE)
		# 다음 2개의 롤은 데이터베이스 서버를 구현하면 자동으로 생성됩니다
			# CONNECT 롤 :
			# RESOURCE 롤 :
		
		# 기타 여러가지 롤들
			# DBA 롤 : DB를 관리하는 202개의 권한을 사용할 수 있습니다
			# SELECT_CATALOG_ROLE 롤 : 일반계정이 DBA만 조회가능한 딕셔너리 뷰를 조회할 수 있습니다
			# SCHEDULER_ADMIN 롤 : {...}


		# 사용자가 직접 롤을 만들 수 있습니다  





CREATE ROLE DEVROLE ;  -- 롤을 생성합니다



GRANT CREATE CLUSTER, CREATE INDEXTYPE,
CREATE OPERATOR, CREATE PROCEDURE,
CREATE SEQUENCE, CREATE TABLE,
CREATE TRIGGER, CREATE TYPE,
CREATE VIEW, CREATE SYNONYM,
ALTER SESSION
TO DEVROLE ;   -- DEVROLE 에 해당 권한을 부여합니다 




GRANT connect, devrole
TO devuser01 ;  -- CONNECT, DEVROLE 롤을 devuser01에게 부여합니다 



GRANT SELECT_CATALOG_ROLE TO devuser01; -- SELECT_CATALOG_ROLE롤을 devuser01 유저에게 부여합니다
										-- DBA만 볼 수 있는 뷰들을 볼 수 있습니다

SELECT name FROM v$datafile;   -- DBA만 볼 수 있는 뷰입니

다


SELECT * FROM session_privs ;  -- 현재 사용자의 권한 정보를 볼 수 있습니다 







		# DEFAULT ROLE (디폴트 롤)을 이용한 권한 제어 
			# 여러가지 부여받은 롤 중에서 로그인 시 사용할 수 있도록 활성화된 롤을 말합니다
			# 암호가 걸린 롤은 자동으로 DEFAULT ROLE에서 제외됩니다 



CREATE USER roleuser
IDENTIFIED BY oracle4U
DEFAULT TABLESPACE users
TEMPORARY TABLESPACE temp
QUOTA unlimited ON users ;  -- roleuser 계정을 만듭니다


GRANT role1, role2, role3
TO roleuser ;  -- role1,2,3를 사용자에게 부여합니다 (role2,3는 비밀번호가 걸려있는 상황)


SELECT granted_role, default_role
FROM user_role_privs ;   -- DEFAULT 롤을 확인합니다


SELECT *
FROM session_roles ;     -- 사용할 수 있는 롤들을 확인합니다
 


	




	# PROFILE (프로파일)을 이용한 계정 제어
		# 사용자별로 리소스 소모량을 제한할 때 주로 사용합니다
		# 패스워드 관리 정책을 설정할 수 있습니다 

			# RESOURCE_LIMIT 파라미터
			# 기본값은 FALSE 이고 TRUE 로 활성화를 시켜주면 제한을 걸 수 있습니다
			
		# 오라클 데이터베이스 서버를 실행하면 DEFAULT, MONITORING_PROFILE 이름의 PROFILE이 생성됩니다 
			
		# DEFAULT PROFILE (디폴트 프로파일)
			# 11g 버전부터는 DEFAULT PROFILE에 PASSWORD 관련 정책이 다음처럼 수정되었습니다
				# PASSWORD_LIFE_TIME 180
				# PASSWORD_GRACE_TIME 7
				# FAILED_LOGIN_ATTEMPTS 10
				# PASSWORD_LOCK_TIME 1
			
			# 이처럼 사용하지 않을거면 반드시 DEFAULT PROFILE을 수정해야합니다
			# sql> ALTER PROFILE DEFAULT LIMIT
				   PASSWORD_GRACE_TIME UNLIMITED
				   PASSWORD_LIFE_TIME UNLIMITED;





-- PROFILE을 생성합니다
CREATE PROFILE myprof1
LIMIT
CPU_PER_SESSION 36000    -- 접속한 세션에서 사용가능한 CPU 사용 시간 (1/100초)
CPU_PER_CALL 1000        -- 하나의 콜당 사용가능한 CPU의 사용시간 (1/100초)
CONNECT_TIME 300         -- 접속이 유지되는 최대시간 (분)
IDLE_TIME 5              -- 접속 후 IDLE 상태가 지속되는 최대시간 (분)
SESSIONS_PER_USER 3      -- 동시에 접속가능한 세션 수를 설정합니다
LOGICAL_READS_PER_SESSION 1000    -- 세션 당 사용가능한 BUFFER CACHE의 최대 버퍼 갯수
LOGICAL_READS_PER_CALL 500        -- 하나의 SQL문을 처리 시  "
PASSWORD_LIFE_TIME 10      -- 패스워드가 유효한 최대기간 (일)      
PASSWORD_GRACE_TIME 2      -- LIFE_TIME이 끝나고 추가적으로 로그인 허용 기간 (경고창 생성) (일)
PASSWORD_REUSE_MAX 3       -- 이전에 사용한 패스워드를 재사용 할 수있게 허용해주는 기간 (일 )
PASSWORD_REUSE_TIME UNLIMITED   
PASSWORD_LOCK_TIME 10      
FAILED_LOGIN_ATTEMPTS 5    -- 허용된 패스워드 오류 횟수 
PASSWORD_VERIFY_FUNCTION null ;  -- 패스워드의 복잡성을 검사하는 함수 이름을 설정합니다

-- PRIVATE_SGA :  접속한 세션에 대한 PGA 서버의 SGA에 캐싱을 시킬 때 SGA 메모리의 양 (잘 안쓰입니다)(사용자가 사용을 안하면서 접속을 계속 유지하면 메모리 낭비가 커지므로)(주로 RMAN으로 관리합니다) 


ALTER USER hr
PROFILE myprof1 ;   -- hr 계정에 myprof1 프로파일을 줍니다






		# 패스워드 복잡도 함수 (PASSWORD_VERIFY_FUNCTION)
			# dbhome_1/RDBMS/ADMIN/utlpwdmg.sql 파일로 패스워드 복잡도를 수정할 수 있습니다 
				
			# 파일을 c:\app\buk213\ 에 놓으시고 몇 문장 수정합니다
				# sql안에서 @c:\app\buk213\utlpwdmg.sql 로 스크립트를 실행합니다
				# verif_function_11G 함수가 추가되었습니다

	




ALTER PROFILE myprof1 LIMIT
PASSWORD_VERIFY_FUNCTION verify_function_11g ;   -- 방금 추가한 함수를 적용합니다

					

SELECT username, profile
FROM dba_users
WHERE username IN ('SYS','SYSMAN','SYSTEM','DBSNMP'
,'HR','SH','OE') ;    -- 각 계정들의 프로파일 정보를 확인합니다



set pagesize 999
col profile format a10
col resource_name format a30
set linesize 200
SELECT *
FROM dba_profiles
WHERE profile = 'MYPROF1'
ORDER BY 3,2 ;   -- MYPROF1 프로파일의 정보를  자세하게 확인합니다




SHOW PARAMETER resource_limit   -- RESOURCE_LIMIT 파라미터를 확인합니다 (TRUE여야 적용됨)

ALTER SYSTEM SET
resource_limit=true SCOPE=both ;  -- 해당 파라미터를 TRUE로 바꿉니다 


col username format a30
col profile format a30
set pagesize 50000
SELECT profile, username
FROM dba_users
WHERE profile LIKE 'MYPROF%'
ORDER BY 1 ,2 ;     -- MYPROF을 사용 중인 사용자 정보를 확인합니다


DROP PROFILE myprof1 CASCADE ;  -- PROFILE을 삭제합니다 (CASCADE를 명시해야합니다)
-- CASCADE를 명시하면 현재 이 프로파일을 사용중인 계정은 자동으로 DEFAULT 프로파일을 사용합니다















--------------------------------------------------------------------------------------------------

<클라이언트 사용자 관리>


## 데이터베이스 사용자 관리 (오라클에서만 사용하는 경우만 설명합니다)
	# 여러가지 로그인 인증 방식들
		# PASSWORD 인증 : DATA DICTIONARY 정보로 패스워드를 저장해놓고 접속시 확인하는 방식입니다
		# EXTERNAL 인증 : OS 인증이고하며 리눅스에서만 가능합니다 (거의 안씁니다)
		# GLOBAL 인증 : 거의 사용하지 않습니다

	# 딕셔너리 뷰
		# DBA_USERS : 데이터베이스 서버의 접속 계정에 대한 정보를 제공합니다



	# 사용자 계정 관리를 위한 실습
		# 임시-테이블스페이스 3개를 만들고 그룹화시킵니다



CREATE TEMPORARY TABLESPACE temp11
TEMPFILE 'C:\app\buk213\oradata\orcl\temp11a.tmp'
SIZE 11256K
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited ;


CREATE TEMPORARY TABLESPACE temp22
TEMPFILE 'C:\app\buk213\oradata\orcl\temp22a.tmp'
SIZE 11256K
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited ;


CREATE TEMPORARY TABLESPACE temp33
TEMPFILE 'C:\app\buk213\oradata\orcl\temp33a.tmp'
SIZE 11256K
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited ;  -- 임시-테이블스페이스 3개를 만듭니다



ALTER TABLESPACE temp11
TABLESPACE GROUP temp_grp1 ;

ALTER TABLESPACE temp22
TABLESPACE GROUP temp_grp1 ;

ALTER TABLESPACE temp33
TABLESPACE GROUP temp_grp1 ;  -- 임시-테이블스페이스를 그룹화합니다



SELECT * FROM dba_tablespace_groups ;  -- 임시-테이블스페이스 정보를 확인합니다

SELECT tablespace_name
FROM dba_tablespaces
WHERE contents = 'TEMPORARY' ;   -- 임시-테이블스페이스 정보를 확인합니다2








		# 영구-테이블스페이스 2개를 만듭니다


CREATE TABLESPACE udata_insa
DATAFILE 'C:\app\buk213\oradata\orcl\udatainsa01.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 20M MAXSIZE unlimited
UNIFORM SIZE 1M ;



CREATE TABLESPACE udata_cust
DATAFILE 'C:\app\buk213\oradata\orcl\udatecust01.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 20M MAXSIZE unlimited ;  -- 영구-테이블스페이스를 2개 만듭니다


SELECT tablespace_name
FROM dba_tablespaces
WHERE contents = 'PERMANENT'
AND tablespace_name not in ('SYSTEM','SYSAUX');  -- 테이블스페이스를 확인합니다













		# 사용자 계정 2개를 생성합니다
			# QUOTA : 해당 테이블스페이스 내에서 공간을 제한하겠다/제한하지 않겠다 명시합니다 
				# 반드시 사용할 테이블스페이스에 모두 명시해야 합니다
				# 언두, 임시-테이블스페이스에는 사용하지 않습니다





CREATE USER devuser01
IDENTIFIED BY oracle4U
TEMPORARY TABLESPACE temp33     -- PGA 메모리가 부족할 때 temp33 임시-테이블스페이스를 사용합니다
ACCOUNT unlock					
PASSWORD EXPIRE					-- 처음 로그인할 때 강제로 암호를 바꾸도록 물어봅니다
DEFAULT TABLESPACE users		
QUOTA unlimited on example		
QUOTA unlimited on users
QUOTA unlimited on udata_insa
QUOTA unlimited on udata_cust ;  



CREATE USER devuser02
IDENTIFIED BY oracle4U
TEMPORARY TABLESPACE temp_grp1   -- PGA 메모리가 부족할 때 temp_grp1 임시 그룹을 사용합니다
ACCOUNT lock					 -- 계정을 잠급니다
DEFAULT TABLESPACE users
QUOTA unlimited on users
QUOTA 10M on example			 -- QUOTA : example 테이블스페이스를 10 Mb만 사용할 수 있게 합니다
QUOTA unlimited on udata_insa
QUOTA unlimited on udata_cust ;



GRANT create session, create table
TO devuser01, devuser02 ;         -- 두 계정에 여러 권한을 줍니다







 -- 생성된 계정의 정보를 확인합니다 



col username format a10
col tablespace_name format a10
set linesize 150
SELECT username, tablespace_name, bytes/1024/1024 used_MB
,max_bytes, dropped
FROM dba_ts_quotas
WHERE username IN ('DEVUSER01','DEVUSER02')
order by 1, 2 ;  -- 계정에 설정된 QUOTA에 관한 정보를 출력합니다



			





			# 생성한 계정의 정보를 변경합니다 (관리자만 가능)


ALTER USER devuser01
TEMPORARY TABLESPACE temp ;   -- 사용자의 임시-테이블스페이스를 변경합니다


ALTER USER devuser01
DEFAULT TABLESPACE example ;  -- 사용자의 기본-테이블스페이스를 변경합니다


ALTER USER devuser01
QUOTA unlimited ON udata_insa
QUOTA 10M ON udata_cust
QUOTA 0 ON example ;    -- 사용자의 QUOTA 정보를 변경합니다


ALTER USER devuser01
ACCOUNT lock
PASSWORD EXPIRE ;    -- 계정을 잠그고 패스워드를 파기합니다


GRANT unlimited tablespace
TO devuser01 ;     -- 사용자에게 모든 테이블스페이스를 편집할 수 있는 권한을 줍니다















---------------------------------------------------------------------------------------------------

<Flash Recovery Area와 아카이브 로그 모드>


## Flash Recovery Area
	# Storage 장비에 일정크기 공간의 복구 파일을 저장해 놓는 방식입니다
		# 기존 백업저장장치인 TAPE 저장장치는 복원시 속도가 매우 느립니다

	# 장애복구 시 파일복원을 빠르게 수행할 수 있습니다

	# 복구 관련 파라미터들 (Parameters)
		# DB_RECOVERY_FILE_DEST_SIZE
			# 복구파일의 크기를 설정합니다.

		# DB_RECOVERY_FILE_DEST
			# 복구파일이 생성될 경로를 설정합니다 	


ALTER SYSTEM SET
db_recovery_file_dest_size=50G SCOPE=BOTH ; -- 복구파일의 크기를 설정합니다

ALTER SYSTEM SET
db_recovery_file_dest='c:\users\buk213\fra' SCOPE=BOTH ;  -- 복구파일의 경로를 설정합니다 


	




## 아카이브 로그 모드 구성 (Archive Log Mode)
	# 온라인 리두로그 그룹은 순환적으로 사용되면서 정보가 사용되므로 그 백업파일인 아카이브 로그 파일을 따로 생성해야 합니다
	
	# 오라클 서버를 중지할 수 없는 환경이라면 ACHIVE LOG MODE를 반드시 설정해야 합니다

	# 일반 사용자로부터 데이터 변경이 수행되는 환경도 반드시 ARCHIVE LOG MODE를 구성해야합니다

	# 아카이브 관련 파라미터들
		# LOG_ARCHIVE_FORMAT
			# 생성되는 아카이브파일의 이름 형식을 지정합니다
			# %d : 데이터베이스 이름
			# %t : 인스턴스 번호
			# %s : LOG-SEQUENCE 번호
			# %r : RESETLOGS-ID로 리두로그가 초기화될 때 지정되는 ID 값


		# LOG_ARCHIVE_DEST_n
			# 아카이브 파일이 생성되는 위치를 설정합니다
			# 동시에 여러 파일에 같은 내용을 기록할 수 있습니다	
			# 네트워크 접속식별자를 경로로 설정하면 데이터가드를 사용할 수 있습니다 (엔터프라이즈 버전만 가능)


	# 아카이브 로그 구성 순서
		1. SHUTDOWN IMMEDIATE
		2. STARTUP MOUNT             	-- 마운트 상태로  
		3. ALTER DATABASE ARCHIVELOG;   -- 아카이브로그 모드를 ON 한다
		4. ARCHIVE LOG LIST;			-- 아카이브로그 상태 확인
		5. ALTER DATABASE OPEN;			-- 데이터베이스를 OPEN한다
		6. ALTER SYSTEM ARCHIVE LOG CURRENT -- 현재 CURRENT 상태인 리두로그파일을 아카이브에 기록합니다 (실습이므로 강제로 아카이브파일을 만드는 과정입니다)
		7. ALTER SYSTEM CHECKPOINT -- ACTIVE ==> VALID 상태로 만들어줍니다
		8. c:\users\buk213\arch\orcl\ 파일에 제대로 아카이브 로그파일이 저장됐는지 확인합니다 




SELECT THREAD#, SEQUENCE#, FIRST_CHANGE#, RESETLOGS_ID
,ARCHIVED, STATUS, NAME
FROM v$archived_log
ORDER BY 1,2 ;  -- 아카이브로그 파일을 조회합니다



		

	# 전체 데이터베이스 백업
		# 아카이브 로그 모드를 변경하면 이전 모드의 백업파일은 사용할 수 없습니다
		# 따라서 변경전에는 반드시 전체 데이터베이스를 백업해야 합니다















--------------------------------------------------------------------------------------------------

<데이터베이스 링크>

## 데이터베이스 링크
	# 자신의 데이터베이스 서버에서 다른 데이터베이스 서버의 정보를 참조하고 싶을 때 사용합니다

	# sqlplus hr/oracle4U@orcl  : 자신의 데이터베이스로 접속합니다

	# 상대방 데이터베이스는 접속식별자로 TEAC라고 설정해놨습니다



CREATE database LINK mylink1
CONNECT TO hr IDENTIFIED BY oracle4U
USING 'TEAC' ;  -- 다른 데이터베이스 서버와 연결할 수 있는 링크를 만듭니다


SELECT * FROM hr.avgsalperdept@mylink1  -- 링크 mylink1을 사용해서 다른 데이터베이스 자료를 얻을 수 있습니다


CREATE SYNONYM myavgsal FOR hr.avgsalperdept@mylink1;   -- 동의어를 만들어 간단하게 접근할 수 있습니다 


SELECT * FROM user_synonyms ;  -- 동의어 목록을 볼 수 있습니다 (동의어는 거의 100% 데이터베이스 링크를 사용할 때 같이 사용한다고 합니다)


















-------------------------------------------------------------------------------------------------

<오라클 네트워크 구성>

## 오라클 네트워크
	# 서버, 클라이언트, 그리드 프로그램으로 구성되어 있습니다

	# 리스너 (LISTENER program)
		# 다른 벤더와 다르게 오라클 리스너는 별도의 프로그램으로 구성되어 있습니다
		
		# 네트워크파일 기본 경로 : c:\app\buk213\product\11.2.0\db_home_1\NETWORK\ADMIN\
		
		# listener.ora (리스너 설정파일)
		
		# 리스너를 통한 원격접속
			# sqlplus system/oracle4U@210.123.41.178:1521/orcl.example11.com 
				# ezconnect 방식이라고 합니다  
				# 계정/비번@아이피:포트/데이터베이스명.도메인명
			
				
			# sqlnet.ora (Naming Method 설정 파일)
				#
			

			# tnsnames.ora (접속 식별자 파일)
				# 이 파일을 통해 위의 긴 정보를 저장해놓으면 편하게 로그인할 수 있습니다
					# 이를 tnsnames 방식이라고 합니다
				# sqlplus system/oracle4U@orcl 만 입력해주면 됩니다







	# WINDOWS 환경에선 TNS_ADMIN 키를 생성해서 설정파일의 기본위치를 변경할 수 있습니다 
		ex) TNS_ADMIN : c:\app\buk213\product\11.2.0\db_home_1\NETWORK\ADMIN\



	# netca 와 netmgr
		# 'netca' : Network Configuration Assistant 툴
			# 리스너 생성 : listener.ora
			# 이름 지정 방법 구성 : tnsname.ora
			# 로컬 네트 서비스 이름 구성 : sqlnet.ora
			# 디렉토리 사용 구성 : x (배우는 범위 아님)	




		# 'netmgr' : Network Manager 툴
			# 프로파일 : sqlnet.ora
			# 서비스 이름 지정 : tnsname.ora
			# 리스너 : listner.ora
				# 수신위치와 데이터베이스 서비스 모두 설정해줍니다
		







	# 서버 네트워크를 구성하는 방법 (실습)
		
		1. 리스너 생성합니다
			# netca를 사용해 리스너를 생성합니다(EDWARD)
			# netmgr을 사용해 리스너를 또 생성합니다(EDWARD2)
				# netmgr을 사용해 2개의 포트를 구성하고 데이터베이스 서비스를 설정해줍니다


			# cmd ==> lsnrctl status LISTENER, EDWARD, EDWARD2 로 리스너상태를 확인합니다
				# lsnrctl start EDWARD2로 리스너를 시작합니다





		2. 리스너에 데이터베이스 서비스 이름을 등록시킵니다
		
			# 동적 서비스 등록 (DYNAMIC SERVICE REGISTRATION)
				# PMON 프로세스가 데이터베이스 운영 중 계속 INSTANCE_NAME, SERVICE_NAME 초기화 파라미터 정보를 리스너에게 자동으로 등록시킵니다		
					
					# PMON 프로세스는 디폴트로 1521포트의 리스너에게만 DB 서비스명을 등록합니다	
						# 이렇게 PMON이 못읽으면 고정 서비스상태('UNKNOWN' 상태) 가 되고
						# 읽으면 동적 서비스상태('READY' 상태)가 됩니다
						# cmd ==> lsnrctl status EDWARD2 
				
				# tnsname.ora 파일을 다음과 같이 수정합니다
				
PMON_REG =
(ADDRESS_LIST =
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 2000))
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 1521))
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 3000))
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 4000))
)  -- 이 내용을 추가해서 PMON이 2000,3000,4000번 포트도 읽을 수 있게 해줍니다

	

				# DB에 접속 후 LOCAL_LISTENER 파라미터에 등록시킵니다


-- DB에 접속 후
SHOW PARAMETER LOCAL_LISTENER ;

ALTER SYSTEM SET
LOCAL_LISTENER=PMON_REG;   -- 해당 파라미터의 PMON_REG 키워드를 등록시킵니다

ALTER SYSTEM REGISTER; -- PMON 프로세스에게 서비스 이름, 인스턴스 이름을 강제로 등록시킵니다





			# 고정 서비스 등록 (STATIC SERVICE REGISTRATION)
				# netmgr로만 설정할 수 있습니다 
				# listener.ora 파일에 다음과 같은 내용이 추가됩니다

SID_LIST_EDWARD =
  (SID_LIST =
    (SID_DESC =
      (GLOBAL_DBNAME = orcl.example11.com)
      (ORACLE_HOME = C:\app\buk213\product\11.2.0\dbhome_1)
      (SID_NAME = orcl)
    )
  ) -- 위와 같은 내용이 있으면 EDWARD 리스너는 고정 서비스입니다




			# 리스너 로그 (Listener Log)
				# c:\app\buk213\diag\tnslsnr\(hostname)\listner\trace\(로그파일).log
				# 해당 리스너에 접속한 세션의 로그정보를 볼 수 있습니다 







		3. LOCAL NAMING(TNSNAMES) Method로 접속하는 방법 (netca 사용)
			# netca ==> 이름 지정 방법 구성
				# 쉬운 접속 이름 지정, 로컬 이름 지정을 클릭합니다 
				# sqlnet.ora 파일에 새로운 구문이 추가됩니다
					# NAMES.DICTONARY_PATH=(EZCONNECT, TNSNAMES)
			
			# netca ==> 로컬 네트서비스 이름 구성
				# 서비스명으로 편하게 접속할 수 있습니다 
					# sqlplus system/oracle4U@orcl
					# tnsnames.ora 파일을 수정합니다

			# netmgr ==> 서비스 이름 지정
				# 이를 통해 tnsnames.ora 파일을 수정할 수 있습니다
				# 다음 접속부턴 편하게 sqlplus system/oracle4U@apple01 같이 접속할 수 있습니다


		4. Dedicated Server (전용 서버) vs Shared Server (공유 서버)
			# Dedicated Server는 한 사용자 당 하나의 서버프로세스를 제공하는 방식입니다
				# Connection Pool로 여러 사용자 묶음을 한 연결로 처리할 수 있습니다

			# Shared Server는 디스패처가 여러 사용자 쿼리를 받아서 처리하므로 부하가 많아지면 디스패처가 죽는 현상이 발생합니다 (잘 사용하지 않습니다)












