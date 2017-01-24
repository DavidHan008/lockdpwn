
<Flashback Database (10g,11g)>


## Flashback Database
	# 불완전 복구를 대체하는 방법을 제공합니다 (RESETLOGS 대신)
	# 데이터베이스 전체를 과거 특정시점으로 회귀시킵니다


	# FLASH RECOVERY AREA 경로에 FLASHBACK-LOG 파일이 생성됩니다
	# SGA Shared Pool 영역에 FLASHBACK-BUFFER 영역이 구성됩니다
	# RECOVER-WRITER(RVWR) 백그라운드 프로세스가 실행됩니다



	# 필수 설정
		# 아카이브 로그모드가 설정되어 있어야합니다
		
		# FLASHBACK RECOVERY AREA가 설정되어 있어야합니다

		# DB_FLASHBACK_RETENTION_TARGET 초기화파라미터 값이 0이 아니어야 합니다
			# 설정 값의 단위 : 분(MINUTE)
			# DEFAULT : 1440 (분)
			# FLASHBACK DATABASE 정보의 저장을 해당 분 동안만 저장합니다





	
show parameter db_recovery -- FRA 구성을 확인합니다

archive log list -- 아카이브로그를 확인합니다

show parameter db_flashback -- 해당 파라미터의 정보를 저장합니다


ALTER SYSTEM SET
db_flashback_retention_target= 2880 SCOPE=BOTH ; -- DB_FLASHBACK_RETENTION_TARGET 파라미터 값을 설정합니다


ALTER DATABASE FLASHBACK ON ; -- FLASHBACK DATABASE 기능을 활성화합니다 (OPEN 상태)(11g)


SELECT flashback_on
FROM v$database ; -- FLASHBACK DATABASE 활성화상태를 확인합니다






CREATE USER fdtestuser1
IDENTIFIED BY oracle4U
DEFAULT TABLESPACE users
QUOTA unlimited ON users ; -- fdtestuser1 계정을 생성합니다


GRANT connect, resource
TO fdtestuser1 ; -- fdtestuser1 계정에 권한을 생성합니다





CREATE TABLE fdtestuser1.emps06_10
(empno number(6)
,ename varchar2(30)
,sal number(8,2)
)
TABLESPACE users ; -- 실습용 테이블을 생성합니다


INSERT INTO fdtestuser1.emps06_10
VALUES (201, 'Hartstein', 13000) ;

INSERT INTO fdtestuser1.emps06_10
VALUES (202, 'Fay', 6000) ;

COMMIT;


SELECT *
FROM fdtestuser1.emps06_10 ; -- 생성된 테이블을 조회합니다









CREATE USER fdtestuser2
IDENTIFIED BY oracle4U
DEFAULT TABLESPACE users
QUOTA unlimited ON users ; -- fdtestuser2 계정을 생성합니다


GRANT connect, resource
TO fdtestuser2 ; -- fdtestuser2 계정에 권한을 생성합니다




CREATE TABLE fdtestuser2.emps06_20
TABLESPACE users
AS
SELECT *
FROM fdtestuser1.emps06_10 ;-- 실습용 테이블을 생성합니다


COMMIT;





CREATE RESTORE POINT b4_drop_schema ; -- 복원지점을 생성합니다

col time format a20
col name format a14
col DDB_INC# format 999999
set pagesize 999
set linesize 200
SELECT NAME,SCN,TIME,STORAGE_SIZE,
GUARANTEE_FLASHBACK_DATABASE,
DATABASE_INCARNATION# AS DB_INC#
FROM v$restore_point ; -- 해당 복원지점 정보를 확인합니다






DROP USER fdtestuser1 cascade ;
TRUNCATE TABLE fdtestuser2.emps06_20 ;  -- 두 계정의 테이블을 DROP, TRUNCATE 합니다




SHUTDOWN IMMEDIATE

STARTUP MOUNT

	

FLASHBACK DATABASE TO RESTORE POINT B4_DROP_SCHEMA ; -- 위에서 확인한 복원지점까지 DB를 복구합니다


















-------------------------------------------------------------------------------------------------

<Flashback Drop (10gNF)>

## Flashback Drop 휴지통
	
	# 삭제된 테이블을 쉽게 복구할 수 있습니다
		# DROP 명령어를 실행하면 테이블의 딕셔너리 정보의 변경작업이 발생합니다
			# 휴지통 정보로 관리됩니다
			# 이 공간은 서버에 의해 공간이 필요한 경우 재사용됩니다
			
			# 인덱스, 제약조건은 복구되지만 FOREIGN KEY는 복구되지 않습니다
			
			# 아래에 SQL문은 FLASHBACK DROP 으로 복구할 수 없습니다

				# DROP TABLE <table_name> PURGE ;
				# DROP TABLESPACE <ts_name> INCLUDING CONTENTS ;
				# DROP USER <user_name> CASCADE ;
				# SYSTEM-테이블스페이스에 구성된 세그먼트는 FLASHBACK DROP 이 안됩니다




	# RECYCLEBIN 초기화 파라미터		
		# DEFAULT 값이 ON 입니다




