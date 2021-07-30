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

initial = va_arg(parameters, double);
expected = va_arg(parameters, double);
interval = va_arg(parameters, double);
lambda_value = va_arg(parameters, double);

char expected_char[10] = "";
char interval_char[10] = "";

y = 0.0;
value_read = 0.0;
last_value = initial;
sigma = INF;
last_time_read = 0.0;
last_time_write = 0;
last_value = 0.0;

f_time_control = PDFileOpen(TIME_POWERDEVS, 'w');
f_input = PDFileOpen(OUTPUT_POWERDEVS, 'w');
sprintf(expected_char, "%lf", initial);
PDFileWrite(f_input, expected_char, 5);
sprintf(interval_char, "%lf", interval);
PDFileWrite(f_time_control, interval_char, 5);
PDFileClose(f_input);
PDFileClose(f_time_control);

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
char time_buf[1024];
double current_time = last_time_read;
while (current_time <= last_time_read) {
    f_modelica_time = PDFileOpen(TIME_MODELICA, 'r');
    int size = PDFileRead(f_modelica_time, time_buf, 255);
    printLog("Time read %s\n", time_buf);
    current_time = strtod(time_buf, NULL);
    printLog("CurrentTime %lf lastTime %lf\n", current_time, last_time_read);
    PDFileClose(f_modelica_time);
    sleep(1);
}

printLog("advancing..\n");
double diff = current_time - last_time_read;
last_time_read = current_time - diff + interval;
char buf[1024];
printLog("PDFileOpen value %ld..\n", f_input);
f_input  = PDFileOpen(OUTPUT_MODELICA, 'r');
int r = PDFileRead(f_input, buf , 255);
PDFileClose(f_input);
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

f_time_control = PDFileOpen(TIME_POWERDEVS, 'w');
char time_to_write[20] = "";
sprintf(time_to_write, "%lf", last_time_read);
PDFileWrite(f_time_control, time_to_write, 20);
PDFileClose(f_time_control);
printLog("Time wrote\n");

double error = expected - value_read;
last_value += error *  lambda_value;

y = last_value;

f_output = PDFileOpen(OUTPUT_POWERDEVS, 'w');
char value_to_write[10] = "";
sprintf(value_to_write, "%lf", y);
printLog("valueToWrite %s\n", value_to_write);
PDFileWrite(f_output, value_to_write, 10);
PDFileClose(f_output);

return Event(&y, 0);
}
void fromfile::exit() {
//Code executed at the end of the simulation.

}
