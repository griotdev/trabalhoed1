#include <stdio.h>
#include <string.h>
#include "formaUtils.h"
#include "../../formas/circulo/circulo.h"
#include "../../formas/retangulo/retangulo.h"
#include "../../formas/linha/linha.h"
#include "../../formas/texto/texto.h"

void trocaCores(Forma *forma)
{
    if (!forma)
        return;
    TipoForma tipo = getFormaTipo(forma);
    void *dados = getFormaDados(forma);
    switch (tipo)
    {
    case TIPO_CIRCULO:
    {
        Circulo c = (Circulo)dados;
        const char *b = getCirculoCorBorda(c);
        const char *p = getCirculoCorPreenchimento(c);
        setCirculoCores(c, p, b);
        break;
    }
    case TIPO_RETANGULO:
    {
        Retangulo r = (Retangulo)dados;
        const char *b = getRetanguloCorBorda(r);
        const char *p = getRetanguloCorPreenchimento(r);
        setRetanguloCores(r, p, b);
        break;
    }
    case TIPO_TEXTO:
    {
        Texto t = (Texto)dados;
        const char *b = getTextoCorBorda(t);
        const char *p = getTextoCorPreenchimento(t);
        setTextoCores(t, p, b);
        break;
    }
    case TIPO_LINHA:
    default:
        break;
    }
}

void getFormaInfo(Forma *forma, char *buffer, size_t bufferSize)
{
    if (!forma || !buffer || bufferSize == 0)
        return;
    TipoForma tipo = getFormaTipo(forma);
    void *dados = getFormaDados(forma);
    switch (tipo)
    {
    case TIPO_CIRCULO:
    {
        Circulo c = (Circulo)dados;
        snprintf(buffer, bufferSize, "Forma %d (círculo) em (%.1f, %.1f) r=%.1f", getCirculoId(c), getCirculoX(c), getCirculoY(c), getCirculoRaio(c));
        break;
    }
    case TIPO_RETANGULO:
    {
        Retangulo r = (Retangulo)dados;
        snprintf(buffer, bufferSize, "Forma %d (retângulo) em (%.1f, %.1f) %.1fx%.1f", getRetanguloId(r), getRetanguloX(r), getRetanguloY(r), getRetanguloLargura(r), getRetanguloAltura(r));
        break;
    }
    case TIPO_LINHA:
    {
        Linha l = (Linha)dados;
        snprintf(buffer, bufferSize, "Forma %d (linha) de (%.1f, %.1f) a (%.1f, %.1f)", getLinhaId(l), getLinhaX1(l), getLinhaY1(l), getLinhaX2(l), getLinhaY2(l));
        break;
    }
    case TIPO_TEXTO:
    {
        Texto t = (Texto)dados;
        snprintf(buffer, bufferSize, "Forma %d (texto) em (%.1f, %.1f): \"%s\"", getTextoId(t), getTextoX(t), getTextoY(t), getTextoConteudo(t));
        break;
    }
    default:
        snprintf(buffer, bufferSize, "Forma desconhecida");
    }
}
