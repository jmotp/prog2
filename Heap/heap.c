/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

heap* heap_nova(int capacidade)
{
	heap *h = malloc(sizeof(heap));
  	if(h==NULL) return NULL;
  	h->tamanho=0;
  	h->capacidade=capacidade;
  	h->elementos=malloc((capacidade+1)*sizeof(elemento*));
  	if(h->elementos==NULL){
    	free(h);
    	return NULL;
  	}
 	return h;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
	if(h == NULL ) return (int)NULL;
  	if(h->tamanho+1>h->capacidade)return 0;
	h->tamanho++;
	elemento * new=malloc(sizeof(elemento));
	new->prioridade=prioridade;
	new->valor = malloc((strlen(texto)+1)*sizeof(char));
	strcpy(new->valor,texto);
	//printf("%s %d\n",new->valor,new->prioridade);
	int i;
	for(i = h->tamanho; (i>1) && h->elementos[i/2]->prioridade > new->prioridade;i/=2){
		h->elementos[i] = h->elementos[i/2];
	}
	
	h->elementos[i]=new;
  	return 1;
}

void heap_apaga(heap *h)
{
	for(int i = 0; i < h->tamanho;i++){
		free(h->elementos[i]->valor);
		free(h->elementos[i]);
	}
	free(h);
	
  return;
}

char* heap_remove(heap * h)
{
  return NULL;
}

heap* heap_constroi(elemento* v, int n_elementos)
{
	heap * h = heap_nova(n_elementos);
	for(int i = 0 ; i < n_elementos;i++){
		heap_insere(h,v[i].valor,v[i].prioridade);
	}
  return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
  return -1;
}

void mostraHeap(heap *h, int indice)
{
  int i, nivel = 0;
  
  if (indice <= h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }
    
    mostraHeap(h, indice*2);
    
    for(i = 0; i < 3 * nivel; i++)
      printf("     ");
    
    printf("%s (%d)\n",h->elementos[indice]->valor, h->elementos[indice]->prioridade);
    
    mostraHeap(h, indice*2+1);
  }
}