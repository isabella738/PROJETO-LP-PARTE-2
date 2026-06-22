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



int main(){

    printf("teste: ");
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

    return 0;
}