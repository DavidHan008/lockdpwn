
<ORACLE DATAPUMP 엔진을 기반하는 외부테이블>


## ORACLE DATAPUMP 엔진을 기반하는 외부테이블
	# orcl 데이터베이스에서 추출한 외부테이블 데이터를 prod 데이터베이스에서 사용합니다	



		# orcl 데이터베이스로 접속합니다




cmd> set oracle_sid=orcl -- orcl 데이터베이스를 사용합니다

conn / as sysdba

CREATE DIRECTORY dpextdir
AS 'C:\Users\buk213\extdptest' ; -- 디렉토리 객체를 생성합니다



GRANT read, write
ON DIRECTORY dpextdir
TO hr ; -- 객체 권한을 hr 유저에게 부여합니다




conn hr/oracle4U



CREATE TABLE hr.extdp_test_tb
(dname, lname, sal, deptno) -- 컬럼의 이름만 나열했습니다
ORGANIZATION EXTERNAL
(TYPE ORACLE_DATAPUMP -- 반드시 oracle_datapump를 명시
DEFAULT DIRECTORY dpextdir -- 디렉토리 객체이름 지정
LOCATION('emp_dept_join_01.dmp') -- 파일 이름 명시
)
PARALLEL
AS   -- 서브쿼리를 사용합니다
SELECT d.department_name, e.last_name
,e.salary, e.department_id
FROM hr.employees e INNER JOIN hr.departments d
ON e.department_id = d.department_id
WHERE e.department_id < 70 ;   -- 객체를 이용해 외부테이블을 생성합니다 (extdptest 폴더에 파일이 생성됩니다)





desc hr.extdp_test_tb -- 테이블 정보를 확인합니다




col DNAME format a15
col LNAME format a11
set linesize 200
set pagesize 50000
SELECT *
FROM hr.extdp_test_tb ; -- 테이블 데이터를 확인합니다






		# prod 데이터베이스로 접속합니다





cmd> set oracle_sid=prod -- prod 데이터베이스를 사용합니다



SELECT username
FROM dba_users
WHERE username = 'HR' ; -- HR 계정이 있는지 확인합니다 (없으면 만듭니다)



CREATE DIRECTORY getextdir1
AS 'C:\Users\buk213\getextdptest'; -- 디렉토리 객체를 생성합니다



GRANT read, write
ON directory getextdir1
TO hr ; -- 디렉토리 객체의 권한을 hr 유저에게 줍니다





cmd> copy C:\Users\buk213\extdptest\EMP_DEPT_JOIN_01.DMP C:\Users\buk213\getextdptest -- dump 파일을 복사합니다






CREATE TABLE hr.extdp_test_tb2
(
DNAME VARCHAR2(30) -- NOT NULL 외부테이블은 제약조건을 정의할 수 없습니다
,LNAME VARCHAR2(25) -- NOT NULL
,SAL NUMBER(8,2)
,DEPTNO NUMBER(4)
)
ORGANIZATION EXTERNAL
(
TYPE ORACLE_DATAPUMP
DEFAULT DIRECTORY getextdir1
LOCATION ('emp_dept_join_01.dmp')
);  -- prod 데이터베이스에 외부테이블을 생성합니다




col DNAME format a15
col LNAME format a11
set linesize 200
set pagesize 50000
SELECT *
FROM hr.extdp_test_tb2 ; -- 생성한 외부테이블의 데이터를 조회합니다






	# 외부테이블 전체가 아니라 원하는 데이터만 추출할땐





CREATE TABLE hr.test_tb2
NOLOGGING -- 입력작업에 리두로그를 생성하지 않기 위해 NOLOGGING을 설정합니다
as
SELECT *
FROM extdp_test_tb2
where 1=2 ; -- 원하는 데이터만 로딩하기 위해 테이블을 생성합니다


INSERT /*+ APPEND */ INTO hr.test_tb2
SELECT *
FROM extdp_test_tb2
WHERE deptno < 30; -- 원하는 행만 로딩할 수 있습니다


