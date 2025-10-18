/* Novo parserQry baseado no módulo /qry */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserQry.h"
#include "../gameState/gameState.h"
#include "../gameCommands/gameCommands.h"

#define MAX_LINE 1024

static char* construirCaminhoQry(const char *dir, const char *arquivo) {
    if (!arquivo) return NULL;
    if (!dir || strlen(dir)==0){ size_t n=strlen(arquivo)+1; char *c=malloc(n); if(c) memcpy(c, arquivo, n); return c; }
    size_t len = strlen(dir)+strlen(arquivo)+2; char *c = malloc(len); if (!c) return NULL;
    if (dir[strlen(dir)-1]=='/' || dir[strlen(dir)-1]=='\\') snprintf(c, len, "%s%s", dir, arquivo); else snprintf(c, len, "%s/%s", dir, arquivo); return c;
}

static char* construirCaminhoSaida(const char *dir, const char *base, const char *suf) {
    if (!dir || !base || !suf) return NULL;
    size_t len = strlen(dir) + 1 + strlen(base) + strlen(suf) + 1;
    char *c = (char*)malloc(len);
    if (!c) return NULL;
    if (dir[strlen(dir)-1] == '/' || dir[strlen(dir)-1] == '\\') {
        snprintf(c, len, "%s%s%s", dir, base, suf);
    } else {
        snprintf(c, len, "%s/%s%s", dir, base, suf);
    }
    return c;
}

static const char* nomeBase(const char *path){ const char *b=path; const char *s1=strrchr(path,'/'); const char *s2=strrchr(path,'\\'); if (s1 && s1>b) b=s1+1; if (s2 && s2>b) b=s2+1; return b; }

static void processarLinha(const char *linha, GameState *state, FILE *saida){
    char cmd[10]; if (sscanf(linha, "%9s", cmd) != 1) return;
    if (strcmp(cmd, "pd")==0){ int id; double x,y; if (sscanf(linha, "pd %d %lf %lf", &id,&x,&y)==3) comando_pd(state,id,x,y,saida); }
    else if (strcmp(cmd, "lc")==0){ int c,n; if (sscanf(linha, "lc %d %d", &c,&n)==2) comando_lc(state,c,n,saida); }
    else if (strcmp(cmd, "atch")==0){ int d,ce,cd; if (sscanf(linha, "atch %d %d %d", &d,&ce,&cd)==3) comando_atch(state,d,ce,cd,saida); }
    else if (strcmp(cmd, "shft")==0){ int d,n; char lado; if (sscanf(linha, "shft %d %c %d", &d,&lado,&n)==3) comando_shft(state,d,lado,n,saida); }
    else if (strcmp(cmd, "dsp")==0){ int d; double dx,dy; char t; if (sscanf(linha, "dsp %d %lf %lf %c", &d,&dx,&dy,&t)==4) comando_dsp(state,d,dx,dy,t,saida); }
    else if (strcmp(cmd, "rjd")==0){ int d; char lado; double dx,dy,ix,iy; if (sscanf(linha, "rjd %d %c %lf %lf %lf %lf", &d,&lado,&dx,&dy,&ix,&iy)==6) comando_rjd(state,d,lado,dx,dy,ix,iy,saida); }
    else if (strcmp(cmd, "calc")==0){ comando_calc(state, saida); }
}

GameState parseQry(Args args, Fila fila, Pilha pilha) {
    (void)pilha; if (!args || !fila){ fprintf(stderr,"Erro: args/fila inválidos em parseQry\n"); return NULL; }
    const char *qry = getQryFile(args); if (!qry || strlen(qry)==0){ printf("Nenhum .qry especificado.\n"); return NULL; }
    char *caminho = construirCaminhoQry(getEntryDir(args), qry); if (!caminho){ fprintf(stderr,"Erro construindo caminho .qry\n"); return NULL; }
    FILE *arq = fopen(caminho, "r"); if (!arq){ fprintf(stderr,"Erro ao abrir .qry: %s\n", caminho); free(caminho); return NULL; }
    printf("Lendo arquivo de consultas: %s\n", caminho); free(caminho);
    const char *leaf = nomeBase(qry);
    char base[256];
    size_t n = strlen(leaf);
    if (n >= sizeof(base)) n = sizeof(base)-1;
    memcpy(base, leaf, n); base[n] = '\0';
    char *dot = strrchr(base, '.');
    if (dot) *dot = '\0';
    char *pathTxt = construirCaminhoSaida(getOutputDir(args), base, "-q.txt"); FILE *out = pathTxt? fopen(pathTxt, "w") : NULL; if (out){ fprintf(out, "# Resultado da execução do arquivo .qry\n\n"); }
    GameState state = criaGameState(fila);
    char linha[MAX_LINE]; while (fgets(linha, sizeof(linha), arq)){
        size_t len=strlen(linha); if (len>0 && linha[len-1]=='\n') linha[len-1]='\0'; if (linha[0]=='\0' || linha[0]=='#') continue; processarLinha(linha, &state, out);
    }
    if (out){ fprintf(out, "\n# Execução concluída\n"); fclose(out);} if (pathTxt) free(pathTxt);
    fclose(arq); printf("Processamento de consultas concluído.\n");
    return state;
}
