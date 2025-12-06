#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>

int is_digit(char *str){
    int i, len = strlen(str);
    for (i = 0 ; i < len ; i++){
        if (!('0' <= str[i] && str[i] <=  '9')) return 0;
    }
    return 1;
}



int main(int argc, char *argv[]){
    int k,iter;
    char *k_temp,*iter_temp;
    k_temp = argv[1];
    if (!is_digit(k_temp)){
        printf("Incorrect number of clusters!");
        return 0;
    }
    k = k_temp 

    

    return 0;
}









