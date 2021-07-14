#include "flib.h"
#include <stdlib.h>
#include <stdio.h>

double WriteLastSigma(double sigma) {
    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "w");
    fprintf(fptr, "%lf", sigma);
    fclose(fptr);
}

double ReadLastSigma() {
    printf("****ReadLastSigma\n");
    double value;
    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "r");
    fscanf(fptr, "%lf\n", &value);
    printf("Read last sigma %lf\n", value);
    return value;
}

double ReadLastValue(double a){
    double m;
    int readed;
    char c;
    double counter = 0;
    FILE *fptr;
    fptr = fopen("/home/fran/Documents/modelica/input.txt", "r");
    //printf("ReadLastSigma %lf", ReadLastSigma());
    readed = fscanf(fptr, "%lf\n", &m);
//    while(i != EOF){
//        printf("n=%f, m=%f,  c=%c, i=%f\n", n, m, c, i);
//        i = fscanf(fptr, "%lf %c %lf\n", &n, &c, &m);
//        if(n >= ln)
//            break;
//    }
    fclose(fptr);
//    WriteLastSigma(n);
    printf("ReadLastValue %lf\n", m);
    return m;
}

double WriteLastValue(double value){
    printf("WriteLastValue %lf\n", value);
    FILE *fptr = fopen("/home/fran/Documents/modelica/output.txt", "w");
//    double sigma = ReadLastSigma();
    fprintf(fptr, "%lf\n", value);
    fclose(fptr);
    return 1.0;
}
