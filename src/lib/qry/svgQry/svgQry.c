#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "svgQry.h"
#include "../gameState/gameState.h"
#include "../disparador/disparador.h"
#include "../../formas/formas/formas.h"
#include "../../estruturas/fila/fila.h"
#include "../../geo/svg/svg.h"

static void desenhaDisparadores(FILE *arq, GameState state){
    Disparador *ds = getDisparadores(state); int n = getNumDisparadores(state);
    for (int i=0;i<n;i++) if (ds[i]){
        int id = getDisparadorId(ds[i]); double x = getDisparadorX(ds[i]); double y = getDisparadorY(ds[i]);
        fprintf(arq, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"8\" fill=\"black\" stroke=\"red\" stroke-width=\"2\" />\n", x, y);
        fprintf(arq, "  <text x=\"%.2f\" y=\"%.2f\" font-size=\"12\" font-weight=\"bold\" fill=\"white\">d%d</text>\n", x-6, y+4, id);
    }
}

static void atualizaBBoxForma(Forma *f, double *minX, double *minY, double *maxX, double *maxY){
    if (!f) return;
    TipoForma t = getFormaTipo(f);
    switch (t){
        case TIPO_CIRCULO: {
            Circulo c = (Circulo)getFormaDados(f);
            double x = getCirculoX(c), y = getCirculoY(c), r = getCirculoRaio(c);
            double lx = x - r, rx = x + r, ty = y - r, by = y + r;
            if (lx < *minX) *minX = lx; if (rx > *maxX) *maxX = rx;
            if (ty < *minY) *minY = ty; if (by > *maxY) *maxY = by;
            break;
        }
        case TIPO_RETANGULO: {
            Retangulo r = (Retangulo)getFormaDados(f);
            double x = getRetanguloX(r), y = getRetanguloY(r);
            double w = getRetanguloLargura(r), h = getRetanguloAltura(r);
            if (x < *minX) *minX = x; if (y < *minY) *minY = y;
            if (x + w > *maxX) *maxX = x + w; if (y + h > *maxY) *maxY = y + h;
            break;
        }
        case TIPO_LINHA: {
            Linha l = (Linha)getFormaDados(f);
            double x1 = getLinhaX1(l), y1 = getLinhaY1(l), x2 = getLinhaX2(l), y2 = getLinhaY2(l);
            double lx = fmin(x1, x2), rx = fmax(x1, x2);
            double ty = fmin(y1, y2), by = fmax(y1, y2);
            if (lx < *minX) *minX = lx; if (rx > *maxX) *maxX = rx;
            if (ty < *minY) *minY = ty; if (by > *maxY) *maxY = by;
            break;
        }
        case TIPO_TEXTO: {
            Texto txt = (Texto)getFormaDados(f);
            double x = getTextoX(txt), y = getTextoY(txt);
            double fs = getTextoFontSize(txt);
            const char *s = getTextoConteudo(txt);
            double w = (s ? strlen(s) : 0) * (fs * 0.6);
            double h = fs;
            if (x < *minX) *minX = x; if (y - h < *minY) *minY = y - h;
            if (x + w > *maxX) *maxX = x + w; if (y > *maxY) *maxY = y;
            break;
        }
        default: break;
    }
}