PURGE RECYCLEBIN;

PURGE USER_RECYCLEBIN ; -- 일반 계정이 휴지통을 삭제할 때 

PURGE TABLESPACE users ;  -- users-테이블스페이스에 세그먼트가 있는 휴지통 정보를 삭제합니다



SELECT *
FROM user_recyclebin ; -- 테이블 인덱스 정보를 확인합니다


SELECT *
FROM dba_recyclebin ; -- 테이블 인덱스 정보를 확인합니다 (sys)






		
	# 실습 1




show parameter recyclebin -- 해당 파라미터를 확인합니다

purge dba_recyclebin ; -- 기존 휴지통의 모든 정보를 삭제합니다 (sys 계정)





CREATE TABLE hr.emps06_01(empno, ename, sal, deptno)
TABLESPACE users
AS
SELECT employee_id, last_name, salary, department_id
FROM hr.employees
WHERE department_id in (10,20,30,50) ; -- 실습용 테이블을 생성합니다



CREATE INDEX hr.pk_emps06_01
ON hr.emps06_01(empno)
TABLESPACE users ; -- 테이블에 인덱스를 추가합니다



SELECT index_name, index_type, status
FROM dba_indexes
WHERE owner='HR'
AND table_name = 'EMPS06_01' ; -- 인덱스 정보를 확인합니다





ALTER TABLE hr.emps06_01
ADD CONSTRAINT pk_emps06_01 PRIMARY KEY (empno)
DEFERRABLE
USING INDEX hr.pk_emps06_01 ;  -- 인덱스를 사용하는 PRIMARY KEY 제약조건을 추가합니다



ALTER TABLE hr.emps06_01
ADD CONSTRAINT fk_emps06_01_dept FOREIGN KEY (deptno)
REFERENCES hr.departments(department_id) ;  -- FOREIGN KEY 제약조건을 추가합니다



SELECT constraint_name, constraint_type
FROM dba_constraints
WHERE owner='HR'
AND table_name='EMPS06_01' ;  -- 설정한 제약조건들을 확인합니다



DROP TABLE hr.emps06_01 ; -- 테이블을 삭제합니다 (제약조건, 인덱스 모두 삭제됩니다)




