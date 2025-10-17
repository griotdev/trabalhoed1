#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentHandler.h"

typedef struct ArgsStruct {
    char *entryDir;
    char *geoFile;
    char *qryFile;
    char *outputDir;
} ArgsStruct;

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

Args handleArguments(int argc, char *argv[]) {
    ArgsStruct *args = (ArgsStruct*)malloc(sizeof(ArgsStruct));
    if (args == NULL) {
        fprintf(stderr, "Erro de alocação de memória para Args.\n");
        return NULL;
    }
    
    args->entryDir = NULL;
    args->geoFile = NULL;
    args->qryFile = NULL;
    args->outputDir = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc) {
                i++;
                args->entryDir = duplicarString(argv[i]);
                if (args->entryDir == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -e.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -e requer um argumento (diretório de entrada).\n");
            }
        }
        else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                i++;
                args->geoFile = duplicarString(argv[i]);
                if (args->geoFile == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -f.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -f requer um argumento (arquivo .geo).\n");
            }
        } 
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                i++;
                args->outputDir = duplicarString(argv[i]);
                if (args->outputDir == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -o.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -o requer um argumento (diretório de saída).\n");
            }
        } 
        else if (strcmp(argv[i], "-q") == 0) {
            if (i + 1 < argc) {
                i++;
                args->qryFile = duplicarString(argv[i]);
                if (args->qryFile == NULL) {
                    fprintf(stderr, "Erro ao processar argumento -q.\n");
                }
            } else {
                fprintf(stderr, "Erro: flag -q requer um argumento (arquivo .qry).\n");
            }
        }
        else {
            fprintf(stderr, "Aviso: argumento '%s' não reconhecido e será ignorado.\n", argv[i]);
        }
    }

    return (Args)args;
}

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

char* getEntryDir(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->entryDir;
}

char* getGeoFile(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->geoFile;
}

char* getQryFile(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->qryFile;
}

char* getOutputDir(Args args) {
    if (args == NULL) {
        return NULL;
    }
    ArgsStruct *argsStruct = (ArgsStruct*)args;
    return argsStruct->outputDir;
}
