<인스턴스 복구>

## CRASH(INSTANCE) FAILURE
	# 데이터베이스 서버가 비정상적으로 종료되었을 때를 말합니다
		# 단순히 DB를 STARTUP 하면 알아서 인스턴스 복구를 합니다 (SMON 프로세스에 의해)

		# MOUNT ==> ROLLFORWARD ==> OPEN ==> ROLLBACK 
			# ROLLFORWARD	
				# SMON 프로세스가 실행되어 모든 버퍼캐시 데이터를 데이터파일에 저장합니다 
				# REDO LOG ENTRY의 위치부터 모든 리두로그를 재실행합니다 
					# COMMIT 여부 없이 모든 데이터를 전부 버퍼가 기록합니다	

				# 리두로그를 재실행해서 버퍼가 모두 복원되면 데이터파일에 저장합니다
					# 데이터파일과 리두로그파일의 CHECKPOINT 정보가 일치해야 합니다	


		# ROLLBACK
			# SMON 프로세스가 COMMIT 되지 않은 데이터를 읽어서 ROLLBACK 시킵니다
			# ROLLFORWARD된 내용 중 COMMIT 되지 않은 데이터는 전부 ROLLBACK 시킵니다
			# 언두데이터를 이용해서 수행됩니다





	# CRASH(INSTANCE) 복구 튜닝
		# 인스턴스 복구 단계 중 ROLLFORWARD 단계에서 소요되는 시간을 파악하는 것이 목적입니다

		# 복구하는데 시간이 얼마나 걸리는지 개발자들에게 알려주기 위해 사용합니다 (보통 5~10분)

		# 'FAST_START_MTTR_TARGET' 초기화 파라미터
			# 인스턴스 복구가 완료되서 OPEN되기까지의 시간을 설정합니다
			# 8i 버전까지 있던 3가지 초기화 파라미터를 9i 버전부터 하나로 묶었습니다
			# 쉽게 CRASH(INSTANCE) 복구 튜닝을 할 수 있습니다




SHOW PARAMETER fast_start_mttr_target -- 파라미터 정보를 확인합니다


SELECT TARGET_MTTR, ESTIMATED_MTTR
FROM v$instance_recovery ;  
-- TARGET_MTTR : (10G부터) 자동으로 관리가 됩니다 (0이 아닌 값으로 우선 설정해야합니다)(ESTIMATED_MTTR보다 항상 커야합니다) 
-- ESTIMATED_MTTR : 현재 리루 로그 크기를 보고 만약 CRASH-복구를 해야할 때 복구 예상 시간



ALTER SYSTEM SET
fast_start_mttr_target=19 SCOPE=both ;  
-- FAST... 파라미터에 ESTIMATED_MTTR 에 표시된 값을 그대로 설정합니다 (서버가 자동으로 설정해므로 일부러 이렇게 설정해봅니다)






		# 위 명령을 실행하면 ALERT_LOG 파일에 오라클 서버가 설정한 권장값을 볼 수 있습니다
			# 하지만 관리자가 설정된 값이 바뀌지는 않습니다
			# 따라서 FAST_START_MTTR_TARGET 설정값을 튜닝된 값으로 다시 설정해야 합니다



FAST_START_MTTR_TARGET 19 is set too low, using minimum achievable MTTR 22 instead.

ALTER SYSTEM SET
fast_start_mttr_target=22 scope=both ; -- 튜닝된 값으로 바꿔줍니다 






SELECT optimal_logfile_size AS "OPTIMAL_LOGFILE_SIZE_MB"
FROM v$instance_recovery ; -- 현재 데이터베이스 로그파일의 최소 크기를 확인할 수 있습니다 
-- MB 크기가 사용 중인 리두로그파일보다 많은 차이가 나면 위의 크기를 갖는 리두 로그 파일로 구성된 로그그룹을 추가하고 기존 로그 그룹을 삭제합니다

























-------------------------------------------------------------------------------------------------

<아카이브 로그 모드에서 사용자 관리 백업>

## 데이터파일 백업 수행
	# 사용자 관리 백업 (OS-백업)
		# 운영체제의 cp 또는 copy 명령어를 이용해 백업합니다
		# DBA가 직접 백업파일을 관리합니다
		
		# CLOSED WHOLE DATABASE BACKUP (OFFLINE 백업)(CONSISTENT 백업)
			# 데이터베이스를 SHUTDOWN 시켜놓고 모든 파일을 백업합니다 

		# OPEN TABLESPACE BACKUP (ONLINE 백업)
			# 데이터베이스를 구동 중이면서 테이블스페이스 단위로 백업합니다





	# 서버 관리 백업 (RMAN 사용)(나중에 배움)
		# RMAN의 명령어를 통해 파일을 백업합니다
		# 백업파일의 정보는 컨트롤파일에 기록합니다 





	# 오라클 SECURE-BACKUP 솔루션
		# TAPE 백업-저장장치를 이용시에만 사용하는 오라클 솔루션 프로그램입니다
		# RMAN과 TAPE 장치를 연결시켜주는 해석프로그램입니다 (RMAN <==> TAPE 장치)




	
	# Terminology (용어 정리)
		# 백업 전략
			# 'WHOLE BACKUP' :모든 데이터파일 + 컨트롤파일을 백업합니다 
			
			# 'PARTIAL BACKUP' : 일부 데이터파일 + 일부 컨트롤파일만 백업합니다 
				# 아카이브모드만 가능합니다 


		# 백업 타입
			# 'FULL BACKUP' : 특정 시점에서 모든 파일의 내용을 백업합니다
			
			# 'INCREMENTAL BACKUP' :이전 백업 이후로 변경된 정보만 백업합니다(RMAN을 쓰는 이유)


		# 백업 모드 
			# 'OFFLINE BACKUP(COLD)' : 데이터베이스를 SHUTDOWN 시키고 백업을 진행합니다
			
			# 'ONLINE BACKUP(HOT)' : 데이터베이스가 구동 중인 상태에서 백업을 수행합니다 
				# 아카이브모드만 가능합니다
				# 아카이브모드가 구성이 안되면 SHUTDOWN 시키고 FULL BACKUP 받는것 밖에 안됩니다
					# 'CONSISTENT' 백업이라고 합니다

		# 백업 대상
			# 데이터파일 (필수)
			# 컨트롤파일 (필수)
			# Server Parameter File (적극 권장)
			# 아카이브 리두 로그파일 (RMAN 권장)



				
	
	# CLOSE WHOLE DATABASE BACKUP 실습
		# 백업 SCRIPT 작성 (C:\Users\buk213\SCIPRT\orcl\orcl_bak_20160803.sql)