COMMIT;


SELECT * FROM hr.test_tb2 ; -- 입력된 데이터를 확인합니다


ALTER TABLE hr.test_tb2
LOGGING ; -- 다시 LOGGING 모드로 전환합니다













-------------------------------------------------------------------------------------------------

<데이터베이스 링크를 통한 데이터 이동>


## ORCL 데이터베이스 ==> PROD 데이터베이스
	
	# export할 필요없이 링크를 통해 바로 import 할 수 있습니다	

	# LOGFILE 옵션을 사용해 로그파일을 만드려면 디렉토리 객체를 생성해야합니다
	


set oracle_sid=prod  -- prod DB로 설정합니다

conn / as sysdba


SELECT tablespace_name
FROM dba_tablespaces
WHERE contents='PERMANENT' ; -- 구성된 테이블스페이스를 확인합니다




CREATE TABLESPACE example
DATAFILE 'C:\app\buk213\oradata\prod\example01.dbf'
size 11M
autoextend on next 10M ; -- example 테이블스페이스를 생성합니다



SELECT username
FROM dba_users
WHERE username = 'HR' ; -- hr 유저가 존재하는지 확인합니다



CREATE USER hr
IDENTIFIED BY oracle4U
DEFAULT TABLESPACE example
TEMPORARY TABLESPACE temp
QUOTA unlimited ON example
QUOTA unlimited ON users ; -- hr 유저를 생성합니다



GRANT connect
,resource
,create view
,create synonym
TO hr ;   -- hr 유저에게 시스템권한을 줍니다


GRANT create database link
TO hr ; -- db 링크를 만들 수 있는 권한도 줍니다






conn hr/oracle4U@prod   -- hr 유저로 접속합니다


CREATE DATABASE LINK dblinkorcl
CONNECT TO hr IDENTIFIED BY oracle4U
USING 'orcl' ;



col db_link format a30
col host format a10
SELECT db_link, host
FROM user_db_links ;  -- 데이터베이스 링크를 확인합니다






========================================
## 데이터베이스 링크를 이용한 테이블 임포트  
USERID=hr/oracle4U@prod
JOB_NAME=netimp1
TABLES=HR.departments,HR.employees,HR.COUNTRIES,HR.LOCATIONS,HR.REGIONS,H
R.JOBS,HR.JOB_HISTORY
TABLE_EXISTS_ACTION=replace -- 테이블이 존재하면 지우고 다시 만듭니다
EXCLUDE=INDEX
EXCLUDE=CONSTRAINT
EXCLUDE=TRIGGER
EXCLUDE=GRANT
EXCLUDE=DEMENSION
NETWORK_LINK=dblinkorcl.example11.com   -- DB 링크를 입력합니다 (orcl로 접속합니다)
NOLOGFILE=y
========================================
-- 해당 내용을 netimp.par 파라미터파일로 저장합니다






impdp parfile=C:\Users\buk213\netimp.par -- 해당 파일을 통해 데이터베이스 간 데이터이동을 합니다



conn hr/oracle4U


col tname format a30
set pagesize 100
SELECT *
FROM tab ; -- 제대로 import 됐는지 확인합니다


















-------------------------------------------------------------------------------------------------

<DATAPUMP export/import (10gNF)>

