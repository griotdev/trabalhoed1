/* include/carregadorManager.h
 *
 * Gerenciador de carregadores (pilhas de formas).
 * 
 * Mantém um conjunto de carregadores identificados por ID.
 * Cada carregador é uma pilha que pode ser anexada a disparadores
 * ou usada temporariamente para armazenar formas.
 */

#ifndef CARREGADOR_MANAGER_H
#define CARREGADOR_MANAGER_H

#include "../../estruturas/pilha/pilha.h"

/* Tipo opaco para o gerenciador de carregadores */
typedef void* CarregadorManager;

/**
 * Cria um novo gerenciador de carregadores.
 * @return CarregadorManager criado, ou NULL em caso de erro
 */
CarregadorManager criaCarregadorManager();

/**
 * Destrói o gerenciador e todos os carregadores gerenciados.
 * @param manager Gerenciador a ser destruído
 */
void destroiCarregadorManager(CarregadorManager manager);

/**
 * Obtém um carregador pelo ID, criando-o se não existir.
 * @param manager Gerenciador
 * @param id ID do carregador
 * @return Pilha do carregador
 */
Pilha obtemCarregador(CarregadorManager manager, int id);

/**
 * Remove e retorna um carregador pelo ID.
 * @param manager Gerenciador
 * @param id ID do carregador
 * @return Pilha do carregador removido, ou NULL se não existir
 */
Pilha removeCarregador(CarregadorManager manager, int id);

#endif
