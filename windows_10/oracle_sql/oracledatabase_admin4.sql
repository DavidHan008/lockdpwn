
<REPORT 명령어를 이용한 백업할 대상 확인>


## REPORT 명령어
	# NEED BACKUP : 백업이 필요한 데이터파일의 정보를 표시합니다

		# REDUNDANCY 2 : 백업파일의 갯수가 2개보다 작은 데이터파일
	
		# DAYS 3 :
		
		# INCREMENTAL 3 :
		
		# RECOVERY WINDOW OF 2 DAYS : 


	# REPORT UNRECOVERABLE 명령어
		# 현재시점까지 복구할 수 없는 데이터파일 정보를 표시해줍니다




RMAN> DELETE NOPROMPT COPY OF DATAFILE 4 ; -- 4번 IMAGECOPY 데이터파일을 바로 삭제합니다 

RMAN> DELETE NOPROMPT BACKUP OF DATAFILE 4 ; -- 4번 BACKUPSET 데이터파일을 바로 삭제합니다

RMAN> REPORT SCHEMA ;






RMAN> REPORT NEED BACKUP
REDUNDANCY 3 ;   -- 백업파일 개수가 최소 3개보다 적은 데이터파일들의 정보를 표시합니다



RMAN> REPORT NEED BACKUP
DAYS 3 ;     -- 3일동안 백업이 안된 정보를 확인합니다



RMAN> REPORT NEED BACKUP
INCREMENTAL 3 ; -- LEVEL 0 백업 복원 후에 추가적으로 복원해야하는 LEVEL 1의 백업이 4개 이상인 데이터파일의 정보를 표시합니다 









SQL> INSERT /*+ APPEND */ INTO hr.emp03_02
NOLOGGING
SELECT *
FROM hr.employees ;  -- DIRECT-PATH 모드로 입력한 SQL문 (리두로그에 저장이 안됩니다)

SQL> COMMIT ;




RMAN> REPORT UNRECOVERABLE; -- 복구가 불가능한 데이터파일을 보여줍니다 (DIRECT-PATH 모드로 입력한 SQL문은 리두로그에 저장이 안돼서 복구가 안됩니다)





RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
DATAFILE 4
FORMAT 'C:\Users\buk213\rmanbkg\%U'
TAG 'orcl_BS_DBF4_TS_USERS_20140204 ' ; -- 다음과 같이 UNRECOVERABLE 에 나온 데이터파일을 백업받습니다




RMAN> REPORT UNRECOVERABLE; -- 다시 입력하면 정상적으로 아무 정보도 나오지 않습니다













-------------------------------------------------------------------------------------------------

<RECOVER 명령어를 이용해 IMAGECOPY 유형의 백업파일 업데이트>


## RECOVER 명령어
	





RMAN> BACKUP AS COPY
INCREMENTAL LEVEL 0 DATABASE
FORMAT 'C:\Users\buk213\rmanbkg\%U'
TAG 'orcl_CP_WHOLE_DB_012'
KEEP UNTIL TIME='SYSDATE+730' ; -- 일요일에 LEVEL 0 백업을 수행합니다 



	
RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 1 DATABASE
FORMAT 'C:\Users\buk213\rmanbkg\%U'
TAG 'orcl_CP_WHOLE_DB_012';   -- 매일 LEVEL 1 백업을 수행합니다 (월,화,수,목,금)



RMAN> LIST COPY TAG orcl_CP_WHOLE_DB_012 ; -- 생성된 IMAGECOPY 백업파일을 확인합니다


RMAN> LIST BACKUP OF DATABASE BY FILE TAG orcl_CP_WHOLE_DB_012 ; -- BACKUPSET의 SCN 값을 확인합니다 (전부 생성된 IMAGECOPY 백업파일 SCN보다 큽니다)



RMAN> RECOVER COPY OF DATABASE WITH TAG orcl_CP_WHOLE_DB_012 ; -- LEVEL 1 백업을 LEVEL 0 에 적용합니다 (SCN값이 업데이트 됩니다)(사고발생 시 복구를 훨씬 더 빠르게 할 수 있습니다)





RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 1
FOR RECOVER OF COPY WITH TAG 'orcl_CP_WHOLE_20140204'
DATABASE
FORMAT 'C:\Users\buk213\rmanbkg\%U' ;  -- LEVEL 0 IMAGECOPY 백업본이 없으면 LEVEL 0 IMAGECOPY 백업을 수행하고 만약 있으면 LEVEL 1 BACKUPSET 백업을 수행합니다


















-------------------------------------------------------------------------------------------------

<VALIDATE 명령어를 이용한 파일 검증>


## VALIDATE 명령어
	# 10g 버전에서 처음 제공했습니다
	# dbv는 ASM 시스템에서는 사용할 수 없고 VALIDATE 를 이용해 검증할 수 있습니다

	# Blocks Failing, Marked Corrupt 컬럼의 값이 0 으로 표시되면 정상입니다

	# CHECK LOGICAL : 블록 내 저장된 내용을 검증할 때 사용합니다
		# 이 옵션이 없으면 그냥 파일 앞뒤의 CHECKSUM 값만 확인합니다
		# 이 옵션을 사용하면 ROWID 나 기타 블록안의 정보까지 검증합니다(오랜시간 걸림)


	# SECTION SET 을 사용해 검증할 블록 갯수를 정할 수 있습니다




RMAN> BACKUP VALIDATE DATABASE ; -- (9i, 10g, 11g 버전)

RMAN> BACKUP AS BACKUPSET VALIDATE DATABASE ; -- (10g 이후)


RMAN> BACKUP AS BACKUPSET
VALIDATE
CHECK LOGICAL
DATABASE ; -- (10g 이후) 블록 내 저장된 내용을 검증합니다







RMAN> VALIDATE BACKUPSET 61 ; -- BACKUPSET 61번 BACKUP-PIECE 파일을 검증합니다

RMAN> VALIDATE DATABASE ; -- (11g) 현재 사용하는 VALIDATE 구문입니다

RMAN> VALIDATE CHECK LOGICAL DATAFILE 5 ; -- (11g) 현재 사용하는 VALIDATE 구문입니다


RMAN> VALIDATE SPFILE ; -- (11g) SPFILE을 검증합니다


