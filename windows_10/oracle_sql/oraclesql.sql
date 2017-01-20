

<DATA Dictionary>

## 'DATA Dictionary'
	# 현재 접속한 계정이 사용할 수 있는 테이블 또는 뷰는 어떤것이 있을까?
	# 특정 뷰에 정의된 SELECT 뷰의 내용은 무엇일까?
	# ... 같은 궁금증을 가질 때 사용합니다


		# 'STATIC DATA DICTIONARY VIEW'
			# 디스크상 특정 데이터 딕셔너리 테이블에 저장돼있는 정보입니다
				# USER_TABLES : 현재 사용자의 테이블 정보를 제공합니다
				# ALL_TABLES : 
				# DBA_TABLES : DBA만 조회할 수 있습니다. 모든 테이블의 시스템 정보를 출력합니다


DESC dictionary; -- 데이터 딕셔너리 뷰의 컬럼정보를 확인할 수 있습니다
DESC USER_TABLES;
DESC DBA_TABLES;
DESC ALL_TABLES;  -- 해당 딕셔너리 정보를 얻을 수 있습니다




		# 'DYNAMIC PERFORMANCE VIEW (VS-VIEW)'
			# 이 뷰는 메모리에만 상주하고 저장되지 않습니다
			# 'V$' 로 시작합니다












-------------------------------------------------------------------------------------------------

<사용자 접근 제어 DCL>

	$$ 윈도우는 오라클을 거의 사용하지 않는다
		$ MAC은 아예 오라클을 쓸 수 있는 소프트웨어가 없다
		$ 전세계적으로 리눅스 + 오라클을 사용하는 추세이다
			$ REDHAT + ORACLE 을 주로 사용한다
			$ UBUNTU(DEBIAN) 계열은 아쉽지만 지원하지 않는다



## GRANT, REVOKE, SYS, SYSTEM...
	# 데이터베이스 객체를 만드는 권한을 부여하거나 제어할 수 있습니다	
		# SYS :
		# SYSTEM : 
			# GRANT : 사용자에게 권한을 부여합니다
				# UPDATE(department_id), REFERENCE(department_id) 둘은 컬럼을 정해줄 수 있습니다
				# SELECT, INSERT, DELETE 는 불가능합니다

			# REVOKE : 사용자의 권한을 제거할 수 있습니다






CREATE USER edward IDENTIFIED BY qwer1234; -- 사용자를 생성합니다, 계정과 패스워드는 30 BYTE를 넘으면 안됩니다
CREATE USER edward2 IDENTIFIED BY qwer1234; 



GRANT CREATE SESSION, CREATE TABLE, CREATE VIEW,
CREATE SEQUENCE, CREATE SYNONYM, ALTER SESSION
TO edward, edward2;  -- GRANT로 사용자에게 권한을 부여할 수 있습니다.
-- CRAETE TABLE 권한 외에도 DEFERRED_SEGMENT_CREATION이 FALSE로 되어있어야 테이블을 만들 수 있습니다


GRANT CREATE SESSION
TO PUBLIC ;   -- PUBLIC을 사용하면 모든 계정이 해당 권한을 사용할 수 있게 합니다



GRANT SELECT, INSERT, DELETE, ALTER, INDEX, UPDATE, REFERENCES
ON HR.LOCATIONS
TO HR1, HR2 ;   -- hr.locations 테이블의 권한을 해당 사용자들이 사용할 수 있게 합니다
				-- 오라클은 ON에 한 개의 테이블만 사용할 수 있습니다








	# 여러가지 권한들
		# 내가 만든 테이블은 나만 삭제할 수 있습니다
		# '시스템 권한'
			# DB Administrators 만 사용하는 계정에 부여되는 권한들

				# CREATE USER
				# DROP USER
				# BACKUP ANY TABLE
				# SELECT ANY TABLE
				# CREATE ANY TABLE
				# DROP ANY TABLE
			
			---------------------------------------------------------
			# 개발자들이 사용하는 계정에 부여되는 권한들
			
				# CREATE SESSION
				# ALTER SESSION
				# CREATE TABLE
				# CREATE SEQEUNCE
				# CREATE VIEW
				# CREATE DATABASE LINK
				# CREATE PROCEDURE
				# ...
		
		# '객체 권한' 
			# SELECT, DELETE, UPDATE, INSERT 를 액세스할 수 있는 권한들입니다
			# 보통은 ALL 을 입력해서 모든 권한을 한꺼번에 주지만 TABLE, VIEW 는 예외입니다


		# 'ROLE'
			# 권한을 바로 사용자에게 주면 사용자가 많아질수록 너무 복잡해지므로 ROLE이라는 걸 만들어 중간단계를 거쳐 체계적으로 관리합니다.
			
			# CONNECT-ROLE, RESOURCE-ROLE, DBA-ROLE... 등이 있습니다
			


CREATE ROLE EMPROLE1 ; -- 롤을 생성합니다 
GRANT CREATE SESSION, CREATE TABLE TO emprole1 ; -- 롤에 권한을 부여합니다










		# SQL*PLUS 사용법
			# cmd
			# sqlplus hr/oracle4U@orcl  (리스너를 통한 원격 접속)
			# conn edward/qwer1234@orcl



REVOKE REFERENCES
ON HR.DEPARTMENTS
FROM HR1 CASCADE CONSTRAINTS ; -- CASCADE CONSTRAINT를 이용해 FOREIGN KEY가 참조하는 삭제가 안됐던 테이블의 권한을 삭제할 수 있습니다


GRANT SELECT
ON HR.DEPARTMENTS
TO HR1
WITH GRANT OPTION ;  -- HR1도 GRANT 옵션을 가질 수 있습니다 (일터에선 보안때문에 절대로 쓰지 않습니다)






-------------------------------------------------------------------------------------------------

<오라클 데이터베이스 객체>

