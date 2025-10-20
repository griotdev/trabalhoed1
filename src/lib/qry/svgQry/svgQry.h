/* include/svgQry.h
 *
 * Geração de arquivos SVG para visualização do estado do jogo.
 * 
 * Cria um SVG mostrando:
 *  - Formas no chão (em opacidade reduzida)
 *  - Formas na arena (disparadas)
 *  - Disparadores posicionados
 *  - Carregadores anexados aos disparadores
 * 
 * O SVG usa dimensionamento dinâmico baseado no conteúdo (bounding box)
 * e aplica translação para centralizar a visualização.
 */

#ifndef SVG_QRY_H
#define SVG_QRY_H

#include "../gameState/gameState.h"

/**
 * Gera um arquivo SVG representando o estado atual do jogo.
 * 
 * @param nomeArquivo Nome do arquivo SVG a ser criado
 * @param state Estado do jogo a ser renderizado
 * @param largura Largura mínima do canvas (pode ser aumentada dinamicamente)
 * @param altura Altura mínima do canvas (pode ser aumentada dinamicamente)
 * @return 0 em caso de sucesso, código de erro caso contrário
 * 
 * Observações:
 *  - O canvas é ajustado dinamicamente para conter todo o conteúdo
 *  - Formas do chão são renderizadas com opacidade 0.6
 *  - Formas na arena são renderizadas normalmente
 *  - Disparadores são mostrados como círculos pequenos
 */
int svgGeraArquivoQry(const char *nomeArquivo, GameState state, int largura, int altura);

#endif /* SVG_QRY_H */