## DATAPUMP export/import (10gNF)
	# expdp.exe, impdp.exe
	
		# 오라클 서버에 DBMS_DATAPUMP 내장 프로그램을 실행합니다

		# 외부테이블이나  DIRECT-PATH 중 한 가지 방식을 자동으로 선택합니다

		# 접속 시 서버프로세스가 실행되어 DBMS_DATAPUMP 프로그램을 호출합니다

		# 작업이 병렬처리가 가능합니다
		
		# DBA_DATAPUMP_JOBS 딕셔너리 뷰를 사용해 현재 진행 중인 작업을 알 수 있습니다

		# sys 계정은 expdp, impdp를 사용할 수 없습니다




		# 'MASTER-CONTROL-PROCESS(MCP)' 가 생성됩니다
			
			# DBA_DATAPUMP_JOBS 딕셔너리에 JOB 정보를 등록합니다
			# MASTER-TABLE 을 생성해 저장합니다
			# 작업 큐를 생성합니다
			# 딕셔너리 객체에 export/import 파일을 생성하고 데이터를 이동시킵니다
			# WORKING-서버프로세스에 의해 작업을 계속 진행하고 작업의 진행상황을 MASTER-TABLE 에 계속 기록합니다
			# 작업이 종료된 후 WORKING-서버프로세스가 종료되고 MASTER-TABLE, DBA_DATAPUMP_JOBS 가 삭제되고 MCP 프로세스가 종료되고 접속이 종료됩니다




		

		# expdp parameters
			# VERSION=10.2.0.1.0
				# 상위버전(11g)에서 하위버전(10gNF)으로 Import할 때 사용합니다





		# expdp / impdp 를 사용하는 3가지 방법이 있지만 
		- 이번에는 parameter 파일을 생성해 작업하는 방법을 실습합니다







cmd> expdp help=y -- expdp 도움말을 확인합니다




CREATE DIRECTORY dp_test_dir
AS 'C:\Users\buk213\dptest' ; -- 디렉토리 객체를 생성합니다



col DIRECTORY_NAME format a15
col DIRECTORY_PATH format a50
set linesize 80
SELECT DIRECTORY_NAME, DIRECTORY_PATH
FROM dba_directories
WHERE DIRECTORY_NAME='DP_TEST_DIR' ; -- 디렉토리 객체를 생성합니다



GRANT read, write
ON DIRECTORY dp_test_dir
TO hr ; -- 위에서 생성한 디렉토리 객체 권한을 hr 계정에게 부여합니다



SELECT DIRECTORY_NAME, DIRECTORY_PATH
FROM dba_directories
WHERE DIRECTORY_NAME='DATA_PUMP_DIR' ; -- (11g) DATA_PUMP_DIR 디렉토리 객체 정보를 확인합니다



GRANT exp_full_database, imp_full_database
TO hr ; -- DATA_PUMP_DIR 디렉토리 객체 권한을 hr 유저에게 설정합니다







--=============================
USERID=system/oracle4U@orcl
DIRECTORY=dp_test_dir   -- 디렉토리 객체명
JOB_NAME=exptest1  -- job 이름을 설정합니다
LOGFILE=exp_test1.log
DUMPFILE=exp_test1_%U.dmp  -- export 파일 이름을 설정합니다
FILESIZE=10M  -- export 파일을 10m 단위로 분할합니다
SCHEMAS=HR,SH,OE,PM -- 해당 스키마 객체를 모두 export 합니다
EXCLUDE=GRANT   -- 해당 객체는 제외합니다 
EXCLUDE=INDEX
EXCLUDE=TRIGGER
EXCLUDE=REF_CONSTRAINT
EXCLUDE=TABLE:"LIKE 'STAFF_%'"
EXCLUDE=VIEW
EXCLUDE=PACKAGE
QUERY=HR.EMPLOYEES:"WHERE department_id IS NOT NULL ORDER BY employee_id"
QUERY=HR.DEPARTMENTS:"WHERE department_id < 120"
CONTENT=ALL
PARALLEL=3  -- 3개의 서버프로세스가 실행됩니다
--=================================== 
-- 해당 내용을 exptest1.par 파라미터파일로 저장합니다 (export)




cmd> expdp parfile=C:\Users\buk213\exptest1.par -- expdp를 이용해 export를 수행합니다



