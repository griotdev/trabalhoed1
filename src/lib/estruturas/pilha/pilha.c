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
struct pilha {
    NoPilha *topo;
    int tamanho;
};

/**
 * Cria uma nova pilha vazia.
 */
Pilha* criaPilha(void) {
    Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));
    if (pilha == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a pilha.\n");
        return NULL;
    }
    
    pilha->topo = NULL;
    pilha->tamanho = 0;
    
    return pilha;
}

/**
 * Empilha um elemento no topo da pilha.
 */
int empilha(Pilha *pilha, void *dado) {
    if (pilha == NULL) {
        return 0;
    }
    
    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória para nó da pilha.\n");
        return 0;
    }
    
    novo->dado = dado;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    
    return 1;
}

/**
 * Desempilha um elemento do topo da pilha.
 */
void* desempilha(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return NULL;
    }
    
    NoPilha *temp = pilha->topo;
    void *dado = temp->dado;
    
    pilha->topo = temp->prox;
    free(temp);
    pilha->tamanho--;
    
    return dado;
}

/**
 * Consulta o elemento no topo da pilha sem removê-lo.
 */
void* consultaPilha(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return NULL;
    }
    return pilha->topo->dado;
}

/**
 * Verifica se a pilha está vazia.
 */
int pilhaVazia(Pilha *pilha) {
    if (pilha == NULL) {
        return 1;
    }
    return (pilha->topo == NULL);
}

/**
 * Retorna o tamanho atual da pilha.
 */
int tamanhoPilha(Pilha *pilha) {
    if (pilha == NULL) {
        return 0;
    }
    return pilha->tamanho;
}

/**
 * Destrói a pilha, liberando toda a memória alocada.
 */
void destroiPilha(Pilha *pilha, FuncaoLiberaPilha libera) {
    if (pilha == NULL) {
        return;
    }
    
    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        NoPilha *temp = atual;
        atual = atual->prox;
        
        if (libera != NULL && temp->dado != NULL) {
            libera(temp->dado);
        }
        free(temp);
    }
    
    free(pilha);
}
