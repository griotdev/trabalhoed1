/* include/parserGeo.h
 *
 * Módulo responsável por ler e interpretar arquivos .geo.
 * 
 * Formato do arquivo .geo:
 *  c i x y r corb corp         - círculo
 *  r i x y w h corb corp       - retângulo
 *  l i x1 y1 x2 y2 cor         - linha
 *  t i x y corb corp a txt     - texto
 *  ts fFamily fWeight fSize    - estilo de texto
 */

#ifndef PARSERGEO_H
#define PARSERGEO_H

#include "../../estruturas/fila/fila.h"
#include "../../estruturas/pilha/pilha.h"
#include "../../argumentos/argumentHandler.h"

/**
 * Faz o parse do arquivo .geo e popula a fila com as formas.
 * 
 * @param args Estrutura com os argumentos do programa (contém o caminho do .geo)
 * @param fila Fila onde as formas serão armazenadas
 * @param pilha Pilha auxiliar (pode ser usada para processamento temporário)
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int parseGeo(Args args, Fila fila, Pilha pilha);

#endif /* PARSERGEO_H */