## VIEW, SEQUENCE, INDEX, SYNONYM...
	# VIEW 객체 
		# 사용자들의 데이터 ACCESS 권한을 제한해야 될 때 사용한다
			# 다른 사용자들은 VIEW 안에서 정의된 SELECT 레코드만 ACCESS 가능하다
			# 보안과 관련된 객체이다
			# DEFAULT 키워드를 사용할 수 없다

		# FORCE, WITH READ ONLY, WITH CHECK OPTION 을 이용해 옵션을 설정할 수 있다
			# FORCE : 컴파일 오류가 나도 강제로 VIEW 를 만든다 (거의 안쓰임)
			# WITH READ ONLY : VIEW 를 읽기전용으로 만든다 (거의 안쓰임)
			# WITH CHECK OPTION : VIEW 객체를 생성할 때 조건문같이 값을 검사할 수 있다


		# CREATE OR REPLACE VIEW 
			# VIEW 의 속성을 변경하고 싶을 때 사용한다
			# ANSI 표준과 다르다 (오라클만 사용)(다른 벤더는 전부 ALTER VIEW {...})



			

CREATE VIEW hr.sal30vw
AS
SELECT employee_id, first_name, salary
FROM hr.employees
WHERE department_id = 30 ;  -- 아래 SELECT 문이 컴파일되서 저장된 객체가 VIEW이다.



CREATE VIEW hr.dept_sal_vu
AS 
SELECT UPPER(d.department_name) NAME, MIN(e.salary) MINSAL, MAX(e.salary) MAXSAL, AVG(e.salary) AVGSAL 
FROM hr.employees e INNER JOIN hr.departments d
ON (e.department_id = d.department_id)
GROUP BY d.department_name;   -- INNER JOIN을 활용한 직원들의 봉급에 관해 VIEW 객체를 만든다



CREATE FORCE VIEW hr.empvu10 (employee_number, employee_name, job_title)
AS 
SELECT employee_id, last_name, job_id
FROM hr.employees111
WHERE department_id = 10
WITH READ ONLY ;  -- FORCE와 WITH READ ONLY를 이용해 읽기전용으로 만들 수 있다 (DML 사용불가)(잘 사용하진 않는다)



CREATE VIEW hr.empvu20
AS 
SELECT *
FROM hr.employees
WHERE department_id = 20 WITH CHECK OPTION ; -- WITH CHECK OPTION을 이용해 조건문같이 값을 검사할 수 있다. 



CREATE OR REPLACE VIEW hr.salvu50
AS 
SELECT employee_id AS ID_NUMBER, first_name || ' '|| last_name AS NAME,
salary AS SAL, department_id
FROM hr.employees
WHERE department_id = 50 ;  -- CREATE OR REPLACE VIEW 를 이용해 VIEW를 수정할 수 있다



DROP VIEW hr.sal30vw; -- VIEW를 삭제할 때 사용한다








	

	# 'SEQUENCE' 객체
		# 오라클에만 있는 객체이다.
		# 쇼핑몰사이트에서 주문번호와 같은 형태이다 (내가 입력하지 않았는데 자동으로 생성된 번호)	
		# PRIMARY KEY 값을 생성하는데 사용할 수 있다
			# NOCYCLE 옵션을 적용해야 한다
		
		# 메모리캐시(CACHE)를 이용해 처리속도를 향상시킬 수 있다 (DEFAULT 20)
		
		# 'NEXTVAL', 'CURRVAL'을 이용해 시퀀스를 호출할 수 있다
			# NEXTVAL : 세션에서 다음에 사용할 값을 호출한다
			# CURRVAL : 세션에서 사용한 마지막 시퀀스 값을 호출한다



INSERT INTO table_name
VALUES (sequence_name.NEXTVAL, TO_CHAR(SYSDATE,’YYYYMMDD’)||’_’||sequence_name.CURRVAL) ; -- 시퀀스를 호출하는 NEXTVAL, CURRVAL의 사용법




		# ROLLBACK 이 되지 않는다
			# 시스템이 재부팅되면 SEQUENCE 값이 이어지지 않을 수 있다

		# ALTER, DROP 을 사용해 시퀀스 값을 변경할 수 있다
			# START WITH 값은 ALTER로도 변경할 수 없다





CREATE SEQUENCE hr.dept_deptid_seq1 ; -- 시퀀스 객체를 생성한다



CREATE SEQUENCE hr.dept_deptid_seq2
START WITH 500   -- 500에서 시작한다
INCREMENT BY 10  -- 10씩 증가한다
MAXVALUE 9999    -- 최대값은 9999
MINVALUE 500     -- 최소값은 500 (다시 시작할때 500부터 시작한다)
NOCACHE  -- 메모리 캐시를 사용하지 않는다
CYCLE ;  -- CYCLE을 이용해 반복한다    



CREATE SEQUENCE hr.dept_deptid_seq3
START WITH 500
INCREMENT BY 10
MAXVALUE 9999
--MINVALUE 500
CACHE 10  -- 메모리 캐시를 사용한다 (DEFAULT값은 20)
NOCYCLE ; -- 주기를 반복하지 않는다



ALTER SEQUENCE DEPT_DEPTID_SEQ1 CACHE 1000000 ; -- 메모리캐시 값을 변경할 수 있다


DROP SEQUENCE hr.dept_deptid_seq1 ; -- 시퀀스를 삭제할 수 있다 









	# INDEX 객체
		# 디스크 I/O 횟수를 줄여서 SQL문의 처리 성능을 향상시킬 수 있다.
		# 오라클 서버가 알아서 관리한다
			# ROWID 
				# 오라클 서버가 식별하기 위해 자체적으로 만든 고유의 값이다
				# 6글자(테이블이름), 3글자(파일번호), 6글자(블록번호),  3글자(블록의 위치)
				# 이 정보를 기반을 INDEX 를 사용한다.
				# ROWID + INDEX KEY 값을 이용해 정렬한다


		# 'FULL TABLE SCAN' vs 'INDEX SCAN'
			# 무조건 INDEX SCAN을 쓴다고 빨라지는건 아니다
			# 많은 행을 가지고 있는 테이블 + query 로 2% ~ 4% 미만의 데이터를 추출할 걸로 예상되는 경우 INDEX를 사용하면 좋다
		

		# PRIMARY KEY, UNIQUE 를 입력하면 자동으로 INDEX 가 생성된다
			# 이 KEY들은 삭제할 수 없다 (DROP INDEX 불가능)


		# 데이터 I/O를 따져서 INDEX 를 사용하고 싶지 않으면
			WHERE + 컬럼 || '';  -- 문자데이터의 경우
			WHERE + 컬럼 + 0;    -- 숫자데이터의 경우







