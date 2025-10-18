#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "colisao.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int sobreposicao(Forma *a, Forma *b) {
    if (a == NULL || b == NULL) return 0;

    TipoForma ta = getFormaTipo(a);
    TipoForma tb = getFormaTipo(b);

    if (ta == TIPO_CIRCULO && tb == TIPO_CIRCULO) {
        Circulo ca = (Circulo)getFormaDados(a);
        Circulo cb = (Circulo)getFormaDados(b);
        double dx = getCirculoX(ca) - getCirculoX(cb);
        double dy = getCirculoY(ca) - getCirculoY(cb);
        double dist = sqrt(dx*dx + dy*dy);
        return dist < (getCirculoRaio(ca) + getCirculoRaio(cb));
    }

    if (ta == TIPO_RETANGULO && tb == TIPO_RETANGULO) {
        Retangulo r1 = (Retangulo)getFormaDados(a);
        Retangulo r2 = (Retangulo)getFormaDados(b);
        double x1 = getRetanguloX(r1);
        double y1 = getRetanguloY(r1);
        double w1 = getRetanguloLargura(r1);
        double h1 = getRetanguloAltura(r1);
        double x2 = getRetanguloX(r2);
        double y2 = getRetanguloY(r2);
        double w2 = getRetanguloLargura(r2);
        double h2 = getRetanguloAltura(r2);
        int overlapX = !(x1 + w1 < x2 || x2 + w2 < x1);
        int overlapY = !(y1 + h1 < y2 || y2 + h2 < y1);
        return overlapX && overlapY;
    }

    // circle x rect
    if (ta == TIPO_CIRCULO && tb == TIPO_RETANGULO) {
        Circulo c = (Circulo)getFormaDados(a);
        Retangulo r = (Retangulo)getFormaDados(b);
        double cx = getCirculoX(c);
        double cy = getCirculoY(c);
        double rx = getRetanguloX(r);
        double ry = getRetanguloY(r);
        double rw = getRetanguloLargura(r);
        double rh = getRetanguloAltura(r);
        double nearestX = fmax(rx, fmin(cx, rx + rw));
        double nearestY = fmax(ry, fmin(cy, ry + rh));
        double dx = cx - nearestX;
        double dy = cy - nearestY;
        return (dx*dx + dy*dy) < (getCirculoRaio(c) * getCirculoRaio(c));
    }

    if (ta == TIPO_RETANGULO && tb == TIPO_CIRCULO) {
        return sobreposicao(b, a);
    }

    // For lines and texts we approximated per spec
    if (ta == TIPO_LINHA || tb == TIPO_LINHA) {
        // approximate: no collision detection for lines yet
        return 0;
    }
    if (ta == TIPO_TEXTO || tb == TIPO_TEXTO) {
        // approximate: no collision detection for texts yet
        return 0;
    }

    return 0;
}

double areaForma(Forma *f) {
    if (f == NULL) return 0.0;
    TipoForma t = getFormaTipo(f);
    if (t == TIPO_CIRCULO) {
        Circulo c = (Circulo)getFormaDados(f);
        double r = getCirculoRaio(c);
        return M_PI * r * r;
    }
    if (t == TIPO_RETANGULO) {
        Retangulo r = (Retangulo)getFormaDados(f);
        return getRetanguloLargura(r) * getRetanguloAltura(r);
    }
    if (t == TIPO_LINHA) {
        Linha l = (Linha)getFormaDados(f);
        double dx = getLinhaX2(l) - getLinhaX1(l);
        double dy = getLinhaY2(l) - getLinhaY1(l);
        double compr = sqrt(dx*dx + dy*dy);
        return 2.0 * compr;
    }
    if (t == TIPO_TEXTO) {
        // approximate area as 20.0 * length
        Texto txt = (Texto)getFormaDados(f);
        const char *s = getTextoConteudo(txt);
        return 20.0 * (s ? strlen(s) : 0);
    }
    return 0.0;
}