set pagesize 200
set linesize 200
col object_name format a30
col ORIGINAL_NAME format a12
col OPERATION format a4
col type format a6
col ts_name format a10
col DROPTIME format a19
SELECT OBJECT_NAME,ORIGINAL_NAME,OPERATION,TYPE,TS_NAME
,DROPTIME,DROPSCN,CAN_UNDROP,RELATED,BASE_OBJECT,SPACE
FROM dba_recyclebin
WHERE owner='HR' ; -- DBA_RECYCLEBIN 딕셔너리를 조회합니다 (UNDROP 컬럼 값이 중요합니다








conn hr/oracle4U


SHOW RECYCLEBIN -- UNDROP 할 수 있는 테이블의 정보를 표시합니다 (hr 테이블이므로 hr로 접속해야합니다)


FLASHBACK TABLE hr.emps06_01 TO BEFORE DROP ; -- 해당 테이블을 복구합니다



SELECT *
FROM hr.emps06_01 ; -- 복구된 테이블을 확인합니다



SELECT index_name, index_type, status
FROM user_indexes
WHERE table_name = 'EMPS06_01' ; -- 인덱스 정보를 확인합니다
								-- 인덱스는 휴지통 이름으로 복구됩니다


SELECT constraint_name, constraint_type
FROM user_constraints
WHERE table_name='EMPS06_01' ; -- 제약조건의 정보를 확인합니다
							  -- 제약조건도 휴지통 이름으로 복구됩니다


								

ALTER TABLE hr.emps06_01
RENAME CONSTRAINT "BIN$WZjxIKY4T9KImiCiezKuZA==$0"
TO pk_empno_emps06_01 ; -- 제약조건의 이름을 변경합니다










	# 실습 2
		# 같은 이름인 여러개의 테이블이 있을 경우
			# LAST INPUT FIRST OUTPUT 방식으로 FLASHBACK DROP 이 수행됩니다

			# 먼저 삭제된 테이블을 이름을 바꿔서 복구할 수 있습니다







conn hr/oracle4U

DROP TABLE hr.emps06_01 ; -- 위의 테이블을 삭제합니다

show recyclebin





CREATE TABLE hr.emps06_01(empno, ename, sal, deptno)
TABLESPACE users
AS
SELECT employee_id, last_name, salary, department_id
FROM hr.employees
WHERE department_id = 10 ; -- 삭제된 테이블과 같은 이름의 테이블을 생성합니다





DROP TABLE hr.emps06_01 ; -- 다시 삭제합니다

show recyclebin





FLASHBACK TABLE hr.emps06_01 TO BEFORE DROP ; -- FLASHBACK DROP을 수행합니다

SELECT *
FROM hr.emps06_01 ; -- 복원된 테이블 정보를 확인합니다






FLASHBACK TABLE hr.emps06_01 TO BEFORE DROP
RENAME TO emps06_02 ; -- emps06_02로 이름을 바꿔서 복구합니다 (스키마는 쓰지 않습니다)

SELECT *
FROM hr.emps06_02 ; -- 복원된 테이블 정보를 확인합니다









	# 실습 3
		# 휴지통 이름을 이용한 데이터 조회
		# 복원은 하지 않고 데이터만 알고 싶을 때 사용합니다



DROP TABLE hr.emps06_02 ;


show recyclebin 


SELECT *
FROM "BIN$8BB0vyp3aJbgQKjAbgopkw==$0" ; -- 삭제된 데이터를 복원합니다




























-------------------------------------------------------------------------------------------------

<Flashback Data Archive (Oracle Total Recall, 11gNF)>


## 'Flashback Data Archive' 기능

	# FLASHBACK QUERY (9INF), FLASHBACK VERSIONS QUERY (10GNF)
	- FLASHBACK TRANSACTION QUERY (10GNF), FLASHBACK TABLE (10GNF)
		
		# 위 기능들은  UNDO_RETENTION (default : 900초) 이후로는 UNDO DATA가 사라질 수 있습니다
			# 이 시간이 지나면 사라지는 UNDO DATA를 특정 공간에 저장해놓습니다
			
			# 이 공간 이름을 'Flashback Data Archive'라고 합니다



	# 11g 부터는 'Flashback Data Archive' 기능을 이용해 시간제한없이 기술을 사용할 수 있습니다

		# FLASHBACK DATA ARCHIVE가 활성화된 테이블에서는 다음 구문이 먹히지 않습니다

			# DROP TABLE {...};
			# ALTER TABLE {...};






	# FBDA (백그라운드 프로세스) : Flashback Data Archive의 백그라운드 프로세스입니다

		# 버퍼캐시의 언두에서 작동합니다
		
		# 언두데이터를 통합해 Flashback Data Archive를 구성합니다




	# 사전 작업





CREATE FLASHBACK ARCHIVE {...};  -- FLASHBACK ARCHIVE를 생성합니다

ALTER FLASHBACK ARCHIVE  {...};  -- FLASHBACK ARCHIVE를 수정합니다





GRANT FLASHBACK ARCHIVE ON FLA1 TO hr; -- hr 유저에게 특정 테이블의 기록으 추적할 수 있는  FLASHBACK ARCHIVE 권한을 부여합니다

GRANT FLASHBACK, SELECT on hr.employees to hr; -- 특정 객체를 query할 수 있는 FLASHBACK 및 SELECT 권한을 hr유저에게 부여합니다







	# 실습시작






CREATE TABLESPACE fbda1
DATAFILE
'C:\app\buk213\oradata\orcl\fbda101a.dbf'
SIZE 11 M
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited
, 'C:\app\buk213\oradata\orcl\fbda101b.dbf'
SIZE 11 M
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited ;




CREATE TABLESPACE fbda2
DATAFILE
'C:\app\buk213\oradata\orcl\fbda201a.dbf'
SIZE  11 M
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited
, 'C:\app\buk213\oradata\orcl\fbda201b.dbf'
SIZE  11 M
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited ;  -- 2개의 테이블스페이스를 생성합니다




CREATE USER fbdauser
IDENTIFIED BY oracle4U
DEFAULT TABLESPACE fbda1
QUOTA unlimited ON fbda1
QUOTA unlimited ON fbda2 ; -- FLASHBACK DATA ARCHIVE를 관리할 계정을 생성합니다 (실제로는 따로 안만든다고 합니다)





GRANT connect, resource, FLASHBACK ARCHIVE ADMINISTER
TO fbdauser ; -- 여러가지 FBDA에 필요한 권한을 부여합니다


GRANT alter any table
TO fbdauser ; -- 시스템권한도 부여합니다



conn fbdauser/oracle4u@orcl -- fbdauser로 접속합니다


CREATE FLASHBACK ARCHIVE fla1
TABLESPACE fbda1
QUOTA 1G
RETENTION 5 YEAR ;  -- FLASHBACK ARCHIVE 공간을 fla1라는 이름으로 생성합니다





conn / as sysdba

CREATE FLASHBACK ARCHIVE DEFAULT fla2
TABLESPACE fbda1
QUOTA 1G
RETENTION 2 YEAR ;  -- DEFAULT FLASHBACK DATA ARCHIVE 공간을 fla2라는 이름으로 생성합니다
					-- sys 계정만 DEFAULT 공간을 생성할 수 있습니다
					-- FBDA 백그라운드 포로세스가 실행됩니다





conn fbdauser/oracle4U@orcl


GRANT FLASHBACK ARCHIVE
ON fla1
TO hr ;   -- UNDO DATA를 생성하는 hr 유저에게 fla1 권한을 부여합니다

GRANT FLASHBACK ARCHIVE
ON fla2
TO hr ; -- fla2도 부여합니다







conn hr/oracle4U@orcl


ALTER TABLE hr.employees
FLASHBACK ARCHIVE fla1 ;  -- employees의 UNDO DATA를 fla1 공간에 저장하도록 설정합니다



ALTER TABLE hr.departments
FLASHBACK ARCHIVE ;   -- departments 테이블의 UNDO DATA를 fla2 공간에 저장하도록 설정합니다
					  -- fla2 는 DEFAULT FLASHBACK DATA ARCHIVE 이므로 이름을 안지정해줘도 됩니다







conn fbdauser/oracle4U


ALTER TABLE hr.employees
NO FLASHBACK ARCHIVE;  -- employees 테이블의 공간설정을 해제합니다


ALTER TABLE hr.departments
NO FLASHBACK ARCHIVE;  -- departments 테이블의 공간설정을 해제합니다








ALTER FLASHBACK ARCHIVE fla1
MODIFY TABLESPACE fbda1 QUOTA 10G; -- fla1의 1G 용량이 작다면 10G로 늘려줍니다


ALTER FLASHBACK ARCHIVE fla1
ADD TABLESPACE fbda2 QUOTA 5G; -- fla2도 5G로 늘려줍니다


ALTER FLASHBACK ARCHIVE fla1
MODIFY RETENTION 2 YEAR; -- fla2 기간을 2년으로 늘려줍니다


ALTER FLASHBACK ARCHIVE fla1 PURGE
BEFORE
TIMESTAMP(SYSTIMESTAMP ? INTERVAL '1' YEAR); -- fla1의 특정 기간 데이터를 삭제합니다


DROP FLASHBACK ARCHIVE fla1; -- fla1 공간 설정을 해제합니다 (테이블스페이스는 삭제하지 않습니다)

















--------------------------------------------------------------------------------------------------

<Flashback Transaction Backout (11gNF)>

## Flashback Transaction Backout (11gNF)

	# 여러 트랜잭션간에 종속관계를 확인하면서 FLASHBACK 할 수 있는 11g 새로운 기능입니다

	# DBMS_FALSHBACK.TRANSACTION_BACKOU 내장패키지의 프로시저를 사용합니다

	# sysdba 권한만 사용할 수 있습니다

	# 이 기능을 사용하기 위한 필수 설정
		# 아카이브 로그모드가 구성되어 있어야 합니다
		# FLASH RECOVERY AREA 구성이 설정되어 있어야합니다
		# 보완로그가 활성화되어 있어야 합니다
		# Flashback Transaction을 사용하는 계정에 DBMS_FALSHBACK 권한을 부여해야 합니다
		# 위 계정에 SELECT ANY TRANSACTION 권한도 부여해야 합니다




desc DBMS_FLASHBACK  -- DBMS_FALSHBACK 패키지를 확인합니다





ALTER SYSTEM SET
db_recovery_file_dest_size = 50G ;

ALTER SYSTEM SET
db_recovery_file_dest='c:\users\buk213\fra' SCOPE=BOTH ; -- FRA 구성을 설정합니다




ALTER DATABASE ADD SUPPLEMENTAL LOG DATA;

ALTER DATABASE ADD SUPPLEMENTAL LOG DATA
(PRIMARY KEY) COLUMNS;

ALTER DATABASE ADD SUPPLEMENTAL LOG DATA
(FOREIGN KEY) COLUMNS;  -- 보완로그들을 활성화합니다





GRANT EXECUTE ON dbms_flashback
TO hr;

GRANT SELECT ANY TRANSACTION
TO hr;   -- Transaction 을 사용하는 계정에 두 권한을 부여합니다








archive log list -- 아카이브로그모드 설정을 확인합니다


show parameter db_recovery_file_dest  -- FRA 구성이 설정되었는지 확인합니다


SELECT SUPPLEMENTAL_LOG_DATA_MIN
,SUPPLEMENTAL_LOG_DATA_PK
,SUPPLEMENTAL_LOG_DATA_UI
,SUPPLEMENTAL_LOG_DATA_FK
,SUPPLEMENTAL_LOG_DATA_ALL
FROM v$database ;   -- 보완로그 설정을 확인합니다


ALTER SYSTEM SWITCH LOGFILE;
ALTER SYSTEM CHECKPOINT ;  -- 로그스위치와 체크포인트를 강제로 해줍니다






SHUTDOWN IMMEDIATE

STARTUP

conn hr/oracle4U


CREATE TABLE hr.region_ft
( REGION_ID NUMBER
, REGION_NAME VARCHAR2(25)
) TABLESPACE users ;  -- 실습용 테이블을 생성합니다



INSERT INTO hr.region_ft VALUES (10,'Pole');

INSERT INTO hr.region_ft VALUES (20,'Moon');

INSERT INTO hr.region_ft VALUES (30,'Venus');

INSERT INTO hr.region_ft VALUES (40,'Mars');

INSERT INTO hr.region_ft VALUES (50,'Saturn');

COMMIT ; -- 테스트 트랜잭션1을 수행합니다 





UPDATE hr.region_ft
SET region_name='Two Poles'
WHERE region_id = 10 ;

UPDATE hr.region_ft
SET region_name='Many Moons'
WHERE region_id = 20 ;

COMMIT;  -- 테스트 트랜잭션2를 수행합니다






UPDATE hr.region_ft
SET region_name='No star'
WHERE region_id = 10;

UPDATE hr.region_ft
SET region_name='Red star'
WHERE region_id = 40;

UPDATE hr.region_ft
SET region_name='Big star'
WHERE region_id = 50;

COMMIT ; -- 테스트 트랜잭션3을 수행합니다





UPDATE hr.region_ft
SET region_name='Still called Venus'
WHERE region_id = 30;

COMMIT ;  -- 테스트 트랜잭션4를 수행합니다 




SELECT *
FROM hr.region_ft ; -- 테이블 값을 확인합니다



					REGION_ID REGION_NAME
	--------------------------------------------------------------
	10 	No star <== (Tx 3) <== Two Poles(Tx 2) <== Pole (Tx 1)
	20 	Many Moons <=================== (Tx 2) <== Moon (Tx 1)
	30 	Still called Venus <===== (Tx 4) <======== Venus (Tx 1)
	40 	Red star <== (Tx 3) <===================== Mars (Tx 1)
	50 	Big star <== (Tx 3) <===================== Saturn (Tx 1)









conn / as sysdba

ALTER SYSTEM SWITCH LOGFILE;
ALTER SYSTEM CHECKPOINT ;  -- 로그스위치와 체크포인트를 3번 수행합니다]





