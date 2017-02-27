
--------------------------------------------------------------------------------------------------

	$$ ���� ORACLE_HOME/RDBMS/ADMIN/
		$ ���� ������ 1594�� ������ ���� �����ǰų� �����Ǹ� �ȵ˴ϴ�
		$ �����Ǹ� DBCA�� DB�� ���� �� �ȸ�������ٰ� �մϴ�
		$ �� ���� �ȿ� catalog.sql, catproc.sql 
   		$ �� ������ �������Ϸ� ������ 1300���� sql ������ �ε��մϴ�
   		$ utl* �� �����ϴ� 69�� ������ ����ڰ� �����ص� �����ϴٰ� ������ (����Ŭ �ǰ�) �ظ��ϸ� �Ȱŵ�°� �����ϴ�



<SYS ����� ����>


## 'SYSDBA'�� 'SYSOPER' �׸��� 'SYS' ����
	# SYSDBA : DB ������ ����� ���� �����Դϴ�
	# SYSOPER : DB �⵿/������ ������ �����Դϴ�
	# �� ���� ��� SYS �������� �ο��Ǿ� �ֽ��ϴ�


	# 'LINUX'�� oinstall, dba�� ���� ������ �׷��� ������ �� �ֽ��ϴ�
		# oinstall �׷� : ����Ʈ���� ��ġ/������ å������ �׷��Դϴ�
		# dba �׷� : �����ͺ��̽� ������ �ϴ� �׷��Դϴ�

	# 'WINDOWS'�� �ڵ����� ora_dba �׷��� ������ �ü�� ������ ��Ͻ�ŵ�ϴ�



	# SYS ������ ������� 2��
		# OS ����
			# conn / as sysdba : ���� ��Դ� �α��� ������� ������/�н����带 Ȯ������ �ʽ��ϴ� 
			# ���������� ��쿡�� ��밡���մϴ�
			# sqlnet.ora ���Ͽ��� (NTS)�� (NONE)���� �ٲٸ� OS ��������� ���̻� �۵����� �ʽ��ϴ� 



		# PASSWORD-FILE ����
			# �������ӽ� �����ʰ� ������ ������ PASSWORD-FILE�� ����� ������/�н����带 Ȯ�� �� ������ ����մϴ�
			# ORACLE_HOME\database\PWDorlc.ora ������ ���� �����մϴ� 
			
			# REMOTE_LOGIN_PASSWORDFILE �ʱ�ȭ �Ķ����
				# EXCLUSIVE : PASSWORD-FILE �� ������ �������� �ʽ��ϴ� (DEFAULT)
				# SHARED : PASSWORD-FILE ��������� �����մϴ�
					# PWDorcl.ora ���� ������ �� �� �����ϴ�.



				# PWDorcl.ora ������ ���� ��� (�����ġ)
					# �� �̻� ���������� �ȵ˴ϴ� conn sys/oracle4U@orcl as sysdba ����!
					# orapwd�� ����� �н����� ������ �����մϴ�


orapwd file=C:\app\buk213\product\11.2.0\dbhome_1\database\PWDorcl.ora 
entries=3 password=oracle4U








	# ��������
		# ����(DYNAMIC) ���� ��� : MOUNT, OPEN ���¿����� SYSDBA�� ������ �� �ֽ��ϴ�
		
		# ����(STATIC) ���� ��� : SHUTDOWN, NOMOUNT, MOUNT, OPEN ���� ��� SYSDBA ���� �����մϴ�
		


SELECT sys_context('USERENV','OS_USER') FROM dual;  -- ���� ����� ������ ���ϴ�







	# �Ϲ� �����ͺ��̽� �������� SYS ������ �ο��� ���	


GRANT sysdba TO hr ; -- hr �������� SYSDBA ������ �ݴϴ�

conn hr/oracle4U@orcl  -- �׳� hr �������� �����մϴ�

conn hr/oracle4U@orcl as sysdba  -- SYSDBA ������ ���� �������� �����մϴ�

