#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[51];
    float nota;
    float credito;
}cadeira;


int main()
{
    cadeira* PERIODO = NULL;
    char nomet[50];
    int indice = 0;

    while(strcmp("fim", nomet) != 0)
    {   
        printf("Qual a cadeira: \n");
        scanf(" %50[^\n]", nomet);
    
        if(strcmp("fim", nomet) != 0)
        {
            indice++;
            PERIODO = (cadeira*) realloc(PERIODO, sizeof(cadeira)*indice);
            strcpy(PERIODO[indice-1].nome, nomet);
            printf("Digite a media de %s nesse periodo: \n", PERIODO[indice-1].nome);
            scanf("%f", &PERIODO[indice-1].nota);
            printf("Digite o credito de %s: \n", PERIODO[indice-1].nome);
            scanf("%f", &PERIODO[indice-1].credito);
        }

    }

    float soma = 0;
    float divisor = 0;

    for(int i = 0; i<indice; i++)
    {
        soma+=(PERIODO[i].credito*PERIODO[i].nota);
        divisor+=PERIODO[i].credito;
    }

    float CR = soma/divisor;

    printf("seu CR e: %.2f\n", CR);
    if(CR>7)
    {
        printf("Voce pode realizar mobilidade academica nesse periodo");
    } else printf("Voce NAO pode realizar mobilidade academica nesse periodo");
    
    return 0;
}