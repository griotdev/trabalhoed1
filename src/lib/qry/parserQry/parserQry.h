/* include/parserQry.h
 *
 * Módulo responsável por ler e interpretar arquivos .qry.
 * 
 * Os arquivos .qry contêm comandos para manipular formas em um ambiente de jogo:
 *  - pd: posiciona disparador
 *  - lc: carrega formas do chão para um carregador
 *  - atch: anexa carregadores a um disparador
 *  - shft: desloca formas entre carregadores
 *  - dsp: dispara uma forma
 *  - rjd: rejeita forma de um carregador
 *  - calc: calcula colisões e esmagamentos na arena
 * 
 * O parser executa os comandos e gera:
 *  - Arquivo de log .txt com o resultado das operações
 *  - GameState atualizado para renderização SVG
 */

#ifndef PARSER_QRY_H
#define PARSER_QRY_H

#include "../../argumentos/argumentHandler.h"
#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"
#include "../gameState/gameState.h"

/**
 * Lê e executa comandos de um arquivo .qry.
 * 
 * @param args Estrutura com argumentos do programa (contém caminhos dos arquivos)
 * @param fila Fila com as formas carregadas do .geo (chão do jogo)
 * @param pilha Pilha auxiliar para processamento
 * @return GameState atualizado após execução dos comandos, ou NULL em caso de erro
 * 
 * Observações:
 *  - Gera arquivo de log (geoBase)-(qryBase).txt no diretório de saída
 *  - O GameState retornado deve ser liberado com destroiGameState()
 *  - A fila de entrada não é modificada diretamente
 */
GameState parseQry(Args args, Fila fila, Pilha pilha);

#endif /* PARSER_QRY_H */