static void calculaBBoxState(GameState state, double *outMinX, double *outMinY, double *outMaxX, double *outMaxY, int *outTemAlgo){
    double minX = DBL_MAX, minY = DBL_MAX, maxX = -DBL_MAX, maxY = -DBL_MAX;
    int tem = 0;
    // Disparadores (considera raio de 8)
    Disparador *ds = getDisparadores(state); int n = getNumDisparadores(state);
    for (int i=0;i<n;i++) if (ds[i]){
        double x = getDisparadorX(ds[i]); double y = getDisparadorY(ds[i]);
        double lx = x - 8, rx = x + 8, ty = y - 8, by = y + 8;
        if (lx < minX) minX = lx; if (rx > maxX) maxX = rx;
        if (ty < minY) minY = ty; if (by > maxY) maxY = by; tem = 1;
    }
    // Arena
    Fila arena = getArena(state);
    if (arena && !filaVazia(arena)){
        Fila tmp = criaFila();
        while (!filaVazia(arena)){
            Forma *f = (Forma*)desenfileira(arena);
            if (f){ atualizaBBoxForma(f, &minX, &minY, &maxX, &maxY); tem = 1; enfileira(tmp, f);}    
        }
        while (!filaVazia(tmp)){ Forma *f=(Forma*)desenfileira(tmp); enfileira(arena, f);} destroiFila(tmp, NULL);
    }
    // Chão
    Fila chao = getChao(state);
    if (chao && !filaVazia(chao)){
        Fila tmp = criaFila();
        while (!filaVazia(chao)){
            Forma *f = (Forma*)desenfileira(chao);
            if (f){ atualizaBBoxForma(f, &minX, &minY, &maxX, &maxY); tem = 1; enfileira(tmp, f);}    
        }
        while (!filaVazia(tmp)){ Forma *f=(Forma*)desenfileira(tmp); enfileira(chao, f);} destroiFila(tmp, NULL);
    }
    if (outMinX) *outMinX = minX; if (outMinY) *outMinY = minY;
    if (outMaxX) *outMaxX = maxX; if (outMaxY) *outMaxY = maxY; if (outTemAlgo) *outTemAlgo = tem;
}

int svgGeraArquivoQry(const char *nomeArquivo, GameState state, int largura, int altura){
    if (!nomeArquivo || !state) return 1;
    // Calcula bounding box para ajustar canvas e aplicar margem/translate
    double minX, minY, maxX, maxY; int temAlgo = 0;
    calculaBBoxState(state, &minX, &minY, &maxX, &maxY, &temAlgo);
    const double margem = 20.0;
    double tx = 0.0, ty = 0.0; int W = largura, H = altura;
    if (temAlgo){
        double compW = (maxX - minX) + 2*margem; if (compW < 1) compW = largura;
        double compH = (maxY - minY) + 2*margem; if (compH < 1) compH = altura;
        W = (int)fmax((double)largura, compW);
        H = (int)fmax((double)altura, compH);
        tx = margem - minX; ty = margem - minY;
    }
    FILE *arq = svgCriaArquivo(nomeArquivo, W, H); if (!arq) return 1;
    fprintf(arq, "  <!-- SVG gerado a partir do processamento do .qry -->\n");
    if (temAlgo){ fprintf(arq, "  <g transform=\"translate(%.2f, %.2f)\">\n", tx, ty); }
    desenhaDisparadores(arq, state);
    fprintf(arq, "  <!-- Formas na arena -->\n");
    Fila arena = getArena(state); if (arena && !filaVazia(arena)){
    Fila tmp = criaFila(); while (!filaVazia(arena)){ Forma *f=(Forma*)desenfileira(arena); if (f){ svgEscreveForma(arq, f); enfileira(tmp, f);} }
    while (!filaVazia(tmp)){ Forma *f=(Forma*)desenfileira(tmp); enfileira(arena, f);} destroiFila(tmp, NULL);
    }
    fprintf(arq, "  <!-- Formas no chão (opacidade reduzida) -->\n");
    Fila chao = getChao(state); if (chao && !filaVazia(chao)){
    Fila tmp = criaFila(); while (!filaVazia(chao)){ Forma *f=(Forma*)desenfileira(chao); if (f){ fprintf(arq, "  <g opacity=\"0.3\">\n"); svgEscreveForma(arq, f); fprintf(arq, "  </g>\n"); enfileira(tmp, f);} }
    while (!filaVazia(tmp)){ Forma *f=(Forma*)desenfileira(tmp); enfileira(chao, f);} destroiFila(tmp, NULL);
    }
    if (temAlgo){ fprintf(arq, "  </g>\n"); }
    svgFechaArquivo(arq); return 0;
}
