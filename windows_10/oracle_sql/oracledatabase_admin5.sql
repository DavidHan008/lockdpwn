<NOARCHAIVELOG 모드에서 일부 데이터파일 손실 복구>


## NOARCHAIVELOG 모드
	# 일부 데이터만 유실해도 모든 데이터파일 + 컨트롤파일을 복원해야합니다

	# ARCHIVE 모드를 안하면 단점이 너무 많아서 요즘은 거의 전부 ARCHIVE 모드를 구성합니다
	
	# 따라서 아래 실습은 실전에서는 많이 쓰이진 않습니다



ARCHIVE LOG LIST -- 아카이브 모드 구성을 확인합니다


SHUTDOWN IMMEDIATE

STARTUP MOUNT


ALTER DATABASE NOARCHIVELOG ; -- NOARCHAIVELOG 모드로 변경합니다


ALTER DATABASE OPEN ; -- DB를 OPEN 합니다



RMAN> BACKUP AS BACKUPSET DATABASE ; -- 에러납니다 NOARCHAIVELOG 모드에서는 ONLINE 백업을 수행할 수 없습니다


SHUTDOWN IMMEDIATE

STARTUP MOUNT



RMAN> ALTER DATABASE OPEN ;



RMAN> RUN {
SHUTDOWN IMMEDIATE ;
STARTUP MOUNT ;
BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
DATABASE
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
TAG 'ORCL_BS_NOARC_WHOLE_DB_20140114' ;
ALTER DATABASE OPEN ;
}



RMAN> SQL 'ALTER SYSTEM SWITCH LOGFILE' ;
RMAN> SQL 'ALTER SYSTEM CHECKPOINT' ;   -- 로그스위치, 체크포인트를 4번 수행합니다




SHUTDOWN IMMEDIATE

STARTUP MOUNT





RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 1
DATABASE
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
TAG 'ORCL_BS_NOARC_WHOLE_DB_20140114' ;  -- LEVEL 1 백업을 받습니다




RMAN> ALTER DATABASE OPEN ;


RMAN> LIST BACKUP TAG ORCL_BS_NOARC_WHOLE_DB_20140114 ;



RMAN> SQL 'ALTER SYSTEM SWITCH LOGFILE' ;
RMAN> SQL 'ALTER SYSTEM CHECKPOINT' ;   -- 로그스위치, 체크포인트를 4번 수행합니다


RMAN> REPORT SCHEMA ;








RMAN> SHUTDOWN ABORT

RMAN> STARTUP NOMOUNT


RMAN> RESTORE CONTROLFILE
FROM '/u02/app/BACKUP/rmanbkg/0iq8846n_1_1' ;  -- NOMOUNT 상태에서 컨트롤파일을 복구합니다


RMAN> ALTER DATABASE MOUNT;


RMAN> RESTORE DATABASE
FROM TAG ORCL_BS_NOARC_WHOLE_DB_20140114 ;  -- MOUNT 상태에서 모든 데이터파일들을 복구합니다


RMAN> RECOVER DATABASE NOREDO ; -- (11g) NOREDO 옵션을 명시해서 LEVEL 1 까지만 진행하고 리두로그 적용을 하지 않습니다



RMAN> ALTER DATABASE OPEN RESETLOGS;













---------------------------------------------------------------------------------------------------

<불완전 복구를 이용한 삭제된 Schema 복구>

## 불완전 복구
	# 특정 시점으로부터 부분만 복구하는 방법으로 특정 시점 이전의 
	- 모든 정보를 백업해야하므로 시간이 매우 오래걸리는 단점이 있습니다

	# 잘못 삭제된 SCHEMA에 추가적인 변경작업이 없는 경우에만 사용할 수 있습니다
		
		# 이 보다 더 좋은 방법은 'expdp' 명령어를 이용해 삭제되는 SCHEMA 객체를 백업받아 
		- 나중에 수월하게 장애조치를 하는 방법입니다
		
			# 'expdp' 명령어는 아직 안배웠습니다


	# 퇴사한 직원의 데이터가 필요없다고 생각되어 'expdp' 명령어로 백업안받고 지운 경우




RMAN> REPORT UNRECOVERABLE ; -- 리두로그가 없어서 복구가 안되는 데이터파일 정보를 확인합니다



CREATE USER hruser
IDENTIFIED BY oracle4U
DEFAULT TABLESPACE users
QUOTA unlimited ON users ;  -- hruser 계정을 만듭니다


GRANT connect, resource
TO hruser ;  -- hruser에게 권한을 줍니다





