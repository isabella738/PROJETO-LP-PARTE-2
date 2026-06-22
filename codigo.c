#include <stdio.h>
#include <string.h>

/*
Atualizações da nova versão:
- Criação de menu de opções
- +1 opção do menu: exibir menu (e a criação de uma função para exibi-lo)
- Foram criadas as funções para ler código e nome de colaborador, bem como verificação de código existente
- Desenvolvimento das opções de menu de 1 a 7
    *em 4 (cadastro de atividades) o programa pedia o nome, mas como nome pode ser duplicado, é melhor usar o código
- Tirei a verificacao de nome duplicado no nome de colaborador, pois não foi requisitado no projeto, conforme descrito
    no pdf da avaliação
- Criação de função: procurar_colaborador -> retorna a posição da pessoa no array a partir de seu código 
    (útil para imprimir nomes)
- Criação de função: reorganizar por status -> reorganiza diretamente o vetor de tarefas de dado colaborador, mantendo
    as na etapa 1 em primeiro, 2 no meio e concluidas por ultimo
- Update da funcao ler_int: verifica se o numero esta dentro dos limites especificados no parametro, ao mesmo tempo que
    le o numero: int n = ler_int(a, b), sendo a<=n<=b
- Update da listagem de colaboradores: agora é possível selecionar um especifico e listar todas as suas tarefas.
- Update da funcao ler_string: retorna 2 se for string vazia, então o usuario pode desistir de uma ação somente apertando
    enter. Nova sintaxe:
    int s
    while((s=ler_string(string))==1);
    if(s==2)break;
- Verificacao de numero de colaboradores: se não existirem colaboradores cadastrados, todas as opcoes, menos as de 0 a 2, 
    ficam bloqueadas.
- Na funcao encerrar(), getchar foi substituido por scanf, que já previne lixo no buffer e varios getchar no main
- Se o usuario quiser desistir de uma ação no meio do processo, ele pode digitar 0, no caso de entradas numericas, ou
    enter, no caso de entradas de caractere. Criei essa mecânica, mas não tenho certeza se apliquei para todas as entradas.
    É bom conferir.


ANOTACOES
- É válido fazer mais testes. Fiz somente alguns, provavelmente é preciso fazer alguns ajustes
- Melhorar formatação se necessario
- Faltam os requisitos: 9, 10, 11, 12
- Acho que a funcao lerString_tarefa não está funcionando muito bem para a verificação de tarefas duplicadas
*/

typedef struct {
    char nome[100];
    //char descricao[200]; deixa isso aqui pra depois, muito trabalho...
    int prioridade; // 1, 2 ou 3, prioridade crescente
    int status; //1, 2 ou 3, a fazer, em andamento, concluido
}itens;

typedef struct {
    char nome[100];
    char codigo[6]; //5 digitos
    int concluidas; //isso aqui pode ajudar ao fazer o ranking!
    int lim; //total de tarefas de um colaborador
    itens tarefa[100];
}colaborador;

colaborador pessoa[100]; 
int p=0; //Contador de colaboradores

//
//FUNCOES DE USO GERAL
int encerrar(){ //return 1=parar processo atual; return 0=continuar
	printf("Continuar? (S/N) ");
	char c;
    scanf(" %c", &c);
	if(c=='n' || c=='N')return 1;
	return 0;
}

void minusculas(char string[]){ //transforma todas as letras da string passada no parametro em minusculas
	int i;
	for(i=0; string[i]!='\0'; i++){
		if(string[i]>='A' && string[i]<='Z')string[i]+='a'-'A';
	}
}

void remover_enter(char t[]){
    int x = strlen(t);
    if(t[x-1]=='\n' && x>0)t[x-1]='\0';
}

void exibir_menu(){
    printf("\n| MENU\n");
    printf("1. Exibir menu.\n");
	printf("2. Cadastrar colaborador.\n");
	printf("3. Listar colaboradore(s).\n");
	printf("4. Cadastrar atividade.\n");
	printf("5. Listar atividade(s).\n");
	printf("6. Movimentar atividade.\n");
	printf("7. Buscar atividade.\n");
	printf("8. Mostrar Estatisticas Gerais.\n");
	printf("9. Exibir Ranking de Colaboradores.\n");
    //printf("10. Excluir atividade.\n");
	//printf("11. Editar atividade.\n");
	//printf("12. Trocar colaborador responsavel por atividade.\n");
	printf("0. Sair.\n\n");

}

