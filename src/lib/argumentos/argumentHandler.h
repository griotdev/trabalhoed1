/* include/argumentHandler.h
 *
 * Módulo responsável por processar argumentos da linha de comando.
 * 
 * Argumentos esperados:
 *   -f <arquivo.geo>  : arquivo de entrada com geometrias (obrigatório)
 *   -o <diretório>    : diretório de saída para resultados (obrigatório)
 *   -q <arquivo.qry>  : arquivo de consultas (opcional)
 *
 * A função handleArguments retorna um ponteiro opaco Args com os
 * caminhos fornecidos pelo usuário.
 */

#ifndef ARGUMENT_HANDLER_H
#define ARGUMENT_HANDLER_H

/* Tipo opaco para armazenar argumentos processados */
typedef void* Args;

/**
 * Processa os argumentos da linha de comando e retorna um ponteiro opaco Args.
 * 
 * @param argc Número de argumentos (passado do main)
 * @param argv Array de strings com os argumentos (passado do main)
 * @return Args ponteiro opaco com os caminhos dos arquivos e diretório de saída
 * 
 * Observações:
 *  - Se argumentos obrigatórios estiverem faltando, retorna NULL.
 *  - A memória é alocada dinamicamente e deve ser liberada com freeArgs().
 */
Args handleArguments(int argc, char *argv[]);

/**
 * Libera a memória alocada para Args.
 * 
 * @param args Ponteiro para Args a ser liberado
 */
void freeArgs(Args *args);

/**
 * Obtém o diretório de entrada.
 * 
 * @param args Ponteiro para Args
 * @return Ponteiro para string com o diretório de entrada (pode ser NULL)
 */
char* getEntryDir(Args args);

/**
 * Obtém o caminho do arquivo .geo.
 * 
 * @param args Ponteiro para Args
 * @return Ponteiro para string com o caminho do arquivo .geo (pode ser NULL)
 */
char* getGeoFile(Args args);

/**
 * Obtém o caminho do arquivo .qry.
 * 
 * @param args Ponteiro para Args
 * @return Ponteiro para string com o caminho do arquivo .qry (pode ser NULL)
 */
char* getQryFile(Args args);

/**
 * Obtém o diretório de saída.
 * 
 * @param args Ponteiro para Args
 * @return Ponteiro para string com o diretório de saída (pode ser NULL)
 */
char* getOutputDir(Args args);

#endif /* ARGUMENT_HANDLER_H */