CREATE TABLE hruser.emps07_01
(empno NUMBER(6)
,ename VARCHAR2(30)
,sal NUMBER(8,2)
)TABLESPACE users ;


INSERT INTO hruser.emps07_01
VALUES (100, 'ORACLE', 13000) ;


INSERT INTO hruser.emps07_01
VALUES (101, 'ORADEV',6000) ;  

COMMIT ; -- 테이블을 만들고 값을 입력합니다







col ename format a15
SELECT *
FROM hruser.emps07_01 ;  -- 테이블을 조회합니다


CREATE RESTORE POINT drop_hruser ; -- SCN 값과 TIMESTAMP 값을 drop_hruser 값으로 컨트롤파일에 저장합니다


ALTER SESSION SET
nls_timestamp_format='YYYY/MM/DD:HH24:MI:SS'; -- 시간표시형식을 바꿉니다



col time format a20
col name format a12
col DDB_INC# format 999999
set pagesize 999
set linesize 200
SELECT name, scn, time, storage_size,
guarantee_flashback_database,
database_incarnation# AS DB_INC#
FROM v$restore_point ;  -- RESTORE_POINT 정보를 확인합니다



DROP USER hruser CASCADE ; -- user + SCHEMA 를 전부 삭제합니다


SELECT *
FROM dba_users
WHERE username='HRUSER' ; -- 더이상 계정정보가 없습니다





RMAN> shutdown immediate ; -- 서버를 정상적으로 종료합니다

RMAN> startup mount

RMAN> REPORT SCHEMA ;






cmd ==> mkdir C:\app\oracle\oradata\TEMP_orcl

cmd ==> move C:\app\buk213\oradata\orcl\*.dbf C:\app\oracle\oradata\TEMP_orcl   -- 모든 데이터파일을 이동시킵니다


cmd ==> copy C:\app\buk213\oradata\orcl\* C:\app\oracle\oradata\TEMP_orcl   -- 모든 데이터파일 + 다른 파일들을 복사합니다





RMAN> LIST RESTORE POINT all ; -- SCN 값을 확인해서 이 SCN 값보다 작은 모든 파일을 찾아야합니다





RMAN> LIST BACKUP OF DATAFILE 1 BY FILE ;

RMAN> LIST BACKUP OF DATABASE TAG ORCL_BS_WHOLE_20150105_R1 ; -- BACKUPSET 백업 정보를 확인합니다 






RMAN> LIST COPY OF DATAFILE 1 ;

RMAN> LIST COPY OF DATABASE TAG ORCL_CP_WHOLE_20150105_R2 ; -- IMAGECOPY 백업 정보를 확인합니다
-- 다행히 모든 SCN 값이 RESTORE POINT SCN 값보다 작습니다









RMAN> RESTORE DATABASE
FROM TAG ORCL_CP_WHOLE_20150105_R2 ; -- 해당 태그의 데이터파일로부터 데이터베이스를 복구합니다



RMAN> RECOVER DATABASE UNTIL RESTORE POINT drop_hruser ; -- RESTORE_POINT 지점까지만 복구 (REDO LOG를 적용)를 수행합니다



RMAN> ALTER DATABASE OPEN RESETLOGS ; -- 데이터베이스를  RESETLOGS 모드로 엽니다(모든 온라인 리두로그를 초기화시키고 유실된 멤버파일을 생성합니다)














--------------------------------------------------------------------------------------------------

<완전 복구, 서버관리 백업 복구>

## 완전 복구
	# 서버관리 백업 복구 실습 
		1. 데이터베이스가 OPEN 상태에서 NON-CRITICAL 데이터파일 손실된 경우
			
			# SYSTEM-테이블스페이스, ACTIVE 언두-테이블스페이스는 제외입니다
			
			# USERS-테이블스페이스에 장애를 일으켜 복원 - 복구 작업을 수행합니다




RMAN> REPORT SCHEMA ;  -- USERS-테이블스페이스가 0으로 표시됩니다 (OFFLINE인 경우, 파일이 없는경우)

RMAN> LIST BACKUP OF DATAFILE 4 by file ; -- 백업본 정보를 확인합니다

RMAN> ALTER TABLESPACE USERS OFFLINE IMMEDIATE ; -- 0으로 표시된 테이블스페이를 OFFLINE으로 합니다






RMAN> RESTORE DATAFILE 4 ; -- 데이터베이스가 OPEN 상태일 경우 users-테이블스페이스  복원 명령어


RMAN> RECOVER TABLESPACE 4 ; -- users-테이블스페이스 복구 명령어



