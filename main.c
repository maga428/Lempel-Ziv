/*
2019/08/07
Lempel_Ziv complexity
main.c
*/
#include"Lempel-Ziv_C.h"

int main(void){

    char *fn = "test.txt";
    int array[20];
    Array_Read(array,fn);
    for(int i = 0; i < 20; i++){
        if(i != 0){printf(" ");}
        printf("%d",array[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}