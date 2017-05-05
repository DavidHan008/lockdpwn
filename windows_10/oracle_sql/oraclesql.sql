

<DATA Dictionary>

## 'DATA Dictionary'
	# ���� ������ ������ ����� �� �ִ� ���̺� �Ǵ� ��� ����� ������?
	# Ư�� �信 ���ǵ� SELECT ���� ������ �����ϱ�?
	# ... ���� �ñ����� ���� �� ����մϴ�


		# 'STATIC DATA DICTIONARY VIEW'
			# ��ũ�� Ư�� ������ ��ųʸ� ���̺� ������ִ� �����Դϴ�
				# USER_TABLES : ���� ������� ���̺� ������ �����մϴ�
				# ALL_TABLES : 
				# DBA_TABLES : DBA�� ��ȸ�� �� �ֽ��ϴ�. ��� ���̺��� �ý��� ������ ����մϴ�


DESC dictionary; -- ������ ��ųʸ� ���� �÷������� Ȯ���� �� �ֽ��ϴ�
DESC USER_TABLES;
DESC DBA_TABLES;
DESC ALL_TABLES;  -- �ش� ��ųʸ� ������ ���� �� �ֽ��ϴ�




		# 'DYNAMIC PERFORMANCE VIEW (VS-VIEW)'
			# �� ��� �޸𸮿��� �����ϰ� ������� �ʽ��ϴ�
			# 'V$' �� �����մϴ�












-------------------------------------------------------------------------------------------------

<����� ���� ���� DCL>

	$$ ������� ����Ŭ�� ���� ������� �ʴ´�
		$ MAC�� �ƿ� ����Ŭ�� �� �� �ִ� ����Ʈ��� ����
		$ ������������ ������ + ����Ŭ�� ����ϴ� �߼��̴�
			$ REDHAT + ORACLE �� �ַ� ����Ѵ�
			$ UBUNTU(DEBIAN) �迭�� �ƽ����� �������� �ʴ´�



## GRANT, REVOKE, SYS, SYSTEM...
	# �����ͺ��̽� ��ü�� ����� ������ �ο��ϰų� ������ �� �ֽ��ϴ�	
		# SYS :
		# SYSTEM : 
			# GRANT : ����ڿ��� ������ �ο��մϴ�
				# UPDATE(department_id), REFERENCE(department_id) ���� �÷��� ������ �� �ֽ��ϴ�
				# SELECT, INSERT, DELETE �� �Ұ����մϴ�

			# REVOKE : ������� ������ ������ �� �ֽ��ϴ�






CREATE USER edward IDENTIFIED BY qwer1234; -- ����ڸ� �����մϴ�, ������ �н������ 30 BYTE�� ������ �ȵ˴ϴ�
CREATE USER edward2 IDENTIFIED BY qwer1234; 



GRANT CREATE SESSION, CREATE TABLE, CREATE VIEW,
CREATE SEQUENCE, CREATE SYNONYM, ALTER SESSION
TO edward, edward2;  -- GRANT�� ����ڿ��� ������ �ο��� �� �ֽ��ϴ�.
-- CRAETE TABLE ���� �ܿ��� DEFERRED_SEGMENT_CREATION�� FALSE�� �Ǿ��־�� ���̺��� ���� �� �ֽ��ϴ�


GRANT CREATE SESSION
TO PUBLIC ;   -- PUBLIC�� ����ϸ� ��� ������ �ش� ������ ����� �� �ְ� �մϴ�



GRANT SELECT, INSERT, DELETE, ALTER, INDEX, UPDATE, REFERENCES
ON HR.LOCATIONS
TO HR1, HR2 ;   -- hr.locations ���̺��� ������ �ش� ����ڵ��� ����� �� �ְ� �մϴ�
				-- ����Ŭ�� ON�� �� ���� ���̺� ����� �� �ֽ��ϴ�








	# �������� ���ѵ�
		# ���� ���� ���̺��� ���� ������ �� �ֽ��ϴ�
		# '�ý��� ����'
			# DB Administrators �� ����ϴ� ������ �ο��Ǵ� ���ѵ�

				# CREATE USER
				# DROP USER
				# BACKUP ANY TABLE
				# SELECT ANY TABLE
				# CREATE ANY TABLE
				# DROP ANY TABLE
			
			---------------------------------------------------------
			# �����ڵ��� ����ϴ� ������ �ο��Ǵ� ���ѵ�
			
				# CREATE SESSION
				# ALTER SESSION
				# CREATE TABLE
				# CREATE SEQEUNCE
				# CREATE VIEW
				# CREATE DATABASE LINK
				# CREATE PROCEDURE
				# ...
		
		# '��ü ����' 
			# SELECT, DELETE, UPDATE, INSERT �� �׼����� �� �ִ� ���ѵ��Դϴ�
			# ������ ALL �� �Է��ؼ� ��� ������ �Ѳ����� ������ TABLE, VIEW �� �����Դϴ�


		# 'ROLE'
			# ������ �ٷ� ����ڿ��� �ָ� ����ڰ� ���������� �ʹ� ���������Ƿ� ROLE�̶�� �� ����� �߰��ܰ踦 ���� ü�������� �����մϴ�.
			
			# CONNECT-ROLE, RESOURCE-ROLE, DBA-ROLE... ���� �ֽ��ϴ�
			


CREATE ROLE EMPROLE1 ; -- ���� �����մϴ� 
GRANT CREATE SESSION, CREATE TABLE TO emprole1 ; -- �ѿ� ������ �ο��մϴ�










		# SQL*PLUS ����
			# cmd
			# sqlplus hr/oracle4U@orcl  (�����ʸ� ���� ���� ����)
			# conn edward/qwer1234@orcl



REVOKE REFERENCES
ON HR.DEPARTMENTS
FROM HR1 CASCADE CONSTRAINTS ; -- CASCADE CONSTRAINT�� �̿��� FOREIGN KEY�� �����ϴ� ������ �ȵƴ� ���̺��� ������ ������ �� �ֽ��ϴ�


GRANT SELECT
ON HR.DEPARTMENTS
TO HR1
WITH GRANT OPTION ;  -- HR1�� GRANT �ɼ��� ���� �� �ֽ��ϴ� (���Ϳ��� ���ȶ����� ����� ���� �ʽ��ϴ�)






-------------------------------------------------------------------------------------------------

