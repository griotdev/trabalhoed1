# =============================================================================
# Makefile - Projeto Estrutura de Dados (Jogo de Esmagamento)
# =============================================================================

CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -Werror=implicit-function-declaration
LDFLAGS = -lm

TARGET = ted
BUILD_DIR = obj
LIB_DIR = lib

# =============================================================================
# Diretórios
# =============================================================================

FORMAS_DIR = $(LIB_DIR)/formas
ESTRUTURAS_DIR = $(LIB_DIR)/estruturas
GEO_DIR = $(LIB_DIR)/geo
QRY_DIR = $(LIB_DIR)/qry
ARGUMENTOS_DIR = $(LIB_DIR)/argumentos

# =============================================================================
# Arquivos fonte
# =============================================================================

# Entry point
MAIN_SRC = main.c

# Formas geométricas
CIRCULO_SRC = $(FORMAS_DIR)/circulo/circulo.c
RETANGULO_SRC = $(FORMAS_DIR)/retangulo/retangulo.c
LINHA_SRC = $(FORMAS_DIR)/linha/linha.c
TEXTO_SRC = $(FORMAS_DIR)/texto/texto.c
FORMAS_SRC = $(FORMAS_DIR)/formas/formas.c

# Estruturas de dados
FILA_SRC = $(ESTRUTURAS_DIR)/fila/fila.c
PILHA_SRC = $(ESTRUTURAS_DIR)/pilha/pilha.c

# Parser GEO e SVG
PARSER_GEO_SRC = $(GEO_DIR)/parserGeo/parserGeo.c
SVG_SRC = $(GEO_DIR)/svg/svg.c

# Módulos QRY
PARSER_QRY_SRC = $(QRY_DIR)/parserQry/parserQry.c
GAME_STATE_SRC = $(QRY_DIR)/gameState/gameState.c
GAME_COMMANDS_SRC = $(QRY_DIR)/gameCommands/gameCommands.c
FORMA_UTILS_SRC = $(QRY_DIR)/formaUtils/formaUtils.c
FORMA_ARENA_SRC = $(QRY_DIR)/formaUtils/formaArena.c
COLOR_RULES_SRC = $(QRY_DIR)/formaUtils/colorRules.c
DISPARADOR_SRC = $(QRY_DIR)/disparador/disparador.c
CARREGADOR_SRC = $(QRY_DIR)/carregadorManager/carregadorManager.c
COLISAO_SRC = $(QRY_DIR)/colisao/colisao.c
SVG_QRY_SRC = $(QRY_DIR)/svgQry/svgQry.c
SAIDA_QRY_SRC = $(QRY_DIR)/saida/saidaQry.c

# Argumentos
ARGUMENTOS_SRC = $(ARGUMENTOS_DIR)/argumentHandler.c

# =============================================================================
# Objetos
# =============================================================================

OBJECTS = $(BUILD_DIR)/main.o \
          $(BUILD_DIR)/circulo.o \
          $(BUILD_DIR)/retangulo.o \
          $(BUILD_DIR)/linha.o \
          $(BUILD_DIR)/texto.o \
          $(BUILD_DIR)/formas.o \
          $(BUILD_DIR)/fila.o \
          $(BUILD_DIR)/pilha.o \
          $(BUILD_DIR)/parserGeo.o \
          $(BUILD_DIR)/svg.o \
          $(BUILD_DIR)/parserQry.o \
          $(BUILD_DIR)/gameState.o \
          $(BUILD_DIR)/gameCommands.o \
          $(BUILD_DIR)/formaUtils.o \
          $(BUILD_DIR)/formaArena.o \
          $(BUILD_DIR)/colorRules.o \
          $(BUILD_DIR)/disparador.o \
          $(BUILD_DIR)/carregadorManager.o \
          $(BUILD_DIR)/colisao.o \
          $(BUILD_DIR)/svgQry.o \
          $(BUILD_DIR)/saidaQry.o \
          $(BUILD_DIR)/argumentHandler.o

