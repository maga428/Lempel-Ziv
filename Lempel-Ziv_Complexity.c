/*
2019/08/07
Lempel_Ziv complexity
Lempel-Ziv_Complexity.c
*/
#include"Lempel-Ziv_C.h"

//Read Array data : low file.
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
//Read Array data : column file.
void Array_Read_column(char *array, char *filename, int *array_length){
    FILE *fp = fopen(filename,"r");
    //array file is read.
    if(fp == NULL){
        printf("F:column  Array file cannot open!\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%s",array);
    *array_length = sizeof array /sizeof array[0];
    fclose(fp);
}
void Array_Read__column_TEST(void){
    char *f_name = "test_column.txt";
    char array[32];
    int array_length = 0;
    Array_Read_column(array,f_name,&array_length);
    printf("%s\n",array);
}

//LZ function
int LZ_Complexity(char *array){
    //make index.txt
    int n = sizeof array / sizeof array[0];
    int p = 0; //Pointer
    int C = 1; //Complexity
    int u = 1; //Length of current prefix.
    int v = 1; //Length of the current component for current p
    int vmax = v; //Final length used for the current component.

    while(u + v < n){
        if(array[p+v] == array[u+v]){
            v++;
        }else{
            if(vmax < v) vmax = v;
            p++;
            if(p == u){
                C++;
                u += vmax;
                p = 0;
                vmax = v;
            }else{
                v = 1;
            }
        }
    }
    if(v != 1){
        C += 1;
    }
    return C;
}