<����Ŭ �����ͺ��̽� ��ü>

## VIEW, SEQUENCE, INDEX, SYNONYM...
	# VIEW ��ü 
		# ����ڵ��� ������ ACCESS ������ �����ؾ� �� �� ����Ѵ�
			# �ٸ� ����ڵ��� VIEW �ȿ��� ���ǵ� SELECT ���ڵ常 ACCESS �����ϴ�
			# ���Ȱ� ���õ� ��ü�̴�
			# DEFAULT Ű���带 ����� �� ����

		# FORCE, WITH READ ONLY, WITH CHECK OPTION �� �̿��� �ɼ��� ������ �� �ִ�
			# FORCE : ������ ������ ���� ������ VIEW �� ����� (���� �Ⱦ���)
			# WITH READ ONLY : VIEW �� �б��������� ����� (���� �Ⱦ���)
			# WITH CHECK OPTION : VIEW ��ü�� ������ �� ���ǹ����� ���� �˻��� �� �ִ�


		# CREATE OR REPLACE VIEW 
			# VIEW �� �Ӽ��� �����ϰ� ���� �� ����Ѵ�
			# ANSI ǥ�ذ� �ٸ��� (����Ŭ�� ���)(�ٸ� ������ ���� ALTER VIEW {...})



			

CREATE VIEW hr.sal30vw
AS
SELECT employee_id, first_name, salary
FROM hr.employees
WHERE department_id = 30 ;  -- �Ʒ� SELECT ���� �����ϵǼ� ����� ��ü�� VIEW�̴�.



CREATE VIEW hr.dept_sal_vu
AS 
SELECT UPPER(d.department_name) NAME, MIN(e.salary) MINSAL, MAX(e.salary) MAXSAL, AVG(e.salary) AVGSAL 
FROM hr.employees e INNER JOIN hr.departments d
ON (e.department_id = d.department_id)
GROUP BY d.department_name;   -- INNER JOIN�� Ȱ���� �������� ���޿� ���� VIEW ��ü�� �����



CREATE FORCE VIEW hr.empvu10 (employee_number, employee_name, job_title)
AS 
SELECT employee_id, last_name, job_id
FROM hr.employees111
WHERE department_id = 10
WITH READ ONLY ;  -- FORCE�� WITH READ ONLY�� �̿��� �б��������� ���� �� �ִ� (DML ���Ұ�)(�� ������� �ʴ´�)



CREATE VIEW hr.empvu20
AS 
SELECT *
FROM hr.employees
WHERE department_id = 20 WITH CHECK OPTION ; -- WITH CHECK OPTION�� �̿��� ���ǹ����� ���� �˻��� �� �ִ�. 



CREATE OR REPLACE VIEW hr.salvu50
AS 
SELECT employee_id AS ID_NUMBER, first_name || ' '|| last_name AS NAME,
salary AS SAL, department_id
FROM hr.employees
WHERE department_id = 50 ;  -- CREATE OR REPLACE VIEW �� �̿��� VIEW�� ������ �� �ִ�



DROP VIEW hr.sal30vw; -- VIEW�� ������ �� ����Ѵ�








	

	# 'SEQUENCE' ��ü
		# ����Ŭ���� �ִ� ��ü�̴�.
		# ���θ�����Ʈ���� �ֹ���ȣ�� ���� �����̴� (���� �Է����� �ʾҴµ� �ڵ����� ������ ��ȣ)	
		# PRIMARY KEY ���� �����ϴµ� ����� �� �ִ�
			# NOCYCLE �ɼ��� �����ؾ� �Ѵ�
		
		# �޸�ĳ��(CACHE)�� �̿��� ó���ӵ��� ����ų �� �ִ� (DEFAULT 20)
		
		# 'NEXTVAL', 'CURRVAL'�� �̿��� �������� ȣ���� �� �ִ�
			# NEXTVAL : ���ǿ��� ������ ����� ���� ȣ���Ѵ�
			# CURRVAL : ���ǿ��� ����� ������ ������ ���� ȣ���Ѵ�



INSERT INTO table_name
VALUES (sequence_name.NEXTVAL, TO_CHAR(SYSDATE,��YYYYMMDD��)||��_��||sequence_name.CURRVAL) ; -- �������� ȣ���ϴ� NEXTVAL, CURRVAL�� ����




		# ROLLBACK �� ���� �ʴ´�
			# �ý����� ����õǸ� SEQUENCE ���� �̾����� ���� �� �ִ�

		# ALTER, DROP �� ����� ������ ���� ������ �� �ִ�
			# START WITH ���� ALTER�ε� ������ �� ����





CREATE SEQUENCE hr.dept_deptid_seq1 ; -- ������ ��ü�� �����Ѵ�



CREATE SEQUENCE hr.dept_deptid_seq2
START WITH 500   -- 500���� �����Ѵ�
INCREMENT BY 10  -- 10�� �����Ѵ�
MAXVALUE 9999    -- �ִ밪�� 9999
MINVALUE 500     -- �ּҰ��� 500 (�ٽ� �����Ҷ� 500���� �����Ѵ�)
NOCACHE  -- �޸� ĳ�ø� ������� �ʴ´�
CYCLE ;  -- CYCLE�� �̿��� �ݺ��Ѵ�    



CREATE SEQUENCE hr.dept_deptid_seq3
START WITH 500
INCREMENT BY 10
MAXVALUE 9999
--MINVALUE 500
CACHE 10  -- �޸� ĳ�ø� ����Ѵ� (DEFAULT���� 20)
NOCYCLE ; -- �ֱ⸦ �ݺ����� �ʴ´�



ALTER SEQUENCE DEPT_DEPTID_SEQ1 CACHE 1000000 ; -- �޸�ĳ�� ���� ������ �� �ִ�


