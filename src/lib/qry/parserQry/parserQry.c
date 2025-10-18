#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserQry.h"
#include "../comandos/comandos.h"
#include "../arena/arena.h"
#include "../../argumentos/argumentHandler.h"

#define MAX_LINE 1024

typedef struct arena_internal {
    Fila *chao;
    Fila formasNaArena;
    TabelaDisparadores disparadores;
    TabelaCarregadores carregadores;
    int numDisparos;
    int numInstrucoes;
    int numEsmagadas;
    int numClonadas;
    double pontuacaoTotal;
} ArenaInternal;

Arena criaArena(void) {
    ArenaInternal *arena = (ArenaInternal*)malloc(sizeof(ArenaInternal));
    if (arena == NULL) {
        fprintf(stderr, "Erro ao alocar memória para Arena.\n");
        return NULL;
    }
    
    arena->chao = NULL;
    arena->formasNaArena = criaFila();
    arena->disparadores = criaTabelaDisparadores();
    arena->carregadores = criaTabelaCarregadores();
    arena->numDisparos = 0;
    arena->numInstrucoes = 0;
    arena->numEsmagadas = 0;
    arena->numClonadas = 0;
    arena->pontuacaoTotal = 0.0;
    
    if (arena->formasNaArena == NULL || arena->disparadores == NULL || arena->carregadores == NULL) {
        if (arena->formasNaArena != NULL) destroiFila(arena->formasNaArena, NULL);
        if (arena->disparadores != NULL) destroiTabelaDisparadores(&arena->disparadores);
        if (arena->carregadores != NULL) destroiTabelaCarregadores(&arena->carregadores);
        free(arena);
        return NULL;
    }
    
    return (Arena)arena;
}

void destroiArena(Arena *arena) {
    if (arena == NULL || *arena == NULL) {
        return;
    }
    
    ArenaInternal *a = (ArenaInternal*)(*arena);
    
    if (a->formasNaArena != NULL) {
        destroiFila(a->formasNaArena, NULL);
    }
    
    if (a->disparadores != NULL) {
        destroiTabelaDisparadores(&a->disparadores);
    }
    
    if (a->carregadores != NULL) {
        destroiTabelaCarregadores(&a->carregadores);
    }
    
    free(a);
    *arena = NULL;
}

static char* construirCaminhoQry(const char *dir, const char *arquivo) {
    if (arquivo == NULL) {
        return NULL;
    }
    
    if (dir == NULL || strlen(dir) == 0) {
        size_t len_arq = strlen(arquivo) + 1;
        char *copia = (char*)malloc(len_arq);
        if (copia != NULL) {
            memcpy(copia, arquivo, len_arq);
        }
        return copia;
    }
    
    size_t len = strlen(dir) + strlen(arquivo) + 2;
    char *caminho = (char*)malloc(len);
    if (caminho == NULL) {
        return NULL;
    }
    
    if (dir[strlen(dir) - 1] == '/' || dir[strlen(dir) - 1] == '\\') {
        snprintf(caminho, len, "%s%s", dir, arquivo);
    } else {
        snprintf(caminho, len, "%s/%s", dir, arquivo);
    }
    
    return caminho;
}

int parseQry(Args args, Fila *filaChao, const char *caminhoSvgBase) {
    if (args == NULL || filaChao == NULL) {
        fprintf(stderr, "Erro: argumentos inválidos para parseQry.\n");
        return 1;
    }
    
    char *arquivoQry = getQryFile(args);
    if (arquivoQry == NULL || strlen(arquivoQry) == 0) {
        printf("Nenhum arquivo .qry especificado. Pulando processamento de consultas.\n");
        return 0;
    }
    
    char *caminhoCompleto = construirCaminhoQry(getEntryDir(args), arquivoQry);
    if (caminhoCompleto == NULL) {
        fprintf(stderr, "Erro ao construir caminho do arquivo .qry.\n");
        return 1;
    }
    
    FILE *arquivo = fopen(caminhoCompleto, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo .qry: %s\n", caminhoCompleto);
        free(caminhoCompleto);
        return 1;
    }
    
    printf("\n=== Processando arquivo .qry ===\n");
    printf("Lendo arquivo: %s\n", caminhoCompleto);
    free(caminhoCompleto);
    
    Arena arena = criaArena();
    if (arena == NULL) {
        fclose(arquivo);
        return 1;
    }
    
    ArenaInternal *a = (ArenaInternal*)arena;
    a->chao = filaChao;
    
    char linha[MAX_LINE];
    int numLinhas = 0;
    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        numLinhas++;
        
        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n') {
            linha[len - 1] = '\0';
        }
        
        if (strlen(linha) == 0 || linha[0] == '#') {
            continue;
        }
        
        a->numInstrucoes++;
        
        printf("  [*] %s\n", linha);
        
        int cmdStatus = exec_comando(linha, arena, NULL);
        if (cmdStatus != 0) {
            fprintf(stderr, "  Erro ao executar comando.\n");
        }
    }
    
    printf("Parse do arquivo .qry concluído. %d linhas processadas.\n", numLinhas);
    printf("Total de instruções: %d\n", a->numInstrucoes);
    
    destroiArena(&arena);
    fclose(arquivo);
    
    (void)caminhoSvgBase;
    
    return 0;
}

TabelaDisparadores getArenaDisparadores(Arena arena) {
    if (arena == NULL) return NULL;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->disparadores;
}

TabelaCarregadores getArenaCarregadores(Arena arena) {
    if (arena == NULL) return NULL;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->carregadores;
}

Fila* getArenaChao(Arena arena) {
    if (arena == NULL) return NULL;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->chao;
}

Fila* getArenaFormasNaArena(Arena arena) {
    if (arena == NULL) return NULL;
    ArenaInternal *a = (ArenaInternal*)arena;
    return &a->formasNaArena;
}

void incrementaNumDisparos(Arena arena) {
    if (arena == NULL) return;
    ArenaInternal *a = (ArenaInternal*)arena;
    a->numDisparos++;
}

void incrementaNumEsmagadas(Arena arena) {
    if (arena == NULL) return;
    ArenaInternal *a = (ArenaInternal*)arena;
    a->numEsmagadas++;
}

void incrementaNumClonadas(Arena arena) {
    if (arena == NULL) return;
    ArenaInternal *a = (ArenaInternal*)arena;
    a->numClonadas++;
}

void adicionaPontuacao(Arena arena, double pontos) {
    if (arena == NULL) return;
    ArenaInternal *a = (ArenaInternal*)arena;
    a->pontuacaoTotal += pontos;
}

int getArenaNumInstrucoes(Arena arena) {
    if (arena == NULL) return 0;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->numInstrucoes;
}

int getArenaNumDisparos(Arena arena) {
    if (arena == NULL) return 0;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->numDisparos;
}

int getArenaNumEsmagadas(Arena arena) {
    if (arena == NULL) return 0;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->numEsmagadas;
}

int getArenaNumClonadas(Arena arena) {
    if (arena == NULL) return 0;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->numClonadas;
}

double getArenaPontuacao(Arena arena) {
    if (arena == NULL) return 0.0;
    ArenaInternal *a = (ArenaInternal*)arena;
    return a->pontuacaoTotal;
}