SELECT * FROM v$pwfile_users ; -- SYSDBA ������ ���� ���� ������ �� �� �ֽ��ϴ� 

REVOKE sysdba FROM hr ; -- hr ������ sysdba ������ �����մϴ� 






	

	# WITH ADMIN OPTION ���
		# ���� sysdba ==> devuser01 ���� with admin option �� �ָ�
		# devuser01 ==> devuser02 ���Ե� with admin option �� �� �� �ֽ��ϴ�
		# �̴� sysdba�� devuser01 �� ������ ��Ż�ص� devuser02�� ��� �����˴ϴ�

GRANT create table, connect
TO devuser01
WITH ADMIN OPTION ;  -- devuser01���� �ý��� ������ ���� �ο��մϴ�

		








	# �����ͺ��̽��� �̸� ���ǵ� �� (Predefined ROLE)
		# ���� 2���� ���� �����ͺ��̽� ������ �����ϸ� �ڵ����� �����˴ϴ�
			# CONNECT �� :
			# RESOURCE �� :
		
		# ��Ÿ �������� �ѵ�
			# DBA �� : DB�� �����ϴ� 202���� ������ ����� �� �ֽ��ϴ�
			# SELECT_CATALOG_ROLE �� : �Ϲݰ����� DBA�� ��ȸ������ ��ųʸ� �並 ��ȸ�� �� �ֽ��ϴ�
			# SCHEDULER_ADMIN �� : {...}


		# ����ڰ� ���� ���� ���� �� �ֽ��ϴ�  





CREATE ROLE DEVROLE ;  -- ���� �����մϴ�



GRANT CREATE CLUSTER, CREATE INDEXTYPE,
CREATE OPERATOR, CREATE PROCEDURE,
CREATE SEQUENCE, CREATE TABLE,
CREATE TRIGGER, CREATE TYPE,
CREATE VIEW, CREATE SYNONYM,
ALTER SESSION
TO DEVROLE ;   -- DEVROLE �� �ش� ������ �ο��մϴ� 




GRANT connect, devrole
TO devuser01 ;  -- CONNECT, DEVROLE ���� devuser01���� �ο��մϴ� 



GRANT SELECT_CATALOG_ROLE TO devuser01; -- SELECT_CATALOG_ROLE���� devuser01 �������� �ο��մϴ�
										-- DBA�� �� �� �ִ� ����� �� �� �ֽ��ϴ�

SELECT name FROM v$datafile;   -- DBA�� �� �� �ִ� ���Դ�

��


SELECT * FROM session_privs ;  -- ���� ������� ���� ������ �� �� �ֽ��ϴ� 







		# DEFAULT ROLE (����Ʈ ��)�� �̿��� ���� ���� 
			# �������� �ο����� �� �߿��� �α��� �� ����� �� �ֵ��� Ȱ��ȭ�� ���� ���մϴ�
			# ��ȣ�� �ɸ� ���� �ڵ����� DEFAULT ROLE���� ���ܵ˴ϴ� 



CREATE USER roleuser
IDENTIFIED BY oracle4U
DEFAULT TABLESPACE users
TEMPORARY TABLESPACE temp
QUOTA unlimited ON users ;  -- roleuser ������ ����ϴ�


GRANT role1, role2, role3
TO roleuser ;  -- role1,2,3�� ����ڿ��� �ο��մϴ� (role2,3�� ��й�ȣ�� �ɷ��ִ� ��Ȳ)


SELECT granted_role, default_role
FROM user_role_privs ;   -- DEFAULT ���� Ȯ���մϴ�


