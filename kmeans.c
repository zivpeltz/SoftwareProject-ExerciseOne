#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculateDistance(double p[], double q[], int n){
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < n; ++i){
        sum += (p[i]-q[i])*(p[i]-q[i]);
    }
    return sqrt(sum);
}

int main(void ){
    double p[] = {3.0, 4.0};
    double q[] = {0.0, 0.0};
    int n = sizeof(p) / sizeof(p[0]);
    printf("%f", calculateDistance(p,q,n));
}