RMAN> VALIDATE DATAFILECOPY FROM TAG '태그이름' ; -- (11g) 특정 태그를 가진 IMAGECOPY 데이터파일 백업을 검증합니다


RMAN> VALIDATE CORRUPTION LIST ;  -- V$DATABASE_BLOCK_CORRUPTION 뷰에 기록된 CORRUPTION 블록의 정보를 검증합니다



RMAN> BLOCKRECOVER CORRUPTION LIST ; --(10g) 손상된 블록만을 복구합니다

RMAN> RECOVER CORRUPTION LIST ; -- (11g) 손상된 블록만 복구합니다 (유용한 구문)



RMAN> RUN { ALLOCATE CHANNEL a1 TYPE DISK ;
ALLOCATE CHANNEL a2 TYPE DISK ;
ALLOCATE CHANNEL a3 TYPE DISK ;
VALIDATE DATAFILE 1 SECTION SIZE 100 M ;
} -- SECTION SET 을 사용해 블록 크기를 제한할 수 있습니다

























-------------------------------------------------------------------------------------------------

<CMDFILE 옵션 및 LOG 옵션>


## CMDFILE, LOG 옵션
	# CMDFILE : RMAN 스크립트를 이용해 자동으로 스크립트 내용을 실행할 수 있습니다
	# LOG : CMDFILE이 실행되는 동안 모든 화면정보를 저장합니다


RUN {
SHUTDOWN IMMEDIATE ;
STARTUP MOUNT ;
BACKUP AS BACKUPSET
FORMAT 'C:\Users\buk213\rmanbkg\%U'
INCREMENTAL LEVEL 0
DATABASE
TAG 'orcl_BS_CLS_20140109' ;
ALTER DATABASE OPEN ;
}
EXIT ;   -- rman_bak.rmn 이름으로 SCRIPT\orcl\ 에 저장합니다


cmd ==> rman target / CMDFILE=C:\Users\buk213\SCRIPT\orcl\rman_bak.rmn 
LOG=C:\Users\buk213\BACKUP_LOG\rman_bak.log  -- cmdfile로 스크립트를 실행하면서 log 명령어로 기록합니다 (cmd는 띄어쓰기가 안되므로 입력할 때는 붙여야됩니다)






set ORACLE_SID=orcl
set ORACLE_HOME=C:\app\buk213\product\11.2.0\dbhome_1
set NLS_LANG=AMERICAN_AMERICA.AL32UTF8
set NLS_DATE_FORMAT=YYYY/MM/DD HH24:MI:SS
rman target / CMDFILE=C:\Users\buk213\SCRIPT\orcl\rman_bak.rmn LOG=C:\Users\buk213\BACKUP_LOG\rman_bak2.log  -- 이런식으로 일괄적으로 파일을 실행할 수 있습니다 (Windows는 .bat로 변경 후 실행합니다)















--------------------------------------------------------------------------------------------------

<SPOOL 명령어로 화면표시 내용 저장>

## SPOOL 명령어
	# RMAN 프롬프트에 적힌 모든 내용을 파일에 저장합니다
		# 바로 


RMAN> SPOOL LOG TO 'C:\Users\buk213\rmanbkg\my_lab_output.txt'; -- 화면프롬프트의 내용을 파일에 저장합니다



RMAN> SPOOL LOG OFF ; -- SPOOL을 해제합니다








--------------------------------------------------------------------------------------------------

<MAXPIECESIZE, SECTION SIZE 분할 백업을 수행>


## MAXPIECESIZE 명령어
	# 최근에는 잘 사용하지 않는다고 합니다
	
	# BACKUPSET 형식에만 사용됩니다. IMAGECOPY 형식의 백업을 사용할 수 있습니다
		# 하나의 데이터파일은 하나의 채널-서버프로세스가 백업을 합니다
		
		# 채널-서버프로세스를 2개이상 사용하면 각 프로세스는 자신의 BACKUPSET을 구성해 백업을 합니다
		
		# BACKUPSET 하나 당 하나의 BACKUP-PIECE가 생성됩니다
	
		# ALLOCATE CHANNEL 명령어와 같이 사용됩니다






RMAN> RUN {
ALLOCATE CHANNEL c1 TYPE DISK MAXPIECESIZE 100M ;
BACKUP AS BACKUPSET
FORMAT 'C:\Users\buk213\rmanbkg\%U'
DATABASE
TAG 'orcl_BS_WHOLE_002'; }   -- MAXPIECESIZE 100 M 를 설정해서 전체 데이터파일을 백업합니다








## SECTION SIZE 옵션
	# 이 옵션을 이용해 큰 데이터파일을 분할백업할 수 있습니다 (11g 버전부터 사용가능)
	# MAXPIECESIZE 대신 최근에 많이 사용한다고 합니다

	# 10g까지는 하나의 데이터파일은 하나의 채널-서버프로세스가 백업했습니다
	# 11g부터 SECTION SIZE 옵션으로 여러 채널-서버프로세스가 한 파일을 나눠받을 수 있습니다

	# 한 파일에 최대 256개의 섹션이 있을 수 있습니다 (중요하다고 합니다!)

	# MAXPIECESIZE와 SECTION SIZE 를 동시에 사용할 수 없습니다 (같은 세션에서)

	# 100M (100Mb)로 설정한다고 해서 꼭 100Mb 씩 나눠서 저장되는게 아닙니다
		# 100Mb 블록에서 유효한 정보만 복사합니다

	# AS COPY 옵션과 같이 사용될 수 없습니다 (IMAGECOPY 방식 백업이 안됩니다)






RMAN> RUN
{
ALLOCATE CHANNEL a1 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a2 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a3 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a4 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a5 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a6 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a7 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a8 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a9 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a10 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a11 DEVICE TYPE DISK ;
ALLOCATE CHANNEL a12 DEVICE TYPE DISK ;
BACKUP AS BACKUPSET
DATAFILE 1,5 SECTION SIZE 100M
format 'C:\Users\buk213\rmanbkg\%U'
TAG 'orcl_BS_SYSTEM_EXAMPLE_TS_F_001';
}   -- SECTION SIZE를 설정해 여러개의 채널-서버프로세스로 파일을 백업합니다




RMAN> LIST BACKUP TAG orcl_BS_SYSTEM_EXAMPLE_TS_F_001 ; -- 생성한 백업파일을 확인합니다





















--------------------------------------------------------------------------------------------------