set pagesize 50000
col region_name format a19
SELECT hr.region_ft.*
,versions_startscn ST_SCN
,versions_endscn END_SCN
,versions_XID TX_ID
,versions_operation OPERATION
FROM hr.region_ft VERSIONS BETWEEN SCN MINVALUE AND MAXVALUE ; -- FLASHBACK VERSIONS QUERY를 통해 SCN 값을 확인합니다





REGION_ID REGION_NAME             ST_SCN    END_SCN TX_ID            OPERATI
--------- ------------------- ---------- ---------- ---------------- -------
       50 Big star               1744115            07001C0005030000 U
       40 Red star               1744115            07001C0005030000 U
       10 No star                1744115            07001C0005030000 U
       20 Many Moons             1744096            09000A008C030000 U     
       10 Two Poles              1744096    1744115 09000A008C030000 U
       50 Saturn                 1744070    1744115 0A001700DC020000 I
       40 Mars                   1744070    1744115 0A001700DC020000 I
       30 Venus                  1744070            0A001700DC020000 I
       20 Moon                   1744070    1744096 0A001700DC020000 I
       10 Pole                   1744070    1744096 0A001700DC020000 I
-- TX_ID가 같으면 같이 실행된 구문입니다
-- 09000A008C030000를 Flashback 시키고 싶습니다







