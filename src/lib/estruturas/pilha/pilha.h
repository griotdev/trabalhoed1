#ifndef PILHA_H
#define PILHA_H

#include <stddef.h>

// Tipo opaco da Pilha
typedef void* Pilha;

/**
 * Estrutura de dados: Pilha (LIFO)
 * Armazena linhas de instruções (strings) dos arquivos .geo/.qry.
 *
 * Contrato de memória para strings:
 * - As funções de inserção copiam internamente a string recebida
 *   (strdup/clone). O chamador pode liberar a string original se desejar.
 * - As funções de remoção (desempilha) retornam o ponteiro da string
 *   armazenada; a posse é transferida para o chamador, que deve chamar free().
 */

// Cria uma pilha vazia
Pilha criaPilha(void);

// Libera toda a memória da pilha (inclusive strings remanescentes)
void liberaPilha(Pilha p);

// Remove todos os elementos da pilha, mantendo a pilha válida
void limpaPilha(Pilha p);

// Retorna 1 se vazia, 0 caso contrário
int pilhaVazia(Pilha p);

// Retorna a quantidade de elementos na pilha
size_t tamanhoPilha(Pilha p);

// Empilha uma linha de instrução (é feita cópia da string)
void empilha(Pilha p, const char* instrucao);

// Desempilha e retorna a string do topo (posse transferida ao chamador)
// Retorna NULL se vazia
char* desempilha(Pilha p);

// Retorna a string do topo (somente leitura, ainda pertencente à pilha)
// Retorna NULL se vazia
const char* topoPilha(Pilha p);

#endif // PILHA_H
