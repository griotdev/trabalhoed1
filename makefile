## Root Makefile: full build (no delegation), binary at project root

CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -Werror=implicit-function-declaration
LDFLAGS = -lm

PROJ_NAME = ted

# Defaults for convenience targets (override with: make run GEO=... QRY=...)
ENTRY_DIR ?= testes
OUTPUT_DIR ?= saida
GEO ?= figs-alet.geo
# QRY is optional

SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib
OBJ_DIR = $(SRC_DIR)/obj

FORMAS_DIR = $(LIB_DIR)/formas
ESTRUTURAS_DIR = $(LIB_DIR)/estruturas
GEO_DIR = $(LIB_DIR)/geo
QRY_DIR = $(LIB_DIR)/qry
ARGUMENTOS_DIR = $(LIB_DIR)/argumentos

MAIN_SRC = $(SRC_DIR)/main.c

FORMAS_SRC = $(FORMAS_DIR)/circulo/circulo.c \
             $(FORMAS_DIR)/retangulo/retangulo.c \
             $(FORMAS_DIR)/linha/linha.c \
             $(FORMAS_DIR)/texto/texto.c \
             $(FORMAS_DIR)/formas/formas.c

ESTRUTURAS_SRC = $(ESTRUTURAS_DIR)/fila/fila.c \
                 $(ESTRUTURAS_DIR)/pilha/pilha.c

GEO_SRC = $(GEO_DIR)/parserGeo/parserGeo.c \
          $(GEO_DIR)/svg/svg.c

QRY_SRC = $(QRY_DIR)/parserQry/parserQry.c \
		  $(QRY_DIR)/gameState/gameState.c \
		  $(QRY_DIR)/gameCommands/gameCommands.c \
		  $(QRY_DIR)/formaUtils/formaUtils.c \
		  $(QRY_DIR)/formaUtils/colorRules.c \
		  $(QRY_DIR)/disparador/disparador.c \
		  $(QRY_DIR)/carregadorManager/carregadorManager.c

ARGUMENTOS_SRC = $(ARGUMENTOS_DIR)/argumentHandler.c

SOURCES = $(MAIN_SRC) $(FORMAS_SRC) $(ESTRUTURAS_SRC) $(GEO_SRC) $(QRY_SRC) $(ARGUMENTOS_SRC)

OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/circulo.o $(OBJ_DIR)/retangulo.o $(OBJ_DIR)/linha.o $(OBJ_DIR)/texto.o $(OBJ_DIR)/formas.o \
          $(OBJ_DIR)/fila.o $(OBJ_DIR)/pilha.o \
          $(OBJ_DIR)/parserGeo.o $(OBJ_DIR)/svg.o \
          $(OBJ_DIR)/parserQry.o $(OBJ_DIR)/gameState.o $(OBJ_DIR)/gameCommands.o $(OBJ_DIR)/formaUtils.o $(OBJ_DIR)/colorRules.o $(OBJ_DIR)/disparador.o $(OBJ_DIR)/carregadorManager.o \
		  $(OBJ_DIR)/argumentHandler.o $(OBJ_DIR)/colisao.o \
		  $(OBJ_DIR)/svgQry.o $(OBJ_DIR)/saidaQry.o

.PHONY: all clean distclean run valgrind

