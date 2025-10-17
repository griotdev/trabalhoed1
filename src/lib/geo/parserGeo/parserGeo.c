/* src/parserGeo.c
 *
 * Implementação do parser de arquivos .geo.
 * Lê o arquivo linha por linha e cria as formas correspondentes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserGeo.h"
#include "../../formas/formas/formas.h"
#include "../../estruturas/fila/fila.h"

#define MAX_LINE 1024

static char* construirCaminho(const char *dir, const char *arquivo) {
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

int parseGeo(Args args, Fila fila, Pilha pilha) {
    (void)pilha;
    
    if (args == NULL || fila == NULL) {
        fprintf(stderr, "Erro: argumentos inválidos para parseGeo.\n");
        return 1;
    }
    
    char fontFamily[50] = "sans-serif";
    char fontWeight[20] = "normal";
    double fontSize = 12.0;
    
    char *caminhoCompleto = construirCaminho(getEntryDir(args), getGeoFile(args));
    if (caminhoCompleto == NULL) {
        fprintf(stderr, "Erro ao construir caminho do arquivo .geo.\n");
        return 1;
    }
    
    FILE *arquivo = fopen(caminhoCompleto, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo .geo: %s\n", caminhoCompleto);
        free(caminhoCompleto);
        return 1;
    }
    
    printf("Lendo arquivo: %s\n", caminhoCompleto);
    free(caminhoCompleto);
    
    char linha[MAX_LINE];
    int numLinhas = 0;
    
    while (fgets(linha, MAX_LINE, arquivo) != NULL) {
        numLinhas++;
        
        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n') {
            linha[len - 1] = '\0';
        }
        
        if (strlen(linha) == 0 || linha[0] == '#') {
            continue;
        }
        
        char cmd;
        if (sscanf(linha, " %c", &cmd) != 1) {
            fprintf(stderr, "Aviso: linha %d ignorada (formato inválido).\n", numLinhas);
            continue;
        }
        
        if (cmd == 'c') {
            int id;
            double x, y, raio;
            char corBorda[20], corPreench[20];
            
            if (sscanf(linha, "c %d %lf %lf %lf %19s %19s", 
                       &id, &x, &y, &raio, corBorda, corPreench) == 6) {
                Circulo *circulo = criaCirculo(id, x, y, raio, corBorda, corPreench);
                if (circulo != NULL) {
                    Forma *forma = criaForma(TIPO_CIRCULO, circulo);
                    if (forma != NULL) {
                        enfileira(fila, forma);
                        printf("  Círculo id=%d criado: (%.1f, %.1f) r=%.1f\n", id, x, y, raio);
                    }
                }
            } else {
                fprintf(stderr, "Erro ao processar círculo na linha %d.\n", numLinhas);
            }
        }
        else if (cmd == 'r') {
            int id;
            double x, y, largura, altura;
            char corBorda[20], corPreench[20];
            
            if (sscanf(linha, "r %d %lf %lf %lf %lf %19s %19s", 
                       &id, &x, &y, &largura, &altura, corBorda, corPreench) == 7) {
                Retangulo *retangulo = criaRetangulo(id, x, y, largura, altura, corBorda, corPreench);
                if (retangulo != NULL) {
                    Forma *forma = criaForma(TIPO_RETANGULO, retangulo);
                    if (forma != NULL) {
                        enfileira(fila, forma);
                        printf("  Retângulo id=%d criado: (%.1f, %.1f) %.1fx%.1f\n", 
                               id, x, y, largura, altura);
                    }
                }
            } else {
                fprintf(stderr, "Erro ao processar retângulo na linha %d.\n", numLinhas);
            }
        }
        else if (cmd == 'l') {
            int id;
            double x1, y1, x2, y2;
            char cor[20];
            
            if (sscanf(linha, "l %d %lf %lf %lf %lf %19s", 
                       &id, &x1, &y1, &x2, &y2, cor) == 6) {
                Linha *linhaf = criaLinha(id, x1, y1, x2, y2, cor);
                if (linhaf != NULL) {
                    Forma *forma = criaForma(TIPO_LINHA, linhaf);
                    if (forma != NULL) {
                        enfileira(fila, forma);
                        printf("  Linha id=%d criada: (%.1f, %.1f) -> (%.1f, %.1f)\n", 
                               id, x1, y1, x2, y2);
                    }
                }
            } else {
                fprintf(stderr, "Erro ao processar linha na linha %d.\n", numLinhas);
            }
        }
        else if (cmd == 't' && linha[1] != 's') {
            int id;
            double x, y;
            char corBorda[20], corPreench[20];
            char ancoraChar;
            char textoConteudo[512];
            char ancoraStr[20];
            
            char *ptr = linha;
            if (sscanf(ptr, "t %d %lf %lf %19s %19s %c", 
                       &id, &x, &y, corBorda, corPreench, &ancoraChar) == 6) {
                
                if (ancoraChar == 'i') {
                    strcpy(ancoraStr, "start");
                } else if (ancoraChar == 'm') {
                    strcpy(ancoraStr, "middle");
                } else if (ancoraChar == 'f') {
                    strcpy(ancoraStr, "start");
                } else {
                    strcpy(ancoraStr, "start");
                }
                
                int count = 0;
                while (*ptr && count < 6) {
                    while (*ptr && (*ptr == ' ' || *ptr == '\t')) ptr++;
                    while (*ptr && (*ptr != ' ' && *ptr != '\t')) ptr++;
                    count++;
                }
                while (*ptr && (*ptr == ' ' || *ptr == '\t')) ptr++;
                if (*ptr) ptr++;
                while (*ptr && (*ptr == ' ' || *ptr == '\t')) ptr++;
                
                if (*ptr) {
                    strncpy(textoConteudo, ptr, 511);
                    textoConteudo[511] = '\0';
                    
                    Texto *texto = criaTexto(id, x, y, corBorda, corPreench, ancoraStr, textoConteudo,
                                             fontFamily, fontWeight, fontSize);
                    if (texto != NULL) {
                        Forma *forma = criaForma(TIPO_TEXTO, texto);
                        if (forma != NULL) {
                            enfileira(fila, forma);
                            printf("  Texto id=%d criado: \"%s\"\n", id, textoConteudo);
                        }
                    }
                }
            } else {
                fprintf(stderr, "Erro ao processar texto na linha %d.\n", numLinhas);
            }
        }
        else if (cmd == 't' && linha[1] == 's') {
            char family[20], weight[10];
            double size;
            
            if (sscanf(linha, "ts %19s %9s %lf", family, weight, &size) == 3) {
                if (strcmp(family, "sans") == 0) {
                    strcpy(fontFamily, "sans-serif");
                } else if (strcmp(family, "serif") == 0) {
                    strcpy(fontFamily, "serif");
                } else if (strcmp(family, "cursive") == 0) {
                    strcpy(fontFamily, "cursive");
                } else {
                    strcpy(fontFamily, "sans-serif");
                }
                
                if (strcmp(weight, "n") == 0) {
                    strcpy(fontWeight, "normal");
                } else if (strcmp(weight, "b") == 0) {
                    strcpy(fontWeight, "bold");
                } else if (strcmp(weight, "b+") == 0) {
                    strcpy(fontWeight, "bolder");
                } else if (strcmp(weight, "l") == 0) {
                    strcpy(fontWeight, "lighter");
                } else {
                    strcpy(fontWeight, "normal");
                }
                
                fontSize = size;
                
                printf("  Estilo de texto alterado: family=%s, weight=%s, size=%.1f\n", 
                       fontFamily, fontWeight, fontSize);
            } else {
                fprintf(stderr, "Erro ao processar comando ts na linha %d.\n", numLinhas);
            }
        }
        else {
            fprintf(stderr, "Aviso: comando '%c' desconhecido na linha %d.\n", cmd, numLinhas);
        }
    }
    
    fclose(arquivo);
    printf("Parse do arquivo .geo concluído. %d formas carregadas.\n", tamanhoFila(fila));
    
    return 0;
}
