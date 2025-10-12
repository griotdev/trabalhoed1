#include "pilha.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
	char **dados;      // vetor de strings
	size_t topo;       // quantidade de elementos
	size_t capacidade; // capacidade alocada
} PilhaImpl;

static char* dup_str(const char* s){
	if(!s) return NULL;
	size_t n = strlen(s) + 1;
	char* cpy = (char*)malloc(n);
	if(cpy) memcpy(cpy, s, n);
	return cpy;
}

static void garantir_capacidade(PilhaImpl* pi, size_t nova_qtd){
	if(nova_qtd <= pi->capacidade) return;
	size_t nova_cap = pi->capacidade ? pi->capacidade * 2 : 8;
	while(nova_cap < nova_qtd) nova_cap *= 2;
	char** novo = (char**)realloc(pi->dados, nova_cap * sizeof(char*));
	if(!novo) return;
	pi->dados = novo;
	pi->capacidade = nova_cap;
}

Pilha criaPilha(void){
	PilhaImpl* pi = (PilhaImpl*)calloc(1, sizeof(PilhaImpl));
	return (Pilha)pi;
}

void liberaPilha(Pilha p){
	if(!p) return;
	PilhaImpl* pi = (PilhaImpl*)p;
	for(size_t i=0;i<pi->topo;i++){
		free(pi->dados[i]);
	}
	free(pi->dados);
	free(pi);
}

void limpaPilha(Pilha p){
	if(!p) return;
	PilhaImpl* pi = (PilhaImpl*)p;
	for(size_t i=0;i<pi->topo;i++){
		free(pi->dados[i]);
		pi->dados[i] = NULL;
	}
	pi->topo = 0;
}

int pilhaVazia(Pilha p){
	if(!p) return 1;
	PilhaImpl* pi = (PilhaImpl*)p;
	return pi->topo == 0;
}

size_t tamanhoPilha(Pilha p){
	if(!p) return 0;
	return ((PilhaImpl*)p)->topo;
}

void empilha(Pilha p, const char* instrucao){
	if(!p) return;
	PilhaImpl* pi = (PilhaImpl*)p;
	garantir_capacidade(pi, pi->topo + 1);
	if(pi->capacidade < pi->topo + 1) return;
	pi->dados[pi->topo++] = dup_str(instrucao);
}

char* desempilha(Pilha p){
	if(!p) return NULL;
	PilhaImpl* pi = (PilhaImpl*)p;
	if(pi->topo == 0) return NULL;
	char* s = pi->dados[--pi->topo];
	pi->dados[pi->topo] = NULL;
	return s;
}

const char* topoPilha(Pilha p){
	if(!p) return NULL;
	PilhaImpl* pi = (PilhaImpl*)p;
	if(pi->topo == 0) return NULL;
	return pi->dados[pi->topo - 1];
}

