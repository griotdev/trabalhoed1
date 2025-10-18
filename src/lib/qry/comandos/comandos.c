#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "comandos.h"
#include "../arena/arena.h"
#include "../parserQry/parserQry.h"

static void trim(char *str) {
    if (str == NULL) return;
    
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
    
    char *start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

int exec_comando(char *linha, Arena arena, FILE *saidaTxt) {
    if (linha == NULL || arena == NULL) {
        return 1;
    }
    
    char buffer[1024];
    strncpy(buffer, linha, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    trim(buffer);
    
    if (strlen(buffer) == 0 || buffer[0] == '#') {
        return 0;
    }
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "[*] %s\n", buffer);
    }
    
    char cmd[32];
    if (sscanf(buffer, "%31s", cmd) != 1) {
        return 1;
    }
    
    if (strcmp(cmd, "pd") == 0) {
        char id[64];
        double x, y;
        if (sscanf(buffer, "pd %63s %lf %lf", id, &x, &y) == 3) {
            return exec_pd(id, x, y, arena, saidaTxt);
        }
    }
    else if (strcmp(cmd, "lc") == 0) {
        char idCarregador[64];
        int n;
        if (sscanf(buffer, "lc %63s %d", idCarregador, &n) == 2) {
            return exec_lc(idCarregador, n, arena, saidaTxt);
        }
    }
    else if (strcmp(cmd, "atch") == 0) {
        char idDisp[64], idEsq[64], idDir[64];
        if (sscanf(buffer, "atch %63s %63s %63s", idDisp, idEsq, idDir) == 3) {
            return exec_atch(idDisp, idEsq, idDir, arena, saidaTxt);
        }
    }
    else if (strcmp(cmd, "shft") == 0) {
        char idDisp[64], dir;
        int n;
        if (sscanf(buffer, "shft %63s %c %d", idDisp, &dir, &n) == 3) {
            return exec_shft(idDisp, dir, n, arena, saidaTxt);
        }
    }
    else if (strcmp(cmd, "dsp") == 0) {
        char idDisp[64], modo = 'i';
        double dx, dy;
        int scanned = sscanf(buffer, "dsp %63s %lf %lf %c", idDisp, &dx, &dy, &modo);
        if (scanned >= 3) {
            return exec_dsp(idDisp, dx, dy, modo, arena, saidaTxt);
        }
    }
    else if (strcmp(cmd, "rjd") == 0) {
        char idDisp[64], dir;
        double dx, dy, ix, iy;
        if (sscanf(buffer, "rjd %63s %c %lf %lf %lf %lf", idDisp, &dir, &dx, &dy, &ix, &iy) == 6) {
            return exec_rjd(idDisp, dir, dx, dy, ix, iy, arena, saidaTxt);
        }
    }
    else if (strcmp(cmd, "calc") == 0) {
        return exec_calc(arena, saidaTxt);
    }
    
    fprintf(stderr, "Comando não reconhecido ou mal formatado: %s\n", buffer);
    return 1;
}

int exec_pd(char *id, double x, double y, Arena arena, FILE *saidaTxt) {
    if (arena == NULL || id == NULL) {
        return 1;
    }
    
    TabelaDisparadores tabela = getArenaDisparadores(arena);
    if (tabela == NULL) {
        return 1;
    }
    
    Disparador disp = criaDisparador(id, x, y);
    if (disp == NULL) {
        fprintf(stderr, "Erro ao criar disparador %s\n", id);
        return 1;
    }
    
    if (adicionaDisparador(tabela, disp) != 0) {
        fprintf(stderr, "Erro ao adicionar disparador %s\n", id);
        return 1;
    }
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "disparador %s posicionado em (%.2f, %.2f)\n", id, x, y);
    }
    
    printf("  Disparador %s posicionado em (%.2f, %.2f)\n", id, x, y);
    return 0;
}

