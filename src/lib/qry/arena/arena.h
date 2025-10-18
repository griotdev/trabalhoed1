#ifndef ARENA_H
#define ARENA_H

#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"
#include "../../formas/formas/formas.h"

typedef void* Disparador;
typedef void* Carregador;
typedef void* TabelaDisparadores;
typedef void* TabelaCarregadores;

TabelaDisparadores criaTabelaDisparadores(void);

void destroiTabelaDisparadores(TabelaDisparadores *tabela);

Disparador criaDisparador(const char *id, double x, double y);

void destroiDisparador(Disparador *disp);

int adicionaDisparador(TabelaDisparadores tabela, Disparador disp);

Disparador buscaDisparador(TabelaDisparadores tabela, const char *id);

void getDisparadorPosicao(Disparador disp, double *x, double *y);

const char* getDisparadorId(Disparador disp);

void setDisparadorCarregadores(Disparador disp, Carregador esq, Carregador dir);

Carregador getDisparadorCarregadorEsq(Disparador disp);

Carregador getDisparadorCarregadorDir(Disparador disp);

void setDisparadorPosicaoDisparo(Disparador disp, Forma *forma);

Forma* getDisparadorPosicaoDisparo(Disparador disp);

TabelaCarregadores criaTabelaCarregadores(void);

void destroiTabelaCarregadores(TabelaCarregadores *tabela);

Carregador criaCarregador(const char *id);

void destroiCarregador(Carregador *carr);

int adicionaCarregador(TabelaCarregadores tabela, Carregador carr);

Carregador buscaCarregador(TabelaCarregadores tabela, const char *id);

const char* getCarregadorId(Carregador carr);

Pilha* getCarregadorPilha(Carregador carr);

#endif