DROP SEQUENCE hr.dept_deptid_seq1 ; -- �������� ������ �� �ִ� 









	# INDEX ��ü
		# ��ũ I/O Ƚ���� �ٿ��� SQL���� ó�� ������ ����ų �� �ִ�.
		# ����Ŭ ������ �˾Ƽ� �����Ѵ�
			# ROWID 
				# ����Ŭ ������ �ĺ��ϱ� ���� ��ü������ ���� ������ ���̴�
				# 6����(���̺��̸�), 3����(���Ϲ�ȣ), 6����(��Ϲ�ȣ),  3����(����� ��ġ)
				# �� ������ ����� INDEX �� ����Ѵ�.
				# ROWID + INDEX KEY ���� �̿��� �����Ѵ�


		# 'FULL TABLE SCAN' vs 'INDEX SCAN'
			# ������ INDEX SCAN�� ���ٰ� �������°� �ƴϴ�
			# ���� ���� ������ �ִ� ���̺� + query �� 2% ~ 4% �̸��� �����͸� ������ �ɷ� ����Ǵ� ��� INDEX�� ����ϸ� ����
		

		# PRIMARY KEY, UNIQUE �� �Է��ϸ� �ڵ����� INDEX �� �����ȴ�
			# �� KEY���� ������ �� ���� (DROP INDEX �Ұ���)


		# ������ I/O�� ������ INDEX �� ����ϰ� ���� ������
			WHERE + �÷� || '';  -- ���ڵ������� ���
			WHERE + �÷� + 0;    -- ���ڵ������� ���







SELECT ROWID, employee_id, last_name from hr.employees; -- 6/3/6/3 �� ������ ROWID�� �� �� �ִ�. AAAR5K/AAF/AAAADL/AAA


CREATE INDEX hr.idx_lname_emp ON hr.employees(last_name) ;  -- INDEX�� �����


SELECT * FROM hr.employees WHERE UPPER(last_name)='KING' ; -- WHERE�� �Լ��� ����ϸ� INDEX�� ����� �� ����. ������ FULL TABLE SCAN�� �Ѵ�


DROP INDEX hr.idx_lname_emp ; -- INDEX�� �����Ѵ�

















	# SYNONYM ��ü
		# ���� �л�� DB �������� �����͸� ������ ��� ���� �� �̸��� ���� ���ԵǴµ� �̸� ���̱� ���� ����Ѵ�
		# �Ϲ� ���Ǿ� (Normal Synonym) : ���� ��밡���� ���Ǿ�
		# ���� ���Ǿ� (Public Synonym) : ��� �α��ΰ����� ��밡���� ���Ǿ� (DBA�� ���� �� �ִ�)

		# ALTER �� �������� �ʴ´� DROP �� ������
			



CREATE SYNONYM hr.emp_syn FOR hr.employees ;  -- �Ϲ� ���Ǿ �����

CREATE PUBLIC SYNONYM dept_pusyn FOR hr.departments ; -- ���� ���Ǿ �����



SELECT last_name
FROM hr.emp_syn
WHERE department_id = 90 ;  -- hr.employees ��� hr.emp_syn�� ����� �� �ִ�


DROP PUBLIC SYNONYM dept_pusyn ;  -- SYNONYM�� �����Ѵ�














--------------------------------------------------------------------------------------------------

<���̺� �Ӽ� ���� �� ����>

## ALTER AND DROP
	# ALTER TABLE
		# ���̺� �Ӽ��� �����Ѵ�	

		ALTER TABLE hr.department READ ONLY;  -- ���̺��� �б��������� ����� (�� ���� �Ұ���)
		ALTER TABLE hr.department READ WRITE;


	# DROP TABLE 
		# ������ ���̺��� ���������� �̵��Ѵ� (����Ŭ���� �ִ� ���)
		# ������ ���̺��� �ڵ� COMMIT �Ǿ� ROLLBACK ���� �ʴ´� 

		DROP TABLE hr.dept70;
		DROP TABLE hr.dept70 PURGE; -- PURGE�� �̿��� �����뿡 �������� �ʰ� ���� �����Ѵ� (����Ŭ���� �ִ� ���)









-------------------------------------------------------------------------------------------------

<TRUNCATE �� �̿��� ���̺� ������ ����>


## TRUNCATE VS DELETE 
	# TRUNCATE : ���̺��� �ʱ� ���·� �����Ѵ� (UNDO �����͸� ������ �ʴ´�)
		# �ڵ� COMMIT �ǹǷ� ROLLBACK �� �Ұ����ϴ�
		# FOREIGN KEY�� �������ϴ� ���̺��� TRUNCATE ���� �ʴ´�


	# DELETE : WHERE �� ���� ���� �Ȱ��� ���̺� ��� �����͸� �����Ѵ� (UNDO �����͸� �����)
		# ROLLBACK �� �����ϴ� 



TRUNCATE TABLE hr.employees3 ;








--------------------------------------------------------------------------------------------------

<���������� �̿��� ���̺� ����>

## CREATE TABLE + SUB-QUERY
		# NOT NULL �� ������ �������� PRIMARY KEY, FOREIGN KEY, UNIQUE...�� ������� �ʴ´�



CREATE TABLE hr.dept70
AS
SELECT employee_id, last_name as ENAME, salary*12 ANNSAL, hire_date hiredate
FROM hr.employees
WHERE department_id = 70 ; -- AS ��ɾ �̿��� ���������� �̿��� �� �ִ�


CREATE TABLE hr.dept80 (empno, ename, annsal, hiredate)
AS
SELECT employee_id, last_name, salary*12, hire_date
FROM hr.employees
WHERE department_id = 80 ;  -- ���������� ����� ����












--------------------------------------------------------------------------------------------------

<���� ����>


## 'CONSTRAINT'
	# NOT NULL, UNIQUE, PRIMARY KEY, FOREIGN KEY, CHECK...
		# NOT NULL : NULL ���� �ԷµǸ� �ȵǴ°� �ǹ��Ѵ�
		# UNIQUE  : ���� ���� �ߺ��Ǹ� �ȵǴ°� �ǹ��Ѵ�
		# PRIMARY KEY : NOT NULL + UNIQUE �� ������ ����Ű���� �ǹ��Ѵ�
		# FOREIGN KEY : PRIMARY KEY�� ���� ���Ǹ� ���� �Է��� �� PRIMARY KEY�� ���� �Ǵ��Ѵ�
			# FOREIGN KEY�� ���� �����Ǵ� PRIMARY KEY�� ���� �� ����.

		# CHECK : �������� ���������� ���� �� �ִ�



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
REFERENCES hr.departments(department_id) ON DELETE SET NULL ); -- ���̺����� ���������� ������ DDL �����̴�. (���������� ���� �Ʒ��� ��������)
-- CONSTARINT {...} �� ���� �������� �����ִ°� �������� ���ؼ� ����
-- PRIMARY KEY(eid,name)�� ����Ű �����̴�
-- FOREIGN KEY�� REFERENCES {...} �� ���� ����Ѵ�





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
REFERENCES hr.departments (department_id) ON DELETE CASCADE);  -- �÷������� ���������� ������ ����̴�
-- FOREIGN KEY�� �÷����������� ���� �ʾƵ� �ȴ� .



				# FOREIGN KEY���� 
					# �ƹ��͵� ������ PRIMARY KEY�� ���� �� ����
                    # ON DELETE SET NULL : �ش� PRIMARY KEY�� ���� �� �ְ� �ش� FOREIGN KEY ���� NULL�� �ٲ��.
					# ON DELETE CASCADE  : �ش� PRIMARY KEY�� ���� �� �ְ� �ش� FOREIGN KEY ���� �����ȴ�.















