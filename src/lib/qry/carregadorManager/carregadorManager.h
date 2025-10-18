#ifndef CARREGADOR_MANAGER_H
#define CARREGADOR_MANAGER_H

#include "../../estruturas/pilha/pilha.h"

typedef void* CarregadorManager;

CarregadorManager criaCarregadorManager();
void destroiCarregadorManager(CarregadorManager manager);
Pilha obtemCarregador(CarregadorManager manager, int id);
Pilha removeCarregador(CarregadorManager manager, int id);

#endif