RMAN> SQL 'ALTER TABLESPACE USERS ONLINE' ; -- users-테이블스페이스를 ONLINE 상태로 변경합니다


RMAN> SQL 'ALTER SYSTEM CHECKPOINT' ; -- 체크포인트를 한번 해줍니다 


SELECT file#, checkpoint_change#
FROM v$datafile_header ; -- 복구 후 SCN 값을 확인합니다 (복원한 값이 다른 SCN 값보다 높아야합니다)









		2. 데이터베이스 OPEN 상태에서 CRITICAL + NON-CRITICAL 데이터파일이 손실된 경우  
		
			# SYSTEM-테이블스페이스, ACTIVE 언두-테이블스페이스, 사용자-테이블스페이스 모두 손상되었을 경우입니다

			# Windows는 데이터베이스가 OPEN 상태에서 중요 테이블스페이스가 OFFLINE이 안되므로 SHUTDOWN 상태로 변경해서 실습합니다
				# SYSTEM(1), USERS(4), EXAMPLE(5)-테이블스페이스를 삭제 후 복원 및 복구합니다
					# EXAMPLE-테이블스페이스 파일은 너무 큰 관계로 나중에 복원합니다







col tablespace_name format a10
col file_name format a50
SELECT tablespace_name, file_name
FROM dba_data_files ;   -- 현재 구성된 데이터파일 정보를 확인합니다



SHUTDOWN IMMEDIATE -- 정상적으로 데이터베이스를 종료합니다 (SYSTEM,USERS,EXAMPLE 데이터파일을 지웁니다)


STARTUP MOUNT -- MOUNT 상태로 OPEN합니다


SELECT * FROM v$recover_file; -- 기동 중에 손상된 데이터파일 정보를 확인합니다 (FILE NOT FOUND 라고 나옵니다)(ALERT_LOG 파일에 에러내용이 기록됩니다)


SHUTDOWN ABORT -- RMAN으로 복구하기 위해 ABORT로 서버를 중지합니다




RMAN> STARTUP  -- 알아서 MOUNT 상태로 기동합니다 

RMAN> REPORT SCHEMA ;



RMAN> RESTORE DATAFILE 1,4 ; -- 1,4번 데이터파일을 복원합니다

RMAN> RECOVER DATAFILE 1,4 ; -- 1,4번 데이터파일을 복구합니다



RMAN> SQL 'ALTER DATABASE DATAFILE 5 OFFLINE' ; -- 5번 데이터파일을 OFFLINE 시킵니다

RMAN> ALTER DATABASE OPEN ; -- 데이터베이스를 OPEN합니다



RMAN> RESTORE DATAFILE 5 ; -- 5번 데이터파일을 복원합니다

RMAN> RECOVER DATAFILE 5 ; -- 5번 데이터파일을 복구합니다

RMAN> SQL 'ALTER TABLESPACE example ONLINE' ; -- 5번 테이블스페이스를 ONLINE합니다

RMAN> SQL 'ALTER SYSTEM CHECKPOINT' ; -- 강제 체크포인트를 수행해 다른 데이터파일과 동기화합니다








		3. 데이터베이스가 OPEN 상태에서 모든 데이터파일들이 손실되고 다른경로에 복구해야하는 경우
			# SYSTEM/ACTIVE 언두-테이블스페이스와 사용자-테이블스페이스의 모든 자료가 유실되었습니다
			
			# RMAN을 사용하지 않는 경우 copy 명령어로 일일히 복사해줘야하는 불편함이 있습니다
				
				# ALTER DATABASE RENAME FILE 'old_name' TO 'new_name'; 으로 설정해줍니다
				
				# RMAN은 스크립트 한번으로 복구할 수 있습니다



			# SWITCH 명령어 : 컨트롤파일을 업데이트합니다 (RUN {...} 으로만 실행가능합니다})
			



 

SELECT file_name FROM dba_data_files ; 
SELECT file_name FROM dba_temp_file ;  -- 사용 중인 데이터파일들을 모두 확인합니다



SHUTDOWN IMMEDIATE  -- 이후에 모든 데이터파일(.DBF)을 삭제합니다

RMAN> REPORT SCHEMA ; -- 전부다 0으로 출력됩니다




