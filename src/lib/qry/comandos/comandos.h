#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdio.h>
#include "../parserQry/parserQry.h"

typedef void* Disparador;
typedef void* Carregador;

int exec_comando(char *linha, Arena arena, FILE *saidaTxt);

int exec_pd(char *id, double x, double y, Arena arena, FILE *saidaTxt);

int exec_lc(char *idCarregador, int n, Arena arena, FILE *saidaTxt);

int exec_atch(char *idDisparador, char *idCargaEsq, char *idCargaDir, Arena arena, FILE *saidaTxt);

int exec_shft(char *idDisparador, char direcao, int n, Arena arena, FILE *saidaTxt);

int exec_dsp(char *idDisparador, double dx, double dy, char modo, Arena arena, FILE *saidaTxt);

int exec_rjd(char *idDisparador, char direcao, double dx, double dy, double ix, double iy, Arena arena, FILE *saidaTxt);

int exec_calc(Arena arena, FILE *saidaTxt);

#endif