col OWNER_NAME format a8
col JOB_NAME format a15
col OPERATION format a6
col JOB_MODE format a8
col STATE format a13
col degree format 99
set linesize 120
SELECT OWNER_NAME, JOB_NAME, OPERATION, JOB_MODE, STATE,
DEGREE, DATAPUMP_SESSIONS
FROM dba_datapump_jobs
WHERE job_name = 'EXPTEST1' ; -- 작업이 진행중일 때 조회하면 실행 내용을 알 수 있습니다





cmd> vim C:\Users\buk213\dptest\exp_test1.log -- 로그파일을 확인합니다







--=============================
## SCHEMA MOVING
USERID=system/oracle4U@orcl
DIRECTORY=dp_test_dir
JOB_NAME=imptest1
LOGFILE=imp_test1.log
DUMPFILE=exp_test1_%U.dmp
SCHEMAS=HR,SH
TABLE_EXISTS_ACTION=append -- import 하려는 객체가 이미 있으면 테이블의 메타데이터는 import하지 않고 export 파일의 사용자 데이터만 import 합니다
REMAP_SCHEMA=HR:HR10   -- export 파일에 있는 hr 객체를 hr10 계정의 스키마 객체로 import 합니다
REMAP_SCHEMA=SH:HR10
REMAP_TABLESPACE=EXAMPLE:USERS
--EXCLUDE=INDEX
--EXCLUDE=REF_CONSTRAINT
--EXCLUDE=TRIGGER
--EXCLUDE=PACKAGE
--EXCLUDE=OBJECT_GRANT
--EXCLUDE=VIEW
EXCLUDE=FUNCTION
EXCLUDE=PROCEDURE
EXCLUDE=DIMENSION
EXCLUDE=CONSTRAINT
EXCLUDE=COMMENT
EXCLUDE=STATISTICS
EXCLUDE=TABLE:"LIKE 'COUNTRIES%'"
--===================================
-- 해당 내용을 imptest1.par 파라미터파일로 저장합니다 (import)







cmd> impdp parfile=C:\Users\buk213\imptest1.par  -- 해당 내용을 import 합니다




col USERNAME format a5
col ACCOUNT_STATUS format a15
SELECT USERNAME, ACCOUNT_STATUS
FROM dba_users
WHERE username = 'HR10' ; -- 위의 IMPORT로 HR10 계정이 잘 만들어졌는지 확인합니다




ALTER USER HR10
IDENTIFIED BY oracle4U;




col owner format a10
col table_name format a30
col tablespace_name format a15
set pagesize 50000
SELECT owner, table_name, tablespace_name
FROM dba_tables
WHERE owner = 'HR10'
ORDER BY 1, 3 ; -- HR10 계정으로 import된 테이블 정보를 확인합니다




col PARTITION_NAME format a15
col table_name format a7
col tablespace_name format a15
set linesize 80
SELECT table_name, partition_name, tablespace_name
FROM dba_tab_partitions
WHERE table_owner='HR10' ;  -- 파티션 테이블을 구성하는 파티션정보를 조회합니다
-- 파티션 테이블: 하나의 테이블에 여러개의 세그먼트를 구성할 수 있습니다 






























-------------------------------------------------------------------------------------------------

<ORACLE_LOADER 엔진을 기반하는 외부테이블>

## ORACLE_LOADER 엔진을 기반하는 외부테이블
	# 외부테이블 : 오라클 서버에서 외부 파일을 조회할 수 있는 테이블을 말합니다

		# 디렉토리 객체를 생성합니다
		# DML 작업이 안됩니다


=============================================
301,"KWON","29","F","740205","2598659","107"
302,"KIM",30,M,730715,1824451,108.9
303,"JUNG",22,F,810922,2411057,107
304,"YUN",25,F,781102,2804478,109
305,"PARK",24,M,790130,1496300,108
306,"LEE",32,M,711013,1695521,110
307,"KAWK",34,6908150,1135620,110
==============================================
-- staff.txt 이름으로 exttest 폴더에 저장합니다







conn / as sysdba


CREATE DIRECTORY extdir
AS 'C:\Users\buk213\exttest';  -- 디렉토리 객체를 생성합니다


