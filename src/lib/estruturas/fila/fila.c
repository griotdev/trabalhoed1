#include <stdio.h>
#include <stdlib.h>
#include "../../estruturas/fila/fila.h"

typedef struct no {
    void *dado;
    struct no *prox;
} No;

struct fila {
    No *inicio;
    No *fim;
    int tamanho;
};

Fila* criaFila(void) {
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    if (fila == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fila.\n");
        return NULL;
    }
    
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    
    return fila;
}

int enfileira(Fila *fila, void *dado) {
    if (fila == NULL) {
        return 0;
    }
    
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nó da fila.\n");
        return 0;
    }
    
    novo->dado = dado;
    novo->prox = NULL;
    
    if (fila->fim != NULL) {
        fila->fim->prox = novo;
    }
    fila->fim = novo;
    
    if (fila->inicio == NULL) {
        fila->inicio = novo;
    }
    
    fila->tamanho++;
    return 1;
}

void* desenfileira(Fila *fila) {
    if (fila == NULL || fila->inicio == NULL) {
        return NULL;
    }
    
    No *temp = fila->inicio;
    void *dado = temp->dado;
    
    fila->inicio = temp->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(temp);
    fila->tamanho--;
    
    return dado;
}

void* consultaFila(Fila *fila) {
    if (fila == NULL || fila->inicio == NULL) {
        return NULL;
    }
    return fila->inicio->dado;
}

int filaVazia(Fila *fila) {
    if (fila == NULL) {
        return 1;
    }
    return (fila->inicio == NULL);
}

int tamanhoFila(Fila *fila) {
    if (fila == NULL) {
        return 0;
    }
    return fila->tamanho;
}

void destroiFila(Fila *fila, FuncaoLibera libera) {
    if (fila == NULL) {
        return;
    }
    
    No *atual = fila->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        
        if (libera != NULL && temp->dado != NULL) {
            libera(temp->dado);
        }
        free(temp);
    }
    
    free(fila);
}
