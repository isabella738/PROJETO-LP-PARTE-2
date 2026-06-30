## Projeto – Sistema de Organização e Acompanhamento de Atividades

Universidade Estadual de Santa Cruz  
Curso: Ciência da Computação  
Disciplina: Linguagem de Programação I  
Discente(s): Gabriel Moura Rocha, Giselly Jahel Dias e Isabella Sousa Porto Ferreira  
Docente: Luenne Nailam Souza Nascimento  
Data (última atualização): 26-06-2026   

*Obs: disponibilizamos o codigo fonte dos testes unitarios no main do repositorio, se por acaso quiser dar uma olhada

### Relatório

### 1. Descrição Geral do Sistema
- O sistema comporta 100 usuarios diferenciados por um codigo numerico de 5 digitos. Cada usuario pode ter até 100 tarefas cadastradas, cada uma contendo título (max 100 caracteres) e descricao (max 500 caracteres).
- O sistema conta com um mecanismo de cancelar ação: caso o utilizador selecione uma ação sem querer, ou desista de uma no meio do processo, ele pode inserir um campo vazio (se o programa requerir string) ou inserir 0 (se o programa requerir um numero inteiro) para cancelar e voltar ao menu.
- Os dados são salvos ao encerrar o programa e carregados automaticamente ao iniciá-lo.
- Não há diferenciação entre maiúsculas e minúsculas.
- O sistema conta com um amplo sistema de verificação de entradas, detectando os seguintes casos:
  1. Strings vazias ou maiores que o máximo de caracteres permitido.
  2. Entrada de caracter(es) quando o programa requeria um inteiro.
  3. Entrada de numeros fora do intervalo requerido no contexto (seleção de colaborador, de tarefas, opções de menu, etc...).
  4. Codigo de colaborador duplicado, inexistente ou em formato inválido.
  5. Tarefas com nome duplicado ou sem descrição.
  6. Buscas sem resultado.
  7. Tentativa de movimentação quando a tarefa já foi concluída.

FALHAS
1. A limpeza de buffer não é feita corretamente. No codigo, a leitura é feita numa string maior e então copiada para uma menor, mas isso não resolve o problema.
2. A experiencia do usuario poderia ser melhorada. Por exemplo, quando o programa solicita a seleção de um colaborador e depois uma de suas tarefas, ao encerrar o processo, muitas vezes o loop reinicia por completo. Ou seja, se quizer realizar uma ação para duas tarefas diferentes de um mesmo colaborador, pode ser necessario inserir o codigo de colaborador 2 vezes também, o que não é muito prático.
3. As funcionalidades são implementadas diretamente no main em uma sequência de else-ifs, o que deixa o main extremamente extenso. Tal problema seria resolvido tornando cada funcionalidade em uma subrotina.

### 2. Funcionalidades Implementadas
  1. Exibição de Menu
  2. Cadastro de colaborador
     - Solicita nome e código do novo colaborador
  3. Listagem de colaboradores\
     3.1. Exibição da quantidade e conteudo das atividades individuais, ordenadas por etapa\
          - Também é possível acessar a descrição destas atividades
  4. Cadastro de atividade
     - Solicita o código do colaborador responsável, título, prioridade e descrição (podendo ser vazia ou não) da nova tarefa
  5. Listagem de atividades na integra\
     5.1. (Bônus) Exibição de todas as atividades ordenadas ou filtradas por prioridade ou etapa\
          - Também é possível acessar a descrição destas atividades
  6. Movimentar atividade
     - São exibidas na tela somente as atividades não concluidas, e a movimentação acontece etapa por etapa.
  7. Busca
      - Exibe as informações de todas as tarefas que correspondam à busca ou que contenham a mesma cadeia de caracteres
  8. Exibição de Estatísticas Gerais
      - Total de colaboradores e atividades cadastradas, média de atividades por colaborador, taxa de atividades concluidas no total, total de atividades em cada etapa e prioridade
  9. Ranking
      - 5 primeiros colocados
  10. Edição de Atividade\
      10.1. (Bônus) Editar Nome\
      10.2. (Extra) Mudar Prioridade\
      10.3. (Extra) Trocar Colaborador Responsavel\
      10.4. (Bônus) Excluir Atividade\
      10.5. (Extra) Editar Descrição
  12. Edição de Colaborador\
      11.1. (Extra) Mudar Nome\
      11.2. (Extra) Excluir Colaborador
      
Observação: todas as funcionalidade bônus foram implementadas. 5 extras foram criadas.

### 3. Organização do Código
- As informações dos colaboradores são guardadas em um vetor de structs.
- O usuário pode escolher entre 11 funcionalidades, que estão organizadas em uma sequência de else-ifs
- As subrotinas estão organizadas em 4 seções principais:
  1. Funções de uso geral: funções auxiliares, maioria para fazer modificações ou verificações simples e mais repetitivas
  2. Funções de verificacao: funções de base, que verificam a validade de um dado específico para uma condição específica
  3. Funções de leitura de dados não-específicos: funções de base, que leem uma entrada e, ao mesmo tempo, verificacam sua validade. Esta seção surge pois todas as entradas de determinado tipo precisam ser verificadas para algumas condições em comum, independente do contexto, por exemplo: todos os inteiros precisam ser maiores que 0, nenhuma string pode ser vazia. Outras verificações mais específicas são feitas a parte. Com isso, essas funções substituem o fgets (ler_string) e o scanf(%d) (ler_int) ao longo do código.
  4. Funções de leitura de dados específicos: fundamentadas em todas as funções anteriores. Reúne todas as verificações necessárias para determinado dado em uma só subrotina, para evitar ao máximo repetições e preocupação com validações, e otimizar a leitura no main.
- As funções de leitura de strings retornam 3 valores: 0 (entrada válidada), 1 (erro diverso), 2 (erro específico: string vazia). Essa mecânica surgiu da necessidade de "informar" ao main a hora de interromper um loop, conforme descrito na descrição geral do sistema. Funções análogas a estas, mas que retornam um índice, retornam -1 para erro diverso e -2 para string vazia.

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

Os dados são salvos e carregados de um arquivo binário denominado "dados.bin"

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
1. Manipulação de strings que resultavam em ocasionais erros de segmentação e "stack smashing"

### 7. Melhorias Futuras
1. Limpeza de buffer e melhoria no sistema de checagem do estouro
2. Tirar todas as funcionalidades do main
3. Reduzir funcionalidades, compactando-as em funcionalidades com ações internas em vez de dividí-las em mais de 10 opções no menu