SELECT *
FROM dba_directories
WHERE DIRECTORY_NAME='EXTDIR' ; -- 생성된 객체를 확인합니다





GRANT read, write
ON directory extdir
TO hr ; -- hr 유저에게 해당 디렉토리 권한을 줍니다


conn hr/oracle4U



CREATE TABLE hr.staff_ext
(sname VARCHAR2(10)
,sno NUMBER
,age NUMBER
,gender VARCHAR2(2)
,jumin1 VARCHAR2(6)
,jumin2 VARCHAR2(7)
,dno NUMBER(3)
)
ORGANIZATION EXTERNAL  -- 외부로 구성하겠습니다
( TYPE ORACLE_LOADER   -- ORACLE_LOADER 엔진을 사용하겠습니다
DEFAULT DIRECTORY extdir 
ACCESS PARAMETERS  -- 외부 소스의 데이터 상태를 설명합니다
( RECORDS DELIMITED BY NEWLINE
BADFILE 'staff_bad'
LOGFILE 'staff_log'
FIELDS TERMINATED BY ','
optionally enclosed by '"'
(sno
,sname
,age
,gender
,jumin1
,jumin2
,dno INTEGER external(7)
)
)
LOCATION ('staff.txt') -- 경로명 
)
PARALLEL 5
REJECT LIMIT unlimited ;  -- 외부테이블을 생성합니다
						  -- 외부테이블 생성시에는 TABLESPACE 옵션을 사용할 수 없습니다
						  -- REJECT LIMIT : 허용 에러 갯수를 설정합니다



col sname format a5
col gender format a2
col jumin1 format a7
col jumin2 format a7
SELECT *
FROM hr.staff_ext ; -- 외부테이블로 레코드를 조회합니다




SELECT SNO, SNAME, JUMIN1, JUMIN2
FROM hr.staff_ext
WHERE SNO between 303 and 306 ; -- 입력할 데이터를 확인합니다



CREATE TABLE hr.staff
(sno NUMBER(4)
,sname VARCHAR2(30)
,jumin1 VARCHAR2(6)
,jumin2 VARCHAR2(7)
)TABLESPACE example ; -- 데이터를 입력할 테이블을 생성합니다


ALTER TABLE hr.staff
NOLOGGING ;  -- 리두로그를 생성하지 않기 위해 설정합니다



INSERT /*+ APPEND */ INTO hr.staff (sno, sname, jumin1, jumin2)
SELECT sno, LOWER(sname), jumin1, jumin2
FROM hr.staff_ext
WHERE SNO between 303 and 306 ;  -- DIRECT-PATH LOAD를 사용한 서브쿼리를 실행합니다


COMMIT;






col sname format a5
col gender format a2
col jumin1 format a7
col jumin2 format a7
SELECT *
FROM hr.staff ;  -- 입력된 데이터를 확인합니다


ALTER TABLE hr.staff
LOGGING ;  -- 다시 LOGGING 모드로 설정합니다











-------------------------------------------------------------------------------------------------

<서브쿼리를 활용한 데이터로딩>

## 서브쿼리를 활용한 DIRECT-PATH 데이터로딩


conn / as sysdba

CREATE TABLE hr.sales1
TABLESPACE example
AS
SELECT *
FROM sh.sales
WHERE 1=2 ;

CREATE TABLE hr.sales2
TABLESPACE example
AS
SELECT *
FROM sh.sales
WHERE 1=2 ;

CREATE TABLE hr.sales3
TABLESPACE example
AS
SELECT *
FROM sh.sales
WHERE 1=2 ;




	# /* APPEND */  DIRECT-PATH



ALTER TABLE hr.sales1
NOLOGGING ;

ALTER TABLE hr.sales2
NOLOGGING ;

ALTER TABLE hr.sales3
NOLOGGING ;