void reorganizacao_por_status(int x){//recebe a posição do colaborador no array
    int i, limite=0, status;
    //"limite" é a primeira posicao do vetor que não foi organizada

    /*Lógica: 

    1. Selecionar 1 status de cada vez, em ordem crescente, mantendo as tarefas não iniciadas no topo
    2. Percorrer o array de tarefas, por uma tarefa que esteja no status definido anteriormente
    3. Se corresponder, troca a tarefa na posição 'i' pela posição 'limite', e aumenta o valor de 'limite'
        mantendo, assim, a tarefa que foi permutada fixa na nova posição. Depois, o contador 'i' volta para a nova
        posição 'limite' e reinicia a busca
    4. Se corresponder, mas 'limite' for igual a 'i', então significa que a tarefa já está na posição certa e somente é
        necessário aumentar o valor 'limite'
    */
    for(status=1; status<=3; status++){
        for(i=0; i<pessoa[x].lim; i++){
            if(pessoa[x].tarefa[i].status==status){
                if(limite!=i){
                    itens t = pessoa[x].tarefa[i];
                    pessoa[x].tarefa[i] = pessoa[x].tarefa[limite];
                    pessoa[x].tarefa[limite] = t;
                    limite++;
                    i = limite;
                }
                else{
                    limite++;
                }
            }
        }
    }
}

//
//FUNCOES DE VERIFICACAO
int string_vazia(char string[]){
	int i;
	for(i=0; string[i]!='\0'; i++)if(string[i]!=' ' && string[i]!='\n')return 0;
	return 1;
}

int codigo_existe(char codigo[]){//retorna a posicao do colaborador no array, ou -1 se nao existir
    int x = -1;
    for(int i=0; i<p; i++){
        if(strcmp(pessoa[i].codigo, codigo)==0){
            x = i; break;
        }
    }
    return x;
}

//
//FUNCOES DE LEITURA DE DADOS NAO-ESPECIFICOS
int ler_string(char string[], int tam){//substitui o fgets; retorna 1 para erro, 2 p/ string vazia
    //le string, remove o enter, verifica o tamanho e se eh vazio

    char teste[tam+10];
    int i;
    fgets(teste, tam+10, stdin);
    if(string_vazia(teste))return 2;

    remover_enter(teste);
    if(strlen(teste)>tam){
        printf("Estouro do limite de caracteres. Tente novamente.\n"); return 1;
    }
    
    strcpy(string, teste);
    
    return 0;
}

int ler_int(int a, int b){ //substitui o scanf para inteiros; n>=a && n<=b;
    //le e verifica se a entrada do usuario eh mesmo um numero e se esta nas limitacoes especificadas
    int n;
    do{
        while(scanf("%d", &n)==0){
            printf("Escolha um numero valido.\n");
            while(getchar()!='\n'); //limpa o buffer
        }
        if(n<a || n>b)printf("Escolha um numero valido.\n");
        else break;
    }while(1);

    //getchar();
    return n;
}

//
//FUNCOES DE LEITURA DE DADOS ESPECIFICOS
int lerString_codigo(char codigo[]){//retorna 2 para string vazia, 1 para erro
    int s;
    while((s = ler_string(codigo, 5))==1);
    if(s==2)return 2;
    
    if(strlen(codigo)<5){
        printf("O numero deve conter 5 digitos. Tente novamente\n");
        return 1;
    }
    //Verifica se sao apenas numeros
    for(int i=0; i<5; i++){
        if(codigo[i] < '0' || codigo[i] > '9'){
            printf("O codigo deve conter apenas numeros. Tente novamente.\n");
            return 1;
        }
    }
        
    return 0;
}

int lerString_tarefa(char tarefa[]){
    int s, i, j;
    while((s=ler_string(tarefa, 100))==1);
    if(s==2)return 2;
    char busca[100];
    strcpy(busca, tarefa);

    for(i=0; i<p; i++){
        for(j=0; j<pessoa[i].lim; j++){
            char copia[100];
            strcpy(copia, pessoa[i].tarefa[j].nome);
            minusculas(copia);

            if(strcmp(copia, busca)==0){
                printf("Ja existe uma tarefa cadastrada com este nome. Tente novamente.\n");
                return 1;
            }
        }
    }
    return 0;
}

int procurar_colaborador(){//lê o codigo e retorna a posição do colaborador no array; -1: pessoa nao encontrada; -2:string vazia
    int x = -1, s;
    char codigo[6];
    while((s=lerString_codigo(codigo))==1);
    if(s==2)return -2;

    x = codigo_existe(codigo);
    if(x==-1)printf("Pessoa não encontrada. Tente novamente.\n");
    return x;
}

