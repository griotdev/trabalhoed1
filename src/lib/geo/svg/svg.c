#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "../../formas/formas/formas.h"
#include "../../estruturas/fila/fila.h"

FILE* svgCriaArquivo(const char *nomeArquivo, int largura, int altura) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao criar arquivo SVG: %s\n", nomeArquivo);
        return NULL;
    }
    
    fprintf(arquivo, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(arquivo, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n", 
            largura, altura);
    fprintf(arquivo, "  <!-- Gerado pelo programa ted -->\n");
    
    return arquivo;
}

void svgEscreveCirculo(FILE *arquivo, Circulo *circulo) {
    if (arquivo == NULL || circulo == NULL) {
        return;
    }
    
    fprintf(arquivo, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" ",
            getCirculoX(circulo), getCirculoY(circulo), getCirculoRaio(circulo));
    fprintf(arquivo, "stroke=\"%s\" fill=\"%s\" />\n",
            getCirculoCorBorda(circulo), getCirculoCorPreenchimento(circulo));
}

void svgEscreveRetangulo(FILE *arquivo, Retangulo *retangulo) {
    if (arquivo == NULL || retangulo == NULL) {
        return;
    }
    
    fprintf(arquivo, "  <rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" ",
            getRetanguloX(retangulo), getRetanguloY(retangulo),
            getRetanguloLargura(retangulo), getRetanguloAltura(retangulo));
    fprintf(arquivo, "stroke=\"%s\" fill=\"%s\" />\n",
            getRetanguloCorBorda(retangulo), getRetanguloCorPreenchimento(retangulo));
}

void svgEscreveLinha(FILE *arquivo, Linha *linha) {
    if (arquivo == NULL || linha == NULL) {
        return;
    }
    
    fprintf(arquivo, "  <line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" ",
            getLinhaX1(linha), getLinhaY1(linha), getLinhaX2(linha), getLinhaY2(linha));
    fprintf(arquivo, "stroke=\"%s\" />\n", getLinhaCor(linha));
}

void svgEscreveTexto(FILE *arquivo, Texto *texto) {
    if (arquivo == NULL || texto == NULL) {
        return;
    }
    
    fprintf(arquivo, "  <text x=\"%.2f\" y=\"%.2f\" ",
            getTextoX(texto), getTextoY(texto));
    fprintf(arquivo, "text-anchor=\"%s\" stroke=\"%s\" fill=\"%s\" ",
            getTextoAncora(texto), getTextoCorBorda(texto), 
            getTextoCorPreenchimento(texto));
    fprintf(arquivo, "font-family=\"%s\" font-weight=\"%s\" font-size=\"%.1f\">%s</text>\n",
            getTextoFontFamily(texto), getTextoFontWeight(texto), 
            getTextoFontSize(texto), getTextoConteudo(texto));
}

void svgEscreveForma(FILE *arquivo, Forma *forma) {
    if (arquivo == NULL || forma == NULL) {
        return;
    }
    
    TipoForma tipo = getFormaTipo(forma);
    void *dados = getFormaDados(forma);
    
    switch (tipo) {
        case TIPO_CIRCULO:
            svgEscreveCirculo(arquivo, (Circulo*)dados);
            break;
        case TIPO_RETANGULO:
            svgEscreveRetangulo(arquivo, (Retangulo*)dados);
            break;
        case TIPO_LINHA:
            svgEscreveLinha(arquivo, (Linha*)dados);
            break;
        case TIPO_TEXTO:
            svgEscreveTexto(arquivo, (Texto*)dados);
            break;
        default:
            fprintf(stderr, "Aviso: tipo de forma desconhecido.\n");
            break;
    }
}

void svgFechaArquivo(FILE *arquivo) {
    if (arquivo == NULL) {
        return;
    }
    
    fprintf(arquivo, "</svg>\n");
    fclose(arquivo);
}

int svgGeraArquivo(const char *nomeArquivo, Fila *fila, int largura, int altura) {
    if (nomeArquivo == NULL || fila == NULL) {
        fprintf(stderr, "Erro: parâmetros inválidos para svgGeraArquivo.\n");
        return 1;
    }
    
    FILE *arquivo = svgCriaArquivo(nomeArquivo, largura, altura);
    if (arquivo == NULL) {
        return 1;
    }
    
    Fila *filaTemp = criaFila();
    if (filaTemp == NULL) {
        svgFechaArquivo(arquivo);
        return 1;
    }
    
    while (!filaVazia(fila)) {
        Forma *forma = (Forma*)desenfileira(fila);
        if (forma != NULL) {
            svgEscreveForma(arquivo, forma);
            enfileira(filaTemp, forma);
        }
    }
    
    while (!filaVazia(filaTemp)) {
        Forma *forma = (Forma*)desenfileira(filaTemp);
        enfileira(fila, forma);
    }
    
    destroiFila(filaTemp, NULL);
    svgFechaArquivo(arquivo);
    
    printf("Arquivo SVG gerado: %s\n", nomeArquivo);
    return 0;
}