<SHOW 및 CONFIGURE 명령어를 이용한 RMAN의 설정 관리>


## SHOW, CONFIGURE 명령어
	# 9i 버전부터 사용합니다

	# CONFIGURE는 자주쓰는 명령어를 미리 설정해 놓고 사용할 수 있습니다 (경로, 명령어 등등..)
		# CLEAR 명령어로 원래대로 돌릴 수 있으나 SBT 후 CLEAR하면 제대로 CLEAR되지 않습니다(버그) 

	# SHOW는 CONFIGURE 명령어를 확인하기 위해 사용합니다

	# CONFIGURE 1 : 자동 채널 구성
		# 채널-서버프로세스의 갯수를 미리 설정할 수 있습니다
		# 백업파일이 생성되는 경로를 설정할 수 있습니다
		# BACKUPSET / IMAGECOPY 방식 중 하나를 미리 설정할 수 있습니다





RMAN> SHOW ALL; -- 현재 CONFIGURE 설정 내용을 보여줍니다 (거의 대부분 이걸 씁니다)

RMAN> SHOW CHANNEL ; -- 백업 경로 및 파일이름 형식을 봅니다 (SHOW ALL 항목에 없습니다)





RMAN> CONFIGURE CHANNEL DEVICE TYPE DISK
FORMAT 'C:\Users\buk213\rmanbkg\%U' ;   -- 백업 경로와 파일이름 형식을 설정합니다 


RMAN> CONFIGURE DEVICE TYPE DISK PARALLELISM 3 ; -- 채널-서버프로세스를 3개로 늘립니다


RMAN> CONFIGURE DEVICE TYPE DISK BACKUP TYPE TO COPY ; -- 백업방식을 IMAGECOPY 백업으로 합니다


RMAN> CONFIGURE COMPRESSION ALGORITHM 'LOW' ; -- 압축률을 LOW로 합니다


RMAN> CONFIGURE COMPRESSION ALGORITHM CLEAR ; -- CLEAR 명령어로 DEFAULT 값으로 바꿉니다






		# FORMAT 옵션을 명시하지 않은 경우 %ORACLE_HOME%\database\ 경로에 생성됩니다
			# Flash Recovery Area가 구성되어 있으면 FRA 경로에 생성됩니다
			

		# CONFIGURE 명령어를 사용하면 명령어를 조금만 사용해도 됩니다



RMAN> RUN {
ALLOCATE CHANNEL t1 TYPE DISK ;
ALLOCATE CHANNEL t2 TYPE DISK ;
ALLOCATE CHANNEL t3 TYPE DISK ;
BACKUP AS BACKUPSET
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
INCREMENTAL LEVEL 0 DATABASE ;
}



RMAN> RUN { BACKUP INCREMENTAL LEVEL 0 DATABASE ; }   -- 이처럼 명령어가 간단해집니다










		# CONFIGURE 2 : OFFLINE, READ ONLY 상태의 데이터파일을 백업 시 제외
			# OFFLINE, READ ONLY 파일은 한 번 백업 후 변경되는 내용이 없으므로 추가 백업을 하지 않아도 됩니다
			


RMAN> CONFIGURE BACKUP OPTIMIZATION ON ; -- OFFLINE, READ ONLY 파일은 백업에서 제외합니다


RMAN> BACKUP AS BACKUPSET
SKIP READ ONLY SKIP OFFLINE
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
DATABASE ;  -- 위와 같은 명령어이고 CONFIGURE 대신 사용합니다



RMAN> CONFIGURE EXCLUDE FOR TABLESPACE example ; -- 복구할 필요가 없는 테이블스페이를 제외합니다


RMAN> SHOW EXCLUDE ; -- EXCLUDE 처리된 테이블스페이를 볼 수 있습니다












		# CONFIGURE 3 : 컨트롤파일 및 SPFILE 자동 백업구성
			# 컨트롤파일에 등록된 데이터파일들이 변경되면 자동으로 컨트롤파일/SPFILE이 백업되는 설정입니다 

			# 이 기능으로 생성된 컨트롤파일/SPFILE 백업은 BACKUPSET 방식으로 생성됩니다


			# path\FORMAT : path\%F : c-DBID-백업날짜-xx
				
				# 여기서 xx는 254개의 갯수를 구분할 수 있는 HEX 시퀀스 값
					ex) c-245478574-20160804-00

				# 만약 경로를 설정해놓지 않으면 Flash Recovery Area의 경로에 생성됩니다
				# Flash Recovery Area가 구성되지 않았으면 %ORACLE_HOME%\database\ 에 생성됩니다 







RMAN> CONFIGURE CONTROLFILE AUTOBACKUP ON ; -- 컨트롤파일/ SPFILE 자동백업을 활성화합니다

RMAN> SHOW CONTROLFILE AUTOBACKUP FORMAT ; -- 자동백업을 받을 때 경로와 파일이름을 봅니다



RMAN> CONFIGURE CONTROLFILE AUTOBACKUP
FORMAT FOR DEVICE TYPE DISK TO
'C:\Users\buk213\rmanctlautobkg\%F' ;  -- %F 포멧으로 경로와 파일이름을 생성합니다
	



RMAN> BACKUP TABLESPACE users ; -- CONFIGURE를 이용해 백업해봅니다

RMAN> BACKUP AS COPY CURRENT CONTROLFILE ; -- CONFIGURE를 이용해 백업해봅니다2

RMAN> LIST BACKUP OF CONTROLFILE SPFILE BY FILE ;  -- 파일을 확인합니다




RMAN> CONFIGURE CONTROLFILE AUTOBACKUP CLEAR ; -- 자동백업을 비활성화 합니다


RMAN> CONFIGURE CONTROLFILE AUTOBACKUP
FORMAT FOR DEVICE TYPE DISK CLEAR ; -- 경로와 포맷도 비활성화합니다











			# CONFIGURE 4 : BACKUPSET 백업에서 백업세트를 구성하는 원본파일의 최대크기 제한
				# BACKUPSET만 가능합니다




RMAN> SHOW MAXSETSIZE ; -- 백업세트의 최대크기를 확인합니다


RMAN> CONFIGURE MAXSETSIZE TO 1024 M ; -- 백업세트 최대크기를1024Mb로 제한합니다


RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
DATABASE
TAG 'orcl_BS_WHOLE_001' ;   -- 최대크기를 적용한 상태로 백업세트를 알아서 묶습니다


