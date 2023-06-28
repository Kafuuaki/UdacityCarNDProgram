// implement a PID controller

// First, directives

// q: what does below directive do?
// a: it includes the header file iostream
// q: what is a header file iostram?
// a: it is a header file that contains the declarations of the standard input/output library in C++.
#ifndef PID_H
#define PID_H

// a class framework include:
// constructor, destructor, copy constructor, copy assignment operator, move constructor, move assignment operator..

class PID {
public:
    PID();

    // can c++ have multiple constructors?
    // yes, c++ can have multiple constructors
    // overloading the contructor to initialize the class
    PID(double Kp, double Ki, double Kd);

    // why virtual?
    // a: virtual means that the function can be overriden by a derived class
    virtual ~PID();

    void init(double Kp, double Ki, double Kd);

    void updateError(double cte);

    double totalError();

    double totalErrorWithoutI();

// private:
    double Kp;
    double Ki;
    double Kd;

    double p_error;
    double i_error;
    double d_error;
    double step;
};


// close the directive
#endif