SELECT *
FROM session_roles ;     -- ����� �� �ִ� �ѵ��� Ȯ���մϴ�
 


	




	# PROFILE (��������)�� �̿��� ���� ����
		# ����ں��� ���ҽ� �Ҹ��� ������ �� �ַ� ����մϴ�
		# �н����� ���� ��å�� ������ �� �ֽ��ϴ� 

			# RESOURCE_LIMIT �Ķ����
			# �⺻���� FALSE �̰� TRUE �� Ȱ��ȭ�� �����ָ� ������ �� �� �ֽ��ϴ�
			
		# ����Ŭ �����ͺ��̽� ������ �����ϸ� DEFAULT, MONITORING_PROFILE �̸��� PROFILE�� �����˴ϴ� 
			
		# DEFAULT PROFILE (����Ʈ ��������)
			# 11g �������ʹ� DEFAULT PROFILE�� PASSWORD ���� ��å�� ����ó�� �����Ǿ����ϴ�
				# PASSWORD_LIFE_TIME 180
				# PASSWORD_GRACE_TIME 7
				# FAILED_LOGIN_ATTEMPTS 10
				# PASSWORD_LOCK_TIME 1
			
			# ��ó�� ������� �����Ÿ� �ݵ�� DEFAULT PROFILE�� �����ؾ��մϴ�
			# sql> ALTER PROFILE DEFAULT LIMIT
				   PASSWORD_GRACE_TIME UNLIMITED
				   PASSWORD_LIFE_TIME UNLIMITED;





-- PROFILE�� �����մϴ�
CREATE PROFILE myprof1
LIMIT
CPU_PER_SESSION 36000    -- ������ ���ǿ��� ��밡���� CPU ��� �ð� (1/100��)
CPU_PER_CALL 1000        -- �ϳ��� �ݴ� ��밡���� CPU�� ���ð� (1/100��)
CONNECT_TIME 300         -- ������ �����Ǵ� �ִ�ð� (��)
IDLE_TIME 5              -- ���� �� IDLE ���°� ���ӵǴ� �ִ�ð� (��)
SESSIONS_PER_USER 3      -- ���ÿ� ���Ӱ����� ���� ���� �����մϴ�
LOGICAL_READS_PER_SESSION 1000    -- ���� �� ��밡���� BUFFER CACHE�� �ִ� ���� ����
LOGICAL_READS_PER_CALL 500        -- �ϳ��� SQL���� ó�� ��  "
PASSWORD_LIFE_TIME 10      -- �н����尡 ��ȿ�� �ִ�Ⱓ (��)      
PASSWORD_GRACE_TIME 2      -- LIFE_TIME�� ������ �߰������� �α��� ��� �Ⱓ (���â ����) (��)
PASSWORD_REUSE_MAX 3       -- ������ ����� �н����带 ���� �� ���ְ� ������ִ� �Ⱓ (�� )
PASSWORD_REUSE_TIME UNLIMITED   
PASSWORD_LOCK_TIME 10      
FAILED_LOGIN_ATTEMPTS 5    -- ���� �н����� ���� Ƚ�� 
PASSWORD_VERIFY_FUNCTION null ;  -- �н������� ���⼺�� �˻��ϴ� �Լ� �̸��� �����մϴ�

-- PRIVATE_SGA :  ������ ���ǿ� ���� PGA ������ SGA�� ĳ���� ��ų �� SGA �޸��� �� (�� �Ⱦ��Դϴ�)(����ڰ� ����� ���ϸ鼭 ������ ��� �����ϸ� �޸� ���� Ŀ���Ƿ�)(�ַ� RMAN���� �����մϴ�) 


ALTER USER hr
PROFILE myprof1 ;   -- hr ������ myprof1 ���������� �ݴϴ�






		# �н����� ���⵵ �Լ� (PASSWORD_VERIFY_FUNCTION)
			# dbhome_1/RDBMS/ADMIN/utlpwdmg.sql ���Ϸ� �н����� ���⵵�� ������ �� �ֽ��ϴ� 
				
			# ������ c:\app\buk213\ �� �����ð� �� ���� �����մϴ�
				# sql�ȿ��� @c:\app\buk213\utlpwdmg.sql �� ��ũ��Ʈ�� �����մϴ�
				# verif_function_11G �Լ��� �߰��Ǿ����ϴ�

	




ALTER PROFILE myprof1 LIMIT
PASSWORD_VERIFY_FUNCTION verify_function_11g ;   -- ��� �߰��� �Լ��� �����մϴ�

					

