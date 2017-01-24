
<값기준 감사 (Value-based Auditing)>


## 값기준 감사 (Value-based Auditing)
	
	# DML 문장에 의해 변경되기 전 값들은 표준 데이터베이스 검사로 알 수 없습니다
	
	
	# LOG-MINER 라는 내장패키지를 이용해 아카이브 로그, ONLINE 로그파일을 분석해서 변경 전 값을 알 수 있습니다
		# 하지만 이 방법은 시간이 오래 걸립니다


	
	# PL/SQL 패키지인 TRIGGER 라는 프로그램을 사용해 값기반 검사를 할 수 있습니다








CREATE TABLE hr.employees_audit_target
AS
SELECT employee_id, last_name, salary
FROM hr.employees ;  -- 실습용 테이블을 생성합니다


SELECT *
FROM hr.employees_audit_target ; -- 테이블 데이터를 확인합니다








CREATE TABLE system.audit_employees
(hostuser VARCHAR2(150), 
hostname VARCHAR2(150), 
dbuser VARCHAR2(150), 
ipaddr VARCHAR2(30), 
mod_date TIMESTAMP(0) WITH TIME ZONE, 
old_empno NUMBER(6), 
old_lname VARCHAR2(30), 
old_salary NUMBER(8,2), 
new_empno NUMBER(6), 
new_lname VARCHAR2(30), 
new_salary NUMBER(8,2) 
)TABLESPACE example ; -- TRIGGER 프로그램으로 변경전/후 값이 저장될 테이블을 생성합니다









CREATE OR REPLACE TRIGGER system.hrsalary_audit
AFTER UPDATE OR DELETE OR INSERT ON hr.employees_audit_target
FOR EACH ROW
BEGIN
INSERT INTO system.audit_employees
VALUES (sys_context('userenv','os_user')
,sys_context('userenv','host')
,sys_context('userenv','session_user')
,sys_context('userenv','ip_address') -- 해당 사용자의 ip, hostname, user 이름등을 추출합니다
,systimestamp
,:old.employee_id
,:old.last_name
,:old.salary
,:new.employee_id
,:new.last_name
,:new.salary );
END;
/  -- TRIGGER를 통해 Value-based auditing을 수행합니다






conn hr/oracle4U


SELECT employee_id, salary
FROM hr.employees_audit_target
WHERE employee_id= 198;   -- 변경 전 데이터 값을 확인


UPDATE hr.employees_audit_target
SET salary= 3000
WHERE employee_id= 198 ;  -- 데이터를 변경합니다


COMMIT; 


SELECT employee_id, salary
FROM hr.employees_audit_target
WHERE employee_id= 198; -- 변경 후 데이터를 확인합니다









conn / as SYSDBA



ALTER SESSION SET
nls_timestamp_tz_format='YYYY/MM/DD HH24:MI:SS TZR' ;


col hostuser format a8
col dbuser format a8
col hostname format a10
col IPADDR format a15
col mod_date format a27
col old_lanme format a15
col new_lanme format a15
SELECT *
FROM system.audit_employees ; -- TRIGGER에 의해 입력된 행을 확인합니다



UPDATE hr.
employees_audit_target
SET salary= 2600
WHERE employee_id= 198 ; -- 위의 테이블로 확인했으면 다시 값을 되돌립니다


COMMIT;







SELECT owner, trigger_name
FROM dba_triggers
WHERE table_owner='HR'
AND table_name = 'EMPLOYEES_AUDIT_TARGET' ; -- 삭제되는 테이블에 종속적인 TRIGGER를 확인합니다



set long 5000
SELECT DESCRIPTION, TRIGGER_BODY
FROM dba_triggers
WHERE trigger_name = 'HRSALARY_AUDIT'
AND owner='SYSTEM' ;  -- 트리거 소스코드를 확인합니다





DROP TABLE hr.employees_audit_target PURGE ; -- 사용자 테이블을 삭제하면 TRIGGER도 같이 삭제됩니다


DROP TABLE system.audit_employees PURGE ; -- TRIGGER만 삭제합니다















-----------------------------------------------------------------------------------------------	

<SYSDBA 감사>

## SYSDBA 감사

	# sysdba 권한의 계정은 일반적으로 감사되지 않습니다
	# 관리자가 여러명일 때 주로 사용합니다

	

	# AUDIT_SYS_OPERATORS 초기화 파리미터
		# DEFAULT : false 입니다