//
//
int main(){
    
    printf("+---------------------------------------------------------+\n");
    printf("|  SISTEMA DE ORGANIZACAO E ACOMPANHAMENTO DE ATIVIDADES  |\n");
    printf("+---------------------------------------------------------+\n");
    exibir_menu();

    do{
        printf("\nEscolha uma opcao: ");
        int escolha = ler_int(0, 12);

        if(escolha>2 && p==0){
            printf("Nao existem pessoas cadastradas. Cadastre um colaborador antes de usar esta funcao.\n");
            continue;
        }

        if(escolha==0){
           printf("Saindo....");
           break;
        }
        else if(escolha==1)exibir_menu();
        else if(escolha==2){//CONCLUIDO
			printf("\n+-------------------------------------------------------+\n");
            printf("|               CADASTRO DE COLABORADOR(ES)                 |\n");
            printf("+-------------------------------------------------------+\n");
            // Pede o nome e o codigo de cada colaborador 
            do{
                char nome[100];
                char codigo[6];
                int s;
                
                getchar();
                printf("\nNome do colaborador: ");
                while((s=ler_string(nome, 100))==1);
                if(s==2)break;
               
                do{
                    printf("Codigo identificador: ");
                    while((s=lerString_codigo(codigo))==1); if(s==2)break;
                    if(codigo_existe(codigo)!=-1)printf("Este codigo ja esta em uso. Tente novamente.\n");
                    else break;
                }while(1);
                if(s==2)break;

                strcpy(pessoa[p].codigo, codigo); strcpy(pessoa[p].nome, nome);
                pessoa[p].lim=0; pessoa[p].concluidas=0;
                p++;
                
                if(encerrar())break;//vai solicitar nova entrada ate que a funcao retorne 0, ou seja, nao tenha erros.
           
            }while(1);
        }
        else if(escolha==3){//CONCLUIDO
            printf("\n+-------------------------------------------------------+\n");
            printf("|                LISTA DE COLABORADOR(ES)                 |\n");
            printf("+-------------------------------------------------------+\n");
            do{
                if(p==0){
                    printf("Nenhum colaborador cadastrado.\n");
                } 
                else {
                    int j;
                    for(j = 0; j < p; j++){
                        printf("%d. %s - %s (%d tarefas cadastradas)\n", j+1, pessoa[j].codigo, pessoa[j].nome, pessoa[j].lim);
                    }

                    printf("\nInsira um numero para ver mais detalhes, ou 0 para sair: ");
                    int k = ler_int(0, p); 
                    if(!k)break;
                    
                    k--;
                    printf("\nTarefas de %s:\n", pessoa[k].nome);
                    if(pessoa[k].lim==0)printf("Esta pessoa nao possui atividades cadastradas.\n");
                    else for(j=0; j<pessoa[k].lim; j++){
                        printf("%d. %s; Prioridade: %d ", j+1, pessoa[k].tarefa[j].nome, pessoa[k].tarefa[j].prioridade);
                        switch(pessoa[k].tarefa[j].status){
                            case 1: printf("(A fazer)\n"); break;
                            case 2: printf("(Em andamento)\n"); break;
                            case 3: printf("(Concluida)\n"); break;
                        }
                    }
                }
                printf("\n");
                if(encerrar())break;
            }while(1);
        }
        else if(escolha==4){//CONCLUIDO
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  CADASTRAR ATIVIDADE(S)                  |\n");
            printf("+-------------------------------------------------------+\n");
         
          do{  
            char nome_tarefa[100];
            int x, s;
            getchar();

            //Identificar colaborador
            printf("Codigo do colaborador: ");
            while((x=procurar_colaborador())==-1)
            if(x==-2)break;
            printf("Colaborador selecionado: %s\n", pessoa[x].nome);
           
            //Nome da tarefa
            printf("\nTarefa: ");
            while((s=lerString_tarefa(nome_tarefa))==1);
            if(s==2)break;

            //Prioridade da tarefa
            printf("Prioridade da tarefa:\n");
            printf("1 - Baixa\n");
            printf("2 - Media\n");
            printf("3 - Alta\n");
            printf("Qual das opcoes?: ");
            int prioridade = ler_int(0, 3);
            if(!prioridade)break;

            //Adição da tarefa e inicialização de variaveis
            int t = pessoa[x].lim;
            strcpy(pessoa[x].tarefa[t].nome, nome_tarefa);
            pessoa[x].tarefa[t].prioridade = prioridade;
            pessoa[x].tarefa[t].status = 1;
            pessoa[x].lim++;
            printf("\nA tarefa %s foi cadastrada para o colaborador %s com sucesso.\n", pessoa[x].tarefa[t].nome, pessoa[x].nome);
            reorganizacao_por_status(x);

            if(encerrar())break;
          }while(1);
      
        }
        else if(escolha==5){//CONCLUIDO
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  LISTAR ATIVIDADE(S)                  |\n");
            printf("+-------------------------------------------------------+\n");

            //listar TODAS as atividades, independente do colaborador
            do{
                printf("Escolha uma opcao de exibicao:\n");
                printf("1. Exibir todas as atividades\n");
                printf("2. Filtrar por prioridade\n");
                printf("3. Filtrar por etapa\n");
                int opcao = ler_int(0, 3);
                if(!opcao)break;

                if(opcao==1){//exibir tudo
                    printf("\nOrdenar por prioridade (1) ou etapa (2)? ");
                    int opcao2 = ler_int(0, 2);
                    if(!opcao2)break;

                    if(opcao2==1){//prioridade
                        int i, j, k, contador=0;
                        for(k=3; k>=1; k--)//cada prioridade
                            for(i=0; i<p; i++)//cada pessoa
                                for(j=0; j<pessoa[i].lim; j++)//cada tarefa
                                    if(pessoa[i].tarefa[j].prioridade==k){
                                        contador++;
                                        printf("%d - %s (%s); Prioridade: %d\n", 
                                            contador, pessoa[i].tarefa[j].nome, pessoa[i].nome, pessoa[i].tarefa[j].prioridade);
                                    }
                    }
                    else if(opcao==2){//etapa
                        int i, j, k, contador=0;
                        for(k=1; k<=3; k++)//cada etapa
                            for(i=0; i<p; i++)//cada pessoa
                                for(j=0; j<pessoa[i].lim; j++)//cada tarefa
                                    if(pessoa[i].tarefa[j].status==k){
                                        contador++;
                                        printf("%d - %s (%s)\nEtapa: ", contador, pessoa[i].tarefa[j].nome, pessoa[i].nome);
                                        switch(k){
                                            case 1: printf("A fazer\n\n"); break;
                                            case 2: printf("Em andamento\n\n"); break;
                                            case 3: printf("Concluida\n\n"); break;
                                        }
                                    }
                    }
                }
                else if(opcao==2){//filtrar por prioridade
                    printf("\nSelecione a prioridade (numero 1-3): ");
                    int k = ler_int(0, 3);
                    if(!k)break;

                    int i, j, contador=0;
                    for(i=0; i<p; i++){//cada pessoa
                        for(j=0; j<pessoa[i].lim; j++){//cada tarefa
                            if(pessoa[i].tarefa[j].prioridade==k){
                                contador++;
                                printf("%d. %s (%s)\n", contador, pessoa[i].tarefa[j].nome, pessoa[i].nome);
                            }
                        }
                    }
                    printf("\nExistem %d tarefas com prioridade %d\n\n", contador, k);
                }
                else if(opcao==3){//filtrar por etapa
                    printf("\nSelecione a etapa (numero 1-3): ");
                    int k = ler_int(0, 3);
                    if(!k)break;

                    int i, j, contador=0;
                    for(i=0; i<p; i++){//cada pessoa
                        for(j=0; j<pessoa[i].lim; j++){//cada tarefa
                            if(pessoa[i].tarefa[j].status==k){
                                contador++;
                                printf("%d. %s (%s)\n", contador, pessoa[i].tarefa[j].nome, pessoa[i].nome);
                            }
                        }
                    }
                    printf("\nExistem %d tarefas ", contador);
                    switch(k){
                        case 1: printf("para serem feitas.\n\n"); break;
                        case 2: printf("em andamento.\n\n"); break;
                        case 3: printf("concluidas.\n\n"); break;
                    }
                }

                printf("\n");
                getchar();
                if(encerrar())break;
            }while(1);
        }
        else if(escolha==6){//CONCLUIDO
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  MOVIMENTAR ATIVIDADE(S)                 |\n");
            printf("+-------------------------------------------------------+\n");
            do{
                int i, x, status, t;
                char codigo[6];

                //Identificar colaborador
                printf("Codigo do colaborador: "); getchar();
                while((x=procurar_colaborador(codigo))==-1);
                if(x==-2)break;

                //exibir lista de tarefas da pessoa
                printf("Tarefas pendentes de %s (%d):\n", pessoa[x].nome, pessoa[x].lim-pessoa[x].concluidas);
                for(i=0; i<pessoa[x].lim; i++){
                    status = pessoa[x].tarefa[i].status;

                    if(status==3)break;

                    printf("%d. %s ", i+1, pessoa[x].tarefa[i].nome);
                    switch(status){
                        case 1: printf("(A Fazer)\n"); break;
                        case 2: printf("(Em andamento)\n"); break;
                    }
                }

                //Escolha da tarefa
                do{
                    printf("Escolha uma tarefa (numero): ");
                    t = ler_int(0, pessoa[x].lim);
                    if(pessoa[x].tarefa[t-1].status==3)printf("Esta tarefa ja foi concluida.\n");
                    else break;
                }while(1);
                if(!t)break;

                //Ação
                t--;
                pessoa[x].tarefa[t].status++;
                status = pessoa[x].tarefa[t].status;
                if(status==3)pessoa[x].concluidas++;
                reorganizacao_por_status(x);

                printf("A tarefa '%s' agora esta definida como: ", pessoa[x].tarefa[t].nome);
                switch(status){
                    case 2: printf("Em Andamento.\n"); break;
                    case 3: printf("Concluida.\n"); break;
                }

                if(encerrar())break;
            }while(1);
        }
        else if(escolha==7){//CONCLUIDO
            printf("\n+-------------------------------------------------------+\n");
            printf("|                   BUSCAR ATIVIDADE(S)                    |\n");
            printf("+-------------------------------------------------------+\n");

            do{
                char busca[100];
                int i, j, contador=0, s;

                printf("Busca: "); getchar();
                while((s=ler_string(busca, 5))==1); minusculas(busca);
                if(s==2)break;

                for(i=0; i<p; i++){//para cada pessoa
                    for(j=0; j<pessoa[i].lim; j++){//para cada tarefa
                        char copia[100];
                        strcpy(copia, pessoa[i].tarefa[j].nome);
                        minusculas(copia);

                        if(strstr(copia, busca)!=NULL){
                            printf("- %s (Atribuida a: %s)\nEtapa: ", pessoa[i].tarefa[j].nome, pessoa[i].nome);
                            switch(pessoa[i].tarefa[j].status){
                                case 1: printf("A fazer.\n\n"); break;
                                case 2: printf("Em andamento.\n\n"); break;
                                case 3: printf("Concluida.\n\n"); break;
                            }
                            contador++;
                        }
                    }
                }
                if(!contador)printf("Nao foram encontrados resultados para esta busca.\n");
                else printf("Foram encontrados %d resultados para esta busca.\n", contador);

                if(encerrar())break;
            }while(1);
        }
        else if(escolha==8){//CONCLUIDO
            printf("\n+-------------------------------------------------------+\n");
            printf("|               MOSTRAR ESTATISTICAS GERAIS             |\n");
            printf("+-------------------------------------------------------+\n\n");
            int tarefas_total=0, status1=0, status2=0, status3=0, p1=0, p2=0, p3=0;
            int i, j;

            for(i=0; i<p; i++){//alguns dados são calculados na hora
                for(j=0; j<pessoa[i].lim; j++){
                    tarefas_total+=pessoa[i].lim;

                    switch(pessoa[i].tarefa[j].status){
                        case 1: status1++; break;
                        case 2: status2++; break;
                        case 3: status3++; break;
                    }
                    switch(pessoa[i].tarefa[j].prioridade){
                        case 1: p1++; break;
                        case 2: p2++; break;
                        case 3: p3++; break;
                    }
                }
            }
            float media1 = status3/p, media2 = tarefas_total/p;

            //Impressao
            printf("Total de colaboradores: %d\n", p);
            printf("Total de atividades cadastradas: %d\n", tarefas_total);
            printf("Media de atividades por colaborador: %.1f\n\n", media2);
            printf("Media de atividades concluidas por colaborador: %.1f\n\n", media1);

            printf("Atividades nao iniciadas: %d\n", status1);
            printf("Atividades em andamento: %d\n", status2);
            printf("Atividades concluidas: %d\n\n", status3);

            printf("Prioridade baixa: %d\n", p3);
            printf("Prioridade media: %d\n", p2);
            printf("Prioridade alta: %d\n\n", p1);
        }
        else if(escolha==9){
            printf("\n+-------------------------------------------------------+\n");
            printf("|               RANKING DE PRODUTIVIDADE                |\n");
            printf("+-------------------------------------------------------+\n");

        }
        /*
        else if(escolha==10){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                    EXCLUIR ATIVIDADE                  |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==11){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                    EDITAR ATIVIDADE                   |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==12){
            printf("\n+-------------------------------------------------------+\n");
            printf("|      TROCAR COLABORADOR RESPONSAVEL POR ATIVIDADE     |\n");
            printf("+-------------------------------------------------------+\n");
        }
        */
        else printf("\nNumero invalido.\n");

    }while(1);
}
