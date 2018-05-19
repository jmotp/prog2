#include "auxiliar.h"
#include <stdlib.h>
#include <stdio.h>

/*Criar a table*/

table * cria_table(int size){
    table * nova = (table *) malloc(sizeof(table));
    if (nova==NULL) return NULL;
    nova->tab = calloc(size,sizeof(elemento_table*));
    nova-> tamanho =size;
    return nova;
}

int insere_elemento(table * p,int x , int y, char terreno){
    elemento_table * elem = (elemento_table*) malloc(sizeof(elemento_table));
    elem->coord[0]=x;
    elem->coord[1]=y;
    elem->terreno = terreno;    
}

int pop_elemento(table * p){

}

unsigned long hash_djbm(int* chave,int tamanho)
{
    return chave[0] % tamanho;
}

void del_table(table * p){
    if(p==NULL) return;
    for(int i = 0;i < p->tamanho;i++){
        pop_elemento(p);
    }
    free(p);
}

void print_table(table * p){
    if(p==NULL || p->top==NULL) return;
    elemento_table * elem = p->top;
    for( int i = 0 ; i < p->tamanho;i++){
        printf("%d %d %c\n",elem->x,elem->y,elem->terreno);
        elem = elem->next;
    }
}