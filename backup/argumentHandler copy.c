/* src/argumentHandler.c
 *
 * Implementação do módulo de processamento de argumentos.
 * Processa flags -f, -o e -q da linha de comando.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../argumentos/argumentHandler.h"

/* Definição interna da estrutura (não visível no .h) */
typedef struct ArgsStruct {
    char *entryDir;   /* Diretório de entrada (opcional, padrão: diretório corrente) */
    char *geoFile;    /* Caminho do arquivo .geo (obrigatório) */
    char *qryFile;    /* Caminho do arquivo .qry (opcional, pode ser NULL) */
    char *outputDir;  /* Diretório de saída (obrigatório) */
} ArgsStruct;

/**
 * Função auxiliar para duplicar uma string.
 */
static char* duplicarString(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    size_t len = strlen(src);
    char *dest = (char*)malloc(len + 1);
    if (dest == NULL) {
        fprintf(stderr, "Erro de alocação de memória ao duplicar string.\n");
        return NULL;
    }
    strcpy(dest, src);
    return dest;
}

/**
 * Processa os argumentos da linha de comando.
 * Formato esperado:
 *   -f <arquivo.geo> -o <diretório> [-q <arquivo.qry>]
 * 
 * Retorna um ponteiro opaco Args com os campos preenchidos.
 */
Args handleArguments(int argc, char *argv[]) {
    ArgsStruct *args = (ArgsStruct*)malloc(sizeof(ArgsStruct));
    if (args == NULL) {
        fprintf(stderr, "Erro de alocação de memória para Args.\n");
        return NULL;
    }
    
    /* Inicializa todos os campos como NULL */
    args->entryDir = NULL;
    args->geoFile = NULL;
    args->qryFile = NULL;
    args->outputDir = NULL;

    /* Percorre os argumentos procurando pelas flags */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            /* Flag -e: diretório de entrada */
            if (i + 1 < argc) {
                i++; /* Avança para o próximo argumento (o valor) */
                args->entryDir = duplicarString(argv[i]);
                if (args->entryDir == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -e.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -e requer um argumento (diretório de entrada).\n");
            }
        }
        else if (strcmp(argv[i], "-f") == 0) {
            /* Flag -f: arquivo .geo */
            if (i + 1 < argc) {
                i++; /* Avança para o próximo argumento (o valor) */
                args->geoFile = duplicarString(argv[i]);
                if (args->geoFile == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -f.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -f requer um argumento (arquivo .geo).\n");
            }
        } 
        else if (strcmp(argv[i], "-o") == 0) {
            /* Flag -o: diretório de saída */
            if (i + 1 < argc) {
                i++; /* Avança para o próximo argumento (o valor) */
                args->outputDir = duplicarString(argv[i]);
                if (args->outputDir == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -o.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -o requer um argumento (diretório de saída).\n");
            }
        } 
        else if (strcmp(argv[i], "-q") == 0) {
            /* Flag -q: arquivo .qry (opcional) */
            if (i + 1 < argc) {
                i++; /* Avança para o próximo argumento (o valor) */
                args->qryFile = duplicarString(argv[i]);
                if (args->qryFile == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -q.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -q requer um argumento (arquivo .qry).\n");
            }
        }
        else {
            /* Argumento não reconhecido */
            fprintf(stderr, "Aviso: argumento '%s' não reconhecido e será ignorado.\n", argv[i]);
        }
    }

    return (Args)args;
}

/**
 * Libera a memória alocada para Args.
 */
void freeArgs(Args *args) {
    if (args == NULL || *args == NULL) {
        return;
    }

    ArgsStruct *argsStruct = (ArgsStruct*)(*args);

    if (argsStruct->entryDir != NULL) {
        free(argsStruct->entryDir);
        argsStruct->entryDir = NULL;
    }

    if (argsStruct->geoFile != NULL) {
        free(argsStruct->geoFile);
        argsStruct->geoFile = NULL;
    }

    if (argsStruct->qryFile != NULL) {
        free(argsStruct->qryFile);
        argsStruct->qryFile = NULL;
    }

    if (argsStruct->outputDir != NULL) {
        free(argsStruct->outputDir);
        argsStruct->outputDir = NULL;
    }

    free(argsStruct);
    *args = NULL;
}

/**
 * Obtém o diretório de entrada.
 */
char* getEntryDir(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->entryDir;
}

/**
 * Obtém o caminho do arquivo .geo.
 */
char* getGeoFile(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->geoFile;
}

/**
 * Obtém o caminho do arquivo .qry.
 */
char* getQryFile(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->qryFile;
}

/**
 * Obtém o diretório de saída.
 */
char* getOutputDir(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->outputDir;
}