RMAN> LIST BACKUP TAG 'orcl_BS_WHOLE_001' ; -- 생성된 파일 정보를 확인합니다









			# CONFIGURE 5 : 백업파일 유지 정책 구성 (보존정책)
				# REDUNDANCY : 
				
				# RECOVERY WINDOW : POINT-IN-TIME-RECOVERY(PITR) 가능한 기간을 설정합니다
					# 과거 특정시점의 백업데이터가 필요한 경우에 사용합니다
					
					# 불완전복구를 일부러 하는 경우입니다
					
					# CONTROL_FILE_RECORD_KEEP_TIME 초기화파라미터보다 같거나 커야합니다

				# ARCHIVAL BACKUP 때문에 보존정책은 잘 사용하지 않는다고 합니다






RMAN> SHOW RETENTION POLICY ; -- 유저 정책을 확인해봅니다

RMAN> CONFIGURE RETENTION POLICY TO REDUNDANCY 2 ; -- 각 백업파일들을 최소 2개는 유지합니다

RMAN> CONFIGURE RETENTION POLICY TO
RECOVERY WINDOW OF 30 DAYS ;  -- 현재 시점으로부터 30일 전의 백업데이터가 필요할 경우에 사용합니다 





RMAN> DELETE OBSOLETE REDUNDANCY 5; -- 5개를 기준으로 현재 필요없느 파일을 삭제합니다

RMAN> DELETE OBSOLETE RECOVERY WINDOW OF 30 DAYS ; -- 30일을 기준으로 현재 필요없는 파일을 삭제합니다




RMAN> CONFIGURE RETENTION POLICY TO NONE ; -- 보존정책을 해제합니다











--------------------------------------------------------------------------------------------------

<ALLOCATE CHANNEL 명령어를 이용해 BACKUPSET 병렬화>

## ALLOCATE CHANNEL 명령어
	# 여러개의 CHANNEL 서버프로세스를 이용해 백업을 수행하는 바업입니다
	# 반드시 RUN {...} 에서만 사용됩니다
	# TAPE 장치에 백업할 때 주로 사용합니다 
		# TAPE 장치는 BACKUPSET 방식의 백업만 가능합니다
		# TAPE 장치에 TYPE 은 SBT입니다



RMAN> RUN { 
ALLOCATE CHANNEL t1 TYPE DISK ;
ALLOCATE CHANNEL t2 TYPE DISK ;
ALLOCATE CHANNEL t3 TYPE DISK ;   -- 채널 3개를 디스크에 저장하기 위해 사용합니다
BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
FORMAT 'C:\Users\buk213\rmanbkg\%U'
(DATAFILE 1 CHANNEL t1 tag=df_1)
(DATAFILE 2,4,5 CHANNEL t2 tag=df_2_4_5)
(DATAFILE 3 CHANNEL t3 tag=df_3) ;
}  -- 채널 3개를 사용해 동일한 디렉토리에 백업을 생성합니다





RMAN> RUN {
ALLOCATE CHANNEL t1 TYPE DISK FORMAT 'C:\Users\buk213\rmanbkg1\%U';
ALLOCATE CHANNEL t2 TYPE DISK FORMAT 'C:\Users\buk213\rmanbkg2\%U';
ALLOCATE CHANNEL t3 TYPE DISK FORMAT 'C:\Users\buk213\rmanbkg3\%U';
BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
(DATAFILE 1 CHANNEL t1 tag=df_1)
(DATAFILE 2,4,5 CHANNEL t2 tag=df_2_4_5)
(DATAFILE 3 CHANNEL t3 tag=df_3);
} -- 채널 3개를 사용해 각자 다른 디렉토리에 백업을 생성합니다




RMAN> RUN {
ALLOCATE CHANNEL t1 TYPE SBT ;  -- TAPE 장치에 백업할 때 TYPE은 SBT입니다
ALLOCATE CHANNEL t2 TYPE SBT ;
ALLOCATE CHANNEL t3 TYPE SBT ;
BACKUP AS BACKUPSET
DATABASE
FORMAT 'C:\Users\buk213\rmanbkg\%U' ;
}




















--------------------------------------------------------------------------------------------------

<DELTE 명령어를 이용한 RMAN 백업파일 삭제>

## DELETE 명령어
	# RMAN 백업파일은 운영체제 삭제명령어로 삭제하면 안됩니다 (컨트롤파일에 정보는 그대로 남기때문)
		# NOPROMPT : Yes or No 를 물어보지 않고 바로 삭제합니다 

		# OBSOLETE REDUNDANCY 3 : 가장 최근 백업파일 3개를 제외하고 나머지를 삭제합니다(유용)
			# 필요한 아카이브로그파일만 남기고 나머지 아카이브로그파일은 알아서 삭제해줍니다






RMAN> DELETE COPY OF DATABASE
TAG orcl_CP_WHOLE_001 ;  -- 해당 태그를 가진 모든 데이터파일의 IMAGECOPY를 삭제합니다



RMAN> DELETE NOPROMPT BACKUP OF DATABASE
TAG orcl_BS_WHOLE_001 ;   -- NOPROMPT : Yes, No를 물어보지 않고 바로 삭제합니다(?)


RMAN> DELETE NOPROMPT DATAFILECOPY 57,62 ; -- 해당 번호를 가진 데이터파일 IMAGECOPY 백업파일을 삭제합니다


RMAN> DELETE NOPROMPT CONTROLFILECOPY 63 ; -- 해당 번호를 가진 컨트롤파일 IMAGECOPY 백업파일을 삭제합니다

RMAN> DELETE BACKUPSET 1;   -- 1번 BACKUPSET 백업파일을 삭제합니다


RMAN> DELETE OBSOLETE REDUNDANCY 3 ;  -- OBSOLETE REDUNDANCY 3 : 가장 최근 백업파일 3개는 유지하고 나머지는 삭제합니다










		# 만약 파일이 삭제되었는데 컨트롤파일에 등록이 되어있으면 삭제가 되지 않습니다
			# CROSSCHECK BACKUPSET 1; : BACKUPSET 1번 백업파일 중 현재 디스크에 존재하지 않는 파일을 EXPIRED로 표기합니다

			# DELETE NOPROMPT EXPIRED BACKUPSET 1; : EXPIRED 상태인 파일만 삭제합니다




