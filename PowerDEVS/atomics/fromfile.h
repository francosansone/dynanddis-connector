//CPP:tpfinal/fromfile.cpp
#if !defined fromfile_h
#define fromfile_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "/usr/include/unistd.h"
#include "/usr/include/stdlib.h"


class fromfile: public Simulator { 
// Declare the state,
// output variables
// and parameters

//states
double sigma;
long int FInput;
long int FTimeControl;
int lastTimeRead;
double value;
double counter;


// output
double y;

#define INF 1e20
public:
	fromfile(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
