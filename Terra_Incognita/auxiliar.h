/* Biblioteca de funções auxiliares
/* Trabalho 3 de Programação 2017/2018
/* Copyright João Pinheiro e Diogo Oliveira
/* 1MIEEC07 - FEUP */ 

typedef struct _elemento_pilha{
    struct _elemento_pilha * next;
    int x;
    int y;
    char terreno;
}elemento_pilha;

typedef struct _pilha{
    elemento_pilha * top;
    int tamanho;
}pilha;


pilha * cria_pilha();

int insere_elemento(pilha * p,int x , int y, char terreno);

int pop_elemento(pilha * p);

void del_pilha(pilha * p);

void print_pilha(pilha * p);


