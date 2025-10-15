#ifndef FILA_H
#define FILA_H

#include <stddef.h>

typedef void* Fila;

Fila criaFila(void);

void liberaFila(Fila f);

void limpaFila(Fila f);

int filaVazia(Fila f);

size_t tamanhoFila(Fila f);

void enfileira(Fila f, const char* instrucao);

char* desenfileira(Fila f);

const char* frenteFila(Fila f);

#endif
