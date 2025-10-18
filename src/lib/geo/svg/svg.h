/* include/svg.h
 *
 * Módulo para geração de arquivos SVG.
 * Responsável por escrever as formas geométricas em formato SVG.
 */

#ifndef SVG_H
#define SVG_H

#include "../../estruturas/fila/fila.h"
#include "../../formas/formas/formas.h"
#include <stdio.h>

/**
 * Cria um arquivo SVG e escreve o cabeçalho.
 * @param nomeArquivo Nome do arquivo SVG a ser criado
 * @param largura Largura do canvas SVG
 * @param altura Altura do canvas SVG
 * @return Ponteiro para o arquivo aberto, ou NULL em caso de erro
 */
FILE* svgCriaArquivo(const char *nomeArquivo, int largura, int altura);

/**
 * Escreve uma forma no arquivo SVG.
 * @param arquivo Ponteiro para o arquivo SVG
 * @param forma Ponteiro para a forma a ser escrita
 */
void svgEscreveForma(FILE *arquivo, Forma *forma);

/**
 * Escreve um círculo no arquivo SVG.
 * @param arquivo Ponteiro para o arquivo SVG
 * @param circulo Ponteiro para o círculo
 */
void svgEscreveCirculo(FILE *arquivo, Circulo *circulo);

/**
 * Escreve um retângulo no arquivo SVG.
 * @param arquivo Ponteiro para o arquivo SVG
 * @param retangulo Ponteiro para o retângulo
 */
void svgEscreveRetangulo(FILE *arquivo, Retangulo *retangulo);

/**
 * Escreve uma linha no arquivo SVG.
 * @param arquivo Ponteiro para o arquivo SVG
 * @param linha Ponteiro para a linha
 */
void svgEscreveLinha(FILE *arquivo, Linha *linha);

/**
 * Escreve um texto no arquivo SVG.
 * @param arquivo Ponteiro para o arquivo SVG
 * @param texto Ponteiro para o texto
 */
void svgEscreveTexto(FILE *arquivo, Texto *texto);

/**
 * Finaliza o arquivo SVG e fecha.
 * @param arquivo Ponteiro para o arquivo SVG
 */
void svgFechaArquivo(FILE *arquivo);

/**
 * Gera um arquivo SVG completo a partir de uma fila de formas.
 * @param nomeArquivo Nome do arquivo SVG a ser criado
 * @param fila Fila contendo as formas
 * @param largura Largura do canvas SVG
 * @param altura Altura do canvas SVG
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int svgGeraArquivo(const char *nomeArquivo, Fila fila, int largura, int altura);

#endif /* SVG_H */
