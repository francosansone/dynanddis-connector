#include "fromfile.h"
void fromfile::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

printLog("\initialized...\n");

expected_value = va_arg(parameters,double);

y = 0.0;
value_read = 0.0;
last_value = 0.0;
sigma = INF;
lastTimeWrite = 0;
last_value = 0.0;
FInput = PDFileOpen(TIME_POWERDEVS, 'w');
FTimeControl = PDFileOpen(OUTPUT_POWERDEVS, 'w');
PDFileWrite(FInput, "0", 1);
PDFileWrite(FTimeControl, "0", 1);
PDFileClose(FInput);
PDFileClose(FTimeControl);
sleep(10);

}
double fromfile::ta(double t) {
//This function returns a double.
return sigma;
}
void fromfile::dint(double t) {
sigma = INF;
}
void fromfile::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
// first chck time
char timeBuf[1024];
int currentTime = lastTimeRead;
while (currentTime <= lastTimeRead) {
  FModelicaTime = PDFileOpen(TIME_MODELICA, 'r');
	int tt = PDFileRead(FModelicaTime, timeBuf , 255);
	printLog("Size read %d\n", tt);
	currentTime = atoi(timeBuf);
	printLog("CurrentTime %d lastTime %d\n", currentTime, lastTimeRead);
	PDFileClose(FModelicaTime);
	sleep(1);
}

printLog("advancing..\n");
lastTimeRead = currentTime;
char buf[1024];
printLog("PDFileOpen value %ld..\n", FInput);
FInput = PDFileOpen(OUTPUT_MODELICA, 'r');
int r = PDFileRead(FInput, buf , 255);
PDFileClose(FInput);
printLog("Size read %d\n", r);
value_read = strtod(buf, NULL);
printLog("Value read %f\n", value_read);

sigma = 0;

}
Event fromfile::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

FTimeControl = PDFileOpen(TIME_POWERDEVS, 'w');
char timeToWrite[5] = "";
sprintf(timeToWrite, "%d", lastTimeRead);
PDFileWrite(FTimeControl, timeToWrite, 5);
PDFileClose(FTimeControl);
printLog("Time wrote\n");

double error = expected_value - value_read;
last_value += error *  3;

y = last_value;

FOutput = PDFileOpen(OUTPUT_POWERDEVS, 'w');
char valueToWrite[10] = "";
sprintf(valueToWrite, "%lf", y);
printLog("valueToWrite %s\n", valueToWrite);
PDFileWrite(FOutput, valueToWrite, 10);
PDFileClose(FOutput);


return Event(&y, 0);
}
void fromfile::exit() {
//Code executed at the end of the simulation.

}