RMAN> RUN {
STARTUP FORCE MOUNT ;
SET NEWNAME FOR DATAFILE 1 TO  -- SET NEWNAME으로 해당 데이터파일 복원경로를 설정합니다
'C:\app\oracle\oradata\orcl\system01.dbf';  -- 새로운 경로 c:\app\oracle\orcl\
SET NEWNAME FOR DATAFILE 2 TO
'C:\app\oracle\oradata\orcl\sysaux01.dbf';
SET NEWNAME FOR DATAFILE 3 TO
'C:\app\oracle\oradata\orcl\undotbs01.dbf';
SET NEWNAME FOR DATAFILE 4 TO 
'C:\app\oracle\oradata\orcl\users01.dbf';
SET NEWNAME FOR DATAFILE 5 TO
'C:\app\oracle\oradata\orcl\example01.dbf';  -- REPORT SCHEMA 결과에서 TEMPFILE 번호를 확인후 그 번호를 적습니다
SET NEWNAME FOR TEMPFILE 1 TO 
'C:\app\oracle\oradata\orcl\temp01.dbf';
RESTORE DATABASE ;	--데이터파일을 백업으로부터 복원합니다
SWITCH DATAFILE ALL ;   -- 컨트롤파일에 새로운 파일들의 경로를 업데이트합니다
SWITCH TEMPFILE ALL ;
SQL 'ALTER DATABASE DATAFILE 3 ONLINE' ;
RECOVER DATABASE ;  -- 리두 로그를 적용해서 복구합니다
ALTER DATABASE OPEN ;
}   -- 다음 스크립트를 rman_recover_01.sql 파일로 저장해놓습니다 





RMAN> RUN {
STARTUP FORCE MOUNT ;
SET NEWNAME FOR DATABASE TO 'C:\app\oracle\oradata\orcl\%U.dbf';
SET NEWNAME FOR TEMPFILE 1 TO 'C:\app\oracle\oradata\orcl\%U.dbf';
RESTORE DATABASE ;
SWITCH DATAFILE ALL ;
SWITCH TEMPFILE ALL ;
SQL 'ALTER DATABASE DATAFILE 3 ONLINE' ;
RECOVER DATABASE ;
ALTER DATABASE OPEN ;
}   -- 11g 에서만 실행 가능한 방법입니다 rman_recover_02.sql로 저장합니다
	-- 구문이 단순해졌습니다







cmd ==> rman target / cmdfile='rman_recover_01.sql' -- 위 스크립트를 실행합니다



RMAN> REPORT SCHEMA ; -- 복원이 됐는지 확인합니다


RMAN> VALIDATE CHECK LOGICAL DATABASE ; -- 제대로 복구됐는지 검증해봅니다








			4. 데이터베이스가 OPEN 상태에서 크기가 큰 NON-CRITICAL 데이터파일이 손실되었고 이를 신속히 복구해야 하는 경우 
				
				# 서버관리 백업파일을 사용해 다른 경로에 완전복구해야합니다
				# IMAGECOPY 백업형식에 대해서만 사용가능합니다

				# 사용자-테이블스페이스 파일이 유실됐습니다
				# 해당 파일이 대용량이라 RESTORE 시간이 오래걸립니다
				# 신속히 복구해야합니다
				

				# 백업파일 자체를 컨트롤파일에 등록시켜셔 RESTORE 하는 시간을 줄일 수 있습니다
				# 해당 백업파일은 더 이상 백업파일로 간주되지 않습니다


SELECT file_name
FROM dba_data_files
WHERE tablespace_name='USERS' ; -- USERS-테이블스페이스의 데이터파일 위치를 확인합니다


ALTER TABLESPACE users OFFLINE IMMEDIATE ; -- USERS-테이블스페이스를 OFFLINE시킵니다 (해당 USERS01.DBF 파일을 삭제합니다)(Windows는 ONLINE 상태에서 삭제가 안됩니다)





RMAN> REPORT SCHEMA ;  


RMAN> LIST COPY OF DATAFILE 4 ;  -- 4번 데이터파일의 IMAGECOPY 백업정보를 확인합니다





RMAN> RUN {
SQL 'ALTER TABLESPACE users OFFLINE IMMEDIATE' ;
SET NEWNAME FOR DATAFILE 4
TO
'C:\USERS\BUK213\RMANBKG\DATA_D-ORCL_I-1445317443_TS-USERS_FNO-4_3SRCDV6I
' ;
SWITCH DATAFILE 4 ;
RECOVER DATAFILE 4 ;
SQL 'ALTER TABLESPACE users ONLINE' ;
SQL 'ALTER SYSTEM CHECKPOINT' ;
}    -- RESTORE 복원이 시간이 오래걸리므로 백업파일로 이름 변경을 통해 RESTORE를 대체합니다







ALTER TABLESPACE EXAMPLE OFFLINE IMMEDIATE ; -- EXAMPLE(5)-테이블스페이스를 OFFLINE 시킨 후 실제 파일을 삭제합니다 (EXAMPLE.DBF)


