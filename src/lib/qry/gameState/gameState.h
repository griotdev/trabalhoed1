/* include/gameState.h
 *
 * Gerenciamento do estado global do jogo (cópia do módulo em /qry).
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"
#include "../disparador/disparador.h"

/* Tipo opaco para o estado do jogo. */
typedef void* GameState;

GameState criaGameState(Fila chao);
void destroiGameState(GameState state);

Disparador obtemDisparador(GameState state, int id);
Pilha obtemCarregadorPorId(GameState state, int id);
Pilha removeCarregadorPorId(GameState state, int id);

Fila getChao(GameState state);
Fila getArena(GameState state);
Disparador* getDisparadores(GameState state);
int getNumDisparadores(GameState state);

#endif /* GAME_STATE_H */