SELECT username, profile
FROM dba_users
WHERE username IN ('SYS','SYSMAN','SYSTEM','DBSNMP'
,'HR','SH','OE') ;    -- �� �������� �������� ������ Ȯ���մϴ�



set pagesize 999
col profile format a10
col resource_name format a30
set linesize 200
SELECT *
FROM dba_profiles
WHERE profile = 'MYPROF1'
ORDER BY 3,2 ;   -- MYPROF1 ���������� ������  �ڼ��ϰ� Ȯ���մϴ�




SHOW PARAMETER resource_limit   -- RESOURCE_LIMIT �Ķ���͸� Ȯ���մϴ� (TRUE���� �����)

ALTER SYSTEM SET
resource_limit=true SCOPE=both ;  -- �ش� �Ķ���͸� TRUE�� �ٲߴϴ� 


col username format a30
col profile format a30
set pagesize 50000
SELECT profile, username
FROM dba_users
WHERE profile LIKE 'MYPROF%'
ORDER BY 1 ,2 ;     -- MYPROF�� ��� ���� ����� ������ Ȯ���մϴ�


DROP PROFILE myprof1 CASCADE ;  -- PROFILE�� �����մϴ� (CASCADE�� ����ؾ��մϴ�)
-- CASCADE�� ����ϸ� ���� �� ���������� ������� ������ �ڵ����� DEFAULT ���������� ����մϴ�















--------------------------------------------------------------------------------------------------

<Ŭ���̾�Ʈ ����� ����>


## �����ͺ��̽� ����� ���� (����Ŭ������ ����ϴ� ��츸 �����մϴ�)
	# �������� �α��� ���� ��ĵ�
		# PASSWORD ���� : DATA DICTIONARY ������ �н����带 �����س��� ���ӽ� Ȯ���ϴ� ����Դϴ�
		# EXTERNAL ���� : OS �����̰��ϸ� ������������ �����մϴ� (���� �Ⱦ��ϴ�)
		# GLOBAL ���� : ���� ������� �ʽ��ϴ�

	# ��ųʸ� ��
		# DBA_USERS : �����ͺ��̽� ������ ���� ������ ���� ������ �����մϴ�



	# ����� ���� ������ ���� �ǽ�
		# �ӽ�-���̺����̽� 3���� ����� �׷�ȭ��ŵ�ϴ�



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
AUTOEXTEND ON NEXT 10M MAXSIZE unlimited ;  -- �ӽ�-���̺����̽� 3���� ����ϴ�



ALTER TABLESPACE temp11
TABLESPACE GROUP temp_grp1 ;

ALTER TABLESPACE temp22
TABLESPACE GROUP temp_grp1 ;

ALTER TABLESPACE temp33
TABLESPACE GROUP temp_grp1 ;  -- �ӽ�-���̺����̽��� �׷�ȭ�մϴ�



SELECT * FROM dba_tablespace_groups ;  -- �ӽ�-���̺����̽� ������ Ȯ���մϴ�

SELECT tablespace_name
FROM dba_tablespaces
WHERE contents = 'TEMPORARY' ;   -- �ӽ�-���̺����̽� ������ Ȯ���մϴ�2








		# ����-���̺����̽� 2���� ����ϴ�


CREATE TABLESPACE udata_insa
DATAFILE 'C:\app\buk213\oradata\orcl\udatainsa01.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 20M MAXSIZE unlimited
UNIFORM SIZE 1M ;



CREATE TABLESPACE udata_cust
DATAFILE 'C:\app\buk213\oradata\orcl\udatecust01.dbf'
SIZE 11256K
AUTOEXTEND ON NEXT 20M MAXSIZE unlimited ;  -- ����-���̺����̽��� 2�� ����ϴ�


