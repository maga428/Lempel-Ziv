/*
2019/08/07
Lempel_Ziv complexity
Lempel-Ziv_Complexity.c
*/
#include"Lempel-Ziv_C.h"

//Read Array data.
void Array_Read(int *array, char *filename, int *array_length){
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
    *array_length = co;
    // printf("count = %d\n",co);
    fclose(fp);
    return;
}
void Array_Read_TEST(void){

    char *fn = "test.txt";
    int array[20];
    int array_length = 0;
    Array_Read(array,fn,&array_length);
    for(int i = 0; i < 20; i++){
        if(i != 0){printf(" ");}
        printf("%d",array[i]);
    }
    printf("\n");
}

//LZ function

