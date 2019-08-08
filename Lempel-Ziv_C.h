/*
2019/08/07
Lempel_Ziv complexity
Lempel-Ziv_C.h
*/
#include<stdio.h>
#include<stdlib.h>

/*Macro*/
#define ARRAY_LENGTH 16

/*Func*/
//file read.
void Array_Read(int *array, char *filename, int *array_length);
void Array_Read_TEST(void);
void Array_Read_column(char *array, char *filename, int *array_length);
void Array_Read__column_TEST(void);

//LZ77
int LZ77_Complexity(char *array);
void LZ77_Complexity_TEST(void);

//LZ78
int LZ78_Complexity(char *array, char *filename);
void LZ78_Complexity_TEST(void);