show parameter audit_sys_operations -- 해당 파라미터의 값을 확인합니다



ALTER SYSTEM SET
audit_sys_operations=true SCOPE=spfile ; -- 파라미터 값을 TRUE로 설정합니다


SHUTDOWN IMMEDIATE

STARTUP







SELECT file_name FROM dba_data_files ;

SELECT count(*) FROM hr.employees ;

show parameter audit_file_dest

desc hr.departments  -- 해당 SQL 구문들을 실행합니다


SHUTDOWN IMMEDIATE

STARTUP


cmd> start c:\app\buk213\admin\orcl\adump\orcl_ora_3884_1.xml	-- 생성된 파일들에 정상적으로 기록이 됐는지 확인합니다







ALTER SYSTEM SET
audit_sys_operations=false SCOPE=spfile; -- sysdba 감사 설정을  해제합니다

SHUTDOWN IMMEDIATE

STARTUP












-----------------------------------------------------------------------------------------------	
<Fine-Grained Auditing 감사>

## FGA 감사 (9i)
	
	# Fine-Grained : 행 및 컬럼 레벨을 의미합니다

	# 특정 조건을 만족하는 행 및 SQL 문장에서 특정 컬럼이 있는 경우만 저장합니다
	
	# 표준-데이터베이스 감사보다는 감사기록의 양이 줄어듭니다

	# PL/SQL 패키지인 DBMS_FGA 프로그램을 이용해 수행합니다

	# SYS.FGA_LOG$ 테이블 또는 AUDIT_FILE_DEST 설정에 지정된 경로에 XML 형식으로 기록됩니다


	# DBA_AUDIT_POLICIES 딕셔너리 뷰











BEGIN
DBMS_FGA.ADD_POLICY(
policy_name => 'audit_emp_sal',
object_schema => 'HR',
object_name => 'employees',
audit_condition => 'department_id = 30',
audit_column => 'last_name,salary',
statement_types => 'SELECT,UPDATE,DELETE',
enable => true);
END ;
/ --select, update, delete 구문, last_name, salary 컬럼, department_id 컬럼 값이 30인 경우만 감사를 기록합니다







col OBJECT_SCHEMA format a5
col OBJECT_NAME format a15
col POLICY_OWNER format a5
col POLICY_NAME format a15
col POLICY_TEXT format a20
col POLICY_COLUMN format a20
SELECT OBJECT_SCHEMA
,OBJECT_NAME
,POLICY_OWNER
,POLICY_NAME
,POLICY_TEXT
,POLICY_COLUMN
,ENABLED, SEL, INS, UPD, DEL
,AUDIT_TRAIL
FROM dba_audit_policies ;   -- FGA 정책이 제대로 설정됐는지 확인합니다






SELECT employee_id, last_name, department_id
FROM hr.employees
WHERE department_id=20 ;



SELECT employee_id, department_id
FROM hr.employees
WHERE department_id=30 ;


set pagesize 500
SELECT employee_id, salary, department_id
FROM hr.employees ;



SELECT employee_id, salary, department_id
FROM hr.employees
WHERE last_name = 'Raphaely' ;   -- 여러가지 SQL문을 실행합니다 






set pagesize 200
set linesize 200
col DB_USER format a10
col OS_USER format a10
col USERHOST format a10
col TIMESTAMP format a15
col SQL_TEXT format a50
SELECT to_char(timestamp, 'RR/MM/DD HH24:MI') as timestamp,
db_user, os_user, userhost, sql_text
FROM dba_fga_audit_trail ;   -- DBA_FGA_AUDIT_TRAIL 딕셔너리 뷰에   FGA_AUDIT 기록을 확인합니다




set pagesize 200
set linesize 200
col DB_USER format a10
col OS_USER format a10
col USERHOST format a10
col TIMESTAMP format a15
col SQL_TEXT format a50
SELECT to_char(EXTENDED_TIMESTAMP, 'RR/MM/DD HH24:MI')
as timestamp,
db_user, os_user, userhost, sql_text
FROM dba_common_audit_trail
WHERE UPPER(sql_text) LIKE 'SELECT%' ; -- DBA_COMMON_AUDIT_TRAIL에도 결과가 생겼는지 조회합니다





execute DBMS_FGA.DISABLE_POLICY( -
policy_name => 'audit_emp_sal', -
object_schema => 'HR', -
object_name => 'employees') ; -- 해당 FGA 감사를 DISABLE합니다 



