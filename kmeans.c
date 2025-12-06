#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

int is_digit(char *str){
    int i, len = strlen(str);
    for (i = 0 ; i < len ; i++){
        if (!('0' <= str[i] && str[i] <=  '9')) return 0;
    }
    return 1;
}

double calculateDistance(double p[], double q[], int n){
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < n; ++i){
        sum += (p[i]-q[i])*(p[i]-q[i]);
    }
    return sqrt(sum);
}
struct vector *read_points(void){
    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols;
    double n;
    char c;

    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;


    while (scanf("%lf%c", &n, &c) == 2)
    {

        if (c == '\n')
        {
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }

    return head_vec;
}

double **parse_points(){
    struct vector *points = read_points();

}

int main(int argc, char *argv[]){
    int k,iter;

    if (!is_digit(argv[1])){
        printf("Incorrect number of clusters!");
        return 0;
    }
    k = atoi(argv[1]);
    if (argc <= 3){
        if (!is_digit(argv[2])){
            printf("Incorrect maximum iteration!");
            return 0;
        }
    iter = atoi(argv[2]);
    if(iter < 2 || iter > 799){
        printf("Incorrect maximum iteration!");
        return 0;
    }

    return 0;
}