SELECT tablespace_name
FROM dba_tablespaces
WHERE contents = 'PERMANENT'
AND tablespace_name not in ('SYSTEM','SYSAUX');  -- ���̺����̽��� Ȯ���մϴ�













		# ����� ���� 2���� �����մϴ�
			# QUOTA : �ش� ���̺����̽� ������ ������ �����ϰڴ�/�������� �ʰڴ� ����մϴ� 
				# �ݵ�� ����� ���̺����̽��� ��� ����ؾ� �մϴ�
				# ���, �ӽ�-���̺����̽����� ������� �ʽ��ϴ�





CREATE USER devuser01
IDENTIFIED BY oracle4U
TEMPORARY TABLESPACE temp33     -- PGA �޸𸮰� ������ �� temp33 �ӽ�-���̺����̽��� ����մϴ�
ACCOUNT unlock					
PASSWORD EXPIRE					-- ó�� �α����� �� ������ ��ȣ�� �ٲٵ��� ����ϴ�
DEFAULT TABLESPACE users		
QUOTA unlimited on example		
QUOTA unlimited on users
QUOTA unlimited on udata_insa
QUOTA unlimited on udata_cust ;  



CREATE USER devuser02
IDENTIFIED BY oracle4U
TEMPORARY TABLESPACE temp_grp1   -- PGA �޸𸮰� ������ �� temp_grp1 �ӽ� �׷��� ����մϴ�
ACCOUNT lock					 -- ������ ��޴ϴ�
DEFAULT TABLESPACE users
QUOTA unlimited on users
QUOTA 10M on example			 -- QUOTA : example ���̺����̽��� 10 Mb�� ����� �� �ְ� �մϴ�
QUOTA unlimited on udata_insa
QUOTA unlimited on udata_cust ;



GRANT create session, create table
TO devuser01, devuser02 ;         -- �� ������ ���� ������ �ݴϴ�







 -- ������ ������ ������ Ȯ���մϴ� 



col username format a10
col tablespace_name format a10
set linesize 150
SELECT username, tablespace_name, bytes/1024/1024 used_MB
,max_bytes, dropped
FROM dba_ts_quotas
WHERE username IN ('DEVUSER01','DEVUSER02')
order by 1, 2 ;  -- ������ ������ QUOTA�� ���� ������ ����մϴ�



			





			# ������ ������ ������ �����մϴ� (�����ڸ� ����)


ALTER USER devuser01
TEMPORARY TABLESPACE temp ;   -- ������� �ӽ�-���̺����̽��� �����մϴ�


ALTER USER devuser01
DEFAULT TABLESPACE example ;  -- ������� �⺻-���̺����̽��� �����մϴ�


ALTER USER devuser01
QUOTA unlimited ON udata_insa
QUOTA 10M ON udata_cust
QUOTA 0 ON example ;    -- ������� QUOTA ������ �����մϴ�


ALTER USER devuser01
ACCOUNT lock
PASSWORD EXPIRE ;    -- ������ ��װ� �н����带 �ı��մϴ�


GRANT unlimited tablespace
TO devuser01 ;     -- ����ڿ��� ��� ���̺����̽��� ������ �� �ִ� ������ �ݴϴ�















---------------------------------------------------------------------------------------------------

<Flash Recovery Area�� ��ī�̺� �α� ���>


## Flash Recovery Area
	# Storage ��� ����ũ�� ������ ���� ������ ������ ���� ����Դϴ�
		# ���� ���������ġ�� TAPE ������ġ�� ������ �ӵ��� �ſ� �����ϴ�

	# ��ֺ��� �� ���Ϻ����� ������ ������ �� �ֽ��ϴ�

	# ���� ���� �Ķ���͵� (Parameters)
		# DB_RECOVERY_FILE_DEST_SIZE
			# ���������� ũ�⸦ �����մϴ�.

		# DB_RECOVERY_FILE_DEST
			# ���������� ������ ��θ� �����մϴ� 	


ALTER SYSTEM SET
db_recovery_file_dest_size=50G SCOPE=BOTH ; -- ���������� ũ�⸦ �����մϴ�

