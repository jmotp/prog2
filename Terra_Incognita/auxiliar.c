#include "auxiliar.h"
#include <stdlib.h>
#include <stdio.h>

/*Criar a pilha*/

pilha * cria_pilha(){
    pilha * nova = (pilha *) malloc(sizeof(pilha));
    nova->top = NULL;
    nova-> tamanho =0;
    return nova;
}

int insere_elemento(pilha * p,int x , int y, char terreno){
    elemento_pilha * elem = (elemento_pilha*) malloc(sizeof(elemento_pilha));
    elem->next = p->top;
    p->tamanho ++ ;
    elem->x = x;
    elem -> y = y;
    elem -> terreno = terreno;
    p->top = elem;
    return 1;
}

int pop_elemento(pilha * p){
    if(p->top == NULL)return 0;
    elemento_pilha * elem = p->top;
    p->top = elem->next;
    free(elem);
    p->tamanho --;
    
    return 1;
}

void del_pilha(pilha * p){
    for(int i = 0;i < p->tamanho;i++){
        pop_elemento(p);
    }
    free(p);
}

void print_pilha(pilha * p){
    elemento_pilha * elem = p->top;
    for( int i = 0 ; i < p->tamanho;i++){
        printf("%d %d %c\n",elem->x,elem->y,elem->terreno);
        elem = elem->next;
    }
}