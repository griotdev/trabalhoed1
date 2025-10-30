#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "colorRules.h"
#include "../../formas/circulo/circulo.h"
#include "../../formas/retangulo/retangulo.h"
#include "../../formas/linha/linha.h"
#include "../../formas/texto/texto.h"

// Suporta basicamente cores RGB em formato #RRGGBB. Mantém outras strings inalteradas.
static int invertHexColor(const char *hex, char out[20])
{
    if (!hex)
        return 0;
    size_t n = strlen(hex);
    if (n != 7 || hex[0] != '#')
        return 0;
    // valida
    for (int i = 1; i < 7; i++)
    {
        if (!isxdigit((unsigned char)hex[i]))
            return 0;
    }
    // parse e complementa: 255 - componente
    unsigned r, g, b;
    if (sscanf(hex + 1, "%02x%02x%02x", &r, &g, &b) != 3)
        return 0;
    unsigned cr = 255 - r, cg = 255 - g, cb = 255 - b;
    snprintf(out, 20, "#%02X%02X%02X", cr, cg, cb);
    return 1;
}

static const char *extraiCorBase(Forma *f)
{
    if (!f)
        return NULL;
    TipoForma t = getFormaTipo(f);
    void *d = getFormaDados(f);
    switch (t)
    {
    case TIPO_CIRCULO:
        return getCirculoCorPreenchimento((Circulo)d);
    case TIPO_RETANGULO:
        return getRetanguloCorPreenchimento((Retangulo)d);
    case TIPO_TEXTO:
        return getTextoCorPreenchimento((Texto)d);
    case TIPO_LINHA:
        return getLinhaCor((Linha)d);
    default:
        return NULL;
    }
}

static void aplicaCorDestino(Forma *destino, const char *fill, const char *stroke)
{
    TipoForma t = getFormaTipo(destino);
    void *d = getFormaDados(destino);
    switch (t)
    {
    case TIPO_CIRCULO:
        setCirculoCores((Circulo)d, stroke ? stroke : getCirculoCorBorda((Circulo)d), fill ? fill : getCirculoCorPreenchimento((Circulo)d));
        break;
    case TIPO_RETANGULO:
        setRetanguloCores((Retangulo)d, stroke ? stroke : getRetanguloCorBorda((Retangulo)d), fill ? fill : getRetanguloCorPreenchimento((Retangulo)d));
        break;
    case TIPO_TEXTO:
        setTextoCores((Texto)d, stroke ? stroke : getTextoCorBorda((Texto)d), fill ? fill : getTextoCorPreenchimento((Texto)d));
        break;
    case TIPO_LINHA: /* Sem setter de cor para linha neste TAD; manter como está */
        break;
    default:
        break;
    }
}

int aplicaCorDeFonte(Forma *destino, Forma *fonte)
{
    if (!destino || !fonte)
        return 0;
    const char *corSrc = extraiCorBase(fonte);
    if (!corSrc || strlen(corSrc) == 0)
        return 0;
    // Se fonte é texto/linha, usar complementar 255 - cor
    TipoForma tf = getFormaTipo(fonte);
    char tmp[20];
    const char *final = corSrc;
    if (tf == TIPO_TEXTO || tf == TIPO_LINHA)
    {
        if (invertHexColor(corSrc, tmp))
            final = tmp;
        else
            final = corSrc; // fallback se não for #RRGGBB
    }
    // Heurística: se destino possui preenchimento (círc/ret/texto), aplica como fill; para linha, como stroke
    TipoForma td = getFormaTipo(destino);
    // Preferimos aplicar como preenchimento para formas com fill; linha não é alterada
    if (td != TIPO_LINHA)
        aplicaCorDestino(destino, final, NULL);
    return 1;
}
