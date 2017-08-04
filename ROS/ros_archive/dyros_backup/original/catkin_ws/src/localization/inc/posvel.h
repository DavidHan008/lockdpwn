#pragma once
#include <Eigen/Dense>
#include <Eigen/Core>
#include "mm.h"


using namespace Eigen;
using namespace std;

class PosVelKF
{
public:
	PosVelKF();
	~PosVelKF();

	void Predict (const Matrix3d &Rn, double gyro[3], double accl[3], double dt);
	
	void Update (const Matrix3d &Rn, double pos_x, double pos_y, double pos_z);

public:
	VectorXd _x;	
	MatrixXd _P;
	MatrixXd _Kv;	
	MatrixXd _Kp;		
};
