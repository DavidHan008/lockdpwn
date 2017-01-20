--데이터베이스에 복구할 데이터 변경 작업의 내용을 생성합니다.
conn system/oracle4U@orcl
set echo on

-- 동일한 이름의 테이블을 삭제
-- 테이블이 없으면 에러가 납니다. 정상입니다.

DROP TABLE hr.student PURGE ;

DROP TABLE hr.professor PURGE ;

DROP TABLE hr.course PURGE ;

DROP TABLE hr.score PURGE ;

-- 계정생성: 계정이 있으면 에러가 납니다. 정상입니다.
-- 계정이 없으면 HR 계정을 생성합니다.
create user hr
identified by oracle4U
default tablespace users
quota unlimited on users ;

grant connect, resource to hr ;

CREATE TABLE hr.student
(sno varchar2(6), sname varchar2(20), sex varchar2(4)
,syear number, major varchar2(20), avr number(4,2)) 
tablespace users;
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;

CREATE TABLE hr.professor
(pno varchar2(4), pname varchar2(20), section varchar2(20)
,orders varchar2(20), hdate date) 
tablespace users ;
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;

CREATE TABLE hr.course
(cno varchar2(4), cname varchar2(20)
,st_num number, pno varchar2(4)) 
tablespace users;
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;

CREATE TABLE hr.score
(cno varchar2(4), sno varchar2(6), result number)
tablespace users;
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;

INSERT INTO hr.student VALUES ('915301','shin','m',1,'chem',0.95);
INSERT INTO hr.student VALUES ('915302','kim','m',1,'chem',0.68);
INSERT INTO hr.student VALUES ('915303','lee','m',1,'chem',1.25);
INSERT INTO hr.student VALUES ('915304','macho','m',1,'chem',1.68);
INSERT INTO hr.student VALUES ('915305','kwanwoo','m',1,'chem',3.20);
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;

INSERT INTO hr.professor
VALUES ('1001','songkang','chem','prof1',to_DATE('1999-12-20','YYYY-MM-DD'));
INSERT INTO hr.professor
VALUES ('1002','konsongsung','chem','prof1',to_DATE('1998-01-20','YYYY-MM-DD'));
INSERT INTO hr.professor
VALUES ('1003','jinmoung','chem','prof1',to_DATE('1997-08-20','YYYY-MM-DD'));
INSERT INTO hr.professor
VALUES ('1004','sijin','chem','prof2',to_DATE('2000-12-20','YYYY-MM-DD'));
INSERT INTO hr.professor
VALUES ('1005','nojisim','chem','prof2',to_DATE('1995-03-20','YYYY-MM-DD'));
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;

INSERT INTO hr.course VALUES ('1211','chem1',3,'1001');
INSERT INTO hr.course VALUES ('1212','chem2',3,'1002');
INSERT INTO hr.course VALUES ('1213','chem3',3,'1003');
INSERT INTO hr.course VALUES ('1214','chem4',2,'1004');
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;

INSERT INTO hr.score VALUES ('1211','915301',63);
INSERT INTO hr.score VALUES ('1211','915302',80);
INSERT INTO hr.score VALUES ('1211','915303',6);
INSERT INTO hr.score VALUES ('1211','915304',33);
COMMIT ;
ALTER SYSTEM SWITCH LOGFILE ;
ALTER SYSTEM CHECKPOINT ;
set echo off
exit

