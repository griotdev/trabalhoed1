# Makefile para o programa ted
# Compilador e flags
CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -Werror=implicit-function-declaration
LDFLAGS = -lm

# Nome do executável
PROJ_NAME = ted

# Diretórios
SRC_DIR = .
OBJ_DIR = obj

# Diretórios das categorias
FORMAS_DIR = formas
ESTRUTURAS_DIR = estruturas
GEO_DIR = geo
UTILS_DIR = utils

# Arquivos fonte organizados por categoria
MAIN_SRC = main.c

FORMAS_SRC = $(FORMAS_DIR)/circulo/circulo.c \
             $(FORMAS_DIR)/retangulo/retangulo.c \
             $(FORMAS_DIR)/linha/linha.c \
             $(FORMAS_DIR)/texto/texto.c \
             $(FORMAS_DIR)/formas/formas.c

ESTRUTURAS_SRC = $(ESTRUTURAS_DIR)/fila/fila.c \
                 $(ESTRUTURAS_DIR)/pilha/pilha.c

GEO_SRC = $(GEO_DIR)/geoHandler/geoHandler.c \
          $(GEO_DIR)/svg/svg.c

UTILS_SRC = $(UTILS_DIR)/argumentHandler/argumentHandler.c \
            $(UTILS_DIR)/saida/saida.c

# Todos os arquivos fonte
SOURCES = $(MAIN_SRC) $(FORMAS_SRC) $(ESTRUTURAS_SRC) $(GEO_SRC) $(UTILS_SRC)

# Objetos (mantém os nomes simples no obj/)
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/circulo.o $(OBJ_DIR)/retangulo.o $(OBJ_DIR)/linha.o $(OBJ_DIR)/texto.o $(OBJ_DIR)/formas.o \
          $(OBJ_DIR)/fila.o $(OBJ_DIR)/pilha.o \
          $(OBJ_DIR)/geoHandler.o $(OBJ_DIR)/svg.o \
          $(OBJ_DIR)/argumentHandler.o $(OBJ_DIR)/saida.o

# Regra principal
all: $(OBJ_DIR) $(PROJ_NAME)

# Criar diretório de objetos
$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

# Regra para criar o executável
$(PROJ_NAME): $(OBJECTS)
    $(CC) $(CFLAGS) -o $(PROJ_NAME) $(OBJECTS) $(LDFLAGS)
    @echo "Executável '$(PROJ_NAME)' criado com sucesso!"

# Regras para compilar objetos
# Main
$(OBJ_DIR)/main.o: main.c $(UTILS_DIR)/argumentHandler/argumentHandler.h $(GEO_DIR)/geoHandler/geoHandler.h $(ESTRUTURAS_DIR)/fila/fila.h $(ESTRUTURAS_DIR)/pilha/pilha.h $(GEO_DIR)/svg/svg.h $(UTILS_DIR)/saida/saida.h $(FORMAS_DIR)/formas/formas.h
    $(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

# Formas
$(OBJ_DIR)/circulo.o: $(FORMAS_DIR)/circulo/circulo.c $(FORMAS_DIR)/circulo/circulo.h
    $(CC) $(CFLAGS) -c $(FORMAS_DIR)/circulo/circulo.c -o $(OBJ_DIR)/circulo.o

$(OBJ_DIR)/retangulo.o: $(FORMAS_DIR)/retangulo/retangulo.c $(FORMAS_DIR)/retangulo/retangulo.h
    $(CC) $(CFLAGS) -c $(FORMAS_DIR)/retangulo/retangulo.c -o $(OBJ_DIR)/retangulo.o

$(OBJ_DIR)/linha.o: $(FORMAS_DIR)/linha/linha.c $(FORMAS_DIR)/linha/linha.h
    $(CC) $(CFLAGS) -c $(FORMAS_DIR)/linha/linha.c -o $(OBJ_DIR)/linha.o

$(OBJ_DIR)/texto.o: $(FORMAS_DIR)/texto/texto.c $(FORMAS_DIR)/texto/texto.h
    $(CC) $(CFLAGS) -c $(FORMAS_DIR)/texto/texto.c -o $(OBJ_DIR)/texto.o

$(OBJ_DIR)/formas.o: $(FORMAS_DIR)/formas/formas.c $(FORMAS_DIR)/formas/formas.h $(FORMAS_DIR)/circulo/circulo.h $(FORMAS_DIR)/retangulo/retangulo.h $(FORMAS_DIR)/linha/linha.h $(FORMAS_DIR)/texto/texto.h
    $(CC) $(CFLAGS) -c $(FORMAS_DIR)/formas/formas.c -o $(OBJ_DIR)/formas.o

# Estruturas de dados
$(OBJ_DIR)/fila.o: $(ESTRUTURAS_DIR)/fila/fila.c $(ESTRUTURAS_DIR)/fila/fila.h
    $(CC) $(CFLAGS) -c $(ESTRUTURAS_DIR)/fila/fila.c -o $(OBJ_DIR)/fila.o

$(OBJ_DIR)/pilha.o: $(ESTRUTURAS_DIR)/pilha/pilha.c $(ESTRUTURAS_DIR)/pilha/pilha.h
    $(CC) $(CFLAGS) -c $(ESTRUTURAS_DIR)/pilha/pilha.c -o $(OBJ_DIR)/pilha.o

# GEO (geoHandler e svg)
$(OBJ_DIR)/geoHandler.o: $(GEO_DIR)/geoHandler/geoHandler.c $(GEO_DIR)/geoHandler/geoHandler.h $(FORMAS_DIR)/formas/formas.h $(ESTRUTURAS_DIR)/fila/fila.h $(UTILS_DIR)/argumentHandler/argumentHandler.h
    $(CC) $(CFLAGS) -c $(GEO_DIR)/geoHandler/geoHandler.c -o $(OBJ_DIR)/geoHandler.o

$(OBJ_DIR)/svg.o: $(GEO_DIR)/svg/svg.c $(GEO_DIR)/svg/svg.h $(FORMAS_DIR)/formas/formas.h $(ESTRUTURAS_DIR)/fila/fila.h
    $(CC) $(CFLAGS) -c $(GEO_DIR)/svg/svg.c -o $(OBJ_DIR)/svg.o

# Utils
$(OBJ_DIR)/argumentHandler.o: $(UTILS_DIR)/argumentHandler/argumentHandler.c $(UTILS_DIR)/argumentHandler/argumentHandler.h
    $(CC) $(CFLAGS) -c $(UTILS_DIR)/argumentHandler/argumentHandler.c -o $(OBJ_DIR)/argumentHandler.o

$(OBJ_DIR)/saida.o: $(UTILS_DIR)/saida/saida.c $(UTILS_DIR)/saida/saida.h
    $(CC) $(CFLAGS) -c $(UTILS_DIR)/saida/saida.c -o $(OBJ_DIR)/saida.o

# Limpeza
clean:
    rm -rf $(OBJ_DIR)
    rm -f $(PROJ_NAME).exe
    rm -f $(PROJ_NAME)
    @echo Arquivos de compilacao removidos.

# Limpeza completa (inclui saídas geradas)
distclean: clean
    rm -f ../saida/*
    @echo Diretorio de saida limpo.

# Executar exemplo
run: $(PROJ_NAME)
    ./$(PROJ_NAME) -f ../testes/figs-alet.geo -o ../saida/

# Executar com Valgrind (verificação de memória)
valgrind: $(PROJ_NAME)
    valgrind --leak-check=full --show-leak-kinds=all ./$(PROJ_NAME) -f ../testes/figs-alet.geo -o ../saida/

.PHONY: all clean distclean run valgrind