SELECT ROWID, employee_id, last_name from hr.employees; -- 6/3/6/3 로 나눠진 ROWID를 볼 수 있다. AAAR5K/AAF/AAAADL/AAA


CREATE INDEX hr.idx_lname_emp ON hr.employees(last_name) ;  -- INDEX를 만든다


SELECT * FROM hr.employees WHERE UPPER(last_name)='KING' ; -- WHERE에 함수를 사용하면 INDEX를 사용할 수 없다. 강제로 FULL TABLE SCAN을 한다


DROP INDEX hr.idx_lname_emp ; -- INDEX를 삭제한다

















	# SYNONYM 객체
		# 여러 분산된 DB 서버에서 데이터를 조합해 얻고 싶을 때 이름을 많이 적게되는데 이를 줄이기 위해 사용한다
		# 일반 동의어 (Normal Synonym) : 나만 사용가능한 동의어
		# 공용 동의어 (Public Synonym) : 모든 로그인계정이 사용가능한 동의어 (DBA만 만들 수 있다)

		# ALTER 가 존재하지 않는다 DROP 은 존재함
			



CREATE SYNONYM hr.emp_syn FOR hr.employees ;  -- 일반 동의어를 만든다

CREATE PUBLIC SYNONYM dept_pusyn FOR hr.departments ; -- 공용 동의어를 만든다



SELECT last_name
FROM hr.emp_syn
WHERE department_id = 90 ;  -- hr.employees 대신 hr.emp_syn을 사용할 수 있다


DROP PUBLIC SYNONYM dept_pusyn ;  -- SYNONYM을 삭제한다














--------------------------------------------------------------------------------------------------

<테이블 속성 변경 및 삭제>

## ALTER AND DROP
	# ALTER TABLE
		# 테이블 속성을 변경한다	

		ALTER TABLE hr.department READ ONLY;  -- 테이블을 읽기전용으로 만든다 (값 변경 불가능)
		ALTER TABLE hr.department READ WRITE;


	# DROP TABLE 
		# 삭제된 테이블은 휴지통으로 이동한다 (오라클에만 있는 기능)
		# 삭제된 테이블은 자동 COMMIT 되어 ROLLBACK 되지 않는다 

		DROP TABLE hr.dept70;
		DROP TABLE hr.dept70 PURGE; -- PURGE를 이용해 휴지통에 저장하지 않고 영구 삭제한다 (오라클에만 있는 기능)









-------------------------------------------------------------------------------------------------

<TRUNCATE 를 이용한 테이블 데이터 삭제>


## TRUNCATE VS DELETE 
	# TRUNCATE : 테이블을 초기 상태로 변경한다 (UNDO 데이터를 만들지 않는다)
		# 자동 COMMIT 되므로 ROLLBACK 이 불가능하다
		# FOREIGN KEY로 참조당하는 테이블은 TRUNCATE 되지 않는다


	# DELETE : WHERE 절 없이 쓰면 똑같이 테이블 모든 데이터를 삭제한다 (UNDO 데이터를 만든다)
		# ROLLBACK 이 가능하다 



TRUNCATE TABLE hr.employees3 ;








--------------------------------------------------------------------------------------------------

<서브쿼리를 이용한 테이블 생성>

## CREATE TABLE + SUB-QUERY
		# NOT NULL 을 제외한 제약조건 PRIMARY KEY, FOREIGN KEY, UNIQUE...는 복사되지 않는다



CREATE TABLE hr.dept70
AS
SELECT employee_id, last_name as ENAME, salary*12 ANNSAL, hire_date hiredate
FROM hr.employees
WHERE department_id = 70 ; -- AS 명령어를 이용해 서브쿼리를 이용할 수 있다


CREATE TABLE hr.dept80 (empno, ename, annsal, hiredate)
AS
SELECT employee_id, last_name, salary*12, hire_date
FROM hr.employees
WHERE department_id = 80 ;  -- 서브쿼리를 사용한 예문












--------------------------------------------------------------------------------------------------

<제약 조건>


## 'CONSTRAINT'
	# NOT NULL, UNIQUE, PRIMARY KEY, FOREIGN KEY, CHECK...
		# NOT NULL : NULL 값이 입력되면 안되는걸 의미한다
		# UNIQUE  : 같은 값이 중복되면 안되는걸 의미한다
		# PRIMARY KEY : NOT NULL + UNIQUE 가 합쳐진 고유키값을 의미한다
		# FOREIGN KEY : PRIMARY KEY와 같이 사용되며 값을 입력할 때 PRIMARY KEY를 보고 판단한다
			# FOREIGN KEY에 의해 참조되는 PRIMARY KEY는 지울 수 없다.

		# CHECK : 여러가지 제약조건을 만들 수 있다



CREATE TABLE hr.emps91
(eid NUMBER(4)
,name VARCHAR2(4) CONSTRAINT nn_name_emps91 NOT NULL
,address VARCHAR2(30) DEFAULT 'SEOUL'
,salary NUMBER(8)
,jumin VARCHAR2(13) NOT NULL
,deptid NUMBER(4)
,CONSTRAINT pk_eid_name_emps91 PRIMARY KEY(eid, name)
,CONSTRAINT uk_jumin_emps91 UNIQUE(jumin)
,CONSTRAINT ck_sal_addr_emps91 CHECK(salary > 0 and address is not null)
,CONSTRAINT fk_emps_dept91 FOREIGN KEY(deptid) 
REFERENCES hr.departments(department_id) ON DELETE SET NULL ); -- 테이블레벨로 제약조건을 포함한 DDL 문장이다. (제약조건이 문장 아래에 몰려있음)
-- CONSTARINT {...} 는 뺴도 괜찮으나 적어주는게 가독성을 위해서 좋다
-- PRIMARY KEY(eid,name)는 복합키 형태이다
-- FOREIGN KEY는 REFERENCES {...} 과 같이 사용한다





