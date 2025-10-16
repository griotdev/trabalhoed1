/* include/pilha.h
 *
 * TAD Pilha genérica implementada com ponteiros void.
 * Segue o padrão LIFO (Last In, First Out).
 * 
 * Observações:
 *  - A pilha armazena ponteiros void* para permitir tipos genéricos.
 *  - O usuário é responsável pela alocação/liberação dos dados.
 *  - Funções de callback podem ser fornecidas para liberar memória.
 */

#ifndef PILHA_H
#define PILHA_H

/* Tipo genérico para a Pilha (usa void* conforme exigência) */
typedef void* Pilha;

/* Tipo de função callback para liberar elementos */
typedef void (*FuncaoLiberaPilha)(void*);

/**
 * Cria uma nova pilha vazia.
 * @return Pilha criada (void*), ou NULL em caso de erro.
 */
Pilha criaPilha(void);

/**
 * Empilha um elemento no topo da pilha.
 * @param pilha Pilha (void*).
 * @param dado Ponteiro para o dado a ser empilhado.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int empilha(Pilha pilha, void *dado);

/**
 * Desempilha um elemento do topo da pilha.
 * @param pilha Pilha (void*).
 * @return Ponteiro para o dado desempilhado, ou NULL se a pilha estiver vazia.
 */
void* desempilha(Pilha pilha);

/**
 * Consulta o elemento no topo da pilha sem removê-lo.
 * @param pilha Pilha (void*).
 * @return Ponteiro para o dado no topo, ou NULL se a pilha estiver vazia.
 */
void* consultaPilha(Pilha pilha);

/**
 * Verifica se a pilha está vazia.
 * @param pilha Pilha (void*).
 * @return 1 se vazia, 0 caso contrário.
 */
int pilhaVazia(Pilha pilha);

/**
 * Retorna o tamanho atual da pilha.
 * @param pilha Pilha (void*).
 * @return Número de elementos na pilha.
 */
int tamanhoPilha(Pilha pilha);

/**
 * Destrói a pilha, liberando toda a memória alocada.
 * @param pilha Pilha (void*).
 * @param libera Função callback para liberar cada elemento (pode ser NULL).
 */
void destroiPilha(Pilha pilha, FuncaoLiberaPilha libera);

#endif /* PILHA_H */
