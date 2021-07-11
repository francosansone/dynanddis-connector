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

y = 0.0;
value = 0.0;
sigma = INF;
//FInput = PDFileOpen("/tmp/test.txt", 'r');
//FTimeControl = PDFileOpen("/tmp/test.txt", 'r');
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
  FTimeControl = PDFileOpen("/tmp/time.txt", 'r');
	int tt = PDFileRead(FTimeControl, timeBuf , 255);
	printLog("Size read %d\n", tt);
	currentTime = atoi(timeBuf);
	printLog("CurrentTime %d lastTime %d\n", currentTime, lastTimeRead);
	PDFileClose(FTimeControl);
	sleep(1);
}

printLog("advancing..\n");
lastTimeRead = currentTime;
char buf[1024];
printLog("PDFileOpen value %ld..\n", FInput);
FInput = PDFileOpen("/tmp/test.txt", 'r');
int r = PDFileRead(FInput, buf , 255);
PDFileClose(FInput);
printLog("Size read %d\n", r);
value = strtod(buf, NULL);
counter += 1.0;
printLog("Value read %f\n", value);
sigma = 0;

}
Event fromfile::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

y = value + counter;
return Event(&y, 0);
}
void fromfile::exit() {
//Code executed at the end of the simulation.

}
