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
            if(flag == 0){
                flag = 1;
                v++;
            }else if(flag == 1){//indexに登録されていないWordを追加してbreak.
                strncpy(sub_word, array + p, v );
                sub_word[v] = '\n';
                mk_list(&index, sub_word, v);
                p += v;
                C++;
                break;
            }
        }
    }
    Show_list(&index);
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