/* include/colisao.h
 *
 * Detecção de colisões e cálculo de áreas de formas.
 * 
 * Fornece funções para:
 *  - Verificar se duas formas se sobrepõem no espaço
 *  - Calcular a área ocupada por uma forma
 * 
 * Cálculos de área:
 *  - Círculo: π * r²
 *  - Retângulo: largura × altura
 *  - Linha: aproximado como 2 × comprimento (heurística)
 *  - Texto: aproximado como 20 × número de caracteres (heurística)
 */

#ifndef COLISAO_H
#define COLISAO_H

#include "../../formas/formas/formas.h"

/**
 * Verifica se duas formas se sobrepõem.
 * 
 * Implementa verificação de colisão entre todos os tipos de formas:
 *  - Círculo-Círculo: distância entre centros < soma dos raios
 *  - Retângulo-Retângulo: interseção de AABBs
 *  - Círculo-Retângulo: ponto mais próximo do retângulo ao círculo
 *  - Outras combinações: heurísticas baseadas em distâncias
 * 
 * @param a Primeira forma
 * @param b Segunda forma
 * @return 1 se sobrepõem, 0 caso contrário
 */
int verificaSobreposicao(Forma *a, Forma *b);

/**
 * Calcula a área ocupada por uma forma.
 * 
 * @param f Forma
 * @return Área da forma (em unidades quadradas)
 * 
 * Observações:
 *  - Para linhas e textos, usa heurísticas já que não possuem área real
 *  - Linha: 2 × comprimento
 *  - Texto: 20 × número de caracteres
 */
double calculaArea(Forma *f);

#endif
