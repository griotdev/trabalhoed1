# Trabalho 1 - Jogo de Esmagamento Geométrico

**Estrutura de Dados - C99**

## Informações do Aluno

| Campo     | Valor                      |
|-----------|----------------------------|
| Matrícula | 202500560216               |
| Nome      | André Ichihashi Rodrigues  |

---

## Descrição

Este programa implementa um **Jogo de Esmagamento Geométrico** onde formas são disparadas em uma arena e colidem entre si. O sistema lê arquivos de definição geométrica (`.geo`) e arquivos de comandos (`.qry`), gerando saídas visuais em SVG e relatórios em TXT.

### Funcionalidades

- **Formas Geométricas**: Suporte a círculos, retângulos, linhas e textos.
- **Carregadores e Disparadores**: Sistema de pilhas para carregar e disparar formas.
- **Colisões**: Detecção de sobreposição e esmagamento baseado em área.
- **Clonagem**: Formas maiores clonam-se ao colidir com menores.

---

## Compilação

### Pré-requisitos

- GCC com suporte a C99
- Make

### Comandos

```bash
cd src
make        # Compila o projeto
make clean  # Remove arquivos objeto e executável
```

O executável gerado será `ted` dentro da pasta `src/`.

---

## Execução

### Sintaxe

```bash
./ted -e <dir_entrada> -f <arquivo.geo> -o <dir_saida> [-q <arquivo.qry>]
```

### Argumentos Obrigatórios

| Flag | Descrição                                      |
|------|------------------------------------------------|
| `-e` | Diretório base de entrada (onde estão os arquivos `.geo` e `.qry`) |
| `-f` | Nome do arquivo de geometria (`.geo`)          |
| `-o` | Diretório de saída para os arquivos gerados    |

### Argumentos Opcionais

| Flag   | Descrição                           |
|--------|-------------------------------------|
| `-q`   | Arquivo de consultas (`.qry`)       |

### Exemplos

```bash
# Apenas gerar SVG das formas (sem consultas)
./ted -e ../testes -f cenario.geo -o ../saida

# Executar com arquivo de consultas
./ted -e ../testes -f cenario.geo -q pasta/consultas.qry -o ../saida
```

---

## Estrutura de Arquivos de Entrada

### Arquivo `.geo` (Geometria)

Define as formas do cenário inicial:

```
c <id> <x> <y> <raio> <cor_borda> <cor_preenchimento>
r <id> <x> <y> <largura> <altura> <cor_borda> <cor_preenchimento>
l <id> <x1> <y1> <x2> <y2> <cor>
t <id> <x> <y> <cor_borda> <cor_preenchimento> <ancora> <texto>
ts <familia> <peso> <tamanho>
```

### Arquivo `.qry` (Comandos)

Define comandos a serem executados:

```
pd <id> <x> <y>                    # Posiciona disparador
lc <carreg> <n>                    # Carrega n formas no carregador
atch <disp> <carreg_esq> <carreg_dir>  # Anexa carregadores
shft <disp> <lado> <n>             # Shift de formas
dsp <disp> <lado> <dx> <dy> [v]    # Dispara forma
rjd <disp> <lado> <dx> <dy> <ix> <iy>  # Rajada de disparos
calc                               # Calcula colisões
```

---

## Arquivos de Saída

| Arquivo                          | Descrição                                    |
|----------------------------------|----------------------------------------------|
| `<nome>.svg`                     | SVG inicial com todas as formas              |
| `<nome>-<qry>.svg`               | SVG final após processamento das consultas   |
| `<nome>-<qry>.txt`               | Relatório textual das ações realizadas       |

---

## Estrutura do Projeto

```
src/
├── main.c                  # Ponto de entrada
├── makefile                # Script de compilação
└── lib/
    ├── argumentos/         # Processamento de CLI
    ├── estruturas/         # Fila e Pilha
    ├── formas/             # Círculo, Retângulo, Linha, Texto
    ├── geo/                # Parser GEO e geração SVG
    └── qry/                # Parser QRY, comandos e colisões
        ├── parserQry/      # Parser de comandos
        ├── gameState/      # Estado do jogo (chão, arena, disparadores)
        ├── gameCommands/   # Implementação dos comandos
        ├── disparador/     # TAD Disparador
        ├── carregadorManager/  # Gerenciador de carregadores
        ├── colisao/        # Detecção de colisões
        ├── formaUtils/     # Utilitários e regras de cores
        ├── svgQry/         # SVG para estado do jogo
        └── saida/          # Geração de relatórios TXT
```

---

## Estruturas de Dados

### Pilha (LIFO)
**Uso:** Carregadores de formas

- Formas são empilhadas com `lc` e desempilhadas com `shft`/`dsp`
- Disparadores anexam duas pilhas (esquerda e direita)

### Fila (FIFO)
**Uso:** Chão e Arena

- **Chão**: Armazena todas as formas disponíveis
- **Arena**: Armazena formas disparadas para cálculo de colisões

---

## Regras de Colisão

| Condição | Ação |
|----------|------|
| Sem sobreposição | Ambas voltam ao chão |
| Área(I) < Área(J) | I é esmagada, J volta ao chão |
| Área(I) ≥ Área(J) | J recebe cor de I, I é clonada, todos voltam |

---