declare
v_xid xid_array ;
begin
v_xid := xid_array('09000A008C030000');
dbms_flashback.transaction_backout(
numtxns=>1,
xids=>v_xid,
options=>dbms_flashback.nocascade);  -- nocascade는 의존성이 있으면 에러를 내겠다는 뜻입니다
end;
/  -- 해당 구문을 실행합니다 (에러가 납니다)




declare
v_xid xid_array ;
begin
v_xid := xid_array('09000A008C030000');
dbms_flashback.transaction_backout(
numtxns=>1,
xids=>v_xid,
options=>dbms_flashback.cascade);  -- nocascade는 의존성이 있으면 에러를 내겠다는 뜻입니다
end;
/  -- 해당 구문을 실행합니다 (에러가 납니다)





SELECT *
FROM hr.region_ft ; -- 복구된 데이터를 확인합니다


COMMIT; -- 커밋을 실행합니다















--------------------------------------------------------------------------------------------------

<Flashback Table (10gNF)>

## Flashback Table (10gNF)

	# 잘못된 DMLs 작업을 복구합니다

	# 시스템테이블에는 수행할 수 없습니다

	# Flashback Table 로 이 상황을 조치하려면 다른 세션의 DML 작업이 없어야 합니다
		# 잘못된 작업이 실수로 커밋되고 다음에 정상적인 작업이 커밋된 경우 사용하면 정상적인 작업들 모두 롤백됩니다


	# 테이블의 기존 행을 전부 삭제한 후 UNDO 데이터를 이용해 모두 INSERT 합니다
		# UNDO 데이터와 REDO 로그가 많이 발생합니다