CREATE TABLE hr.emps92
( empid NUMBER(6) CONSTRAINT emp92_emp_id PRIMARY KEY
, f_name VARCHAR2(20)
, l_name VARCHAR2(25) CONSTRAINT emp92_last_name_nn NOT NULL
, email VARCHAR2(25) CONSTRAINT emp92_email_nn NOT NULL
CONSTRAINT emp92_email_uk UNIQUE
, phone_no VARCHAR2(20)
, hire_date DATE CONSTRAINT emp92_hire_date_nn NOT NULL
, job_id VARCHAR2(10) CONSTRAINT emp92_job_nn NOT NULL
, salary NUMBER(8,2) CONSTRAINT emp92_salary_ck CHECK (salary>0)
, comm_pct NUMBER(2,2)
, manager_id NUMBER(6)
, dept_id NUMBER(4) CONSTRAINT emp92_dept_fk
REFERENCES hr.departments (department_id) ON DELETE CASCADE);  -- 컬럼레벨로 제약조건을 정의한 모습이다
-- FOREIGN KEY는 컬럼레벨에서는 적지 않아도 된다 .



				# FOREIGN KEY에서 
					# 아무것도 없으면 PRIMARY KEY를 지울 수 없다
                    # ON DELETE SET NULL : 해당 PRIMARY KEY를 지울 수 있고 해당 FOREIGN KEY 값이 NULL로 바뀐다.
					# ON DELETE CASCADE  : 해당 PRIMARY KEY를 지울 수 있고 해당 FOREIGN KEY 값이 삭제된다.















--------------------------------------------------------------------------------------------------

<사용자 데이터 정의 명령어 DDL>



## 'DATA DEFINITION LANGUAGE', 'DDL'
	# 데이터베이스 정의 명령어 'CREATE', 'ALTER', 'DROP'...
		# 'CREATE' : 테이블 생성


CREATE TABLE tablename(
...
...
...
);   -- CREATE TABLE 구문을 이용해 테이블을 만든다
	 -- 일반적으로 테이블은 대소문자를 구문하지 않는다 (오라클 only)




			# DEFAULT 키워드

CREATE TABLE dept(
deptno number(2),
dname varchar2(14),
loc varchar2(13),
create_date date DEFAULT sysdate); -- DEFAULT 값을 설정해 입력이 없으면 기본값을 설정한다


INSERT INTO dept values(12,'Edward','Im',DEFAULT);  -- 이와같이 DEFAULT 값을 넣을 수 있다







		# 데이터 유형 (DATA TYPE)
			# VARCHAR2 : 최대 4000 BYTE 길이까지 가능하다, 반드시 허용길이를 명시해야 한다, 가변길이 문자데이터이다.
			# CHAR : 최대 2000 BYTE 길이까지 가능하다, 고정길이 문자데이터이다
			# NUMBER 
			# DATE 
			# LONG : 가변길이 문자데이터 (2 GB)
			# CLOB : 문자 데이터 (4 GB)
			# RAW
			# LONG RAW
			# BLOB
			# BFILE
			# ROWID






		# 'TIMESTAMP' 계열의 데이터 유형
			# 글로벌 환경에서 DB를 관리하기 위해 생겨난 유형이다

				# TIMESTAMP 와 DATE
					# 서버와 세션 사이 시간대가 고려되지 않는다	

				# TIMESTAMP WITH TIME ZONE
				# TIMESTAMP WITH LOCAL TIME ZONE
					# 입력한 데이터의 시간값을 시간대별로 고려해서 변경시킨 값 
					# SYSTIMESTAMP, CURRENT_TIMESTAMP, LOCALTIMESTAMP
						# SYSDATE 보다 더 정확한 시간 함수이다.


		# 'INTERVAL' 계열의 데이터 유형
			# 기간을 표시해준다 (데이터 유형에 맞게)
			# INTERVAL YEAR TO MONTH, INTERVAL DAY TO SECOND 유형이 있다
				# 











--------------------------------------------------------------------------------------------------

<사용자 데이터 조작 명령어 DML>

## 'DATA MANIPULATION LANGUAGE', 'DML'
	# 데이터조작명령어 'INSERT', 'UPDATE', 'DELETE'...
		# 'INSERT' : 데이터 삽입

INSERT INTO hr.departments
VALUES (320, 'Oracle Administration', 100, 1700); -- INSERT문. 보통 hr.departments의 컬럼은 표기하지 않는다
	

INSERT INTO hr.employees
VALUES (302, UPPER('Den'), UPPER('Raphealy'),'hong@yahoo.co.kr', '515.127.4561',
TO_DATE('FEB 3, 1999', 'MON DD, YYYY', 'NLS_DATE_LANGUAGE=american'),
'AC_ACCOUNT', 11000, NULL, 100, 30) ;  -- TO_DATE를 이용해 원하는 형식의 날짜를 넣을 수 있다


INSERT INTO hr.sales_reps (id, name, salary, comm, email)
SELECT employee_id, last_name, salary, commission_pct, email
FROM hr.employees
WHERE job_id LIKE '%REP%' ;  -- 서브쿼리를 이용해 여러 값을 동시에 INSERT 할 수 있다







		# 'UPDATE' : 데이터 변경

UPDATE hr.copy_emp
SET salary = 8500
,name = INITCAP('SHSHIN')
,hiredate = TO_DATE('FEB 3, 1999', 'MON DD, YYYY', 'NLS_DATE_LANGUAGE=AMERICAN')
,DEPARTMENT_ID = NULL
WHERE id = 113;     -- UPDATE, SET, WHERE 를 이용해 값을 변경한다


UPDATE hr.copy_emp
SET department_id = (SELECT department_id
					FROM hr.employees
					WHERE employee_id = 100)
WHERE jobid = (SELECT job_id
			   FROM hr.employees
			   WHERE employee_id = 201); -- 서브쿼리를 사용해서 여러 값을 동시에 UPDATE 할 수 있다






		# 'DELETE' : 데이터 삭제
		# 'TRUNCATE' : 데이터 삭제2 (롤백 불가)

DELETE FROM hr.copy_emp
WHERE department_id = 30 ;  -- DELETE문


