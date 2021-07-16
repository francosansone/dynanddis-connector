#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "flib.h"

//double WriteLastSigma(double sigma)
//{
//    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "w");
//    fprintf(fptr, "%lf", sigma);
//    fclose(fptr);
//    return 0.0;
//}

//double ReadLastSigma()
//{
//    printf("****ReadLastSigma\n");
//    double value;
//    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "r");
//    fscanf(fptr, "%lf\n", &value);
//    printf("Read last sigma %lf\n", value);
//    return value;
//}

///This function is in charge of sanitize the files
double InitialEquation(double v)
{
    printf("*************** Initial equation!!! ***************\n");
    return 1.0;
}

double WriteTime(double time)
{
    printf("WriteTime %lf\n", time);
    FILE *fptr = fopen(TIME_MODELICA, "w");
    fprintf(fptr, "%lf\n", time);
    fclose(fptr);
    return 0.0;
}

double ReadLastValue(double time)
{
    if(time > 1.) {
        printf("ReadLastValue %lf\n", time);
    }
    double m;
    FILE *fptr;
    fptr = fopen(OUTPUT_POWERDEVS, "r");
    //printf("ReadLastSigma %lf", ReadLastSigma());
    fscanf(fptr, "%lf\n", &m);
    fclose(fptr);
    if(time > 1.) {
        printf("entered while zone\n");
        FILE *f_time_ptr = fopen(TIME_POWERDEVS, "r");
        double power_devs_time = 0;
        if (f_time_ptr){
            fscanf(f_time_ptr, "%lf\n", &power_devs_time);
        }
        while(time > power_devs_time){
            printf("waiting!!!!\n");
            fclose(f_time_ptr);
            sleep(1);
            f_time_ptr = fopen(TIME_POWERDEVS, "r");
            fscanf(f_time_ptr, "%lf\n", &power_devs_time);
            printf("power devs time %lf\n", power_devs_time);
        }
        fclose(f_time_ptr);
    }
    
    return m;
}

double WriteLastValue(double value)
{
    printf("WriteLastValue %lf\n", value);
    FILE *fptr = fopen(OUTPUT_MODELICA, "w");
    fprintf(fptr, "%lf\n", value);
    fclose(fptr);
    return 1.0;
}
