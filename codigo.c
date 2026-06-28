#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[100];
    char descricao[500];
    int prioridade; // 1, 2 ou 3, alta, media, baixa
    int status; //1, 2 ou 3, a fazer, em andamento, concluido
} itens;

typedef struct {
    char nome[100];
    char codigo[6]; //5 digitos
    int concluidas;
    int lim; //total de tarefas de um colaborador
    itens tarefa[100];
} colaborador;

colaborador pessoa[100]; 
int p = 0; //Contador de colaboradores

//
//FUNCOES DE VERIFICACAO
int string_vazia(char string[]) { //1: é vazia
    int i;
    if(string[0]=='\0')return 1;

    for(i = 0; string[i] != '\0'; i++) {
        if(string[i] != ' ' && string[i] != '\n' && string[i] != '\t') {
            return 0;
        }
    }
    return 1;
}

int posicao_codigo(char codigo[]) { //retorna a posicao do colaborador no array, ou -1 se nao existir
    int i;
    for(i = 0; i < p; i++) {
        if(strcmp(pessoa[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1;
}

//
//FUNCOES DE USO GERAL
int encerrar() { //return 1=parar processo atual; return 0=continuar
    printf("\nContinuar? (S/N): ");
    char c;
    scanf(" %c", &c);
    getchar();
    if(c == 'n' || c == 'N') return 1;
    return 0;
}

void minusculas(char string[]) { //transforma todas as letras da string passada no parametro em minusculas
    int i;
    for(i = 0; string[i] != '\0'; i++) {
        if(string[i] >= 'A' && string[i] <= 'Z') {
            string[i] += 'a' - 'A';
        }
    }
}

void remover_enter(char t[]) {
    int x = strlen(t);
    if(x > 0 && t[x-1] == '\n') {
        t[x-1] = '\0';
    }
}

void tirar_espacos(char string[]) {
    int i, j = 0;
    int espaco_anterior = 0;
    
    // Remove espaços do início
    while(string[0] == ' ') {
        for(i = 0; string[i] != '\0'; i++) {
            string[i] = string[i+1];
        }
    }
    
    // Remove espaços duplicados
    for(i = 0; string[i] != '\0'; i++) {
        if(string[i] == ' ') {
            if(!espaco_anterior) {
                string[j++] = string[i];
                espaco_anterior = 1;
            }
        } else {
            string[j++] = string[i];
            espaco_anterior = 0;
        }
    }
    string[j] = '\0';
    
    // Remove espaço do final
    if(j > 0 && string[j-1] == ' ') {
        string[j-1] = '\0';
    }
}

void exibir_menu() {
    printf("\n# MENU\n");
    printf("1. Exibir menu.\n");
    printf("2. Cadastrar colaborador.\n");
    printf("3. Listar colaboradore(s).\n");
    printf("4. Cadastrar atividade.\n");
    printf("5. Listar atividade(s).\n");
    printf("6. Alterar etapa de atividade.\n");
    printf("7. Buscar atividade.\n");
    printf("8. Mostrar Estatisticas Gerais.\n");
    printf("9. Exibir Ranking de Colaboradores.\n");
    printf("10. Editar atividade.\n");
    printf("11. Editar informacoes de colaborador.\n");
    printf("0. Salvar e Sair.\n\n");
    printf("Obs: digite 0 ou deixe o campo vazio para cancelar qualquer acao em andamento.\n");
}

void reorganizacao_por_status(int x) {
    if(x < 0 || x >= p) return;
    
    itens temp;
    int i, j;
    for(int status = 1; status <= 3; status++) {
        for(i = 0; i < pessoa[x].lim; i++) {
            if(pessoa[x].tarefa[i].status == status) {
                for(j = i; j > 0 && pessoa[x].tarefa[j-1].status > status; j--) {
                    temp = pessoa[x].tarefa[j];
                    pessoa[x].tarefa[j] = pessoa[x].tarefa[j-1];
                    pessoa[x].tarefa[j-1] = temp;
                }
            }
        }
    }
}

void listar_prioridade(int x) {
    switch(x) {
        case 1: printf("Alta.\n"); break;
        case 2: printf("Media.\n"); break;
        case 3: printf("Baixa.\n"); break;
        default: printf("Invalida.\n");
    }
}

void listar_etapa(int x) {
    switch(x) {
        case 1: printf("A Fazer.\n"); break;
        case 2: printf("Em andamento.\n"); break;
        case 3: printf("Concluido.\n"); break;
        default: printf("Invalida.\n");
    }
}

void exibir_descricao(int x, int y) {
    
    if(string_vazia(pessoa[x].tarefa[y].descricao)) {
        printf("> Esta tarefa nao possui descricao.\n");
    } else {
        printf("> %s\n", pessoa[x].tarefa[y].descricao);
    }
}

//
//FUNCOES DE LEITURA DE DADOS NAO-ESPECIFICOS

int ler_string(char string[], int tam) { //substitui o fgets; retorna 1 para erro, 2 p/ string vazia
    //le string, remove o enter, verifica o tamanho e se eh vazio
    
    /*Exemplo de uso 1:
        while(ler_string(frase));

        O while se repete até ler_string se tornar "falsa" (0) 
    */

    /*Exemplo de uso 2:
        int erro;
        while((erro = ler_string(frase)) == 1);
        if(erro == 2)break;

        O valor de ler_string é armazenado numa variavel temporaria. 
        O while verifica o valor dela, e mantem o loop enquanto seu valor for 1
        Se for 2, o loop externo é interrompido e a acao em andamento eh cancelada
    */

    fgets(string, tam+100, stdin);
    remover_enter(string);
    tirar_espacos(string);

    if(string_vazia(string)) return 2;

    if(strlen(string) > tam) {
        printf("\nEstouro do limite de caracteres. Tente novamente.\n");
        return 1;
    } 
    return 0;
}

int ler_int(int a, int b) { //substitui o scanf para inteiros; n>=a && n<=b; retorna o valor n
    //le e verifica se a entrada do usuario eh mesmo um numero e se esta nas limitacoes especificadas

    /*Exemplo de uso:
        int x = ler_int(1, 10)
        x eh um numero do intervalo [1, 10]
    */

    do {
        char n[100];
        int i, num = 0, erro = 0, s;

        while((s = ler_string(n, 100)) == 1);
        
        //Campo vazio
        if(s == 2) {
            printf("\nEscolha um numero valido.\n");
            continue;
        }

        //Nao contem apenas digitos
        for(i = 0; n[i] != '\0'; i++) {
            if(n[i] < '0' || n[i] > '9') {
                printf("\nInsira um numero valido.\n");
                erro = 1;
                break;
            }
        }
        if(erro) continue;

        //Conversão de string para inteiro
        for(i = 0; n[i] != '\0'; i++) {
            num *= 10;
            num += n[i] - '0';
        }

        //Verificacao de intervalo
        if(num < a || num > b) {
            printf("\nInsira um numero valido (entre %d e %d).\n", a, b);
            continue;
        }

        return num;
    } while(1);
}

//
//FUNCOES DE LEITURA DE DADOS ESPECIFICOS
int lerString_codigo(char codigo[]) { //retorna 2 para string vazia, 1 para erro
    //lê um codigo num formato valido (5 digitos, so numeros), sem verificar se ja existe

    int s;
    while((s = ler_string(codigo, 5)) == 1);
    if(s == 2) return 2;

    //Codigo de 5 digitos
    if(strlen(codigo) < 5) {
        printf("\nO codigo deve conter 5 digitos. Tente novamente.\n");
        return 1;
    }
    
    //Verifica se sao apenas numeros
    int i;
    for(i = 0; i < 5; i++) {
        if(codigo[i] < '0' || codigo[i] > '9') {
            printf("\nO codigo deve conter apenas numeros. Tente novamente.\n");
            return 1;
        }
    }
        
    return 0;
}

int lerString_tarefa(char tarefa[]) { //retorna 2 para string vazia, 1 para erro
    int s, i, j;
    while((s = ler_string(tarefa, 100)) == 1);
    if(s == 2) return 2;

    //Verifica se ja nao existe uma tarefa com este nome
    char busca[100]; 
    strcpy(busca, tarefa);
    minusculas(busca);
    for(i = 0; i < p; i++) {
        for(j = 0; j < pessoa[i].lim; j++) {
            char copia[100];
            strcpy(copia, pessoa[i].tarefa[j].nome);
            minusculas(copia);

            if(strcmp(copia, busca) == 0) {
                printf("\nJa existe uma tarefa cadastrada com este nome. Tente novamente.\n");
                return 1;
            }
        }
    }
    return 0;
}
//
//OUTROS

void exibir_tarefas(int k) { //recebe a posicao da pessoa no vetor e imprime todas as suas atividades
    
    int j;
    printf("\nTarefas de %s:\n\n", pessoa[k].nome);

    if(pessoa[k].lim == 0) {
        printf("Esta pessoa nao possui atividades cadastradas.\n");
    } else {
        
            for(j = 0; j < pessoa[k].lim; j++) {
                printf("%d. %s\n", j+1, pessoa[k].tarefa[j].nome);//nome

                printf("Prioridade: ");//prioridade
                listar_prioridade(pessoa[k].tarefa[j].prioridade);

                printf("Etapa: ");//etapa
                listar_etapa(pessoa[k].tarefa[j].status);

                printf("\n");
            }
        do{
            printf("\n-> Insira um numero para ver a descricao desta tarefa, ou 0 para sair.\n> ");
            int l = ler_int(0, pessoa[k].lim);
            if(l == 0) break;
            l--;
            exibir_descricao(k, l);
        }while(1);
    }
}

int procurar_colaborador() { //le o codigo e retorna a posicao do colaborador no array; -1: pessoa nao encontrada; -2:string vazia
    int x = -1, s;
    char codigo[6];
    while((s = lerString_codigo(codigo)) == 1);
    if(s == 2) return -2;

    x = posicao_codigo(codigo);
    if(x == -1) {printf("\nPessoa nao encontrada. Tente novamente.\n"); return -1;}
    return x;
}

//
//SALVAR E CARREGAR DADOS
void carregar_dados(colaborador *c) {
    FILE *arquivo = fopen("dados_lp.bin", "rb");
    if(arquivo == NULL) {
        printf("Nenhum arquivo de dados encontrado. Iniciando com dados vazios.\n");
        return;
    }
    fread(&p, sizeof(int), 1, arquivo);
    fread(c, sizeof(colaborador), p, arquivo);
    fclose(arquivo);
}

void salvar_dados(colaborador *c) {
    FILE *arquivo = fopen("dados_lp.bin", "wb");
    if(arquivo == NULL) {
        printf("Ocorreu um erro ao salvar os arquivos.\n");
        return;
    }
    fwrite(&p, sizeof(int), 1, arquivo);
    fwrite(c, sizeof(colaborador), p, arquivo);
    fclose(arquivo);
}

//
//FUNCAO PRINCIPAL
int main() {
    carregar_dados(pessoa);

    printf("+---------------------------------------------------------+\n");
    printf("|  SISTEMA DE ORGANIZACAO E ACOMPANHAMENTO DE ATIVIDADES  |\n");
    printf("+---------------------------------------------------------+\n");
    exibir_menu();

    do {
        printf("\n===============================================================\n");
        printf("-> Escolha uma opcao do menu(1), ou 0 para encerrar o programa.\n> ");
        int escolha = ler_int(0, 11);

        if(escolha > 2 && p == 0) {
            printf("Nao existem pessoas cadastradas. Cadastre um colaborador antes de usar esta funcao.\n");
            continue;
        }

        if(escolha == 0) {
            printf("Saindo...\n");
            salvar_dados(pessoa);
            break;
        }
        else if(escolha == 1) {
            exibir_menu();
        }
        else if(escolha == 2) { //Cadastro de colaboradores
            if(p == 100) {
                printf("A capacidade maxima de colaboradores cadastrados foi alcancada (100).\n"
                        "Exclua algum perfil para cadastrar outro.\n");
                continue;
            }

            printf("\n+-------------------------------------------------------+\n");
            printf("|               CADASTRO DE COLABORADOR(ES)             |\n");
            printf("+-------------------------------------------------------+\n");
            // Pede o nome e o codigo de cada colaborador 
            do {
                printf("\n////");
                char nome[100], codigo[6];
                int s;

                //Ler nome
                printf("\n-> Nome do colaborador: ");
                while((s = ler_string(nome, 100)) == 1);
                if(s == 2) break;

                //Ler Codigo
                printf("\n-> Codigo identificador: ");
                do {
                    while((s = lerString_codigo(codigo)) == 1);
                    if(s == 2) break;

                    if(posicao_codigo(codigo) != -1) {
                        printf("\nEste codigo ja esta em uso. Tente novamente.\n");
                    } else break;
                } while(1);
                if(s == 2) break;

                //Criacao do colaborador e inicializacao de variaveis
                strcpy(pessoa[p].codigo, codigo);
                strcpy(pessoa[p].nome, nome);
                pessoa[p].lim = 0;
                pessoa[p].concluidas = 0;
                p++;
                printf("O perfil de %s (%s) foi criado com sucesso.\n", nome, codigo);
                
                if(encerrar()) break;
            } while(1);
        }
        else if(escolha == 3) { //Listagem de colaboradores
            printf("\n+-------------------------------------------------------+\n");
            printf("|                LISTA DE COLABORADOR(ES)               |\n");
            printf("+-------------------------------------------------------+\n");
            do {
                int j;
                printf("\n////\nLista de Colaboradores (%d)\n\n", p);

                //Listagem de colaboradores
                for(j = 0; j < p; j++) {
                    printf("%d. %s - %s (%d tarefas, %d pendentes)\n", 
                           j+1, pessoa[j].codigo, pessoa[j].nome, 
                           pessoa[j].lim, pessoa[j].lim - pessoa[j].concluidas);
                }

                //Exibir tarefas do colaborador
                printf("\n-> Insira um numero para ver mais detalhes, ou 0 para sair.\n> ");
                int k = ler_int(0, p);
                if(k == 0) break;
                k--;
                exibir_tarefas(k);
                
            } while(1);
        }
        else if(escolha == 4) { //Cadastro de atividades
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  CADASTRAR ATIVIDADE(S)                  |\n");
            printf("+-------------------------------------------------------+\n");
         
            do {  
                char nome_tarefa[100], desc[500];
                int x, s;
                printf("\n////");

                //Identificar colaborador
                printf("\n-> Codigo do colaborador: ");
                while((x = procurar_colaborador()) == -1);
                if(x == -2) break;
                printf("\nColaborador selecionado: %s\n", pessoa[x].nome);

                //Verificacao do estouro do limite de tarefas
                if(pessoa[x].lim == 100) {
                    printf("Este colaborador ja alcancou o limite maximo de atividades cadastradas em seu nome.\nExclua alguma para adicionar outras.\n");
                    continue;
                }
           
                //Nome da tarefa
                printf("\n-> Nova Tarefa: ");
                while((s = lerString_tarefa(nome_tarefa)) == 1);
                if(s == 2) break;

                //Prioridade da tarefa
                printf("\nPrioridade da tarefa:\n");
                printf("1. Alta\n");
                printf("2. Media\n");
                printf("3. Baixa\n");
                printf("> ");
                int prioridade = ler_int(0, 3);
                if(!prioridade) break;

                //Descricao
                printf("\n-> Adicione uma descricao, ou deixe em branco para pular esta etapa.\n> ");
                while((s = ler_string(desc, 500)) == 1);

                //Adicao da tarefa e inicializacao de variaveis
                int t = pessoa[x].lim;
                strcpy(pessoa[x].tarefa[t].nome, nome_tarefa);
                strcpy(pessoa[x].tarefa[t].descricao, desc);
                pessoa[x].tarefa[t].prioridade = prioridade;
                pessoa[x].tarefa[t].status = 1;
                pessoa[x].lim++;
                printf("\nA tarefa %s foi cadastrada para o colaborador %s com sucesso.\n", 
                       pessoa[x].tarefa[t].nome, pessoa[x].nome);
                reorganizacao_por_status(x);

                if(encerrar()) break;
            } while(1);
        }
        else if(escolha == 5) { //Listagem de atividades
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  LISTAR ATIVIDADE(S)                  |\n");
            printf("+-------------------------------------------------------+\n");

            do {
                printf("\n////\n");
                printf("Escolha uma opcao de exibicao:\n");
                printf("1. Exibir todas as atividades\n");
                printf("2. Filtrar por prioridade\n");
                printf("3. Filtrar por etapa\n\n> ");
                int opcao = ler_int(0, 3);
                
                // Arrays com tamanho fixo seguro (maximo 100 colaboradores * 100 tarefas)
                int user[10000], item[10000], tam = 0;

                //Exibicao
                if(!opcao) break;
                else if(opcao == 1) { //exibir tudo
                    printf("\nOrdenar por prioridade (1) ou etapa (2)?\n> ");
                    int opcao2 = ler_int(0, 2);
                    if(!opcao2) break;

                    if(opcao2 == 1) { //prioridade
                        int i, j, k, contador = 0;
                        for(k = 1; k <= 3; k++) { //cada prioridade
                            for(i = 0; i < p; i++) { //cada pessoa
                                for(j = 0; j < pessoa[i].lim; j++) { //cada tarefa
                                    if(pessoa[i].tarefa[j].prioridade == k) {
                                        contador++;
                                        printf("%d. %s (%s)\n    Prioridade: ", 
                                               contador, pessoa[i].tarefa[j].nome, pessoa[i].nome);
                                        listar_prioridade(k); printf("\n");

                                        user[tam] = i;
                                        item[tam] = j; 
                                        tam++;
                                    }
                                }
                            }
                        }                        
                    }
                    else if(opcao2 == 2) { //etapa
                        int i, j, k, contador = 0;
                        for(k = 1; k <= 3; k++) { //cada etapa
                            for(i = 0; i < p; i++) { //cada pessoa
                                for(j = 0; j < pessoa[i].lim; j++) { //cada tarefa
                                    if(pessoa[i].tarefa[j].status == k) {
                                        contador++;
                                        printf("%d - %s (%s)\n    Etapa: ", contador, pessoa[i].tarefa[j].nome, pessoa[i].nome);
                                        listar_etapa(pessoa[i].tarefa[j].status); printf("\n");
                                        user[tam] = i;
                                        item[tam] = j; 
                                        tam++;
                                    }
                                }
                            }
                        }                            
                    }
                }
                else if(opcao==2){//filtrar por prioridade
                    printf("\nSelecione a prioridade (numero 1-3): ");
                    int k = ler_int(0, 3);
                    if(!k)break;

					printf("\nExibindo todas as tarefas com prioridade: "); listar_prioridade(k);
                    printf("\n");
					
                    int i, j, contador=0;
                    for(i=0; i<p; i++)//cada pessoa
                        for(j=0; j<pessoa[i].lim; j++)//cada tarefa
                            if(pessoa[i].tarefa[j].prioridade==k){
                                contador++;
                                printf("%d - %s (%s)\n", contador, pessoa[i].tarefa[j].nome, pessoa[i].nome);

                                user[tam]=i; item[tam]=j; 
                                tam++;
                            }
                }
                else if(opcao==3){//filtrar por etapa
                    printf("\nSelecione a etapa (numero 1-3): ");
                    int k = ler_int(0, 3);
                    if(!k)break;

					printf("\nExibindo todas as tarefas na etapa: "); listar_etapa(k);
                    printf("\n");

                    int i, j, contador=0;
                    for(i=0; i<p; i++)//cada pessoa
                        for(j=0; j<pessoa[i].lim; j++)//cada tarefa
                            if(pessoa[i].tarefa[j].status==k){
                                contador++;
                                printf("%d - %s (%s)\n", contador, pessoa[i].tarefa[j].nome, pessoa[i].nome);

                                user[tam]=i; item[tam]=j; 
                                tam++;
                            }
                }
                
                if (tam) do{
                    printf("\n-> Insira um numero para ver a descricao desta tarefa, ou 0 para sair.\n> ");
                    int x = ler_int(0, tam);
                    if(x == 0) break;
                    x--;
                    exibir_descricao(user[x], item[x]);
                }while(1);

                printf("\n");

            } while(1);
        }
        else if(escolha == 6) { //Alterar etapa
            printf("\n+-------------------------------------------------------+\n");
            printf("|              ALTERAR STATUS DE ATIVIDADE(S)           |\n");
            printf("+-------------------------------------------------------+\n");
            do {
                int i, x, status, t;
                printf("\n////");

                //Identificar colaborador
                printf("\nCodigo do colaborador: ");
                while((x = procurar_colaborador()) == -1);
                if(x == -2) break;

                //exibir lista de tarefas da pessoa (apenas nao concluidas)
                printf("Tarefas pendentes de %s (%d):\n", pessoa[x].nome, pessoa[x].lim - pessoa[x].concluidas);
                for(i = 0; i < pessoa[x].lim; i++) {
                    status = pessoa[x].tarefa[i].status;
                    if(status == 3) break; 
                    // no vetor, as tarefas concluidas estao por ultimo
                    // elas nao sao exibidas, entao quebra o loop
                    
                    printf("%d. %s ", i+1, pessoa[x].tarefa[i].nome);
                    switch(status) {
                        case 1: printf("(A Fazer)\n"); break;
                        case 2: printf("(Em andamento)\n"); break;
                    }
                }

                //Escolha da tarefa
                printf("\nEscolha uma tarefa (numero): ");
                do {
                    t = ler_int(0, pessoa[x].lim);
                    if(!t) break;
                    if(pessoa[x].tarefa[t-1].status == 3) {
                        printf("\nEsta tarefa ja foi concluida. Insira outra.\n");
                    } else break;
                } while(1);
                if(!t) break; 

                //Acao
                t--;
                printf("\nA tarefa '%s' agora esta definida como: ", pessoa[x].tarefa[t].nome);
                pessoa[x].tarefa[t].status++;
                status = pessoa[x].tarefa[t].status;
                if(status == 3) pessoa[x].concluidas++;
                reorganizacao_por_status(x);
                
                listar_etapa(status);

                printf("Voce pode alterar outras tarefas.\n");
                if(encerrar()) break;
            } while(1);
        }
        else if(escolha == 7) { //Buscar
            printf("\n+-------------------------------------------------------+\n");
            printf("|                   BUSCAR ATIVIDADE(S)                    |\n");
            printf("+-------------------------------------------------------+\n");

            do {
                char busca[100];
                int i, j, contador = 0, s;
                printf("\n////");

                //Leitura da string busca - CORRIGIDO: tamanho 100
                printf("\nBusca: ");
                while((s = ler_string(busca, 100)) == 1);
                minusculas(busca);
                if(s == 2) break;
                printf("\n");

                //Busca por todas as tarefas, de todas as pessoas
                for(i = 0; i < p; i++) { //para cada pessoa
                    for(j = 0; j < pessoa[i].lim; j++) { //para cada tarefa
                        char copia[100];
                        strcpy(copia, pessoa[i].tarefa[j].nome);
                        minusculas(copia);

                        if(strstr(copia, busca) != NULL) {
                            printf("- %s (Atribuida a: %s (%s))\n", 
                                   pessoa[i].tarefa[j].nome, pessoa[i].nome, pessoa[i].codigo);
                            printf("Etapa: ");
                            listar_etapa(pessoa[i].tarefa[j].status);
                            printf("Prioridade: ");
                            listar_prioridade(pessoa[i].tarefa[j].prioridade);
                            exibir_descricao(i, j);
                            printf("\n");
                            contador++;
                        }
                    }
                }
                if(!contador) {
                    printf("Nao foram encontrados resultados para esta busca.\n");
                } else {
                    printf("Foram encontrados %d resultados para esta busca.\n", contador);
                }

                printf("Voce pode realizar uma nova busca.");
                if(encerrar()) break;
            } while(1);
        }
        else if(escolha == 8) { //Estatisticas Gerais
            printf("\n+-------------------------------------------------------+\n");
            printf("|               MOSTRAR ESTATISTICAS GERAIS             |\n");
            printf("+-------------------------------------------------------+\n\n");
            int tarefas_total = 0;
            int status1 = 0, status2 = 0, status3 = 0;
            int p1 = 0, p2 = 0, p3 = 0;
            int i, j;
            
            //alguns dados sao calculados na hora:
            //tarefas totais, tarefas por etapa, tarefas por prioridade, medias
            for(i = 0; i < p; i++) {
                tarefas_total += pessoa[i].lim;

                for(j = 0; j < pessoa[i].lim; j++) {
                    switch(pessoa[i].tarefa[j].status) {
                        case 1: status1++; break;
                        case 2: status2++; break;
                        case 3: status3++; break;
                    }
                    switch(pessoa[i].tarefa[j].prioridade) {
                        case 1: p1++; break;
                        case 2: p2++; break;
                        case 3: p3++; break;
                    }
                }
            }
            float media = (float)tarefas_total / p;
            float taxa;

            if(tarefas_total==0) taxa=0;
            else taxa = ((float)status3/tarefas_total)*100;

            //Impressao
            printf("Total de colaboradores: %d\n", p);
            printf("Total de atividades cadastradas: %d\n", tarefas_total);
            printf("Media de atividades por colaborador: %.1f\n", media);
            printf("Taxa de tarefas concluidas: %.2f%%\n\n", taxa);

            printf("Atividades nao iniciadas: %d\n", status1);
            printf("Atividades em andamento: %d\n", status2);
            printf("Atividades concluidas: %d\n\n", status3);

            printf("Prioridade baixa: %d\n", p3);
            printf("Prioridade media: %d\n", p2);
            printf("Prioridade alta: %d\n\n", p1);

            printf("Fim da exibicao.\n");
        }
        else if(escolha == 9) { //Ranking 
            printf("\n+-------------------------------------------------------+\n");
            printf("|               RANKING DE PRODUTIVIDADE                |\n");
            printf("+-------------------------------------------------------+\n");

            int usados[5], u = 0;
            int i, j, ranking;

            //Impressao do ranking
            int max_ranking = (p < 5) ? p : 5;
            for(ranking = 1; ranking <= max_ranking; ranking++) { //para cada posicao do ranking
                int maior = -1, posicao = -1;

                for(i = 0; i < p; i++) { //para cada pessoa
                    if(pessoa[i].concluidas > maior) {
                        int parar = 0;
                        for(j = 0; j < u; j++) {
                            if(i == usados[j]) {
                                parar = 1;
                                break;
                            }
                        }
                        if(!parar) {
                            maior = pessoa[i].concluidas;
                            posicao = i;
                        }
                    }
                }
                
                if(posicao != -1) {
                    printf("%do. %s (%d tarefas concluidas)\n", 
                           ranking, pessoa[posicao].nome, pessoa[posicao].concluidas);
                    usados[u] = posicao;
                    u++;
                }
            }
            printf("\nFim da exibicao.\n");
        }
        else if(escolha == 10) { //Editar atividade
            printf("\n+-------------------------------------------------------+\n");
            printf("|                    EDITAR ATIVIDADE                   |\n");
            printf("+-------------------------------------------------------+\n");
            do {
                int x, t, opcao, i, j;
                printf("\n////");

                //Leitura do codigo do colaborador x
                printf("\n-> Codigo do colaborador: ");
                while((x = procurar_colaborador()) == -1);
                if(x == -2) break;

                //Exibicao das tarefas
                printf("\nTarefas de %s:\n\n", pessoa[x].nome);
                if(pessoa[x].lim == 0) {
                    printf("Esta pessoa nao possui atividades cadastradas.\n");
                    continue;
                } 
                else {
                    for(j = 0; j < pessoa[x].lim; j++) {
                        printf("%d. %s\n", j+1, pessoa[x].tarefa[j].nome);//nome

                        printf("Prioridade: ");//prioridade
                        listar_prioridade(pessoa[x].tarefa[j].prioridade);

                        printf("Etapa: ");//etapa
                        listar_etapa(pessoa[x].tarefa[j].status);

                        printf("\n");
                    }
                }

                //Escolha e exibicao da tarefa t
                printf("-> Escolha a tarefa: ");
                t = ler_int(0, pessoa[x].lim);
                if(!t) break;
                t--;

                do{
                    //Tarefa Selecionada
                    printf("\n----------");
                    printf("\nA seguinte tarefa foi selecionada:\n");
                    printf("\n%s (%s)\n", pessoa[x].tarefa[t].nome, pessoa[x].nome);
                    printf("Etapa atual: ");
                    listar_etapa(pessoa[x].tarefa[t].status);
                    printf("Prioridade: ");
                    listar_prioridade(pessoa[x].tarefa[t].prioridade);
                    printf("Descricao:\n");
                    exibir_descricao(x, t);

                    //Listagem de opcoes de edicao
                    printf("\nEscolha uma opcao para editar:\n");
                    printf("1. Nome\n");
                    printf("2. Prioridade\n");
                    printf("3. Trocar Colaborador Responsavel\n");
                    printf("4. Excluir Atividade\n");
                    printf("5. Editar Descricao\n");
                    printf("> ");
                    opcao = ler_int(0, 5); printf("\n");

                    //Acoes
                    if(!opcao) break;
                    else if(opcao == 1) { //editar nome
                        int s;
                        char novo[100];

                        //Leitura do novo nome
                        printf("-> Novo nome: ");
                        while((s = lerString_tarefa(novo)) == 1);
                        if(s == 2) break;

                        //Confirmacao
                        printf("\nA seguinte modificacao de nome sera feita:\n");
                        printf("%s -> %s\n", pessoa[x].tarefa[t].nome, novo);
                        if(encerrar()) break;

                        //Acao
                        strcpy(pessoa[x].tarefa[t].nome, novo);
                        printf("Mudanca bem-sucedida.\n");
                    }
                    else if(opcao == 2) { //editar prioridade
                        //Leitura da nova prioridade
                        printf("-> Nova prioridade (1-3)\n> ");
                        int prioridade = ler_int(0, 3);
                        if(!prioridade) break;

                        //Acao
                        pessoa[x].tarefa[t].prioridade = prioridade;
                        printf("Agora a tarefa '%s' tem prioridade: ", pessoa[x].tarefa[t].nome);
                        listar_prioridade(prioridade);
                    }
                    else if(opcao == 3) { // atribuir a outro colaborador
                        int x2;

                        //Leitura do novo colaborador
                        printf("-> Informe o codigo do novo colaborador responsavel.\n> ");
                        do {
                            while((x2 = procurar_colaborador()) == -1);
                            if(x2 == -2) break;
                            
                            if(pessoa[x2].lim == 100) {
                                printf("\nEste colaborador ja alcancou o limite maximo de atividades cadastradas em seu nome. Tente novamente.\n");
                            }
                            else break;
                        } while(1);
                        if(x2 == -2) break;

                        //Confirmacao
                        printf("\nO colaborador %s passara a ser responsavel pela tarefa selecionada.\n", pessoa[x2].nome);
                        if(encerrar()) break;

                        //Acao
                        pessoa[x2].tarefa[pessoa[x2].lim] = pessoa[x].tarefa[t]; 
                        for(i = t; i < pessoa[x].lim - 1; i++) {
                            pessoa[x].tarefa[i] = pessoa[x].tarefa[i+1];
                        }
                        pessoa[x].lim--;
                        pessoa[x2].lim++;
                        if(pessoa[x].tarefa[t].status == 3) {
                            pessoa[x].concluidas--;
                            pessoa[x2].concluidas++;
                        }
                        reorganizacao_por_status(x2);
                        printf("\nTroca bem-sucedida.\n");
                    }
                    else if(opcao == 4) { //excluir
                        //Confirmacao
                        printf("Aviso: A acao de apagar atividade nao pode ser desfeita.\n");
                        if(encerrar()) break;

                        //Acao
                        if(pessoa[x].tarefa[t].status==3)pessoa[x].concluidas--;
                        for(i = t; i < pessoa[x].lim - 1; i++) {
                            pessoa[x].tarefa[i] = pessoa[x].tarefa[i+1];
                        }
                        pessoa[x].lim--;
                        printf("\nTarefa apagada com sucesso.\n");
                        break;
                    }
                    else if(opcao == 5) { //editar descricao
                        char novo[500];
                        int s;

                        printf("-> Insira a nova descricao.\n> ");
                        while((s = ler_string(novo, 500)) == 1);

                        if(s == 2) {
                            printf("\nAviso: A descricao desta tarefa sera apagada.\n");
                            if(encerrar()) break;
                        }
                        
                        strcpy(pessoa[x].tarefa[t].descricao, novo);
                        printf("\nMudanca bem-sucedida.\n");
                    }
                    
                    printf("\nVoce pode realizar mais modificacoes para esta tarefa.");
                    if(encerrar())break;
                }while(1);

            } while(1);
        }
        else if(escolha == 11) { //Editar colaborador
            printf("\n+-------------------------------------------------------+\n");
            printf("|                    EDITAR COLABORADOR                   |\n");
            printf("+-------------------------------------------------------+\n");
            
            do {
                int x, i;
                printf("\n////\n");

                //Leitura do colaborador
                printf("Insira o codigo do colaborador: ");
                while((x = procurar_colaborador()) == -1);
                if(x == -2) break;
                printf("\nUsuario selecionado: %s\n", pessoa[x].nome);

                //Listagem de acoes
                printf("\nEscolha uma acao para prosseguir:\n");
                printf("1. Mudar nome\n");
                printf("2. Excluir colaborador\n> ");
                int opcao = ler_int(0, 3);
                if(!opcao) break;

                if(opcao == 1) { //Mudar nome
                    char novo[100];
                    printf("\nNovo nome: ");
                    ler_string(novo, 100);

                    //Confirmacao
                    printf("A seguinte mudanca sera feita:\n");
                    printf("%s -> %s\n", pessoa[x].nome, novo);
                    if(encerrar()) break;

                    strcpy(pessoa[x].nome, novo);
                    printf("Mudanca bem-sucedida.\n");
                }
                else if(opcao == 2) { //Excluir
                    //Confirmacao
                    printf("Tem certeza que deseja excluir o usuario %s (%s)? ", 
                           pessoa[x].nome, pessoa[x].codigo);
                    printf("Todas as seguintes tarefas serao perdidas:\n");
                    exibir_tarefas(x);
                    if(encerrar()) break;

                    for(i = x; i < p - 1; i++) {
                        pessoa[i] = pessoa[i+1];
                    }
                    p--;
                    printf("\nRemocao bem-sucedida.\n");
                }
            } while(1);
        }
        else {
            printf("\nNumero invalido.\n");
        }

    } while(1);

    salvar_dados(pessoa);
    return 0;
}
