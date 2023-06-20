#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *arquivo;
    char nome[100];
    if((arquivo = fopen("nomes.txt", "w+"))!=NULL)
    {
        do{
            printf("Digite um nome: ");
            scanf(" %99[^\n]", nome);
            if(nome[0]!='.')
            {
                fprintf(arquivo, "%s\n", nome);
            }
        }while(nome[0]!='.');

        fclose(arquivo);
        printf("Tudo tranquilo meu chapa");
    }
    else printf("DEU MERDA MANE");
    return 0;
}