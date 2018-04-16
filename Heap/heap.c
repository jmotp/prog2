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
	if(capacidade<0) return NULL;
	
	heap *h = malloc(sizeof(heap));
 	if(h==NULL) return NULL;
 	h->tamanho=0;
 	h->capacidade=capacidade;
 	h->elementos=calloc(capacidade+1,sizeof(elemento*));
 	if(h->elementos==NULL){
   		free(h);
   		return NULL;
 	}
 	return h;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
	if(h == NULL || texto==NULL ) return (int)NULL;
  	if(h->tamanho+1>h->capacidade) return 0;
	h->tamanho++;
	elemento * new=calloc(1,sizeof(elemento));
	new->prioridade=prioridade;
	new->valor = calloc((strlen(texto)+1),sizeof(char));
	strcpy(new->valor,texto);
	//printf("%s %d\n",new->valor,new->prioridade);
	int i;
	for(i = h->tamanho; (i>1) && h->elementos[i/2]->prioridade > new->prioridade;i = i/2){
		h->elementos[i] = h->elementos[i/2];
	}
	
	h->elementos[i]=new;
  	return 1;
}

void heap_apaga(heap *h)
{
	if(h==NULL) return;

	for(int i = 0; i <=h->tamanho;i++){
		if(i!=0)free(h->elementos[i]->valor);
		free(h->elementos[i]);
	}
	free(h->elementos);
	free(h);
	
  return;
}

char* heap_remove(heap * h)
{
	if(h==NULL || h->tamanho==0) return NULL;

	char *save = h->elementos[1]->valor;

	free(h->elementos[1]);

	if(h->tamanho==1){
		h->tamanho=0;
		return save;
	}

	int i = 1;
	while(i*2<=h->tamanho){
		
		if(i*2==h->tamanho){
			if(h->elementos[i*2]->prioridade < h->elementos[h->tamanho]->prioridade){
				h->elementos[i]=h->elementos[i*2];
				i*=2;
			}
			break;
		}
		else if(h->elementos[i*2]->prioridade < h->elementos[h->tamanho]->prioridade || h->elementos[i*2+1]->prioridade < h->elementos[h->tamanho]->prioridade){
			if(h->elementos[i*2+1]->prioridade < h->elementos[i*2]->prioridade){
				h->elementos[i]=h->elementos[i*2+1];
				i=i*2+1;
			}
			else{
				h->elementos[i]=h->elementos[i*2];
				i*=2;
			}
		}
		else break;
	}

	h->elementos[i]=h->elementos[h->tamanho];

	h->tamanho--;
	return save;
}

heap* heap_constroi(elemento* v, int n_elementos)
{
	if(v==NULL || n_elementos <0) return NULL;

	heap * h = heap_nova(n_elementos);
	for(int i = 0 ; i < n_elementos;i++){
		if(heap_insere(h,v[i].valor,v[i].prioridade)==0) return NULL;
	}
  return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
	if(h==NULL || h->tamanho<=0 || indice<1 || indice > h->tamanho) return -1;

	int i=indice;
	elemento *tmp=h->elementos[indice];
	tmp->prioridade=nova_prioridade;
	
	if(h->elementos[indice]->prioridade < h->elementos[indice/2]->prioridade){
		
		for(i = indice; (i>1) && h->elementos[i/2]->prioridade > nova_prioridade;i = i/2){
			h->elementos[i] = h->elementos[i/2];
		} 
		
		h->elementos[i]=tmp;
	}	

	else if (h->elementos[indice]->prioridade > h->elementos[indice/2]->prioridade){

		for(i=indice; i*2+1<=h->tamanho || i*2==h->tamanho;){
			
			if(nova_prioridade < h->elementos[i*2]->prioridade){
				if(i*2==h->tamanho) break;
				else if (nova_prioridade < h->elementos[i*2+1]->prioridade) break;
			}

			if(h->elementos[i*2]->prioridade < h->elementos[i*2+1]->prioridade){
				h->elementos[i]=h->elementos[i*2];
				i*=2;
			}
			else {
				h->elementos[i]=h->elementos[i*2+1];
				i=i*2+1;
			}
		}

		h->elementos[i]=tmp;
	}

  return 1;
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