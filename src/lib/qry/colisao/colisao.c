#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "colisao.h"
#include "../../formas/circulo/circulo.h"
#include "../../formas/retangulo/retangulo.h"
#include "../../formas/linha/linha.h"
#include "../../formas/texto/texto.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double dist(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1, dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

static int retSobrepoe(Retangulo r1, Retangulo r2) { return retangulosSobrepoe(r1, r2); }

static int circCirc(Circulo c1, Circulo c2) { return dist(getCirculoX(c1), getCirculoY(c1), getCirculoX(c2), getCirculoY(c2)) < (getCirculoRaio(c1) + getCirculoRaio(c2)); }

static int circRet(Circulo c, Retangulo r)
{
    double cx = getCirculoX(c), cy = getCirculoY(c), rr = getCirculoRaio(c);
    double rx = getRetanguloX(r), ry = getRetanguloY(r), rw = getRetanguloLargura(r), rh = getRetanguloAltura(r);
    double closestX = (cx < rx) ? rx : (cx > rx + rw ? rx + rw : cx);
    double closestY = (cy < ry) ? ry : (cy > ry + rh ? ry + rh : cy);
    return dist(cx, cy, closestX, closestY) < rr;
}

static int circLinha(Circulo c, Linha l)
{
    double cx = getCirculoX(c), cy = getCirculoY(c), r = getCirculoRaio(c);
    double x1 = getLinhaX1(l), y1 = getLinhaY1(l), x2 = getLinhaX2(l), y2 = getLinhaY2(l);
    double A = cx - x1, B = cy - y1, C = x2 - x1, D = y2 - y1;
    double dot = A * C + B * D, len = C * C + D * D;
    double param = (len != 0) ? dot / len : -1;
    double xx, yy;
    if (param < 0)
    {
        xx = x1;
        yy = y1;
    }
    else if (param > 1)
    {
        xx = x2;
        yy = y2;
    }
    else
    {
        xx = x1 + param * C;
        yy = y1 + param * D;
    }
    return dist(cx, cy, xx, yy) < r;
}

static int retLinha(Retangulo r, Linha l)
{
    double x1 = getLinhaX1(l), y1 = getLinhaY1(l), x2 = getLinhaX2(l), y2 = getLinhaY2(l);
    double rx = getRetanguloX(r), ry = getRetanguloY(r), rw = getRetanguloLargura(r), rh = getRetanguloAltura(r);
    int p1 = (x1 >= rx && x1 <= rx + rw && y1 >= ry && y1 <= ry + rh);
    int p2 = (x2 >= rx && x2 <= rx + rw && y2 >= ry && y2 <= ry + rh);
    if (p1 || p2)
        return 1;
    return 0;
}

int verificaSobreposicao(Forma *f1, Forma *f2)
{
    if (!f1 || !f2)
        return 0;
    TipoForma t1 = getFormaTipo(f1), t2 = getFormaTipo(f2);
    void *d1 = getFormaDados(f1), *d2 = getFormaDados(f2);
    if (t1 == TIPO_CIRCULO && t2 == TIPO_CIRCULO)
        return circCirc((Circulo)d1, (Circulo)d2);
    if (t1 == TIPO_CIRCULO && t2 == TIPO_RETANGULO)
        return circRet((Circulo)d1, (Retangulo)d2);
    if (t1 == TIPO_RETANGULO && t2 == TIPO_CIRCULO)
        return circRet((Circulo)d2, (Retangulo)d1);
    if (t1 == TIPO_RETANGULO && t2 == TIPO_RETANGULO)
        return retSobrepoe((Retangulo)d1, (Retangulo)d2);
    if (t1 == TIPO_CIRCULO && t2 == TIPO_LINHA)
        return circLinha((Circulo)d1, (Linha)d2);
    if (t1 == TIPO_LINHA && t2 == TIPO_CIRCULO)
        return circLinha((Circulo)d2, (Linha)d1);
    if (t1 == TIPO_RETANGULO && t2 == TIPO_LINHA)
        return retLinha((Retangulo)d1, (Linha)d2);
    if (t1 == TIPO_LINHA && t2 == TIPO_RETANGULO)
        return retLinha((Retangulo)d2, (Linha)d1);
    return 0;
}

double calculaArea(Forma *f)
{
    if (!f)
        return 0.0;
    TipoForma t = getFormaTipo(f);
    void *d = getFormaDados(f);
    switch (t)
    {
    case TIPO_CIRCULO:
    {
        double r = getCirculoRaio((Circulo)d);
        return M_PI * r * r;
    }
    case TIPO_RETANGULO:
    {
        return getRetanguloLargura((Retangulo)d) * getRetanguloAltura((Retangulo)d);
    }
    case TIPO_LINHA:
    {
        double x1 = getLinhaX1((Linha)d), y1 = getLinhaY1((Linha)d), x2 = getLinhaX2((Linha)d), y2 = getLinhaY2((Linha)d);
        double c = dist(x1, y1, x2, y2);
        return 2.0 * c;
    }
    case TIPO_TEXTO:
    {
        const char *s = getTextoConteudo((Texto)d);
        return 20.0 * strlen(s);
    }
    default:
        return 0.0;
    }
}
