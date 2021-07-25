#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_BEBIDAS_NA_ESTEIRA 3
#define MAX_ESTEIRAS 2


typedef struct esteira_s
{
  float volume, preco;
  char nome[10];
  char bebida[MAX_BEBIDAS_NA_ESTEIRA];
  int topo;
} esteira_t;

esteira_t g_esteiras[MAX_ESTEIRAS];


void esteira_inicia(esteira_t *esteira)
{
  esteira-> topo = -1;
}


int esteira_esta_vazia(esteira_t *esteira)
{
  return esteira->topo == -1 ? 1 : 0;
}


int esteira_esta_lotada (esteira_t *esteira)
{
  return esteira->topo==MAX_BEBIDAS_NA_ESTEIRA-1 ? 1 : 0;
}


int esteira_insere(esteira_t *esteira, int nova_bebida)
{
  if(esteira_esta_lotada(esteira)){
    printf("Erro: esteira lotada.\n");
    return 1;
  }
  else{
    esteira->topo++;
    esteira->bebida[esteira->topo] = nova_bebida;
    printf("\nDigite o nome: ");
    (void) scanf("%s", esteira->nome);
    printf("Digite o preco: ");
    (void) scanf("%f", &esteira->preco);
    printf("Digite o volume:");
    (void) scanf("%f", &esteira->volume);
    printf("\nUma bebida adicionada na esteira com sucesso.\n");
    printf("O nome da bebida e: %s\n", esteira->nome);
    printf("O preco da bebida e: %f\n", esteira->preco);
    printf("O volume da bebida e: %f\n", esteira->volume);
    return 0;
  }
}


int main (){
  int erro = 0;
  int pos_esteira = -1;
  esteira_t* esteira;

  printf("Qual esteira deseja inserir uma bebida (de 1 a %d)? ", MAX_ESTEIRAS);
  (void) scanf("%d", &pos_esteira);

  if( pos_esteira < 1 || pos_esteira > MAX_ESTEIRAS )
  {
    printf("Erro: esteira invalida\n");
    return 1;
  }

  esteira = &g_esteiras[pos_esteira - 1];
	esteira_inicia(esteira);
  erro = esteira_insere(esteira, 0);

	if( ! erro )
  {
    printf("Tudo certo; ate a proxima =)\n");
  }
  else
  {
    printf("Erro %d ocorreu\n", erro);
  }

  return erro;
}

