/*
2019/08/07
Lempel_Ziv complexity
Lempel-Ziv_Complexity.c
*/
#include"Lempel-Ziv_C.h"

void Array_Read(int *array, char *filename){
    FILE *fp = fopen(filename,"r");
    int e = 0; //array element recode.
    int co = 0; //counter.
    //array file is read.
    if(fp == NULL){
        printf("Array file cannot open!\n");
        exit(EXIT_FAILURE);
    }
    
    while(fscanf(fp,"%d",&e) != EOF){
        array[co] = e;
        co++;
    }
    // printf("count = %d\n",co);
    fclose(fp);
    return;
}