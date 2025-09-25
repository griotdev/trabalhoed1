#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>

typedef void* Circulo;

/** 
 * @param id (int) Identificador único do círculo.
 * @param x (float) Coordenada x do centro do círculo.
 * @param y (float) Coordenada y do centro do círculo.
 * @param r (float) Raio do círculo.
 * @param cb (string) Cor da borda em ColorHex, #RRGGBB.
 * @param cp (string) Cor do preenchimento em ColorHex, #RRGGBB. 
*/

Circulo criaCirculo(int id, float x, float y, float r, char* cb, char* cp);

float CalculaCirculoArea();

int getCirculoId();
float getCirculoX();
float getCirculoY();
float getCirculoRaio();
char* getCirculoCB();
char* getCirculoCP();

/**
 * Ambas funções abaixo servem para mudar as cores de um círculo já existente.
 * Necessário para quando as figuras se sobrepuserem e por via de regra, alterar a cor delas.
*/ 
void setCirculoBorda(Circulo c, char* cb);
void setCirculoPreenchimento(Circulo c, char* cp);

//Libera a memória alocada para o círculo.
void freeCirculo(Circulo c);

#endif