set pagesize 999
set linesize 200
SELECT 'conn / as sysdba' AS "command"
FROM dual --1. sysdba로 로그인합니다
UNION ALL
SELECT 'set echo on'
FROM dual -- 2. script 수행명령어를 화면에 출력합니다
UNION ALL
SELECT 'spool C:\Users\buk213\BACKUP_LOG\20160803.txt'
FROM dual -- 3. 화면에 있는 전체 내용을 전부 파일로 저장합니다
UNION ALL
SELECT 'shutdown immediate '
FROM dual -- 4. database shutdown
UNION ALL
SELECT 'host copy '||name||' C:\Users\buk213\BACKUP\orcl\20160803'
FROM v$datafile -- 5. 데이터파일 복사
UNION ALL
SELECT 'host copy '||name||' C:\Users\buk213\BACKUP\orcl\20160803'
FROM v$controlfile -- 6. 컨트롤파일 복사
UNION ALL
SELECT 'startup'
FROM dual -- 7. Database 기동
UNION ALL
SELECT 'spool off'
FROM dual -- 8. 화면표시내용을 파일로 저장하는 기능 OFF
UNION ALL
SELECT 'exit' -- 9. 세션 접속 종료
FROM dual ;


		# 위 명령어로 나오는 결과물을 SCRIPT\orcl\orcl_bak_20160803.sql 파일로 저장합니다



conn / as sysdba
set echo on
spool C:\Users\buk213\BACKUP_LOG\20160803.txt
shutdown immediate
host copy C:\APP\BUK213\ORADATA\ORCL\SYSTEM01.DBF C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\SYSAUX01.DBF C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\UNDOTBS01.DBF C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\USERS01.DBF C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\EXAMPLE01.DBF C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\CONTROL01.CTL C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\CONTROL02.CTL C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\CONTROL03.CTL C:\Users\buk213\BACKUP\orcl\20160803
host copy C:\APP\BUK213\ORADATA\ORCL\CONTROL04.CTL C:\Users\buk213\BACKUP\orcl\20160803
startup
spool off
exit



		
cmd ==> C:\Users\buk213\SCIPRT\orcl\ sqlplus /nolog @orcl_bak_20160803.sql -- 스크립트를 실행합니다








		# DB-VERIFY(dbv) 툴을 이용해 현재 사용중인 ONLINE, OFFLINE 파일을 검증할 수 있습니다
			# CONTROL FILE, 온라인 리두로그파일, ASM 저장공간 파일은 검증하지 못합니다
			# 전체 페이지기 실패됨 : 0 이어야 합니다 
			# 전체 페이지에 손상한 것 표시 : 0 이어야 합니다
			# 똑같이 백업파일도 검증할 수 있습니다

		
cmd ==> dbv file=C:\APP\BUK213\ORADATA\ORCL\SYSTEM01.DBF blocksize=8192
cmd ==> dbv file='system01.dbf' blocksize=8192 LOGFILE='result.txt'	 -- 로그파일을 생성합니다 
cmd ==> dbv file='sysaux01.dbf' blocksize=8192 LOGFILE='result_sysaux_20130404.txt' START=1 END=768000 -- 첫번째 블록과





		
		# Linux는 'crontab', Windows는 'schtasks' 명령어를 이용해 해당 스크립트 예약시간을 설정합니다 








	# OPEN TABLESPACE BACKUP 실습 (ONLINE BACKUP 또는 HOT BACKUP)
		# 데이터베이스를 운영하는 도중에 백업합니다
		# 아카이브로그 모드 상태에서만 가능합니다
		# 백업이 수행되는 동안 DML 구문들로 수정된 버퍼는 온라인 리두로그파일에 저장됩니다
			# 백업이 끝나면 수정된 버퍼가 파일에 씌워지게 됩니다

		# 백업이 끝나고 CHECKPOINT를 수동으로 수행해야합니다 (데이터파일 SYNC를 일치시킵니다)


		# V$BACKUP 뷰 
			# OPEN BACKUP 상태에 있는 파일을 확인할 수 있습니다
			# CHANGE# :	SCN 값
			# TIME : OPEN BACKUP을 시작한 시각


		# V$DATAFILE_HEADER
			# 데이터파일 헤더에 기록된 SCN 값입니다





ALTER SESSION SET
nls_date_format='YYYY/MM/DD HH24:MI:SS'; -- 시간표시형식을 바꿉니다 


