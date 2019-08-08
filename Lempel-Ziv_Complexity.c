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
    char array[20];
    int array_length = 0;
    Array_Read_column(array,f_name,&array_length);
    printf("%s\n",array);
}

//LZ77 function
int LZ77_Complexity(char *array){
    const int n = ARRAY_LENGTH; //Length of array.
    int p = 0; //Pointer
    int C = 1; //Complexity
    int u = 1; //Length of current prefix.
    int v = 1; //Length of the current component for current p
    int vmax = v; //Final length used for the current component.
    //printf("n = %d\n",n);
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
void LZ77_Complexity_TEST(void){
    char *f_name = "test_column.txt";
    char array[ARRAY_LENGTH];
    int array_length = 0;
    Array_Read_column(array,f_name,&array_length);
    printf("%s\n",array);
    int C = LZ77_Complexity(array);
    printf("C = %d\n",C);
}

//LZ78 function
int LZ78_Complexity(char *array, char *filename){
    //make index.txt
    char F_name[124];
    sprintf(F_name,".\\Index\\index_of_%s",filename);
    FILE *index_fp;
    if((index_fp  = fopen(F_name,"w")) == NULL){
        printf("F:LZ78_Complexity index text can not make.\n");
        exit(EXIT_FAILURE);
    }
    int n = ARRAY_LENGTH; //Length of array.
    int p = 1; //Pointer
    int u = 2; //corent pointer.
    int v = 0;
    int C = 0; //Complexity
    char sub_word[ARRAY_LENGTH];
    char index_word[ARRAY_LENGTH];
    int sub_word_len = 1;
    int flag = 0;

    fprintf(index_fp,"%c\n",array[0]);
    fclose(index_fp);
    //printf("%s\n",F_name);
    while(p < n){
        
        if((index_fp = fopen(F_name,"r")) == NULL){ printf("F:LZ78_Complexity index text can not read.\n"); exit(EXIT_FAILURE);}
        while(fscanf(index_fp,"%s",index_word) != EOF){
            flag = 0;
            v = 0;
            for(int i = p, j = 0; i < n ;i++, j++){
                //printf("i = %d\n",i);
                if(index_word[j] == '\0'){
                    v = j;
                    break;
                }
                if(strncmp(&array[i],&index_word[j],1) != 0){
                    printf("array[%d] = %c\nindex[%d] = %c\n",i,array[i],j,index_word[j]);
                    flag = 1;
                    if(v < j) v = j;
                }
            }
            //if(flag == 1) break;
        }
        fclose(index_fp);
        //sub_word is added to index.
        if((index_fp = fopen(F_name,"a")) == NULL){ printf("F:LZ78_Complexity index text can not open.\n"); exit(EXIT_FAILURE);}
        for(int i = p; i <= p+v; i++){
            printf("v = %d\n",v);
            fprintf(index_fp,"%c",array[i]);
        }
        fprintf(index_fp,"\n");
        fclose(index_fp);
        p += v+1;
    }
    
    if((index_fp = fopen(F_name,"r")) == NULL){ printf("F:LZ78_Complexity index text can not read. count index words.\n"); exit(EXIT_FAILURE);}
    while(fscanf(index_fp,"%s",index_word) != EOF){
        printf("%s\n",index_word);
        C++;
    }
    fclose(index_fp);
    return C;
}

void LZ78_Complexity_TEST(){
    char *f_name = "test_column.txt";
    char array[ARRAY_LENGTH];
    int array_length = 0;
    Array_Read_column(array,f_name,&array_length);
    printf("%s\n",array);
    int C = LZ78_Complexity(array,f_name);
    printf("C = %d\n",C);
    return;
}