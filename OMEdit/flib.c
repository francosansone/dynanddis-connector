#include "flib.h"
#include <stdlib.h>
#include <stdio.h>

double WriteLastSigma(double sigma) {
    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "w");
    fprintf(fptr, "%lf", sigma);
    fclose(fptr);
}

double ReadLastSigma() {
    double value;
    FILE *fptr = fopen("/home/fran/Documents/modelica/lastsigma.txt", "r");
    fscanf(fptr, "%lf\n", &value);
    printf("Read last sigma %lf\n", value);
    return value;
}

double ReadLastValue(double ln){
    printf("Read last value baby\n");
    double n, m, i;
    char c;
    double counter = 0;
    FILE *fptr;
    fptr = fopen("/home/fran/Documents/modelica/output.txt", "r");
    printf("ReadLastSigma %lf", ReadLastSigma());
    i = fscanf(fptr, "%lf %c %lf\n", &n, &c, &m);
    while(i != EOF){
        printf("n=%f, m=%f,  c=%c, i=%f\n", n, m, c, i);
        i = fscanf(fptr, "%lf %c %lf\n", &n, &c, &m);
        if(n >= ln)
            break;
    }
    fclose(fptr);
    WriteLastSigma(n);
    return m;
}

double WriteLastValue(double value){
    FILE *fptr = fopen("/home/fran/Documents/modelica/output.txt", "a");
    double sigma = ReadLastSigma();
    fprintf(fptr, "%lf, %lf\n", sigma + 1.0, value);
    fclose(fptr);
    return sigma + 1.0;
}
