<Row Chaining 과 Row Migration>

 SYSTEM/ACTIVE 언두-테이블스페이스와 사용자-테이블스페이스의 모든 자료가 유실되었습니다

## 기존에 테이블에 있던 데이터보다 긴 데이터가 들어오면 (UPDATE문으로 인해)
	# 옛날 버젼(7i)에서는 Row Chaining 현상이 일어났고 요즘 버젼은 Row Migration 현상이 일어납니다
	# 데이터들이 조각나면서 여러 블록에 저장되는 걸 뜻합니다

	# PCTFREE 파라미터
		# PCTFREE 파라미터를 사용해 Row Migration을 줄일 수 있습니다
		# 해당 퍼센트만큼 빈공간을 세그먼트에 확보합니다 (보통 40)
		# 행의 길이가 길어진 경우 동일 블락에 데이터가 저장되어 디스크 I/O를 줄일 수 있습니다




CREATE TABLE hr.emp_dept80
TABLESPACE example
PCTFREE 20
AS
SELECT *
FROM hr.employees
WHERE department_id=80
ORDER BY employee_id ;  -- PCTFREE 20%로 설정한 테이블입니다. (보통 40%)














-------------------------------------------------------------------------------------------------
	
	$ 공부는 찾아서 하자
		$ 대학에서 교수님이 알려주시는건 가이드일 뿐
		$ 지금 보는 자료들은 강사님이 15년간 만들어 온 편집본이다
        $ 직장가서 공부하고 있으면 많이 눈치받는다고 한다
		$ 직장에서 질문은 효율적으로 최대한 적게



<언두 데이터 (Undo Data)>

## 언두 데이터
	# DML 문장을 통해 데이터가 변경되면 변경 전 데이터가 Undo 데이터로 생성됩니다
	# 오직 오라클에만 있습니다	
	
	# 읽기일관성을 가질 수 있게 해주는 중요한 요소이다
		# 읽기일관성이란 Query가 시작된 시점의 데이터와 일치하는 결과를 제공하는걸 말합니다
	# Flashback Query를 할 수 있게 해주는 요소이다 
	# 실패한 트랙잭션으로부터 복구할 때 사용합니다 (PMON 프로세스를 사용합니다)


	# 언두 데이터는 언두-테이블스페이스에 저장됩니다
		# 하나의 인스턴스는 1개의 언두-테이블스페이스만 사용할 수 있습니다
		# 두 개 이상의 인스턴스가 1개의 언두-테이블스페이스를 공유할 수 없습니다


	# 언두 데이터는 서버가 알아서 AUTO로 관리해줍니다 (11g 이상부터 자동으로 AUTO)
		# SHOW PARAMETER UNDO_MANAGEMENT; 로 확인 가능합니다



	# V$UNDOSTAT 뷰를 사용해 특정 시간동안에 사용한 언두 블록의 갯수를 알 수 있습니다


SELECT begin_time, (end_time-begin_time)*86400 AS "INTERVAL_SECs"
,UNDOBLKS AS "BLOCKS"
,UNDOBLKS*8192/1024 SIZE_KB
FROM v$undostat ;  -- V$UNDOSTAT뷰로 시간대별 트랙잭션이 발생하는 빈도를 확인할 수 있습니다





	# 언두 모니터링 (ALERT-LOG 파일)
		# ORA-01650: UNABLE TO EXTEND ROLLBACK SEGMENT 에러
			# 언두-테이블스페이스 안에 데이터파일의 공간이 부족해 생기는 오류입니다
			# 사용 중인 언두-테이블스페이스에 데이터파일을 추가해주면 해결됩니다


		# ORA-01555 SNAPSHOT TOO OLD 에러
			# 읽기일관성과 관련된 에러입니다
			
			# 자주 발생하는 에러입니다

			# 이 에러를 줄이기 위해 UNDO_RETENTION 초기화파라미터를 도입합니다
				# UNDO_RETENTION = 900 (커밋 후 900초 동안 언두파일을 지우지 않겠다는 뜻입니다)

				# 이 파라미터를 이용해 언두-테이블스페이스의 크기를 다시 재설정해줘야 합니다

				# UNDO_RETENTION GUARANTEE 를 이용해 강제로 RETENTION 시간동안 언두 데이터를 유지합니다
			



SELECT ((UR * (UPS * DBS)) + (DBS * 24))/1024/1024 AS "MBytes"
FROM
( SELECT value AS UR
FROM v$parameter
WHERE name = 'undo_retention')
,( SELECT (SUM(undoblks)/
SUM(
( (end_time ? begin_time)*86400 )
)
) AS UPS
FROM v$undostat)
,( SELECT value AS DBS
FROM v$parameter
WHERE name = 'db_block_size');  -- 이 공식을 사용하면 UNDO_RETENTION 값에 따른 적절한 언두-테이블스페이스의 크기를 구할 수 있습니다 (오라클이 공개한 공식)

	


		# 언두데이터 관리 지침
			# 사용 중인 언두-테이블스페이스 이름과 파일크기를 확인합니다 
			# 현재 사용 중인 데이터파일보다 50% 큰 데이터파일을 추가합니다
			# UNDO_RETENTION 값을 30% 정도 더한 값으로 설정합니다


		








CREATE UNDO TABLESPACE UNDOTBS01
DATAFILE
'c:\app\buk213\oradata\orcl\undotbs1a.dba'
SIZE 11256K;   -- 두 개의 언두-테이블스페이스를 생성한다


CREATE UNDO TABLESPACE UNDOTBS02
DATAFILE
'c:\app\buk213\oradata\orcl\undotbs2a.dba'
SIZE 11256K
AUTOEXTEND ON NEXT 10M ;



ALTER SYSTEM SET
undo_tablespace=UNDOTBS01
SCOPE=both
SID='orcl1' ;   -- 언두-테이블스페이스를 사용 할 인스턴스 이름을 명시해줄 수 있다 (명시 안하면 *로 된다)



