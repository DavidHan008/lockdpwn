#include "../inc/posvel.h"
#include "../inc/mm.h"
#include <iostream>

using namespace std;

PosVelKF::PosVelKF()
{
	_x = VectorXd(6).setZero();
	_P =  _P.Identity(6, 6) * 1.e10;
	_Kp = MatrixXd(6, 3).setZero();
	_Kv = MatrixXd(6, 3).setZero();
}

PosVelKF::~PosVelKF()
{

}

void PosVelKF::Predict (const Matrix3d &Rn, double gyro[3], double accl[3], double dt)
{
	Vector3d g = Vector3d( 0., 0., -1. );	
	Vector3d f = Vector3d( accl[0], accl[1], accl[2] );

	const double gz = -9.80665; 
	Vector3d vd = gz * (Rn * f - g); 

	Vector3d rd = Vector3d ( _x[0], _x[1], _x[2] ); 


	double xd_[6] = { 
		vd[0], vd[1], vd[2],	
		rd[0], rd[1], rd[2],	
	};


	VectorXd xd = VectorXd(6).setZero();

	for(int i = 0 ; i < 6 ; i++)
		xd(i) = xd_[i];

	//Vector6d xd(&xd_[0], 6);

	///////////////////////////////////
	MatrixXd I = I.Identity(6, 6);
	MatrixXd F = MatrixXd(6, 6).setZero();
	MatrixXd G = MatrixXd(6, 6).setZero();
	MatrixXd Q = MatrixXd(6, 6).setZero();


	F(3,0) = F(4,1) = F(5,2) = 1;

	G(0,0) = Rn(0,0);		G(0,1) = Rn(0,1);		G(0,2) = Rn(0,2);	
	G(1,0) = Rn(1,0);		G(1,1) = Rn(1,1);		G(1,2) = Rn(1,2);	
	G(2,0) = Rn(2,0);		G(2,1) = Rn(2,1);		G(2,2) = Rn(2,2);	

	G(0,3) = G(1,4) = G(2,5) = -1;


	double sw = 5 * _DEG2RAD * sqrt(gyro[0]*gyro[0] + gyro[1]*gyro[1] + gyro[2]*gyro[2]);	
	double sa = 5 * gz * fabs(sqrt(accl[0]*accl[0] + accl[1]*accl[1] + accl[2]*accl[2]) - 1.);	

	//Q
	Q(0,0) = Q(1,1) = Q(2,2) = 0.01 + sw * sw + sa * sa;	
	Q(3,3) = Q(4,4) = Q(5,5) = 0.1 * 0.1;	

	MatrixXd A = I + F * dt;

	//cout << "A\n" << A << endl;


	_x += xd * dt;
	_P = A * _P * A.transpose() + G * Q * G.transpose() * (dt * dt);
}

void PosVelKF::Update (const Matrix3d &Rn, double pos_x, double pos_y, double pos_z)
{
	Vector3d z(3);
	z[0] = pos_x;	z[1] = pos_y;	z[2] = pos_z;

	//R
	const double sigma_gps = 0.001; //parameter R	//130329 sigma_gps 1º¯°æÇÔÀž·ÎŒ­ R°ª º¯°æ ->3º¯°æ ->0.1

	MatrixXd R = MatrixXd(3, 3).setZero();
	//cout << "R\n" << R << endl << endl;

	R(0,0) = R(1,1) = R(2,2) = sigma_gps*sigma_gps;

	MatrixXd I = I.Identity(6, 6);
	MatrixXd H = MatrixXd(3, 6).setZero();



	H(0,3) = H(1,4) = H(2,5) = 1.;
	
	_Kp = _P * H.transpose() * (H * _P * H.transpose() + R).inverse();
	_P = (I - _Kp * H) * _P;
	_x += _Kp * (z - H * _x);	

}


void PosVelKF::Update (const Matrix3d &Rn, double vel_x, double sigma_x)
{
	Vector3d z(3);
	z[0] = vel_x;	z[1] = 0.;	z[2] = 0.;

	MatrixXd R = MatrixXd(3, 3).setZero();
	//cout << "R\n" << R << endl << endl;
	double sigma_ = 0.01;
	R(0,0) = sigma_x;
	R(1,1) = R(2,2) = sigma_*sigma_;

	MatrixXd I = I.Identity(6, 6);
	MatrixXd H = MatrixXd(3, 6).setZero();

	MatrixXd RnI = R.transpose();

	H(0,0)  = RnI(0,0); H(0,1)  = RnI(0,1); H(0,2)  = RnI(0,2);
	H(1,0)  = RnI(1,0); H(1,1)  = RnI(1,1); H(1,2)  = RnI(1,2);
	H(2,0)  = RnI(2,0); H(2,1)  = RnI(2,1); H(2,2)  = RnI(2,2);

	//cout << "I\n" << I << endl << endl;
	//cout << "H\n" << H << endl << endl;

	_Kp = _P * H.transpose() * (H * _P * H.transpose() + R).inverse();
	_P = (I - _Kp * H) * _P;
	_x += _Kp * (z - H * _x);	

	//cout << "Kp\n" << _Kp << endl << endl;
	//cout << "P\n" << _P << endl << endl;
	//cout << "_x\n" << _x << endl << endl;
	
}






