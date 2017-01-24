
===================================================================
*****************************MATLAB******************************
===================================================================

## matlab 명령어들

	# roots : 
	# poly :
	# conv :
	# sysm :
	# diff :
	# int :
	# integral :
	# laplace :
	# solve :
	# plot :
	# ezplot :
	# dsolve :
	# tf2zp :
	# tf('s') :  s = tf('s') 라플라스 함수를 사용하기 위해 s 선언
				 z = tf('z',0.001)
	
	# feedback : 폐루프시스템으로 만들어준다
				 bb = feedback(aa,1);
	# rlocus : 근궤적법
	# rlocfind :
	# rltool :
	# impulse : 충격응답
	# bode : 보드선도, 주파수응답 선도 그리는 함수
	# bandwidth : bandwidth(sysD) 대역폭구하는 함수, 반드시 closed loop 이어야 한다
	# [Gm,Pm,Wcg,Wcp] = margin(SYS) : 해당 함수의 Gain, Phase Margin을 볼 수 있는 함수
	# lsim :
	# nyquist : 나이키스트 선도 그리는 함수
	# c2d :  bb = c2d(aa,0.001,'zoh');
	# d2c :
	# sisotool : sisotool(sysG) rltool과 같은 툴




%----------------------------------------------------
% matlab ==> z변환 예제코드

	Ts =0.001;  % Sampling Time : 0.001 
	s= tf('s');
	z = tf('z',Ts);  

	aa = (0.01272*z + 0.01203)/(z^2 - 1.8349*z + 0.8597);
	bb = feedback(aa,1);

	% bb의l Step응답 테스트
	step(bb,0.1)

	% bb의 Ramp응답 테스트 
	step(bb/(1-z^-1),0.5*z/(z-1),0.1);





%----------------------------------------------------
% matlab ==> 라플라스를 z 변환시키는 코드

	s = tf('s');
	sysDc = 10 * (s/2 + 1)/(s/10 + 1)

	sysDc =
	 
	  100 s + 200
	  -----------
	   2 s + 20
	 
	Continuous-time transfer function.

	T = 0.025;
	 
	sysDd = c2d(sysDc, T, 'zoh');  % z 변환을 수행하나다 zoh를 통해








%----------------------------------------------------
% matlab ==> bode 선도 그리는 코드

	opts = bodeoptions('abs')   % bode 선도 magnitude 단위 바꾸기
	bode(sys,opts)





%----------------------------------------------------
% matlab ==> 다항식 명령어들 root, poly, conv...
	
	# roots([1 3 3 1])     % 근 구하기
	# poly([1 2])            % 다항식 구하기
	# conv(a,b)             % 다항식 곱하기




%----------------------------------------------------
% matlab ==> 미분,적분,라플라스,미분방정식 syms,int,integral...

	syms a b w t x y          % a b w t x y 는 기호임을 선언
	int(x^3/sqrt(1-x),a,b)          % 적분
	diff(t^2 + sin(w*t),t)          % 미분
	diff(x^2 + sin(w*t),x)          % 미분2
	laplace(exp(-t)*sin(w*t),t,s)   % 라플라스 변환
	solve(x^2-1)     	              % 근을 구한다
	ezplot(x^2-1)          % 그래프를 그린다, 구간은 자동설정
  
	% 미분방정식을 푼다
	y = dsolve('(Dy)^2 + y^2 = 1','y(0) = 0')      
   
	% 무명함수 만들기
	fx = @(x) x.^2 + 2*x + 1    



%----------------------------------------------------
% matlab ==>  자동제어 책 코드들

	s = tf('s')
	step(sysG)
	impulse(sysG)

	w = logspace(-2,2);      % set frequency w to 50 values from 10^-2 to 10^2 
	[mag,phase] = bode(sysH,w);
	
	loglog(w,squeeze(mag));   % log-log plot of magnitude   
	
	semilogx(w,squeeze(phase));  % semi-log plot of phase

	# p110
	num = conv([1 2],[1 4]);
	den = conv([1 1 0],[1 3]);
	
	[r,p,k] = residue(num,den);      % compute the residues 

	# p114
	num = 2;
	
	den = poly([-2;-1;-4]);     % form denominator polynomial from its roots

	[r,p,k] = residue(num,den); 	% compute the residues

	# p117
	num = [0 0 0.001]
	den = [1 0.05 0]
	[z,p,k] = tf2zp(num,den)   

	# p118
	s = tf('s')
	sysb = 100/(s^2+10.1*s +101)
	t = 0:0.01:5;
	y = step(sysb,t)
	plot(t,y)

	# p120
	s  = tf('s')
	sysG = 0.0002/s^2;
	t = 0:0.01:10;
	u1 = ...
	[y1] = lsim(sysG,u1,t);    % linear simulation
	...

	# p255
	...
	sysL = ...
	rlocus(sysL)

	# p265
	...
	sysL=...
	rltool(sysL)

	# p270
	...
	sysL = ...
	rlocfind(sysL)

	# p350
	...
	sysG = ...
	nyquist(sysG)






