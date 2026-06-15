# PROJETO-LP-PARTE-2
Trabalho de faculdade - Gerenciador de tarefas com multiplos usuarios
Grupo: Isabella, Giselly e Gabriel

REQUISITOS
1. Cadastrar colaboradores
2. Listar colaboradores
3. Cadastrar atividades
4. Listar atividades
5. Movimentar atividades (1->2->3)
6. Buscar atividade
7. Quantidade de atividades por colaborador
8. Estatisticas gerais
9. Ranking

outros....
10. Excluir e editar atividades
11. Filtrar por prioridade e/ou etapa
12. Atribuir tarefa a outro colaborador (foi Isabella quem pensou nesse ;P)

IDEIAS
- As tarefas não são mais separadas por listas, e sim por STATUS(etapa): 1- a fazer, 2- em andamento, 3- concluido
- Deixar campo vazio ou digitar 0 para cancelar um processo em andamento
- Ordenar automaticamente as tarefas assim que são adicionadas no struct por prioridade, deixando as concluidas no final 
  independente da prioridade
- Em listar colaboradores, poder mostrar as atividades e quantidade destas de cada um, se estao concluidas 
  e o nivel de prioridade delas. (Isso equivale aos requisitos 2 e 7 juntos)

---------------------------------------------------------------------------------------
SOBRE MODULARIZAÇÃO

Os itens abaixo com asterisco são os que demandam entrada do usuário e, portanto, devem ser criadas funcoes de
leitura e verificacao para cada, conforme especificado ao lado de cada item

CADA TAREFA TEM:
- *Nome -> string vazia, nome de TAREFA ja existente, tamanho
- *Nivel de prioridade -> entre 1 e 3
- *Status -> entre 1 e 3, maior que o status anterior
- *Um numero correspondente à sua posição -> maior que zero, menor que a quantidade total de tarefas da pessoa

CADA COLABORADOR TEM:
- *Nome (nao tem uso pratico. Aqui no software, é mais pratico usar o codigo) -> string vazia, tamanho
- *Codigo -> string vazia, CODIGO ja existente, só numeros, tamanho
- Quantidade total de tarefas cadastradas em seu nome
- Quantidade de tarefas pendentes
- Struct com todas as suas tarefas

Como toda entrada string não pode ser vazia e é sucetível a estouro de buffer, é mais pratico criar uma 
funcao que lê a string e verifica tudo isso ao mesmo tempo. Essa é a ler_string(), que substitui o FGETS
De forma análoga, nenhuma entrada int espera receber um caractere. Para isso, ler_int() substitui o SCANF
A implementacao de ambas as funcoes esta exemplificada no main (no inicio do do-while e em else if(funcao==1))

É interessante manter esse padrão para otimizar as verificações e podermos focar no que o projeto realmente requer.
Conforme formos desenvolvendo o programa, devemos criar funcoes baseado nisso, ou seja, leitura e verificacao 
automaticas dos dados indicados por asterisco anteriormente. Talvez não todos, mas os que aparecem muito, sim.

Existem alguns exemplos de funcoes que poderiam ser implementadas na parte "leitura e verificacao de dados especificos" no codigo, 
escritos como comentário
- Usar 'remover_enter' sempre ao ler uma string
- Mostrar opção de filtrar atividades por prioridade e/ou etapa (requisito bonus 11) dentro do requisito 4
