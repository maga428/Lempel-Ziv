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
//listの追加
void mk_list(struct node *index, char *word, int length){
    if(index->child_p == NULL){
        index->child_p = make_list(word, length);
    }else if(index->child_p != NULL){
        mk_list(index->child_p, word, length);
    }
    return;
}
struct node *make_list(char *word, int length){
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    strcpy(new_node->sub_word,word);
    new_node->sub_word_length = length;
    new_node->child_p = NULL;
    return new_node;
}
//listの検索
void Search_list(struct node *no, int *flag, char *array, int curent_p, int curent_v){
    if(*(flag) == 0) return;
    if(no->child_p != NULL){
        Search_list(no->child_p, flag, array, curent_p, curent_v);
    }
    if(no->sub_word_length == curent_v){
        if(strncmp(&array[curent_p], no->sub_word, curent_v) == 0){
            *(flag) = 0;
        }
    }
    return;
}
//index list の表示
void Show_list(struct node *index){
    int co = 0;
    printf("Sub word:");
    while(index->sub_word[co] != '\n'){
        printf("%c",index->sub_word[co]);
        co++;
    }
    printf("\tlength:%d\n",index->sub_word_length);
    if(index->child_p != NULL){
        Show_list(index->child_p);
    }
    return;
}
//free list メモリの開放
void Free_list(struct node *index){
    if(index->child_p != NULL){ 
        Free_list(index->child_p); 
    }
    free(index);
    return;
}
//output index to a text file.
void Op_index(struct node *index, FILE *fp){
    int co = 0;
    fprintf(fp,"Sub word: ");
    while(index->sub_word[co] != '\n'){
        // if(co != 0){
        //     fprintf(fp,",");
        // }
        fprintf(fp,"%c",index->sub_word[co]);//一文字ずつ表示
        co++;
    }
    fprintf(fp,"\n");
    // fprintf(fp,"length:%d,\n",index->sub_word_length);
    if(index->child_p != NULL){
        Op_index(index->child_p,fp);
    }
    return;
}
void Output_index(struct node *index, char *f_name, int c){
    char f_n[62];
    sprintf(f_n,".\\Index\\Index_%s",f_name);
    FILE *fp = fopen(f_n,"w");
    if(fp == NULL){
        printf("F:Output_index() file can not open.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp,"Complexity = %d\n",c);
    Op_index(index,fp); //list output.
    fclose(fp);
}

//LZ78 main 
int LZ78_Complexity(char *array, char *filename){
    /* var */
    int n = ARRAY_LENGTH; //Length of array.
    int p = 1; //Pointer 現在見ている文字列の始点
    int v = 1; //Pointer 現在見ている文字列の終点
    int C = 1; //Complexity 複雑度 高いほどランダム性が高い.
    int flag = 1;
    char sub_word[ARRAY_LENGTH];

    struct node index; 
    /*Prefix index is set*/
    strncpy(index.sub_word,array,1);
    index.sub_word[1] = '\n';
    index.sub_word_length = 1;
    index.child_p = NULL;

    /*LZ Complexity calculat start.*/
    while(p < n){
        flag = 1;
        v = 1;
        while(flag && p < n){
            Search_list(&index, &flag, array, p, v); //list search. indexに同じWordがあったらvを加算してもう一度search.
            //printf("p = %d_v = %d\n",p,v);
            if(flag == 0){
                flag = 1;
                v++;
            }else if(flag == 1){//indexに登録されていないWordを追加してbreak.
                strncpy(sub_word, array + p, v );
                sub_word[v] = '\n';
                mk_list(&index, sub_word, v);
                p += v;
                v = 0;
                C++;
                break;
            }
        }
        if(p+v > n) break;
    }
    //Show_list(&index);
    Output_index(&index,filename,C);
    Free_list(&index);
    return C;
}
void LZ78_Complexity_TEST(){
    char *f_name = "test_column.txt";
    char array[ARRAY_LENGTH];
    int array_length = 0;
    Array_Read_column(array,f_name,&array_length);
    printf("Target : %s\n",array);
    int C = LZ78_Complexity(array,f_name);
    printf("C = %d\n",C);
    return;
}


//
int Rondom_Cequence_test(void){
    char array[ARRAY_LENGTH];
    char F_name[20];
    int C = 0;
    
    FILE *fp = fopen("Random_C.csv","w");
    if(fp == NULL){printf("File can not opened.\n"); exit(EXIT_FAILURE); }
    fprintf(fp,"No.,C\n");
    for(int i = 0; i < RONDOM_SEQUENCE_NUM; i++){
        sprintf(F_name,"%d.txt", i+1);
        for(int i = 0; i < ARRAY_LENGTH; i++){
            int r = genrand_int32() % 3;
            sprintf(&array[i],"%d",r);
            // if(r == 0){
            //     // snprintf(&array[i],1, "%d", 0);
            //     array[i] = '0';
            // }else if(r == 1){
            //     // snprintf(&array[i],1, "%d", 1);
            //     array[i] = '1';
            // }else if(r == 2){
            //     // sprintf(&array[i], "%d", 2);
            //     array[i] = '2';
            // }
            // printf("%c",array[i]);
        }
        // printf("\n");
        printf("%s\n",array);
        C = LZ78_Complexity(array,F_name);
        fprintf(fp, "%d,%d\n",i+1,C);
    }
    fclose(fp);

    printf("END\n");
    return EXIT_SUCCESS;
}
int Human_C(void){
    FILE *A_fp, *C_fp;
    char array[ARRAY_LENGTH];
    char index[24];
    int C[492];
    int co = 1;

    for(int i = 0; i < 492; i++){
        C[i] = -1;
    }

    /*file open */
    //hand data read
    A_fp = fopen("HandData_column.txt","r");
    if(A_fp == NULL){printf("HandData_column.txt can not read.\n"); exit(EXIT_FAILURE);}
    /*---*/
    
    while(fscanf(A_fp,"%s",array) != EOF){  //array read.
        printf("No.%d : %s\n",co,array);
        sprintf(index,"%d",co);  //index file name set.
        C[co-1] = LZ78_Complexity(array,index);   //col Complexity.
        printf("C = %d\n",C[co-1]);
        //fprintf(C_fp,"%d,%d\n",co,C);    //output complexity.
        co++;
    }

    fclose(A_fp);

    C_fp = fopen("Human_C.csv","w");
    if(C_fp == NULL){printf("Human_C.txt can not opened.\n"); exit(EXIT_FAILURE);}
    fprintf(C_fp,"No.,C\n");
    for(int i = 0; i < 492; i++){
        fprintf(C_fp,"%d,%d\n",i+1,C[i]);
    }
    fclose(C_fp);
    return EXIT_SUCCESS;
}





/*
__MT__
Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.
*/
void init_genrand(unsigned long s){
	mt[0] = s & 0xffffffffUL;
	for (mti = 1; mti<MT_N; mti++) {
		mt[mti] =
			(1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		mt[mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
}

unsigned long genrand_int32(void)
{
	unsigned long y;
	static unsigned long mag01[2] = { 0x0UL, MATRIX_A };
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= MT_N) { /* generate N words at one time */
		int kk;

		if (mti == MT_N + 1)   /* if init_genrand() has not been called, */
			init_genrand(5489UL); /* a default initial seed is used */

		for (kk = 0; kk<MT_N - MT_M; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + MT_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (; kk<MT_N - 1; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + (MT_M - MT_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[MT_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[MT_N - 1] = mt[MT_M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}
/* MT */