#ifndef SVG_QRY_H
#define SVG_QRY_H

#include <stdio.h>
#include "../../formas/formas/formas.h"

/**
 * Abre arquivo SVG para registrar eventos do .qry
 * @param nomeArquivo Nome do arquivo SVG de saída
 * @param largura Largura do canvas
 * @param altura Altura do canvas
 * @return Ponteiro para o arquivo ou NULL em caso de erro
 */
FILE* svgQryAbreArquivo(const char *nomeArquivo, int largura, int altura);

/**
 * Desenha um disparador no SVG
 * @param arquivo Arquivo SVG aberto
 * @param id Identificador do disparador
 * @param x Coordenada x
 * @param y Coordenada y
 */
void svgQryDesenhaDisparador(FILE *arquivo, const char *id, double x, double y);

/**
 * Desenha uma trajetória (linha tracejada) de disparo
 * @param arquivo Arquivo SVG aberto
 * @param x1 Coordenada x inicial
 * @param y1 Coordenada y inicial
 * @param x2 Coordenada x final
 * @param y2 Coordenada y final
 * @param cor Cor da linha
 */
void svgQryDesenhaTrajetoria(FILE *arquivo, double x1, double y1, double x2, double y2, const char *cor);

/**
 * Marca um ponto de colisão com asterisco
 * @param arquivo Arquivo SVG aberto
 * @param x Coordenada x
 * @param y Coordenada y
 */
void svgQryMarcaColisao(FILE *arquivo, double x, double y);

/**
 * Desenha uma forma na arena com opacidade reduzida
 * @param arquivo Arquivo SVG aberto
 * @param forma Forma a ser desenhada
 * @param opacidade Opacidade (0.0 a 1.0)
 */
void svgQryDesenhaFormaArena(FILE *arquivo, Forma *forma, double opacidade);

/**
 * Adiciona texto informativo ao SVG
 * @param arquivo Arquivo SVG aberto
 * @param x Coordenada x
 * @param y Coordenada y
 * @param texto Texto a exibir
 */
void svgQryAdicionaTexto(FILE *arquivo, double x, double y, const char *texto);

/**
 * Fecha arquivo SVG do .qry
 * @param arquivo Arquivo SVG aberto
 */
void svgQryFechaArquivo(FILE *arquivo);

#endif /* SVG_QRY_H */
