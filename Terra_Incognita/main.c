#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "auxiliar.h"

char ** mapa;


int mapa_pos(int x, int y)
{
    /* devolve tipo de terreno na posicao x,y */
    if(mapa[x][y]<0||mapa[x][y]>4) return TERRA_INCOGNITA;
    return mapa[x][y];
}


int main(int argc, char *argv[])
{
      int nExplorador;
      int positio[1000][2];
    /* 1) iniciar comunicacao com exploradores
          NOTA: primeiros parametros deverao ser argc e argv */
      
      intro(argc,argv,&nExplorador,positio);
      //realloc(positio,nExplorador * 2 * sizeof(int));
      //printf("%d\n",nExplorador);
      /*for(int i = 0  ; i < nExplorador; i++){
            printf("%d %d\n",positio[i][0],positio[i][1]);
      }*/
      
    /* 2) comunicar com os exploradores e receber informacoes, 
          enquanto existem movimentacoes a realizar */
      int id,typus;
      char save;
      int minh = 2147483647, maxh= -2147483648, maxv = -2147483648, minv = 2147483647;
      pilha * pilha_coordenadas = cria_pilha();
      if(pilha_coordenadas==NULL) return 0;

      while('X'!=(save=explorator(&id,&typus))){
            //printf("%c %d %d \n",save,id,typus);
            switch(save){
                  case 'N':
                        positio[id][1]--;
                        break;
                  
                  case 'S':
                        positio[id][1]++;
                        break;
                  case 'O':
                        positio[id][0]--;
                        break;
                  case 'E':
                        positio[id][0]++;
                        break;                
            }
            if(typus>4||typus<0) return 0;
            if(insere_elemento(pilha_coordenadas,positio[id][0],positio[id][1],typus)==0) return 0;
            if(positio[id][0]<minh)minh = positio[id][0];
            if(positio[id][0]>maxh)maxh = positio[id][0];
            if(positio[id][1]<minv)minv = positio[id][1];
            if(positio[id][1]>maxv)maxv = positio[id][1];
            
      };
      //printf("H : %d %d V: %d %d\n",maxh, minh ,maxv,minv );
      //printf("\n");
      //print_pilha(pilha_coordenadas);
      mapa = (char **)malloc((maxh-minh+1)*sizeof(char *));
      for( int i = 0 ; i < maxh-minh+1;i++){
            mapa[i] = (char*)calloc(maxv-minv+1,1);
      }
      
      while( pilha_coordenadas->tamanho>0){
            //printf("Tamanho -> %d \n", pilha_coordenadas->tamanho);
            mapa[pilha_coordenadas->top->x-minh][pilha_coordenadas->top->y-minv]= (char) pilha_coordenadas->top->terreno;
            if(pop_elemento(pilha_coordenadas)==0) return 0;
      }
      //printf("%d %d ",maxh-minh+1,maxv-minv+1);
      
    /* 3) imprime e verifica o mapa
          NOTA: funcao mapa_pos e' o primeiro das funcoes */

      tabula(mapa_pos,maxh-minh+1,maxv-minv+1);
      veritas(mapa_pos,maxh-minh+1,maxv-minv+1);

    /* 4) termina comunicacoes com os exploradores */
      relinquo();
      
      for(int i = 0; i < maxh-minh+1;i++){
            free(mapa[i]);
      }
      free(mapa);

      del_pilha(pilha_coordenadas);

    return 0;
}