int exec_lc(char *idCarregador, int n, Arena arena, FILE *saidaTxt) {
    if (arena == NULL || idCarregador == NULL || n <= 0) {
        return 1;
    }
    
    TabelaCarregadores tabelaCarr = getArenaCarregadores(arena);
    if (tabelaCarr == NULL) {
        return 1;
    }
    
    Carregador carr = buscaCarregador(tabelaCarr, idCarregador);
    if (carr == NULL) {
        carr = criaCarregador(idCarregador);
        if (carr == NULL) {
            fprintf(stderr, "Erro ao criar carregador %s\n", idCarregador);
            return 1;
        }
        if (adicionaCarregador(tabelaCarr, carr) != 0) {
            fprintf(stderr, "Erro ao adicionar carregador %s\n", idCarregador);
            destroiCarregador(&carr);
            return 1;
        }
    }
    
    Pilha *pilhaCarregador = getCarregadorPilha(carr);
    if (pilhaCarregador == NULL) {
        fprintf(stderr, "Erro: pilha do carregador %s é NULL\n", idCarregador);
        return 1;
    }
    
    Fila *chao = getArenaChao(arena);
    if (chao == NULL) {
        fprintf(stderr, "Erro: chão da arena é NULL\n");
        return 1;
    }
    
    int carregadas = 0;
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "carregador %s: carregando %d formas\n", idCarregador, n);
    }
    
    for (int i = 0; i < n; i++) {
        if (filaVazia(chao)) {
            if (saidaTxt != NULL) {
                fprintf(saidaTxt, "  aviso: chão vazio, apenas %d formas carregadas\n", carregadas);
            }
            printf("  Aviso: chão vazio após %d formas\n", carregadas);
            break;
        }
        
        Forma *forma = (Forma*)desenfileira(chao);
        if (forma == NULL) {
            break;
        }
        
        empilha(pilhaCarregador, forma);
        carregadas++;
        
        if (saidaTxt != NULL && i < 5) {
            fprintf(saidaTxt, "  forma %d: id=%d tipo=%d\n", i + 1, getFormaId(forma), getFormaTipo(forma));
        }
    }
    
    printf("  Carregador %s: %d formas carregadas do chão\n", idCarregador, carregadas);
    
    return 0;
}

int exec_atch(char *idDisparador, char *idCargaEsq, char *idCargaDir, Arena arena, FILE *saidaTxt) {
    if (arena == NULL || idDisparador == NULL || idCargaEsq == NULL || idCargaDir == NULL) {
        return 1;
    }
    
    TabelaDisparadores tabelaDisp = getArenaDisparadores(arena);
    TabelaCarregadores tabelaCarr = getArenaCarregadores(arena);
    
    if (tabelaDisp == NULL || tabelaCarr == NULL) {
        return 1;
    }
    
    Disparador disp = buscaDisparador(tabelaDisp, idDisparador);
    if (disp == NULL) {
        fprintf(stderr, "Erro: disparador %s não encontrado\n", idDisparador);
        return 1;
    }
    
    Carregador carrEsq = buscaCarregador(tabelaCarr, idCargaEsq);
    if (carrEsq == NULL) {
        carrEsq = criaCarregador(idCargaEsq);
        if (carrEsq != NULL) {
            adicionaCarregador(tabelaCarr, carrEsq);
        }
    }
    
    Carregador carrDir = buscaCarregador(tabelaCarr, idCargaDir);
    if (carrDir == NULL) {
        carrDir = criaCarregador(idCargaDir);
        if (carrDir != NULL) {
            adicionaCarregador(tabelaCarr, carrDir);
        }
    }
    
    setDisparadorCarregadores(disp, carrEsq, carrDir);
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "disparador %s: carregadores encaixados (esq=%s, dir=%s)\n", 
                idDisparador, idCargaEsq, idCargaDir);
    }
    
    printf("  Disparador %s: carregadores %s (esq) e %s (dir) encaixados\n", 
           idDisparador, idCargaEsq, idCargaDir);
    return 0;
}

