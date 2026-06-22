## Projeto – Sistema de Organização e Acompanhamento de Atividades

Universidade Estadual de Santa Cruz  
Curso: Ciência da Computação  
Disciplina: Linguagem de Programação I  
Discente(s): Gabriel Moura Rocha, Giselly Jahel Dias e Isabella Sousa Porto Ferreira  
Docente: Luenne Nailam Souza Nascimento  
Data (última atualização): 22-06-2026   

### Relatório

### 1. Descrição Geral do Sistema

### 2. Funcionalidades Implementadas

### 3. Organização do Código
- As informações são guardadas em um vetor de structs.
- O usuário pode escolher entre 12 funcionalidades, que estão organizadas em uma sequência de else-ifs
- As subrotinas estão organizadas em 4 seções principais:
  1. Funções de uso geral: funções auxiliares, maioria para fazer modificações ou verificações simples e mais repetitivas
  2. Funções de verificacao: funções de base, que verificam a validade de um dado específico para uma condição específica
  3. Funções de leitura de dados não-específicos: funções de base, que leem uma entrada e, ao mesmo tempo, verificacam sua validade. Todas as entradas de determinado tipo precisam ser verificadas para algumas condições em comum, independente do contexto, por exemplo: todos os inteiros precisam ser maiores que 0, nenhuma string pode ser vazia. Outras verificações mais específicas são feitas a parte.
  4. Funções de leitura de dados específicos: fundamentadas em todas as funções anteriores. Reúne todas as verificações necessárias para determinado dado em uma só subrotina, para evitar ao máximo repetições e preocupação com validações, e otimizar a leitura no main
  

### 4. Estruturas de Dados
As informações de cada colaborador são armazenadas em uma posição do vetor do struct 'colaborador'.
Cada colaborador contém:
1. char nome[50]
2. char codigo[6]
3. int concluidas (quantidade de tarefas concluidas do colaborador)
4. int lim (quantidade total de tarefas cadastradas para este colaborador)
5. item tarefa[100]
O total de pessoas cadastradas é armazenado pelo inteiro 'p'.

.
Também há um struct próprio para armazenar informações de uma tarefa
Cada tarefa contém:
1. char nome[50]
2. int prioridade (1-alta, 2-media, 3- baixa).
3. int status (1-a fazer, 2-em andamento, 3- concluida).
  
### 5. Testes Unitários
*Obs: o codigo fonte desses testes está no main sob o nome 'testes_unitarios'

Teste 1:

Funcionalidade: reorganizar os valores (1-3) de um vetor em forma crescente

Dados de entrada: 2, 3, 1, 1, 2, 3, 1, 3, 1, 2

Resultado esperado: 1, 1, 1, 1, 2, 2, 2, 3, 3, 3

Este teste simula a funcao 'reorganizacao por status' no codigo principal


Teste 2:

Funcionalidade: interromper ou não um processo em andamento

Dados de entrada: n; s; N; w

Resultados esperados: "Programa encerrado"; "Continuar programa"; "Programa encerrado"; "Continuar programa"

Este teste simula a funcao 'encerrar()' no codigo principal

### 6. Dificuldades Encontradas

### 7. Melhorias Futuras