DELETE FROM hr.copy_emp
WHERE department_id = (SELECT department_id
					   FROM hr.departments
					   WHERE department_name LIKE '%Administration%'); -- 서브쿼리를 사용해 여러 값을 DELETE할 수 있다. ('=' 과 LIKE는 서로 조합이 안좋다고 한다. 연산이 많이 요구되므로)


TRUNCATE TABLE hr.copy_emp;  -- TRUNCATE문






	# '트랜잭션' (TRANSACTION) COMMIT, ROLLBACK, SAVEPOINT...
		# 여러 사용자들이 한 가지 이상의 작업을 할 때 여러 관련있는 명령문(ACTION)들의 집합
			# 세션 하나 당 한개의 트랜잭션을 생성하고 관리한다
			# 'DML' 작업이 끝나면 (MSSQL을 제외하고) 항상 COMMIT 명령을 넣어줘야 한다
			# 'DDL' 명령어를 입력하면 자동으로 COMMIT 명령어가 실행된다
				# 따라서 세션을 따로 관리해줘야 하는듯


		# ROLLBACK 을 입력하면 지금까지 입력된 모든 명령어들이 취소된다 
			# (마지막 COMMIT 명령어 전까지)
		
		# SAVEPOINT 를 이용해 중간 트랙잭션을 저장할 수 있다. (잘 사용하진 않는다고 한다)
			# SAVEPOINT insert1; 과 같이 저장점을 설정할 수 있다.
			# ROLLBACK TO SAVEPOINT insert1; 과 같이 저장점으로 돌아갈 수 있다
			# COMMIT 명령어를 사용하면 모든 SAVEPOINT 가 사라진다

		# LOCK
			# 세션 여러개를 이용해 서로 겹치는 문장들을 실행하면 LOCK 을 해제해주기 전까진 겹치지 못한다
				# COMMIT 을 쓰면 LOCK 이 해제된다
				# 테이블의 한 행 한 행마다 LOCK 이 걸린다
				
				# 'FOR UPDATE' 구문을 사용하면 강제로 LOCK 을 걸 수 있다
					# COMMIT 이나 ROLLBACK 전까진 다른 세션유저가 해당 행을 수정할 수 없다


SELECT employee_id, salary, commission_pct, job_id
FROM hr.employees
WHERE department_id = 90
FOR UPDATE
ORDER BY employee_id ;    -- FOR UPDATE를 이용해 해당 행을 LOCK 걸 수 있다


SELECT e.employee_id, e.salary, e.commission_pct, d.department_name, d.department_id
FROM employees e INNER JOIN departments d
ON e.department_id=d.department_id
WHERE job_id = 'FI_ACCOUNT'
AND location_id = 1700
FOR UPDATE OF e.salary
ORDER BY 1 ;     -- OF e.salary 구문을 통해 e.salary 행만 LOCK을 걸 수 있다


SELECT employee_id, salary, commission_pct, job_id
FROM employees
WHERE job_id = 'FI_ACCOUNT'
FOR UPDATE WAIT 5
ORDER BY employee_id;  -- WAIT 5 를 통해 다른 세션사용자가 LOCK 기능을 얻을 수 있게 5초간 기다린다






			# 읽기 일관성 (Read-Consistency)
				# '세그먼트'(SEGMENT), '블록' (BLOCK)
					# '세그먼트'는 각 테이블마다 자신의 데이터가 저장된 저장공간이다
					# '데이터블록'은 데이터들의 조각을 말한다
						# '언두 세그먼트' (UNDO SEGMENT)
							# 오라클에서만 사용하는 고유 아키텍쳐이다
							# COMMIT, ROLLBACK 을 하기 전까지 입력된 데이터들은 모두 언두 세그먼트에 기록된다	
							# 다른 세션에서 해당 데이터를 조회하면 '언두 세그먼트' 데이터를 읽어와 아직 수정 전 데이터만 볼 수 있다(COMMIT, ROLLBACK 전까지)










--------------------------------------------------------------------------------------------------

<SET 연산자의 활용>

## UNION, UNION ALL, INTERSECT, MINUS
	# UNION, UNION ALL (합집합)과 유사하다
		# A UNION (ALL) B 에서 두 결과물을 합쳐서 출력한다
			# UNION 은 중복을 정렬하고 UNION ALL 은 정렬하지 않는다

	# INTERSECT (교집합)
		# A INTERSECT B 에서 두 결과물 중 같은 값들만 한 번씩 출력한다

	# MINUS (차집합)
		# A MINUS B 에서 두 결과물 중 첫번째 결과물에'만' 있는 값을 출력한다




SELECT department_id, NULL AS "LOCATION_ID", hire_date
FROM hr.employees
UNION
SELECT department_id, location_id, NULL
FROM hr.departments;  -- 데이터 타입을 위와같이 NULL로 강제로 맞춰서 출력되게 만들 수 있다




SELECT employee_id, job_id
FROM hr.employees
WHERE employee_id IN (101,102,114,122,176,200,201)
UNION (ALL)
SELECT employee_id, job_id
FROM hr.job_history ;  -- UNION을 이용해 두 쿼리를 합치고 알아서 정렬되고 중복값 없이 나온다
					   -- UNION ALL이면 중복값까지 그대로 출력된다



SELECT employee_id, job_id
FROM hr.employees
INTERSECT
SELECT employee_id, job_id
FROM hr.job_history ;  -- INTERSECT 를 이용해 교집합을 구할 수 있다



SELECT employee_id
FROM hr.employees
MINUS
SELECT employee_id
FROM hr.job_history ;  -- MINUS를 사용해 차집합을 구할 수 있다















--------------------------------------------------------------------------------------------------

<서브 퀘리 (SUB QUERY)>

