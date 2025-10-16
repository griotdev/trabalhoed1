/* include/fila.h
 *
 * TAD Fila genérica implementada com ponteiros void.
 * Segue o padrão FIFO (First In, First Out).
 * 
 * Observações:
 *  - A fila armazena ponteiros void* para permitir tipos genéricos.
 *  - O usuário é responsável pela alocação/liberação dos dados.
 *  - Funções de callback podem ser fornecidas para liberar memória.
 */

#ifndef FILA_H
#define FILA_H

/* Tipo genérico para a Fila (usa void* conforme exigência) */
typedef void* Fila;

/* Tipo de função callback para liberar elementos */
typedef void (*FuncaoLibera)(void*);

/**
 * Cria uma nova fila vazia.
 * @return Ponteiro para a fila criada (void*), ou NULL em caso de erro.
 */
Fila criaFila(void);

/**
 * Enfileira um elemento no final da fila.
 * @param fila Fila (void*).
 * @param dado Ponteiro para o dado a ser enfileirado.
 * @return 1 em caso de sucesso, 0 em caso de erro.
 */
int enfileira(Fila fila, void *dado);

/**
 * Desenfileira um elemento do início da fila.
 * @param fila Fila (void*).
 * @return Ponteiro para o dado desenfileirado, ou NULL se a fila estiver vazia.
 */
void* desenfileira(Fila fila);

/**
 * Consulta o elemento no início da fila sem removê-lo.
 * @param fila Fila (void*).
 * @return Ponteiro para o dado no início, ou NULL se a fila estiver vazia.
 */
void* consultaFila(Fila fila);

/**
 * Verifica se a fila está vazia.
 * @param fila Fila (void*).
 * @return 1 se vazia, 0 caso contrário.
 */
int filaVazia(Fila fila);

/**
 * Retorna o tamanho atual da fila.
 * @param fila Fila (void*).
 * @return Número de elementos na fila.
 */
int tamanhoFila(Fila fila);

/**
 * Destrói a fila, liberando toda a memória alocada.
 * @param fila Fila (void*).
 * @param libera Função callback para liberar cada elemento (pode ser NULL).
 */
void destroiFila(Fila fila, FuncaoLibera libera);

#endif /* FILA_H */
