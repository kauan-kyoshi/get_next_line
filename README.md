# get_next_line

## Descrição do projeto

`get_next_line` é um exercício da 42 que implementa uma função capaz de ler uma linha por vez a partir de um file descriptor (fd). Este repositório contém a implementação padrão e a versão *bonus* que suporta múltiplos file descriptors simultaneamente.

O objetivo do projeto é construir uma função robusta, eficiente e que respeite as regras impostas pela 42 (uso restrito de funções da libc, tratamento correto de memória, e comportamento definido em todas as bordas/erros).

## Como funciona (visão geral)

- A função principal é `get_next_line(int fd)` e deve retornar uma string alocada contendo a próxima linha lida de `fd`, incluindo o caractere de nova linha (`\n`) quando presente. Quando não houver mais dados, deve retornar `NULL`.
- A leitura deve ser feita em blocos usando `read` com um `BUFFER_SIZE` configurável em tempo de compilação.
- A função precisa manter dados entre chamadas para lidar com linhas que cruzam limites de leitura — isso é feito usando uma área de armazenamento estática (por file descriptor na versão bonus) ou outra estrutura que persista entre chamadas.
- Ao encontrar uma nova linha, `get_next_line` deve separar o conteúdo até a nova linha e manter o restante para a próxima chamada.
- Todas as strings retornadas são alocadas com `malloc`; quem chama deve liberar a memória quando não precisar mais.

## Arquivos presentes

- `get_next_line.c` — Implementação principal (versão padrão).
- `get_next_line_bonus.c` — Implementação que suporta múltiplos file descriptors (bonus).
- `get_next_line_utils.c` e `get_next_line_utils_bonus.c` — Funções auxiliares (manipulação de strings, joins, cortes, etc.).
- `get_next_line.h` e `get_next_line_bonus.h` — Cabeçalhos com protótipos e includes.

## Regras / Restrições (comuns na 42)

- Apenas funções permitidas pela enunciado (normalmente: `read`, `malloc`, `free`, e funções do projeto como `write` para debugging se permitido) devem ser usadas.
- Não é permitido usar funções como `strdup`, `strjoin` da libc sem reimplementá-las (exceto se explicitamente permitido).
- `BUFFER_SIZE` controla quantos bytes `read` tenta ler por chamada.
- A implementação deve evitar vazamentos de memória e comportamento indefinido.

## Exemplos de compilação e uso

Compilar (exemplo simples sem Makefile):

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c -o gnl
```

Testando com um arquivo:

```bash
./gnl < arquivo.txt
```

Exemplo de uso em código (pseudo):

```c
#include "get_next_line.h"

int fd = open("arquivo.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL) {
	printf("%s", line);
	free(line);
}
close(fd);
```

## Casos de teste e comportamento esperado

- Arquivos vazios → `get_next_line` deve retornar `NULL` imediatamente.
- Linhas sem `\n` no final → retornar a última linha (sem `\n`) e depois `NULL`.
- Linhas maiores que `BUFFER_SIZE` → a função deve concatenar leituras até encontrar `\n`.
- Erro em `read` → liberar recursos e retornar `NULL`.
- Versão *bonus* deve tratar múltiplos fds sem mistura de dados entre eles.

## Competências desenvolvidas

- Gerência de memória em C: alocação dinâmica, evitar vazamentos e double-free.
- Manipulação de buffers e leitura parcial de streams.
- Trabalho com file descriptors e chamadas de sistema (`read`, `open`, `close`).
- Estruturas persistentes entre chamadas (uso de variáveis estáticas ou estruturas para armazenar estado por fd).
- Tratamento de casos de borda e testes: arquivos vazios, fim de arquivo, erros de leitura e linhas muito longas.
- Depuração e uso de ferramentas: Valgrind (detectar memory leaks), gdb (debug), e ferramentas de lint/compilador.

## Dificuldades comuns e como superei

- Sincronizar o conteúdo lido entre chamadas: resolvido mantendo um buffer estático por `fd` (versão bonus) e cuidadosamente manipulando cortes e junções de strings.
- Evitar cópias desnecessárias: minimizar realocações usando operações bem definidas para juntar partes de uma linha.
- Cobrir todos os casos limites em testes automatizados e manuais.


## Como testar localmente

1. Compile com diferentes `BUFFER_SIZE` para validar comportamento:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -o gnl
./gnl < arquivo_com_linhas.txt
```

2. Rodar Valgrind para checar memória:

```bash
valgrind --leak-check=full ./gnl < arquivo.txt
```

3. Testar a versão bonus com múltiplos fds (ex.: abrir dois arquivos e alternar chamadas a `get_next_line`).

