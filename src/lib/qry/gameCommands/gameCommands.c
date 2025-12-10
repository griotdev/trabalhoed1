#include <stdio.h>
#include <stdlib.h>
#include "gameCommands.h"
#include "../disparador/disparador.h"
#include "../formaUtils/formaUtils.h"
#include "../formaUtils/formaArena.h"
#include "../formaUtils/colorRules.h"
#include "../colisao/colisao.h"
#include "../svgQry/svgQry.h"
#include "../../formas/formas/formas.h"

void comando_pd(GameState *state, int id, double x, double y, FILE *saida)
{
    if (saida)
        fprintf(saida, "[*] pd %d %.1f %.1f\n", id, x, y);
    Disparador d = obtemDisparador(*state, id);
    if (!d)
    {
        if (saida)
            fprintf(saida, "    ERRO: Não foi possível criar disparador %d\n", id);
        return;
    }
    setDisparadorPosicao(d, x, y);
    if (saida)
        fprintf(saida, "    Disparador %d posicionado em (%.1f, %.1f)\n", id, x, y);
}

void comando_lc(GameState *state, int idCarregador, int n, FILE *saida)
{
    if (saida)
        fprintf(saida, "[*] lc %d %d\n", idCarregador, n);
    Fila chao = getChao(*state);
    Pilha carregador = obtemCarregadorPorId(*state, idCarregador);
    if (!chao || !carregador)
    {
        if (saida)
            fprintf(saida, "    ERRO: Estado inválido\n");
        return;
    }
    int carregadas = 0;
    char info[256];
    
    // Carregar formas diretamente na pilha (LIFO)
    // A última forma carregada será a primeira a ser disparada
    for (int i = 0; i < n; i++)
    {
        if (filaVazia(chao))
        {
            if (saida)
                fprintf(saida, "    Chão vazio após %d formas carregadas\n", carregadas);
            break;
        }
        Forma *f = (Forma *)desenfileira(chao);
        empilha(carregador, f);
        carregadas++;
        getFormaInfo(f, info, sizeof(info));
        if (saida)
            fprintf(saida, "    %s carregada\n", info);
    }
    
    if (saida && carregadas == n)
        fprintf(saida, "    %d formas carregadas com sucesso no carregador %d\n", n, idCarregador);
}

void comando_atch(GameState *state, int idDisp, int idCesq, int idCdir, FILE *saida)
{
    if (saida)
        fprintf(saida, "[*] atch %d %d %d\n", idDisp, idCesq, idCdir);
    Disparador d = obtemDisparador(*state, idDisp);
    if (!d)
    {
        if (saida)
            fprintf(saida, "    ERRO: Disparador %d não existe\n", idDisp);
        return;
    }
    Pilha cesq = removeCarregadorPorId(*state, idCesq);
    Pilha cdir = removeCarregadorPorId(*state, idCdir);
    if (!cesq)
    {
        if (saida)
            fprintf(saida, "    AVISO: Carregador esquerdo %d não existe (criando vazio)\n", idCesq);
        cesq = criaPilha();
    }
    if (!cdir)
    {
        if (saida)
            fprintf(saida, "    AVISO: Carregador direito %d não existe (criando vazio)\n", idCdir);
        cdir = criaPilha();
    }
    encaixaCarregadores(d, cesq, cdir);
    if (saida)
        fprintf(saida, "    Carregadores %d e %d encaixados no disparador %d\n", idCesq, idCdir, idDisp);
}

void comando_shft(GameState *state, int idDisp, char lado, int n, FILE *saida)
{
    if (saida)
        fprintf(saida, "[*] shft %d %c %d\n", idDisp, lado, n);
    Disparador d = obtemDisparador(*state, idDisp);
    if (!d)
    {
        if (saida)
            fprintf(saida, "    ERRO: Disparador %d não existe\n", idDisp);
        return;
    }
    int movimentos = 0;
    for (int i = 0; i < n; i++)
    {
        int ok = pressionaBotao(d, lado);
        if (ok == 1)
            movimentos++;
        else
        {
            if (saida)
                fprintf(saida, "    Movimento interrompido após %d/%d: sem formas disponíveis\n", movimentos, n);
            break;
        }
    }
    if (saida && movimentos == n)
        fprintf(saida, "    Botão '%c' pressionado %d vezes no disparador %d\n", lado, n, idDisp);
}

void comando_dsp(GameState *state, int idDisp, double dx, double dy, char tipo, FILE *saida)
{
    if (saida)
        fprintf(saida, "[*] dsp %d %.1f %.1f %c\n", idDisp, dx, dy, tipo);
    Disparador d = obtemDisparador(*state, idDisp);
    if (!d)
    {
        if (saida)
            fprintf(saida, "    ERRO: Disparador %d não existe\n", idDisp);
        return;
    }
    // Guarda posição do disparador antes de disparar
    double dispX = getDisparadorX(d);
    double dispY = getDisparadorY(d);
    
    Forma *f = disparaForma(d, dx, dy);
    if (!f)
    {
        if (saida)
            fprintf(saida, "    Nenhuma forma na posição de disparo\n");
        return;
    }
    Fila arena = getArena(*state);
    char info[256];
    getFormaInfo(f, info, sizeof(info));
    if (saida)
    {
        if (tipo == 'i')
            fprintf(saida, "    %s disparada (invisível)\n", info);
        else
            fprintf(saida, "    %s disparada (visível)\n", info);
    }
    // Cria FormaArena com anotação se tipo == 'v'
    bool anotada = (tipo == 'v' || tipo == 'V');
    FormaArena fa = criaFormaArena(f, dispX, dispY, anotada);
    enfileira(arena, fa);
}

