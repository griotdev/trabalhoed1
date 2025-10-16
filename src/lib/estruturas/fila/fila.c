/* src/fila.c
 *
 * Implementação do TAD Fila genérica usando lista encadeada.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../estruturas/fila/fila.h"

/* Nó da fila (implementação interna, não visível no .h) */
typedef struct no {
    void *dado;
    struct no *prox;
} No;

/* Estrutura da fila */
typedef struct fila_internal {
    No *inicio;
    No *fim;
    int tamanho;
} FilaInternal;

/**
 * Cria uma nova fila vazia.
 */
Fila criaFila(void) {
    FilaInternal *fila = (FilaInternal*)malloc(sizeof(FilaInternal));
    if (fila == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fila.\n");
        return NULL;
    }
    
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    
    return (Fila)fila;
}

/**
 * Enfileira um elemento no final da fila.
 */
int enfileira(Fila fila, void *dado) {
    FilaInternal *f = (FilaInternal*)fila;
    if (f == NULL) {
        return 0;
    }
    
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nó da fila.\n");
        return 0;
    }
    
    novo->dado = dado;
    novo->prox = NULL;
    
    if (f->fim != NULL) {
        f->fim->prox = novo;
    }
    f->fim = novo;
    
    if (f->inicio == NULL) {
        f->inicio = novo;
    }
    
    f->tamanho++;
    return 1;
}

/**
 * Desenfileira um elemento do início da fila.
 */
void* desenfileira(Fila fila) {
    FilaInternal *f = (FilaInternal*)fila;
    if (f == NULL || f->inicio == NULL) {
        return NULL;
    }
    
    No *temp = f->inicio;
    void *dado = temp->dado;
    
    f->inicio = temp->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(temp);
    f->tamanho--;
    
    return dado;
}

/**
 * Consulta o elemento no início da fila sem removê-lo.
 */
void* consultaFila(Fila fila) {
    FilaInternal *f = (FilaInternal*)fila;
    if (f == NULL || f->inicio == NULL) {
        return NULL;
    }
    return f->inicio->dado;
}

/**
 * Verifica se a fila está vazia.
 */
int filaVazia(Fila fila) {
    FilaInternal *f = (FilaInternal*)fila;
    if (f == NULL) {
        return 1;
    }
    return (f->inicio == NULL);
}

/**
 * Retorna o tamanho atual da fila.
 */
int tamanhoFila(Fila fila) {
    FilaInternal *f = (FilaInternal*)fila;
    if (f == NULL) {
        return 0;
    }
    return f->tamanho;
}

/**
 * Destrói a fila, liberando toda a memória alocada.
 */
void destroiFila(Fila fila, FuncaoLibera libera) {
    FilaInternal *f = (FilaInternal*)fila;
    if (f == NULL) {
        return;
    }
    
    No *atual = f->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        
        if (libera != NULL && temp->dado != NULL) {
            libera(temp->dado);
        }
        free(temp);
    }
    
    free(f);
}
