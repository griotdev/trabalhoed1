# 🎯 Bocha Geométrica - Projeto ED1

## 🧠 Identificação


- **Matrícula:** 202500560216
- **Nome do aluno:** André Ichihashi Rodrigues
- **Projeto:** Bocha Geométrica
- **Disciplina:** Estrutura de Dados I
- **Universidade:** UEL (Universidade Estadual de Londrina)
- **Professor:** Evandro Baccarin
- **Período:** 2025/1

---

## 📋 Descrição do Projeto

Sistema para manipulação e visualização de formas geométricas com suporte a:
- Leitura de arquivos `.geo` (geometrias)
- Processamento de comandos `.qry` (consultas/operações)
- Geração de arquivos SVG para visualização
- Simulação de colisões e esmagamentos entre formas
- Uso exclusivo de **pilhas** e **filas** como estruturas de dados

---

## ⚙️ Compilação

O projeto utiliza **Makefile** para automatizar a compilação. O Makefile está localizado em `src/` e gera o executável `ted` dentro da pasta `src/`.

### Comandos de compilação:

```bash
# Entrar no diretório src
cd src

# Limpar arquivos de compilação anteriores
make clean

# Compilar o projeto
make all

# Ou simplesmente
make
```

### Alvos disponíveis no Makefile:

- `make all` ou `make`: Compila o projeto e gera o executável `ted`
- `make clean`: Remove arquivos objeto e o executável
- `make distclean`: Remove também os arquivos de saída
- `make run GEO=<arquivo.geo> QRY=<arquivo.qry>`: Compila e executa com parâmetros
- `make valgrind GEO=<arquivo.geo> QRY=<arquivo.qry>`: Executa com valgrind para verificar vazamentos

### Flags de compilação:

- `-std=c99`: Padrão C99
- `-fstack-protector-all`: Proteção de pilha
- `-Wall -Wextra`: Warnings habilitados
- `-Werror=implicit-function-declaration`: Erro em funções implícitas
- `-lm`: Biblioteca matemática

---

## ▶️ Execução

O programa `ted` deve ser executado a partir do diretório `src/`:

### Sintaxe:

```bash
./ted -e <diretório_entrada> -f <arquivo.geo> -o <diretório_saída> [-q <arquivo.qry>]
```

### Parâmetros:

- `-e <diretório>`: Diretório onde estão os arquivos de entrada (opcional, padrão: `../testes`)
- `-f <arquivo.geo>`: Nome do arquivo `.geo` com as geometrias (obrigatório)
- `-o <diretório>`: Diretório onde os arquivos de saída serão gerados (obrigatório)
- `-q <arquivo.qry>`: Nome do arquivo `.qry` com comandos (opcional)

### Exemplos de execução:

```bash
# Executar apenas com arquivo .geo (gera SVG base)
./ted -e ../testes -f figs-alet.geo -o ../saida

# Executar com .geo e .qry (gera SVG base + SVG de consultas + log .txt)
./ted -e ../testes -f figs-alet.geo -o ../saida -q figs-alet/d2-1x1-norte.qry

# Usando caminhos relativos diferentes
./ted -f ../testes/retg-cres.geo -o ../saida -q retg-cres/d1-seq-raj.qry
```

### Arquivos gerados:

1. **<geo>.svg**: Visualização das formas do arquivo `.geo`
2. **<geo>-<qry>.svg**: Visualização do estado após comandos `.qry`
3. **<geo>-<qry>.txt**: Log textual da execução dos comandos

---

## 📂 Estrutura de Arquivos

