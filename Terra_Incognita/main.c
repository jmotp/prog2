#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
//#include "auxiliar.h"
#include "tabdispersao.h"

tabela_dispersao * table;
int minh,minv;


int mapa_pos(int x, int y)
{
	int chave[2]={x+minh,y+minv};
	char valor = tabela_valor(table,chave);
	if(valor==-1)return 0;

	return valor;
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
	int i = 0;
	minh = 100000000;
	minv = 100000000;
	int maxh = -1000000000;
	int maxv = -1000000000;
	//pilha * pilha_coordenadas = cria_pilha();
	//if(pilha_coordenadas==NULL) return 0;
	table = tabela_nova(10000,hash_djbm);
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
		//if(insere_elemento(pilha_coordenadas,positio[id][0],positio[id][1],typus)==0) return 0;
		int chave[2]={positio[id][0],positio[id][1]};
		tabela_adiciona(table,chave,typus);
		////printf("%d %d %d\n",typus,positio[id][0],positio[id][1]);
		//mostraTabela(table);
		if(positio[id][0]<minh)minh = positio[id][0];
		if(positio[id][0]>maxh)maxh = positio[id][0];
		if(positio[id][1]<minv)minv = positio[id][1];
		if(positio[id][1]>maxv)maxv = positio[id][1];
		
		//printf("%d\n",i++);
	};
	//mostraTabela(table);
	//printf("H : %d %d V: %d %d\n",maxh, minh ,maxv,minv );
	//printf("\n");
	//print_pilha(pilha_coordenadas);

		//printf("%d %d ",maxh-minh+1,maxv-minv+1);

	/* 3) imprime e verifica o mapa
		NOTA: funcao mapa_pos e' o primeiro das funcoes */

	tabula(mapa_pos,maxh-minh+1,maxv-minv+1);
	veritas(mapa_pos,maxh-minh+1,maxv-minv+1);

	/* 4) termina comunicacoes com os exploradores */
	relinquo();

	tabela_apaga(table);
	printf("hey");

	return 0;
}