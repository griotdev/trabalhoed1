#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "../../estruturas/pilha/pilha.h"
#include "../../formas/formas/formas.h"

typedef void* Disparador;

Disparador criaDisparador(int id, double x, double y);
void destroiDisparador(Disparador d);
void setDisparadorPosicao(Disparador d, double x, double y);
void encaixaCarregadores(Disparador d, Pilha esquerdo, Pilha direito);
int pressionaBotao(Disparador d, char lado);
Forma* disparaForma(Disparador d, double dx, double dy);

int getDisparadorId(Disparador d);
double getDisparadorX(Disparador d);
double getDisparadorY(Disparador d);
Forma* getFormaPosicaoDisparo(Disparador d);
Pilha getCarregadorEsquerdo(Disparador d);
Pilha getCarregadorDireito(Disparador d);

#endif /* DISPARADOR_H */
