#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arena.h"

// Forward declaration for cleanup
static void liberaFormaVoid(void *f) {
    if (f != NULL) {
        destroiForma((Forma*)f);
    }
}

typedef struct disparador_node {
    char *id;
    double x;
    double y;
    Carregador carregadorEsq;
    Carregador carregadorDir;
    Forma *posicaoDisparo;
    struct disparador_node *prox;
} DisparadorNode;

typedef struct {
    DisparadorNode *head;
} TabelaDisparadoresInternal;

typedef struct carregador_node {
    char *id;
    Pilha *pilha;
    struct carregador_node *prox;
} CarregadorNode;

typedef struct {
    CarregadorNode *head;
} TabelaCarregadoresInternal;

TabelaDisparadores criaTabelaDisparadores(void) {
    TabelaDisparadoresInternal *tabela = (TabelaDisparadoresInternal*)malloc(sizeof(TabelaDisparadoresInternal));
    if (tabela == NULL) {
        return NULL;
    }
    tabela->head = NULL;
    return (TabelaDisparadores)tabela;
}

void destroiTabelaDisparadores(TabelaDisparadores *tabela) {
    if (tabela == NULL || *tabela == NULL) {
        return;
    }
    
    TabelaDisparadoresInternal *t = (TabelaDisparadoresInternal*)(*tabela);
    DisparadorNode *atual = t->head;
    
    while (atual != NULL) {
        DisparadorNode *prox = atual->prox;
        if (atual->id != NULL) {
            free(atual->id);
        }
        free(atual);
        atual = prox;
    }
    
    free(t);
    *tabela = NULL;
}

Disparador criaDisparador(const char *id, double x, double y) {
    if (id == NULL) {
        return NULL;
    }
    
    DisparadorNode *disp = (DisparadorNode*)malloc(sizeof(DisparadorNode));
    if (disp == NULL) {
        return NULL;
    }
    
    disp->id = (char*)malloc(strlen(id) + 1);
    if (disp->id == NULL) {
        free(disp);
        return NULL;
    }
    strcpy(disp->id, id);
    
    disp->x = x;
    disp->y = y;
    disp->carregadorEsq = NULL;
    disp->carregadorDir = NULL;
    disp->posicaoDisparo = NULL;
    disp->prox = NULL;
    
    return (Disparador)disp;
}

void destroiDisparador(Disparador *disp) {
    if (disp == NULL || *disp == NULL) {
        return;
    }
    
    DisparadorNode *d = (DisparadorNode*)(*disp);
    if (d->id != NULL) {
        free(d->id);
    }
    free(d);
    *disp = NULL;
}

int adicionaDisparador(TabelaDisparadores tabela, Disparador disp) {
    if (tabela == NULL || disp == NULL) {
        return 1;
    }
    
    TabelaDisparadoresInternal *t = (TabelaDisparadoresInternal*)tabela;
    DisparadorNode *d = (DisparadorNode*)disp;
    
    DisparadorNode *existente = t->head;
    while (existente != NULL) {
        if (strcmp(existente->id, d->id) == 0) {
            existente->x = d->x;
            existente->y = d->y;
            free(d->id);
            free(d);
            return 0;
        }
        existente = existente->prox;
    }
    
    d->prox = t->head;
    t->head = d;
    
    return 0;
}

