#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    int cpf[11];
}pessoa;


int main()
{
    FILE* arquivo;
    pessoa* id;
    
    if((arquivo = fopen("file.bin", "a+"))!= NULL)
    {
        do{
            printf("Digite um nome e cpf ");
            scanf(" %49[^\n]", id.nome);
            if(id.nome[0]!='.')
            {
                printf("Digite o CPF de %s: ", id.nome);
                for(int i = 0; i<11; i++)
                {
                    scanf("%d", &id.cpf[i]);
                }
                fwrite(&id, sizeof(pessoa), 1, arquivo);
            }
        }while(id.nome[0]!='.');

        rewind(arquivo);

        fclose(arquivo);

    } else
    {
        printf("Ih mane"); 
        exit(1);
    }
}