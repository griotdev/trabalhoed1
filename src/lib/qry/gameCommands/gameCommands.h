/* include/gameCommands.h
 *
 * Implementação dos comandos do arquivo .qry.
 * 
 * Cada comando modifica o estado do jogo e opcionalmente gera log.
 * Os comandos correspondem às operações do jogo de esmagamento de formas.
 */

#ifndef GAME_COMMANDS_H
#define GAME_COMMANDS_H

#include <stdio.h>
#include "../gameState/gameState.h"

/**
 * Comando pd: posiciona um disparador no espaço.
 * @param state Ponteiro para o estado do jogo
 * @param id ID do disparador (0-9)
 * @param x Coordenada x
 * @param y Coordenada y
 * @param saida Arquivo para log (pode ser NULL)
 */
void comando_pd(GameState *state, int id, double x, double y, FILE *saida);

/**
 * Comando lc: carrega n formas do chão para um carregador.
 * @param state Ponteiro para o estado do jogo
 * @param idCarregador ID do carregador
 * @param n Número de formas a carregar
 * @param saida Arquivo para log (pode ser NULL)
 */
void comando_lc(GameState *state, int idCarregador, int n, FILE *saida);

/**
 * Comando atch: anexa dois carregadores a um disparador.
 * @param state Ponteiro para o estado do jogo
 * @param idDisp ID do disparador
 * @param idCesq ID do carregador esquerdo
 * @param idCdir ID do carregador direito
 * @param saida Arquivo para log (pode ser NULL)
 */
void comando_atch(GameState *state, int idDisp, int idCesq, int idCdir, FILE *saida);

/**
 * Comando shft: desloca n formas entre carregadores do disparador.
 * @param state Ponteiro para o estado do jogo
 * @param idDisp ID do disparador
 * @param lado Lado a deslocar ('e' = esquerdo, 'd' = direito)
 * @param n Número de formas a deslocar
 * @param saida Arquivo para log (pode ser NULL)
 */
void comando_shft(GameState *state, int idDisp, char lado, int n, FILE *saida);

/**
 * Comando dsp: dispara uma forma de um disparador para a arena.
 * @param state Ponteiro para o estado do jogo
 * @param idDisp ID do disparador
 * @param dx Deslocamento x do disparo
 * @param dy Deslocamento y do disparo
 * @param tipo Tipo de botão ('e' = esquerdo, 'd' = direito)
 * @param saida Arquivo para log (pode ser NULL)
 */
void comando_dsp(GameState *state, int idDisp, char lado, double dx, double dy, char tipo, FILE *saida);

/**
 * Comando rjd: rejeita uma forma de um carregador, devolvendo ao chão.
 * @param state Ponteiro para o estado do jogo
 * @param idDisp ID do disparador
 * @param lado Lado do carregador ('e' = esquerdo, 'd' = direito)
 * @param dx Deslocamento x da rejeição
 * @param dy Deslocamento y da rejeição
 * @param ix Incremento x para múltiplas formas
 * @param iy Incremento y para múltiplas formas
 * @param saida Arquivo para log (pode ser NULL)
 */
void comando_rjd(GameState *state, int idDisp, char lado, double dx, double dy, double ix, double iy, FILE *saida);

/**
 * Comando calc: calcula colisões na arena e esmaga formas sobrepostas.
 * Formas com menor área são destruídas. Sobreviventes recebem cores das perdedoras
 * (cor complementar se a fonte for texto ou linha) e são clonadas de volta ao chão.
 * @param state Ponteiro para o estado do jogo
 * @param saida Arquivo para log (pode ser NULL)
 * @param svgPath Caminho para gerar o SVG (pode ser NULL para não gerar)
 * @param esmagadas Ponteiro para acumular formas esmagadas (pode ser NULL)
 * @param clones Ponteiro para acumular formas clonadas (pode ser NULL)
 * @param pontuacao Ponteiro para acumular pontuação (pode ser NULL)
 */
void comando_calc(GameState *state, FILE *saida, const char *svgPath,
                  int *esmagadas, int *clones, double *pontuacao);

#endif