Disparador buscaDisparador(TabelaDisparadores tabela, const char *id) {
    if (tabela == NULL || id == NULL) {
        return NULL;
    }
    
    TabelaDisparadoresInternal *t = (TabelaDisparadoresInternal*)tabela;
    DisparadorNode *atual = t->head;
    
    while (atual != NULL) {
        if (strcmp(atual->id, id) == 0) {
            return (Disparador)atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}

void getDisparadorPosicao(Disparador disp, double *x, double *y) {
    if (disp == NULL) {
        return;
    }
    
    DisparadorNode *d = (DisparadorNode*)disp;
    if (x != NULL) *x = d->x;
    if (y != NULL) *y = d->y;
}

const char* getDisparadorId(Disparador disp) {
    if (disp == NULL) {
        return NULL;
    }
    DisparadorNode *d = (DisparadorNode*)disp;
    return d->id;
}

void setDisparadorCarregadores(Disparador disp, Carregador esq, Carregador dir) {
    if (disp == NULL) {
        return;
    }
    DisparadorNode *d = (DisparadorNode*)disp;
    d->carregadorEsq = esq;
    d->carregadorDir = dir;
}

Carregador getDisparadorCarregadorEsq(Disparador disp) {
    if (disp == NULL) {
        return NULL;
    }
    DisparadorNode *d = (DisparadorNode*)disp;
    return d->carregadorEsq;
}

Carregador getDisparadorCarregadorDir(Disparador disp) {
    if (disp == NULL) {
        return NULL;
    }
    DisparadorNode *d = (DisparadorNode*)disp;
    return d->carregadorDir;
}

void setDisparadorPosicaoDisparo(Disparador disp, Forma *forma) {
    if (disp == NULL) {
        return;
    }
    DisparadorNode *d = (DisparadorNode*)disp;
    d->posicaoDisparo = forma;
}

Forma* getDisparadorPosicaoDisparo(Disparador disp) {
    if (disp == NULL) {
        return NULL;
    }
    DisparadorNode *d = (DisparadorNode*)disp;
    return d->posicaoDisparo;
}

TabelaCarregadores criaTabelaCarregadores(void) {
    TabelaCarregadoresInternal *tabela = (TabelaCarregadoresInternal*)malloc(sizeof(TabelaCarregadoresInternal));
    if (tabela == NULL) {
        return NULL;
    }
    tabela->head = NULL;
    return (TabelaCarregadores)tabela;
}

void destroiTabelaCarregadores(TabelaCarregadores *tabela) {
    if (tabela == NULL || *tabela == NULL) {
        return;
    }
    
    TabelaCarregadoresInternal *t = (TabelaCarregadoresInternal*)(*tabela);
    CarregadorNode *atual = t->head;
    
    while (atual != NULL) {
        CarregadorNode *prox = atual->prox;
        if (atual->id != NULL) {
            free(atual->id);
        }
        if (atual->pilha != NULL) {
            // Destroy forms remaining in the carregador
            destroiPilha(atual->pilha, liberaFormaVoid);
        }
        free(atual);
        atual = prox;
    }
    
    free(t);
    *tabela = NULL;
}

Carregador criaCarregador(const char *id) {
    if (id == NULL) {
        return NULL;
    }
    
    CarregadorNode *carr = (CarregadorNode*)malloc(sizeof(CarregadorNode));
    if (carr == NULL) {
        return NULL;
    }
    
    carr->id = (char*)malloc(strlen(id) + 1);
    if (carr->id == NULL) {
        free(carr);
        return NULL;
    }
    strcpy(carr->id, id);
    
    carr->pilha = criaPilha();
    if (carr->pilha == NULL) {
        free(carr->id);
        free(carr);
        return NULL;
    }
    
    carr->prox = NULL;
    
    return (Carregador)carr;
}

void destroiCarregador(Carregador *carr) {
    if (carr == NULL || *carr == NULL) {
        return;
    }
    
    CarregadorNode *c = (CarregadorNode*)(*carr);
    if (c->id != NULL) {
        free(c->id);
    }
    if (c->pilha != NULL) {
        destroiPilha(c->pilha, NULL);
    }
    free(c);
    *carr = NULL;
}

int adicionaCarregador(TabelaCarregadores tabela, Carregador carr) {
    if (tabela == NULL || carr == NULL) {
        return 1;
    }
    
    TabelaCarregadoresInternal *t = (TabelaCarregadoresInternal*)tabela;
    CarregadorNode *c = (CarregadorNode*)carr;
    
    CarregadorNode *existente = t->head;
    while (existente != NULL) {
        if (strcmp(existente->id, c->id) == 0) {
            return 1;
        }
        existente = existente->prox;
    }
    
    c->prox = t->head;
    t->head = c;
    
    return 0;
}

Carregador buscaCarregador(TabelaCarregadores tabela, const char *id) {
    if (tabela == NULL || id == NULL) {
        return NULL;
    }
    
    TabelaCarregadoresInternal *t = (TabelaCarregadoresInternal*)tabela;
    CarregadorNode *atual = t->head;
    
    while (atual != NULL) {
        if (strcmp(atual->id, id) == 0) {
            return (Carregador)atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}

const char* getCarregadorId(Carregador carr) {
    if (carr == NULL) {
        return NULL;
    }
    CarregadorNode *c = (CarregadorNode*)carr;
    return c->id;
}

Pilha* getCarregadorPilha(Carregador carr) {
    if (carr == NULL) {
        return NULL;
    }
    CarregadorNode *c = (CarregadorNode*)carr;
    return c->pilha;
}
