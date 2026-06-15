#include <stdio.h>
#include <string.h>

/*
LISTA DE AFAZERES (que ironia)
- Criar funções de leitura e verificação
- Fazer as funcionalidades solicitadas pelo projeto
- Requisito 1: Pensar numa forma de acrescentar tarefas ao mesmo tempo que as realoca por prioridade
*/

typedef struct {
    char nome[100];
    //char descricao[200]; deixa isso aqui pra depois, muito trabalho...
    int prioridade; // 1, 2 ou 3, prioridade crescente
    int status;//1, 2 ou 3, a fazer, em andamento, concluido
}itens;

typedef struct{
    char nome[100];
    char codigo[6];//5 digitos
    int pendentes;//isso aqui pode ajudar ao fazer o ranking!
    int lim;//total de tarefas de um colaborador
    itens tarefa[100];
}colaborador;

colaborador pessoa[100]; int p=0;


//
//FUNCOES DE USO GERAL
int encerrar(){//return 1=parar processo atual; return 0=continuar
	printf("Continuar? (S/N) ");
	char c = getchar();
	if(c=='n' || c=='N')return 1;
	return 0;
}

void minusculas(char string[]){//transforma todas as letras da string passada no parametro em minusculas
	int i;
	for(i=0; string[i]!='\0'; i++){
		if(string[i]>='A' && string[i]<='Z')string[i]+='a'-'A';
	}
}

void remover_enter(char t[]){
    int x = strlen(t);
    if(t[x-1]=='\n' && x>0)t[x-1]='\0';
}


//
//FUNCOES DE VERIFICACAO
int string_vazia(char string[]){
	int i;
	for(i=0; string[i]!='\0'; i++)if(string[i]!=' ' && string[i]!='\n')return 0;
    printf("A entrada nao pode ser vazia.\n");
	return 1;
}


//
//FUNCOES DE LEITURA DE DADOS NAO-ESPECIFICOS
int ler_string(char string[], int tam){//substitui o fgets
    //lê string, remove o enter, verifica o tamanho e se é vazio
    int i;
    fgets(string, tam+10, stdin); remover_enter(string);
    
    if(strlen(string)>tam){
        printf("Estouro do limite de caracteres. Tente novamente."); return 1;
    }
    if(string_vazia(string))return 1;
    
    return 0;
}

int ler_int(){//substitui o scanf para inteiros
    //lê e verifica se a entrada do usuario é mesmo um numero
    int n;
    while(scanf("%d", &n)==0){
        printf("Por favor, insira um numero valido: ");
        while(getchar()!='\n');//limpar buffer
    }
    getchar();
    return n;
}

//
//FUNCOES DE LEITURA DE DADOS ESPECIFICOS
//exemplos:
//int lerString_tarefa() --> contém: verificacao para nome de tarefa já usado
//int lerString_codigo() --> contém: verificacao para codigo de colaborador já usado
//int lerInt_ prioridade()
//etc etc

int main(){

    /*
        Inserir Menu Aqui
    */

    do{
        printf("Escolha um numero: ");
        int escolha = ler_int();

        if(!escolha)break;
        else if(escolha==1){
            printf(":: Cadastro de Colaborador ::\n");
            do{
                char nome[100];

                printf("Nome do colaborador: ");
                while(ler_string(nome, 100)); strcpy(pessoa[p].nome, nome);
                //vai solicitar nova entrada até que a funcao retorne 0, ou seja, não tenha erros

                if(encerrar())break;
            }while(1);


        }
        else if(escolha==2){
            printf(":: Listar Colaboradores ::\n");



        }
        else if(escolha==3){
            printf(":: Cadastrar nova Atividade ::\n");



        }
        else if(escolha==4){
            printf(":: Listar Atividades ::\n");



        }
        else if(escolha==5){
            printf(":: Movimentar Atividades ::\n");



        }
        else if(escolha==6){
            printf(":: Buscar Atividades ::\n");



        }
        else if(escolha==7){
            printf(":: Mostrar Estatisticas Gerais ::\n");



        }
        else if(escolha==8){
            printf(":: Ranking de Colaboradores ::\n");



        }
        /*
        else if(escolha==9){
            printf(":: Excluir Atividade ::\n");
        }
        else if(escolha==10){
            printf(":: Editar Atividade ::\n");
        }
        else if(escolha==11){
            printf(":: Trocar colaborador responsavel por uma atividade ::\n");
        }
        */
        else printf("Numero valido.\n");

    }while(1);
}