## 메인 쿼리 안에 또다른 쿼리가 있는 형식을 '서브 쿼리'라고 한다 
	# 메인쿼리 {...}
			   {...} (서브쿼리);
	# '서브쿼리' 안에는 ORDER BY 절을 적을 수 없다 (서브쿼리 밖에는 적을 수 있다)
	# WHERE , HAVING 절에 상수대신 사용할 수 있다.
		# 단일행, 다중행 서브쿼리로 나눌 수 있다
		# 다중행 서브쿼리는 IN, ANY, ALL 같은 연산자와 같이 쓸 수 있다
			# 컬럼 < ANY (서브쿼리) : 컬럼이 가장 큰 값보다 작으면 됨
			# 컬럼 > ANY (서브쿼리) : 컬럼이 가장 작은 값보다 크면 됨
			# 컬럼 > ALL (서브쿼리)
				# 하지만 실제는 거의 안쓰이고 MIN, MAX 로 대체된다
	
		# IN, NOT IN
			# WHERE employee_id IN (서브쿼리)
		  	  WHERE employee_id NOT IN (서브쿼리) 

			
SELECT employee_id, last_name, salary, manager_id
FROM hr.employees
WHERE employee_id NOT IN (SELECT manager_id
						  FROM hr.employees
						  WHERE manager_id IS NOT NULL)
ORDER BY 1 ;   -- NOT IN 은 IS NOT NULL과 같이 써야지 에러를 방지할 수 있다. NOT IN은 (...) 안에 null 값이 있으면 항상 에러가 나기 때문이다. 
-- 따라서 테이블의 속성에서 NULLABLE 값을 확인해서 IS NOT NULL을 쓸지 말지 결정한다.



SELECT last_name, salary
FROM hr.employees
WHERE salary = (SELECT MIN(salary)
				FROM hr.employees
				GROUP BY department_id ) ;  -- 이 구문은 에러가 나는데 서브쿼리가 다중(12개)값을 출력하기 때문이다. IN을 사용하면 다중행을 받을 수 있다.



SELECT department_id, AVG(salary)
FROM hr.employees
GROUP BY department_id
HAVING AVG(salary) = (SELECT MAX(AVG(salary))
					  FROM hr.employees
					  GROUP BY department_id);  -- 상당히 많이 쓰이는 구문이다. 평균임금을 구해서 최대 평균임금을 출력하는 구조이다.









--------------------------------------------------------------------------------------------------

<두 테이블의 행을 결합하기>

## JOIN, ON...
	# 'INNER JOIN'(EQUI-JOIN, NONEQUI JOIN) , 'OUTER JOIN' , 'CROSS JOIN', 'ORACLE JOIN' , 'NATURAL JOIN' 으로 나눌 수 있다
		# 그냥 JOIN만 입력하면 INNER JOIN이 디폴트값으로 설정된다

	# 'INNER JOIN'
		# 'EQUI-JOIN', 'NON-EQUI JOIN'(JOIN의 90% 이상을 차지한다)
			# ON 안에 있는 구문이 같은지를 검사하면
			# 아니면 NON-EQUI JOIN이다
				# ON (e.salary BETWEEN j.lowest_sal AND j.highest.sal) 과 같이 ON 구문이 EQUI와 같지 않다
		# 'SELF JOIN'
			# 'EQUI-JOIN'의 한 부분이다

SELECT a.last_name AS "BUHA", b.last_name AS "BOSS"
FROM  hr.employees a INNER JOIN hr.employees b
ON (a.manager_id= b.employee_id)  
WHERE a.employee_id = 101 ;     -- SELF JOIN은 이와 같이 한 테이블에서 참조를 할 때 사용한다





	# 'OUTER JOIN' (LEFT, RIGHT, FULL)
		# INNER JOIN을 통해 출력되지 않은 결과물을 보여주는 JOIN ('INNER + @'의 효과)
		# LEFT, RIGHT, FULL은 JOIN 키워드를 기준으로 왼쪽, 오른쪽, 둘다 출력하는걸 뜻한다
			# LEFT OUTER JOIN, RIGHT OUTER JOIN, FULL OUTER JOIN


SELECT e.last_name, d.department_name ,d.department_id
FROM hr.employees e, hr.departments d
WHERE e.department_id (+) = d.department_id ;
또는
WHERE e.department_id = d.department_id (+); -- (+) 수식을 이용해 OUTER JOIN을 사용할 수 있다 (별로 추천하지는 않는 방법)




	# 'CROSS JOIN'
		# 합칠 수 없는 행을 강제로 합칠 때 사용한다
		# 원래는 못 합치는 두 테이블을 강제로 합치는데 썻지만 'INNER JOIN' 대신으로 요즘 많이 쓰며 'INNER JOIN'보다 속도가 빠르다



	# 'ORACLE JOIN'
		# ORACLE에서만 쓸 수 있는 JOIN (ON 절이 없다)
		# 다른 조인과 달리 WHERE 절에 사용한다 
			
SELECT e.last_name, d.department_name ,d.department_id
FROM hr.employees e, hr.departments d
WHERE e.department_id = 90
AND e.department_id = d.department_id ;  -- WHERE 절에 사용한 ORACLE INNER EQUI JOIN이다

	


	# 'NATURAL JOIN'
		# 별로 안 중요~

	
	# 'PRIMARY KEY', 'FOREIGN KEY' (1 : 다수 관계)
		# 이 때만 JOIN을 사용해야 하고 비록 이름이 같아도 PRIK, FORK의 관계가 아니면 사용하면 안된다(많은 경험이 필요한듯)




SELECT e.employee_id, e.last_name, e.department_id, d.department_name
FROM hr.employees e JOIN hr.departments d
ON (e.department_id = d.department_id)
order by 3 ; -- 테이블 이름이 너무 길어서 쓰기 힘드므로 TABLE ALIAS를 사용해서 간단하게 한다


SELECT hr.employees.employee_id, hr.employees.last_name, hr.employees.department_id , hr.departments.department_id, hr.departments.department_name 
FROM hr.employees INNER JOIN hr.departments 
ON (hr.employees.department_id = hr.departments.department_id) 
order by 3 ;  -- ON을 이용해 두 테이블의 department_id 값이 같으면 INNER JOIN 으로 두 테이블의 값을 가져온다 


SELECT e.employee_id, e.last_name, e.department_id, d.department_id, d.department_name
FROM hr.employees e RIGHT OUTER JOIN departments d
ON (e.department_id = d.department_id) ; -- RIGHT OUTER JOIN 을 이용해 결과를 출력한다