--------------------------------------------------------------------------------------------------

<����� ������ ���� ��ɾ� DDL>



## 'DATA DEFINITION LANGUAGE', 'DDL'
	# �����ͺ��̽� ���� ��ɾ� 'CREATE', 'ALTER', 'DROP'...
		# 'CREATE' : ���̺� ����


CREATE TABLE tablename(
...
...
...
);   -- CREATE TABLE ������ �̿��� ���̺��� �����
	 -- �Ϲ������� ���̺��� ��ҹ��ڸ� �������� �ʴ´� (����Ŭ only)




			# DEFAULT Ű����

CREATE TABLE dept(
deptno number(2),
dname varchar2(14),
loc varchar2(13),
create_date date DEFAULT sysdate); -- DEFAULT ���� ������ �Է��� ������ �⺻���� �����Ѵ�


INSERT INTO dept values(12,'Edward','Im',DEFAULT);  -- �̿Ͱ��� DEFAULT ���� ���� �� �ִ�







		# ������ ���� (DATA TYPE)
			# VARCHAR2 : �ִ� 4000 BYTE ���̱��� �����ϴ�, �ݵ�� �����̸� ����ؾ� �Ѵ�, �������� ���ڵ������̴�.
			# CHAR : �ִ� 2000 BYTE ���̱��� �����ϴ�, �������� ���ڵ������̴�
			# NUMBER 
			# DATE 
			# LONG : �������� ���ڵ����� (2 GB)
			# CLOB : ���� ������ (4 GB)
			# RAW
			# LONG RAW
			# BLOB
			# BFILE
			# ROWID






		# 'TIMESTAMP' �迭�� ������ ����
			# �۷ι� ȯ�濡�� DB�� �����ϱ� ���� ���ܳ� �����̴�

				# TIMESTAMP �� DATE
					# ������ ���� ���� �ð��밡 ������� �ʴ´�	

				# TIMESTAMP WITH TIME ZONE
				# TIMESTAMP WITH LOCAL TIME ZONE
					# �Է��� �������� �ð����� �ð��뺰�� ����ؼ� �����Ų �� 
					# SYSTIMESTAMP, CURRENT_TIMESTAMP, LOCALTIMESTAMP
						# SYSDATE ���� �� ��Ȯ�� �ð� �Լ��̴�.


		# 'INTERVAL' �迭�� ������ ����
			# �Ⱓ�� ǥ�����ش� (������ ������ �°�)
			# INTERVAL YEAR TO MONTH, INTERVAL DAY TO SECOND ������ �ִ�
				# 











--------------------------------------------------------------------------------------------------

<����� ������ ���� ��ɾ� DML>

## 'DATA MANIPULATION LANGUAGE', 'DML'
	# ���������۸�ɾ� 'INSERT', 'UPDATE', 'DELETE'...
		# 'INSERT' : ������ ����

INSERT INTO hr.departments
VALUES (320, 'Oracle Administration', 100, 1700); -- INSERT��. ���� hr.departments�� �÷��� ǥ������ �ʴ´�
	

INSERT INTO hr.employees
VALUES (302, UPPER('Den'), UPPER('Raphealy'),'hong@yahoo.co.kr', '515.127.4561',
TO_DATE('FEB 3, 1999', 'MON DD, YYYY', 'NLS_DATE_LANGUAGE=american'),
'AC_ACCOUNT', 11000, NULL, 100, 30) ;  -- TO_DATE�� �̿��� ���ϴ� ������ ��¥�� ���� �� �ִ�


INSERT INTO hr.sales_reps (id, name, salary, comm, email)
SELECT employee_id, last_name, salary, commission_pct, email
FROM hr.employees
WHERE job_id LIKE '%REP%' ;  -- ���������� �̿��� ���� ���� ���ÿ� INSERT �� �� �ִ�







		# 'UPDATE' : ������ ����

UPDATE hr.copy_emp
SET salary = 8500
,name = INITCAP('SHSHIN')
,hiredate = TO_DATE('FEB 3, 1999', 'MON DD, YYYY', 'NLS_DATE_LANGUAGE=AMERICAN')
,DEPARTMENT_ID = NULL
WHERE id = 113;     -- UPDATE, SET, WHERE �� �̿��� ���� �����Ѵ�


UPDATE hr.copy_emp
SET department_id = (SELECT department_id
					FROM hr.employees
					WHERE employee_id = 100)
WHERE jobid = (SELECT job_id
			   FROM hr.employees
			   WHERE employee_id = 201); -- ���������� ����ؼ� ���� ���� ���ÿ� UPDATE �� �� �ִ�






		# 'DELETE' : ������ ����
		# 'TRUNCATE' : ������ ����2 (�ѹ� �Ұ�)

DELETE FROM hr.copy_emp
WHERE department_id = 30 ;  -- DELETE��


DELETE FROM hr.copy_emp
WHERE department_id = (SELECT department_id
					   FROM hr.departments
					   WHERE department_name LIKE '%Administration%'); -- ���������� ����� ���� ���� DELETE�� �� �ִ�. ('=' �� LIKE�� ���� ������ �����ٰ� �Ѵ�. ������ ���� �䱸�ǹǷ�)