INSERT INTO hr.sales1
NOLOGGING
SELECT *
FROM sh.sales;  -- /*+ APPEND */ 힌트가 없는 일반적인 서브쿼리이므로 리두로그가 생성됩니다
				-- (NOLOGGING 옵션이어도)

COMMIT;






INSERT /*+ APPEND */ INTO hr.sales2
NOLOGGING
SELECT *
FROM sh.sales; -- NOLOGGING 옵션인 경우 리두로그가 생성되지 않습니다 (오라클 전용 힌트)

COMMIT;




ALTER TABLE hr.sales3
NOPARALLEL
LOGGING ;




	# /* PARALLEL */  DIRECT-PATH





ALTER TABLE hr.sales3
PARALLEL 2 ;  -- 서버프로세스를 2개 씁니다 
			  -- 단점 : 해당 테이블에 존재하는 모든 인덱스가 없어야 합니다


ALTER SESSION
ENABLE PARALLEL DML ;  -- 병령 DML 기능을 활성화합니다



INSERT /*+ PARALLEL */ INTO hr.sales3
NOLOGGING
SELECT *
FROM sh.sales ;  -- 2개의 서버프로세스가 입력을 수행합니다

COMMIT;



ALTER SESSION
DISABLE PARALLEL DML; -- 병령 DML을 비활성화합니다


ALTER TABLE hr.sales1
LOGGING ;

ALTER TABLE hr.sales2
LOGGING ;

ALTER TABLE hr.sales3
NOPARALLEL
LOGGING ; -- 원래 값으로 되돌려 놓습니다










-------------------------------------------------------------------------------------------------

<SQL*Loader를 이용한 데이터 로딩>


## SQL*Loader (sqlldr.exe)

	


conn hr/oracle4U -- hr 계정으로 접속합니다


CREATE TABLE hr.product_master
(product_id NUMBER(7) CONSTRAINT pk_pid PRIMARY KEY
,product_name VARCHAR2(50) NOT NULL
,code VARCHAR2(10) NOT NULL
,reorder_threshold NUMBER(5)
CONSTRAINT ckvalue CHECK (REORDER_THRESHOLD >
0)
,cost NUMBER(5,2)
,price NUMBER(5,2)
,primary_source VARCHAR2(50)
,secondary_source VARCHAR2(50)
,obsoleted DATE
)
TABLESPACE example ;  -- 테이블을 생성합니다





=====================================================================================
a000,Oracle Database 7.3,server,1,35.12,28.73,Redwood Shores,Reston,01-JAN-2000,
1041.6,Oracle Database 10g,server,25,45.45,14.32,Redwood Shores,,
1002,"Oracle9i Database",server,15,55.78,50.10,Redwood Shores,Reston,01-JAN-2000,
1003,Oracle8.0 Database,server,7.2,67.14,54.40,Redwood Shores,Reston,14-FEB-2001,
1004,Oracle Application Server 10g,server,25,92.87,89.13,Redwood Shores,Reston,
1005,Oracle Internet Application Server 9i,server,15,10.95,9.95,Redwood Shores,Reston,
1006,Oracle JDeveloper,tools,5,78.78,81.15,Redwood Shores,
1007,Oracle Developer,tools,10,32.32,30.22,Redwood Shores,Reston,
1008,Oracle Reports,tools,3,45.21,40.18,Redwood Shores,Reston,
1009,Oracle Discoverer,tools,7,12.47,10.69,Redwood Shores,Reston,
1010,Oracle Collaborations Suite,server,25,97.32,90.12,Redwood Shores,Reston,
1011,Oracle Real Application Clusters,server,30,7.21,6.15,Redwood Shores,Reston,
1012,Oracle Financial Applications,apps,8,1.99,0.87,Redwood Shores,Reston,
1013,Oracle Human Resource Applications,apps,9,92.87,89.14,Redwood Shores,Reston,
1014,Oracle Business Intelligence,apps,11,104.21,72.34,Redwood Shores,Reston,
1015,Oracle Maintenance Management,apps,14,12.31,8.14,Redwood Shores,Reston,
1016,Oracle Manufacturing,apps,3,34.56,34.55,Redwood Shores,Reston,
1017,Oracle Order Management,apps,7,56.67,56.72,Redwood Shores,Reston,
1018,Oracle Procurement,apps,16,67.78,60.01,Redwood Shores,Reston,
1019,Oracle Marketing and Sales,apps,9,78.89,75.97,Redwood Shores,Reston,
1020,Oracle Project Management,apps,10,12.23,11.79,Redwood Shores,Reston,
1021,Oracle Inventory Optimization,apps,2,23.34,12.14,Redwood Shores,Reston,
1022,Oracle Supply Chain Management,apps,1,34.45,31.63,Redwood Shores,Reston,
1023,Oracle Forms,tools,19,45.56,41.75,Redwood Shores,Reston,
1024,Oracle Depot Repair,apps,2,56.67,49.34,Redwood Shores,Reston,
1025,Oracle Tutor,apps,1,67.78,61.17,Redwood Shores,Reston,
1026,Oracle iStore,apps,9,78.89,75.00,Redwood Shores,Reston,
1027,Oracle Outsourcing,services,3,89.90,85.90,Redwood Shores,Reston,
1028,Oracle Consulting,services,35,12.23,12.14,Redwood Shores,Reston,
1029,Oracle University,services,50,23.34,21.23,Redwood Shores,Reston,
1030,Oracle Support,services,32,18.74,17.55,Colorado Springs,
,,,,,,,