--------------------------------------------------------------------------------------------------------

<다중행 함수>

## 다중행 함수 : SUM, AVG, MAX, MIN, COUNT, STDDEV, VARIANCE...
	# SUM, AVG 는 숫자만 가능하다
	# MAX, MIN, COUNT 는 문자, 숫자, 날짜 유형 모두 가능하다
		# MAX , MIN 은 LONG, CLOB 데이터 유형에는 사용 못한다
			LONG: 최대 2GB 길이까지 가능한 문자 데이터
			CLOB: 최대 4GB 길이까지 가능한 문자 데이터

	# 집합함수에는 ALL , DISTINCT 를 추가해 사용할 수 있다
		# 예를들어 SUM(ALL score) , SUM(DISTINCT score) 과 같이 쓸 수 있다.
		# DISTINCT : 중복된 값은 대표값으로 치며 한 번만 더한다
		# 기본적으로 null 값은 무시한다
			  AVG(score)          : 300/4
			  AVG(NVL(score,0))   : 300/5
			  COUNT(score)        : 4
			  COUNT(NVL(score,0)) : 5     == COUNT(*) 라는 구문과 일치한다(너무 많이 쓰여서 하나 새로 생김)
			  -- 위처럼 값이 null에 따라 달라진다

SELECT COUNT(*) FROM hr.employees -- hr.employees 테이블의 데이터 개수를 출력한다



	# GROUP BY 와 HAVING
		# {...1} UNION ALL {...2}  : 1과 2의 결과 레코드를 붙여서 보여준다
		# GROUP BY
			# 데이터를 일괄적으로 처리하기 좋다 (부분집계) (엄청나게 많이 쓰인다)
			ex) 월별 매출 합계, 시간별 매출 합계, 은행별 예금액 합계, 지역별 매출 합계...
			
			# 항상 SELECT 절에 있는 컬럼 값은 GROUP BY 절에 적어줘야 한다 (문법이다)
			# WHERE 절에는 SUM(salary)를 GROUP BY 와 같이 입력할 수 없다 (HAVING 으로 대체 가능)
			

SELECT department_id, AVG(salary) AS "AVG_SAL_PER_DEPT" , COUNT(*) AS Persons 
FROM hr.employees 
GROUP BY department_id ;  -- department_id에 따라 SELECT한 컬럼들을 그룹지어 보여준다



		# HAVING
			# 집합함수에서 최종 결과를 선별할 수 있다
			# WHERE 절에 위에 말한것처럼 SUM(...) 이런걸 못하는 대신 HAVING 으로 최종 결과를 정렬할 수 있다
		





--------------------------------------------------------------------------------------------------------------------


<일반 함수>

## 일반함수는 NVL,NVL2,NULLIF,COALESCE... 이며 주로 null값의 사용과 관련이 있다
	# 조건함수는 CASE, DECODE...
	
	NVL(commission_pct,0) -- commission_pct 값이 null일 경우 0으로 변경한다
	NVL2(commission_pct,'OK','NO') -- commission_pct 값이 null이 아니면 OK, null이면 NO를 반환한다
	NULLIF(LENGTH(first_name),LENGTH(last_name)) -- 두 값이 같으면 null, 다르면 앞에 값을 반환한다
	COALESCE(관리자,커미션,-1) -- 여기 있는 3개 값 중 최초로 null이 아닌 컬럼의 값을 표현한다. 3개 인자의 형이 같아야 한다.


	(CASE job_id WHEN 'IT_PROG' THEN 1.10*salary WHEN 'ST_CLERK' THEN 1.15*salary ELSE salary END) AS "REVISED_SALARY" -- DECODE와 기능이 똑같은 함수. Mysql이나 MSsql에서 사용할 수 있다
	(CASE WHEN salary < 5000 THEN 'Low' WHEN salary < 10000 THEN 'Medium' WHEN salary < 20000 THEN 'Good' ELSE 'Excellent' END) -- 검색된 CASE 구문이라고 불리며 조건식을 쓸 수 있다 (DECODE는 불가능)(CASE가 DECODE보다 더 빠르다)


	DECODE(job_id, 'IT_PROG', 1.10*salary,
					'ST_CLERK', 1.15*salary, salary) AS 'REVISED_SALARY' -- job_id 값에 따라 조건식을 만든다. 마지막 salary는 생략가능하다 (오라클에만 존재하는 함수)




-------------------------------------------------------------------------------------------------------------------


<단일행 함수>