TRUNCATE TABLE hr.copy_emp;  -- TRUNCATE��






	# 'Ʈ�����' (TRANSACTION) COMMIT, ROLLBACK, SAVEPOINT...
		# ���� ����ڵ��� �� ���� �̻��� �۾��� �� �� ���� �����ִ� ��ɹ�(ACTION)���� ����
			# ���� �ϳ� �� �Ѱ��� Ʈ������� �����ϰ� �����Ѵ�
			# 'DML' �۾��� ������ (MSSQL�� �����ϰ�) �׻� COMMIT ����� �־���� �Ѵ�
			# 'DDL' ��ɾ �Է��ϸ� �ڵ����� COMMIT ��ɾ ����ȴ�
				# ���� ������ ���� ��������� �ϴµ�


		# ROLLBACK �� �Է��ϸ� ���ݱ��� �Էµ� ��� ��ɾ���� ��ҵȴ� 
			# (������ COMMIT ��ɾ� ������)
		
		# SAVEPOINT �� �̿��� �߰� Ʈ������� ������ �� �ִ�. (�� ������� �ʴ´ٰ� �Ѵ�)
			# SAVEPOINT insert1; �� ���� �������� ������ �� �ִ�.
			# ROLLBACK TO SAVEPOINT insert1; �� ���� ���������� ���ư� �� �ִ�
			# COMMIT ��ɾ ����ϸ� ��� SAVEPOINT �� �������

		# LOCK
			# ���� �������� �̿��� ���� ��ġ�� ������� �����ϸ� LOCK �� �������ֱ� ������ ��ġ�� ���Ѵ�
				# COMMIT �� ���� LOCK �� �����ȴ�
				# ���̺��� �� �� �� �ึ�� LOCK �� �ɸ���
				
				# 'FOR UPDATE' ������ ����ϸ� ������ LOCK �� �� �� �ִ�
					# COMMIT �̳� ROLLBACK ������ �ٸ� ���������� �ش� ���� ������ �� ����


SELECT employee_id, salary, commission_pct, job_id
FROM hr.employees
WHERE department_id = 90
FOR UPDATE
ORDER BY employee_id ;    -- FOR UPDATE�� �̿��� �ش� ���� LOCK �� �� �ִ�


SELECT e.employee_id, e.salary, e.commission_pct, d.department_name, d.department_id
FROM employees e INNER JOIN departments d
ON e.department_id=d.department_id
WHERE job_id = 'FI_ACCOUNT'
AND location_id = 1700
FOR UPDATE OF e.salary
ORDER BY 1 ;     -- OF e.salary ������ ���� e.salary �ุ LOCK�� �� �� �ִ�


SELECT employee_id, salary, commission_pct, job_id
FROM employees
WHERE job_id = 'FI_ACCOUNT'
FOR UPDATE WAIT 5
ORDER BY employee_id;  -- WAIT 5 �� ���� �ٸ� ���ǻ���ڰ� LOCK ����� ���� �� �ְ� 5�ʰ� ��ٸ���






			# �б� �ϰ��� (Read-Consistency)
				# '���׸�Ʈ'(SEGMENT), '���' (BLOCK)
					# '���׸�Ʈ'�� �� ���̺��� �ڽ��� �����Ͱ� ����� ��������̴�
					# '�����ͺ��'�� �����͵��� ������ ���Ѵ�
						# '��� ���׸�Ʈ' (UNDO SEGMENT)
							# ����Ŭ������ ����ϴ� ���� ��Ű�����̴�
							# COMMIT, ROLLBACK �� �ϱ� ������ �Էµ� �����͵��� ��� ��� ���׸�Ʈ�� ��ϵȴ�	
							# �ٸ� ���ǿ��� �ش� �����͸� ��ȸ�ϸ� '��� ���׸�Ʈ' �����͸� �о�� ���� ���� �� �����͸� �� �� �ִ�(COMMIT, ROLLBACK ������)










--------------------------------------------------------------------------------------------------

<SET �������� Ȱ��>

## UNION, UNION ALL, INTERSECT, MINUS
	# UNION, UNION ALL (������)�� �����ϴ�
		# A UNION (ALL) B ���� �� ������� ���ļ� ����Ѵ�
			# UNION �� �ߺ��� �����ϰ� UNION ALL �� �������� �ʴ´�

	# INTERSECT (������)
		# A INTERSECT B ���� �� ����� �� ���� ���鸸 �� ���� ����Ѵ�

	# MINUS (������)
		# A MINUS B ���� �� ����� �� ù��° �������'��' �ִ� ���� ����Ѵ�




SELECT department_id, NULL AS "LOCATION_ID", hire_date
FROM hr.employees
UNION
SELECT department_id, location_id, NULL
FROM hr.departments;  -- ������ Ÿ���� ���Ͱ��� NULL�� ������ ���缭 ��µǰ� ���� �� �ִ�




SELECT employee_id, job_id
FROM hr.employees
WHERE employee_id IN (101,102,114,122,176,200,201)
UNION (ALL)
SELECT employee_id, job_id
FROM hr.job_history ;  -- UNION�� �̿��� �� ������ ��ġ�� �˾Ƽ� ���ĵǰ� �ߺ��� ���� ���´�
					   -- UNION ALL�̸� �ߺ������� �״�� ��µȴ�



SELECT employee_id, job_id
FROM hr.employees
INTERSECT
SELECT employee_id, job_id
FROM hr.job_history ;  -- INTERSECT �� �̿��� �������� ���� �� �ִ�



SELECT employee_id
FROM hr.employees
MINUS
SELECT employee_id
FROM hr.job_history ;  -- MINUS�� ����� �������� ���� �� �ִ�















--------------------------------------------------------------------------------------------------

<���� ���� (SUB QUERY)>

## ���� ���� �ȿ� �Ǵٸ� ������ �ִ� ������ '���� ����'��� �Ѵ� 
	# �������� {...}
			   {...} (��������);
	# '��������' �ȿ��� ORDER BY ���� ���� �� ���� (�������� �ۿ��� ���� �� �ִ�)
	# WHERE , HAVING ���� ������ ����� �� �ִ�.
		# ������, ������ ���������� ���� �� �ִ�
		# ������ ���������� IN, ANY, ALL ���� �����ڿ� ���� �� �� �ִ�
			# �÷� < ANY (��������) : �÷��� ���� ū ������ ������ ��
			# �÷� > ANY (��������) : �÷��� ���� ���� ������ ũ�� ��
			# �÷� > ALL (��������)
				# ������ ������ ���� �Ⱦ��̰� MIN, MAX �� ��ü�ȴ�
	
		# IN, NOT IN
			# WHERE employee_id IN (��������)
		  	  WHERE employee_id NOT IN (��������) 

			
