#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
#include "../../formas/circulo/circulo.h"
#include "../../formas/retangulo/retangulo.h"
#include "../../formas/linha/linha.h"
#include "../../formas/texto/texto.h"

typedef struct disparador_internal
{
    int id;
    double x;
    double y;
    Pilha carregadorEsq;
    Pilha carregadorDir;
    Forma *posicaoDisparo;
} DisparadorInternal;

Disparador criaDisparador(int id, double x, double y)
{
    DisparadorInternal *d = malloc(sizeof(DisparadorInternal));
    if (!d)
    {
        fprintf(stderr, "Erro alocar disparador\n");
        return NULL;
    }
    d->id = id;
    d->x = x;
    d->y = y;
    d->carregadorEsq = NULL;
    d->carregadorDir = NULL;
    d->posicaoDisparo = NULL;
    return (Disparador)d;
}

void destroiDisparador(Disparador disparador)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    if (!d)
        return;
    if (d->carregadorEsq)
        destroiPilha(d->carregadorEsq, NULL);
    if (d->carregadorDir)
        destroiPilha(d->carregadorDir, NULL);
    free(d);
}

void setDisparadorPosicao(Disparador disparador, double x, double y)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    if (d)
    {
        d->x = x;
        d->y = y;
    }
}
void encaixaCarregadores(Disparador disparador, Pilha esquerdo, Pilha direito)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    if (d)
    {
        d->carregadorEsq = esquerdo;
        d->carregadorDir = direito;
    }
}

int pressionaBotao(Disparador disparador, char lado)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    if (!d)
        return 0;
    // Lógica invertida: botão esquerdo ('e') tira do carregador DIREITO
    // e a forma deslocada vai para o carregador ESQUERDO
    Pilha origem = (lado == 'e') ? d->carregadorDir : d->carregadorEsq;
    Pilha oposto = (lado == 'e') ? d->carregadorEsq : d->carregadorDir;
    if (!origem)
        return 0;
    if (d->posicaoDisparo && oposto)
    {
        empilha(oposto, d->posicaoDisparo);
        d->posicaoDisparo = NULL;
    }
    if (!pilhaVazia(origem))
    {
        d->posicaoDisparo = (Forma *)desempilha(origem);
        return 1;
    }
    return 0;
}

Forma *disparaForma(Disparador disparador, double dx, double dy)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    if (!d || !d->posicaoDisparo)
        return NULL;
    Forma *forma = d->posicaoDisparo;
    d->posicaoDisparo = NULL;
    TipoForma tipo = getFormaTipo(forma);
    void *dados = getFormaDados(forma);
    double nx = d->x + dx, ny = d->y + dy;
    switch (tipo)
    {
    case TIPO_CIRCULO:
        setCirculoPosicao((Circulo)dados, nx, ny);
        break;
    case TIPO_RETANGULO:
        setRetanguloPosicao((Retangulo)dados, nx, ny);
        break;
    case TIPO_LINHA:
    {
        Linha l = (Linha)dados;
        double x1 = getLinhaX1(l), y1 = getLinhaY1(l);
        setLinhaPosicao(l, nx - x1, ny - y1);
        break;
    }
    case TIPO_TEXTO:
        setTextoPosicao((Texto)dados, nx, ny);
        break;
    default:
        break;
    }
    return forma;
}

int getDisparadorId(Disparador disparador)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    return d ? d->id : -1;
}

double getDisparadorX(Disparador disparador)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    return d ? d->x : 0.0;
}

double getDisparadorY(Disparador disparador)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    return d ? d->y : 0.0;
}

Forma *getFormaPosicaoDisparo(Disparador disparador)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    return d ? d->posicaoDisparo : NULL;
}

Pilha getCarregadorEsquerdo(Disparador disparador)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    return d ? d->carregadorEsq : NULL;
}

Pilha getCarregadorDireito(Disparador disparador)
{
    DisparadorInternal *d = (DisparadorInternal *)disparador;
    return d ? d->carregadorDir : NULL;
}
