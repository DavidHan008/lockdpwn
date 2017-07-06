#pragma once
#include <Eigen/Dense>
#include <Eigen/Core>
#include "mm.h"

using namespace Eigen;
using namespace std;

class AttitudeKF
{
public:
	AttitudeKF();
	~AttitudeKF();
	void Predict (double gyro[3],double dt);
	void Update (double yaw_gps, double vel_gps);
	
	Vector3d RotationToEuler(Matrix3d X);
	Matrix3d EulerToRotation(Vector3d X_Euler);
	Matrix3d C0_INV(Vector3d x_Euler);

public:
	Matrix3d _X_predict_XYZ;
	Vector3d _X_predict_Euler;

	Matrix3d _P_predict;

	Matrix3d _X_XYZ;
	Vector3d _X_Euler;

	Matrix3d _P;

	Matrix3d _Kh;	

private:
	double _VEL_MIN;

};