int exec_shft(char *idDisparador, char direcao, int n, Arena arena, FILE *saidaTxt) {
    if (arena == NULL || idDisparador == NULL || n <= 0) {
        return 1;
    }
    
    TabelaDisparadores tabelaDisp = getArenaDisparadores(arena);
    if (tabelaDisp == NULL) {
        return 1;
    }
    
    Disparador disp = buscaDisparador(tabelaDisp, idDisparador);
    if (disp == NULL) {
        fprintf(stderr, "Erro: disparador %s não encontrado\n", idDisparador);
        return 1;
    }
    
    Carregador carrEsq = getDisparadorCarregadorEsq(disp);
    Carregador carrDir = getDisparadorCarregadorDir(disp);
    
    if (carrEsq == NULL || carrDir == NULL) {
        fprintf(stderr, "Erro: carregadores não encaixados no disparador %s\n", idDisparador);
        return 1;
    }
    
    Pilha *pilhaEsq = getCarregadorPilha(carrEsq);
    Pilha *pilhaDir = getCarregadorPilha(carrDir);
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "shft disparador %s direção %c: %d movimentações\n", 
                idDisparador, direcao, n);
    }
    
    for (int i = 0; i < n; i++) {
        Forma *posicaoAtual = getDisparadorPosicaoDisparo(disp);
        
        if (direcao == 'e') {
            if (posicaoAtual != NULL) {
                empilha(pilhaDir, posicaoAtual);
            }
            
            if (!pilhaVazia(pilhaEsq)) {
                Forma *novaForma = (Forma*)desempilha(pilhaEsq);
                setDisparadorPosicaoDisparo(disp, novaForma);
            } else {
                setDisparadorPosicaoDisparo(disp, NULL);
                if (saidaTxt != NULL) {
                    fprintf(saidaTxt, "  aviso: carregador esquerdo vazio na movimentação %d\n", i + 1);
                }
            }
        }
        else if (direcao == 'd') {
            if (posicaoAtual != NULL) {
                empilha(pilhaEsq, posicaoAtual);
            }
            
            if (!pilhaVazia(pilhaDir)) {
                Forma *novaForma = (Forma*)desempilha(pilhaDir);
                setDisparadorPosicaoDisparo(disp, novaForma);
            } else {
                setDisparadorPosicaoDisparo(disp, NULL);
                if (saidaTxt != NULL) {
                    fprintf(saidaTxt, "  aviso: carregador direito vazio na movimentação %d\n", i + 1);
                }
            }
        }
    }
    
    Forma *formaFinal = getDisparadorPosicaoDisparo(disp);
    if (formaFinal != NULL) {
        printf("  Shft %s '%c' x%d: forma id=%d na posição de disparo\n", 
               idDisparador, direcao, n, getFormaId(formaFinal));
        
        if (saidaTxt != NULL) {
            fprintf(saidaTxt, "forma em posição de disparo: tipo=%d id=%d\n", 
                    getFormaTipo(formaFinal), getFormaId(formaFinal));
        }
    } else {
        printf("  Shft %s '%c' x%d: posição de disparo vazia\n", idDisparador, direcao, n);
    }
    
    return 0;
}

int exec_dsp(char *idDisparador, double dx, double dy, char modo, Arena arena, FILE *saidaTxt) {
    if (arena == NULL || idDisparador == NULL) {
        return 1;
    }
    
    TabelaDisparadores tabelaDisp = getArenaDisparadores(arena);
    if (tabelaDisp == NULL) {
        return 1;
    }
    
    Disparador disp = buscaDisparador(tabelaDisp, idDisparador);
    if (disp == NULL) {
        fprintf(stderr, "Erro: disparador %s não encontrado\n", idDisparador);
        return 1;
    }
    
    Forma *forma = getDisparadorPosicaoDisparo(disp);
    if (forma == NULL) {
        fprintf(stderr, "Erro: posição de disparo vazia no disparador %s\n", idDisparador);
        return 1;
    }
    
    double xDisp, yDisp;
    getDisparadorPosicao(disp, &xDisp, &yDisp);
    
    double xFinal = xDisp + dx;
    double yFinal = yDisp + dy;
    
    setFormaPosicao(forma, xFinal, yFinal);
    
    Fila *formasNaArena = getArenaFormasNaArena(arena);
    if (formasNaArena != NULL) {
        enfileira(formasNaArena, forma);
    }
    
    setDisparadorPosicaoDisparo(disp, NULL);
    
    incrementaNumDisparos(arena);
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "forma disparada:\n");
        fprintf(saidaTxt, "  tipo: %d\n", getFormaTipo(forma));
        fprintf(saidaTxt, "  id: %d\n", getFormaId(forma));
        fprintf(saidaTxt, "  disparador: (%.2f, %.2f)\n", xDisp, yDisp);
        fprintf(saidaTxt, "  deslocamento: (%.2f, %.2f)\n", dx, dy);
        fprintf(saidaTxt, "  posicao_final: (%.2f, %.2f)\n", xFinal, yFinal);
        fprintf(saidaTxt, "  modo: %c\n", modo);
    }
    
    printf("  Disparo: forma id=%d de (%.2f, %.2f) para (%.2f, %.2f) modo '%c'\n", 
           getFormaId(forma), xDisp, yDisp, xFinal, yFinal, modo);
    
    (void)modo;
    
    return 0;
}

int exec_rjd(char *idDisparador, char direcao, double dx, double dy, double ix, double iy, Arena arena, FILE *saidaTxt) {
    (void)arena;
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "rajada: disparador=%s dir=%c dx=%.2f dy=%.2f ix=%.2f iy=%.2f\n", 
                idDisparador, direcao, dx, dy, ix, iy);
    }
    
    printf("  Rajada: %s direção '%c' deslocamento (%.2f, %.2f) incremento (%.2f, %.2f)\n", 
           idDisparador, direcao, dx, dy, ix, iy);
    return 0;
}

int exec_calc(Arena arena, FILE *saidaTxt) {
    (void)arena;
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "processando colisões e cálculos da arena\n");
    }
    
    printf("  Calc: processando arena\n");
    return 0;
}
