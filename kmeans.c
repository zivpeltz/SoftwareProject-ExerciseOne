#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_distance(double p[], double q[], int n){
    double sum = 0.0;
    for (int i = 0; i < n; i++){
        sum += (p[i] - q[i]) * (p[i] - q[i]);
    }
    return sqrt(sum);
}

void print_centroids(int k, int dim, double m[k][dim]){
    for (int i = 0; i < k; i++){
        for (int j = 0; j < dim; j++){
            if (j == dim - 1) printf("%.4f", m[i][j]);
            else printf("%.4f,", m[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    double p[] = {3.0, 4.0};
    double q[] = {0.0, 0.0};
    double m[2][2] = {
        { p[0], p[1] },
        { q[0], q[1] }
    };

    int n = sizeof(p) / sizeof(p[0]);
    printf("%f\n", calculate_distance(p, q, n));
    print_centroids(2, 2, m);
}