all: $(OBJ_DIR) $(PROJ_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(PROJ_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROJ_NAME) $(OBJECTS) $(LDFLAGS)
	@echo "Executável '$(PROJ_NAME)' criado com sucesso!"

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/circulo.o: $(FORMAS_DIR)/circulo/circulo.c $(FORMAS_DIR)/circulo/circulo.h
	$(CC) $(CFLAGS) -c $(FORMAS_DIR)/circulo/circulo.c -o $(OBJ_DIR)/circulo.o

$(OBJ_DIR)/retangulo.o: $(FORMAS_DIR)/retangulo/retangulo.c $(FORMAS_DIR)/retangulo/retangulo.h
	$(CC) $(CFLAGS) -c $(FORMAS_DIR)/retangulo/retangulo.c -o $(OBJ_DIR)/retangulo.o

$(OBJ_DIR)/linha.o: $(FORMAS_DIR)/linha/linha.c $(FORMAS_DIR)/linha/linha.h
	$(CC) $(CFLAGS) -c $(FORMAS_DIR)/linha/linha.c -o $(OBJ_DIR)/linha.o

$(OBJ_DIR)/texto.o: $(FORMAS_DIR)/texto/texto.c $(FORMAS_DIR)/texto/texto.h
	$(CC) $(CFLAGS) -c $(FORMAS_DIR)/texto/texto.c -o $(OBJ_DIR)/texto.o

$(OBJ_DIR)/formas.o: $(FORMAS_DIR)/formas/formas.c $(FORMAS_DIR)/formas/formas.h
	$(CC) $(CFLAGS) -c $(FORMAS_DIR)/formas/formas.c -o $(OBJ_DIR)/formas.o

$(OBJ_DIR)/fila.o: $(ESTRUTURAS_DIR)/fila/fila.c $(ESTRUTURAS_DIR)/fila/fila.h
	$(CC) $(CFLAGS) -c $(ESTRUTURAS_DIR)/fila/fila.c -o $(OBJ_DIR)/fila.o

$(OBJ_DIR)/pilha.o: $(ESTRUTURAS_DIR)/pilha/pilha.c $(ESTRUTURAS_DIR)/pilha/pilha.h
	$(CC) $(CFLAGS) -c $(ESTRUTURAS_DIR)/pilha/pilha.c -o $(OBJ_DIR)/pilha.o

$(OBJ_DIR)/parserGeo.o: $(GEO_DIR)/parserGeo/parserGeo.c $(GEO_DIR)/parserGeo/parserGeo.h
	$(CC) $(CFLAGS) -c $(GEO_DIR)/parserGeo/parserGeo.c -o $(OBJ_DIR)/parserGeo.o

$(OBJ_DIR)/svg.o: $(GEO_DIR)/svg/svg.c $(GEO_DIR)/svg/svg.h
	$(CC) $(CFLAGS) -c $(GEO_DIR)/svg/svg.c -o $(OBJ_DIR)/svg.o

$(OBJ_DIR)/parserQry.o: $(QRY_DIR)/parserQry/parserQry.c $(QRY_DIR)/parserQry/parserQry.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/parserQry/parserQry.c -o $(OBJ_DIR)/parserQry.o

$(OBJ_DIR)/gameState.o: $(QRY_DIR)/gameState/gameState.c $(QRY_DIR)/gameState/gameState.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/gameState/gameState.c -o $(OBJ_DIR)/gameState.o

$(OBJ_DIR)/gameCommands.o: $(QRY_DIR)/gameCommands/gameCommands.c $(QRY_DIR)/gameCommands/gameCommands.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/gameCommands/gameCommands.c -o $(OBJ_DIR)/gameCommands.o

$(OBJ_DIR)/formaUtils.o: $(QRY_DIR)/formaUtils/formaUtils.c $(QRY_DIR)/formaUtils/formaUtils.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/formaUtils/formaUtils.c -o $(OBJ_DIR)/formaUtils.o

$(OBJ_DIR)/colorRules.o: $(QRY_DIR)/formaUtils/colorRules.c $(QRY_DIR)/formaUtils/colorRules.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/formaUtils/colorRules.c -o $(OBJ_DIR)/colorRules.o

$(OBJ_DIR)/disparador.o: $(QRY_DIR)/disparador/disparador.c $(QRY_DIR)/disparador/disparador.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/disparador/disparador.c -o $(OBJ_DIR)/disparador.o

$(OBJ_DIR)/carregadorManager.o: $(QRY_DIR)/carregadorManager/carregadorManager.c $(QRY_DIR)/carregadorManager/carregadorManager.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/carregadorManager/carregadorManager.c -o $(OBJ_DIR)/carregadorManager.o

$(OBJ_DIR)/argumentHandler.o: $(ARGUMENTOS_DIR)/argumentHandler.c $(ARGUMENTOS_DIR)/argumentHandler.h
	$(CC) $(CFLAGS) -c $(ARGUMENTOS_DIR)/argumentHandler.c -o $(OBJ_DIR)/argumentHandler.o

$(OBJ_DIR)/colisao.o: $(QRY_DIR)/colisao/colisao.c $(QRY_DIR)/colisao/colisao.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/colisao/colisao.c -o $(OBJ_DIR)/colisao.o

$(OBJ_DIR)/svgQry.o: $(QRY_DIR)/svgQry/svgQry.c $(QRY_DIR)/svgQry/svgQry.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/svgQry/svgQry.c -o $(OBJ_DIR)/svgQry.o

$(OBJ_DIR)/saidaQry.o: $(QRY_DIR)/saida/saidaQry.c $(QRY_DIR)/saida/saidaQry.h
	$(CC) $(CFLAGS) -c $(QRY_DIR)/saida/saidaQry.c -o $(OBJ_DIR)/saidaQry.o

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(PROJ_NAME) $(PROJ_NAME).exe
	@echo "Arquivos de compilação removidos."

distclean: clean
	rm -f $(OUTPUT_DIR)/*
	@echo "Diretório de saída limpo."

run: all
	@if [ -n "$(QRY)" ]; then \
		./$(PROJ_NAME) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)" -q "$(QRY)"; \
	else \
		./$(PROJ_NAME) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)"; \
	fi

valgrind: all
	@if [ -n "$(QRY)" ]; then \
		valgrind --leak-check=full --show-leak-kinds=all ./$(PROJ_NAME) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)" -q "$(QRY)"; \
	else \
		valgrind --leak-check=full --show-leak-kinds=all ./$(PROJ_NAME) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)"; \
	fi
