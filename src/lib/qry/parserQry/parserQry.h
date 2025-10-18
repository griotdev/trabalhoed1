#ifndef PARSER_QRY_H
#define PARSER_QRY_H

#include "../../argumentos/argumentHandler.h"
#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"
#include "../gameState/gameState.h"

// Lê e executa o .qry, retornando o GameState (o chamador deve destruí-lo)
GameState parseQry(Args args, Fila fila, Pilha pilha);

#endif /* PARSER_QRY_H */