# =============================================================================
# Parâmetros de execução (make run GEO=... QRY=...)
# =============================================================================

ENTRY_DIR ?= ../testes
OUTPUT_DIR ?= ../saida
GEO ?= figs-alet.geo

# =============================================================================
# Regras principais
# =============================================================================

.PHONY: all clean distclean run valgrind dirs

all: dirs $(TARGET)
	@echo "========================================"
	@echo "  Build concluído com sucesso!"
	@echo "  Executável: $(TARGET)"
	@echo "========================================"

dirs:
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	@echo "Linkando executável final..."
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# =============================================================================
# Compilação dos módulos
# =============================================================================

# --- Entry Point ---
$(BUILD_DIR)/main.o: $(MAIN_SRC)
	@echo "Compilando main..."
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Formas Geométricas ---
$(BUILD_DIR)/circulo.o: $(CIRCULO_SRC)
	@echo "Compilando circulo..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/retangulo.o: $(RETANGULO_SRC)
	@echo "Compilando retangulo..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/linha.o: $(LINHA_SRC)
	@echo "Compilando linha..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/texto.o: $(TEXTO_SRC)
	@echo "Compilando texto..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/formas.o: $(FORMAS_SRC)
	@echo "Compilando formas..."
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Estruturas de Dados ---
$(BUILD_DIR)/fila.o: $(FILA_SRC)
	@echo "Compilando fila..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/pilha.o: $(PILHA_SRC)
	@echo "Compilando pilha..."
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Parser GEO e SVG ---
$(BUILD_DIR)/parserGeo.o: $(PARSER_GEO_SRC)
	@echo "Compilando parserGeo..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/svg.o: $(SVG_SRC)
	@echo "Compilando svg..."
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Módulos QRY ---
$(BUILD_DIR)/parserQry.o: $(PARSER_QRY_SRC)
	@echo "Compilando parserQry..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/gameState.o: $(GAME_STATE_SRC)
	@echo "Compilando gameState..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/gameCommands.o: $(GAME_COMMANDS_SRC)
	@echo "Compilando gameCommands..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/formaUtils.o: $(FORMA_UTILS_SRC)
	@echo "Compilando formaUtils..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/formaArena.o: $(FORMA_ARENA_SRC)
	@echo "Compilando formaArena..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/colorRules.o: $(COLOR_RULES_SRC)
	@echo "Compilando colorRules..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/disparador.o: $(DISPARADOR_SRC)
	@echo "Compilando disparador..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/carregadorManager.o: $(CARREGADOR_SRC)
	@echo "Compilando carregadorManager..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/colisao.o: $(COLISAO_SRC)
	@echo "Compilando colisao..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/svgQry.o: $(SVG_QRY_SRC)
	@echo "Compilando svgQry..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/saidaQry.o: $(SAIDA_QRY_SRC)
	@echo "Compilando saidaQry..."
	@$(CC) $(CFLAGS) -c $< -o $@

# --- Argumentos ---
$(BUILD_DIR)/argumentHandler.o: $(ARGUMENTOS_SRC)
	@echo "Compilando argumentHandler..."
	@$(CC) $(CFLAGS) -c $< -o $@

# =============================================================================
# Limpeza
# =============================================================================

clean:
	@echo "Removendo arquivos de compilação..."
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET) $(TARGET).exe
	@echo "Limpeza concluída."

distclean: clean
	@rm -f $(OUTPUT_DIR)/*
	@echo "Diretório de saída limpo."

# =============================================================================
# Execução e Debug
# =============================================================================

run: all
	@if [ -n "$(QRY)" ]; then \
		./$(TARGET) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)" -q "$(QRY)"; \
	else \
		./$(TARGET) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)"; \
	fi

valgrind: all
	@if [ -n "$(QRY)" ]; then \
		valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)" -q "$(QRY)"; \
	else \
		valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) -e "$(ENTRY_DIR)" -f "$(GEO)" -o "$(OUTPUT_DIR)"; \
	fi