void comando_rjd(GameState *state, int idDisp, char lado, double dx, double dy, double ix, double iy, FILE *saida)
{
    if (saida)
        fprintf(saida, "[*] rjd %d %c %.1f %.1f %.1f %.1f\n", idDisp, lado, dx, dy, ix, iy);
    Disparador d = obtemDisparador(*state, idDisp);
    if (!d)
    {
        if (saida)
            fprintf(saida, "    ERRO: Disparador %d não existe\n", idDisp);
        return;
    }
    // Guarda posição do disparador
    double dispX = getDisparadorX(d);
    double dispY = getDisparadorY(d);
    
    Fila arena = getArena(*state);
    int num = 0;
    double cdx = dx, cdy = dy;
    while (1)
    {
        int ok = pressionaBotao(d, lado);
        if (ok != 1)
        {
            if (saida)
                fprintf(saida, "    Rajada interrompida após %d disparos: sem mais formas\n", num);
            break;
        }
        Forma *f = disparaForma(d, cdx, cdy);
        if (!f)
            break;
        // Rajadas sempre são anotadas para visualização
        FormaArena fa = criaFormaArena(f, dispX, dispY, true);
        enfileira(arena, fa);
        num++;
        cdx += ix;
        cdy += iy;
    }
    if (saida)
        fprintf(saida, "    Rajada de %d disparos executada\n", num);
}

void comando_calc(GameState *state, FILE *saida, const char *svgPath,
                  int *out_esmagadas, int *out_clones, double *out_pontuacao)
{
    if (saida)
        fprintf(saida, "[*] calc\n");
    Fila arena = getArena(*state);
    Fila chao = getChao(*state);
    
    // Gerar SVG ANTES de processar colisões (para mostrar rajadas)
    if (svgPath != NULL)
    {
        svgGeraArquivoQry(svgPath, *state, 800, 600);
    }
    
    if (filaVazia(arena))
    {
        if (saida)
            fprintf(saida, "Arena vazia - sem colisões\n");
        return;
    }
    
    double area_round = 0.0;
    int verif = 0, esmag = 0, clones = 0;
    
    // Processar PARES sequencialmente (FIFO) - não O(n²)!
    while (!filaVazia(arena) && tamanhoFila(arena) >= 2)
    {
        // Extrai par I, J da arena
        FormaArena faI = (FormaArena)desenfileira(arena);
        Forma *I = getFormaArenaForma(faI);
        destroiFormaArena(faI);
        
        FormaArena faJ = (FormaArena)desenfileira(arena);
        Forma *J = getFormaArenaForma(faJ);
        destroiFormaArena(faJ);
        
        verif++;
        double aI = calculaArea(I);
        double aJ = calculaArea(J);
        
        if (saida)
            fprintf(saida, "  [verif %d] id=%d (area=%.2f) x id=%d (area=%.2f)\n",
                    verif, getFormaId(I), aI, getFormaId(J), aJ);
        
        if (verificaSobreposicao(I, J))
        {
            if (saida)
                fprintf(saida, "    -> Sobreposicao detectada!\n");
            
            if (aI < aJ)
            {
                // I esmagada (menor área perde)
                if (saida)
                    fprintf(saida, "    -> [I<J] Forma %d ESMAGADA (%.2f < %.2f). J retorna ao chao.\n",
                            getFormaId(I), aI, aJ);
                
                area_round += aI;
                esmag++;
                destroiForma(I);
                enfileira(chao, J);
            }
            else
            {
                // I >= J: NÃO esmaga! Troca cores, clona I, todos voltam
                if (saida)
                    fprintf(saida, "    -> [I>=J] Forma %d modifica %d. Clone de %d criado. Todos retornam.\n",
                            getFormaId(I), getFormaId(J), getFormaId(I));
                
                // J recebe cor de preenchimento de I (ou complementar se I for linha)
                aplicaCorDeFonte(J, I);
                
                // Cria clone de I com cores invertidas
                Forma *clone = clonaForma(I);
                if (clone)
                {
                    trocaCores(clone);
                    clones++;
                }
                
                // Todos voltam ao chão: I, J, clone
                enfileira(chao, I);
                enfileira(chao, J);
                if (clone)
                    enfileira(chao, clone);
            }
        }
        else
        {
            // Sem sobreposição: ambos voltam ao chão
            if (saida)
                fprintf(saida, "    -> Sem sobreposicao. Ambos retornam ao chao.\n");
            enfileira(chao, I);
            enfileira(chao, J);
        }
    }
    
    // Se sobrou forma ímpar (sem par), volta ao chão
    if (!filaVazia(arena))
    {
        FormaArena fa = (FormaArena)desenfileira(arena);
        Forma *sobra = getFormaArenaForma(fa);
        destroiFormaArena(fa);
        if (saida)
            fprintf(saida, "  [impar] Forma %d sem par, retorna ao chao.\n", getFormaId(sobra));
        enfileira(chao, sobra);
    }
    
    if (saida)
        fprintf(saida, "  Pontos do round: %.2f\n", area_round);
    
    // Atualizar estatísticas de saída
    if (out_esmagadas) *out_esmagadas += esmag;
    if (out_clones) *out_clones += clones;
    if (out_pontuacao) *out_pontuacao += area_round;
}