SELECT employee_id, last_name, salary, manager_id
FROM hr.employees
WHERE employee_id NOT IN (SELECT manager_id
						  FROM hr.employees
						  WHERE manager_id IS NOT NULL)
ORDER BY 1 ;   -- NOT IN �� IS NOT NULL�� ���� ����� ������ ������ �� �ִ�. NOT IN�� (...) �ȿ� null ���� ������ �׻� ������ ���� �����̴�. 
-- ���� ���̺��� �Ӽ����� NULLABLE ���� Ȯ���ؼ� IS NOT NULL�� ���� ���� �����Ѵ�.



SELECT last_name, salary
FROM hr.employees
WHERE salary = (SELECT MIN(salary)
				FROM hr.employees
				GROUP BY department_id ) ;  -- �� ������ ������ ���µ� ���������� ����(12��)���� ����ϱ� �����̴�. IN�� ����ϸ� �������� ���� �� �ִ�.



SELECT department_id, AVG(salary)
FROM hr.employees
GROUP BY department_id
HAVING AVG(salary) = (SELECT MAX(AVG(salary))
					  FROM hr.employees
					  GROUP BY department_id);  -- ����� ���� ���̴� �����̴�. ����ӱ��� ���ؼ� �ִ� ����ӱ��� ����ϴ� �����̴�.









--------------------------------------------------------------------------------------------------

<�� ���̺��� ���� �����ϱ�>

## JOIN, ON...
	# 'INNER JOIN'(EQUI-JOIN, NONEQUI JOIN) , 'OUTER JOIN' , 'CROSS JOIN', 'ORACLE JOIN' , 'NATURAL JOIN' ���� ���� �� �ִ�
		# �׳� JOIN�� �Է��ϸ� INNER JOIN�� ����Ʈ������ �����ȴ�

	# 'INNER JOIN'
		# 'EQUI-JOIN', 'NON-EQUI JOIN'(JOIN�� 90% �̻��� �����Ѵ�)
			# ON �ȿ� �ִ� ������ �������� �˻��ϸ�
			# �ƴϸ� NON-EQUI JOIN�̴�
				# ON (e.salary BETWEEN j.lowest_sal AND j.highest.sal) �� ���� ON ������ EQUI�� ���� �ʴ�
		# 'SELF JOIN'
			# 'EQUI-JOIN'�� �� �κ��̴�

SELECT a.last_name AS "BUHA", b.last_name AS "BOSS"
FROM  hr.employees a INNER JOIN hr.employees b
ON (a.manager_id= b.employee_id)  
WHERE a.employee_id = 101 ;     -- SELF JOIN�� �̿� ���� �� ���̺��� ������ �� �� ����Ѵ�





	# 'OUTER JOIN' (LEFT, RIGHT, FULL)
		# INNER JOIN�� ���� ��µ��� ���� ������� �����ִ� JOIN ('INNER + @'�� ȿ��)
		# LEFT, RIGHT, FULL�� JOIN Ű���带 �������� ����, ������, �Ѵ� ����ϴ°� ���Ѵ�
			# LEFT OUTER JOIN, RIGHT OUTER JOIN, FULL OUTER JOIN


SELECT e.last_name, d.department_name ,d.department_id
FROM hr.employees e, hr.departments d
WHERE e.department_id (+) = d.department_id ;
�Ǵ�
WHERE e.department_id = d.department_id (+); -- (+) ������ �̿��� OUTER JOIN�� ����� �� �ִ� (���� ��õ������ �ʴ� ���)




	# 'CROSS JOIN'
		# ��ĥ �� ���� ���� ������ ��ĥ �� ����Ѵ�
		# ������ �� ��ġ�� �� ���̺��� ������ ��ġ�µ� ������ 'INNER JOIN' ������� ���� ���� ���� 'INNER JOIN'���� �ӵ��� ������



	# 'ORACLE JOIN'
		# ORACLE������ �� �� �ִ� JOIN (ON ���� ����)
		# �ٸ� ���ΰ� �޸� WHERE ���� ����Ѵ� 
			
SELECT e.last_name, d.department_name ,d.department_id
FROM hr.employees e, hr.departments d
WHERE e.department_id = 90
AND e.department_id = d.department_id ;  -- WHERE ���� ����� ORACLE INNER EQUI JOIN�̴�

	


	# 'NATURAL JOIN'
		# ���� �� �߿�~

	
	# 'PRIMARY KEY', 'FOREIGN KEY' (1 : �ټ� ����)
		# �� ���� JOIN�� ����ؾ� �ϰ� ��� �̸��� ���Ƶ� PRIK, FORK�� ���谡 �ƴϸ� ����ϸ� �ȵȴ�(���� ������ �ʿ��ѵ�)




SELECT e.employee_id, e.last_name, e.department_id, d.department_name
FROM hr.employees e JOIN hr.departments d
ON (e.department_id = d.department_id)
order by 3 ; -- ���̺� �̸��� �ʹ� �� ���� ����Ƿ� TABLE ALIAS�� ����ؼ� �����ϰ� �Ѵ�


SELECT hr.employees.employee_id, hr.employees.last_name, hr.employees.department_id , hr.departments.department_id, hr.departments.department_name 
FROM hr.employees INNER JOIN hr.departments 
ON (hr.employees.department_id = hr.departments.department_id) 
order by 3 ;  -- ON�� �̿��� �� ���̺��� department_id ���� ������ INNER JOIN ���� �� ���̺��� ���� �����´� 


SELECT e.employee_id, e.last_name, e.department_id, d.department_id, d.department_name
FROM hr.employees e RIGHT OUTER JOIN departments d
ON (e.department_id = d.department_id) ; -- RIGHT OUTER JOIN �� �̿��� ����� ����Ѵ�




--------------------------------------------------------------------------------------------------------

<������ �Լ�>

