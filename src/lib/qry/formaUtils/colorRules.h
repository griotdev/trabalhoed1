#ifndef COLOR_RULES_H
#define COLOR_RULES_H

#include "../../formas/formas/formas.h"

// Retorna 1 se conseguiu aplicar a cor da fonte (complementar para texto/linha) no destino; 0 caso contrário.
int aplicaCorDeFonte(Forma *destino, Forma *fonte);

#endif /* COLOR_RULES_H */