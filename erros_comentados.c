#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[30];
    char cpf[12];
    int qtdNumeros=0; //nao se inicializa um int dentro de struct
    char** numeros;
} Pessoa;

//cabecalho da funcao
int main ()
{
    Pessoa* usuario; //vetor deve ser inicializado como NULL
    int qtdPessoas = 0, resposta; //= qlqr inteiro
    
    while(resposta!=0){//resposta precisa ser inicializada nesse caso
        printf("Aperte 1 para adicionar um usuário e 0 para sair do programa\n");
        scanf("%d", &resposta);
        if(resposta!=0 || resposta!=1) printf("Escolha uma opcao valida\n"); //uso errado de condicional, resposta deve ser diferente de ambos ao mesmo tempo (usa &&)
        else if(resposta==1)
            addPessoa(usuario, qtdPessoas); // uso implicito de addPessoa
            //qtdPessoas deve aumentar em +1
    }
    
    free(usuario);
    return 0;
}

void addPessoa(Pessoa *user, int qtdPessoas)
{
    user = (Pessoa*) realloc(user, (qtdPessoas+1)*sizeof(Pessoa));
    if(user==NULL) printf("Erro!!");
    
    printf("\n\n--- Dados do novo usuário ----\n\n");
    printf("Digite o nome e o cpf:\n");
    scanf("%s%s", user[qtdPessoas].nome, user[qtdPessoas].cpf);
    printf("Quantos telefones essa pessoa tem?\n");
    scanf("%d", user[qtdPessoas].qtdNumeros); //falta um & antes de user[qtdPessoas].qtdNumeros
    
    int qtd = user[qtdPessoas].qtdNumeros;
    user[qtdPessoas].numeros = (Pessoa*) realloc(user[qtdPessoas].numeros, qtd*sizeof(Pessoa)); //numeros é do tipo char** nao Pessoa*
    // falta uma verificação de falha de realocação e +1 realloc para a linha de numeros (vetor)
    
    printf("Digite os numeros:\n");
    int i=0;
    while(i<qtd){
        scanf("%s", user[qtdPessoas].numeros[i]);
        i++;
    }

}

