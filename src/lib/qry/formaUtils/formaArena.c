/* src/lib/qry/formaUtils/formaArena.c */

#include <stdlib.h>
#include "formaArena.h"

typedef struct forma_arena_internal
{
    Forma *forma;
    double disparadorX;
    double disparadorY;
    bool anotada;
} FormaArenaInternal;

FormaArena criaFormaArena(Forma *forma, double disparadorX, double disparadorY, bool anotada)
{
    FormaArenaInternal *fa = malloc(sizeof(FormaArenaInternal));
    if (!fa)
        return NULL;
    fa->forma = forma;
    fa->disparadorX = disparadorX;
    fa->disparadorY = disparadorY;
    fa->anotada = anotada;
    return (FormaArena)fa;
}

void destroiFormaArena(FormaArena formaArena)
{
    FormaArenaInternal *fa = (FormaArenaInternal *)formaArena;
    if (fa)
        free(fa);
}

Forma* getFormaArenaForma(FormaArena formaArena)
{
    FormaArenaInternal *fa = (FormaArenaInternal *)formaArena;
    return fa ? fa->forma : NULL;
}

double getFormaArenaDisparadorX(FormaArena formaArena)
{
    FormaArenaInternal *fa = (FormaArenaInternal *)formaArena;
    return fa ? fa->disparadorX : 0.0;
}

double getFormaArenaDisparadorY(FormaArena formaArena)
{
    FormaArenaInternal *fa = (FormaArenaInternal *)formaArena;
    return fa ? fa->disparadorY : 0.0;
}

bool getFormaArenaAnotada(FormaArena formaArena)
{
    FormaArenaInternal *fa = (FormaArenaInternal *)formaArena;
    return fa ? fa->anotada : false;
}