execute DBMS_FGA.ENABLE_POLICY(- 
policy_name => 'audit_emp_sal',-
object_schema => 'HR', -
object_name => 'employees') ; -- 해당 FGA 감사를 다시 ENABLE 시킵니다




execute DBMS_FGA.DROP_POLICY( -
policy_name => 'audit_emp_sal',- 
object_schema => 'HR', -
object_name => 'employees') ; -- 해당 FGA 감사를 삭제합니다















-----------------------------------------------------------------------------------------------	
<표준 데이터베이스 감사>

## 표준 데이터베이스 감사
	# 언제, 누가, 무엇을 했는지 SQL문을 통해 알 수 있습니다
	
	# SYSDBA 권한을 가진 계정은 모니터링되지 않습니다

	# DBCA를 이용해 데이터베이스를 만들면 기본적으로 활성화돼있습니다 (11g)

		# DB를 초기에 생성해서 감사기록을 쓰지 않을 경우

			NOAUDIT ALL;
			NOAUDIT ALL PRIVILEGES;
			NOAUDIT EXEMPT ACCESS POLICY;
			ALTER SYSTEM SET audit_trail = 'NONE'
			shutdown IMMEDIATE
			STARTUP 






	# 'AUDIT_TRAIL' 초기화파라미터
		# NONE : 감사기능을 사용하지 않습니다
		# OS : 
		# DB : 표준 데이터베이스 감사기능을 사용합니다 (aud$에 감사기록이 저장됩니다)
		# XML : 위와 같고 xml 형식으로 저장됩니다
		# DB, EXTENDED : DB와 같지만 SQL 문장의 모든 정보까지 저장합니다
		# XML, EXTENDED : 위와 같고 xml 형식으로 저장합니다



		# DBCA를 통해 데이터베이스를 만들면 기본값이 DB로 설정됩니다. 
		
		# SYS.AUD$ 테이블에 감사기록이 저장됩니다
			# SYSTEM-테이블스페이스 크기가 너무 커지므로 적절하게 백업 후 삭제해야합니다




	# 감사-옵션을 설정하는 3가지 방법
		# 문장 AUDITING : SQL 문장이 실행될 때마다 기록합니다
		
		# 시스템권한 AUDITING : 시스템권한이 사용되면 기록합니다
		
		# 객체 권한 AUDITING : 특정 객체의 객체권한이 사용되면 기록합니다
	
		# +@ 

			# BY ACCESS : DML 문장이 실행될 때마다 감사기록이 저장됩니다

			# BY SESSION : 동일한 DML 문장이 한번만 기록됩니다 (잘 사용하지 않습니다)

			# WHENEVER SUCCESSFUL : SQL 문장이 성공할 때만 기록합니다











===========================================================
ALTER ANY PROCEDURE ALTER ANY TABLE
ALTER DATABASE ALTER PROFILE
ALTER SYSTEM ALTER USER
AUDIT SYSTEM CREATE ANY JOB
CREATE ANY LIBRARY CREATE ANY PROCEDURE
CREATE ANY TABLE CREATE EXTERNAL JOB
CREATE PUBLIC DATABASE LINK CREATE SESSION <????
CREATE USER DROP ANY PROCEDURE
DROP ANY TABLE DROP PROFILE
DROP USER EXEMPT ACCESS POLICY
GRANT ANY OBJECT PRIVILEGE GRANT ANY PRIVILEGE
GRANT ANY ROLE
=========================================================== 
-- 다음의 시스템권한이 auditing 됩니다



===========================================================
ALTER ANY PROCEDURE ALTER ANY TABLE
ALTER DATABASE ALTER PROFILE
ALTER SYSTEM ALTER USER
CREATE ANY JOB CREATE ANY LIBRARY
CREATE ANY PROCEDURE CREATE ANY TABLE
CREATE EXTERNAL JOB CREATE PUBLIC DATABASE LINK
CREATE SESSION CREATE USER
DATABASE LINK DROP ANY PROCEDURE
DROP ANY TABLE DROP PROFILE
DROP USER EXEMPT ACCESS POLICY
GRANT ANY OBJECT PRIVILEGE GRANT ANY PRIVILEGE
GRANT ANY ROLE PROFILE
PUBLIC SYNONYM ROLE
SYSTEM AUDIT SYSTEM GRANT
=========================================================== 
-- 다음의 문장이 auditing 됩니다







		# 'DBA_COMMON_AUDIT_TRAIL' 딕셔너리 뷰 (10gNF)
			
			# 감사기록을 확인할 때 사용합니다
			
			# 아래 2개의 뷰의 내용을 한꺼번에 확인할 수 있습니다
				
				# DBA_AUDIT_TRAIL 딕셔너리 뷰 : 표준 데이터베이스 감사기능으로 저장된 감사기록 정보를 제공합니다
				# DBA_FGA_AUDIT_TRAIL 딕셔너리 뷰 : FIND-GRAINED AUDIT 기능으로 저장된 감사기록 정보를 확인합니다 