```
trabalhoed1/
├── README.md                    # Este arquivo
├── makefile                     # Makefile da raiz (delegação)
├── src/                         # Código-fonte
│   ├── makefile                 # Makefile principal (gera ted aqui)
│   ├── main.c                   # Ponto de entrada do programa
│   ├── obj/                     # Arquivos objeto (.o)
│   ├── ted                      # Executável gerado
│   └── lib/                     # Bibliotecas modulares
│       ├── argumentos/          # Processamento de argumentos CLI
│       │   ├── argumentHandler.c
│       │   └── argumentHandler.h
│       ├── estruturas/          # Estruturas de dados básicas
│       │   ├── fila/            # TAD Fila (FIFO)
│       │   │   ├── fila.c
│       │   │   └── fila.h
│       │   └── pilha/           # TAD Pilha (LIFO)
│       │       ├── pilha.c
│       │       └── pilha.h
│       ├── formas/              # TADs de formas geométricas
│       │   ├── circulo/
│       │   ├── retangulo/
│       │   ├── linha/
│       │   ├── texto/
│       │   └── formas/          # Interface genérica
│       ├── geo/                 # Processamento de arquivos .geo
│       │   ├── parserGeo/       # Parser de .geo
│       │   └── svg/             # Geração de SVG base
│       └── qry/                 # Sistema de consultas/comandos
│           ├── parserQry/       # Parser de .qry
│           ├── gameState/       # Estado global do jogo
│           ├── gameCommands/    # Implementação dos comandos
│           ├── disparador/      # TAD Disparador
│           ├── carregadorManager/ # Gerenciador de carregadores
│           ├── colisao/         # Detecção de colisões
│           ├── formaUtils/      # Utilitários (cores, info)
│           ├── svgQry/          # Geração de SVG de consultas
│           └── saida/           # Geração de logs
├── testes/                      # Arquivos de teste
│   ├── *.geo                    # Arquivos de geometrias
│   ├── figs-alet/               # Conjunto de testes
│   │   └── *.qry
│   ├── retg-cres/
│   └── ...
├── saida/                       # Arquivos gerados
│   ├── *.svg                    # Visualizações SVG
│   └── *.txt                    # Logs de execução
└── ignore/                      # Arquivos auxiliares (não entregues)
```

---

## 🧮 Funcionalidades Implementadas

### ✅ Parser de arquivos `.geo`
- Leitura e interpretação de formas geométricas:
  - `c`: Círculo (id, x, y, raio, corBorda, corPreenchimento)
  - `r`: Retângulo (id, x, y, largura, altura, corBorda, corPreenchimento)
  - `l`: Linha (id, x1, y1, x2, y2, cor)
  - `t`: Texto (id, x, y, corBorda, corPreenchimento, âncora, texto)
  - `ts`: Estilo de texto (família, peso, tamanho)

### ✅ Parser de arquivos `.qry`
Implementação completa dos 7 comandos:

1. **`pd`** - Posiciona disparador no espaço (x, y)
2. **`lc`** - Carrega n formas do chão para um carregador
3. **`atch`** - Anexa carregadores esquerdo e direito a um disparador
4. **`shft`** - Desloca n formas entre carregadores
5. **`dsp`** - Dispara forma de um carregador para a arena
6. **`rjd`** - Rejeita forma de um carregador, devolvendo ao chão
7. **`calc`** - Calcula colisões e esmaga formas sobrepostas

### ✅ Sistema de colisões
- Detecção de sobreposição entre todas as combinações de formas
- Cálculo de áreas (incluindo heurísticas para linha e texto)
- Esmagamento: forma menor é destruída
- Transferência de cores com regra complementar para texto/linha

### ✅ Geração de SVG
- SVG base: todas as formas do `.geo`
- SVG de consultas: estado após comandos (chão, arena, disparadores)
- Dimensionamento dinâmico baseado no conteúdo
- Opacidade diferenciada para formas no chão (0.6)

### ✅ Saída textual
- Log detalhado da execução dos comandos
- Formato: `<geo>-<qry>.txt`

---

## 🧱 Estrutura de Dados

### Pilhas (LIFO - Last In, First Out)
**Uso:** Carregadores de formas

