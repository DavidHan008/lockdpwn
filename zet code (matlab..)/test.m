% 디지털제어 수업 Assignment3 레포트용 코드
%{
        설계목표
        Tr = 0.016s  <==> Wn = 112.5 rad/s
        Ts = 0.06s   <==> sigma = 76.6
        Mp = 4%     <==> zeta = 0.71
        ess = 0%
%}
clear,clc;

s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]

% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));  


% =============== 이산등가 (Discrete Equivalent) 설계  ======================
% 자세한 설계의 확인은 시뮬링크에 저장해놨다
Ds = pid(4,2.5,0.012);
Gs = my_motor;
DGs = Ds * Gs;
[Gm,Pm,Wcg,Wcp] = margin(Gs)
clGs = feedback(Gs,1);
bandwidth(clGs)
bode(clGs)

% 적절한 Ts를 찾는다 (Wcpm의 2배가 Wbw이고 Wbw의 25배가 안정한 Ts이므로
% Ts는 Wcpm의 50배 정도로 볼 수 있다.
Ws = 25*2 * 20.6463;
fs = Ws / 2 / pi;
Ts = 1/fs;
Dz = c2d(Ds,Ts,'tustin');




% =============== 이산설계 (Discrete Design) 주파수응답 설계  ======================
Gz = c2d(Gs,Ts,'zoh');
bode(Gz)
[Gm2,Pm2,Wcg2,Wcp2] = margin(Gz)
clGz = feedback(Gz,1);
DGz = Dz * Gz;
bode(DGz)
[Gm3,Pm3,Wcg3,Wcp3] = margin(DGz)
clDGz = feedback(DGz,1);
step(clGs,clDGz)
stepinfo(clDGz)

% Gs의 ess(ramp)를 구하기 위한 코드
Es = (1-clGs);
syms s;
double(limit( s/s^2 *(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s)/(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s + 0.0245)  ,s,0))
% Gs의 ess(ramp)는 0.0479인 것을 확인했고 K=100을 넣어 ess를 0에 수렴하게 했다
K = 100;
double(limit( s/s^2 *(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s)/(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s + 0.0245* K)  ,s,0))


% Gz의 ess(ramp)를 구하기 위한 코드
% ess = 0에 매우 근접하게 하기 위해서 Kv의 값은  10000정도로 잡는다
Ez = (1- clGz);

syms z
double(limit(  ( (z-1)/Ts*z )*(z^3-1.443*z^2 + 0.4503*z - 0.007173)/(z^3 - 1.416*z^2 + 0.4924*z - 0.00464)  ,z,1))