RMAN> CROSSCHECK BACKUPSET 1;

RMAN> DELETE NOPROMPT EXPIRED BACKUPSET 1; 







		# CROSSCHECK 명령어 (삭제된 백업파일들 확인)
			# RMAN 백업파일들이 실제로 존재하는지를 체크해서 없으면 EXPIRED 상태로 설정합니다 
			# DELETE ... EXPIRED ... 로 삭제할 수 있습니다




RMAN> CROSSCHECK BACKUP ; -- TARGET 데이터베이스의 CONTROLFILE에 있는 모든 BACKUPSET 방식의 백업파일 정보를 검증합니다


RMAN> CROSSCHECK COPY ; -- TARGET 데이터베이스의 CONTROLFILE에 있는 모든 IMAGECOPY 방식의 백업파일 정보를 검증합니다










--------------------------------------------------------------------------------------------------

<CATALOG 명령어를 이용해 누락된 백업파일 등록>


## CATALOG 명령어
	# TARGET 데이터베이스에 컨트롤파일 정보가 없는 RMAN 백업파일을 재등록 할 수 있습니다
	# 운영체제 복사명령어로 생성된 백업파일을 등록시킬 때도 사용가능합니다
		# 알아서 컨트롤파일에 모든 백업정보를 갱신합니다	


RMAN> CATALOG START WITH 'C:\Users\buk213\BACKUP\orcl\20160803' ; -- 해당 폴더 안에 모든 파일을 복원합니다

RMAN> CATALOG START WITH 'C:\Users\buk213\rmanbkg' ; 


RMAN> LIST COPY OF DATABASE CONTROLFILE ; -- 등록된 컨트롤파일 정보를 확인합니다





	# CHANGE 명령어 (CATALOG 해제)
		# RMAN 백업으로 등록된 파일정보를 CATALOG 등록 해제할 때 사용합니다 
		# 파일은 삭제하지 않고 컨트롤파일에 등록된 정보만 삭제(CATALOG 해제)합니다

		# BACKUPSET 의 CATALOG 해제는 지원하지 않습니다
		


RMAN> CHANGE COPY OF DATABASE TAG 'orcl_CP_WHOLE_001' UNCATALOG ; -- 특정 TAG를 가지는 데이터파일의 IMAGECOPY 정보를 CATALOG 해제



RMAN> CHANGE DATAFILECOPY 24 UNCATALOG ;  -- 해당 키번호를 가진 데이터파일의 IMAGECOPY 정보를 CATALOG 해제합니다



RMAN> CHANGE CONTROLFILECOPY 23 UNCATALOG ; -- 해당 키번호를 가진 컨트롤파일의 IMAGECOPY 정보를 CATALOG 해제합니다

















--------------------------------------------------------------------------------------------------

<LIST 명령어로 백업파일 정보 확인>


## LIST 명령어로 백업파일 정보 확인
	# RMAN> LIST 명령어로 백업파일 정보를 확인할 수 있습니다
	# 모든 데이터파일, 특정 데이터파일, 특정 테이블스페이스, 컨트롤파일, SPFILE, 모든 파일, 태그별로, 백업셀 번호 별로 등등.. 원하는 정보를 볼 수 있습니다
	


RMAN> REPORT SCHEMA ; -- 

RMAN> LIST BACKUP OF DATABASE ;
RMAN> LIST BACKUP OF DATAFILE 1 ;
RMAN> LIST BACKUP OF TABLESPACE users ;
RMAN> LIST BACKUP OF CONTROLFILE ;
RMAN> LIST BACKUP OF SPFILE ;
RMAN> LIST BACKUP ;
RMAN> LIST BACKUP TAG='태그 이름' ;
RMAN> LIST BACKUPSET 백업셀 번호 ; 
RMAN> LIST BACKUP by file ;
RMAN> LIST COPY OF DATABASE ;  -- BACKUP 대신 COPY를 사용하면 IMAGECOPY 정보를 볼 수 있습니다




RMAN> LIST BACKUP OF DATABASE BY FILE ; -- by file : 요약된 형식으로 볼 수 있습니다
RMAN> LIST BACKUPSET 3;
RMAN> LIST BACKUP TAG "ORCL_BS_WHOLE_001" ;
RMAN> LIST COPY TAG='orcl_CP_WHOLE_001' ; 
RMAN> LIST COPY OF TABLESPACE example ;  -- example 테이블스페이스 관련 IMAGECOPY 백업 정보를 확인합니다
RMAN> LIST COPY OF CONTROLFILE ; -- 컨트롤파일의 IMAGECOPY 백업 정보를 확인합니다






	# RMAN으로 SQL문장을 실행할 수 있습니다
		# SELECT 문장은 해도 레코드가 보이지 않습니다
		# 아카이브 로그파일을 조회할 때 사용할 수 있습니다
			# 데이터파일 중 가장 작은 SCN 값을 선정해서 그 특정 시간 이후로부터 생성된 아카이브 로그파일만 조회할 수 있습니다 (실전에서 많이 사용됩니다)	
				# 백업 시 반드시 필요한 아카이브 로그파일만 볼 수 있습니다





RMAN> SQL 'ALTER SYSTEM SWITCH LOGFILE' ;

RMAN> SQL 'ALTER SYSTEM CHECKPOINT' ;  -- 아카이브 로그파일을 생성하기 위해 로그스위치, 체크포인트를 4번씩 실행합니다



RMAN> LIST COPY OF ARCHIVELOG ALL ;    -- 아카이브 로그파일을 IMAGECOPY 백업하지 않았지만 조회할 수 있습니다 


RMAN> LIST COPY OF ARCHIVELOG 
FROM TIME "TO_DATE('2016/08/03 16:00:00', 'YYYY/MM/DD HH24:MI:SS')"; -- 해당 날짜시간 이후 생성된 아카이브 로그파일을 조회합니다


RMAN> LIST COPY OF ARCHIVELOG FROM SEQUENCE 3 ;  -- 해당 번호부터 기록된 아카이브 로그파일을 조회할수 있습니다



RMAN> LIST COPY OF DATABASE CONTROLFILE ARCHIVELOG FROM SCN 1593480 ;  -- 가장 작은 SCN 값을 찾은 다음 그 이후부터 생성된 아카이브 로그파일만 조회할 수 있습니다 (백업시 반드시 필요한 파일로 절대 지워지면 안되는 파일만 볼 수 있습니다)