RMAN> SWITCH DATAFILE 5 TO COPY ; -- (11g에서만 사용가능) 5번 백업 데이터파일을 컨트롤파일에 적용합니다


RMAN> RECOVER DATAFILE 5 ; -- 5번 데이터파일을 복구합니다


RMAN> SQL 'ALTER TABLESPACE example ONLINE' ; -- EXAMPLE-테이블스페이스를 ONLINE으로 변경합니다







RMAN> VALIDATE CHECK LOGICAL DATAFILE 4,5 ; -- USERS,EXAMPLE-테이블스페이스가 제대로 복구됐는지 검증합니다


RMAN> LIST COPY TAG 'ORCL_CP_WHOLE_20150105_R2' ; -- 이렇게 변경된 두 테이블스페이스는 더 이상 백업파일로 간주되지 않습니다






RMAN> BACKUP AS COPY
DURATION 00:01
MINIMIZE LOAD
INCREMENTAL LEVEL 0
DATAFILE 4 TAG=DBF4
FORMAT
'C:\app\buk213\oradata\orcl\data_D-orcl_TS-USERS_FNO-4.dbf'
DATAFILE 5 TAG=DBF5
FORMAT
'C:\app\buk213\oradata\orcl\data_D-orcl_TS-EXAMPLE_FNO-5.dbf'; -- 백업파일을 원래의 운영경로에 다시 복사해서 컨트롤파일에 재등록시켜줘야 합니다 (DURATION 카피로 진행합니다)



RMAN> LIST COPY OF DATAFILE 4,5 ; -- 생성된 백업파일 정보를 확인합니다







RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 1
DATAFILE 4 , 5
TAG DBF4DBF5
FORMAT 'C:\Users\buk213\rmanbkg\%U' ;  -- IMAGECOPY 백업 후 변경된 부분만 백업받는 LEVEL 1 백업을 수행합니다




RMAN> RECOVER COPY OF DATAFILE 4 WITH TAG DBF4 ;
RMAN> RECOVER COPY OF DATAFILE 5 WITH TAG DBF5 ; -- 사용하려는 IMAGECOPY 백업을 LEVEL 1 백업으로 UPDATE 시킵니다



RMAN> RUN {
SQL 'ALTER TABLESPACE USERS OFFLINE' ;
SQL 'ALTER TABLESPACE EXAMPLE OFFLINE' ;
SWITCH DATAFILE 4 TO DATAFILECOPY TAG DBF4 ;
SWITCH DATAFILE 5 TO DATAFILECOPY TAG DBF5 ;  -- DATAFILECOPY를 쓰면 TAG를 쓸 수 있습니다
RECOVER DATAFILE 4,5 ;
SQL 'ALTER TABLESPACE USERS ONLINE' ;
SQL 'ALTER TABLESPACE EXAMPLE ONLINE' ;
SQL 'ALTER SYSTEM CHECKPOINT' ;
}  -- USERS, EXAMPLE-테이블스페이스를 이름재지정을 통해 원래 경로로 복구를 수행합니다



RMAN> REPORT SCHEMA ; -- 경로가 제대로 변경됐는지 확인해봅니다














---------------------------------------------------------------------------------------------------

<서버관리백업을 이용한 데이터파일 복구>

## NON CRITICAL, CRITICAL, 완전복구, 불안전복구 

	# 'NON CRITICAL'
		# SYSTEM-테이블스페이스, ACTIVE 언두-테이블스페이스가 아닌 사용자 데이터만 복구할 때 서버를 구동 중인 상태에서 백업할 수 있습니다.
	
	# 'CRITICAL' 
		# DB를 SHUTDOWN 하고 복구를 수행해야 합니다


	
	# '완전복구' : 장애가 발생한 시점까지 커밋된 모든 데이터의 변경사항을 복구합니다
	
	# '불완전복구(PITR)' : 복구작업을 과거의 특정시점까지만 합니다


	# 'RECOVER' 와 'RESTORE'
		# 'RECOVER' : 리두로그(REDO LOG), 아카이브로그(ARCHIVE LOG)를 적용시켜 복구하는 걸 말합니다

		# 'RESTORE' : 백업파일로부터의 복원을 말합니다




	# 복구실습을 하기 위한 준비 
		# SQL에서 테이블스페이스도 정리하고 
		# RMAN에서 BACKUPSET, IMAGECOPY 백업을 받아놓습니다
		# make_data_to_recover.sql 을 이용해 복구에 필요한 스크립트를 실행합니다 
			# 아카이브로그 8개 생성합니다



