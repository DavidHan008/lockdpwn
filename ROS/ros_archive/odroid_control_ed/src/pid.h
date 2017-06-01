class PID {
	double Kp;
	double Ki;
	double Kd;

	double set_point;
	double e;
	double e_int;
	double int_e_max;
	double int_e_min;

	double e_t;
	double de_t;
	double P_val;
	double I_val;
	double D_val;
	double PID_result;

	double current_value;

public:
	PID(double p=2.0, double i=0, double d=0, double de =0, double e_int = 0, double Integrator_max= 500, double Integrator_min = -500);
	double update(double curr_value, int dt);

	void setPoint(double set_point);

	void setKp(double P);
	void setKi(double I);
	void setKd(double D);

	double getPoint();
	double getError();
};

PID::PID(double P, double I, double D, double de, double e_int, double Integrator_max, double Integrator_min){
	this->Kp = P;
	this->Ki = I;
	this->Kd = D;

	this->set_point = 0;
	this->e  = 0;

	this->e_int = 0;
	this->int_e_max = Integrator_max;
	this->int_e_min = Integrator_min;

	this->current_value = 0;
}

double PID::update(double curr_value, int dt){
	this->current_value = curr_value;

	e_t = this->set_point - curr_value;
	de_t = (e_t - this->e) / dt;

	this->e_int = this->e_int * e_t * dt;

	if (this->e_int  > this->int_e_max)
		this->e_int = this->int_e_max;
	else if (this->e_int  < this->int_e_min)
		this->e_int = this->int_e_min;


	P_val = this->Kp * e_t;
	I_val = this->Ki * this->e_int;
	D_val = this->Kd * de_t;

	
	this->PID_result = P_val + I_val + D_val;
	this->e = e_t;

	return this->PID_result;
}

void PID::setPoint(double set_point){
	this->set_point = set_point;
	this->e_int = 0;
	this->e = set_point - this->current_value;
}

void PID::setKp(double P){
	this->Kp = P;
}

void PID::setKi(double I){
	this->Ki = I;
}

void PID::setKd(double D){
	this->Kd = D;
}

double PID::getPoint(){
	return this->set_point;
}

double PID::getError(){
	return this->e;
}
