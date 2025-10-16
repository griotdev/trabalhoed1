#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumentos/argumentHandler.h"
#include "geo/geoHandler/geoHandler.h"
#include "estruturas/fila/fila.h"
#include "estruturas/pilha/pilha.h"
#include "geo/svg/svg.h"
#include "formas/formas/formas.h"

#define MAX_ALLOWED_ARGS 12

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Uso incorreto: argumentos insuficientes.\n");
        fprintf(stderr, "Exemplo: %s -f entrada.geo -o saida/ [-e entrada/] [-q comandos.qry]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc > MAX_ALLOWED_ARGS) {
        fprintf(stderr, "Erro: muitos argumentos (argc = %d). Máximo permitido é %d.\n",
                argc, MAX_ALLOWED_ARGS);
        return EXIT_FAILURE;
    }

    Args args = handleArguments(argc, argv);

    if (getGeoFile(args) == NULL || strlen(getGeoFile(args)) == 0) {
        fprintf(stderr, "Erro: arquivo .geo não informado ou inválido.\n");
        freeArgs(&args);
        return EXIT_FAILURE;
    }
    if (getOutputDir(args) == NULL || strlen(getOutputDir(args)) == 0) {
        fprintf(stderr, "Erro: diretório de saída não informado ou inválido.\n");
        freeArgs(&args);
        return EXIT_FAILURE;
    }

    Fila *filaFormas = criaFila();
    if (filaFormas == NULL) {
        fprintf(stderr, "Erro ao criar Fila.\n");
        freeArgs(&args);
        return EXIT_FAILURE;
    }

    Pilha *pilhaAux = criaPilha();
    if (pilhaAux == NULL) {
        fprintf(stderr, "Erro ao criar Pilha.\n");
        destroiFila(filaFormas, NULL);
        freeArgs(&args);
        return EXIT_FAILURE;
    }

    printf("\n=== Processando arquivo .geo ===\n");
    int geoStatus = parseGeo(&args, filaFormas, pilhaAux);
    if (geoStatus != 0) {
        fprintf(stderr, "Erro durante parseGeo (código %d).\n", geoStatus);
        destroiPilha(pilhaAux, NULL);
        destroiFila(filaFormas, (FuncaoLibera)destroiForma);
        freeArgs(&args);
        return EXIT_FAILURE;
    }

    char nomeBase[256];
    extrairNomeBase(getGeoFile(args), nomeBase, sizeof(nomeBase));

    char *caminhoSvg = construirCaminhoSaida(getOutputDir(args), nomeBase, ".svg");
    if (caminhoSvg != NULL) {
        printf("\n=== Gerando arquivo SVG ===\n");
        svgGeraArquivo(caminhoSvg, filaFormas, 800, 600);
        free(caminhoSvg);
    }
    
    destroiPilha(pilhaAux, NULL);
    destroiFila(filaFormas, (FuncaoLibera)destroiForma);
    freeArgs(&args);

    printf("\n=== Execução finalizada com sucesso ===\n");
    return EXIT_SUCCESS;
}
