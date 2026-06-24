#include <stdio.h>
#include <string.h>


void reorganizacao_crescente(int v[]){
    //Proposta: reorganizar os termos de um vetor em forma crescente de dado valor
    int limite=0;

    for(int k=1; k<=3; k++){
        for(int i=0; i<10; i++){
            if(v[i]==k){
                if(limite!=i){
                    int x = v[i];
                    v[i] = v[limite];
                    v[limite] = x;
                    limite++;
                    i = limite;
                }
                else limite++;
            }
        }
    }

}

int encerrar(){ //return 1=parar processo atual; return 0=continuar
	printf("Continuar? (S/N) ");
	char c;
    scanf(" %c", &c);
	if(c=='n' || c=='N')return 1;
	return 0;
}

void ranking(int v[]){
    //Proposta: imprimir, em ordem, os 5 maiores valores de um vetor
    int usados[5], u=0;
    for(int ranking=1; ranking<=5; ranking++){
        int maior=0, posicao=0;
        for(int i=0; i<10; i++){//para cada elemento do vetor

            if(v[i]>maior){
                int parar=0;
                for(int j=0; j<u; j++){
                    if(i==usados[j]){parar=1; break;}
                }
                if(!parar){
                    maior = v[i]; posicao=i;
                }
            }

        }
        usados[u]=posicao; u++;
        printf("%d. '%d'\n", ranking+1, v[posicao]);
    }
}

void teste_validacao_codigo(){
    //Proposta: verificar se os digitos sao apenas numeros e se o codigo tem 5 digitos
    char codigo[15];
    int valido = 1;
    
    printf("Digite um codigo de um colaborador (5 digitos): ");
    scanf("%s", codigo);
    
    int tamanho_real = strlen(codigo); //verifica o tamanho
    int i = 0;
    
    for(i = 0; i < tamanho_real; i++) {
        if(codigo[i] < '0' || codigo[i] > '9'){ // consulta a tabela ASCII
            valido = 0;
            break; //se achar uma letra, encerra
        }
    }
    
    if (!valido){
        printf("Erro: O codigo deve conter apenas numeros. Tente novamente.\n");
    }else if (tamanho_real != 5){
        printf("Erro: O codigo contem apenas numeros, mas tambem deve ter 5 digitos.\n");
    }else{
        printf("Codigo \"%s\" valido para o sistema.\n", codigo);
    }
}

int main(){
	//menu de testes
    printf("Teste 1: Reorganizacao crescente\n");
    printf("Teste 2: Encerrar\n");
    printf("Teste 3: Ranking\n");
    printf("Teste 1: Reorganizao crescente\n");
    printf("\n> ");
    int n; scanf("%d", &n);

    if(n==1){
        int v[10];
        printf("Numeros aleatorios de 1 a 3:\n");
        for(int i=0; i<10; i++){
            printf("%d: ", i+1); scanf("%d", &v[i]);
        }
        reorganizacao_crescente(v); printf("\n");
        for(int i=0; i<10; i++)printf("%d. %d\n", i+1, v[i]);
    }
    if(n==2){
        int x = encerrar();
        if(x)printf("Programa encerrado\n");
        else printf("Continuar programa\n");
    }
    if(n==3){
        int v[10];
        printf("Numeros aleatorios (10):\n");
        for(int i=0; i<10; i++){
            printf("%d: ", i+1); scanf("%d", &v[i]);
        }
        printf("\n");
        ranking(v);
    }

	if(n==4){
        teste_validacao_codigo();
    }

    return 0;
}