show parameter audit_trail -- 해당 파라미터 값을 확인합니다




CREATE TABLE system.audit_std_trail_old
TABLESPACE users
AS
SELECT * FROM SYS.AUD$ ; -- sys.adu$ 데이터를 백업할 테이블을 생성합니다



INSERT /* +APPEND */ INTO system.audit_std_trail_old
SELECT * FROM SYS.AUD$ ; -- sys.aud$의 데이터를 백업합니다


TRUNCATE TABLE SYS.AUD$ ; -- sys.aud$ 테이블을 TRUNCATE 합니다





		# 실습 시작





show parameter audit_trail 


SELECT count(*) FROM SYS.AUD$; -- AUD$ 테이블에 기록된 행들을 확인합니다




ALTER SYSTEM SET
audit_trail='XML','EXTENDED' SCOPE=spfile ; -- 해당 파라미터를 XML, EXTENDED로 변경합니다



TRUNCATE TABLE SYS.AUD$ ; -- aud$ 테이블을 TRUNCATE 시킵니다





SHUTDOWN IMMEDIATE

STARTUP

show parameter audit_trail -- 시스템 재시작 후 파라미터를 확인합니다





NOAUDIT ALL ; -- 모든 문장 감사 옵션을 해제합니다

NOAUDIT ALL PRIVILEGES ; -- 시스템 권한 감사를 해제합니다

NOAUDIT EXEMPT ACCESS POLICY ; -- EXEMPT 시스템 감사를 해제합니다





set pagesize 5000
col user_name format a6
col privilege format a30
SELECT user_name, privilege, success, failure
FROM dba_priv_audit_opts ; -- 해제된 감사 옵션을 확인합니다 (없다고 나와야 정상)




set pagesize 5000
col user_name format a6
col privilege format a30
col audit_option format a27
SELECT user_name, audit_option, success, failure
FROM dba_stmt_audit_opts
ORDER BY 1, 2 ; -- 해제된 감사 옵션을 확인합니다 (없다고 나와야 정상)




AUDIT TABLE
BY HR
BY ACCESS
WHENEVER SUCCESSFUL ; -- 테이블 키워드가 들어간 문장을 성공할 때마다 감사를 합니다



AUDIT DROP ANY TABLE, SELECT ANY TABLE
BY HR, SYSTEM
BY ACCESS
WHENEVER SUCCESSFUL ; -- drop any table, select any table 일 때 감사를 합니다



AUDIT connect
BY hr, system
BY ACCESS
WHENEVER SUCCESSFUL ;  -- hr, system 계정이 connect 롤을 사용할 때마다 감사를 합니다




AUDIT UPDATE, DELETE
ON HR.DEPARTMENTS
BY SESSION
WHENEVER SUCCESSFUL ; -- update, delete 를 할때마다 감사를 합니다 (by session)



AUDIT UPDATE, DELETE, SELECT, INSERT
ON HR.EMPLOYEES
BY ACCESS ; -- hr.employees 테이블에 update ,delete, select, insert 구문에 감사를 합니다





set pagesize 5000
col user_name format a6
col privilege format a20
SELECT user_name, privilege, success, failure
FROM dba_priv_audit_opts
WHERE user_name IN ('HR','SYSTEM')
ORDER BY 1, 2 ;  -- 현재 설정된 감사 옵션을 확인합니다








GRANT select ANY TABLE
TO hr; -- hr에게 select any table 권한을 줍니다




REVOKE all
ON scott.dept
FROM hr ;  -- hr에게서 scctt.dept 테이블에 모든 권한을 뺏습니다







conn hr/oracle4U


CREATE TABLE hr.test01
AS
SELECT *
FROM hr.departments ;  -- 테이블을 만들고


TRUNCATE TABLE hr.test01 ; -- 자르고

DROP TABLE hr.test01 ;  -- 삭제합니다



