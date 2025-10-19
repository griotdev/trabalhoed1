#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/argumentos/argumentHandler.h"
#include "lib/geo/parserGeo/parserGeo.h"
#include "lib/qry/parserQry/parserQry.h"
#include "lib/qry/gameState/gameState.h"
#include "lib/qry/svgQry/svgQry.h"
#include "lib/estruturas/fila/fila.h"
#include "lib/estruturas/pilha/pilha.h"
#include "lib/geo/svg/svg.h"
#include "lib/formas/formas/formas.h"

#define MAX_ALLOWED_ARGS 12

void extrairNomeBase(const char *caminho, char *nomeBase, size_t tamanho) {
    if (caminho == NULL || nomeBase == NULL || tamanho == 0) {
        return;
    }
    
    const char *ultimaBarra = strrchr(caminho, '/');
    const char *nomeArquivo = (ultimaBarra != NULL) ? ultimaBarra + 1 : caminho;
    
    const char *ponto = strrchr(nomeArquivo, '.');
    
    if (ponto != NULL) {
        size_t comprimento = ponto - nomeArquivo;
        if (comprimento >= tamanho) {
            comprimento = tamanho - 1;
        }
        strncpy(nomeBase, nomeArquivo, comprimento);
        nomeBase[comprimento] = '\0';
    } else {
        strncpy(nomeBase, nomeArquivo, tamanho - 1);
        nomeBase[tamanho - 1] = '\0';
    }
}

char* construirCaminhoSaida(const char *diretorio, const char *nomeBase, const char *extensao) {
    if (diretorio == NULL || nomeBase == NULL || extensao == NULL) {
        return NULL;
    }
    
    size_t tamTotal = strlen(diretorio) + strlen(nomeBase) + strlen(extensao) + 2;
    char *caminho = (char*)malloc(tamTotal);
    
    if (caminho == NULL) {
        fprintf(stderr, "Erro ao alocar memória para caminho de saída.\n");
        return NULL;
    }
    
    snprintf(caminho, tamTotal, "%s/%s%s", diretorio, nomeBase, extensao);
    return caminho;
}

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

    Fila filaFormas = criaFila();
    if (filaFormas == NULL) {
        fprintf(stderr, "Erro ao criar Fila.\n");
        freeArgs(&args);
        return EXIT_FAILURE;
    }

    Pilha pilhaAux = criaPilha();
    if (pilhaAux == NULL) {
        fprintf(stderr, "Erro ao criar Pilha.\n");
        destroiFila(filaFormas, NULL);
        freeArgs(&args);
        return EXIT_FAILURE;
    }

    printf("\n=== Processando arquivo .geo ===\n");
    int geoStatus = parseGeo(args, filaFormas, pilhaAux);
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

    // Processa .qry usando o novo módulo (retorna GameState)
    GameState state = NULL;
    if (getQryFile(args) != NULL && strlen(getQryFile(args)) > 0) {
        printf("\n=== Processando arquivo .qry (novo módulo) ===\n");
        state = parseQry(args, filaFormas, pilhaAux);
        if (state == NULL) {
            fprintf(stderr, "Aviso: erro durante parseQry.\n");
        } else {
            // Nome final deve ser (geoBase)-(qryBase).svg
            char nomeBaseQry[256];
            extrairNomeBase(getQryFile(args), nomeBaseQry, sizeof(nomeBaseQry));

            char combinado[512];
            snprintf(combinado, sizeof(combinado), "%s-%s", nomeBase, nomeBaseQry);

            char *caminhoSvgQry = construirCaminhoSaida(getOutputDir(args), combinado, ".svg");
            if (caminhoSvgQry != NULL) {
                svgGeraArquivoQry(caminhoSvgQry, state, 800, 600);
                free(caminhoSvgQry);
            }
        }
    }

    // Destroi estado do jogo (devolve formas ao chão; chão é destruído abaixo)
    if (state != NULL) {
        destroiGameState(state);
    }

    destroiPilha(pilhaAux, NULL);
    destroiFila(filaFormas, (FuncaoLibera)destroiForma);
    freeArgs(&args);

    printf("\n=== Execução finalizada com sucesso ===\n");
    return EXIT_SUCCESS;
}