RMAN>
RMAN>








--------------------------------------------------------------------------------------------------

<백업 명령어>

## RMAN 백업
	# BACKUP 명령어
		# RMAN이 백업받을 수 있는 파일들
			# 데이터파일
			# 컨트롤파일 
			# SPFILE  : SQL문으로 처리하는게 더 간단합니다
			# 아카이브된 리두 로그파일 
			# 이전에 생성한 RMAN의 백업파일들(DUPLEX 백업파일) : BACKUPSET 방식만 가능합니다


		# 백업이 안되는 파일들
			# 온라인 리두로그파일
			# 임시파일
			# PFILE
			# 패스워드 파일
			# 운영체제상의 파일들 



		# 여러가지 BACKUP 명령어 옵션들
			# AS BACKUPSET 옵션
				# FILESPERSET 2 :
				# COMPRESSED 옵션 :


			# FORMAT "값" 옵션 : 
				# %d : 데이터베이스 이름
				# %s : BACKUPSET 번호
				# %p : PIECE 번호 
				# %c : DUPLEX 파일 구분 번호 
				# %U : BACKUPSET : 
					   IMAGECOPY : 데이터파일 : 
								   컨트롤파일 : 


			# DATABASE 옵션
				# 데이터베이스의 모든 데이터파일을 백업받습니다
				# SYSTEM TABLESPACE 가 포함되었으면 컨트롤파일과 데이터파일 SPFILE 모두 백업됩니다

				# 이 옵션 대신 사용할 수 있는 옵션들 
					# TABLESPACE ts_name
					# DATABASE file_id
					# CURRENT CONTROLFILE
					# SPFILE
					# ARCHIVED ALL
					# BACKUPSET bs_key


			# INCREMENTAL LEVEL 0 옵션
				# 0 : INCREMENTAL BACKUP을 받습니다 (레벨 0)
				# 1 : INCREMENTAL BACKUP을 받습니다 (레벨 1)


			


RMAN> BACKUP AS BACKUPSET
FORMAT '/u02/app/BACKUP/rmanbkg/%U'  -- %U 는 오라클서버가 알아서 이름을 정합니다
DATABASE ;



RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0      -- 이 옵션이 없으면 FULL BACKUP 입니다 (0은 FULL BACKUP과 같습니다)
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
FILESPERSET 2     -- 이 옵션이 없으면 모든 데이터파일을 1개의 세트로 인식합니다
				  -- 2개의 데이터파일 당 하나의 세트로 설정합니다
DATABASE
TAG "orcl_BS_WHOLE_003" ;



RMAN> BACKUP AS COPY
INCREMENTAL LEVEL 0
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
DATABASE   -- 모든 데이터파일을 백업받습니다
TAG "orcl_CP_WHOLE_001";  -- 쉽게 알 수 있는 별명을 붙여줍니다




BACKUP AS BACKUPSET
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
BACKUPSET 백업세트 번호;  -- DUPLEX 백업 중 TAPE 장치로 옮기기 위해 백업세트번호를 입력하면 됩니다






		# RMAN 백업 실습해보기



cmd ==> setx NLS_LANG AMERICAN_AMERICA.AL32UTF8
cmd ==> setx NLS_DATE_FORMAT YYYY/MM/DD HH24:MI:SS  -- 환경변수를 적절하게 변경합니다


cmd ==> rman target /



RMAN> BACKUP AS BACKUPSET
FORMAT 'C:\Users\buk213\rmanbkg\%U'
DATABASE ;   -- 모든 데이터파일 백업을 시작합니다



RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
FORMAT 'C:\Users\buk213\rmanbkg\%U'
FILESPERSET 2
DATABASE
TAG "orcl_BS_WHOLE_001" ;   -- FILESPERSET 2, TAG "..." 를 사용해 백업합니다




RMAN> BACKUP AS COPY
INCREMENTAL LEVEL 0
FORMAT 'C:\Users\buk213\rmanbkg\%U'
DATABASE
TAG "ORCL_CP_WHOLE_001";    -- IMAGECOPY 방식으로 백업합니다



SET COMPRESSION ALGORITHM 'LOW'; -- 압축률을 LOW로 설정합니다



RMAN> BACKUP AS COMPRESSED BACKUPSET
FORMAT 'C:\Users\buk213\rmanbkg\%U'
DATABASE
TAG 'orcl_BS_WHOLE_003' ;  -- COMPRESSED BACKUPSET (LOW) 방식으로 백업합니다




RMAN> BACKUP AS COPY
INCREMENTAL LEVEL 0
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
DATAFILE 4
TAG orcl_CP_DBF_4_001 ;  -- 특정 테이블스페이스만 선정해서 백업할 수 있습니다






			# INCREMENTAL 백업
				# FULL BACKUP과는 다르게 부분적으로 백업을 받는 형식입니다
				# FULL 방식의 BACKUPSET 백업파일은 INCREMENTAL LEVEL 0 백업으로 사용이 안됩니다
			
				# LEVEL 0은 IMAGECOPY, BACKUPSET 백업 모두 가능하지만
				# LEVEL 1은 BACKUPSET만 가능합니다

				# INCREMENTAL 백업 방식
					# 'CUMULATIVE' 
						#레벨 0, 1까지만 있고 3번째 백업을 레벨 1로 받을 때 0부터 쭈욱 다 받습니다
				
					# 'DIFFERENTIAL'
						#레벨 0, 1까지만 있고 3번째 백업을 레벨 1로 받을 때 동일레벨(1) 이 후의 변경부분만 받습니다 







RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 1 CUMULATIVE
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
DATABASE ;   -- CUMULATIVE 방식으로 INCREMENTAL 백업을 진행합니다



RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 1
FORMAT '/u02/app/BACKUP/rmanbkg/%U'
DATABASE ;   -- DIFFERENTIAL 백업을 받습니다 (레벨 1)
			 -- 9i 버전까지는 DIFFERENTIAL 백업을 해도 속도가 똑같이 느려서 잘 쓰지 않았습니다









				# INCREMENTAL 백업 속도를 빠르게하기 위한 방법(10g 이후)
					# 'CHANGE_TRACKING_WRITER' 기능
						# 비트맵을 이용해 변경 블록들의 위치를 저장해놓고 백업해 속도가 빨라집니다