- Cada carregador é uma pilha que armazena formas
- Operações: `empilha`, `desempilha`, `consulta`
- Disparadores anexam duas pilhas (carregadores esquerdo e direito)
- Comando `shft` transfere formas entre pilhas

### Filas (FIFO - First In, First Out)
**Uso:** Chão e arena

- **Chão**: Fila com todas as formas disponíveis do `.geo`
- **Arena**: Fila com formas disparadas aguardando cálculo de colisões
- Operações: `enfileira`, `desenfileira`, `consulta`
- Comando `lc` retira formas do chão
- Comando `calc` processa formas da arena

### TADs Opacos
Todos os tipos são opacos (`void*`) para garantir encapsulamento:
- `Fila`, `Pilha`, `Forma`, `Circulo`, `Retangulo`, `Linha`, `Texto`
- `GameState`, `Disparador`, `CarregadorManager`

---

## 🧩 Modularização

O projeto está organizado em módulos independentes:

| Módulo | Responsabilidade |
|--------|------------------|
| **argumentHandler** | Processamento de argumentos da linha de comando |
| **fila / pilha** | Estruturas de dados genéricas |
| **circulo / retangulo / linha / texto** | TADs de formas específicas |
| **formas** | Interface genérica para todas as formas |
| **parserGeo** | Leitura e interpretação de arquivos `.geo` |
| **svg** | Geração de SVG para geometrias base |
| **parserQry** | Leitura e execução de comandos `.qry` |
| **gameState** | Gerenciamento do estado global (chão, arena, disparadores) |
| **gameCommands** | Implementação dos 7 comandos do `.qry` |
| **disparador** | TAD Disparador com carregadores |
| **carregadorManager** | Gerenciamento de pilhas de formas |
| **colisao** | Detecção de sobreposição e cálculo de áreas |
| **formaUtils** | Utilitários (troca de cores, informações) |
| **colorRules** | Regras de transferência de cores (complementar) |
| **svgQry** | Geração de SVG do estado do jogo |
| **saidaQry** | Geração de logs textuais |

---

## 🧪 Testes e Validação

### Verificação de memória (Valgrind)

```bash
cd src
make valgrind GEO=figs-alet.geo QRY=figs-alet/d2-1x1-norte.qry
```

**Resultado esperado:**
```
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

### Exemplos de teste incluídos

- `figs-alet.geo` + múltiplos `.qry` (testes de disparo e colisão)
- `retg-cres.geo` / `retg-cres-2.geo` + `.qry` (testes de retângulos)
- `retg-decres.geo` + `.qry`
- `rets-circs-cres.geo` + `.qry` (mistura de formas)

---

## 🧾 Observações Finais

### Características do projeto

- ✅ **100% modular**: Cada funcionalidade em seu próprio módulo
- ✅ **TADs opacos**: Encapsulamento total das estruturas
- ✅ **Zero vazamentos**: Validado com Valgrind
- ✅ **Headers documentados**: Todas as funções com comentários explicativos
- ✅ **Código limpo**: Segue boas práticas de C99
- ✅ **Nomenclatura padronizada**: Saídas seguem padrão `<geo>-<qry>.svg/txt`

### Decisões de design

1. **Área de linha e texto**: Usamos heurísticas (2×comprimento e 20×caracteres) já que essas formas não têm área real
2. **Cor complementar**: Quando fonte da cor é texto ou linha, aplicamos RGB complementar (255 - componente)
3. **SVG dinâmico**: Canvas ajusta automaticamente para conter todo o conteúdo
4. **Opacidade**: Formas no chão renderizadas com 60% de opacidade para diferenciação visual

### Compilação e execução testadas

- ✅ Ubuntu 22.04 LTS
- ✅ GCC 11.4.0
- ✅ Valgrind 3.18.1
- ✅ Make 4.3

---

**Projeto desenvolvido para a disciplina de Estrutura de Dados I - UEL 2025/1**
