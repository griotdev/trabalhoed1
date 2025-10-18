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
    (void)arena;
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "carregador %s: %d formas carregadas\n", idCarregador, n);
    }
    
    printf("  Carregador %s: %d formas carregadas\n", idCarregador, n);
    return 0;
}

int exec_atch(char *idDisparador, char *idCargaEsq, char *idCargaDir, Arena arena, FILE *saidaTxt) {
    (void)arena;
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "disparador %s: carregadores encaixados (esq=%s, dir=%s)\n", 
                idDisparador, idCargaEsq, idCargaDir);
    }
    
    printf("  Disparador %s encaixado com carregadores %s (esq) e %s (dir)\n", 
           idDisparador, idCargaEsq, idCargaDir);
    return 0;
}

int exec_shft(char *idDisparador, char direcao, int n, Arena arena, FILE *saidaTxt) {
    (void)arena;
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "shft disparador %s direção %c: %d movimentações\n", 
                idDisparador, direcao, n);
    }
    
    printf("  Shft %s direção '%c': %d movimentações\n", idDisparador, direcao, n);
    return 0;
}

int exec_dsp(char *idDisparador, double dx, double dy, char modo, Arena arena, FILE *saidaTxt) {
    (void)arena;
    
    if (saidaTxt != NULL) {
        fprintf(saidaTxt, "forma disparada: disparador=%s dx=%.2f dy=%.2f modo=%c\n", 
                idDisparador, dx, dy, modo);
    }
    
    printf("  Disparo: %s com deslocamento (%.2f, %.2f) modo '%c'\n", 
           idDisparador, dx, dy, modo);
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