## ������ �Լ� : SUM, AVG, MAX, MIN, COUNT, STDDEV, VARIANCE...
	# SUM, AVG �� ���ڸ� �����ϴ�
	# MAX, MIN, COUNT �� ����, ����, ��¥ ���� ��� �����ϴ�
		# MAX , MIN �� LONG, CLOB ������ �������� ��� ���Ѵ�
			LONG: �ִ� 2GB ���̱��� ������ ���� ������
			CLOB: �ִ� 4GB ���̱��� ������ ���� ������

	# �����Լ����� ALL , DISTINCT �� �߰��� ����� �� �ִ�
		# ������� SUM(ALL score) , SUM(DISTINCT score) �� ���� �� �� �ִ�.
		# DISTINCT : �ߺ��� ���� ��ǥ������ ġ�� �� ���� ���Ѵ�
		# �⺻������ null ���� �����Ѵ�
			  AVG(score)          : 300/4
			  AVG(NVL(score,0))   : 300/5
			  COUNT(score)        : 4
			  COUNT(NVL(score,0)) : 5     == COUNT(*) ��� ������ ��ġ�Ѵ�(�ʹ� ���� ������ �ϳ� ���� ����)
			  -- ��ó�� ���� null�� ���� �޶�����

SELECT COUNT(*) FROM hr.employees -- hr.employees ���̺��� ������ ������ ����Ѵ�



	# GROUP BY �� HAVING
		# {...1} UNION ALL {...2}  : 1�� 2�� ��� ���ڵ带 �ٿ��� �����ش�
		# GROUP BY
			# �����͸� �ϰ������� ó���ϱ� ���� (�κ�����) (��û���� ���� ���δ�)
			ex) ���� ���� �հ�, �ð��� ���� �հ�, ���ະ ���ݾ� �հ�, ������ ���� �հ�...
			
			# �׻� SELECT ���� �ִ� �÷� ���� GROUP BY ���� ������� �Ѵ� (�����̴�)
			# WHERE ������ SUM(salary)�� GROUP BY �� ���� �Է��� �� ���� (HAVING ���� ��ü ����)
			

SELECT department_id, AVG(salary) AS "AVG_SAL_PER_DEPT" , COUNT(*) AS Persons 
FROM hr.employees 
GROUP BY department_id ;  -- department_id�� ���� SELECT�� �÷����� �׷����� �����ش�



		# HAVING
			# �����Լ����� ���� ����� ������ �� �ִ�
			# WHERE ���� ���� ���Ѱ�ó�� SUM(...) �̷��� ���ϴ� ��� HAVING ���� ���� ����� ������ �� �ִ�
		





--------------------------------------------------------------------------------------------------------------------


<�Ϲ� �Լ�>

## �Ϲ��Լ��� NVL,NVL2,NULLIF,COALESCE... �̸� �ַ� null���� ���� ������ �ִ�
	# �����Լ��� CASE, DECODE...
	
	NVL(commission_pct,0) -- commission_pct ���� null�� ��� 0���� �����Ѵ�
	NVL2(commission_pct,'OK','NO') -- commission_pct ���� null�� �ƴϸ� OK, null�̸� NO�� ��ȯ�Ѵ�
	NULLIF(LENGTH(first_name),LENGTH(last_name)) -- �� ���� ������ null, �ٸ��� �տ� ���� ��ȯ�Ѵ�
	COALESCE(������,Ŀ�̼�,-1) -- ���� �ִ� 3�� �� �� ���ʷ� null�� �ƴ� �÷��� ���� ǥ���Ѵ�. 3�� ������ ���� ���ƾ� �Ѵ�.


	(CASE job_id WHEN 'IT_PROG' THEN 1.10*salary WHEN 'ST_CLERK' THEN 1.15*salary ELSE salary END) AS "REVISED_SALARY" -- DECODE�� ����� �Ȱ��� �Լ�. Mysql�̳� MSsql���� ����� �� �ִ�
	(CASE WHEN salary < 5000 THEN 'Low' WHEN salary < 10000 THEN 'Medium' WHEN salary < 20000 THEN 'Good' ELSE 'Excellent' END) -- �˻��� CASE �����̶�� �Ҹ��� ���ǽ��� �� �� �ִ� (DECODE�� �Ұ���)(CASE�� DECODE���� �� ������)


	DECODE(job_id, 'IT_PROG', 1.10*salary,
					'ST_CLERK', 1.15*salary, salary) AS 'REVISED_SALARY' -- job_id ���� ���� ���ǽ��� �����. ������ salary�� ���������ϴ� (����Ŭ���� �����ϴ� �Լ�)




-------------------------------------------------------------------------------------------------------------------


<������ �Լ�>

## ������ �Լ� <====> ������ �Լ�
	# '������ �Լ�'�� �� �� �� �ٸ��� ��ɾ �����ϴ� ��
	# '������ �Լ�'�� ��� �����͸� ��Ƽ�(?) �� �� �����ϴ� ��
	# �Լ��� �׽�Ʈ ���� ���Ͽ� ����� �� �ֵ��� DUAL ���̺�
		# DESC DUAL;
	
	# ���� �Լ�
		# UPPER, LOWER, INITCAP, CONCAT, SUBSTR, LENGTH, LENGTHB, REPLACE, LPAD, RPAD, TRIM,INSTR...
			UPPER('last_name');  -- ���� �빮�ڷ� �ٲ۴� 
			INITCAP('first_name'); -- ù���ڸ� �빮�ڷ� �ٲ۴�
			SUBSTR('200080815',-2); -- �ڿ��� 2��° ���ں��� ������ �����Ѵ�
			REPLACE('JACK and JUE','J','BL');	-- 'J'�� 'BL'�� �ٲ۴�
			TRIM('S' FROM 'SSMISTMSS') AS "RESULT";  -- ���ڿ����� 'S'�� ���ش�
			INSTR('HELLO ORACLE','L',1,1) "RESULT"; -- 1��° ���ں��� 1��° ������ L�� ��ġ
			INSTR('HELLO ORACLE','L',4,2) "RESULT"; -- 4��° ���ں��� 2��° ������ L�� ��ġ
	
		# INSTR�� ���� ���� Ȱ���ϴ� �Լ� �� �ϳ��̴�




	# ���� �Լ�
		# ROUND, TRUNC, MOD...
			ROUND(1726.236,2);   -- �Ҽ��� 2�ڸ����� ��ȿ�ϴ� : 1726.24
			ROUND(1726.236,-2);	 -- �Ҽ��� -2�ڸ�(���� 2�ڸ�)���� ��ȿ�ϴ� : 1700
			TRUNC(1726.236,2);   
			TRUNC(1726.236,-2);
			MOD(1600,300);    -- 1600�� 300���� ���� �������� ����Ѵ�




	# ��¥ �Լ�
			# MONTHS_BETWEEN, ADD_MONTHS, NEXT_DAY, LAST_DAY...
			SELECT MONTHS_BETWEEN(TO_DATE('1995/09/01','yyyy/mm/dd'), TO_DATE('1995/12/12','yyyy/mm/dd')) FROM dual; -- ������ ������ �� ���� ���̸� ã�´�
			SELECT NEXT_DAY(TO_DATE('08/11/11','YY/MM/DD'),6) FROM dual; -- ������ date �� ������ ���� ������ ������ ã�´� 1~7(��~��)


			# ����(Ŭ���̾�Ʈ)�� ��¥ ǥ�������� ������ ���� ������ �� �ִ�
				# ȯ�漳�� -> �����ͺ��̽� -> NLS���� ������ ���� �ִ�.
				ALTER SESSION SET NLS_DATE_FORMAT='YYYY/MM/DD' ;
					'YYYY/MM/DD HH24:MI:SS' ���� �ú��ʵ� �߰��� �� �ִ�



	# ��ȯ �Լ�
		# TO_DATE, TO_CHAR, TO_NUMBER...
			TO_DATE('2002-06-15','YYYY-MM-DD');  -- �ſ� �߿�! �ý���(�̳� ����)���� ǥ���ϴ� ��¥ ü�谡 �ٸ��Ƿ� TO_DATE�� ����� �ټ� �ִ�.
			# ��ǥ���� ���� ��
				YYYY, MM ,DD ,DAY, HH24, MI, SS, AM... ��� ���� �ִ�
				TO_CHAR(SYSDATE, 'YYYY/MON/DD HH24:MI:SS AM DAY');
				TO_CHAR(sysdate, 'YYYY-mON-DD HH24:MI:SS AM DaY','NLS_DATE_LANGUAGE=AMERICAN')     -- ���� �������� ǥ��ǰ� �ٲ۴�. �տ� mON, MOnth, mon, MON � ���� ǥ�� ������ �޶�����
				TO_CHAR(sysdate, 'YYYY" �� " MM"��" DD"��" HH24"�� " MI"��" SS "��" AM Day')        -- ��¥ �����ڸ� ���ϴ� ���ڷ� �ٲ۴�







