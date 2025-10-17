#ifndef PARSER_QRY_H
#define PARSER_QRY_H

#include "../../argumentos/argumentHandler.h"
#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"

typedef void* Arena;

Arena criaArena(void);

void destroiArena(Arena *arena);

int parseQry(Args args, Fila *filaChao, const char *caminhoSvgBase);

#endif
