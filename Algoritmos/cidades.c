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
  vetor* buffer= vetor_novo();

  FILE* ficheiro = fopen(nomef,"rb");

  if(ficheiro == NULL) return NULL;

  while(!feof(ficheiro)){
    cidade load_buffer;
    if(fread(&load_buffer,sizeof(cidade),1,ficheiro)==1){
      vetor_insere(buffer,load_buffer,-1);
     }
  }
  fclose(ficheiro);
  return buffer;
}


int cidades_save(const vetor *vec, const char *nomef)
{
  FILE* ficheiro = fopen(nomef,"wb");

  if(ficheiro==NULL) return -1;

  int i;
  for( i = 0; i < vec->tamanho;i++){
    if(fwrite(&vec->elementos[i],sizeof(cidade),1,ficheiro)!=1) return -1;
  }

  fclose(ficheiro);

  return i;
}


int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
	return -1;
}

int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
  return -1;
}

int cidades_resort(vetor *vec, char criterio)
{
  return -1;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  return NULL;
}
