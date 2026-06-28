## Projeto – Sistema de Organização e Acompanhamento de Atividades

Universidade Estadual de Santa Cruz  
Curso: Ciência da Computação  
Disciplina: Linguagem de Programação I  
Discente(s): Gabriel Moura Rocha, Giselly Jahel Dias e Isabella Sousa Porto Ferreira  
Docente: Luenne Nailam Souza Nascimento  
Data (última atualização): 26-06-2026   

*Obs: disponibilizamos o codigo fonte dos testes unitarios no main do repositorio, só pra caso quiser dar uma olhada

### Relatório

### 1. Descrição Geral do Sistema
[Descricao...]

FALHAS
1. A limpeza de buffer não é feita corretamente. Muitas vezes a leitura é feita numa string maior e então copiada para uma menor, mas isso não resolve o problema.

### 2. Funcionalidades Implementadas

### 3. Organização do Código
- As informações são guardadas em um vetor de structs.
- O usuário pode escolher entre 11 funcionalidades, que estão organizadas em uma sequência de else-ifs
- As subrotinas estão organizadas em 4 seções principais:
  1. Funções de uso geral: funções auxiliares, maioria para fazer modificações ou verificações simples e mais repetitivas
  2. Funções de verificacao: funções de base, que verificam a validade de um dado específico para uma condição específica
  3. Funções de leitura de dados não-específicos: funções de base, que leem uma entrada e, ao mesmo tempo, verificacam sua validade. Esta seção surge pois todas as entradas de determinado tipo precisam ser verificadas para algumas condições em comum, independente do contexto, por exemplo: todos os inteiros precisam ser maiores que 0, nenhuma string pode ser vazia. Outras verificações mais específicas são feitas a parte.
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

Também há um struct próprio para armazenar informações de uma tarefa. 
Cada tarefa contém:
1. char nome[50]
2. int prioridade (1-alta, 2-media, 3- baixa).
3. int status (1-a fazer, 2-em andamento, 3- concluida).
  
### 5. Testes Unitários

Teste 1:

Funcionalidade: reorganizar os valores (1-3) de um vetor em forma crescente

Dados de entrada: 2, 3, 1, 1, 2, 3, 1, 3, 1, 2

Resultado esperado: 1, 1, 1, 1, 2, 2, 2, 3, 3, 3

Este teste simula a funcao 'reorganizacao por status' no codigo principal.

-------
Teste 2:

Funcionalidade: interromper ou não um processo em andamento

Dados de entrada: n; s; N; w

Resultados esperados: "Programa encerrado"; "Continuar programa"; "Programa encerrado"; "Continuar programa"

Este teste simula a funcao 'encerrar()' no codigo principal.

-------
Teste 3:

Funcionalidade: imprimir os 5 maiores valores de um vetor

Dados de entrada: 8, 3, 2, 10, 1, 7, 2, 0, 2, 3

Resultados esperados: 10, 8, 7, 3, 3

Este teste simula o requisito 'ranking' no codigo principal.

--------
Teste 4:

Funcionalidade: Validar o formato de uma entrada do tipo 'codigo de colaborador'

Dados de entrada: qwert; 99; 00001

Resultados esperados: 'O codigo deve conter apenas numeros'; 'O codigo contem apenas numeros, mas tambem deve ter 5 digitos.'; 'Codigo "00001" valido para o sistema.'

Este teste simula a função 'lerString_codigo' no codigo principal.

-------
Teste 5: 

Funcionalidade: tirar espaços em excesso de uma string

Dado de entrada: ----tirar--espaços----em---excesso------ (hifens representam espaços)

Resultado esperado: 'tirar-espaços-em-excesso'

Este teste simula a função 'tirar_espacos' no codigo principal

### 6. Dificuldades Encontradas

### 7. Melhorias Futuras
1. Limpeza de buffer e melhoria no sistema de checagem do estouro
2. Ampliar ações do usuário: não é possível acessar diretamente a descrição de uma atividade através de 'Listar Atividades' (5), pois a listagem na tela não é linear em relação aos vetores, o que torna este trabalho mais complexo.
