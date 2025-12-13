#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int global_num_of_points; /*global variables for total number of points*/
int global_dim; /*global variables for total dimansion of points*/

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

int find_string_length(char *s) {
    int c = 0;
    while (*s++) {
    c++;
    }
    return c;
}
int is_digit(char *str){
    int i, len = find_string_length(str);
    for (i = 0 ; i < len ; i++){
        if (!('0' <= str[i] && str[i] <=  '9')) return 0;
    }
    return 1;
}

void print_centroids(int k, int dim, double **centroids){
    int i,j;
    for (i = 0; i < k; i++){
        for (j = 0; j < dim; j++){
            if (j == dim - 1) printf("%.4f", centroids[i][j]);
            else printf("%.4f,", centroids[i][j]);
        }
        printf("\n");
    }
}

double *update_centroid(int length_of_cluster, int dim, double **cluster){
    double *updated_centroid = malloc(sizeof(double) * dim);
    int i,j;
    double sum;
    if (updated_centroid == NULL){
        return NULL;
    }

    for (i = 0; i < dim ; ++i){
        sum = 0.0;
        for (j = 0 ; j < length_of_cluster ; ++j){
            sum+= cluster[j][i];
        }
        updated_centroid[i] = sum/length_of_cluster;
    }
    return updated_centroid;
}

double calculate_distance(double p[], double q[], int n){
    double sum = 0.0;
    int i;
    for (i = 0; i < n; i++){
        sum += (p[i] - q[i]) * (p[i] - q[i]);
    }
    return sqrt(sum);
}

struct vector *read_points(void){
    struct vector *head_vec, *curr_vec;
    struct cord *head_cord, *curr_cord;
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
    int i,j,k;
    double **points_arr;
    struct vector *curr_point,*points,*temp_point;
    struct cord *curr_cord,*temp_cord;

    points = read_points();
    if (points == NULL || points->cords == NULL) {
        return NULL;
    }

    dim = count_dimensions(points->cords);
    num_of_points = count_points(points);

    global_dim = dim;
    global_num_of_points = num_of_points;

    points_arr = malloc(num_of_points * sizeof(double *));
    if (!points_arr) {
        return NULL; /* allocation failed */
    }

    for ( i = 0; i < num_of_points; i++){
        points_arr[i] = malloc(dim * sizeof(double));
        if (!points_arr[i]) {
            /* handle partial failure: free previous rows */
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



int find_closest_cluster(double **centroids, double *point ,int cluster_num, int dim){
    int i, distance, temp_distance, closest_cluster_index = 0;
    distance = calculate_distance(point, centroids[0], dim);
    for (i = 1; i < cluster_num ; i++) {
        temp_distance = calculate_distance(centroids[i], point,dim);
        if (temp_distance < distance) {
            distance = temp_distance;
            closest_cluster_index = i;
        }
    }
    return closest_cluster_index;
}

int *count_cluster_points(int k , double **centroids ,double **points, int dim, int num_of_points){
    int *counter_arr = calloc (k, sizeof(int));
    int i, curr = 0;
    if (!counter_arr) {
        return NULL;
    }
    for (i = 0; i < num_of_points; i++) {
        curr = find_closest_cluster(centroids, points[i], k , dim);
        counter_arr[curr] += 1 ;
    }
    return counter_arr;
}





void cluster_handle(int k, int iter, int num_of_points, int dim, double **points){
    int i,j,l, curr,convergence;
    int *counter_arr, *counter_arr_copy;
    double **centroids, **updated_centroids, ***clusters;
    clusters = malloc(sizeof(double **)*k);
    if (!clusters) {
        return;
    }
    centroids = malloc(sizeof(double) * k);
    if (!centroids) {
        return;
    }
    updated_centroids = malloc(sizeof(double) * k);
    if (!updated_centroids) {
        return;
    }
    counter_arr_copy = calloc(k, sizeof(int)); /*we need another counter array in order to update the centroids */
    if (!counter_arr_copy) {
        return;
    }
    for(i = 0; i < k; i++){
        centroids[i] = points[i];
    }

    for (i = 0; i < iter; i++){
        counter_arr = count_cluster_points(k, centroids, points, dim, num_of_points);
        for (j = 0; j < k; j++){
            clusters[j] = malloc(sizeof(double *) * counter_arr[j]);
            if (!clusters[j]) {
                free(centroids);
                free(counter_arr);
                return;
            }
        }
        for (j = 0; j < num_of_points; j++){
            curr = find_closest_cluster(centroids, points[j], k , dim);
            clusters[curr][counter_arr[curr]-1] = points[j];
            counter_arr[curr]--;
            counter_arr_copy[curr]++; /* this is instead of having its own loop, probably more efficien this way */
        }
        convergence = 1;
        for (j = 0 ; j < k ; j++){
            updated_centroids[j] = update_centroid(counter_arr_copy[j], dim, clusters[j]);
            for (l=0; l < dim; l++){
                if(fabs(centroids[j][l] - updated_centroids[j][l]) >= 0.001){
                    convergence = 0;
                }
            }
            centroids[j] = updated_centroids[j];
        }
        if (convergence == 1) break;
    }
    print_centroids(k,dim,centroids);
    free(counter_arr_copy);
    free(updated_centroids);
    free(counter_arr);
    free(centroids);
}




int main(int argc, char *argv[]){
    int k,iter;
    double **points;
    if (!is_digit(argv[1])){
        printf("Incorrect number of clusters!");
        return 0;
    }
    k = atoi(argv[1]);
    printf("%d", argc);
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
    }
    printf("%d", iter);
    points = parse_points();
    cluster_handle(k, iter, global_num_of_points, global_dim , points);
    free(points);
    return 0;
}