conn / as sysdba -- 관리자로 접속합니다

CREATE TABLE hr.emps17_02
(empno NUMBER(6)
,ename VARCHAR2(30)
,sal NUMBER(8,2)
,deptno NUMBER(4)
)
TABLESPACE users ;  -- 실습용 테이블을 생성합니다


INSERT INTO hr.emps17_02(empno, ename, sal, deptno)
SELECT employee_id, last_name, salary, department_id
FROM hr.employees
WHERE department_id < 60 ;  -- 데이터를 입력합니다


COMMIT;  


col ename format a12
set pagesize 5000
SELECT *
FROM hr.emps17_02
ORDER BY 4 ;  -- 입력된 데이터를 확인합니다


UPDATE hr.emps17_02
SET sal = 10000
WHERE deptno = 50 ;   -- Grant 직원의 월급을 10000으로 변경합니다  (실수로 50번 부서의 모든 월급이 바꼇습니다)


COMMIT;




--------------------------


conn hr/oracle4U -- 새로 접속 후


UPDATE hr.emps17_02
SET sal = 15000
WHERE empno = 200 ;  -- 데이터변경 작업을 실행합니다 (정상적인 작업)


COMMIT;




col ename format a15
col st_time format a17
col end_time format a17
set linesize 120
set pagesize 999
SELECT ename, sal, versions_startscn ST_SCN
, versions_endscn END_SCN
, versions_xid TX_ID
, versions_operation OPERATION
FROM hr.emps17_02
VERSIONS BETWEEN scn MINVALUE AND MAXVALUE
WHERE deptno = 50 or empno=200 ;  -- FLASHBACK VERSION QUERY 먼저 확인합니다
								  -- SCN 값을 확인해서 변경 전 값을 확인합니다





-- 방법 1 (FLASHBACK TRANSACTION QUERY)
set pagesize 50000
SELECT undo_sql
FROM flashback_transaction_query
WHERE table_name = 'EMPS17_02'
AND commit_scn = 1741811
ORDER BY start_timestamp desc ;  -- 위에서 확인한 SCN값을 이용해서 FLASHBACK Transaction 복구를 합니다
								-- UNDO SQL문이 생성됩니다 (조치 완료)
								-- 이후에 발생한 정상적인 DML문이 그대로 유지됩니다





-- 방법 2 (FLASHBACK TABLE)
ALTER TABLE hr.emps17_02
ENABLE row movement ; -- 해당 테이블에 row movement 기능을 활성화시킵니다



FLASHBACK TABLE hr.emps17_02 TO SCN 1741810; -- FLASHBACK TABLE로 복구를 수행합니다
											 -- SCN 값은 위에서 확인한 값보다 1 작은 값으로 합니다
-- 단점 : 해당 변경 이후의 정상적인 DML도 전부 변경됩니다


col ename format a12
SELECT *
FROM hr.emps17_02
WHERE DEPTNO=50 ; -- 복구된 데이터를 확인합니다

















--------------------------------------------------------------------------------------------------

<Flashback Transaction Query (10gNF)>