cmd ==> mkdir mkdir C:\Users\buk213\changetracking\orcl\ -- 해당 폴더를 만듭니다


ALTER DATABASE
ENABLE BLOCK CHANGE TRACKING
USING FILE 'C:\Users\buk213\changetracking\orcl\orclctf.ctf' ;  -- CHANGE_TRACKING_WRITER 를 실행합니다


col filename format a50
SELECT *
FROM v$block_change_tracking ;  -- CHANGE_TRACKING_WRITER 정보를 조회합니다
							-- 이 설정을 ENABLE한 이후는 반드시 레벨 0부터 백업을 시작해야합니다


RMAN> BACKUP AS COPY
INCREMENTAL LEVEL 0
FORMAT 'C:\Users\buk213\rmanbkg\%U'
DATABASE
TAG 'orcl_CP_WHOLE_002' ;   -- 레벨 0부터 INCREMENTAL 백업을 진행합니다





		# 백업파일을 지울 때 (실습 x)
			# 운영체제 명령어 del로 지우면 안됩니다
				# 컨트롤파일의 정보는 안지워졌기 때문입니다



RMAN>
RMAN>
RMAN>






		# 아카이브된 로그파일 백업
			# 백업보다는 아카이브 로그파일 관리를 쉽게하기 위해 사용합니다
			# 다른경로에 아카이브 로그파일을 백업받고 원본을 삭제해 공간을 확보합니다
			# 아카이브-HANG (ARCHIVE-HANG) 상태를 방지하기 위해 사용합니다

			# 가장 오래된 데이터파일 백업본의 Ckp SCN, Ckp Time을 확인해서 두 값을 포함하는 아카이브로그는 유지해야합니다

			# DELETE ALL INPUT 옵션을 이용해 백업 후 원본파일을 삭제합니다



12,13,14,15,16,17,18,19
1624447
1624461

RMAN> LIST COPY OF ARCHIVELOG FROM SCN 1624447 ; -- 해당 SCN 값에 해당하는 아카이브 로그값을 확인합니다




RMAN> LIST COPY OF ARCHIVELOG
FROM TIME "TO_DATE('2016/08/04 09:00:00','YYYY/MM/DD HH24:MI:SS')"; -- 해당 시간 이후부터 생성된 아카이브 로그파일을 확인합니다






BACKUP AS BACKUPSET
ARCHIVELOG FROM SEQUENCE 12
FORMAT 'C:\Users\buk213\rmanarchbkg\%U.arc.bak'
TAG 'orcl_BS_ARC_FROM_LSN_12_20'
DELETE ALL INPUT ; -- 해당 로그시퀀스 12번 아카이브 로그파일을 다운받고 원본을 지웁니다




RMAN> LIST BACKUP OF ARCHIVELOG ALL ; -- 모든 아카이브 로그파일 정보를 확인합니다




RMAN> BACKUP AS BACKUPSET
ARCHIVELOG LIKE 'C:\app\buk213\product\11.2.0\dbhome_1\RDBMS\ARC%'
FORMAT 'C:\Users\buk213\rmanarchbkg\TO_20160804.arc.bak'
TAG 'orcl_BS_ARC_TO_20160804'
DELETE ALL INPUT ;   -- LIKE 연산자를 이용해 아카이브로그파일을 백업할 수 있습니다 (윈도우에선 안되네용)











		# ARCHIVAL BACKUP 생성
			# CONTROL_FILE_RECORD_KEEP_TIME 파라미터와 관계없이 장기간 유지되는 백업을 말합니다
			
			# KEEP UNTIL TIME = 'date_string'
								'sysdate+300'
								 FOREVER : 반드시 CATALOG DB를 구성해야 사용할 수 있습니다(잘 안쓰입니다)

			# 10g, 11g에서 FLASH RECOVERY AREA에 생성한 백업파일은 CHANGE 명령어를 쓸 수 없습니다

		


RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
DATABASE
FORMAT 'C:\Users\buk213\rmanbkg\%U'
TAG 'orcl_BS_WHOLE_DB_017' ;  -- 백업을 받습니다



RMAN> LIST BACKUP TAG='orcl_BS_WHOLE_DB_017' ; -- 백업정보를 확인합니다



RMAN> CHANGE BACKUP TAG orcl_BS_WHOLE_DB_017
KEEP UNTIL TIME = "TO_DATE('2019/12/31','YYYY/MM/DD')" LOGS ; -- 해당 백업파일을 2019/12/31까지 유지하도록 설정합니다



RMAN> CHANGE BACKUPSET 64,65
KEEP UNTIL TIME = "TO_DATE ('2016/12/31', 'YYYY/MM/DD')" LOGS ; -- BACKUPSET 번호로 할수도 있습니다




RMAN> BACKUP AS BACKUPSET
INCREMENTAL LEVEL 0
DATABASE
FORMAT 'C:\Users\buk213\rmanbkg\%U'
TAG 'orcl_BS_WHOLE_DB_018'
KEEP UNTIL TIME = "TO_DATE('2017/12/31','YYYY/MM/DD')" ; -- 위처럼 나눠서 하지않고 이렇게 한번에 백업하면서 KEEP UNTIL TIME을 명시해도 됩니다





RMAN> BACKUP AS COPY
FORMAT 'C:\Users\buk213\rmanbkg\%U'
INCREMENTAL LEVEL 0
DATABASE
KEEP UNTIL TIME="TO_DATE('2020/12/31','YYYY/MM/DD')"
TAG 'orcl_CP_WHOLE_DB_20160804' ;  -- IMAGECOPY 백업형식으로 ARCHIVAL BACKUP을 받을 수 있습니다






RMAN> CHANGE BACKUP OF CONTROLFILE SPFILE TAG 'orcl_CP_WHOLE_DB_20160804'
KEEP UNTIL TIME = "TO_DATE ('2021/12/31','YYYY/MM/DD')" LOGS ; -- 이미 ARCHIVAL BACKUP된 파일의 기간을 변경할 수도 있습니다



RMAN> CHANGE BACKUPSET 55 NOKEEP ; -- ARCHIVAL BACKUP 설정을 해제할 수 있습니다 

RMAN> CHANGE COPY OF DATABASE CONTROLFILE NOKEEP ;