ALTER SYSTEM SET
undo_tablespace=UNDOTBS02
SCOPE=both
SID='orcl2' ;  -- orcl2 인스턴스에게 UNDOTBS02 테이블스페이스를 사용할 수 있게 해줍니다



SELECT segment_name, status, file_id, block_id
FROM dba_rollback_segs ;  -- 현재 사용중인 UNDO-SEGMENT 이름을 확인합니다


SELECT segment_name, extent_id, bytes/1024 EXTENT_SZ_KB
FROM dba_undo_extents
ORDER BY 1,2 ;  -- 언두-세그먼트의 크기를 확인할 수 있습니다



SELECT segment_name, sum(bytes)/1024 SEGMENT_SZ_KB, count(*) EXTENTS
FROM dba_undo_extents
GROUP BY segment_name
ORDER BY 1 ;  -- 언두-세그먼트별로 정렬된 크기를 알 수 있습니다(조금 더 유용)















-------------------------------------------------------------------------------------------------

<테이블스페이스 (Table Space)>


## 테이블스페이스 관리
	# 테이블스페이스 (Table Space)
			# 물리적인 하나 이상의 데이터파일들이 매핑된 논리적인 저장공간입니다 
			
			# 다른 DB는 하나의 DATABASE 당 1개의 Data file을 보유하지만 ORACLE은 TABLE SPACE를 활용해 여러 Data files를 저장할 수 있습니다
		
			# SYSTEM 과 SYSAUX Table Space
				# 데이터베이스가 생성되면 자동으로 구성되는 테이블스페이스입니다

				# SYSTEM Table Space
					# 데이터 딕셔너리(Data Dictionary) 테이블의 세그먼트가 저장돼있는 공간입니다	

				# SYSAUX Table Space
					# 샘플 스키마가 저장돼있는 공간입니다
		


			# 테이블스페이스 유형1 (저장되는 내용에 따라)
				# Perament Type (영구유형)
					# 테이블 데이터가 저장되있는 테이블스페이스 타입입니다	
				
				# Undo Type (언두유형)
					# DDL, DML 명령문을 이용해 수정하기 전 데이터들이 저장됩니다
				
				# Temporary Type (임시유형)
					# SQL문 처리시 PGA의 메모리공간이 작을 때 이곳에 임시적으로 저장됩니다
					# 운영체제의 페이지파일, 스왑메모리와 비슷합니다
					# 임시파일(TEMP FILE)로 구성됩니다 <===> 데이터파일(DATA FILE)과 다릅니다

				


			# 테이블스페이스 유형2 (파일의 특성에 따라)
				# BIG FILE Table Space
					# 큰 용량의 하나의 데이터파일/임시파일로 구성되는 테이블스페이스입니다
					# 파일추가가 불가능합니다
					# 8192 블록사이즈에서 32Tb - 1Mb 입니다

				# SMALL FILE Table Space
					# 작은 용량의 여러개의 데이터파일/임시파일로 구성되는 테이블스페이스입니다
					# 8192 블록사이즈에서 32Gb - 1Mb 입니다



			# 여러가지 뷰(View)들
				# DBA_TABLESPACES, V$TABLESPACE : 테이블스페이스 정보를 제공합니다
				# DBA_DATA_FILES, V$DATAFILE : 데이터파일 정보를 제공합니다
				# DBA_TEMP_FILES, V$TEMPFILE : 임시파일 정보를 제공합니다 
				# V$FILESTAT : 데이터파일의 I/O 양에 관한 정보를 제공합니다


			# UNDO, TEMPORARY 테이블스페이스는 EXTENT 단위로 데이터를 생성합니다







CREATE TABLESPACE udata1
DATAFILE 'C:\app\buk213\oradata\orcl\udata1a.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 10M MAXSIZE UNLIMITED
UNIFORM SIZE 1M ;   -- SMALL FILE 영구-테이블스페이스를 생성합니다
-- 데이터파일 설정하고, 
-- 데이터파일의 크기 설정하고, 
-- 자동용량확장기능 ON, 데이터파일이 10M 단위로 커지고 최대 무한대까지 커질 수 있습니다
-- EXTENT 크기를 무조건 1M로 합니다



CREATE UNDO TABLESPACE undo1
DATAFILE 'C:\app\buk213\oradata\orcl\undo1a.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 10M MAXSIZE 2048M ; -- SMALL FILE 언두-테이블스페이스를 생성합니다
-- 언두-테이블스페이스는 UNIFORM SIZE를 설정할 수 없습니다




CREATE TEMPORARY TABLESPACE temp1
TEMPFILE 'C:\app\buk213\oradata\orcl\temp1a.dbf'
SIZE 13304K
AUTOEXTEND ON NEXT 8M MAXSIZE UNLIMITED
UNIFORM SIZE 4M ; -- SMALL FILE 임시-테이블스페이스를 생성합니다 
-- 임시-테이블스페이스는 UNIFORM SIZE를 반드시 써야합니다



CREATE BIGFILE TABLESPACE bigudata1
DATAFILE 'C:\app\buk213\oradata\orcl\bigudata1a.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 10M MAXSIZE UNLIMITED
UNIFORM SIZE 1M ;    -- BIG FILE 영구-테이블스페이스를 생성합니다
-- BIGFILE UNDO, BIGFILE TEMPORARY를 이용해 언두, 임시 테이블스페이스를 생성할 수 있습니다




ALTER TABLESPACE udata1
ADD DATAFILE 'C:\app\buk213\oradata\orcl\udata1b.dbf'
SIZE 31736K
AUTOEXTEND ON NEXT 30M MAXSIZE UNLIMITED ;    -- 데이터파일을 추가합니다 (SMALL FILE 테이블스페이스만 가능합니다)




ALTER TABLESPACE undo1
ADD DATAFILE 'C:\app\buk213\oradata\orcl\undo1b.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 10M MAXSIZE UNLIMITED ;  -- 데이터파일을 추가합니다2




