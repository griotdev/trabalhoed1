/* src/lib/qry/formaUtils/formaArena.h
 *
 * Estrutura para armazenar formas na arena com informações de disparo
 * para visualização de trajetórias e anotações no SVG.
 */

#ifndef FORMA_ARENA_H
#define FORMA_ARENA_H

#include "../../formas/formas/formas.h"
#include <stdbool.h>

/* Tipo opaco para FormaArena */
typedef void* FormaArena;

/**
 * Cria uma FormaArena com informações de disparo.
 * @param forma Forma disparada
 * @param disparadorX Posição X do disparador
 * @param disparadorY Posição Y do disparador
 * @param anotada Se deve desenhar trajetória no SVG
 * @return FormaArena criada, ou NULL em caso de erro
 */
FormaArena criaFormaArena(Forma *forma, double disparadorX, double disparadorY, bool anotada);

/**
 * Destroi uma FormaArena (mas NÃO destroi a forma contida).
 * @param fa FormaArena a ser destruída
 */
void destroiFormaArena(FormaArena fa);

/**
 * Obtém a forma contida na FormaArena.
 */
Forma* getFormaArenaForma(FormaArena fa);

/**
 * Obtém a posição X do disparador.
 */
double getFormaArenaDisparadorX(FormaArena fa);

/**
 * Obtém a posição Y do disparador.
 */
double getFormaArenaDisparadorY(FormaArena fa);

/**
 * Verifica se a forma está anotada (deve desenhar trajetória).
 */
bool getFormaArenaAnotada(FormaArena fa);

#endif
