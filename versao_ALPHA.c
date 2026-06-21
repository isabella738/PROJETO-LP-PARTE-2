#include <stdio.h>
#include <string.h>

/*
LISTA DE AFAZERES (que ironia)
- Criar funcoes de leitura e verificacao
- Fazer as funcionalidades solicitadas pelo projeto
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
    int pendentes; //isso aqui pode ajudar ao fazer o ranking!
    int lim; //total de tarefas de um colaborador
    itens tarefa[100];
}colaborador;

colaborador pessoa[100]; 
int p=0 /*Contador de colaboradores*/;
int t=0 /* Contador para tarefas*/;

int i,j,f=0,a=0,c=0;

//FUNCOES DE USO GERAL
int encerrar(){ //return 1=parar processo atual; return 0=continuar
	printf("Continuar? (S/N) ");
	char c = getchar();
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

//FUNCOES DE VERIFICACAO
int string_vazia(char string[]){
	int i;
	for(i=0; string[i]!='\0'; i++)if(string[i]!=' ' && string[i]!='\n')return 0;
    printf("A entrada nao pode ser vazia.\n");
	return 1;
}

//FUNCOES DE LEITURA DE DADOS NAO-ESPECIFICOS
int ler_string(char string[], int tam){//substitui o fgets
    //le string, remove o enter, verifica o tamanho e se eh vazio
    int i;
    fgets(string, tam+10, stdin); remover_enter(string);
    
    if(strlen(string)>tam){
        printf("Estouro do limite de caracteres. Tente novamente."); return 1;
    }
    if(string_vazia(string))return 1;
    
    return 0;
}

int ler_int(){ //substitui o scanf para inteiros
    //le e verifica se a entrada do usuario eh mesmo um numero
    int n;
    while(scanf("%d", &n)==0){
        printf("Por favor, insira um numero valido: ");
        while(getchar()!='\n'); //limpa o buffer
    }
    getchar();
    return n;
}

//FUNCOES DE LEITURA DE DADOS ESPECIFICOS

//int lerString_tarefa() --> contem: verificacao para nome de tarefa ja usado
int codigo_existe(char codigo[]){
    for(int i=0; i<p; i++){
        if(strcmp(pessoa[i].codigo, codigo)==0){
            return 1;
        }
    }
    return 0;
}

// Verifica a quantidade de dígitos do código de cada colaborador 
int lerString_codigo(char codigo[]){
    do{
        printf("Codigo identificador: ");
        if(ler_string(codigo, 6)) continue;
        
        if(strlen(codigo) != 5){
            printf("O codigo deve ter exatamente 5 digitos.\n");
            continue;
        }
        
        //Verifica se sao apenas numeros
        int numerico = 1;
        for(int i=0; i<5; i++){
            if(codigo[i] < '0' || codigo[i] > '9'){
                numerico = 0;
                break;
            }
        }
        if(!numerico){
            printf("O codigo deve conter apenas numeros.\n");
            continue;
        }
        
        if(codigo_existe(codigo)){
            printf("Este codigo ja esta em uso.\n");
            continue;
        }
        
        return 0;
    }while(1);
}

int nome_ja_existe(char nome[]){
    for(int i=0; i<p; i++){
        if(strcmp(pessoa[i].nome, nome)==0) return 1;
    }
    return 0;
}

int lerString_nome(char nome[]){
    do{
        printf("Nome do colaborador: ");
        if(ler_string(nome, 100)) continue;
        
        if(nome_ja_existe(nome)){
            printf("Este nome ja esta cadastrado.\n");
            continue;
        }
        
        return 0;
    }while(1);
}

int main(){
    
    // Menu das opcoes
    
    printf("+---------------------------------------------------------+\n");
    printf("|  SISTEMA DE ORGANIZACAO E ACOMPANHAMENTO DE ATIVIDADES  |\n");
    printf("+---------------------------------------------------------+");
    printf("\n");
	printf("1. Cadastrar colaborador.\n");
	printf("2. Listar colaboradore(s).\n");
	printf("3. Cadastrar atividade.\n");
	printf("4. Listar atividade(s).\n");
	printf("5. Movimentar atividade.\n");
	printf("6. Buscar atividade.\n");
	printf("7. Mostrar Estatisticas Gerais.\n");
	printf("8. Exibir Ranking de Colaboradores.\n");
    printf("9. Excluir atividade.\n");
	printf("10. Editar atividade.\n");
	printf("11. Trocar colaborador responsavel por atividade.\n");
	printf("0. Sair.\n\n");

    do{
        printf("Escolha uma opcao: ");
        int escolha = ler_int();
        if(escolha==0){
           printf("Saindo....");
           break;
        }   
        else if(escolha==1){
			printf("\n+-------------------------------------------------------+\n");
            printf("|               CADASTRO DE COLABORADOR(ES)                 |\n");
            printf("+-------------------------------------------------------+\n");
            // Pede o nome e o codigo de cada colaborador 
            do{
                char nome[100];
                char codigo[6];
                
                getchar();
                printf("\nNome do colaborador: ");
                while(ler_string(nome, 100)); strcpy(pessoa[p].nome, nome);
               
                printf("Codigo identificador: ");
                while(ler_string(codigo, 6)); strcpy(pessoa[p].codigo, codigo);
                p++;
                
                if(encerrar())break;//vai solicitar nova entrada ate que a funcao retorne 0, ou seja, nao tenha erros.
           
            }while(1);
        }
        else if(escolha==2){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                LISTA DE COLABORADOR(ES)                 |\n");
            printf("+-------------------------------------------------------+\n");
              
            if(p==0){
                printf("Nenhum colaborador cadastrado.\n");
            } else {
                for(j = 0; j < p; j++){
                    printf("%d - %s\n", j+1, pessoa[j].nome);//Lista o nome dos cadastrados
                }
            }
        }
        
        else if(escolha==3){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  CADASTRAR ATIVIDADE(S)                  |\n");
            printf("+-------------------------------------------------------+\n");
         
         
          do{  
            char nome_tarefa[100];
            char nome[100];
            
            getchar();
            printf("Nome do colaborador: ");
            while(ler_string(nome, 100)); strcpy(pessoa[p].nome, nome);
           
            printf("Tarefa: ");
            while(ler_string(nome_tarefa, 100)); strcpy(pessoa[t].tarefa, nome_tarefa);
            t++;
            
            if(encerrar())break;
         
          }while(1);
      
        }
        else if(escolha==4){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  LISTAR ATIVIDADE(S)                  |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==5){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                  MOVIMENTAR ATIVIDADE(S)                 |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==6){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                   BUSCAR ATIVIDADE(S)                    |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==7){
            printf("\n+-------------------------------------------------------+\n");
            printf("|               MOSTRAR ESTATISTICAS GERAIS             |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==8){
            printf("\n+-------------------------------------------------------+\n");
            printf("|               RANKING DE COLABORADORES                |\n");
            printf("+-------------------------------------------------------+\n");
        }
        
        else if(escolha==9){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                    EXCLUIR ATIVIDADE                  |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==10){
            printf("\n+-------------------------------------------------------+\n");
            printf("|                    EDITAR ATIVIDADE                   |\n");
            printf("+-------------------------------------------------------+\n");
        }
        else if(escolha==11){
            printf("\n+-------------------------------------------------------+\n");
            printf("|      TROCAR COLABORADOR RESPONSAVEL POR ATIVIDADE     |\n");
            printf("+-------------------------------------------------------+\n");
        }
        
        else printf("\nNumero invalido.\n");

    }while(1);
}
