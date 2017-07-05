#include "../inc/attitude.h"
#include <stdio.h>
#include <iostream>

using namespace std;

AttitudeKF::AttitudeKF()
{
	//initialization of matrix and vectors
	_X_XYZ = _X_XYZ.Identity();
	_P = _P.Identity() * 1.e10;
	_X_Euler = VectorXd(3);
	_Kh = MatrixXd(3, 3).setZero();
	_VEL_MIN = 0.278;

}
//attitude = [roll, pitch, yaw]

AttitudeKF::~AttitudeKF()
{
	
}

void AttitudeKF::Predict (double gyro[3], double dt)
{
	Vector3d sigma = Vector3d(10.+_DEG2RAD *gyro[0], 10.+_DEG2RAD *gyro[1], 10.+_DEG2RAD *gyro[2]);

	// _x_XYZ
	
	_X_predict_XYZ = _X_XYZ * AngleAxisd(_DEG2RAD * gyro[2] * dt, Vector3d::UnitZ())
				* AngleAxisd(_DEG2RAD * gyro[1] * dt, Vector3d::UnitY())
				* AngleAxisd(_DEG2RAD * gyro[0] * dt, Vector3d::UnitX());

	_X_predict_Euler = RotationToEuler(_X_predict_XYZ);

	Matrix3d C1 = EulerToRotation(_X_Euler);
	//Matrix3d Q = Matrix3d(Vector3d(sigma[0], sigma[1], sigma[2]).asDiagonal());
	Matrix3d C1_inv = C1.inverse();	

	// Pk = P(k-1) + C(1)^(-1) * Q * C(1)^(-T) * dt ^ 2.
	_P_predict = _P + C1_inv * Matrix3d(Vector3d(sigma[0], sigma[1], sigma[2]).asDiagonal()) * C1_inv.transpose() * dt * dt;
	//cout << Matrix3d(Vector3d(sigma[0], sigma[1], sigma[2]).asDiagonal()) << endl << endl << endl;
	//puts("");
}

void AttitudeKF::Update_IMU(double gyro[3], double accl[3])
{

	Vector3d g = Vector3d(_X_predict_XYZ(0)*accl[0],_X_predict_XYZ(1)*accl[1],_X_predict_XYZ(2)*accl[2]);

	double sw = _DEG2RAD*sqrt(gyro[0]*gyro[0] + gyro[1]*gyro[1] + gyro[1]*gyro[1]);
	double sa = fabs(sqrt (accl[0]*accl[0] + accl[1]*accl[1] + accl[2]*accl[2]) - 1.);
	double sigma = 0.1 + 100*sa + 100*sw;

	double delta_phi   = atan2 (-g(1), -g(2));
	double delta_theta = (-1 < g(0) && g(0) < 1) ? asin(-g(0)/-1.) : 0.;

	
	Matrix3d C0_inv = C0_INV(_X_predict_Euler);

	_Kh = _P_predict * (_P_predict + C0_inv * Matrix3d(Vector3d(sigma, sigma, 1.e8).asDiagonal()) * C0_inv.transpose() ).inverse();

	_X_XYZ = EulerToRotation(Vector3d(_Kh(0,0) *delta_phi, _Kh(1,1) *delta_theta, 0.0)) * _X_predict_XYZ;

	_P = _P_predict - _Kh *_P_predict;

}

void AttitudeKF::Update_GPS(double yaw_gps, double vel_gps)	
{
	if(_VEL_MIN < vel_gps)
	{
		//double vel_filtered = (_VEL_MIN < vel_gps) ? vel_gps-_VEL_MIN : 0.;

		double psi = atan2( _X_predict_XYZ(1,0), _X_predict_XYZ(0,0));


		// 상수들 .. 임의.
		const double sigma_gps = 10.0;
		const double epsilon = 1.e-8;
		//double sigma_psi = 2 * sigma_gps/(epsilon + vel_gps*2.0);
		//double sigma_psi = 2 * sigma_gps/(epsilon + exp(vel_gps*8.0));
		
		
		//sigma_psi =  2.0;
		double sigma_psi = 0.001; //0.001
		double rn = 1.e8; //1.e10

		Matrix3d C0_inv = C0_INV(_X_predict_Euler);

		_Kh = _P_predict * (_P_predict + C0_inv * Matrix3d(Vector3d(rn*rn, rn*rn, sigma_psi*sigma_psi).asDiagonal()) * C0_inv.transpose() ).inverse();

		_X_XYZ = EulerToRotation(Vector3d(0, 0, _Kh(2,2) * DeltaRad (yaw_gps, psi))) * _X_predict_XYZ;

		_P = _P_predict - _Kh *_P_predict;
	}
}



Matrix3d AttitudeKF::EulerToRotation(Vector3d X_Euler)
{
	double sin_phi = sin(X_Euler[0]);
	double cos_phi = cos(X_Euler[0]);

	double sin_tht = sin(X_Euler[1]);
	double cos_tht = cos(X_Euler[1]);

	double sin_psi = sin(X_Euler[2]);
	double cos_psi = cos(X_Euler[2]);

	Matrix3d A;

	A(0,0) = cos_psi*cos_tht;	
	A(0,1) = cos_psi*sin_phi*sin_tht - cos_phi*sin_psi;		
	A(0,2) = sin_phi*sin_psi + cos_phi*cos_psi*sin_tht;		
	A(1,0) = cos_tht*sin_psi;	
	A(1,1) = cos_phi*cos_psi + sin_phi*sin_psi*sin_tht;		
	A(1,2) = cos_phi*sin_psi*sin_tht - cos_psi*sin_phi;	
	A(2,0) = -sin_tht;			
	A(2,1) = cos_tht*sin_phi;								
	A(2,2) = cos_phi*cos_tht;

	return A;
}

Vector3d AttitudeKF::RotationToEuler (Matrix3d X)
{
	// x, x, x = (atan2, atan2, atan2)
	return Vector3d( atan2(X(2,1), X(2,2)), atan2(-X(2,0), sqrt(X(2,1)*X(2,1) + X(2,2)*X(2,2))), atan2(X(1,0), X(0,0)) );
}


Matrix3d AttitudeKF::C0_INV(Vector3d x_Euler)
{
	const double eps = 1.e-6;

	double sp = sin(x_Euler[2]);
	double cp = cos(x_Euler[2]);
	double ct = cos(x_Euler[1]);
	double tt = tan(x_Euler[1]);

	if (-eps < ct && ct < 0) ct = -eps;	
	if (0 <= ct && ct < eps) ct = +eps;

	Matrix3d ret = MatrixXd(3, 3).setZero();

	ret(0,0) = cp/ct;
	ret(0,1) = sp/ct;
	ret(0,2) = 0;
	ret(1,0) = -sp;
	ret(1,1) = cp;
	ret(1,2) = 0;
	ret(2,0) = cp*tt;
	ret(2,1) = sp*tt;
	ret(2,2) = 1;


	return ret;
}