ALTER DATABASE
DATAFILE 'C:\app\buk213\oradata\orcl\udata1a.dbf'
RESIZE 31736K ;   -- 데이터파일의 크기를 변경합니다 (BIG, SMALL FILE 모두 동일합니다)





CREATE TABLESPACE udata2
DATAFILE
'C:\app\buk213\oradata\orcl\udata2a.dbf'
SIZE 11256 K
AUTOEXTEND ON NEXT 10M MAXSIZE UNLIMITED,
'C:\app\buk213\oradata\orcl\udata2b.dbf'
SIZE 11256 K
AUTOEXTEND ON NEXT 10M MAXSIZE 2G
UNIFORM SIZE 1M
EXTENT MANAGEMENT LOCAL
SEGMENT SPACE MANAGEMENT AUTO
LOGGING
BLOCKSIZE 8192;  -- 여러가지 옵션이 추가된 테이블스페이스의 생성구문입니다 (실제는 전혀 안쓴다고 합니다)
-- EXTENT MANAGEMENT LOCAL : EXTENT를 관리하는 방식으로 LOCAL 방식과 DICTIONARY 방식이 있습니다. DICTIONARY 방식은 옛날방식이고 성능도 안좋다고 합니다
-- SEGMENT SPACE MANAGEMENT AUTO : INSERT 명령어 실행 시 빈공간을 가진 블록 정보를 확인하는 방법을 AUTO로 설정합니다.
-- LOGGING : 해당 테이블스페이스의 모든 작업의 리두 로그정보를 기록합니다. NOLOGGING으로 설정해도 리두 로그정보가 저장됩니다. 다만 테이블/인덱스 생성작업할 때나, Direct-Path Inserting 작업을 할 때 로그정보가 생성되지 않습니다
-- BLOCKSIZE : 데이터파일의 블록크기를 지정합니다 (보통 8192kb)





ALTER DATABASE
DATAFILE 'C:\app\buk213\oradata\orcl\udata1a.dbf'
AUTOEXTEND ON NEXT 20M ;   -- 테이블스페이스 설정을 변경합니다





ALTER TABLESPACE udata1
OFFLINE NORMAL, TEMPORARY, IMMEDIATE ; -- 테이블스페이스를 사용하지 않는 OFFLINE으로 변경합니다
-- CONTROL FILE, ONLINE REDO LOG FILE은 OFFLINE이 되지 않습니다
-- 사용 중인 UNDO 테이블스페이스, 모든 TEMPORARY 테이블스페이스는 OFFLINE되지 않습니다
-- IMMEDIATE로 종료한 테이블스페이스는 ONLINE 시키면서 데이터파일을 복구해야합니다
-- IMMEDIATE로 종료시키려면 데이터베이스가 아카이브(ARCHIVE) 모드로 되있어야만 합니다





ALTER TABLESPACE udata1 RENAME TO udata01 ;   -- 테이블스페이스 이름을 변경합니다



ALTER TABLESPACE udata1 READ ONLY ;  -- 테이블스페이스 상태를 READ ONLY로 변경합니다
ALTER TABLESPACE udata1 READ WRITE ;



CREATE TABLE hr.test1
(id NUMBER(2)
,name VARCHAR2(30)
) TABLESPACE udata1 ;    -- TABLESAPCE udata1에 테이블을 생성합니다





DROP TABLESPACE TS_테파 INCLUDING CONTENTS ;   -- 테이블스페이스 +  저장된 세그먼트 모두 지웁니다. 실제 파일은 삭제되지 않습니다

DROP TABLESPACE TS_테파 INCLUDING CONTENTS AND DATAFILES; -- 실제파일까지 삭제합니다








			# Oracle-Managed Files 기능 (OMF)
				# 데이터파일, 온라인 리두 로그파일, 컨트롤 파일들의 생성 경로 및 파일 이름을 오라클 서버가 자동으로 지정하게 하는 기능입니다.

				# 파라미터들
					# DB_CREATE_FILE_DEST
						# 이 파라미터만 입력하면 데이터파일, 임시파일, 온라인 리두 로그파일, 컨트롤 파일 모두 이 경로에 생성됩니다

					# DB_CREATE_ONLINE_LOG_DEST_1,2,3,4,5
						# 이 파라미터만 입력하면 데이터파일, 임시파일을 만들 때 에러가 납니다


				# 간편하게 테이블스페이스를 만들 수 있습니다 
					# SHOW PARAMETER DB_CREATE; -- 현재 설정된 파라미터를 볼 수 있습니다
					# cmd ==> mkdir c:\app\buk213\oradata1



ALTER SYSTEM SET DB_CREATE_FILE_DEST = 'c:\app\buk213\oradata1' SCOPE=both;  -- 파라미터의 경로를 설정합니다



CREATE TABLESPACE udata7 ; -- 이처럼 간단하게 테이블스페이스를 생성할 수 있습니다



CREATE TABLESPACE udata8
DATAFILE
SIZE 21496 K
AUTOEXTEND ON NEXT 10M
UNIFORM SIZE 2M ;   -- DATAFILE에 명시를 안하면 알아서 OMF가 작동합니다



CREATE TABLESPACE udata9
UNIFORM SIZE 2M ;  -- UNIFORM SIZE 옵션만 써서 간단하게 만들 수 있습니다


SELECT tablespace_name, file_id, relative_fno, file_name,
status, autoextensible, maxbytes, maxblocks, increment_by
FROM dba_data_files
WHERE tablespace_name IN ('UDATA7','UDATA8','UDATA9')
ORDER BY 2, 3; -- 생성한 테이블스페이스를 볼 수 있습니다














--------------------------------------------------------------------------------------------------

<테이블 재구성 및 인덱스 공간관리>

## 테이블을 다른 테이블스페이스로 옮기면 기존의 rowid(INDEX) 값을 업데이트 해줘야 합니다
	# V$SQLAREA 뷰 : SGA의 Shared Pool에 캐싱된 Library Cache 내용과 관련된 통계정보를 제공합니다



