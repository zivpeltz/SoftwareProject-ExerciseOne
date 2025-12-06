#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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

void print_centroids(int k, int dim, double m[k][dim]){
    for (int i = 0; i < k; i++){
        for (int j = 0; j < dim; j++){
            if (j == dim - 1) printf("%.4f", m[i][j]);
            else printf("%.4f,", m[i][j]);
        }
        printf("\n");
    }
}

double calculate_distance(double p[], double q[], int n){
    double sum = 0.0;
    for (int i = 0; i < n; i++){
        sum += (p[i] - q[i]) * (p[i] - q[i]);
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

int count_dimensions(struct cord *v){
    int count = 0;
    while (v != NULL) {
        count++;
        v = v->next;
    }
    return count;
}

int count_points(struct vector *v){
    int count = 0;
    while (v != NULL) {
        count++;
        v = v->next;
    }
    return count;
}



double **parse_points(){
    int dim,num_of_points;
    int i,j;
    double **points_arr;
    struct vector *curr_point,*points,*temp_point;
    struct cord *curr_cord,*temp_cord;

    points = read_points();
    points = read_points();
    if (points == NULL || points->cords == NULL) {
        return NULL;
    }

    dim = count_dimensions(points->cords);
    num_of_points = count_points(points);

    points_arr = malloc(num_of_points * sizeof(double *));
    if (!points_arr) {
        return NULL; // allocation failed
    }

    for ( i = 0; i < num_of_points; i++){
        points_arr[i] = malloc(dim * sizeof(double));
        if (!points_arr[i]) {
            // handle partial failure: free previous rows
            int k;
            for (k = 0; k < i; k++) {
                free(points_arr[k]);
            }
            free(points_arr);
            return NULL;
        }
    }

    curr_point = points;
    for (i = 0; i < num_of_points; i++){
        temp_point = curr_point;
        curr_cord = curr_point->cords;
        for (j = 0; j < dim; j++){
            points_arr[i][j] = curr_cord->value;
            temp_cord = curr_cord;
            curr_cord = curr_cord->next;
            free(temp_cord);
        }
        curr_point = curr_point->next;
        free(temp_point);
    }
    return points_arr;
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


