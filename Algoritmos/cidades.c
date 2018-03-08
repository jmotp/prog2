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


int cidades_resort(vetor *vec, char criterio)
{
  quicksort(vec,0,(vec->tamanho)-1,criterio);

}

void quicksort(vetor *vec,int ini,int fim,char criterio){
    if(ini<fim){
      int pivot = partition(vec,ini,fim, criterio);
      quicksort(vec,ini,pivot-1,criterio);
      quicksort(vec,pivot+1,fim, criterio);
    }
}

int partition(vetor * vec,int ini,int fim,char criterio){
  cidade pivot = vec->elementos[fim];
  int i =ini -1;
  if(criterio=='a'){
  for (int j = ini; j <= fim- 1; j++)
    {
        if (vec->elementos[j].area < pivot.area)
        {
            i++;
            swap_cidades(vec,i,j);
        }else if(vec->elementos[j].area == pivot.area){
              if(vec->elementos[j].populacao<pivot.populacao){
                i++;
                swap_cidades(vec,i,j);
              }
        }
    }
  }
  else if(criterio=='p'){
    for (int j = ini; j <= fim- 1; j++)
    {
        if (strcmp(vec->elementos[j].pais,pivot.pais)<0)
        {
            i++;
            swap_cidades(vec,i,j);
        }else if(strcmp(vec->elementos[j].pais,pivot.pais)==0){
              if(vec->elementos[j].populacao<pivot.populacao){
                i++;
                swap_cidades(vec,i,j);
              }
        }
    }
  }

  swap_cidades(vec,i+1,fim);
  return i+1;
}


void swap_cidades(vetor * vec,int i,int j){
  cidade aux = vec->elementos[i];
  vec->elementos[i]=vec->elementos[j];
  vec->elementos[j]=aux;

  return;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  return NULL;
}