## 단일행 함수 <====> 다중행 함수
	# '단일행 함수'는 한 줄 한 줄마다 명령어를 실행하는 것
	# '다중행 함수'는 모든 데이터를 모아서(?) 한 번 실행하는 것
	# 함수의 테스트 등을 위하여 사용할 수 있도록 DUAL 테이블
		# DESC DUAL;
	
	# 문자 함수
		# UPPER, LOWER, INITCAP, CONCAT, SUBSTR, LENGTH, LENGTHB, REPLACE, LPAD, RPAD, TRIM,INSTR...
			UPPER('last_name');  -- 전부 대문자로 바꾼다 
			INITCAP('first_name'); -- 첫글자만 대문자로 바꾼다
			SUBSTR('200080815',-2); -- 뒤에서 2번째 글자부터 끝까지 추출한다
			REPLACE('JACK and JUE','J','BL');	-- 'J'를 'BL'로 바꾼다
			TRIM('S' FROM 'SSMISTMSS') AS "RESULT";  -- 문자열에서 'S'를 없앤다
			INSTR('HELLO ORACLE','L',1,1) "RESULT"; -- 1번째 글자부터 1번째 나오는 L의 위치
			INSTR('HELLO ORACLE','L',4,2) "RESULT"; -- 4번째 글자부터 2번째 나오는 L의 위치
	
		# INSTR은 제일 많이 활용하는 함수 중 하나이다




	# 숫자 함수
		# ROUND, TRUNC, MOD...
			ROUND(1726.236,2);   -- 소수점 2자리까지 유효하다 : 1726.24
			ROUND(1726.236,-2);	 -- 소수점 -2자리(정수 2자리)까지 유효하다 : 1700
			TRUNC(1726.236,2);   
			TRUNC(1726.236,-2);
			MOD(1600,300);    -- 1600을 300으로 나눈 나머지를 출력한다




	# 날짜 함수
			# MONTHS_BETWEEN, ADD_MONTHS, NEXT_DAY, LAST_DAY...
			SELECT MONTHS_BETWEEN(TO_DATE('1995/09/01','yyyy/mm/dd'), TO_DATE('1995/12/12','yyyy/mm/dd')) FROM dual; -- 데이터 사이의 월 수의 차이를 찾는다
			SELECT NEXT_DAY(TO_DATE('08/11/11','YY/MM/DD'),6) FROM dual; -- 지정된 date 값 다음에 오는 지정된 요일을 찾는다 1~7(일~토)


			# 세션(클라이언트)의 날짜 표시형식을 다음과 같이 설정할 수 있다
				# 환경설정 -> 데이터베이스 -> NLS에서 변경할 수도 있다.
				ALTER SESSION SET NLS_DATE_FORMAT='YYYY/MM/DD' ;
					'YYYY/MM/DD HH24:MI:SS' 같이 시분초도 추가할 수 있다



	# 변환 함수
		# TO_DATE, TO_CHAR, TO_NUMBER...
			TO_DATE('2002-06-15','YYYY-MM-DD');  -- 매우 중요! 시스템(이나 국가)마다 표현하는 날짜 체계가 다르므로 TO_DATE로 명시해 줄수 있다.
			# 대표적인 형식 모델
				YYYY, MM ,DD ,DAY, HH24, MI, SS, AM... 등등 많이 있다
				TO_CHAR(SYSDATE, 'YYYY/MON/DD HH24:MI:SS AM DAY');
				TO_CHAR(sysdate, 'YYYY-mON-DD HH24:MI:SS AM DaY','NLS_DATE_LANGUAGE=AMERICAN')     -- 영어 형식으로 표기되게 바꾼다. 앞에 mON, MOnth, mon, MON 등에 따라 표시 형식이 달라진다
				TO_CHAR(sysdate, 'YYYY" 년 " MM"월" DD"일" HH24"시 " MI"분" SS "초" AM Day')        -- 날짜 구분자를 원하는 글자로 바꾼다







'단일행 함수'
SELECT last_name, UPPER(last_name) AS "UPPER_NAME", salary FROM hr.employees WHERE department_id = 90 ;

'다중행 함수'
SELECT SUM(salary) FROM hr.employees WHERE department_id = 90;













------------------------------------------------------------------------------------------------


<SELECT 구문 연습>

## 'q' 연산자는 오라클에만 존재하고 ANSI표준이 아니다 
	인용시 사용한다



## DISTINCT 수식자
	# 중복된 레코드를 한 번만 표시한다
	# ORDER BY와 같이 안쓰는걸 권장한다 (메모리 문제?)

SELECT DISTINCT department_id, job_id FROM hr.employees WHERE department_id = 30 ;




## 연결연산자(||)는 연산자 앞 뒤로 명시된 두 개의 문자열을 붙입니다

SELECT last_name || JOB_ID AS "RESULT" FROM hr.employees WHERE employee_id = 100 ;





## Literal Chracter String
	# 결과에 그대로 나오는 문자열을 말하는듯

SELECT last_name , 'is a', 90 , job_id FROM hr.employees WHERE department_id = 90 ;





## WHERE 문법 
	# WHERE문 안에 조건문
	# BETWEEN, IN(set), LIKE, IS NULL
		# IN은 지정된 값 집합에서 값을 추출할 때 사용한다
		  ex) manager_id IN (100,101,201);
		# LIKE는 같은 문자열을 찾는다 
		  ex) LIKE 'S%'; LIKE '_o%'; LIKE '%o%'; 등등 
			#'_'는 한 글자 '%'는 여러 글자 '\_'는 이스케이스 문자를 가르킨다
		  	ex) LIKE 'AD\_%' ESCAPE '\';    '

	# > = >= < <= <>(같지 않음 != ^=...) 등등이 있다

SELECT last_name, job_id, department_id,salary FROM hr.employees WHERE last_name = 'Smith' AND salary >= 7500;





## 서버의 현재 시간과 날짜를 DATE 형식으로 반환하려면

SELECT sysdate FROM dual;






## ORDER BY 절
	# ORDER BY hire_date ASC(or DESC) 오름차순, 내림차순으로 정렬한다
	# SELECT employee_id(1), last_name(2), salary(3) from ... where ... order by 3 ASC
		# 위에 제시한 3개의 열 중 3번째 컬럼(salary) 순으로 오름차순으로 정렬한다
	
	# 그냥 ORDER BY만 있으면 ASC대로 정렬한다
	# NULL FIRST, NULL LAST 는 오라클에만 있는 고유 명령어라고 한다






	
-------------------------------------------------------------------------------------------


## HR (Human Resource) 유저 권한 변경
ALTER user hr IDENTIFIED BY oracle4U ACCOUNT UNLOCK;


## '데이터(Data)'는 구체적으로 표현된 하나의 값을 의미합니다.
예를 들면, 아래에서 "홍길동"과 "01024567856"을 각각 "이름 데이터", "전화번호 데이터"라고 합니다.


## '정보(Information)'는 사용자(Client)에게 특별한 의미를 가지는 데이터의 조합(Data-Group)을 의미합니다.
예를 들면, 아래에서 "홍길동"과 "01024567856"의 2 개의 데이터가 조합되어 "홍길동의 연락처 정보"라고 합니다.
이름 데이터
전화번호 데이터
→ 홍길동의 연락처 정보
홍길동
01024567856

## '행(Row)'은 특정 테이블에 정의된 모든 컬럼들의 값들로 구성된 데이터들 한 개의 묶음을 의미합니다.

## '레코드(Record)'는 행에서, 하나 이상의 필드에 있는 값들의 조합을 의미합니다. 이러한 레코드가 사용자-프로그램에서
처리되는 값들의 조합으로 사용됩니다.





2016/07/18 에 시작된 ORACLE 11g 데이터베이스 강의 / 신상현 강사









