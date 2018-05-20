/*****************************************************************/
/*         Tabela de Dispersao | PROG2 | MIEEC | 2017/18         */
/*****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "tabdispersao.h"

tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc)
{
    /* aloca memoria para a estrutura tabela_dispersao */
    if (hfunc == NULL)
        return NULL;

    tabela_dispersao *t = (tabela_dispersao*) malloc(sizeof (tabela_dispersao));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elemento **) calloc(tamanho, sizeof (elemento*));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;
    t->hfunc = hfunc;
    return t;
}

void tabela_apaga(tabela_dispersao *td)
{
    int i;
    elemento *elem, *aux;

    if (td == NULL) return;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];
        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            free(elem->obj);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);
}

int tabela_adiciona(tabela_dispersao *td, int *chave,  char valor)
{
    int index;
    elemento * elem;

    if (!td ) return TABDISPERSAO_ERRO;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(chave, td->tamanho);
    //printf("Index ->%d\n",index);
    /* verifica se chave ja' existe na lista */
    elem = td->elementos[index];
    while (elem != NULL && (elem->obj->chave[0]!= chave[0] || elem->obj->chave[1]!=chave[1]))
        elem = elem->proximo;

    if (elem == NULL)
    {
        /* novo elemento, chave nao existe na lista */

        /* aloca memoria para o elemento */
        elem = (elemento*) malloc(sizeof (elemento));
        if (elem == NULL)
            return TABDISPERSAO_ERRO;

        /* aloca memoria para o valoreto */
        elem->obj = (objeto*) malloc(sizeof (objeto));
        if (elem->obj == NULL)
            return TABDISPERSAO_ERRO;

        /*copia chave e valor */
        elem->obj->chave[0]=chave[0];
        elem->obj->chave[1]=chave[1];
        
        elem->obj->valor= valor;

        /* insere no inicio da lista */
        elem->proximo = td->elementos[index];
        td->elementos[index] = elem;
    } else {
        /* chave repetida, simplesmente atualiza o valor */
        elem->obj->valor=valor;
    }

    return TABDISPERSAO_OK;
}

int tabela_remove(tabela_dispersao *td, int *chave)
{
    int index;
    elemento * elem, * aux;

    if (!td) return TABDISPERSAO_ERRO;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(chave, td->tamanho);

    elem = td->elementos[index];
    aux = NULL;

    /* para cada elemento na posicao index */
    while(elem != NULL)
    {
        /* se for a string que se procura, e' removida */
        if (elem->obj->chave[0]==chave[0]&&elem->obj->chave[1]==chave[1])
        {
            /* se nao for a primeira da lista */
            if (aux != NULL)
                aux->proximo = elem->proximo;
            else
                td->elementos[index] = elem->proximo;
            free(elem->obj);
            free(elem);

            return TABDISPERSAO_OK;
        }

        aux = elem;
        elem = elem->proximo;
    }
    return TABDISPERSAO_NAOEXISTE;
}

int tabela_existe(tabela_dispersao *td, int * chave)
{
    if (!chave || !td) return TABDISPERSAO_ERRO;

    char c = tabela_valor(td, chave);

    if (c==-1) return TABDISPERSAO_NAOEXISTE;

    return TABDISPERSAO_EXISTE;
}

char tabela_valor(tabela_dispersao *td, int *chave)
{
    
    int pos = td->hfunc(chave,td->tamanho);
    elemento * el = td->elementos[pos];
    while(el!=NULL){
        if(el->obj->chave[0]==chave[0])
            if(el->obj->chave[1]==chave[1])
                return el->obj->valor;
        el=el->proximo;
    }
    return 0;
}

int tabela_esvazia(tabela_dispersao *td)
{
    int i;
    elemento * elem, * aux;

    if (!td) return TABDISPERSAO_ERRO;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* apaga todos os elementos da entrada */
        elem = td->elementos[i];
        while(elem != NULL)
        {
            aux = elem->proximo;
            free(elem->obj);
            free(elem);
            elem = aux;
        }
        td->elementos[i] = NULL;
    }
    return TABDISPERSAO_OK;
}

int tabela_numelementos(tabela_dispersao *td)
{
    int i, count = 0;
    elemento * elem;

    if (!td) return TABDISPERSAO_ERRO;

    /* percorre todos os elementos da tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        elem = td->elementos[i];
        while(elem != NULL)
        {
            elem = elem->proximo;
            count++;
        }
    }
    return count;
}

objeto * tabela_elementos(tabela_dispersao *td, int *n)
{
    objeto *v;
    int i, j;
    elemento * elem;
    objeto * valor;

    *n = tabela_numelementos(td);

    if ((*n) <= 0)
        return NULL;

    v = (objeto*) malloc(sizeof(objeto)*(*n));
    if (!v)
        return NULL;

    for (i=0,j=0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            elem = td->elementos[i];
            while (elem)
            {
                valor = elem->obj;
                v[j++] = *valor;
                elem = elem->proximo;
            }
        }
    }
    return v;
}

unsigned long hash_krm(int* chave, int tamanho)
{
    
    return tamanho;
}

unsigned long hash_djbm(int* chave, int tamanho)
{
    
    int hash = (chave[0] * 137 + chave[1]) % tamanho;
    return hash>0?hash:-hash;
}

/*================================================================================*/
void mostraTabela(tabela_dispersao *td)
{
    int i;
    elemento * elem;
    printf("TABELA DE DISPERSAO (%d elementos)\n", tabela_numelementos(td));
    for (i = 0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            printf("\t[%2d]", i);
            elem = td->elementos[i];
            while (elem)
            {
                printf(" : [\"%d %d\" :: \"%c\"]", elem->obj->chave[0],elem->obj->chave[1], elem->obj->valor);
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}
