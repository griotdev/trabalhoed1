#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"

/* Estrutura concreta (NÃO colocar no .h) */
typedef struct
{
    char *entrada_path; /* -e */
    char *geo_file;     /* -f */
    char *qry_file;     /* -q */
    char *saida_path;   /* -o */
} ArgsImpl;

Args argumentos_cria(int argc, char **argv)
{
    ArgsImpl *a = malloc(sizeof(ArgsImpl));
    if (!a)
        return NULL;
    a->entrada_path = NULL;
    a->geo_file = NULL;
    a->qry_file = NULL;
    a->saida_path = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc)
        {
            a->entrada_path = strdup(argv[++i]);
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            a->geo_file = strdup(argv[++i]);
        }
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc)
        {
            a->qry_file = strdup(argv[++i]);
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            a->saida_path = strdup(argv[++i]);
        }
        else
        {
            /* argumento não tratado: poderia juntar em msg */
        }
    }
    return (Args)a;
}

void argumentos_destroi(Args a)
{
    ArgsImpl *ai = (ArgsImpl *)a;
    if (!ai)
        return;
    free(ai->entrada_path);
    free(ai->geo_file);
    free(ai->qry_file);
    free(ai->saida_path);
    free(ai);
}

char *argumentos_get_entrada_path(Args a) { return ((ArgsImpl *)a)->entrada_path; }
char *argumentos_get_geo_file(Args a) { return ((ArgsImpl *)a)->geo_file; }
char *argumentos_get_qry_file(Args a) { return ((ArgsImpl *)a)->qry_file; }
char *argumentos_get_saida_path(Args a) { return ((ArgsImpl *)a)->saida_path; }