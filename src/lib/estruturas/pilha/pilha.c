/* src/pilha.c
 *
 * Implementação do TAD Pilha genérica usando lista encadeada.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../estruturas/pilha/pilha.h"

/* Nó da pilha (implementação interna, não visível no .h) */
typedef struct noPilha {
    void *dado;
    struct noPilha *prox;
} NoPilha;

/* Estrutura da pilha */
typedef struct pilha_internal {
    NoPilha *topo;
    int tamanho;
} PilhaInternal;

/**
 * Cria uma nova pilha vazia.
 */
Pilha criaPilha(void) {
    PilhaInternal *pilha = (PilhaInternal*)malloc(sizeof(PilhaInternal));
    if (pilha == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a pilha.\n");
        return NULL;
    }
    
    pilha->topo = NULL;
    pilha->tamanho = 0;
    
    return (Pilha)pilha;
}

/**
 * Empilha um elemento no topo da pilha.
 */
int empilha(Pilha pilha, void *dado) {
    PilhaInternal *p = (PilhaInternal*)pilha;
    if (p == NULL) {
        return 0;
    }
    
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nó da pilha.\n");
        return 0;
    }
    
    novo->dado = dado;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
    
    return 1;
}

/**
 * Desempilha um elemento do topo da pilha.
 */
void* desempilha(Pilha pilha) {
    PilhaInternal *p = (PilhaInternal*)pilha;
    if (p == NULL || p->topo == NULL) {
        return NULL;
    }
    
    NoPilha *temp = p->topo;
    void *dado = temp->dado;
    
    p->topo = temp->prox;
    free(temp);
    p->tamanho--;
    
    return dado;
}

/**
 * Consulta o elemento no topo da pilha sem removê-lo.
 */
void* consultaPilha(Pilha pilha) {
    PilhaInternal *p = (PilhaInternal*)pilha;
    if (p == NULL || p->topo == NULL) {
        return NULL;
    }
    return p->topo->dado;
}

/**
 * Verifica se a pilha está vazia.
 */
int pilhaVazia(Pilha pilha) {
    PilhaInternal *p = (PilhaInternal*)pilha;
    if (p == NULL) {
        return 1;
    }
    return (p->topo == NULL);
}

/**
 * Retorna o tamanho atual da pilha.
 */
int tamanhoPilha(Pilha pilha) {
    PilhaInternal *p = (PilhaInternal*)pilha;
    if (p == NULL) {
        return 0;
    }
    return p->tamanho;
}

/**
 * Destrói a pilha, liberando toda a memória alocada.
 */
void destroiPilha(Pilha pilha, FuncaoLiberaPilha libera) {
    PilhaInternal *p = (PilhaInternal*)pilha;
    if (p == NULL) {
        return;
    }
    
    NoPilha *atual = p->topo;
    while (atual != NULL) {
        NoPilha *temp = atual;
        atual = atual->prox;
        
        if (libera != NULL && temp->dado != NULL) {
            libera(temp->dado);
        }
        free(temp);
    }
    
    free(p);
}
