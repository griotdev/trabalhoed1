#include <stdio.h>
#include <stdlib.h>
#include "gameCommands.h"
#include "../disparador/disparador.h"
#include "../formaUtils/formaUtils.h"
#include "../formaUtils/colorRules.h"
#include "../colisao/colisao.h"
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
    enfileira(arena, f);
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
        enfileira(arena, f);
        num++;
        cdx += ix;
        cdy += iy;
    }
    if (saida)
        fprintf(saida, "    Rajada de %d disparos executada\n", num);
}

void comando_calc(GameState *state, FILE *saida)
{
    if (saida)
        fprintf(saida, "[*] calc\n");
    Fila arena = getArena(*state);
    Fila chao = getChao(*state);
    if (filaVazia(arena))
    {
        if (saida)
            fprintf(saida, "    Arena vazia - sem colisões\n");
        return;
    }
    int num = 0;
    Forma *arr[1000];
    while (!filaVazia(arena))
        arr[num++] = (Forma *)desenfileira(arena);
    if (saida)
        fprintf(saida, "    Processando %d formas na arena\n", num);
    int col = 0, esmag = 0, clones = 0;
    for (int i = 0; i < num; i++)
        if (arr[i])
            for (int j = i + 1; j < num; j++)
                if (arr[j])
                    if (verificaSobreposicao(arr[i], arr[j]))
                    {
                        col++;
                        double ai = calculaArea(arr[i]);
                        double aj = calculaArea(arr[j]);
                        if (saida)
                            fprintf(saida, "    Colisão %d detectada (áreas: %.2f vs %.2f)\n", col, ai, aj);
                        if (ai < aj)
                        {
                            if (saida)
                                fprintf(saida, "      Forma I esmagada (menor área)\n");
                            // Ajusta cor do sobrevivente J com base em I (aplica complementar se I for texto/linha)
                            aplicaCorDeFonte(arr[j], arr[i]);
                            // Agora destrói I
                            destroiForma(arr[i]);
                            arr[i] = NULL;
                            esmag++;
                            // Mantém o swap das cores do sobrevivente
                            trocaCores(arr[j]);
                            if (saida)
                                fprintf(saida, "      Forma J: cores trocadas (e ajustadas por regra)\n");
                            Forma *c = clonaForma(arr[j]);
                            if (c)
                            {
                                enfileira(chao, c);
                                clones++;
                                if (saida)
                                    fprintf(saida, "      Clone de J criado e adicionado ao chão\n");
                            }
                        }
                        else if (aj < ai)
                        {
                            if (saida)
                                fprintf(saida, "      Forma J esmagada (menor área)\n");
                            // Ajusta cor do sobrevivente I com base em J (aplica complementar se J for texto/linha)
                            aplicaCorDeFonte(arr[i], arr[j]);
                            // Agora destrói J
                            destroiForma(arr[j]);
                            arr[j] = NULL;
                            esmag++;
                            // Mantém o swap das cores do sobrevivente
                            trocaCores(arr[i]);
                            if (saida)
                                fprintf(saida, "      Forma I: cores trocadas (e ajustadas por regra)\n");
                            Forma *c = clonaForma(arr[i]);
                            if (c)
                            {
                                enfileira(chao, c);
                                clones++;
                                if (saida)
                                    fprintf(saida, "      Clone de I criado e adicionado ao chão\n");
                            }
                        }
                        else
                        {
                            if (saida)
                                fprintf(saida, "      Áreas iguais - ambas esmagadas\n");
                            destroiForma(arr[i]);
                            destroiForma(arr[j]);
                            arr[i] = arr[j] = NULL;
                            esmag += 2;
                        }
                    }
    int sob = 0;
    for (int i = 0; i < num; i++)
        if (arr[i])
        {
            enfileira(chao, arr[i]);
            sob++;
        }
    if (saida)
    {
        fprintf(saida, "    Resultado: %d colisões detectadas\n", col);
        fprintf(saida, "    %d formas esmagadas, %d clones criados\n", esmag, clones);
        fprintf(saida, "    %d formas sobreviventes retornaram ao chão\n", sob);
    }
}