## Flashback Transaction Query (10gNF)
	# 11g에서 약간 변경되었습니다
	
	# FLASHBACK 기술 중 가장 중요하다고 합니다

	# 잘못 수행된 트랜잭션의 DML 문장에 대한 UNDO DATA를 분석하여 UNDO SQL을 작성합니다
		
		# FLASHBACK_TRANSACTION_QUERY 뷰를 사용합니다
			# 일반 계정은 해당 뷰에 권한이 없습니다
			
			# SELECT ANY Transaction 권한을 받아야합니다
			
			# 최소 보완로그 기능, PRIMARY KEY 보완로그 기능이 활성화되어있어야 합니다

	




ALTER DATABASE ADD SUPPLEMENTAL LOG DATA ; -- 최소 보완로그 기능 활성화

ALTER DATABASE ADD SUPPLEMENTAL LOG DATA
(PRIMARY KEY) COLUMNS;		-- PRIMARY KEY 보완로그 기능 활성화	






col ename format a7
col empno format 999
col salary format 99999
col deptno format 99
set linesize 200
set pagesize 999
SELECT hr.emps10_01.*
, versions_startscn ST_SCN
, versions_endscn END_SCN
, versions_XID TX_ID
, versions_operation OPERATION
FROM hr.emps10_01
VERSIONS BETWEEN SCN MINVALUE AND MAXVALUE
WHERE empno=101;  -- FLASHBACK VERSION QUERY로 SCN 정보를 확인합니다








GRANT SELECT ANY TRANSACTION
TO hr ; -- hr 계정에 FLASHBACK_TRANSACTION_QUERY 뷰를 볼 수 있는 권한을 줍니다





conn hr/oracle4U




set pagesize 999
set linesize 85
col START_TIMESTAMP format a8
col COMMIT_TIMESTAMP format a8
col table_owner format a2
col table_name format a9
col undo_sql format a100
col operation format a7
SELECT XID, START_SCN, COMMIT_SCN, UNDO_CHANGE#
,OPERATION,ROW_ID, UNDO_SQL
FROM FLASHBACK_TRANSACTION_QUERY
WHERE TABLE_NAME = 'EMPS10_01'
AND COMMIT_SCN BETWEEN 1743200 AND 1743500
ORDER BY start_timestamp desc ;  -- SCN 값을 확인 후 그 값을 삽입해서 조회합니다
								-- UNDO_SQL 란에 있는 값을 이용해 복구를 수행합니다





SELECT *
FROM hr.emps10_01
WHERE empno=101 ; -- 변경된 값을 확인합니다
















--------------------------------------------------------------------------------------------------

<Flashback Versions Query (10gNF)>


## Flashback Versions Query (10gNF)
	# FlashBack Query의 반응이 좋아서 업그레이드된 버전입니다

	# 하나의 행이 여러 트랜잭션에 의해 바꼈을 때 이 행이 UNDO_RETENTION 값보다 작으면
	- 예전값과 변경 사항까지 전부 알 수 있습니다


	# Versions_xxx 구문을 사용합니다
		# versions_startscn : 트랜잭션이 COMMIT 시 SCN
		# versions_endscn : 해당 버젼의 유효성이 상실된 SCN
		# versions_starttime : 트랜잭션이 COMMIT 시 datetime
		# versions_endtime : 해당 버젼이 유효한 최종 datetime
		# versions_XID : 해당 트랜잭션 ID
		# versions_operation : 해당 트랜잭션의 DML 작업 종류
		
		(U: update, D: delete, I: insert)







	# 다음 Object를 조회하는 쿼리에는 Versions 쿼리를 적용할 수 없습니다
		# External tables : DML안됨
		# Temporary tables : 저장된 데이터가 없음
 		# Fixed tables : v$ 계열의 시스템 뷰의  Base Table
		# Views



CREATE TABLE hr.emps10_01(empno, ename, sal, deptno)
TABLESPACE users
AS
SELECT employee_id, last_name, salary, department_id
FROM hr.employees
WHERE department_id in (10,20,90) ;  -- 테이블 하나를 만듭니다
	


col ename format a9
SELECT *
FROM hr.emps10_01
order by 1;  -- 테이블을 조회합니다





UPDATE hr.emps10_01
SET ename='Kwanwoo'
WHERE empno=101 ;  -- 테이블의 값을 변경합니다 


COMMIT;



UPDATE hr.emps10_01
SET sal=0
WHERE empno=101 ;   -- 테이블의 값을 변경합니다2


COMMIT ;



DELETE FROM hr.emps10_01
WHERE empno=101 ;   -- 테이블의 값을 변경합니다3



COMMIT ;


SELECT *
FROM hr.emps10_01
WHERE empno=101 ; -- 상태를 확인합니다 






