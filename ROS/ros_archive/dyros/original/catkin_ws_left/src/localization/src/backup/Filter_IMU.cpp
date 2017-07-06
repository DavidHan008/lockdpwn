#include "../inc/Filter_IMU.h"
#include <math.h>

Filter_IMU::Filter_IMU ()
{
	_HDR_I[0] = _HDR_I[1] = _HDR_I[2] = 0;
	_HSR_I = 1.;

	_w_lp_init = false;
	_w_dl_init = false;

	_T = 0.005;
	_tau = 0.01; //시상수 //130329 HB may be 변경 
}
Filter_IMU::~Filter_IMU ()
{
}

inline int SIGN (double v)
{
	if (v > 0.) return 1;
	if (v < 0.) return -1;
	return 0;
}

inline int SIGN_CHANGED (double v1, double v2)
{
	if (v1 < 0. && v2 > 0.) return 1;
	if (v1 > 0. && v2 < 0.) return 1;
	return 0;

}

void Filter_IMU::HDR (double v[3], double threshold, double ic)	//Lk gyro, 3, 0.001
{
	v[0] += _HDR_I[0];
	v[1] += _HDR_I[1];
	v[2] += _HDR_I[2];

	//const double ic = 0.001;
	//const double threshold = 15;

	if ((-threshold < v[0] && v[0] < threshold) && 	//Lk 각속도가 +3~-3사이인 경우 bias drift 처리
		(-threshold < v[1] && v[1] < threshold) &&  // threshold는 맞는지???
		(-threshold < v[2] && v[2] < threshold) ){  //Lk 좌회전시 +, 우회전시 - 

		_HDR_I[0] -= SIGN(v[0])*ic;    //Lk한 방향으로 정속인 경우 누적이 된다???
		_HDR_I[1] -= SIGN(v[1])*ic;	   //Repetition Attenuator는 필요 없나???
		_HDR_I[2] -= SIGN(v[2])*ic;
	}
}

void Filter_IMU::HSR (double v[3], double threshold, double ic)//accl, 0.03, 1.0001
{
	v[0] *= _HSR_I;	//initial value = 1
	v[1] *= _HSR_I;
	v[2] *= _HSR_I;

	double a = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]) - 1.;

	//const double ic = 1.0001;
	//const double threshold = 0.01;

	if (-threshold < a && a < threshold) {	//Lk threshold보다 크면 신뢰x 
		if (a > 0.)      _HSR_I /= ic;		//threshold 0.03 ???
		else if (a < 0.) _HSR_I *= ic;
	}
}

void Filter_IMU::LowPassFilter (double v[3])
{
	if (!_w_lp_init) {
		_w_lp[0] = v[0];	
		_w_lp[1] = v[1];	
		_w_lp[2] = v[2];	

		_w_lp_init = true;
	}

	_w_lp[0] = (_T*v[0] + _tau*_w_lp[0])/(_T + _tau);
	_w_lp[1] = (_T*v[1] + _tau*_w_lp[1])/(_T + _tau);
	_w_lp[2] = (_T*v[2] + _tau*_w_lp[2])/(_T + _tau);

	v[0] = _w_lp[0];
	v[1] = _w_lp[1];
	v[2] = _w_lp[2];
}

void Filter_IMU::Delagging (double v[3])
{
	if (!_w_dl_init) {
		_w_dl[0] = v[0];	
		_w_dl[1] = v[1];	
		_w_dl[2] = v[2];	

		_w_dl_init = true;
	}

	double wd[3];

	wd[0] = v[0] + _tau/_T*(v[0] - _w_dl[0]);
	wd[1] = v[1] + _tau/_T*(v[1] - _w_dl[1]);
	wd[2] = v[2] + _tau/_T*(v[2] - _w_dl[2]);

	_w_dl[0] = v[0];
	_w_dl[1] = v[1];
	_w_dl[2] = v[2];

	v[0] = wd[0];
	v[1] = wd[1];
	v[2] = wd[2];
}

