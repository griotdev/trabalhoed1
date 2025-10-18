#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svgQry.h"
#include "../../geo/svg/svg.h"

FILE* svgQryAbreArquivo(const char *nomeArquivo, int largura, int altura) {
    if (nomeArquivo == NULL) {
        return NULL;
    }
    
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao criar arquivo SVG QRY: %s\n", nomeArquivo);
        return NULL;
    }
    
    // Cabeçalho SVG
    fprintf(arquivo, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(arquivo, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" "
                     "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
    fprintf(arquivo, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\" "
                     "xmlns:svg=\"http://www.w3.org/2000/svg\">\n", largura, altura);
    fprintf(arquivo, "  <desc>Eventos do arquivo .qry - Bocha Geométrica</desc>\n");
    fprintf(arquivo, "  <rect width=\"%d\" height=\"%d\" fill=\"#f0f0f0\" />\n", largura, altura);
    
    return arquivo;
}

void svgQryDesenhaDisparador(FILE *arquivo, const char *id, double x, double y) {
    if (arquivo == NULL || id == NULL) {
        return;
    }
    
    // Desenha um círculo preto para marcar o disparador
    fprintf(arquivo, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"5\" fill=\"black\" stroke=\"red\" stroke-width=\"2\" />\n", x, y);
    // Adiciona o ID ao lado
    fprintf(arquivo, "  <text x=\"%.2f\" y=\"%.2f\" font-size=\"10\" fill=\"red\" font-weight=\"bold\">D%s</text>\n", 
            x + 8, y + 4, id);
}

void svgQryDesenhaTrajetoria(FILE *arquivo, double x1, double y1, double x2, double y2, const char *cor) {
    if (arquivo == NULL || cor == NULL) {
        return;
    }
    
    // Linha tracejada para mostrar a trajetória
    fprintf(arquivo, "  <line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
                     "stroke=\"%s\" stroke-width=\"2\" stroke-dasharray=\"5,5\" opacity=\"0.6\" />\n",
            x1, y1, x2, y2, cor);
    
    // Seta no final da trajetória
    fprintf(arquivo, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"3\" fill=\"%s\" />\n", x2, y2, cor);
}

void svgQryMarcaColisao(FILE *arquivo, double x, double y) {
    if (arquivo == NULL) {
        return;
    }
    
    // Desenha asterisco vermelho no ponto de colisão
    fprintf(arquivo, "  <text x=\"%.2f\" y=\"%.2f\" font-size=\"20\" fill=\"red\" font-weight=\"bold\" "
                     "text-anchor=\"middle\">*</text>\n", x, y + 5);
}

void svgQryDesenhaFormaArena(FILE *arquivo, Forma *forma, double opacidade) {
    if (arquivo == NULL || forma == NULL) {
        return;
    }
    
    TipoForma tipo = getFormaTipo(forma);
    
    if (tipo == TIPO_CIRCULO) {
        Circulo c = (Circulo)getFormaDados(forma);
        double x = getCirculoX(c);
        double y = getCirculoY(c);
        double r = getCirculoRaio(c);
        const char *corBorda = getCirculoCorBorda(c);
        const char *corPreench = getCirculoCorPreenchimento(c);
        
        fprintf(arquivo, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" "
                         "fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" opacity=\"%.2f\" />\n",
                x, y, r, corPreench, corBorda, opacidade);
    }
    else if (tipo == TIPO_RETANGULO) {
        Retangulo r = (Retangulo)getFormaDados(forma);
        double x = getRetanguloX(r);
        double y = getRetanguloY(r);
        double w = getRetanguloLargura(r);
        double h = getRetanguloAltura(r);
        const char *corBorda = getRetanguloCorBorda(r);
        const char *corPreench = getRetanguloCorPreenchimento(r);
        
        fprintf(arquivo, "  <rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" "
                         "fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" opacity=\"%.2f\" />\n",
                x, y, w, h, corPreench, corBorda, opacidade);
    }
    // Adicionar suporte para linha e texto se necessário
}

void svgQryAdicionaTexto(FILE *arquivo, double x, double y, const char *texto) {
    if (arquivo == NULL || texto == NULL) {
        return;
    }
    
    fprintf(arquivo, "  <text x=\"%.2f\" y=\"%.2f\" font-size=\"12\" fill=\"blue\" "
                     "font-family=\"monospace\">%s</text>\n", x, y, texto);
}

void svgQryFechaArquivo(FILE *arquivo) {
    if (arquivo == NULL) {
        return;
    }
    
    fprintf(arquivo, "</svg>\n");
    fclose(arquivo);
}