=======================================================================================
-- 해당 내용을 저장해서 loadtest 폴더에 loadtest.csv로 저장합니다 (===는 빼고)





--======================================================
LOAD DATA
INFILE 'C:\Users\buk213\loadtest\loadtest.csv'   -- sqlldr이 입력할 데이터파일 
BADFILE 'sample.bad'		-- 형식이 맞지 않는 파일은 sample.bad 파일에 저장
DISCARDFILE 'sample.dsc'	-- 테이블에 정의된 제약조건에 위반된 파일은 sample.dsc에 저장
INTO TABLE hr.product_master
APPEND     -- APPEND, INSERT, REPLACE, TRUNCATE...
--WHEN (code = 'server') -- 라인주석
FIELDS TERMINATED BY ','     -- 필드 구분자
OPTIONALLY ENCLOSED BY '"'   -- "ORACLE" 같이 감싸는 경우를 인식합니다
TRAILING NULLCOLS      -- 필드가 부족하면 NULL 값으로 대체합니다
(product_id integer external ,
product_name "upper(:product_name)",   -- 전부 대문자화해서 입력합니다
code char(10),
reorder_threshold,
cost,   -- 안 적어주면 서버가 알아서 해석합니다 (적어주는게 좋습니다) 
price,
primary_source char(50),
secondary_source char(50),
obsoleted date(11) "DD-MON-YYYY" "nvl(:obsoleted, sysdate)"  -- 값이 없으면 null 필드 대신 sysdate를 입력합니다
)
--======================================================
-- SQL*Loader용 컨트롤 파일을 작성합니다 loadtest1.ctl





cmd> sqlldr.exe system/oracle4U@orcl ^
control=C:\Users\buk213\loadtest\loadtest1.ctl ^
errors=10000 -- SQL*Loader를 실행합니다
			 -- 10000개까지의  허용 오류 로그를 저장합니다







conn hr/oracle4U

set pagesize 50000
SELECT *
FROM hr.PRODUCT_MASTER
WHERE rownum=1;  

