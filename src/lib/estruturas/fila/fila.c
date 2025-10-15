#include "fila.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
	char **dados;      // vetor de strings
	size_t inicio;     // índice do primeiro elemento
	size_t qtd;        // quantidade de elementos
	size_t capacidade; // capacidade alocada
} FilaImpl;

static char* dup_str_f(const char* s){
	if(!s) return NULL;
	size_t n = strlen(s) + 1;
	char* cpy = (char*)malloc(n);
	if(cpy) memcpy(cpy, s, n);
	return cpy;
}

static void garantir_capacidade(FilaImpl* fi, size_t nova_qtd){
	if(nova_qtd <= fi->capacidade) return;
	size_t nova_cap = fi->capacidade ? fi->capacidade * 2 : 8;
	while(nova_cap < nova_qtd) nova_cap *= 2;
	char** novo = (char**)malloc(nova_cap * sizeof(char*));
	if(!novo) return;
	for(size_t i=0;i<fi->qtd;i++){
		size_t idx = (fi->inicio + i) % (fi->capacidade ? fi->capacidade : 1);
		novo[i] = fi->capacidade ? fi->dados[idx] : NULL;
	}
	free(fi->dados);
	fi->dados = novo;
	fi->inicio = 0;
	fi->capacidade = nova_cap;
}

Fila criaFila(void){
	FilaImpl* fi = (FilaImpl*)calloc(1, sizeof(FilaImpl));
	return (Fila)fi;
}

void liberaFila(Fila f){
	if(!f) return;
	FilaImpl* fi = (FilaImpl*)f;
	for(size_t i=0;i<fi->qtd;i++){
		size_t idx = (fi->inicio + i) % fi->capacidade;
		free(fi->dados[idx]);
	}
	free(fi->dados);
	free(fi);
}

void limpaFila(Fila f){
	if(!f) return;
	FilaImpl* fi = (FilaImpl*)f;
	for(size_t i=0;i<fi->qtd;i++){
		size_t idx = (fi->inicio + i) % fi->capacidade;
		free(fi->dados[idx]);
		fi->dados[idx] = NULL;
	}
	fi->inicio = 0;
	fi->qtd = 0;
}

int filaVazia(Fila f){
	if(!f) return 1;
	FilaImpl* fi = (FilaImpl*)f;
	return fi->qtd == 0;
}

size_t tamanhoFila(Fila f){
	if(!f) return 0;
	return ((FilaImpl*)f)->qtd;
}

void enfileira(Fila f, const char* instrucao){
	if(!f) return;
	FilaImpl* fi = (FilaImpl*)f;
	garantir_capacidade(fi, fi->qtd + 1);
	if(fi->capacidade < fi->qtd + 1) return;
	size_t pos = (fi->inicio + fi->qtd) % fi->capacidade;
	fi->dados[pos] = dup_str_f(instrucao);
	fi->qtd++;
}

char* desenfileira(Fila f){
	if(!f) return NULL;
	FilaImpl* fi = (FilaImpl*)f;
	if(fi->qtd == 0) return NULL;
	char* s = fi->dados[fi->inicio];
	fi->dados[fi->inicio] = NULL;
	fi->inicio = (fi->inicio + 1) % fi->capacidade;
	fi->qtd--;
	return s;
}

const char* frenteFila(Fila f){
	if(!f) return NULL;
	FilaImpl* fi = (FilaImpl*)f;
	if(fi->qtd == 0) return NULL;
	return fi->dados[fi->inicio];
}

