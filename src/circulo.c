#include "circulo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265358979323846

typedef struct circulo_t{
    int id;
    float x, y;
    float raio;
    char cb[8];
    char cp[8];
}circulo;

circulo* criaCirculo(int id, float x, float y, float r, char* cb, char* cp)
{
    circulo *c = (circulo*) malloc(sizeof(circulo));
    
    if (c == NULL) {
        return NULL;
    }
    
    c->id = id;
    c->x = x;
    c->y = y;
    c->raio = r;
    strncpy(c->cb, cb, sizeof(c->cb) - 1);
    c->cb[sizeof(c->cb) - 1] = '\0';
    strncpy(c->cp, cp, sizeof(c->cp) - 1);
    c->cp[sizeof(c->cp) - 1] = '\0';
    return c;
}

float CalculaCirculoArea()
{

}

int getCirculoId(circulo *c)
{
    return c->id;
}

float getCirculoX(circulo *c)
{
    return c->x;
}

float getCirculoY(circulo *c)
{
    return c->y;
}

float getCirculoRaio(circulo *c)
{
    return c->raio;
}

char* getCirculoCb(circulo *c)
{
    return c->cb;
}

char* getCirculoCp(circulo *c)
{
    return c->cp;
}

