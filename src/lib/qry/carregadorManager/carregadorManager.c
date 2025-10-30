#include <stdio.h>
#include <stdlib.h>
#include "carregadorManager.h"
#include "../../estruturas/pilha/pilha.h"

#define MAX_CARREGADORES 100

typedef struct
{
    int id;
    Pilha pilha;
} EntradaCarregador;

typedef struct carregador_manager_internal
{
    EntradaCarregador entradas[MAX_CARREGADORES];
    int numCarregadores;
} CarregadorManagerInternal;

CarregadorManager criaCarregadorManager()
{
    CarregadorManagerInternal *manager = malloc(sizeof(CarregadorManagerInternal));
    if (!manager)
    {
        fprintf(stderr, "Erro alocar CarregadorManager\n");
        exit(EXIT_FAILURE);
    }
    manager->numCarregadores = 0;
    for (int i = 0; i < MAX_CARREGADORES; i++)
    {
        manager->entradas[i].id = -1;
        manager->entradas[i].pilha = NULL;
    }
    return (CarregadorManager)manager;
}

void destroiCarregadorManager(CarregadorManager m)
{
    CarregadorManagerInternal *manager = (CarregadorManagerInternal *)m;
    if (!manager)
        return;
    for (int i = 0; i < manager->numCarregadores; i++)
    {
        if (manager->entradas[i].pilha)
            destroiPilha(manager->entradas[i].pilha, NULL);
    }
    free(manager);
}

static int buscaIndice(CarregadorManagerInternal *manager, int id)
{
    for (int i = 0; i < manager->numCarregadores; i++)
    {
        if (manager->entradas[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

Pilha obtemCarregador(CarregadorManager m, int id)
{
    CarregadorManagerInternal *manager = (CarregadorManagerInternal *)m;
    if (!manager)
        return NULL;
    int idx = buscaIndice(manager, id);
    if (idx >= 0)
        return manager->entradas[idx].pilha;
    if (manager->numCarregadores >= MAX_CARREGADORES)
    {
        fprintf(stderr, "Max carregadores excedido\n");
        return NULL;
    }
    Pilha p = criaPilha();
    manager->entradas[manager->numCarregadores].id = id;
    manager->entradas[manager->numCarregadores].pilha = p;
    manager->numCarregadores++;
    return p;
}

Pilha removeCarregador(CarregadorManager m, int id)
{
    CarregadorManagerInternal *manager = (CarregadorManagerInternal *)m;
    if (!manager)
        return NULL;
    int idx = buscaIndice(manager, id);
    if (idx < 0)
        return NULL;
    Pilha p = manager->entradas[idx].pilha;
    for (int i = idx; i < manager->numCarregadores - 1; i++)
    {
        manager->entradas[i] = manager->entradas[i + 1];
    }
    manager->numCarregadores--;
    manager->entradas[manager->numCarregadores].id = -1;
    manager->entradas[manager->numCarregadores].pilha = NULL;
    return p;
}