SELECT count(*) FROM hr.product_master ;  -- 제대로 입력됐는지 확인합니다





	# loadtest1.ctl 이 있는 폴더에 여러가지 로그파일들이 생성됐습니다
		# sample.bad
		# sample.dsc
		# loadtest1.log : 여러가지 결과 로그들이 저장돼있습니다










	# 데이터 로드를 빠르게 하는 방법
		# Conventional Path load 
			
			# 하이워터마크(HWM) 블록 이전에서 작업합니다
			# 일반적인 INSERT 문과 같습니다
			# 데이터로딩 동안 다른 사용자들이 테이블 기존 데이터를 수정할 수 있습니다
			# 리두로그를 생성합니다


		# Direct Path load  : 'direct=y' 를 명시합니다 
			
			# HWM 이후에 블록에 직접 저장해서 속도가 빠릅니다
			# 로딩 중 다른 세션의 DML 작업이 안됩니다 
			# FOREIGN KEY와 CHECK 제약조건은 검사하지 않습니다
			# 작업 전 적절한 저장공간을 미리 확보해주는 것이 권장됩니다
			# 리두로그가 NOARCHIVELOG 모드이면 생성하지 않습니다








--실습 다시 시작

conn hr/oracle4U


ALTER TABLE hr.product_master NOLOGGING ; -- 리두로그 생성을 줄이기 위해 NOLOGGING 설정을 합니다





col CONSTRAINT_NAME for a15
col SEARCH_CONDITION for a45
SELECT constraint_name, constraint_type, search_condition
FROM user_constraints
WHERE table_name= 'PRODUCT_MASTER' ; -- 테이블의 제약조건을 확인합니다



ALTER TABLE hr.product_master
DISABLE CONSTRAINT ckvalue ; -- check 제약조건을 disable 시킵니다



cmd> sqlldr.exe system/oracle4U@orcl ^
control=/u02/app/lab/loadtest/loadtest1.ctl ^
direct=y errors=10000



ALTER TABLE hr.product_master
LOGGING ;  -- LOGGING 설정을 합니다


ALTER TABLE hr.product_master
ENABLE CONSTRAINT ckvalue ; -- 제약조건을 ENABLE 합니다














--------------------------------------------------------------------------------------------------

<데이터베이스 LINK 및 데이터 이동>

## 데이터베이스 LINK 및 DATA 이동
		
	# 데이터베이스 LINK 는 전에 다 했다고 합니다



	# DATA 이동
		# DATA LOAD (데이터 로드) : 많은 데이터를 테이블에 입력하는것을 말합니다
		# DATA UNLOAD (데이터 언로드) : 많은 데이터를 테이블에서 추출하는것을 말합니다


		1. SQL*Loader
			# 데이터를 로딩할 때 사용합니다

			# 다른 Oracle DB나 다른 Vender(MYSQL, MSSQL, DB2) 등의 데이터를 표준 텍스트 형식으로 변환된 파일을 로딩할 때 사용합니다

	
		2. Sub-query를 이용한 DIRECT PATH LOADING
			# 다른 Oracle DB에서 서브쿼리로 바로 로딩(INSERT) 합니다


		3. ORACLE_LOADER 엔진을 사용하는 외부테이블로 데이터 이동
			# SQL*LOADER의 기능을 보완했습니다
		

		4. Datapump export/import로 데이터 이동
			# 서로 다른 Oracle DB간에 데이터 이동 (로드/언로드)를 할 때 사용합니다
			

		5. ORACLE_DATAPUMP 엔진을 사용하는 외부테이블로 데이터 이동
			# 서브쿼리를 테이블행이 아닌 원하는 데이터로 추출/삽입할 수 있어서 매우 유용하게 사용됩니다
			#










--------------------------------------------------------------------------------------------------

<DBCA를 사용해 prod 데이터베이스 생성>

## DBCA를 사용해 prod 데이터베이스 생성 
	# 기존의 연습용 orcl 데이터베이스는 사용하지 않는 많은 데이터들이 들어있습니다
	# 실전에서 사용할 가벼운 DB를 생성합니다




conn sys/oracle4U@orcl as sysdba  -- orcl SID로 접속합니다

conn sys/oracle4U@prod as sysdba  -- prod 계정으로 접속합니다

show parameter db_name -- SID를 확인합니다






