/* include/disparador.h
 *
 * TAD para representar um disparador de formas.
 * 
 * Um disparador possui:
 *  - ID único (0-9)
 *  - Posição (x, y) no espaço
 *  - Dois carregadores (esquerdo e direito) que são pilhas de formas
 *  - Uma posição de disparo temporária para a forma prestes a ser lançada
 * 
 * Operações principais:
 *  - Posicionar no espaço
 *  - Encaixar carregadores (pilhas)
 *  - Pressionar botão para selecionar forma
 *  - Disparar forma para a arena
 */

#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "../../estruturas/pilha/pilha.h"
#include "../../formas/formas/formas.h"

/* Tipo opaco para Disparador */
typedef void* Disparador;

/**
 * Cria um novo disparador.
 * @param id Identificador único (0-9)
 * @param x Coordenada x inicial
 * @param y Coordenada y inicial
 * @return Disparador criado, ou NULL em caso de erro
 */
Disparador criaDisparador(int id, double x, double y);

/**
 * Destrói um disparador, liberando memória.
 * @param d Disparador a ser destruído
 */
void destroiDisparador(Disparador d);

/**
 * Define a posição do disparador.
 * @param d Disparador
 * @param x Nova coordenada x
 * @param y Nova coordenada y
 */
void setDisparadorPosicao(Disparador d, double x, double y);

/**
 * Encaixa dois carregadores (pilhas) no disparador.
 * @param d Disparador
 * @param esquerdo Pilha do carregador esquerdo
 * @param direito Pilha do carregador direito
 */
void encaixaCarregadores(Disparador d, Pilha esquerdo, Pilha direito);

/**
 * Pressiona um botão do disparador para selecionar uma forma.
 * Remove a forma do topo do carregador correspondente e coloca
 * na posição de disparo.
 * @param d Disparador
 * @param lado Lado do botão ('e' = esquerdo, 'd' = direito)
 * @return 1 em caso de sucesso, 0 se não havia forma no carregador
 */
int pressionaBotao(Disparador d, char lado);

/**
 * Dispara a forma posicionada, aplicando um deslocamento.
 * @param d Disparador
 * @param dx Deslocamento x
 * @param dy Deslocamento y
 * @return Forma disparada (já reposicionada), ou NULL se não havia forma
 */
Forma* disparaForma(Disparador d, double dx, double dy);

/**
 * Obtém o ID do disparador.
 */
int getDisparadorId(Disparador d);

/**
 * Obtém a coordenada x do disparador.
 */
double getDisparadorX(Disparador d);

/**
 * Obtém a coordenada y do disparador.
 */
double getDisparadorY(Disparador d);

/**
 * Obtém a forma na posição de disparo (pode ser NULL).
 */
Forma* getFormaPosicaoDisparo(Disparador d);

/**
 * Obtém o carregador esquerdo.
 */
Pilha getCarregadorEsquerdo(Disparador d);

/**
 * Obtém o carregador direito.
 */
Pilha getCarregadorDireito(Disparador d);

#endif /* DISPARADOR_H */
