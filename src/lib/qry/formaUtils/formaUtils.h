/* include/formaUtils.h
 *
 * Utilitários para manipulação de formas genéricas.
 * 
 * Fornece funções auxiliares para:
 *  - Troca de cores (borda <-> preenchimento)
 *  - Obtenção de informações textuais sobre formas
 */

#ifndef FORMA_UTILS_H
#define FORMA_UTILS_H

#include "../../formas/formas/formas.h"

/**
 * Troca as cores de borda e preenchimento de uma forma.
 * Funciona para círculos, retângulos e textos.
 * Não tem efeito em linhas (que possuem apenas uma cor).
 * @param forma Forma a ser modificada
 */
void trocaCores(Forma *forma);

/**
 * Obtém uma descrição textual da forma.
 * Útil para logging e debug.
 * @param forma Forma a ser descrita
 * @param buffer Buffer onde a descrição será escrita
 * @param bufferSize Tamanho do buffer
 */
void getFormaInfo(Forma *forma, char *buffer, size_t bufferSize);

#endif