col status format a10
set linesize 200
set pagesize 50000
SELECT *
FROM v$backup ;  -- V$BACKUP 뷰를 확인합니다 (CHANGE#이 0이면 백업을 한번도 안한걸 의미합니다)


ALTER TABLESPACE tablespace_name
BEGIN BACKUP;  -- OPEN BACKUP을 설정합니다


ALTER TABLESPACE tablespace_name
END BACKUP;    -- BACKUP을 종료합니다



SELECT file#, CHECKPOINT_CHANGE#
FROM v$datafile_header ;   -- 데이터파일 헤더에 기록된 SCN 값을 봅니다



ALTER SYSTEM CHECKPOINT ; -- OPEN BACKUP 후 SCN 값을 맞추기 위해 강제로 CHECKPOINT를 합니다



	

		# 실습을 시작해봅니다




set pagesize 900
set linesize 400
SELECT 'conn / as sysdba' AS "command"
FROM dual -- 1. sysdba로 로그인
UNION ALL
SELECT 'set echo on'
FROM dual -- 2. script 수행명령어를 화면에 출력
UNION ALL
SELECT 'spool C:\Users\buk213\BACKUP_LOG\20130129_2.txt'
FROM dual -- 3. 화면표시 내용을 파일로 저장
UNION ALL
SELECT 'ALTER TABLESPACE '||tablespace_name||' BEGIN BACKUP ;'
FROM dba_tablespaces -- 4. BEGIN 백업 선언
WHERE contents IN ('PERMANENT' , 'UNDO')
UNION ALL
SELECT 'host copy '||file_name||' C:\Users\buk213\BACKUP\orcl\20160803_2'
FROM dba_data_files -- 5. 데이터파일 복사
UNION ALL
SELECT 'ALTER TABLESPACE '||tablespace_name||' END BACKUP ;'
FROM dba_tablespaces -- 6. END 백업 선언
WHERE contents IN ('PERMANENT' , 'UNDO')
UNION ALL
SELECT 'ALTER SYSTEM CHECKPOINT ;'
FROM dual -- 7. 체크포인트 수행
UNION ALL
SELECT 'spool off'
FROM dual -- 8. 화면표시내용을 파일로 저장하는 기능 OFF
UNION ALL
SELECT 'exit' -- 9. 세션 접속 종료
FROM dual ;		




	# 위 명령어로 나오는 결과물을 SCRIPT\orcl\orcl_bak_20160803_2.sql 파일로 저장합니다



conn / as sysdba
set echo on
spool C:\Users\buk213\BACKUP_LOG\20130129_2.txt
ALTER TABLESPACE SYSTEM BEGIN BACKUP ;
ALTER TABLESPACE SYSAUX BEGIN BACKUP ;
ALTER TABLESPACE UNDOTBS1 BEGIN BACKUP ;
ALTER TABLESPACE USERS BEGIN BACKUP ;
ALTER TABLESPACE EXAMPLE BEGIN BACKUP ;
host copy C:\APP\BUK213\ORADATA\ORCL\EXAMPLE01.DBF C:\Users\buk213\BACKUP\orcl\20160803_2
host copy C:\APP\BUK213\ORADATA\ORCL\USERS01.DBF C:\Users\buk213\BACKUP\orcl\20160803_2
host copy C:\APP\BUK213\ORADATA\ORCL\UNDOTBS01.DBF C:\Users\buk213\BACKUP\orcl\20160803_2
host copy C:\APP\BUK213\ORADATA\ORCL\SYSAUX01.DBF C:\Users\buk213\BACKUP\orcl\20160803_2
host copy C:\APP\BUK213\ORADATA\ORCL\SYSTEM01.DBF C:\Users\buk213\BACKUP\orcl\20160803_2
ALTER TABLESPACE SYSTEM END BACKUP ;
ALTER TABLESPACE SYSAUX END BACKUP ;
ALTER TABLESPACE UNDOTBS1 END BACKUP ;
ALTER TABLESPACE USERS END BACKUP ;
ALTER TABLESPACE EXAMPLE END BACKUP ;
ALTER SYSTEM CHECKPOINT ;
spool off
exit

		

cmd ==> C:\Users\buk213\SCIPRT\orcl\ sqlplus /nolog @orcl_bak_20160803_2.sql -- 스크립트를 실행합니다






ALTER DATABASE BEGIN BACKUP ;  -- 10g버전이상부터 모든 테이블스페이스를 한꺼번에 온라인 백업 가능합니다 (모든 데이터파일이 동일한 SCN에서 BEGIN BACKUP 선언이 가능하게 되었습니다)


ALTER DATABASE END BACKUP;  -- 모든 데이터파일에 설정된 OPEN 백업 설정을 해제합니다






















--------------------------------------------------------------------------------------------------

<온라인 리두로그 그룹 손실에 대한 장애조치>


## 온라인 리두로그 그룹에 대한 장애조치
	# 커밋된 모든 SQL구문들이 온라인 리두로그 그룹에 저장됩니다

	# 리두로그 그룹의 멤버파일이 일부만 손상된 경우
		# 유실된 파일 정보를 데이터베이스에서 삭제하고 다시 멤버파일을 로그그룹에 추가하는 방법




col member format a41
col group# format 999
col status format a10
set linesize 200
set pagesize 999
SELECT group#, member, status
FROM v$logfile
ORDER BY 1,2 ;    -- 온라인 로그 그룹의 멤버파일을 확인합니다




col status format a10
col archived format a3
SELECT group#, status, sequence#, archived
FROM v$log ;  -- 현재 로그 그룹의 상태 정보를 확인합니다


SHUTDOWN ABORT 


cmd ==> del C:\app\buk213\oradata\orcl\REDO01B.RDO -- REDO01B.RDO 파일을 삭제합니다


STARTUP   -- 위에 ABORT했으므로 시작하면서 인스턴스 복구가 수행되어 로그스위치가 한 번 일어납니다



COL MEMBER FOR A41
COL GROUP# FOR 99
COL SEQUENCE# FOR 9999
COL GROUP_STATUS FOR A8
COL FILE_STATUS FOR A7
SET LINESIZE 200
SELECT A.GROUP#, A.SEQUENCE#, A.ARCHIVED
, A.STATUS AS GROUP_STATUS, B.STATUS AS FILE_STATUS
, B.MEMBER
FROM V$LOG A INNER JOIN V$LOGFILE B
ON (A.GROUP# = B.GROUP#)
ORDER BY 1, 5 ;    --  온라인 로그그룹의 멤버파일 상태를 확인합니다 (REDO01B.RDO가 INVALID라고 나옵니다) 



ALTER SYSTEM SWITCH LOGFILE ;

ALTER SYSTEM CHECKPOINT ;   -- 로그스위치를 발생시켜 그룹1을 INACTIVE 상태로 바꿉니다



ALTER DATABASE DROP LOGFILE MEMBER
'C:\app\buk213\oradata\orcl\redo01b.rdo' ;  -- 해당 멤버파일 정보를 삭제합니다


ALTER DATABASE ADD LOGFILE MEMBER
'C:\app\buk213\oradata\orcl\redo01b.rdo' TO GROUP 1 ;  -- 새로운 멤버파일을 생성합니다	







			# 리두 로그그룹을 CLEAR 시켜서 삭제된 파일을 복원하는 방법
				# CLEAR는 두 번시켜줍니다
					# 한 번만하면 ALERT_LOG 기록에 헤더를 잘 읽지 못했다는 에러메세지가 나옵니다
		
				# CLEAR 된 그룹은 UNUSED 상태가 됩니다






SHUTDOWN IMMEDIATE


cmd ==> del C:\APP\BUK213\ORADATA\ORCL\REDO03B.RDO  -- REDO03B.RDO 멤버파일을 지웁니다


STARTUP  -- 정상적으로 실행되지만 온라인 로그그룹을 확인해보면 REDO03B.RDO 파일은 INVALID 상태입니다




ALTER DATABASE CLEAR LOGFILE GROUP 3 ;  -- 그룹 3을 CLEAR 시킵니다 (INACTIVE 상태만 가능합니다)
										-- 삭제한 REDO03B.RDO 파일이 생성됩니다


ALTER DATABASE CLEAR LOGFILE GROUP 3 ;  -- 두번째 CLEAR를 시킵니다 (UNUSED 상태가 됩니다)









	# 특정 리두로그 그룹의 모든 멤버파일이 손실된 경우 (아카이브가 된 경우)
		# 위 상태에서 그룹2가 CURRENT 이고 그룹3이 UNUSED 인 상태에서 로그스위치를 합니다


ALTER SYSTEM SWITCH LOGFILE ;

ALTER SYSTEM CHECKPOINT ;  -- 그룹3을 CURRENT가 되게 로그스위치를 작동시킵니다


SHUTDOWN IMMEDIATE -- 데이터베이스를 종료합니다


cmd ==> del C:\app\buk213\oradata\orcl\REDO02.LOG 
		del C:\app\buk213\oradata\orcl\REDO02B.DBO    -- 그룹2 파일을 전부 삭제합니다



STARTUP MOUNT -- 마운트 상태로 시작합니다 



COL MEMBER FOR A41
COL GROUP# FOR 99
COL SEQUENCE# FOR 9999
COL GROUP_STATUS FOR A8
COL FILE_STATUS FOR A7
SET LINESIZE 200
SELECT A.GROUP#, A.SEQUENCE#, A.ARCHIVED
, A.STATUS AS GROUP_STATUS, B.STATUS AS FILE_STATUS
, B.MEMBER
FROM V$LOG A INNER JOIN V$LOGFILE B
ON (A.GROUP# = B.GROUP#)
ORDER BY 1, 6 ;     -- 로그파일 및 그룹정보를 확인합니다




ALTER DATABASE DROP LOGFILE GROUP 2 ;   -- 장애가 발생한 그룹2를 삭제합니다




ALTER DATABASE ADD LOGFILE GROUP 2
('C:\app\buk213\oradata\orcl\redo02b.rdo'
,'C:\app\buk213\oradata\orcl\redo02.log') SIZE 50 M reuse ; -- 다시 그룹2를 생성합니다




ALTER DATABASE OPEN ;  -- 데이터베이스를 OPEN 합니다


ALTER SYSTEM SWITCH LOGFILE ;

ALTER SYSTEM CHECKPOINT ;  -- 로그스위치 및 체크포인트를 3번 수행합니다












	# 아카이브 되지 않은 그룹에 모든 멤버파일이 유실되었고 DB는 OPEN 상태인 경우
		# Windows 실습환경으로는 못한다고 합니다 (서버 운영 도중 파일 삭제가 안되므로)
		
		# 리두로그파일을 아카이빙하려고 하는데 공간이 없어서 못하는 경우
			
			1. LOG-WRITER가 아카이빙을 시도 중인 온라인 리두로그그룹을 사용하려합니다
			
			2. 리두로그그룹은 아카이빙을 하려고 기다리는중이므로 LOG-WRITER는 대기상태에 빠집니다

			3. CPU 사용량이 급격히 증가합니다

			4. 아카이브 - HANG 상태라고 합니다
			
			5. CLEAR UNARCHIVED를 여러번 시켜줍니다 (최소 2번 이상)
				# ALERT_LOG 파일에 오류가 안뜰 때까지

			6. 장애 그룹들을 삭제합니다

			7. 새로운 로그 그룹을 생성합니다




ALTER DATABASE CLEAR UNARCHIVED LOGFILE GROUP 2 ; -- HANG을 없애기 위해 UNARCHIVED 합니다
												  -- CLEAR를 ALERT_LOG에 에러메세지가 안나올 때까지 계속 실행시켜줍니다


ALTER DATABASE DROP LOGFILE GROUP 2 ;   -- 로그그룹2 를 삭제합니다 


ALTER DATABASE ADD LOGFILE GROUP 2
('C:\APP\BUK213\ORADATA\ORCL\REDO02.LOG'
,'C:\APP\BUK213\ORADATA\ORCL\REDO02B.RDO') SIZE 50 M REUSE ;  -- 로그그룹2를 새로 생생헙니다















	# CURRENT 리두로그 그룹의 모든 멤버파일이 유실되었고 DB가 정상적으로 종료된 경우
		# 로그그룹3이 CURRENT 가 된 상태에서 리두로그를 생성하는 작업을 실행합니다


CREATE TABLE hr.sales_test3
AS
SELECT *
FROM sh.sales
WHERE 1=2 ;   -- 리두로그 그룹을 생성하는 작업을 실행합니다 (마지막에 거짓조건을 사용해 해당 column만 복사합니다)




INSERT INTO hr.sales_test3
SELECT *
FROM sh.sales
WHERE prod_id=139 ;    -- 리두로그 그룹을 생성하는 작업을 실행합니다2


COMMIT ; 			-- 커밋(COMMIT)되므로 온라인 리두로그그룹에 저장됩니다



DELETE FROM hr.sales_test3
WHERE prod_id=139
AND cust_id=8349 ;      -- 리두를 생성하는 데이터베이스 작업을 수행된합니다


COMMIT ;



SHUTDOWN IMMEDIATE  -- 정상적으로 종료합니다 



cmd ==> del C:\app\buk213\oradata\orcl\REDO03.LOG
	    del C:\app\buk213\oradata\orcl\REDO03B.DBO -- 현재 CURRENT인 두 파일을 삭제합니다



STARTUP -- 실행하면 에러가 발생합니다  ORA-03113 : 통신 채널에 EOF가 있습니다



conn / as sysdba 
STARTUP MOUNT    -- sysdba로 접속해서 MOUNT까지 접속합니다







		# 현재 MOUNT 상태이므로 그룹3가 CLEAR 또는 삭제가 안됩니다 (+ 로그스위치도 안됩니다)
			# RESETLOGS 옵션으로 데이터베이스를 OPEN 해야합니다
				# RESTLOGS : 현재 존재하는 모든 온라인 로그파일를 초기화시키고 유실된 멤버파일을 자동으로 생성합니다






RECOVER DATABASE UNTIL CANCEL ;  -- RESTLOGS 옵션이 가능하게 하기 위해 일부러 입력한 명령어입니다

ALTER DATABASE OPEN RESETLOGS ;  -- 데이터베이스를  RESETLOGS 모드로 엽니다(모든 온라인 리두로그를 초기화시키고 유실된 멤버파일을 생성합니다)





ALTER SYSTEM SWITCH LOGFILE ;

ALTER SYSTEM CHECKPOINT ;  -- 로그스위치, 체크포인트를 UNUSED가 모두 사라질 때까지 합니다

























-------------------------------------------------------------------------------------------------

<컨트롤파일 손실에 대한 장애조치>


## 컨트롤파일(CONTROL FILE)이 손실된 경우 
	# 컨트롤파일에 대한 다중화가 구성된 DB에서만 실습해야합니다
	# 컨트롤파일이 없으면 ORA-00205, ORA-00214 에러가 발생합니다


	
	1. 서버를 중지합니다

SHUTDOWN IMMEDIATE -- 서버를 중지합니다


	2. 컨트롤파일을 삭제합니다 (장애조치를 위해)
		# cmd ==> del C:\app\buk213\oradata\orcl\CONTROL01.CTL


	3. 다중화된 컨트롤파일 하나를 복사해서 삭제된 파일을 복원합니다
		# cmd ==> copy C:\app\buk213\oradata\orcl\CONTROL02.CTL C:\app\buk213\oradata\orcl\CONTROL01.CTL





SELECT name
FROM v$controlfile ;  -- 컨트롤파일의 운영경로를 확인합니다





	# RMAN을 이용한 컨트롤파일 손실에 대한 장애조치
		# CMD ==> rman target /
		# RMAN> STARTUP NOMOUNT;
		# RMAN> RESTORE controlfile FROM 'C:\app\buk213\oradata\orcl\control02.ctl' ; 
		# RMAN> HOST 'dir c:\app\buk213\oradata\orcl\CONTROL*';
		# RMAN> ALTER DATABASE MOUNT; 
		# RMAN> ALTER DATABASE OPEN;
		# SQL> SHOW parameter control_files; (제대로 설정됐는지 확인해봅니다)






	
	
	# 모든 컨트롤파일 손실에 대한 장애조치
		# 컨트롤파일 온라인 백업
			# 트레이스파일(Trace File) 형식 백업
				# 컨트롤파일을 생성하는 SQL문이 포함된 트레이스파일을 생성합니다
				# 컨트롤파일에서 [Set #1. NORESETLOGS case] 라인에 있는 CREATE... 구문을 찾습니다




ALTER DATABASE BACKUP CONTROLFILE
TO TRACE
AS 'C:\Users\buk213\BACKUP\orcl\ctl\orcl_crectl.trc.20130226';-- 트레이스파일 형식으로 백업하기



CREATE CONTROLFILE REUSE DATABASE "ORCL" NORESETLOGS  ARCHIVELOG
   MAXLOGFILES 16 /* 생구 서기대 최대 REDO LOG GROUP 수 */
	MAXLOGMEMBERS 3 /* 각 REDO LOG GROUP해 최대 맴맴 수 */
	MAXDATAFILES 100 /* 생구서기대 최대 DATAFILE 수 */
	MAXINSTANCES 8 /* RAC인모 구구 서기대 최대 INSTANCE 수*/
	MAXLOGHISTORY 292 /* REDO LOG history파 entry 수 */
LOGFILE
  GROUP 1 (
    'C:\APP\BUK213\ORADATA\ORCL\REDO01.LOG',
    'C:\APP\BUK213\ORADATA\ORCL\REDO01B.RDO'
  ) SIZE 50M BLOCKSIZE 512,
  GROUP 2 (
    'C:\APP\BUK213\ORADATA\ORCL\REDO02.LOG',
    'C:\APP\BUK213\ORADATA\ORCL\REDO02B.RDO'
  ) SIZE 50M BLOCKSIZE 512,
  GROUP 3 (
    'C:\APP\BUK213\ORADATA\ORCL\REDO03.LOG',
    'C:\APP\BUK213\ORADATA\ORCL\REDO03B.RDO'
  ) SIZE 50M BLOCKSIZE 512,
  GROUP 4 'C:\APP\BUK213\ORADATA1\ORCL\ONLINELOG\O1_MF_4_CSLTNBNK_.LOG'  SIZE 100M BLOCKSIZE 512
DATAFILESELECT *
FROM v$backup ;
  'C:\APP\BUK213\ORADATA\ORCL\SYSTEM01.DBF',
  'C:\APP\BUK213\ORADATA\ORCL\SYSAUX01.DBF',
  'C:\APP\BUK213\ORADATA\ORCL\UNDOTBS01.DBF',
  'C:\APP\BUK213\ORADATA\ORCL\USERS01.DBF',
  'C:\APP\BUK213\ORADATA\ORCL\EXAMPLE01.DBF'
CHARACTER SET AL32UTF8
;  --[Set #1. NORESETLOGS case]  구문의 내용 -- STANDBYLOGFILE 구문이 있었는데 그 구문은 삭제해줘야합니다




ALTER TABLESPACE TEMP ADD TEMPFILE 'C:\APP\BUK213\ORADATA\ORCL\TEMP02.DBF'
SIZE 41943040  REUSE AUTOEXTEND ON NEXT 10485760  MAXSIZE 32767M;  -- 임시파일을 추가하는 스크립트입니다 같은 파일 안에 End of tempfile addtions 위에 있습니다








			# 바이너리파일 형식 백업 
				# 명시된 경로에 똑같은 복사본을 하나 만듭니다


ALTER DATABASE BACKUP CONTROLFILE
TO 'C:\Users\buk213\BACKUP\orcl\ctl\control.bak.20130129' ; -- 바이너리파일 형식으로 백업하기






		# 모든 컨트롤파일 유실로부터 장애조치
			# SHUTDOWN 후 모든 컨트롤파일을 삭제합니다
		
			# 미리 만들어논 스크립트를 실행합니다
				# sql> @c:\users\buk213\SCRIPT\orcl\orcl_crectl.sql




COL MEMBER FOR A41
COL GROUP# FOR 99
COL SEQUENCE# FOR 9999
COL GROUP_STATUS FOR A8
COL FILE_STATUS FOR A7
SET LINESIZE 200
SELECT A.GROUP#, A.SEQUENCE#, A.ARCHIVED, A.FIRST_CHANGE#
, A.STATUS AS GROUP_STATUS, B.STATUS AS FILE_STATUS
, B.MEMBER
FROM V$LOG A INNER JOIN V$LOGFILE B
ON (A.GROUP# = B.GROUP#)
ORDER BY 1, 5 ;   -- 온라인 리두 로그그룹 및 멤버파일 상태를 확인합니다 (STALE 상태가 나옵니다)



col name format a50
col status format a15
SELECT name, status
FROM v$datafile ; -- 데이터파일 상태를 확인합니다 (RECOVER 혹은 ONLINE 상태가 나옵니다)
                  -- 만약 SHUTDOWN ABORT가 된 경우 RECOVER라고 나옵니다 


SELECT file#, checkpoint_change#
FROM v$datafile_header ;  -- 데이터파일 헤더 정보를 확인합니다 (큰 의미 없습니다)


RECOVER DATABASE ;  -- 데이터베이스를 복구합니다


ALTER DATABASE OPEN; -- 데이터베이스를 실행합니다



ALTER SYSTEM SWITCH LOGFILE ;

ALTER SYSTEM CHECKPOINT ;   -- 위 두 문장을 계속 실행시켜서 STALE 상태가 나온 파일들을 없애줍니다



SELECT tablespace_name, file_name
FROM dba_temp_files ;  -- 임시파일 정보를 확인합니다 (아무 정보도 표시되지 않습니다)



@C:\Users\buk213\SCRIPT\orcl\orcl_add_tempfile.sql -- 미리 생성한 스크립트를 이용해 임시파일을 생성합니다










--------------------------------------------------------------------------------------------------

<임시파일(TEMP) 손실에 대한 장애조치>


## TEMP01.DBF 파일이 손상된 경우
	# SHUTDOWN으로 서버를 끈 후 TEMP01.DBF 파일을 삭제합니다
	# Windows 시스템은 삭제되도 자동으로 서버 기동시 생성됩니다
		# 배트섹터난걸로 간주해서 장애조치를 합니다

	# PGA에 할당된 초기화파라미터를 수정합니다


SHOW PARAMETER memory_target; -- MEMORY_TARGET 파라미터를 확인합니다 

ALTER SYSTEM SET memory_target=0 SCOPE=memory ;  -- MEMORY_TARGET을 0으로 설정합니다


SHOW PARAMETER pga_aggregate_target  -- PGA_AGGREGATE_TARGET 파라미터를 확인합니다

ALTER SYSTEM SET pga_aggregate_target=40M SCOPE=memory ; -- PGA_AGGREGATE_TARGET를 축소합니다



SELECT *
FROM sh.sales
ORDER BY 1,2,3,4,5,6,7;  -- 91만개의 데이터를 불러와야되므로 TEMP 파일을 사용해야하는데 임시파일이 없으면 에러가 납니다 



col tablespace_name format a10
col file_name format a41
set linesize 200
set pagesize 999
SELECT tablespace_name, file_name, bytes/1024 SIZE_KB
FROM dba_temp_files;  -- TEMP 파일의 정보를 확인합니다



ALTER TABLESPACE temp
ADD TEMPFILE
'C:\APP\BUK213\ORADATA\ORCL\TEMP02.DBF'
SIZE 20480 K
AUTOEXTEND ON NEXT 10M ; -- 새로운 TEMP02.DBF 파일을 추가합니다



ALTER TABLESPACE temp
DROP TEMPFILE
'C:\APP\BUK213\ORADATA\ORCL\TEMP01.DBF' ;  -- 기존 TEMP01.DBF 파일을 삭제합니다(배트섹터 파일이므로 삭제합니다)



		# TEMP02.DBF가 유일한 TEMP파일이 됐으므로 장애조치가 완료됐습니다
			# 다시 TEMP01.DBF로 변경해도 됩니다




















--------------------------------------------------------------------------------------------------

<SPFILE 손실에 대한 장애조치>


## SPFILE이 손상된 경우
	# SPFILE은 직접 VIM으로 수정하면 안되는듯 합니다
	# 백업 폴더를 만들어줍니다
		# cmd ==> mkdir c:\Users\buk213\BACKUP\orcl\pfile
		# cmd ==> mkdir c:\Users\buk213\BACKUP\orcl\spfile


	# PFILE을 SPFILE로부터 백업받습니다


	
CREATE PFILE='c:\Users\buk213\BACKUP\orcl\pfile\initorcl.bkg.20130130'
FROM SPFILE ;

CREATE PFILE='c:\Users\buk213\initorcl.ora.memory'
FROM MEMORY ; -- 11g 부터 되는 명령어로 메모리로부터 pfile을 만듭니다

show parameter spfile;  -- spfile 경로와 이름을 확인합니다





	# SPFILE 자체를 백업받습니다

sql> host copy C:\APP\BUK213\PRODUCT\11.2.0\DBHOME_1\DATABASE\SPFILEORCL.ORA -
               C:\Users\buk213\BACKUP\orcl\spfile\SPFILEORCL.ORA.BAK.1


CREATE SPFILE='c:\Users\buk213\BACKUP\orcl\spfile\spfileorcl.ora.bak.2'
FROM PFILE='c:\Users\buk213\BACKUP\orcl\pfile\initorcl.bkg.20130130' ;
-- PFILE로부터 SPFILE을 백업받습니다 (방법2)





	# SHUTDOWN 상태에서 STARTUP 중 SPFILE이 유실된 경우
		# 실습을 위해 SPFILE 삭제
			# SHUTDOWN IMMEDIATE 로 데이터베이스 종료	
			
			# cmd ==> del %ORACLE_HOME%\database\SPFILEORCL.ORA
			
			# STARTUP 을 입력하면 정상적으로 실행되지 않습니다




		1. 백업된 PFILE로부터 SPFILE을 복원


CREATE SPFILE
FROM PFILE='c:\Users\buk213\BACKUP\orcl\pfile\initorcl.bkg.20130130' ; -- 백업해논 PFILE로 SPFILE을 생성합니다 

		
CREATE SPFILE='c:\Users\buk213\spfileorcl.ora.memory'
FROM MEMORY;  -- 11g 새로운 명령어로 OPEN, NOMOUNT, MOUNT 상태에서만 실행할 수 있습니다 (SPFILE 복원)



		2. 운영체제 명령어로 백업된 SPFILE을 복사해서 복원하는 방법

sql> host copy C:\Users\buk213\BACKUP\orcl\spfile\SPFILEORCL.ORA.BAK.1 -
	 		   %ORACLE_HOME%\database\SPFILEORCL.ORA -- copy 명령어로 복사합니다







	# 정상적인 서비스 중에 SPFILE이 유실된 상황인 경우
		# 실습을 위해 SPFILE을 삭제합니다 
			# cmd ==> host del %ORACLE_HOME%\database\SPFILEORCL.ORA 

		
		# 장애조치는 위에 1. 2. 와 같습니다 






	# STATIC 초기화 파라미터가 잘못된 값으로 설정이 바뀐 후 데이터베이스가 기동되지 못하는 경우


SHOW PARAMETER audit_file_dest;  -- 파라미터 값을 확인합니다

ALTER system SET audit_trail='xml','extended' scope=spfile;

ALTER SYSTEM SET audit_file_dest=
'C:\bpp\buk213\admin\orcl\adump' scope=spfile ;  -- 위와같이 설정 변경하고 (bpp로 잘못된 경로 입력) 다시 시작하면 ORA-09822 에러가 납니다






		# 아래같이 설정을 변경하고 SHUTDOWN ==> STARTUP 하면 ORA-09822 에러가 납니다

			1. SPFILEORCL.ORA 파일이 훼손돼서 실행이 안돼면 우선 SPFILEORCLE.ORA를 삭제합니다
			2. ORACLE SERVICE를 중지했다 다시 시작합니다
			
			3. 백업해논 INITorcl.ORA 파일을 복원해서 STARTUP으로 DB를 실행합니다 
			4. SHOW PARAMETER SPFILE 하면 경로가 설정되지 않은 채로 기동됐습니다 (PFILE로 기동) 

			5. CREATE SPFILE FROM PFILE 명령어로 SPFILE을 생성합니다
			6. SPFILEORCL.ORA 파일이 생성돼므로 다시 SHUTDOWN ==> STARTUP으로 기동합니다












--------------------------------------------------------------------------------------------------

<PASSWORD-FILE 손실에 대한 장애조치>

## PASSWORD-FILE 이 손상된 경우
	
	# 패스워드 파일을 삭제합니다 (PWDorcl.ora 파일)
		# cmd ==> %ORACLE_HOME%\database\ del PWD*
		# 원격접속을 시도하면 권한이 불충분하다는 에러가 뜹니다	


	# 장애조치 시작
		# cmd ==> orapwd file=PWDorcl.ora password=oracle4U 로 파일을 재생성합니다


	# 다시 원격접속을 시도해보면 잘 접속됩니다












--------------------------------------------------------------------------------------------------

	$$ 오라클 데이터베이스 OCP 시험 소개 (16/8/1)
		$ 우리나라 60% 점유율 
		$ 라이센스비용 최대 400억짜리 시디 한장
		$ OCM 자격증 우리나라 69명밖에 없다
		$ 지금까지 배운 수업들 150 * 3만원 정도 (교재 값: 15만원)
		$ 시험비용은 15,27,27 만원




<오라클 인스턴스에 대한 ALERT-LOG 및 트레이스 파일>

## 모든 인스턴스는 자신만의 ALERT-LOG 를 가지고 있습니다 
	# 파일이 없어지면 알아서 다시 생성됩니다
		# 다른 트레이스파일들은 자동으로 생성되지 않습니다


	# alert_orcl.log 파일에 기록되는 내용들  
		1. 초기화 파라미터의 설정 값들
	

		2. 여러가지 오류코드들
			# ORA-00600 번대 오류들 (커널 오류)
			# 데이터블록 손상 오류 (ORA-01578)
			# 교차락 (Dead-Lock) 오류 (ORA-00060)
			# 메모리 부족 오류 


		3. 특정 SQL문의 실행 내역들
			# CREATE DATABASE
			# ALTER DATABASE
			# CREATE TABLESPACE
			# ALTER TABLESPACE
			# DROP TABLESPACE
			# ALTER DATABASE ADD LOGFILE
			# ALTER DATABASE DROP LOGFILE


		4. 서버의 기동 및 중지에 수행된 내용
	
		5. 아카이브된 리두 로그파일 생성 내용

		6. 데이터베이스에 대한 복구 수행 내용

		7. 공유서버 프로세스와 디스패처 프로세스의 작동 메시지 & 오류 내용 (공유서버를 잘 안씁니다)
		
		8. 로그스위치 수행 내용 (Thread 1 advanced to log sequence xx)









SHOW PARAMETER background_dump_dest -- BACKGROUND_DUMP_DEST 파라미터 정보를 확인합니다


















--------------------------------------------------------------------------------------------------

<Automatic Diagnostic Repository (ADR)>

## 장애조치 시작
	# Automatic Diagnostic Repository (ADR)
		# 오라클 서버와 관련된 로그들이 생성되는 경로를 알아서 구성하는 기능을 말합니다 
		
		# DIAGNOSTIC_DEST 초기화 파라미터에 경로를 설정합니다
			# 설정된 경로 이름을 ADR Base라고 합니다
			# 'ADR Base' 디렉토릭 구조
				# 'ORACLE_BASE\diag\rdbms' : 데이터베이스 인스턴스 로그파일
					# \orcl(DB_NAME)\orcl(SID)	
			
				
					# \alert 폴더
						# log.xml 이름으로 XML 형식의 ALERT-LOG 파일이 생성됩니다


					# \incident 폴더 
						# 백그라운드 프로세스, 서버프로세스의 모든 장애트레이스가 저장됩니다


					# \trace 폴더
						# orcl_ora_xxx : 서버프로세스에 의해 생성된 트레이스파일
						# orcl_ckpt_xxx : ckpt 프로세스에 의해 생성된 트레이스파일
						# orcl.yyy.xxx : 특정 yyy 백그라운드 프로세스에 의해 생성된 트레이스파일 
						# alert_orcl.log : ALERT-LOG 파일



				# 'ORACLE_BASE\diag\tnslsnr' : 리스너 로그파일
					# \215-08(hostname)\listener(listener_name)
					
					
						# \alert 폴더
							# log.xml 이름으로 XML 형식의 로그가 자동으로 저장됩니다 	
		
						# \trace 폴더
							# 텍스트형식의 로그가 자동으로 저장됩니다



				# 'ORACLE_BASE\diag\asm' : 인스턴스 로그파일
					#







		# ORACLE 10g를 관리할 때는 3개의 초기화 파라미터를 관리자가 직접 설정해야 합니다	
			# BACKGROUND_DUMP_DEST : ALERT-LOG 파일의 경로를 설정합니다
			# USER_DUMP_DEST : 서버 프로세스의 장애-트레이스 파일의 경로를 설정합니다
			# CORE_DUMP_DEST : 오라클-서버의 메모리 덤프가 저장되는 경로를 설정합니다
			
			# ORACLE 11g 버전부터는 관리자가 설정하지 않고 ADR 기능에 의해 자동으로 설정됩니다 (DIAGNOSTIC_DEST 파라미터에 의해)







SHOW PARAMETER diagnostic_dest  -- DIAGNOSTIC_DEST 파라미터 값을 확인합니다



SHOW PARAMETER _dump_dest  -- BACKGROUND_DUMP_DEST, CORE_DUMP_DEST, USER_DUMP_DEST 파라미터의 경로를 확인합니다




col value format a62
col name format a22
col inst_id format 99
set linesize 200
set pagesize 999
SELECT *
FROM V$DIAG_INFO ;  -- V$DIAG_INFO 뷰로 ADR 경로 정보를 조회합니다
					-- 결과 행 중
					-- Active Problem Count : 에러코드가 얼마나 많이 발생했는지 
					-- Active incident Count : 동일한 에러코드가 얼마나 많이 반복됐는지 




ALTER SESSION SET SQL_TRACE TRUE; -- trace 파일에 트레이스 로그를 기록합니다


