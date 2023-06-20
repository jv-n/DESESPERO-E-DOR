#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void carregaVotos(int* qtdVotos, char*** votos)
{
    FILE *arq;
    char voto [11];
    arq = fopen("votos.txt", "r");
    int digitos = 0;
    if(arq == NULL) 
    {
        printf("Nao foi possivel computar votos\n"); exit(1);
    }
    while (!feof(arq))
    {
        fscanf(arq, "%10[^\n]\n", voto);
        digitos = strlen (voto);
        (*qtdVotos)++;
        (*votos) = (char**) realloc ((*votos), (*qtdVotos)*sizeof(char*));
        (*votos)[(*qtdVotos) - 1] = (char*) malloc(digitos*sizeof(char));
        strcpy((*votos)[(*qtdVotos) - 1], voto);
    }
    fclose(arq);
}

int main()
{
    char** votos = NULL;
    int qtdVotos = 0;

    carregaVotos(&qtdVotos, &votos);

    for(int i = 0; i<qtdVotos; i++)
    {
        int k = strlen(votos[i]);

        for (int j = 0; j<k; j++)
        {
            printf("%c", votos[i][j]);
        }
        //     if(votos[i][j] == '0')
        //     {

        //     }
        //     if(votos[i][j] == '1')
        //     {

        //     }
        //     if(votos[i][j] == '2')
        //     {

        //     }
        //     if(votos[i][j] == '3')
        //     {

        //     }
        //     if(votos[i][j] == '4')
        //     {

        //     }
        //     if(votos[i][j] == '5')
        //     {

        //     }
        //     if(votos[i][j] == '6')
        //     {

        //     }
        //     if(votos[i][j] == '7')
        //     {

        //     }
        //     if(votos[i][j] == '8')
        //     {

        //     }
        //     if(votos[i][j] == '9')
        //     {

        //     }
        // }
        printf("\n");
        //codigo do botão confirma;
    }
    return 0;
}