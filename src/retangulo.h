#ifndef CIRCULO_H
#define CIRCULO_H

#include <stdio.h>

typedef void* Retangulo;

/** 
 * @param id Identificador único do retângulo.
 * @param x Coordenada x da âncora do retângulo.
 * @param y Coordenada y da âncora do retângulo.
 * @param w Largura do retângulo.
 * @param h Altura do retângulo.
 * @param cb String da cor da borda.
 * @param cp String da cor do preenchimento. 
*/

Retangulo criaRetangulo(int id, float x, float y, float w, float h, char* cb, char* cp);

void freeRetangulo(Retangulo r);

#endif