ALTER SYSTEM SET
db_recovery_file_dest='c:\users\buk213\fra' SCOPE=BOTH ;  -- ���������� ��θ� �����մϴ� 


	




## ��ī�̺� �α� ��� ���� (Archive Log Mode)
	# �¶��� ���ηα� �׷��� ��ȯ������ ���Ǹ鼭 ������ ���ǹǷ� �� ��������� ��ī�̺� �α� ������ ���� �����ؾ� �մϴ�
	
	# ����Ŭ ������ ������ �� ���� ȯ���̶�� ACHIVE LOG MODE�� �ݵ�� �����ؾ� �մϴ�

	# �Ϲ� ����ڷκ��� ������ ������ ����Ǵ� ȯ�浵 �ݵ�� ARCHIVE LOG MODE�� �����ؾ��մϴ�

	# ��ī�̺� ���� �Ķ���͵�
		# LOG_ARCHIVE_FORMAT
			# �����Ǵ� ��ī�̺������� �̸� ������ �����մϴ�
			# %d : �����ͺ��̽� �̸�
			# %t : �ν��Ͻ� ��ȣ
			# %s : LOG-SEQUENCE ��ȣ
			# %r : RESETLOGS-ID�� ���ηαװ� �ʱ�ȭ�� �� �����Ǵ� ID ��


		# LOG_ARCHIVE_DEST_n
			# ��ī�̺� ������ �����Ǵ� ��ġ�� �����մϴ�
			# ���ÿ� ���� ���Ͽ� ���� ������ ����� �� �ֽ��ϴ�	
			# ��Ʈ��ũ ���ӽĺ��ڸ� ��η� �����ϸ� �����Ͱ��带 ����� �� �ֽ��ϴ� (������������ ������ ����)


	# ��ī�̺� �α� ���� ����
		1. SHUTDOWN IMMEDIATE
		2. STARTUP MOUNT             	-- ����Ʈ ���·�  
		3. ALTER DATABASE ARCHIVELOG;   -- ��ī�̺�α� ��带 ON �Ѵ�
		4. ARCHIVE LOG LIST;			-- ��ī�̺�α� ���� Ȯ��
		5. ALTER DATABASE OPEN;			-- �����ͺ��̽��� OPEN�Ѵ�
		6. ALTER SYSTEM ARCHIVE LOG CURRENT -- ���� CURRENT ������ ���ηα������� ��ī�̺꿡 ����մϴ� (�ǽ��̹Ƿ� ������ ��ī�̺������� ����� �����Դϴ�)
		7. ALTER SYSTEM CHECKPOINT -- ACTIVE ==> VALID ���·� ������ݴϴ�
		8. c:\users\buk213\arch\orcl\ ���Ͽ� ����� ��ī�̺� �α������� ����ƴ��� Ȯ���մϴ� 




SELECT THREAD#, SEQUENCE#, FIRST_CHANGE#, RESETLOGS_ID
,ARCHIVED, STATUS, NAME
FROM v$archived_log
ORDER BY 1,2 ;  -- ��ī�̺�α� ������ ��ȸ�մϴ�



		

	# ��ü �����ͺ��̽� ���
		# ��ī�̺� �α� ��带 �����ϸ� ���� ����� ��������� ����� �� �����ϴ�
		# ���� ���������� �ݵ�� ��ü �����ͺ��̽��� ����ؾ� �մϴ�















--------------------------------------------------------------------------------------------------

<�����ͺ��̽� ��ũ>

## �����ͺ��̽� ��ũ
	# �ڽ��� �����ͺ��̽� �������� �ٸ� �����ͺ��̽� ������ ������ �����ϰ� ���� �� ����մϴ�

	# sqlplus hr/oracle4U@orcl  : �ڽ��� �����ͺ��̽��� �����մϴ�

	# ���� �����ͺ��̽��� ���ӽĺ��ڷ� TEAC��� �����س����ϴ�



CREATE database LINK mylink1
CONNECT TO hr IDENTIFIED BY oracle4U
USING 'TEAC' ;  -- �ٸ� �����ͺ��̽� ������ ������ �� �ִ� ��ũ�� ����ϴ�


SELECT * FROM hr.avgsalperdept@mylink1  -- ��ũ mylink1�� ����ؼ� �ٸ� �����ͺ��̽� �ڷḦ ���� �� �ֽ��ϴ�


CREATE SYNONYM myavgsal FOR hr.avgsalperdept@mylink1;   -- ���Ǿ ����� �����ϰ� ������ �� �ֽ��ϴ� 


SELECT * FROM user_synonyms ;  -- ���Ǿ� ����� �� �� �ֽ��ϴ� (���Ǿ�� ���� 100% �����ͺ��̽� ��ũ�� ����� �� ���� ����Ѵٰ� �մϴ�)


















-------------------------------------------------------------------------------------------------

<����Ŭ ��Ʈ��ũ ����>

## ����Ŭ ��Ʈ��ũ
	# ����, Ŭ���̾�Ʈ, �׸��� ���α׷����� �����Ǿ� �ֽ��ϴ�

	# ������ (LISTENER program)
		# �ٸ� ������ �ٸ��� ����Ŭ �����ʴ� ������ ���α׷����� �����Ǿ� �ֽ��ϴ�
		
		# ��Ʈ��ũ���� �⺻ ��� : c:\app\buk213\product\11.2.0\db_home_1\NETWORK\ADMIN\
		
		# listener.ora (������ ��������)
		
		# �����ʸ� ���� ��������
			# sqlplus system/oracle4U@210.123.41.178:1521/orcl.example11.com 
				# ezconnect ����̶�� �մϴ�  
				# ����/���@������:��Ʈ/�����ͺ��̽���.�����θ�
			
				
			# sqlnet.ora (Naming Method ���� ����)
				#
			

			# tnsnames.ora (���� �ĺ��� ����)
				# �� ������ ���� ���� �� ������ �����س����� ���ϰ� �α����� �� �ֽ��ϴ�
					# �̸� tnsnames ����̶�� �մϴ�
				# sqlplus system/oracle4U@orcl �� �Է����ָ� �˴ϴ�







	# WINDOWS ȯ�濡�� TNS_ADMIN Ű�� �����ؼ� ���������� �⺻��ġ�� ������ �� �ֽ��ϴ� 
		ex) TNS_ADMIN : c:\app\buk213\product\11.2.0\db_home_1\NETWORK\ADMIN\



	# netca �� netmgr
		# 'netca' : Network Configuration Assistant ��
			# ������ ���� : listener.ora
			# �̸� ���� ��� ���� : tnsname.ora
			# ���� ��Ʈ ���� �̸� ���� : sqlnet.ora
			# ���丮 ��� ���� : x (���� ���� �ƴ�)	




		# 'netmgr' : Network Manager ��
			# �������� : sqlnet.ora
			# ���� �̸� ���� : tnsname.ora
			# ������ : listner.ora
				# ������ġ�� �����ͺ��̽� ���� ��� �������ݴϴ�
		







	# ���� ��Ʈ��ũ�� �����ϴ� ��� (�ǽ�)
		
		1. ������ �����մϴ�
			# netca�� ����� �����ʸ� �����մϴ�(EDWARD)
			# netmgr�� ����� �����ʸ� �� �����մϴ�(EDWARD2)
				# netmgr�� ����� 2���� ��Ʈ�� �����ϰ� �����ͺ��̽� ���񽺸� �������ݴϴ�


			# cmd ==> lsnrctl status LISTENER, EDWARD, EDWARD2 �� �����ʻ��¸� Ȯ���մϴ�
				# lsnrctl start EDWARD2�� �����ʸ� �����մϴ�





		2. �����ʿ� �����ͺ��̽� ���� �̸��� ��Ͻ�ŵ�ϴ�
		
			# ���� ���� ��� (DYNAMIC SERVICE REGISTRATION)
				# PMON ���μ����� �����ͺ��̽� � �� ��� INSTANCE_NAME, SERVICE_NAME �ʱ�ȭ �Ķ���� ������ �����ʿ��� �ڵ����� ��Ͻ�ŵ�ϴ�		
					
					# PMON ���μ����� ����Ʈ�� 1521��Ʈ�� �����ʿ��Ը� DB ���񽺸��� ����մϴ�	
						# �̷��� PMON�� �������� ���� ���񽺻���('UNKNOWN' ����) �� �ǰ�
						# ������ ���� ���񽺻���('READY' ����)�� �˴ϴ�
						# cmd ==> lsnrctl status EDWARD2 
				
				# tnsname.ora ������ ������ ���� �����մϴ�
				
