#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "flib.h"

double WriteLastSigma(double sigma)
{
    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "w");
    fprintf(fptr, "%lf", sigma);
    fclose(fptr);
    return 0.0;
}

double ReadLastSigma()
{
    printf("****ReadLastSigma\n");
    double value;
    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "r");
    fscanf(fptr, "%lf\n", &value);
    printf("Read last sigma %lf\n", value);
    return value;
}

double WriteTime(double time)
{
    printf("WriteTime %lf\n", time);
    FILE *fptr = fopen("/home/fran/Documents/modelica/time.txt", "w");
    fprintf(fptr, "%lf\n", time);
    fclose(fptr);
    return 0.0;
}

double ReadLastValue(double time)
{
    printf("ReadLastValue %lf\n", time);
    double m;
    FILE *fptr;
    fptr = fopen("/home/fran/Documents/modelica/input.txt", "r");
    //printf("ReadLastSigma %lf", ReadLastSigma());
    fscanf(fptr, "%lf\n", &m);
/*    if(time > 1.) {
        printf("entered while zone\n");
        FILE *f_time_ptr = fopen("/home/fran/Documents/modelica/time_powerdevs.txt", "r");
        double power_devs_time = 0;
        fscanf(f_time_ptr, "%lf\n", &power_devs_time);
        while(time > power_devs_time){
            printf("waiting!!!!\n");
            sleep(1);
            fscanf(f_time_ptr, "%lf\n", &power_devs_time);
            printf("power devs time %lf\n", power_devs_time);
        }
        fclose(f_time_ptr);
    }
   */
//    while(i != EOF){
//        printf("n=%f, m=%f,  c=%c, i=%f\n", n, m, c, i);
//        i = fscanf(fptr, "%lf %c %lf\n", &n, &c, &m);
//        if(n >= ln)
//            break;
//    }
    fclose(fptr);
//    WriteLastSigma(n);
    return m;
}

double WriteLastValue(double value)
{
    printf("WriteLastValue %lf\n", value);
    FILE *fptr = fopen("/home/fran/Documents/modelica/output.txt", "w");
    //sleep(1);
//    double sigma = ReadLastSigma();
    fprintf(fptr, "%lf\n", value);
    fclose(fptr);
    return 1.0;
}
