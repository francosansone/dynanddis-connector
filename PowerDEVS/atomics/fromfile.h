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
long int f_input;
long int f_time_control;
long int f_modelica_time;
long int f_output;
double last_time_read;
double last_time_write;
double value_read;
double last_value;

// output
double y;

// parameters
double initial;
double expected;
double interval;
double lambda_value;

#define INF 1e20
#define TIME_POWERDEVS "/tmp/time_powerdevs.txt"
#define TIME_MODELICA "/tmp/time_modelica.txt"
#define OUTPUT_POWERDEVS "/tmp/output_powerdevs.txt"
#define OUTPUT_MODELICA "/tmp/output_modelica.txt"

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