PMON_REG =
(ADDRESS_LIST =
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 2000))
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 1521))
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 3000))
(ADDRESS = (PROTOCOL = TCP)(HOST = 215-08)(PORT = 4000))
)  -- �� ������ �߰��ؼ� PMON�� 2000,3000,4000�� ��Ʈ�� ���� �� �ְ� ���ݴϴ�

	

				# DB�� ���� �� LOCAL_LISTENER �Ķ���Ϳ� ��Ͻ�ŵ�ϴ�


-- DB�� ���� ��
SHOW PARAMETER LOCAL_LISTENER ;

ALTER SYSTEM SET
LOCAL_LISTENER=PMON_REG;   -- �ش� �Ķ������ PMON_REG Ű���带 ��Ͻ�ŵ�ϴ�

ALTER SYSTEM REGISTER; -- PMON ���μ������� ���� �̸�, �ν��Ͻ� �̸��� ������ ��Ͻ�ŵ�ϴ�





			# ���� ���� ��� (STATIC SERVICE REGISTRATION)
				# netmgr�θ� ������ �� �ֽ��ϴ� 
				# listener.ora ���Ͽ� ������ ���� ������ �߰��˴ϴ�

SID_LIST_EDWARD =
  (SID_LIST =
    (SID_DESC =
      (GLOBAL_DBNAME = orcl.example11.com)
      (ORACLE_HOME = C:\app\buk213\product\11.2.0\dbhome_1)
      (SID_NAME = orcl)
    )
  ) -- ���� ���� ������ ������ EDWARD �����ʴ� ���� �����Դϴ�




			# ������ �α� (Listener Log)
				# c:\app\buk213\diag\tnslsnr\(hostname)\listner\trace\(�α�����).log
				# �ش� �����ʿ� ������ ������ �α������� �� �� �ֽ��ϴ� 







		3. LOCAL NAMING(TNSNAMES) Method�� �����ϴ� ��� (netca ���)
			# netca ==> �̸� ���� ��� ����
				# ���� ���� �̸� ����, ���� �̸� ������ Ŭ���մϴ� 
				# sqlnet.ora ���Ͽ� ���ο� ������ �߰��˴ϴ�
					# NAMES.DICTONARY_PATH=(EZCONNECT, TNSNAMES)
			
			# netca ==> ���� ��Ʈ���� �̸� ����
				# ���񽺸����� ���ϰ� ������ �� �ֽ��ϴ� 
					# sqlplus system/oracle4U@orcl
					# tnsnames.ora ������ �����մϴ�

			# netmgr ==> ���� �̸� ����
				# �̸� ���� tnsnames.ora ������ ������ �� �ֽ��ϴ�
				# ���� ���Ӻ��� ���ϰ� sqlplus system/oracle4U@apple01 ���� ������ �� �ֽ��ϴ�


		4. Dedicated Server (���� ����) vs Shared Server (���� ����)
			# Dedicated Server�� �� ����� �� �ϳ��� �������μ����� �����ϴ� ����Դϴ�
				# Connection Pool�� ���� ����� ������ �� ����� ó���� �� �ֽ��ϴ�

			# Shared Server�� ����ó�� ���� ����� ������ �޾Ƽ� ó���ϹǷ� ���ϰ� �������� ����ó�� �״� ������ �߻��մϴ� (�� ������� �ʽ��ϴ�)