SELECT *
FROM scott.dept
WHERE deptno=10 ;



SELECT *
FROM scott.dept
WHERE deptno=10 ; -- 같은 select문을 2번 실행합니다




UPDATE hr.departments
SET department_name = 'Oracle'
WHERE department_id =250 ;



UPDATE hr.departments
SET department_name = 'Oracle'
WHERE department_id =250 ;  -- update문도 2번 실행합니다



ROLLBACK; 롤백을 합니다








conn / as SYSDBA  -- 관리자로 접속해서




COL OBJECT_SCHEMA FORMAT A5
COL OBJECT_NAME FORMAT A15
COL DB_USER FORMAT A7
COL STATEMENT_TYPE FORMAT A15
COL EXTENDED_TIMESTAMP FORMAT A40
COL USERHOST FORMAT A8
COL SQL_TEXT FORMAT A40
SET LINESIZE 100
SET PAGESIZE 50000
SELECT extended_timestamp, object_schema, object_name,
db_user, userhost, sql_text, scn, transactionid,
action, statement_type
FROM sys.dba_common_audit_trail
WHERE UPPER(db_user) NOT IN ('DBSNMP', 'SYSMAN')
AND action NOT IN (0,100,101)
ORDER BY extended_timestamp ;  -- 위의 구문들을 통해 생성된 감사기록을 확인합니다





SELECT count(*) FROM sys.aud$ ; -- 감사기록의 행 수를 확인합니다 (실습전에 TRUNCATE시켜서 기록된 것이 없습니다)





SELECT *
FROM audit_actions ; -- sys.DBA_COMMON_AUDIT_TRAIL 딕셔너리 뷰의 ACTIO 컬럼과 STATEMENT_TYPE 컬럼의 항목을 확인합니다






set pagesize 5000
col user_name format a6
col privilege format a20
SELECT user_name, privilege, success, failure
FROM dba_priv_audit_opts
WHERE user_name IN ('HR','SYSTEM')
ORDER BY 1, 2 ; -- HR, SYSTEM 계정의 시스템 권한 감사옵션을 확인합니다




col audit_option format a25
SELECT user_name, audit_option, success, failure
FROM dba_stmt_audit_opts
WHERE user_name IN ('HR','SYSTEM')
ORDER BY 1, 2 ; -- HR, SYSTEM 계정의 문장 감사옵션을 확인합니다





SELECT owner, object_name, object_type, SEL, INS, UPD, DEL
FROM dba_obj_audit_opts
WHERE owner='HR' and object_name='DEPARTMENTS'
ORDER BY 1,2 ;  -- hr.departments 테이블에 걸린 객체 감사옵션을 확인합니다





SELECT owner, object_name, object_type, SEL, INS, UPD, DEL, LOC
FROM dba_obj_audit_opts
WHERE owner='HR' and object_name='EMPLOYEES'
ORDER BY 1,2 ; -- hr.employees 테이블에 걸린 객체 감사옵션을 확인합니다 (감사옵션은 pdf 파일 참고)





NOAUDIT connect
BY hr, system ; -- 해당 계정의 감사옵션을 해제합니다


NOAUDIT drop any table
,select any table
BY hr, system ; 


NOAUDIT ALL
ON hr.departments ;


NOAUDIT ALL
ON hr.employees ; 


NOAUDIT TABLE
BY hr ;  -- 위에서 설정한 감사옵션을 전부 해제합니다

























-----------------------------------------------------------------------------------------------	
<필수 감사 (Windows에서 안됨)>

## 필수 감사
	# 리눅스에서만 유효하고 윈도우에서는 수행되지 않습니다









		
-----------------------------------------------------------------------------------------------	
		
	$$ 11g 버전은 프로그램을 삭제할 때 deinstall 프로그램을 사용하면 됩니다 



<오라클 데이터베이스 감사(Audit)>


## 데이터베이스 감사(Audit)
	# 정해진 규칙을 토대로 벗어난 명령어를 한 사용자를 찾을 수 있습니다
		# 필수 감사 (Windows에서 안됨)
		# 표준 데이터베이스 감사
		# 값 기준 감사
		# FGA 감사
		# SYSDBA 감사 


	# AUDIT_FILE_DEST 초기화 파라미터
		# 모니터링 로그를 저장할 경로를 설정합니다



show parameter audit_file_dest -- 해당 파라미터 경로를 확인합니다

















































