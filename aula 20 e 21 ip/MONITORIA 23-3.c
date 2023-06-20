#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char filename[50] = "nomes.txt";
    /*printf("Qual o nome do seu arquivo, meu bom?: ");
    scanf(" %s", filename);
    strcat(filename, ".txt");*/

    FILE* arquivo;
    char nome[50];
    int i = 0;

    if((arquivo = fopen(filename, "a+"))!= NULL)
    {
        do{
            printf("Digite um nome: ");
            scanf(" %49[^\n]", nome);
            if(nome[0]!='.')
            {
                fprintf(arquivo, "%s\n", nome);
                i++;
            }
        }while(nome[0]!='.');

        rewind(arquivo);

        while (fscanf(arquivo, " %49[^\n]\n", nome)!=EOF)
        {
            printf("%s IS MARKED FOR ELIMINATION\n", nome);
        }

        fclose(arquivo);

    } else
    {
        printf("Ih mane"); 
        exit(1);
    }

    return 0;
}