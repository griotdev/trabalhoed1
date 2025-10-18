#include <stdio.h>
#include <stdlib.h>
#include "formas.h"

struct forma {
    TipoForma tipo;
    void *dados;
};

Forma* criaForma(TipoForma tipo, void *dados) {
    Forma *f = (Forma*)malloc(sizeof(Forma));
    if (f == NULL) {
        fprintf(stderr, "Erro ao alocar memória para forma genérica.\n");
        return NULL;
    }
    
    f->tipo = tipo;
    f->dados = dados;
    
    return f;
}

TipoForma getFormaTipo(Forma *f) {
    return f ? f->tipo : -1;
}

void* getFormaDados(Forma *f) {
    return f ? f->dados : NULL;
}

int getFormaId(Forma *f) {
    if (f == NULL || f->dados == NULL) {
        return -1;
    }
    
    switch (f->tipo) {
        case TIPO_CIRCULO:
            return getCirculoId((Circulo*)f->dados);
        case TIPO_RETANGULO:
            return getRetanguloId((Retangulo*)f->dados);
        case TIPO_LINHA:
            return getLinhaId((Linha*)f->dados);
        case TIPO_TEXTO:
            return getTextoId((Texto*)f->dados);
        default:
            return -1;
    }
}

void destroiForma(Forma *forma) {
    if (forma == NULL) {
        return;
    }
    
    if (forma->dados != NULL) {
        switch (forma->tipo) {
            case TIPO_CIRCULO:
                destroiCirculo((Circulo*)forma->dados);
                break;
            case TIPO_RETANGULO:
                destroiRetangulo((Retangulo*)forma->dados);
                break;
            case TIPO_LINHA:
                destroiLinha((Linha*)forma->dados);
                break;
            case TIPO_TEXTO:
                destroiTexto((Texto*)forma->dados);
                break;
        }
    }
    
    free(forma);
}

void setFormaPosicao(Forma *forma, double x, double y) {
    if (forma == NULL || forma->dados == NULL) {
        return;
    }
    
    switch (forma->tipo) {
        case TIPO_CIRCULO:
            setCirculoCentro((Circulo*)forma->dados, x, y);
            break;
        case TIPO_RETANGULO:
            setRetanguloAncora((Retangulo*)forma->dados, x, y);
            break;
        case TIPO_LINHA:
            {
                double x1, y1, x2, y2;
                getLinhaP1((Linha*)forma->dados, &x1, &y1);
                getLinhaP2((Linha*)forma->dados, &x2, &y2);
                double dx = x2 - x1;
                double dy = y2 - y1;
                setLinhaP1((Linha*)forma->dados, x, y);
                setLinhaP2((Linha*)forma->dados, x + dx, y + dy);
            }
            break;
        case TIPO_TEXTO:
            setTextoAncora((Texto*)forma->dados, x, y);
            break;
    }
}
