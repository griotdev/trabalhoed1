/* include/colorRules.h
 *
 * Regras especiais para transferência de cores entre formas.
 * 
 * Implementa a lógica de transferência de cor durante esmagamentos:
 *  - Se a forma fonte é texto ou linha: aplica cor complementar (255 - RGB)
 *  - Caso contrário: aplica a cor original
 * 
 * A cor é extraída do preenchimento (ou stroke para linha) da fonte
 * e aplicada ao preenchimento da forma destino.
 */

#ifndef COLOR_RULES_H
#define COLOR_RULES_H

#include "../../formas/formas/formas.h"

/**
 * Aplica cor da forma fonte na forma destino, seguindo regras especiais.
 * 
 * Regras:
 *  - Se fonte é texto ou linha: usa cor complementar (255 - cada componente RGB)
 *  - Caso contrário: usa cor original da fonte
 * 
 * A cor é aplicada ao preenchimento da forma destino (quando aplicável).
 * Linhas não têm cor de preenchimento, então não são modificadas como destino.
 * 
 * @param destino Forma que receberá a cor
 * @param fonte Forma de onde a cor será extraída
 * @return 1 se conseguiu aplicar, 0 caso contrário
 */
int aplicaCorDeFonte(Forma *destino, Forma *fonte);

#endif /* COLOR_RULES_H */