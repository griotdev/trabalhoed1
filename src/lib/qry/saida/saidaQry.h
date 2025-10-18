#ifndef SAIDA_QRY_H
#define SAIDA_QRY_H

#include <stdio.h>

/**
 * Abre arquivo de saída textual para logs do .qry
 * @param nomeArquivo Nome do arquivo .txt de saída
 * @return Ponteiro para o arquivo ou NULL em caso de erro
 */
FILE* saidaQryAbreArquivo(const char *nomeArquivo);

/**
 * Registra um comando executado
 * @param arquivo Arquivo de saída
 * @param linha Linha do comando original
 */
void saidaQryLogComando(FILE *arquivo, const char *linha);

/**
 * Registra um evento (disparo, colisão, etc)
 * @param arquivo Arquivo de saída
 * @param evento Descrição do evento
 */
void saidaQryLogEvento(FILE *arquivo, const char *evento);

/**
 * Registra estatísticas finais
 * @param arquivo Arquivo de saída
 * @param numInstrucoes Número total de instruções
 * @param numDisparos Número de disparos
 * @param numEsmagadas Número de formas esmagadas
 * @param numClonadas Número de formas clonadas
 * @param pontuacao Pontuação total
 */
void saidaQryLogResumo(FILE *arquivo, int numInstrucoes, int numDisparos, 
                       int numEsmagadas, int numClonadas, double pontuacao);

/**
 * Fecha arquivo de saída textual
 * @param arquivo Arquivo de saída
 */
void saidaQryFechaArquivo(FILE *arquivo);

#endif /* SAIDA_QRY_H */
