#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "saidaQry.h"

FILE *saidaQryAbreArquivo(const char *nomeArquivo)
{
    if (nomeArquivo == NULL)
    {
        return NULL;
    }

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao criar arquivo de saída QRY: %s\n", nomeArquivo);
        return NULL;
    }

    // Cabeçalho do arquivo
    fprintf(arquivo, "========================================\n");
    fprintf(arquivo, "  LOG DE EXECUÇÃO - BOCHA GEOMÉTRICA\n");
    fprintf(arquivo, "========================================\n\n");

    time_t now = time(NULL);
    fprintf(arquivo, "Data/Hora: %s\n", ctime(&now));

    return arquivo;
}

void saidaQryLogComando(FILE *arquivo, const char *linha)
{
    if (arquivo == NULL || linha == NULL)
    {
        return;
    }

    fprintf(arquivo, "\n[CMD] %s\n", linha);
}

void saidaQryLogEvento(FILE *arquivo, const char *evento)
{
    if (arquivo == NULL || evento == NULL)
    {
        return;
    }

    fprintf(arquivo, "  -> %s\n", evento);
}

void saidaQryLogResumo(FILE *arquivo, int numInstrucoes, int numDisparos,
                       int numEsmagadas, int numClonadas, double pontuacao)
{
    if (arquivo == NULL)
    {
        return;
    }

    fprintf(arquivo, "\n========================================\n");
    fprintf(arquivo, "  RESUMO FINAL\n");
    fprintf(arquivo, "========================================\n\n");
    fprintf(arquivo, "Número total de instruções executadas: %d\n", numInstrucoes);
    fprintf(arquivo, "Número total de disparos: %d\n", numDisparos);
    fprintf(arquivo, "Número total de formas esmagadas: %d\n", numEsmagadas);
    fprintf(arquivo, "Número total de formas clonadas: %d\n", numClonadas);
    fprintf(arquivo, "Pontuação final: %.2f\n", pontuacao);
    fprintf(arquivo, "\n========================================\n");
}

void saidaQryFechaArquivo(FILE *arquivo)
{
    if (arquivo == NULL)
    {
        return;
    }

    fclose(arquivo);
}