RMAN> CHANGE BACKUP OF DATABASE CONTROLFILE NOKEEP ; -- BACKUPSET 형식의 모든 백업파일의 KEEP 옵션을 해제합니다




		

		# 'BACKUP RECOVERY FILES , AREA' 명령어
			# 테이프 백업장치에 백업파일을 저장할 때 사용합니다
			# 일관적으로 디스크 상의 RMAN 백업파일들을 TAPE 장치에 넣을 수 있습니다 
			# BACKUPSET 형태의 백업파일만 가능합니다



RMAN> BACKUP RECOVERY FILES ; -- 해당 서버 디스크의 모든 RMAN 백업파일 (FRA + 다른 파일) 들을 TAPE 장치에 검색해서 없는파일만 백업합니다


RMAN> BACKUP RECOVERY AREA ; -- FRA로 설정된 경로에만 있는 백업파일들을 TAPE 장치에 검색해서 없는 파일들만 백업합니다

			







		# DURATION 옵션을 이요해 시스템 리소스 사용량 제한
			# LEVEL 0 IMAGECOPY 백업이 되있고 아카이브 로그파일이 30개가 생성됐는데 
			  관리자가 실수로 일부 아카이브 로그파일을 유실한 경우
				
				# 완전복구를 수행할 수 없게 됩니다

				# 이 경우 서비스 피크 시간대이더라도 백업을 수행해야만 합니다
	
				# 이 때 CPU 및 메모리 사용량을 최소화해서 백업하면 효과적입니다

				# PARTIAL : 만약 아래처럼 10 분안에 안끝나면 진행파일까지만
				            유효한 백업으로 설정합니다

				# MINIMIZE LOAD : 최소의 리소스를 사용해 정해진 시간동안 백업합니다

				# MINIMIZE TIME : 최대의 리소스를 사용해 최소시간동안 백업합니다





RMAN> BACKUP AS BACKUPSET
DURATION 00:10 PARTIAL  -- 평소 백업 소요 시간의 2~3배정도 긴 시간으로 설정합니다 
MINIMIZE LOAD           -- 리소스를 최소로 사용합니다   
FORMAT 'C:\Users\buk213\rmanbkg\%U'
INCREMENTAL LEVEL 1 TAG orcl_CP_WHOLE_20140204
DATABASE ;   -- DURATION 옵션을 사용해 백업 소요시간을 설정합니다 (평소 백업 시간을 알아놔야합니다)


RMAN> LIST BACKUP BY FILE TAG orcl_CP_WHOLE_20140204 ; -- 백업파일 정보를 확인합니다






RMAN> RUN { 
BACKUP AS COPY
DURATION 00:03 PARTIAL
MINIMIZE TIME
FORMAT 'C:\Users\buk213\rmanbkg\%U'
DATABASE ;
}   -- MINIMIZE TIME 옵션을 이용해 최대의 리소스를 사용해 백업합니다 



RMAN> RUN { 
BACKUP AS COPY
DURATION 00:01 PARTIAL
MINIMIZE TIME
FORMAT 'C:\Users\buk213\rmanbkg\%U'
INCREMENTAL LEVEL 0
DATABASE
TAG orcl_cp_whole_025;
}    -- 1분만 백업하고 그때까지 저장된 내용만 유효한 백업파일로 저장합니다



RMAN> LIST COPY TAG orcl_cp_whole_025 ; -- 백업파일 정보를 확인합니다 
























--------------------------------------------------------------------------------------------------

<RMAN을 이용한 데이터베이스 백업>


## RMAN을 이용한 백업
	# 서버 관리 백업이라고 합니다
	# 백업 내용을 컨트롤파일에 기록합니다 (RMAN 메타데이터라고 합니다) 


	# CONTROL_FILE_RECORD_KEEP_TIME 초기화 파라미터 
		# 컨트롤파일에 있는 백업 정보의 유효 날짜를 설정합니다 (일)(DEFAULT : 7)


	# 실제 백업및복구 작업은 데이터베이스에 있는 DBMS_BACKUP_RESTORE (PL/SQL 패키지)가 수행합니다
	# RMAN이 메타데이터를 확인하려면 DBMS_RCVMAN (PL/SQL 패키지)에 의해 수행됩니다


	# ASM-저장공간은 RMAN만 백업할 수 있습니다


	# BACKUPSET 과 IMAGECOPY 유형
		# 'BACKUPSET' : 백업의 대상파일을 하나의 세트로 묶어서 하나의 BACKUP-PIECE를 생성합니다
			# 데이터가 저장된 블록만 백업합니다 (100Mb 파일 중 10Mb만 사용중이면 10Mb만 백업)
			# COMPRESSED BACKUPSET 방식도 있습니다
		
		# 'IMAGECOPY' : 파일을 그대로 복사해서 원본과 동일한 백업파일을 생성합니다 (OS 백업과 비슷)
			# TAPE 장치 백업이 안됩니다


	# RMAN으로 백업및복구를 하려면 Dedicated Server (전용서버) 모드로 접속해야만 합니다
		# Shared Server는 백업및복구 조회만 가능합니다






RMAN target /  -- RMAN으로 DB를 로컬접속합니다 (DBID : 데이터베이스 고유 10자리 숫자)
RMAN target sys/oracle4U@orcl -- RMAN으로 DB를 원격접속합니다





RMAN> REPORT SCHEMA ; -- 컨트롤파일 내용을 참고해서 데이터파일과 임시파일의 정보를 표시합니다

RMAN> CONFIGURE COMPRESSION ALGORITHM 'HIGH' ; -- 압축률을 정할 수 있습니다 (11g부터 가능)
	
RMAN> SET COMPRESSION ALGORITHM 'LOW';  -- 압축률을 LOW로 정합니다




	# RMAN 툴에서 명령어를 실행하는 3가지 방법
			# RMAN> 프롬프트
				# CREATE CATALOG
				# RESYNC CATALOG
				# REGISTER DATABASE
				# CREATE SCRIPT
				# PRINT SCRIPT
				# REPLACE SCRIPT
				# DELETE SCRIPT


			# RUN {...} 내에서 스크립트를 실행하는 방법
				# SWITCH 명령어 대부분
				# SET 명령어 대부분
				# ALLOCATE CHANNEL
				# EXECUTE SCRIPT 


			# 운영체제 스크립트를 생성해 RMAN의 CMDFILE 옵션으로 실행하는 방법