SELECT EXECUTIONS, LOADS, UPPER(sql_text)
FROM v$sqlarea
WHERE UPPER(sql_text) LIKE 'INSERT%'
AND UPPER(sql_text) NOT LIKE '%$%'
AND UPPER(sql_text) NOT LIKE '%MGMT%'
AND UPPER(sql_text) NOT LIKE '%SMON_SCN_TIME%'
AND UPPER(sql_text) NOT LIKE '%ALERT_QT%'
ORDER BY 2 ;   -- 지금까지 입력된 SQL문들을 확인할 수 있습니다. 그 중 특정 구문만 출력합니다
-- 출력값 중 LOADS : Hard Parse 횟수
-- Executions - LOADS : Soft Parse 횟수







ALTER TABLE hr.employees
MOVE; -- 기존 테이블스페이스에서 SEGMENT 공간을 새로 할당받아서 이동합니다

SELECT index_name, status
FROM dba_indexes
WHERE table_name = 'EMPLOYEES' and OWNER='HR' -- 만약 hr.employees 테이블을 옮기면 해당 관련된 인덱스 상태정보 값이 UNUSABLE가 됩니다

ALTER INDEX index_name REBUILD; -- 인덱스 정보를 UNUSABLE ==> VALID로 업데이트합니다


		# 이 처럼 테이블을 다른 테이블스페이스로 이동하면 테이블 정보를 업데이트해줘야 합니다
			# 인덱스 값이 VALID ==> UNUSABLE로 변합니다
			# 따라서 이 값을 다시 VALID 해줘야 합니다

			# exec dbms_stats.gather_table_stats('HR','EMPLOYEES', cascade=>true) 
				# 서버의 통계정보는 위처럼 수동으로 업데이트 해줘야 합니다 
















--------------------------------------------------------------------------------------------------

<컨트롤 파일 관리>


## 컨트롤 파일 관리 (Control file management)
	# 컨트롤 파일(Control file) :  데이터베이스에 대한 제어 + 구조 정보를 저장하고 있습니다
	
	# 이 파일이 손상되면 데이터 파일을 열 수 없습니다
		# 데이터 보존을 위해 같은 파일을 2개 이상 구성해서 미러링시키는 방법이 있습니다
		# 최대 8개까지 파일을 다중화시킬 수 있습니다
		# 작업은 항상 NOMOUNT 상태에서 합니다

	# RMAN 명령어를 사용해 컨트롤파일을 다중화 해보기
		# cmd ==> rman target /
		# RMAN> startup nomount; (컨트롤파일은 항상 NOMOUNT 상태에서 합니다)
		# RMAN> RESTORE CONTROLFILE FROM 'c:\app\buk213\oradata\orcl\control01.ctl' ; 
		# RMAN> HOST 'dir c:\app\buk213\oradata\orcl\CONTROL*';
		# RMAN> ALTER DATABASE MOUNT; 
		# RMAN> ALTER DATABASE OPEN;
		# SQL> SHOW parameter control_files; (제대로 설정됐는지 확인해봅니다)





SELECT name FROM v$controlfile ;  -- 현재 사용중인 컨트롤파일 정보를 확인합니다



ALTER SYSTEM SET control_files =
'c:\app\buk213\oradata\orcl\control01.ctl' ,
'c:\app\buk213\oradata\orcl\control02.ctl' ,
'c:\app\buk213\oradata\orcl\control03.ctl' SCOPE=SPFILE ;   -- static parameter이므로 SCOPE=SPFILE을 입력해줘야 합니다


SHUTDOWN IMMEDIATE  -- 서버를 중지합니다 (stataic parameter이므로 바로 적용 x)


HOST copy c:\app\buk213\oradata\orcl\control01.ctl c:\app\buk213\oradata\orcl\control03.ctl -- 기존 파일을 복사해서 새로운 컨트롤파일을 만듭니다


















---------------------------------------------------------------------------------------------------

<온라인 리두 로그파일 관리>


## 온라인 리두 로그파일 (Online Redo Log-File)
		# CURRENT : 현재 Log-Writer가 작업 중인 로그파일을 CURRENT 로그파일이라고 합니다 
		
		# INACTIVE : 
		
		# ACTIVE : 로그스위치가 넘어간 다음 직전에 있는 파일들은 ACTIVE 상태가 됩니다 스위치가 넘어간 직후 CKPT 프로세스가 작동하면서 DBWn 프로세스가 작동하고 Dirty-Buffer도 저장하는 동안을 말합니다. 전부 완료하면 INACTIVE 상태로 변경됩니다



	# 보안을 강화하기 위해 같은 로그파일을 여러 파일에 저장해놓는 로그그룹 형식을 사용합니다
		# 그룹화된 같은 내용의 파일들은 다른 디스크에 구성해야합니다	

	# 리두 로그파일이 손상되면 어떠한 DB도 복구할 수 없습니다





	# 온라인 리두 로그파일 관리
		# 새로운 멤버 리두 로그파일을 만들면 처음 상태는 INVALID 상태정보로 표시됩니다	
			
			# 로그가 쓰이기 시작하면 INVALID가 사라집니다
			
			# Sequence# 순서대로 로그스위치는 기록합니다. (GROUP# 순서대로가 아닙니다)
			
	
			# 로그 그룹 파일 삭제
				# 멤버파일이 2개 이상일 때만 일부 멤버파일 삭제가 가능합니다
					# UNUSED, INACTIVE, ACTIVE 상태의 파일은 삭제할 수 있습니다
				# 그룹 삭제도 정보만 삭제되고 실제 파일은 삭제되지 않습니다
			
			# 실제 현장에는 90% 이상이 스토리지 미러링이 되어있으므로 굳이 그룹파일에 여러 멤버파일을 만들 필요가 없습니다.
				# 그룹 당 멤버파일 1개만 설정합니다







SELECT group#, sequence#, bytes, members, status, first_change# FROM v$log ;  -- 리두 로그그룹의 정보를 확인합니다
-- bytes : 512k
-- members : 멤버파일의 갯수
-- status : 로그그룹의 상태
-- first_change# : 로그마다 처음 기록된 SCN값




