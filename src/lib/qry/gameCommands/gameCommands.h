#ifndef GAME_COMMANDS_H
#define GAME_COMMANDS_H

#include <stdio.h>
#include "../gameState/gameState.h"

void comando_pd(GameState *state, int id, double x, double y, FILE *saida);
void comando_lc(GameState *state, int idCarregador, int n, FILE *saida);
void comando_atch(GameState *state, int idDisp, int idCesq, int idCdir, FILE *saida);
void comando_shft(GameState *state, int idDisp, char lado, int n, FILE *saida);
void comando_dsp(GameState *state, int idDisp, double dx, double dy, char tipo, FILE *saida);
void comando_rjd(GameState *state, int idDisp, char lado, double dx, double dy, double ix, double iy, FILE *saida);
void comando_calc(GameState *state, FILE *saida);

#endif
