<MYSQL 명령어>

## SQL 명령어

	
## CREATE, UPDATE, ALTER, RENAME, SELECT, DESCRIBE, DROP, DELETE...

	# UPDATE 구문

		-- 컬럼의 값을 수정합니다
		# update tablename set col1=새값 weher 조건





	# ALTER 구문  

		-- 테이블 컬럼 이름 or 정보를 수정합니다
		# alter table table_name add name varchar(10);
		
		# alter table 테이블명 change 컬럼이름 새컬럼이름 새컬럼타입
	







	# SHOW 구문

		-- 여러 변수값 중 general_log 이름이 들어간 변수들을 확인합니다
		# show variables where variable_name like 'general_log%';





		-- 여러 변수값 중 version, log, general_log 구문이 들어간 변수값을 확인합니다
		# show variables where variable_name in('version','log','general_log');
		



		-- binary log를 확인합니다 (SQL 쿼리를 수행하면서 쌓는 로그)
		# show binary logs;








	# SET 구문

		-- general_log를 ON으로 설정합니다
		# set global general_log = ON;





	# RENAME 구문

		테이블이름을 잘못 지정했으면 이름을 변경할 수도 있다.
		# rename table tablename1 to tablename2[, tablename3 to tablename4];






	# CREATE 구문

		-- 데이터베이스를 생성합니다
		# create database koradb;


		-- 유저 생성 후 권한 주기
		# create user 'userid'@'localhost' identified by 'qwer1234';
	
		-- 생성된 유저에게 권한을 줍니다
		# grant all privileges on *.* to 'userid'@'localhost';
		# grant all privileges on dbname.* to 'userid'@'localhost';



		-- mytable 테이블을 생성합니다
		# create table mytable(
			id int not null auto_increment primary key, -- 자동으로 1씩 증가하며 ,primarykey 속성을 가집니다
			name varchar(50) not null,   -- null 값이 올 수 없습니다
			modelnumber varchar(15) not null,
			series varchar(30) not null
			);	




		-- koraiv 테이블을 생성합니다
		# create table koraiv (
		  num int(200) auto_increment not null,
		  name varchar(20) not null,
		  univ_id  int(20)  not null,
		  pass varchar(255) not null,
		  primary key (num),
		  unique key korakey1 (univ_id)
		) engine=innodb default charset=utf8;



		-- univ_id 테이블을 생성합니다
		# create table univ_id (
		  univ_id  int(20)  primary key not null,
		  unique key korakey2 (univ_id)
		) engine=innodb default charset=utf8;




		-- emps91 테이블을 생성합니다 
		# create table emps91
		(
		eid int(4)
		,name varchar(4)
		,address varchar(30) default 'seoul'
		,salary int(8)
		,jumin varchar(13) not null
		,deptid int(4)
		,constraint pk_eid_name_emps91 primary key(eid, name)
		,constraint uk_jumin_emps91 unique(jumin)
		,constraint ck_sal_addr_emps91 check(salary > 0 and address is not null)
		);


		# create table dept(
		deptno int(2),
		dname varchar(14),
		loc varchar(13),
		currentdate date default null);












	# SELECT 구문 

		-- 원하는 필드만 조회
		# select 필드명, 필드명 from 테이블명


		-- where 조건 검색
		# select * from 테이블명 where 필드명 = '값'


		-- LIKE 연산자를 활용해 검색합니다
		# select * from 테이블명 where 필드명 like '홍%';


		-- desc 명령어를 통해 내림차순으로 정렬합니다
		# select * from 테이블명 order by 필드명 desc;


		-- 특정 위치에 있는 레코드 ~ 레코드 까지 선택
		-- 예) 2번쨰레코드부터 4개까지선택
		# select * from 필드명 limit 2,4;


		-- a_column 의 같은 값끼리 그룹을 묶음.
		# select a_column from table_name group by a_column;


		-- 테이블의 전체 레코드 갯수를 가져옴
		# select count(*) from table_name;



	 	-- 문자관련 함수
  		-- a_컬럼 에서 왼쪽부터 2자리 잘라서 가져온다.
		# select left(a_column, 2) from table_name;


		-- a_컬럼에서 길이가 10인 레코드만
		# select * from table_name where length(a_column)=10; 


		-- avg : 평균값, min : 최소값, max : 최대값, sum : 합계
		# select avg(a_column),min(a_column),max(a_column),sum(a_column) from table_name;


		-- mysql 버젼 , 유저 , 데이터베이스명 , 날짜보기
		# select version(),user(),database(), now(), current_date;


		
		-- join : a_테이블 과 b_테이블 에서 a_컬럼의 값이 같은 레코드만 가져옴
		# select b.column_b
		from table_a as a
		inner join 
		table_b as b 
		on a.column_a=b.column_a
		where a.column='000';




		-- union : a_테이블 과 b_테이블 에서 a_컬럼,b_컬럼 모든 값을 한꺼번에 가져옴
		select a_column from a_table
		union
		select b_column from b_table;










	# INSERT 구문

		-- 데이터 저장
		# insert into 테이블명 (필드명, 필드명, 필드명) values ('값','값', '값');













	# UPDATE 구문

		-- 데이터 수정
		# update 테이블명 set 수정하고싶은필드명 = '수정하고싶은값' where 기본(primarykey)필드 = '값';


		-- 두개의 테이블에서 조건을 비교하여 업데이트
		update table_a set table_a . a_column = table_b . a_column 
		from table_a, table_b 
		where table_a.a_column = table_b.a_column ;


		-- a_컬럼의 '변경전글자' 라는 문자열을 '변경후글자'로 바꾸어 a_컬럼 수정
		# update table_name set a_column=replace(a_column,'변경전글자','변경후글자');


		-- trim을 사용해 a_컬럼의 왼쪽 오른쪽 공백을 모두 제거합니다
		# update table_name set a_column=trim(a_column);





	# DELETE 구문

		-- 데이터 삭제
		# delete from 테이블명 where 필드 = '값';





	# DROP 구문

		-- 테이블삭제 
		# drop table "table name";

		




	# DESCRIBE 구문

		데이블 필드와 관련된 정보 조회
		# desc 테이블명




	











		
		
--------------------------------------------------------------------------------

<MYSQL 구문 활용>


	# SQLDUMP 명령어
		
	   -- koradb 데이터베이스를 논리적으로 백업합니다 (sql문 생성)
	   cmd> mysqldump -u kora -p koradb > dump.sql
	   


	

	# MYSQLSHOW

		해당 서버에 데이터베이스 종류를 확인합니다	
		cmd> mysqlshow -u kora -p









