/* src/lib/qry/gameState/gameState.c
 * Implementação replicada do módulo /qry/gameState.
 */

#include <stdio.h>
#include <stdlib.h>
#include "gameState.h"
#include "../carregadorManager/carregadorManager.h"

#define MAX_DISPARADORES 100

typedef struct game_state_internal
{
    Fila chao;
    Fila arena;
    CarregadorManager carregadores;
    Disparador disparadores[MAX_DISPARADORES];
    int numDisparadores;
} GameStateInternal;

GameState criaGameState(Fila chao)
{
    GameStateInternal *state = malloc(sizeof(GameStateInternal));
    if (!state)
    {
        fprintf(stderr, "Erro ao alocar GameState\n");
        exit(EXIT_FAILURE);
    }
    state->chao = chao;
    state->arena = criaFila();
    state->carregadores = criaCarregadorManager();
    state->numDisparadores = 0;
    for (int i = 0; i < MAX_DISPARADORES; i++)
        state->disparadores[i] = NULL;
    return (GameState)state;
}

void destroiGameState(GameState gameState)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    if (!state)
        return;

    // Arena agora contém FormaArena wrappers
    while (!filaVazia(state->arena))
    {
        void *item = desenfileira(state->arena);
        // Pode ser NULL, FormaArena ou Forma (transição)
        // Tentamos ambos para compatibilidade
        if (item && state->chao)
            enfileira(state->chao, item);
    }
    destroiFila(state->arena, NULL);

    for (int i = 0; i < state->numDisparadores; i++)
    {
        if (state->disparadores[i])
        {
            Disparador d = state->disparadores[i];
            Forma *formaDisparo = getFormaPosicaoDisparo(d);
            if (formaDisparo && state->chao)
                enfileira(state->chao, formaDisparo);
            Pilha cesq = getCarregadorEsquerdo(d);
            Pilha cdir = getCarregadorDireito(d);
            if (cesq)
            {
                while (!pilhaVazia(cesq))
                {
                    void *f = desempilha(cesq);
                    if (f && state->chao)
                        enfileira(state->chao, f);
                }
            }
            if (cdir)
            {
                while (!pilhaVazia(cdir))
                {
                    void *f = desempilha(cdir);
                    if (f && state->chao)
                        enfileira(state->chao, f);
                }
            }
        }
    }

    for (int i = 0; i < state->numDisparadores; i++)
    {
        if (state->disparadores[i])
            destroiDisparador(state->disparadores[i]);
    }

    destroiCarregadorManager(state->carregadores);
    free(state);
}

static int buscaIndiceDisparador(GameStateInternal *state, int id)
{
    for (int i = 0; i < state->numDisparadores; i++)
    {
        if (state->disparadores[i] && getDisparadorId(state->disparadores[i]) == id)
            return i;
    }
    return -1;
}

Disparador obtemDisparador(GameState gameState, int id)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    if (!state)
        return NULL;
    int idx = buscaIndiceDisparador(state, id);
    if (idx >= 0)
        return state->disparadores[idx];
    if (state->numDisparadores >= MAX_DISPARADORES)
    {
        fprintf(stderr, "Max disparadores excedido\n");
        return NULL;
    }
    Disparador novo = criaDisparador(id, 0.0, 0.0);
    state->disparadores[state->numDisparadores++] = novo;
    return novo;
}

Pilha obtemCarregadorPorId(GameState gameState, int id)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    if (!state)
        return NULL;
    return obtemCarregador(state->carregadores, id);
}

Pilha removeCarregadorPorId(GameState gameState, int id)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    if (!state)
        return NULL;
    return removeCarregador(state->carregadores, id);
}

Fila getChao(GameState gameState)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    return state ? state->chao : NULL;
}

Fila getArena(GameState gameState)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    return state ? state->arena : NULL;
}

Disparador *getDisparadores(GameState gameState)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    return state ? state->disparadores : NULL;
}

int getNumDisparadores(GameState gameState)
{
    GameStateInternal *state = (GameStateInternal *)gameState;
    return state ? state->numDisparadores : 0;
}
