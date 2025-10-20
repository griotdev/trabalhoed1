/* include/gameState.h
 *
 * Gerenciamento do estado global do jogo.
 * 
 * O GameState mantém:
 *  - Chão: fila com as formas disponíveis para uso
 *  - Arena: fila com formas disparadas (aguardando cálculo de colisões)
 *  - Disparadores: array de disparadores posicionados no espaço
 *  - Carregadores: gerenciador de pilhas de formas
 * 
 * O estado é criado a partir da fila de formas do .geo e é modificado
 * pelos comandos do .qry. Ao final, deve ser destruído para liberar recursos.
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"
#include "../disparador/disparador.h"

/* Tipo opaco para o estado do jogo. */
typedef void* GameState;

/**
 * Cria um novo estado de jogo.
 * @param chao Fila com as formas disponíveis (não é copiada, apenas referenciada)
 * @return GameState criado, ou NULL em caso de erro
 */
GameState criaGameState(Fila chao);

/**
 * Destrói o estado do jogo, liberando toda memória alocada.
 * Devolve formas retidas (arena e carregadores) ao chão.
 * @param state Estado a ser destruído
 */
void destroiGameState(GameState state);

/**
 * Obtém um disparador pelo seu ID.
 * @param state Estado do jogo
 * @param id ID do disparador (0-9)
 * @return Disparador correspondente, ou NULL se não existir
 */
Disparador obtemDisparador(GameState state, int id);

/**
 * Obtém um carregador pelo seu ID.
 * @param state Estado do jogo
 * @param id ID do carregador
 * @return Pilha do carregador, ou NULL se não existir
 */
Pilha obtemCarregadorPorId(GameState state, int id);

/**
 * Remove e retorna um carregador pelo ID.
 * @param state Estado do jogo
 * @param id ID do carregador
 * @return Pilha do carregador removido, ou NULL se não existir
 */
Pilha removeCarregadorPorId(GameState state, int id);

/**
 * Obtém a fila do chão (formas disponíveis).
 * @param state Estado do jogo
 * @return Fila do chão
 */
Fila getChao(GameState state);

/**
 * Obtém a fila da arena (formas disparadas).
 * @param state Estado do jogo
 * @return Fila da arena
 */
Fila getArena(GameState state);

/**
 * Obtém o array de disparadores.
 * @param state Estado do jogo
 * @return Array de disparadores
 */
Disparador* getDisparadores(GameState state);

/**
 * Obtém o número de disparadores disponíveis.
 * @param state Estado do jogo
 * @return Número de disparadores (máximo 10)
 */
int getNumDisparadores(GameState state);

#endif /* GAME_STATE_H */
