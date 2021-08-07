#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "flib.h"

///This function is in charge of sanitize the files
double InitialEquation(double v)
{
    printf("*************** Initial equation!!! ***************\n");
    
    FILE *fptr_time = fopen(TIME_MODELICA, "w");
    fprintf(fptr_time, "%lf\n", 0.0);
    fclose(fptr_time);
    
    FILE *fptr_output = fopen(OUTPUT_MODELICA, "w");
    fprintf(fptr_output, "%lf\n", 0.0);
    fclose(fptr_output);
    
    //sleep to wait PowerDEVS starts...
    sleep(10);
    
    FILE *fptr_input = fopen(OUTPUT_POWERDEVS, "r");
    double initial_value = 0.0;
    fscanf(fptr_input, "%lf\n", &initial_value);
    fclose(fptr_input);
    
    printf("initial value read %lf\n", initial_value);
    
    return 1.0;
}

/// Writes the time of modelica simulation
double WriteTime(double time)
{
    printf("WriteTime %lf\n", time);
    FILE *fptr = fopen(TIME_MODELICA, "w");
    fprintf(fptr, "%lf\n", time);
    fclose(fptr);
    return 0.0;
}

/// Reads the last time value of the PowerDEVS simulation and
/// waits if the read value is lower.
double ReadLastValue(double time)
{
    double m = 0.0;
    FILE *fptr;
    fptr = fopen(OUTPUT_POWERDEVS, "r");
    if(fptr){
        fscanf(fptr, "%lf\n", &m);
        fclose(fptr);
    }

    FILE *f_time_ptr = fopen(TIME_POWERDEVS, "r");
    double power_devs_time = 0;
    if (f_time_ptr){
        fscanf(f_time_ptr, "%lf\n", &power_devs_time);
    }
    while(time > power_devs_time){
        fclose(f_time_ptr);
        sleep(1);
        f_time_ptr = fopen(TIME_POWERDEVS, "r");
        fscanf(f_time_ptr, "%lf\n", &power_devs_time);
        printf("power devs time %lf\n", power_devs_time);
    }
    fclose(f_time_ptr);
    return m;
}

/// Write the last value to give information to PowerDEVS simulation.
double WriteLastValue(double value)
{
    printf("WriteLastValue %lf\n", value);
    FILE *fptr = fopen(OUTPUT_MODELICA, "w");
    fprintf(fptr, "%lf\n", value);
    fclose(fptr);
    return 1.0;
}
