/*
2019/08/07
Lempel_Ziv complexity
Lempel-Ziv_C.h
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*Macro*/
#define ARRAY_LENGTH 50
#define RONDOM_SEQUENCE_NUM 1000

/*Func*/
//file read.
void Array_Read(int *array, char *filename, int *array_length);
void Array_Read_TEST(void);
void Array_Read_column(char *array, char *filename, int *array_length);
void Array_Read__column_TEST(void);

/* LZ77 */
int LZ77_Complexity(char *array);
void LZ77_Complexity_TEST(void);

/* LZ78 */
struct node{
    char sub_word[100];
    int sub_word_length;
    struct node *child_p;
};

//make list function.
void mk_list(struct node *index, char *word, int length); 
struct node *make_list(char *word, int length);
//index serch.
void Search_list(struct node *no, int *flag, char *array, int curent_p, int curent_v);
// << index list の表示
void Show_list(struct node *index);
//free list メモリの開放
void Free_list(struct node *index);

//output index to a text file.
void Op_index(struct node *index, FILE *fp);
void Output_index(struct node *index, char *f_name, int c);

//LZ78 main
int LZ78_Complexity(char *array, char *filename);
void LZ78_Complexity_TEST(void);

//Random Sequences test
int Rondom_Cequence_test(void);
int Human_C(void);


/*MT*/
#define MT_N 624
#define MT_M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[MT_N]; /* the array for the state vector  */
static int mti = MT_N + 1; /* mti==MT_N+1 means mt[MT_N] is not initialized */
void init_genrand(unsigned long s);
unsigned long genrand_int32(void);
/*MT*/