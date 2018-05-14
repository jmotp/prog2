#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"

int mapa_pos(int x, int y)
{
    /* devolve tipo de terreno na posicao x,y */
    
    return TERRA_INCOGNITA;
}

int main(int argc, char *argv[])
{
      int nExplorador;
      int positio[1000][2];
    /* 1) iniciar comunicacao com exploradores
          NOTA: primeiros parametros deverao ser argc e argv */
      
      intro(argc,argv,&nExplorador,positio);
      realloc(positio,nExplorador * 2 * sizeof(int));
      printf("%d\n",nExplorador);
      for(int i = 0  ; i < nExplorador; i++){
            printf("%d %d\n",positio[i][0],positio[i][1]);
      }
    /* 2) comunicar com os exploradores e receber informacoes, 
          enquanto existem movimentacoes a realizar */
      int id,typus;
      char save;
      int minh = 1000000, maxh= -1000000, maxv = -10000000, minv = 1000000;
      while('X'!=(save=explorator(&id,&typus))){
            printf("%c %d %d \n",save,id,typus);
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
            if(positio[id][0]<minh)minh = positio[id][0];
            if(positio[id][0]>maxh)maxh = positio[id][0];
            if(positio[id][1]<minv)minv = positio[id][1];
            if(positio[id][1]>maxv)maxv = positio[id][1];
      };
      printf("%d %d\n",maxh-minh +1 ,maxv-minv +1 );

    /* 3) imprime e verifica o mapa
          NOTA: funcao mapa_pos e' o primeiro das funcoes */


    /* 4) termina comunicacoes com os exploradores */


    return 0;
}