col ename format a7
col empno format 999
col salary format 99999
col deptno format 99
set linesize 200
set pagesize 999
SELECT hr.emps10_01.*
, versions_startscn ST_SCN
, versions_endscn END_SCN
, versions_XID TX_ID
, versions_operation OPERATION
FROM hr.emps10_01
VERSIONS BETWEEN SCN MINVALUE AND MAXVALUE -- 언두데이터의 최초부터 마지막 데이터를 전부 출력
WHERE empno=101;    -- FlashBack Versions Query를 활용해 언두데이터를 조회합니다















------------------------------------------------------------------------------------------------

<FlashBack Query (9iNF)>


## FlashBack Query (9iNF)
	# 앞서 수행된 DML 작업이 잘못된 작업이고 작업전 값으로 되돌려놔야합니다
	# 이미 커밋되어서 롤백할 수 없고 예전 값을 모릅니다

	# UNDO_RETENTION 값에 저장된 시간은 아직 안지났습니다

	# AS OF + TIMESTAMP 를 활용합니다




SELECT salary
FROM hr.employees
WHERE employee_id = 200 ;	


UPDATE hr.employees
SET salary=6500
WHERE employee_id = 200 ;

COMMIT;   -- 6500으로 값 변경 후 커밋합니다




conn hr/oracle4U  -- 다시 접속합니다



SELECT employee_id, salary
FROM hr.employees
WHERE employee_id = 200 ;



SELECT employee_id, salary
FROM hr.employees
AS OF TIMESTAMP (SYSDATE-5/1440)
WHERE employee_id = 200 ;    -- 하루(1440분) 에서 5분전에 해당되는 시간에 해당된 언두데이터가 있으면 그 데이터를 불러옵니다


UPDATE hr.employees
SET salary=4400
WHERE employee_id= 200 ; -- 값을 확인 후 다시 전 값으로 되돌려놉니다






		# FlashBack Query 예제





SELECT employee_id, salary
FROM hr.employees
AS OF TIMESTAMP TO_TIMESTAMP
('2011?07?29 10:29:40'
,'yyyy?mm?dd hh24:mi:ss')
WHERE employee_id = 200 ;


SELECT employee_id, salary
FROM hr.employees
AS OF TIMESTAMP (SYSDATE - 1800/86400)
WHERE employee_id = 200 ;    -- 



SELECT mployee_id, salary
FROM hr.employees
AS OF TIMESTAMP (SYSDATE?15/1440)
WHERE employee_id = 200 ;










--------------------------------------------------------------------------------------------------

<FlashBack 수행>



## FlashBack 수행
	# 11g에서는 총 8 가지의 FLASHBACK 기능이 제공됩니다 (오라클에서만 가능합니다)

	# 1부  (오라클의 언두데이터를 이용한 Flashback)

		# Flashback Query ( 9iNF)
		# Flashback Versions Query (10gNF)
		# Flashback Transaction Query (10gNF)
		# Flashback Table (10gNF)
		# Flashback Transaction Backout (11gNF)











	
	# 사전 준비


show parameter undo_  -- UNDO 데이터 설정을 확인합니다



show parameter undo_tablespace -- UNDO-테이블스페이스를 확인합니다




SELECT tablespace_name, retention, contents
FROM dba_tablespaces
WHERE tablespace_name='UNDOTBS1' ; -- retention 값을 확인합니다



ALTER TABLESPACE UNDOTBS1
RETENTION GUARANTEE ; -- RETENTION을 GUARANTEE로 변경합니다







col file_name for a63
SELECT file_name, bytes/1024/1024 SIZE_MB
FROM dba_data_files
WHERE tablespace_name = 'UNDOTBS1' ;   -- UNDO-테이블스페이스의 크기를 확인합니다



ALTER DATABASE DATAFILE
'C:\APP\BUK213\ORADATALTER SYSTEM SWITCH LOGFILE ;A\ORCL\DATA_D-ORCL_TS-UNDOTBS1_FNO-3.DBF'
RESIZE 201M ;   -- UNDO-테이블스페이스의 크기를 201M 로 늘립니다





		# SUPPLEMENTAL LOGGING (보완로그)
			# PRIMARY KEY, FOREIGN KEY.. 등의 값을 관리하는 키인것 같습니다 (부정확)
			
			# 최소보완로그, PRIMARY KEY 보완로그 등등.. 이 있습니다

			# 기본적으로 11g에서는 비활성화돼있습니다
			



			
ALTER DATABASE
ADD SUPPLEMENTAL LOG DATA ;  -- 최소 보완로그를 활성화합니다


ALTER DATABASE
ADD SUPPLEMENTAL LOG DATA
(PRIMARY KEY) COLUMNS;   -- PRIMARY KEY 보완로그를 활성화합니다




ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;  -- 로그스위치, 체크포인트를 1번씩 수행합니다


















