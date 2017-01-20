% ���������� ���� Assignment3 ����Ʈ�� �ڵ�
%{
        �����ǥ
        Tr = 0.016s  <==> Wn = 112.5 rad/s
        Ts = 0.06s   <==> sigma = 76.6
        Mp = 4%     <==> zeta = 0.71
        ess = 0%
%}
clear,clc;

s = tf('s');

J = 52E-7;        % �����������Ʈ [ kg * m^2 ]
b = 3.1831E-4;   % ����������� [ Nm*s/rad ]  % pdf�� Speed Regulation Constant�� ���� ��´� % 3.141e-03
K = 0.0245;       % Kt ,��ũ��� [ Nm/A ] 
                      % Ke ,�������»�� [ V*s/rad ] ���� ��� ���� ������ �Ѵ� 
R = 1.8;           % ������ �������� [ Ohm ]
L = 0.0024;       % ������ �δ��Ͻ� [ H ]

% ������ �и� 2���������̳� 
% ���ӵ�(theta') ==> ����(theta)�� output�� �ٲ�鼭 �������·� 1/s�� �߰��Ǿ� 3�������� ���°� �ȴ�.
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));  


% =============== �̻� (Discrete Equivalent) ����  ======================
% �ڼ��� ������ Ȯ���� �ùĸ�ũ�� �����س���
Ds = pid(4,2.5,0.012);
Gs = my_motor;
DGs = Ds * Gs;
[Gm,Pm,Wcg,Wcp] = margin(Gs)
clGs = feedback(Gs,1);
bandwidth(clGs)
bode(clGs)

% ������ Ts�� ã�´� (Wcpm�� 2�谡 Wbw�̰� Wbw�� 25�谡 ������ Ts�̹Ƿ�
% Ts�� Wcpm�� 50�� ������ �� �� �ִ�.
Ws = 25*2 * 20.6463;
fs = Ws / 2 / pi;
Ts = 1/fs;
Dz = c2d(Ds,Ts,'tustin');




% =============== �̻꼳�� (Discrete Design) ���ļ����� ����  ======================
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

% Gs�� ess(ramp)�� ���ϱ� ���� �ڵ�
Es = (1-clGs);
syms s;
double(limit( s/s^2 *(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s)/(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s + 0.0245)  ,s,0))
% Gs�� ess(ramp)�� 0.0479�� ���� Ȯ���߰� K=100�� �־� ess�� 0�� �����ϰ� �ߴ�
K = 100;
double(limit( s/s^2 *(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s)/(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s + 0.0245* K)  ,s,0))


% Gz�� ess(ramp)�� ���ϱ� ���� �ڵ�
% ess = 0�� �ſ� �����ϰ� �ϱ� ���ؼ� Kv�� ����  10000������ ��´�
Ez = (1- clGz);

syms z
double(limit(  ( (z-1)/Ts*z )*(z^3-1.443*z^2 + 0.4503*z - 0.007173)/(z^3 - 1.416*z^2 + 0.4924*z - 0.00464)  ,z,1))


