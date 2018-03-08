/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

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
  while(!feof(ficheiro)){
    cidade load_buffer;
    if(fread(&load_buffer,sizeof(cidade),1,ficheiro)==1){
      vetor_insere(buffer,load_buffer,-1);
     }
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
    FILE * ficheiro = fopen(nomef,"wb");
    if(ficheiro==NULL) return -1;

    //escrita no ficheiro, na pos encontrada
    fseek(ficheiro,-tamanho,SEEK_CUR);
    
    if(fwrite(&nova,tamanho,1,ficheiro)!=1) return -1;
    fclose(ficheiro);
  } 
  return pos;
}

int cidades_resort(vetor *vec, char criterio)
{
  
  return -1;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  if (vec==NULL || nomecidade==NULL) return NULL;

  int posref=-1;

  int i;
  for(i=0; i<vec->tamanho ; i++){
    if(strcmp(nomecidade,vec->elementos[i].nome)==0){
      posref=i;
      break;
    }
  }

  if(posref==-1) return NULL;

  int popref=vec->elementos[posref].populacao;

  char **vecsimilares;

  vecsimilares=malloc(sizeof(char**));
  vecsimilares[0]=calloc(MAXSTR,sizeof(char*));

  (*nsimilares)=0;
  
  for(i=0; i<vec->tamanho ; i++){
    
    if((vec->elementos[i].populacao - popref)<=deltapop && (vec->elementos[i].populacao - popref)>= -1*deltapop && strcmp(vec->elementos[i].nome,nomecidade)!=0) {
      
      if(nsimilares!=0){
        vecsimilares=realloc(vecsimilares,((*nsimilares)+1)*sizeof(char*));
        vecsimilares[*nsimilares]=calloc(MAXSTR,sizeof(char*));  
      }

      strcpy(vecsimilares[*nsimilares],vec->elementos[i].nome);
      (*nsimilares)++;

    }
  }

  if((*nsimilares)==0) return NULL;

  return vecsimilares;
}