%----------------------------------------------------
% matlab ==> 공을 45각도로 던지는 상황을 plot으로 동영상처럼 보이게 한 코드
	clc,clear all

	% g 값과 초기 던지는 각도 theta값, 초기속도 값을 설정합니다
	g = 9.81; 
	theta0 = 45*pi/180; 
	v0=5;

	% 초기값을 설정합니다
	t(1) = 0; 
	x =0; 
	y =0;

	% 0초일때를 plot합니다
	plot(x,y,'o','MarkerFaceColor','b','MarkerSize',8)
	title('The orbital of thrown Ball','fontsize',15);
	xlabel('Time (t)','fontsize',15);
	ylabel('Height (m)','fontsize',15);
	axis([0 3 0 0.8])
	grid on
	hold on

	% dt의 값을 설정합니다
	% 작게 설정할 수록 더 천천히 움직이는 동영상을 볼 수 있습니다
	dt = 1/256;

	for j = 2:1000
		
		% 루프를 돌면서 x,y 값을 받고
		t(j) = t(j-1) + dt;
		x = v0*cos(theta0)*t(j);
		y = v0*sin(theta0)*t(j)-0.5*g*t(j)^2;
		
		% 그래프를 그립니다
		plot(x,y,'o','MarkerFacecolor','b','MarkerSize',8)
		axis([0 3 0 0.8])
		
		M(j) = getframe;
		
		% 공이 땅에 떨어지면 프로그램이 종료됩니다
		if y<=0
			break
		end
	end







%----------------------------------------------------
% matlab ==>  plot 사용 예제 코드

	t = 0:1:20;
	g = 9.81; m = 68.1; cd = 0.25;
	v = sqrt(g*m/cd)*tanh(sqrt(g*cd/m)*t);

	figure()
	plot(t,v,'r--+','linewidth',1);
	legend('Free fall','location','northwest');
	title('Free fall','fontsize',16);
	xlabel('Time[s]','fontsize',16);
	ylabel('Velocity[km/h]','fontsize',16);
	% axis([0 20 0 65]);
	xlim([0 20]);
	ylim([0 65]);
	grid on;




%----------------------------------------------------
% matlab ==> for 사용 예제 코드

	s = 10;
	H = zeros(s);

	for c =  1:s
		for r = 1:s
			H(r,c) = 1/(r+c-1);
		end
	end




%----------------------------------------------------
% matlab ==> for-if 사용 예제 코드

	nrows = 10; % 행
	ncols = 11; % 열
	A = ones(nrows,ncols);

	for c = 1:nrows
		for r = 1:ncols
			if r == c
				A(r,c) = 2;
			elseif abs(r-c) == 1
				A(r,c) = -1;
			else
				A(r,c) = 0;
			end
		end
	end




%----------------------------------------------------
% matlab ==> for-if 사용 예제 코드2

	A = zeros(1,40);

	for n = 1:1:40;
		if n < 10
			A(1,n) = 111;
		elseif 11 <= n && n <20
			A(1,n) = 222;
		 elseif 21 <= n && n < 30
			A(1,n) = 333;
		elseif 31 <= n && n < 40
			A(1,n) = 444;
		end
	end

	plot(A,'r+','linewidth',3),grid



















===================================================================
*****************************SCILAB******************************
===================================================================

## scilab 명령어들

	# poly :
	# syslin :
	# evans :
	# bode :
	# csim :   gs1 = csim('step',t,sys); // 계단응답




%----------------------------------------------------
% scilab ==> 라플라스 변환 예제 코드

	  s = poly(0,'s'); 		% 라플라스 변수 s를 선언합니다
	  P = 1/(10*s^2 + 0.1*s)
	  P = syslin('c',P)		% P를 시불변선형연속시스템의 전달함수로 표현합니다


	  % 다른 방법도 있다
	  num = 1;
	  den = poly([0 0.1 10],'s','c');
	  P = syslin('c',num,den)





%----------------------------------------------------
% scilab ==> bode 선도를 그리는 예제 코드

	f=linspace(0.01,1,1000); // frequency vector (Hz)
	w=2*%pi*f;  // convert to rad/s
	Pmag=zeros(1,1000);Pph=zeros(1,1000);
	
	for k=1:1000, // compute P(jw) at each frequency point
	  P=1/(-10*w(k)^2+0.1*%i*w(k)); 
	  [Pmag(k),Pph(k)]=polar(P);
	end
	 
	Pph = (180/%pi)*Pph; // convert to degree
	
	figure(1)
	subplot(211),plot2d(f,Pmag);  // magnitude plot
	xlabel("Frequency (Hz)");
	ylabel("Magnitude");
	
	subplot(212),plot2d(f,Pph);  // phase plot
	xlabel("Frequency (Hz)");
	ylabel("Phase (degree)")




%----------------------------------------------------
% scilab ==> design lead Compensator in frequency response system

clear,clc

s = poly(0,'s');
gs = 4/(s^3 + 3*s^2 + 2*s);
gs = syslin('c',gs);
kgs = 5*gs;
ds1 = (1 + s/2) / (1 + s/200);
ds2 = (1+s/3) /(1+s/300);
ds3 = (1+s/2) * (1+s/2) / (1+s/20) / (1+s/20);
ds4 = (1+s/2) * (1+s/2) / (1+s/200) / (1+s/200);
ds5 = (1+s/2) * (1+s/2) * (1+s/2) / (1+s/20) / (1+s/20) / (1+s/20);

kdgs1 = kgs * ds1;
kdgs2 = kgs * ds2;
kdgs3 = kgs * ds3;
kdgs4 = kgs * ds4;
kdgs5 = kgs * ds5;

p_margin(kdgs1)
p_margin(kdgs2)
p_margin(kdgs3)
p_margin(kdgs4)
p_margin(kdgs5)








%----------------------------------------------------
% scilab ==> design lead Compensator in frequency response system

clc //clear window
num=poly([1.59],'s','coeff');
den=poly([1 7],'s','coeff');
g1=syslin('c',num/den) //define tf
t=0:0.05:50;
gs1=csim('step',t,g1);   // 계단응답을 받는 명령어
plot2d(t,gs1); // plotting step response











