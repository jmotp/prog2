/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include <time.h>
#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

vetor* cidades_load(const char *nomef)
{
  //vetor temporario
  vetor* buffer= vetor_novo();
  if(buffer== NULL) return NULL;
  //abertura de ficheiro
  FILE* ficheiro = fopen(nomef,"rb");
  if(ficheiro == NULL) return NULL;
  //load dos dados
  cidade load_buffer;
  while(!feof(ficheiro)&&fread(&load_buffer,sizeof(cidade),1,ficheiro)==1){
      vetor_insere(buffer,load_buffer,-1);
  }
  //return sucesso
  fclose(ficheiro);
  return buffer;
}


int cidades_save(const vetor *vec, const char *nomef)
{
  //criacao / abertura de ficheiro de output
  FILE* ficheiro = fopen(nomef,"wb");
  if(ficheiro==NULL) return -1;
  //save dos dados
  int i;
  for( i = 0; i < vec->tamanho;i++){
    if(fwrite(&vec->elementos[i],sizeof(cidade),1,ficheiro)!=1) return -1;
  }
  //return sucesso
  fclose(ficheiro);
  return i;
}


int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
  int pos = -1;
  FILE *ficheiro = fopen(nomef,"rb");
  if(ficheiro==NULL) return -1;
  size_t tamanho = sizeof(cidade);
  cidade tmp;
  while(!feof(ficheiro)){
    if(fread(&tmp,tamanho,1,ficheiro)!=1) return -1;
    if(strcmp(tmp.nome,nomecidade)==0){
      if(resultado!=NULL) *resultado=tmp;
      pos=(ftell(ficheiro)-tamanho)/tamanho;
      break;
    }  
  }
  fclose(ficheiro);
	return pos;
}

int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
  
  int pos = cidades_peek(nomef,nomecidade,NULL);
  
  
  if(pos>=0)
  {
    size_t tamanho = sizeof(cidade); 
    FILE * ficheiro = fopen(nomef,"rb+");
    if(ficheiro==NULL) return -1;

    //escrita no ficheiro, na pos encontrada
    fseek(ficheiro,pos*(tamanho),SEEK_SET);
    
    if(fwrite(&nova,tamanho,1,ficheiro)!=1) return -1;
    fclose(ficheiro);
  } 
  return pos;
}

void cidade_print(vetor * vec,int size){
  for(int i = 0;i < size;i++){
    printf("%d\n",vec->elementos[i].area);
  }
  printf("\n");
}

int cidades_resort(vetor *vec, char criterio)
{
  cidade aux;
  cidade a,b;
  if(criterio == 'p'){

  
    for(int i= 1;i < vec->tamanho;i++){
      int j=i;
      while(j>0&&strcmp(vec->elementos[j].pais,vec->elementos[j-1].pais)<0){
        aux = vec->elementos[j-1];
        vec->elementos[j-1]=vec->elementos[j];
        vec->elementos[j]=aux;
        j--;
        //cidade_print(vec,10);
      }
    }
  }else if(criterio == 'a'){
    for(int i= 1;i < vec->tamanho;i++){
      int j=i;
      while(j>0){
        a=vec->elementos[j-1];
        b=vec->elementos[j];
        if(a.area>b.area){
          swap_cidades(vec,j);
         // printf("swap\n%d ", j);
        }else if(a.area==b.area){
          if(a.populacao>b.populacao){
            swap_cidades(vec,j);
          }
        }
        j--;
        //cidade_print(vec,10);
      }
    }

  }else return -1;


  return 0;
}

void swap_cidades(vetor * vec,int j){
  cidade aux = vec->elementos[j-1];
        vec->elementos[j-1]=vec->elementos[j];
        vec->elementos[j]=aux;
  
  return;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  return NULL;
}
