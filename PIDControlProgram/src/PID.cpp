// crate a PID class

// include the header file
#include "PID.h"

PID::PID() {}

PID::PID(double Kp, double Ki, double Kd): Kp(Kp), Ki(Ki), Kd(Kd) {}

PID::~PID() {}

void PID::init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    p_error = 0.0;
    i_error = 0.0;
    d_error =0.0;
    step = 1;
}

void PID::updateError(double cte) {
    if (step == 1) {
        p_error = cte;
    }
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;

    step++;
}

double PID::totalError() {
    return -Kp * p_error - Ki * i_error - Kd * d_error;
}

double PID::totalErrorWithoutI() {
    return -Kp * p_error - Kd * d_error;
}