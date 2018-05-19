/* Biblioteca de funções auxiliares */
/* Trabalho 3 de Programação 2017/2018 */
/* Copyright João Pinheiro e Diogo Oliveira */
/* 1MIEEC07 - FEUP */ 

typedef struct _elemento_table{
    struct _elemento_table * next;
    int coord[2];
    char terreno;
}elemento_table;

typedef struct _table{
    elemento_table ** tab;
    int tamanho;
}table;


table * cria_table();

int insere_elemento(table * p,int x , int y, char terreno);

int pop_elemento(table * p);

void del_table(table * p);

void print_table(table * p);


