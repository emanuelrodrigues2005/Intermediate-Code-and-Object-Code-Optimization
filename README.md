# Otimização de Código Intermediário e Objeto baseada em Combinadores

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![UFRPE](https://img.shields.io/badge/UFRPE-Compiladores-blue?style=for-the-badge)

Bem-vindo ao repositório do projeto de **Otimização de Código Intermediário e Objeto**, desenvolvido para a disciplina de **Compiladores** na **Universidade Federal Rural de Pernambuco (UFRPE)**.

Este projeto implementa diversas **Máquinas de dois arrays** em **C**, explorando diferentes conjuntos de **Combinadores Lógicos** (como os de Curry, Turner, KS e KSI). O objetivo principal é demonstrar na prática como a escolha dos combinadores impacta diretamente a otimização na execução de programas da linguagem funcional no nível de código intermediário e objeto.

---

## Estrutura do Repositório

O código está dividido em diretórios, cada um focado em uma máquina de redução ou cenário de teste específico:

* **`curry/` - Máquina de Combinadores de Curry**
  Implementação das regras de redução utilizando os combinadores propostos por Haskell Curry. Conta com versões base e específicas para manipulação de inteiros.

* **`turner/` - Máquina de Combinadores de Turner**
  Implementa o conjunto de combinadores de David Turner (S, K, I, B, C, S', B', C'), que melhora drasticamente a eficiência da redução de grafos em relação ao conjunto original de Curry, otimizando o tamanho do código gerado e a velocidade de execução.
  Obs: Os combinadores S', B' e C' são nomeados como D, E e F respectivamente

* **`ks-machine/` - Máquina KS**
  Máquina fundamentalista operando estritamente com os combinadores essenciais estruturais **K** e **S** (Lógica Combinatória básica).

* **`ksi/` - Máquina KSI**
  Evolução direta da máquina KS, com a adição do combinador de Identidade (**I**), permitindo passos de redução adicionais e simplificações na árvore sintática.

* **`fib-fat/` - Benchmarks e Testes de Carga**
  A prova real da otimização! Aqui você encontra implementações compiladas nessas máquinas, testando a eficiência computacional de cada uma:
  * **Fatorial (`fat`)**: Cálculos de fatorial de 5 e de 20 (ex: `fat5-ksi.c`, `fat20-turner.c`).
  * **Fibonacci (`fib`)**: Cálculos da sequência de Fibonacci para 5 e 20 (ex: `fib5-turner.c`, `fib20-turner.c` etc.).

---

## Objetivo

Na teoria dos compiladores, linguagens funcionais frequentemente são traduzidas para um código intermediário matemático (Lógica Combinatória) para abstrair variáveis livres. O intuito deste projeto é apresentar as bases dessas otimizações rodando diretamente em máquinas construídas em `C`. A comparação entre as máquinas (por exemplo, KSI vs Turner) em algoritmos de estresse (como Fib 20) permite analisar e comprovar a redução de passos computacionais (otimização natural do código objeto gerado!).

---

## Como Executar

Por ser um projeto puramente escrito em **C**, você precisará do `gcc` (ou qualquer outro compilador de C) instalado em seu ambiente.

1. **Clone este repositório:**
   ```bash
   git clone https://github.com/seu-usuario/Intermediate-Code-and-Object-Code-Optimization.git
   cd Intermediate-Code-and-Object-Code-Optimization
   ```

2. **Compilando um dos testes de Fibonacci (na máquina de Turner, por exemplo):**
   ```bash
   gcc fib-fat/fib20-turner.c -o fib20_turner
   ```

3. **Executando no terminal:**
   ```bash
   ./fib20_turner   # (No Windows: .\fib20_turner.exe)
   ```
   > Recomenda-se compilar e rodar diferentes arquivos da pasta `fib-fat` para constatar a diferença de performance na engine de cada conjunto de combinador.

---