'������ �Լ�'
SELECT last_name, UPPER(last_name) AS "UPPER_NAME", salary FROM hr.employees WHERE department_id = 90 ;

'������ �Լ�'
SELECT SUM(salary) FROM hr.employees WHERE department_id = 90;













------------------------------------------------------------------------------------------------


<SELECT ���� ����>

## 'q' �����ڴ� ����Ŭ���� �����ϰ� ANSIǥ���� �ƴϴ� 
	�ο�� ����Ѵ�



## DISTINCT ������
	# �ߺ��� ���ڵ带 �� ���� ǥ���Ѵ�
	# ORDER BY�� ���� �Ⱦ��°� �����Ѵ� (�޸� ����?)

SELECT DISTINCT department_id, job_id FROM hr.employees WHERE department_id = 30 ;




## ���Ῥ����(||)�� ������ �� �ڷ� ��õ� �� ���� ���ڿ��� ���Դϴ�

SELECT last_name || JOB_ID AS "RESULT" FROM hr.employees WHERE employee_id = 100 ;





## Literal Chracter String
	# ����� �״�� ������ ���ڿ��� ���ϴµ�

SELECT last_name , 'is a', 90 , job_id FROM hr.employees WHERE department_id = 90 ;





## WHERE ���� 
	# WHERE�� �ȿ� ���ǹ�
	# BETWEEN, IN(set), LIKE, IS NULL
		# IN�� ������ �� ���տ��� ���� ������ �� ����Ѵ�
		  ex) manager_id IN (100,101,201);
		# LIKE�� ���� ���ڿ��� ã�´� 
		  ex) LIKE 'S%'; LIKE '_o%'; LIKE '%o%'; ��� 
			#'_'�� �� ���� '%'�� ���� ���� '\_'�� �̽����̽� ���ڸ� ����Ų��
		  	ex) LIKE 'AD\_%' ESCAPE '\';    '

	# > = >= < <= <>(���� ���� != ^=...) ����� �ִ�

SELECT last_name, job_id, department_id,salary FROM hr.employees WHERE last_name = 'Smith' AND salary >= 7500;





## ������ ���� �ð��� ��¥�� DATE �������� ��ȯ�Ϸ���

SELECT sysdate FROM dual;






## ORDER BY ��
	# ORDER BY hire_date ASC(or DESC) ��������, ������������ �����Ѵ�
	# SELECT employee_id(1), last_name(2), salary(3) from ... where ... order by 3 ASC
		# ���� ������ 3���� �� �� 3��° �÷�(salary) ������ ������������ �����Ѵ�
	
	# �׳� ORDER BY�� ������ ASC��� �����Ѵ�
	# NULL FIRST, NULL LAST �� ����Ŭ���� �ִ� ���� ��ɾ��� �Ѵ�






	
-------------------------------------------------------------------------------------------


## HR (Human Resource) ���� ���� ����
ALTER user hr IDENTIFIED BY oracle4U ACCOUNT UNLOCK;


## '������(Data)'�� ��ü������ ǥ���� �ϳ��� ���� �ǹ��մϴ�.
���� ���, �Ʒ����� "ȫ�浿"�� "01024567856"�� ���� "�̸� ������", "��ȭ��ȣ ������"��� �մϴ�.


## '����(Information)'�� �����(Client)���� Ư���� �ǹ̸� ������ �������� ����(Data-Group)�� �ǹ��մϴ�.
���� ���, �Ʒ����� "ȫ�浿"�� "01024567856"�� 2 ���� �����Ͱ� ���յǾ� "ȫ�浿�� ����ó ����"��� �մϴ�.
�̸� ������
��ȭ��ȣ ������
�� ȫ�浿�� ����ó ����
ȫ�浿
01024567856

## '��(Row)'�� Ư�� ���̺� ���ǵ� ��� �÷����� ����� ������ �����͵� �� ���� ������ �ǹ��մϴ�.

## '���ڵ�(Record)'�� �࿡��, �ϳ� �̻��� �ʵ忡 �ִ� ������ ������ �ǹ��մϴ�. �̷��� ���ڵ尡 �����-���α׷�����
ó���Ǵ� ������ �������� ���˴ϴ�.





2016/07/18 �� ���۵� ORACLE 11g �����ͺ��̽� ���� / �Ż��� ����









