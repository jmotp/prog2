#include "auxiliar.h"
#include <stdlib.h>
#include <stdio.h>

/*Criar a pilha*/

pilha * cria_pilha(){
    pilha * nova = (pilha *) malloc(sizeof(pilha));
    if (nova==NULL) return NULL;
    nova->top = NULL;
    nova-> tamanho =0;
    return nova;
}

int insere_elemento(pilha * p,int x , int y, char terreno){
    elemento_pilha * elem = (elemento_pilha*) malloc(sizeof(elemento_pilha));
    if (elem==NULL || p==NULL) return 0;
    elem->next = p->top;
    p->tamanho ++ ;
    elem->x = x;
    elem -> y = y;
    elem -> terreno = terreno;
    p->top = elem;
    return 1;
}

int pop_elemento(pilha * p){
    if(p==NULL || p->top == NULL || p->tamanho==0) return 0;
    elemento_pilha * elem = p->top;
    p->top = elem->next;
    free(elem);
    p->tamanho --;
    
    return 1;
}

void del_pilha(pilha * p){
    if(p==NULL) return;
    for(int i = 0;i < p->tamanho;i++){
        pop_elemento(p);
    }
    free(p);
}

void print_pilha(pilha * p){
    if(p==NULL || p->top==NULL) return;
    elemento_pilha * elem = p->top;
    for( int i = 0 ; i < p->tamanho;i++){
        printf("%d %d %c\n",elem->x,elem->y,elem->terreno);
        elem = elem->next;
    }
}