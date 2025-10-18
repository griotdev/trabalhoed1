#ifndef PARSER_QRY_H
#define PARSER_QRY_H

#include "../../argumentos/argumentHandler.h"
#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"

typedef void* Arena;
typedef void* TabelaDisparadores;
typedef void* TabelaCarregadores;

Arena criaArena(void);

void destroiArena(Arena *arena);

int parseQry(Args args, Fila *filaChao, const char *caminhoSvgBase);

TabelaDisparadores getArenaDisparadores(Arena arena);

TabelaCarregadores getArenaCarregadores(Arena arena);

Fila* getArenaChao(Arena arena);

Fila* getArenaFormasNaArena(Arena arena);

void incrementaNumDisparos(Arena arena);

void incrementaNumEsmagadas(Arena arena);

void incrementaNumClonadas(Arena arena);

void adicionaPontuacao(Arena arena, double pontos);

int getArenaNumInstrucoes(Arena arena);

int getArenaNumDisparos(Arena arena);

int getArenaNumEsmagadas(Arena arena);

int getArenaNumClonadas(Arena arena);

double getArenaPontuacao(Arena arena);

#endif
