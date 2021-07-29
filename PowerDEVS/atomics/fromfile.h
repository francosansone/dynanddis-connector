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
long int FModelicaTime;
long int FOutput;
int lastTimeRead;
int lastTimeWrite;
double value_read;
double last_value;

// output
double y;

// parameters
double expected_value;

#define INF 1e20
#define TIME_POWERDEVS "/home/fran/Documents/modelica/time_powerdevs.txt"
#define TIME_MODELICA "/home/fran/Documents/modelica/time_modelica.txt"
#define OUTPUT_POWERDEVS "/home/fran/Documents/modelica/output_powerdevs.txt"
#define OUTPUT_MODELICA "/home/fran/Documents/modelica/output_modelica.txt"

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