SELECT group#, status, type, member FROM v$logfile ORDER BY 1,4 ;   -- 멤버 파일의 경로를 표시해줍니다
-- status는 원래 빈칸이 나와야합니다(정상이라는 뜻)



ALTER SYSTEM SWITCH LOGFILE;   -- 강제로 로그스위치를 바꿉니다
ALTER SYSTEM CHECKPOINT;       -- 체크포인트 프로세스를 불러옵니다 (ACTIVE => INACTIVE) (둘은 세트입니다)




SELECT A.GROUP#, A.SEQUENCE#, A.ARCHIVED
, A.STATUS AS GROUP_STATUS, A.FIRST_CHANGE#
, B.MEMBER, B.STATUS AS FILE_STATUS
FROM V$LOG A INNER JOIN V$LOGFILE B ON (A.GROUP# = B.GROUP#)
ORDER BY 1, 6 ; -- 멤버 파일 경로와 여러가지 정보를 한꺼번에 보는 스크립트 





ALTER DATABASE ADD LOGFILE MEMBER
'c:\app\buk213\oradata\orcl\redo01b.rdo' TO GROUP 1 ,
'c:\app\buk213\oradata\orcl\redo02b.rdo' TO GROUP 2 ,
'c:\app\buk213\oradata\orcl\redo03b.rdo' TO GROUP 3 ; -- 3개의 로그그룹에 멤버 로그파일을 하나씩 추가하는 구문입니다
-- 이렇게 생성된 파일은 상태정보가 INVALID 이므로 바로 ALTER SYSTEM SWITCH LOGFILE, ALTER SYSTEM CHECKPOINT를 사용해 INVALID를 없애줍니다




ALTER DATABASE ADD LOGFILE GROUP 4
('c:\app\buk213\oradata\orcl\redo04a.rdo'
,'c:\app\buk213\oradata\orcl\redo04b.rdo') SIZE 50M ;  -- 새로운 로그파일을 하나 만듭니다, Sequence#가 0이 되어 로그스위치가 다음에 바로 사용할 수 있습니다.(로그스위치는 낮은 Sequence#로 갑니다)




ALTER DATABASE DROP LOGFILE MEMBER
'c:\app\buk213\oradata\orcl\redo04b.rdo' ;   -- 해당 멤버파일 정보를 삭제합니다 (파일정보만 삭제하고 실제 파일은 삭제되지 않습니다)





ALTER DATABASE DROP LOGFILE GROUP 4 ;   -- GROUP 자체를 삭제합니다 (CURRENT, ACTIVE는 삭제할 수 없습니다) (역시 정보만 삭제되고 실제 파일은 삭제되지 않습니다)










--------------------------------------------------------------------------------------------------


	$$ sqlplus ==> host 명령어
		$ host dir
		$ host cls
		$ host vim ... 같이 cmd 명령어를 사용할 수 있습니다
		



<초기화 파라미터 파일>


## 초기화 파라미터 파일
	# ORACLE_HOME/dbs/init.ora 
	# ORACLE_HOME/database/SPFILEORCL.ORA (WINDOWS이므로 전부 대문자로 변경됩니다)
	# ORACLE_HOME/database/PWDorcl.ora : 패스워드 파일


	# 'SPFILE' 과 'PFILE'
		# SPFILE(Server Parameter File)
			# 특정 인스턴스에 대한 디폴트 SPFILE은 위에있는 SPFILEORCL.ORA 입니다	
			# 바이너리 형식입니다 (텍스트편집기 사용하지 말아야합니다)
			# 따라서 오직 SQL명령어로만 수정해야 합니다


		# PFILE(Text Initialization Parameter File)
			# 특정 인스턴스에 대한 디폴트 PFILE은 위에있는 init.ora입니다
			# 텍스트 형식입니다.
			# SQL 명령어 + 텍스트 편집기로 변경할 수 있습니다. 




SHOW PARAMETER SPFILE; -- SPFILE의 경로를 출력합니다
SHOW PARAMETER PFILE;





	# 서버 시작 메커니즘
		# STARTUP
			# SPFILEORCL.ORA ==> SPFILE.ORA ==> INITorcl.ORA
			# 위 파일순으로 검색해서 먼저나온 파일을 기준으로 파라미터값을 읽습니다


		# STARTUP PFILE {...}
			# CREATE PFILE='C:\app\buk213\initpfile.ora.bkg' FROM SPFILE; 
				# SHUTDOWN 상태에서는 디폴트위치에 있는 SPFILE로부터 PFILE을 생성합니다
				# NOMOUNT,MOUNT,OPEN 상태에서는 현재 기동중인 인스턴스 SPFILE로부터 PFILE을 생성합니다

			# STARTUP PFILE='C:\app\buk213\initpfile.ora.bkg' 
				# 해당 PFILE로 서버를 시작할 수 있습니다


			# CREATE SPFILE='c:\app\buk213\MYSPFILE.ORA' FROM PFILE='c:\app\buk213\initorcl.ora.bkg'; 
				# SPFILE을 PFILE로부터 복구할 수 있습니다


			# sqlplus ==> host vim c:\app\buk213\myinit.ora
				# SPFILE='c:\app\buk213\MYSPFILE.ORA' 를 vim 편집기를 통해 입력하고
				# STARTUP PFILE='c:\app\buk213\myinit.ora' 를 입력하면 해당 myspfile.ora 파일을 불러옵니다








	# Static Parameter 와 Dynamic Parameter
		# Static Parameter
			# 시스템이 동작 중에는 변경할 수 없는 파라미터입니다. 
			# 반드시 서비스를 재시작해야합니다
			# init.ora 또는 SPFILE을 수정해 변경할 수 있습니다
			# 약 110개 정도의 파라미터
	



ALTER SYSTEM SET 파라미터=값 SCOPE=SPFILE    -- Static Parameter 변경 방법 (SPFILE)          반드시 SCOPE=SPFILE이어야 합니다. (현재 시스템에는 설정이 불가능하므로)





		# Dynamic Parameter
			# 시스템이 동작하는 중에 파라미터를 변경할 수 있습니다
			# Dynamic은 DEFFERED 옵션을 줄 수 있습니다 (거의 안쓰임) 
				# 기존 세션들은 변경사항이 적용되지 않는다는 뜻입니다


			# 약 234개 정도의 파라미터 값을 가집니다
		
	



ALTER SYSTEM SET 파라미터=값 SCOPE=BOTH    -- Dynamic Parameter 변경 방법 (BOTH)

ALTER SESSION {...} -- 현재 세션에만 적용하고 싶은 경우 사용합니다





$ Various Parameters
		
DB_NAME : Database 이름을 설정하는 파라미터
DB_FILE_MULTIBLOCK_READ_COUNT : Full Table Scan시 한번에 읽어드릴 수 있는 Block의 크기
DB_BLOCK_SIZE : DB Block의 최소 크기를 결정합니다
CONTROL_FILES
INSTANCE_NAME : 
SERVICE_NAMES
DB_FILES
PROCEESSES




$ SGA 구성요소를 설정하는 파라미터

LOG_BUFFER
SHARED_POOL_SIZE
DB_CACHE_SIZE
DB_KEEP_CACHE_SIZE
DB_RECYCLE_CACHE_SIZE
DB_nK_CACHE_SIZE
LARGE_POOL_SIZE
JAVA_POOL_SIZE
STREAMS_POOL_SIZE




















--------------------------------------------------------------------------------------------------

<데이터베이스 인스턴스 시작 : 개요>


## SHUTDOWN -> NOMOUNT -> MOUNT -> OPEN
	# SHUTDOWN : 인스턴스를 중지합니다

	# NOMOUNT : 인스턴스 시작
		# SGA 구성이 완료됩니다
		# 백그라운드 프로세스들이 기동됩니다
		# ALERT-LOG 파일 기록이 시작됩니다
		# TRACE 파일이 생성되어 실행됩니다

		# NOMOUNT 상태에서 데이터베이스를 생성합니다
		# 컨트롤파일을 수정할 수 있습니다


	# MOUNT : 컨트롤파일이 열림
		# 컨트롤파일이 정상적으로 액세스된 상태입니다

		# 데이터파일 복구 및 수정할 때 사용합니다


	# OPEN : 모든 데이터파일이 열림
		# 모든 온라인 데이터파일과 리두로그파일들이 정상적으로 액세스 가능한 상태입니다.
		


	# CMD 명령어들
		# 원격으로 접속하는법
			# sqlplus system/oracle4U@210.123.41.178:1521/orcl.example11.com
				# system 계정으로 해당 IP에 orcl 데이터베이스로 접근을 시도합니다
		
		# 리스너 상태 확인
			# cmd -> lsnrctl status LISTENER
			
		

		# SHUTDOWN
			# NORMAL : 현재 접속한 모든 세션들이 나갈때까지 기다린 후 종료합니다
			# TRANSACTIONAL : 현재 세션들의 트랜잭션이 끝나면 자동으로 종료합니다
			# IMMEDIATE : 세션과 상관없이 즉시 종료합니다. 진행 중인 세션은 전부 롤백됩니다
			# ABORT : 서버를 비정상적으로 종료시킬 때 사용합니다
				# 데이터파일이나 컨트롤파일이 손상되면 정상종료가 안되는데 이 때 강제종료하기 위해 사용합니다
				# 시작되면서 자동으로 인스턴스 복구를 하고 로그스위치를 한 번 합니다



		# STARTUP
			# MOUNT:
			# NOMOUNT:
			# FORCE: SHUTDOWN ABORT + STARTUP과 같은 명령어입니다



	# 관리자가 조회할 수 있는 성능 뷰(V$)들
		# v$datafile
		# v$tempfile
		# v$logfile
		# v$controlfile
		# v$log
		# v$archived_log
		# v$database
		# v$instance





	# 인스턴스 복구가 진행되는 단계
		# MOUNT -> ROLLFORWARD -> OPEN -> ROLLBACK
		
		# ROLLFOWARD : SMON 프로세스가 실행되어 모든 버퍼캐시 데이터를 데이터파일에 저장하는 단계입니다 
		# ROLLBACK : SMON 프로세스가 COMMIT 되지 않은 데이터를 읽어서 ROLLBACK 시킵니다












STARTUP NOMOUNT -- NOMOUNT 상태로 데이터베이스를 기동하는 명령어



SELECT status FROM v$instance  -- 서버의 상태를 나타내는 컬럼인듯..



ALTER DATABASE MOUNT; -- NOMOUNT --> MOUNT 상태로 변경하는 명령어
ALTER DATABASE OPEN; -- MOUNT --> OPEN 상태로 변경하는 명령어
ALTER DATABASE OPEN READ ONLY; -- 읽기전용으로 데이터베이스를 여는 명령어
















--------------------------------------------------------------------------------------------------

<데이터베이스 저장영역 및 데이터 구조>


## 데이터베이스 저장영역 구조 (Storage Architecture)
	# 오라클 데이터베이스
		# Control files 
		# Data files
		# Online redo log files


	# Parameter file : 서버의 기동을 위한 필수 파일입니다. 시스템 데이터 등등...
	# Password file : sysdba를 원격으로 접속할 때 사용하는 파일입니다


	# Backup files 
	# Archived redo log files 
	# Alert log and trace files : 서버 운영 중 기록을 남기는 파일입니다






## 논리적 및 물리적 데이터베이스 구조 (Logical and Physical Database Structure)
	# Physical Structure
		# Data files 
		# OS Block (File system, ASM, Exadata, NAS, NFS...)



	# Logical Structure
		# 데이터베이스
		
		# 테이블스페이스(Table Space)

		# 스키마 (Scheme)
			# 같은 내용이나 분야를 한 저장영역으로 묶은 것을 스키마라고 합니다 ex) hr.employees


		
		# 세그먼트 (Segment) : Extent의 모음입니다. 테이블이나 인덱스의 최소단위입니다 
			# 세그먼트를 볼 수 있는 뷰(View)
				# DBA_SEGMENTS 

SELECT * FROM DBA_SEGMENTS;



		# Extent : 데이터블록 모음입니다. 세그먼트가 꽉 찼을 경우 공간을 확장하기 위해 사용합니다
			# Extent를 볼 수 있는 뷰(View)
				# DBA_EXTENTS

SELECT * FROM DBA_EXTENTS;



		# 데이터블록 : Oracle에서 가장 작은 데이터들의 단위입니다 





















--------------------------------------------------------------------------------------------------

	$$ Database Buffer Cache를 구성하는 버퍼의 상태
		$ PINNED : 특정 프로세스가 해당 버퍼를 사용중일 때
		$ DIRTY : DDL,DML문장에 의해 버퍼가 변경된 경우입니다
		$ CLEAN : SELECT문에 의해 버퍼가 변경되지 않을 경우입니다
		$ FREE/UNUSED : 최초의 메모리를 할당받을 때 사용합니다

	$$ Checkpoint
		$ Dirty buffer가 발생된 순서대로 메모리 주소를 기록한 공간입니다


	$ Windows는 oracle.exe로 Server Process와 Backgroun Process가 동시에 실행됩니다.
	$ Linux는 두 서비스가 각각 따로 실행됩니다



<프로세스 구조>

## Client <===> Server <===> Daemon(Service)
	
	# Client	
		# 'User Process' : 리스너에게 접속요청을 합니다 -> 서버프로세스에 연결됩니다



	# Server
		# 'Server Process' : 리스너로부터 요청은 받습니다 -> 백그라운드 프로세스에 해당 요청을 다시 요청합니다


		# 'Background Process' : 오라클 DB의 커널입니다. oracle.exe 프로그램 안에 스레드 형태로 구현됩니다

			# 필수 프로세스
				# DBWn (DB 기록자 프로세스)
					# DB Buffer Cache에 저장된 데이터를 디스크에 기록합니다
						# DB Buffer Cache에 Dirty buffer만 디스크에 기록합니다
					
					# Checkpoint queue를 확인하고 전진시킵니다

					# 최대 DBWn수는 36개입니다
						# CPU 갯수에 많이 의존합니다



				# CKPT (체크포인트 프로세스)
					# 특정 시점의 RBA, SCN 값을 컨트롤파일과 각 데이터 파일 헤더에 기록하는 프로세스입니다
						# RBA : Redo Byte Address 리두 로그 버퍼에 있는 주소 정보입니다
						# SCN : System Change Number로 커밋할 때마다 1씩 증가합니다

					# Full Complete Checkpoint
						# SCN값을 컨트롤 파일 + 모든 데이터파일 헤더에 기록합니다	
						
						# 이 SCN 이하의 번호까지는 맞출 필요없다는걸 알려주는 역할입니다
							# 정상적으로 데이터베이스를 종료할 때
							# 로그스위치가 발생되었을 때
							# 관리자가 ALTER SYSTEM CHECKPOINT; 구문을 실행했을 때

SELECT file#, checkpoint_change# FROM v$datafile_header;

					# Incremental Checkpoint
						# RBA값을 컨트롤 파일에만 기록합니다
						# 비정상적으로 시스템이 종료되면 RBA값을 읽고 그 다음부터 로그를 실행해서 Instance 복구시간을 단축시킨다 




				# LGWR (로그 기록자 프로세스)
					# 리두 로그 버퍼 항목을 디스크의 온라인 리두 로그 파일에 기록합니다
						# 사용자가 트랜잭션을 commit 할 때
						# 리두 로그 버퍼가 1/3이상 찼을 때
						# 3초마다

						


				# SMON (시스템 모니터 프로세스)
					# 인스턴스 복구를 수행합니다 (시스템이 비정상적 종료된 경우)
					# 정상 운영중인 경우 SMON은 항시 대기하고 있습니다





				# PMON (프로세스 모니터 프로세스)
					# 사용자 프로세스가 비정상적으로 접속이 끊어졌을 때 ROLLBACK, DB Buffer Cache를 정리하고 리스소를 해제하는 작업을 수행합니다
					# 시스템 리소스를 많이 잡아먹을 수 있으므로 소스코딩할 때 항상 주의해야 합니다
					# UNDO 데이터를 사용합니다



				# RECO (복구자 프로세스)
					# 분산 데이터베이스를 구성할 때 사용합니다
					# 트랜잭션이 비정상적이라고 판단될 경우 해당 트랜잭션을 복구하는 프로세스입니다



					
SELECT group#, status, sequence# FROM v$log;






			# 선택 프로세스
				# ARCn (아카이버 프로세스)
					# 온라인 로그파일 -> 아카이브된 리두 로그파일로 변경하면 효율적으로 백업할 수 있다 (시스템 전원 ON 상태로 백업할 수 있습니다)


					# LSN이 증가함에 따라 커지는 데이터들을 복구를 위해 Archive에 따로 저장해놓습니다
						# LSN (Redo Log Sequence Number)
							# 로그스위치가 발생할 때마다 1씩 증가하는 값입니다


				# ASMB
				# RBAL
				# ... 





	# Daemon, Service
		# 'Networking Listener' : Client와 Server 사이에서 접속요청을 확인하는 프로세스입니다
		# 'Grid Infrastructure Daemon'(+ Clusterware, ASM): DB구축할 때 Cluster화 시키기 위해 사용되는 프로세스입니다. ASM(오라클사가 만든 Filesystem 형태인듯..) 기능도 포함됩니다.




















--------------------------------------------------------------------------------------------------

## PGA (Process Global Area)
	# 각 서버 프로세스들이 개별적으로 사용하는 메모리공간입니다
	# 모든 SQL문을 임시적으로 저장했다가 'Shared Pool', 'Data Buffer Cache', 'Redo Log Data' 영역 중 알맞은 곳에 저장합니다.
	

	# 'Stack Space'
		# 

	# 'UGA (User Global Area)'
		# Cursor State :
		# User Session Data :
		# SQL Working Area :










--------------------------------------------------------------------------------------------------

	$$ SQL 문장의 실행 원리
		$ SELECT 문장 : parsing -> executing -> fetching
			$ parsing: 데이터를 원하는 형태로 재가공하는 과정을 말합니다
			$ executing: parsing 후 블록의 주소를 Hash 테이블에서 찾는 과정입니다.
			$ fetching: executing 후 블록에서 원하는 데이터를 골라내어 인출하는 과정입니다. 


		$ DML,DDL 문장 : parsing -> executing


	$$ LRU (Least Recently Used) 알고리즘
		$ 메모리 공간이 꽉차면 가장 오래전에 사용된 데이터를 삭제하고 새로운 데이터를 넣는 알고리즘입니다






## SGA (System Global Area)
	# 오라클 데이터베이스 Instance 별로 1개 씩 생성되는 메모리 영역으로 공유 메모리 구조입니다.

	# 'Shared Pool'
		# LRU 알고리즘으로 관리됩니다
		# DB 서버에 저장된 컴파일 코드, 시스템 데이터 등등을 저장해 처리속도를 높일 수 있습니다
		# 모든 유저가 동시에 공유합니다


		# Library Cache
			# 이미 수행되었던 SQL 문장이나 parse code, 실행 계획등이 저장되어 있는 공간입니다
			# Soft Parse할 때 사용되는 공간입니다
		
		# Dictionary Cache
			# 구문분석이나 실행계획을 세울 때 사용되는 주요 dictionary들이 저장되어 있습니다
			# LRU 알고리즘으로 관리됩니다
			

		# 작동 메카니즘
			#Hard Parsing된 컴파일 코드를 ASCII -> SUM -> HASH화 시킨 후 Shared Pool에 저장시켜 놓습니다
			# Soft Parsing이라고 합니다
			# 한번 Parsing해놓으면 다음부터 같은 SQL문을 실행할 때 Shared Pool을 검사해 실행하므로 더 빠르게 실행할 수 있습니다




	# 'Database Buffer Cache'
		# LRU 알고리즘으로 관리됩니다
		# 제일 큰 메모리영역입니다.
		# 모든 유저가 동시에 공유합니다
		
		# 테이블의 데이터들이 사용자들로부터 불려질 때 저장되는 영역입니다.
			# 다음부터는 더 빠르게 ACCESS 할 수 있습니다.

		# Executing
			# Parsing된 데이터를 실행하는 과정입니다.
			# DML문은 데이터를 변경하므로 변경 전 데이터를 Redo Log Buffer에 저장합니다
			


	# KEEP Buffer Pool : LRU 알고리즘에 의해 자주쓰는 버퍼가 지워지지 않도록 KEEP으로 옮깁니다
	# RECYCLE Buffer Pool : 소수인원만 쓰는 Buffer들은 RECYCLE Buffer로 옮겨서 메인버퍼의 부하를 줄입니다
	# nK Buffer Cache : 8k, 4k 등 다른 데이터블록의 데이터를 읽을 경우 사용합니다 






	# 'Redo Log Buffer'
		# DML, DDL 문장을 처리 시에 변경 전 데이터를 저장하는 저장소입니다. (복구정보)





	# 'Large Pool'
		# 필수 구성요소가 아닙니다
		# ORACLE RMAN이라는 백업툴로 백업/복구할 때 Buffer가 생성되는 Pool입니다
		# Large Pool을 구성안하면 모든 Large Pool 데이터는 Shared Pool에 저장됩니다.



	# 'Java Pool'
		# 필수 구성요소가 아닙니다
		# 오라클 DB안에 저장된 자바 Class를 저장할 때 사용하는 Pool입니다
		# JAVA 코드나 JVM 관련 데이터들을 저장합니다









--------------------------------------------------------------------------------------------------

## CMD command 
	# set ORACLE_SID=orcl
	# sqlplus
		# sqlplus 계정/패스워드
		# sqlplus /nolog (로그인없이 실행하겠다)
		# conn / as sysdba (sysdba로 접속하겠다)
		# oradim -STARTUP -SID orcl -SYSPWD oracle4U -STARTTYPE srvc,inst -SPFILE (서비스를 시작하겠다)(srvc->서비스, inst->인스턴스)
		# show user (현재 내 계정)
		# shutdown immediate (서비스 중지)
		# startup (서비스 시작)










--------------------------------------------------------------------------------------------------

## 'RDBMS' and 'Database'
	# RDBMS는 데이터베이스를 관리하는 소프트웨어를 말합니다	
		# ex) MariaDB, Sybase, DB2, MSSQL, MYSQL...


	# Database는 RDBMS를 이용해 구축된 서버를 의미합니다
		# 메모리에서 실행되는 인스턴스 + 스토리지에 구성되는 데이터베이스로 구성됩니다


	# 클라이언트가 서버에 연결하는 방법
		# 원격 연결 : 리스너를 통해 다른 시스템으로부터 연결된 상태를 말합니다
		# 로컬 연결 : 리스너없이 서버가 구성된 시스템에 클라이언트 프로그램을 이용해 연결한 상태를 말합니다 
	
		
		# 환경변수 (Environment Variables)
		    # ORACLE_HOME : RDBMS가 설치된 경로
			# ORACLE_SID : ORACLE 인스턴스 이름
			# PATH : you know what it is 
			# 'WINDOWS'의 경우 HKLM\SOFTWARE\ORACLE\KEY_OraDb11g_home1 폴더 안에 자동으로 설정되어 있습니다.
			# 'LINUX'의 경우 oraenv 스크립트를 이용해 환경변수를 쉽게 설정할 수 있습니다

	# Putty (SSH)
		# 원격으로 데이터베이스 서버에 접속한 후 데이터베이스에는 로컬로 접속할 수 있습니다
		












--------------------------------------------------------------------------------------------------
	$$ 1~6까진 workshop 1 내용이고 7~9는 워크샵 2내용입니다




