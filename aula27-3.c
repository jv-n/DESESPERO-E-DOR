#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* carregaPrograma(char *nomArq, int *tam){

    FILE*meuArq;
    char* vet = NULL;
    char i = NULL;

    if((meuArq = fopen(nomArq, "ab+")) != NULL)
    {   
        *tam = (int) ftell(meuArq);
        fseek(meuArq, 0, SEEK_SET);
        if((vet = (char*) malloc(*tam)) == NULL)
        {
            exit(1);
        } else
        fread(vet, sizeof(char), (*tam), meuArq);
        /*while(fread(&i, sizeof(char), 1, meuArq)!=EOF)
        {
            *tam++;
            vet = (char*) realloc (vet, sizeof(char)*(*tam));
            if(vet == NULL)
            {
                exit(1);
            }
            vet[*tam-1] = i;
        }*/
                
        fclose(meuArq);
    }
    return vet;
}
char* read(char* vet, int* tam, int* pc)
{
    vet = (char *) realloc(vet, (*tam)+1);
    (*tam)++;
    scanf("%d", &vet[*tam]);
    (*pc)++;
}
void write(char* vet, int* pc)
{
    printf("%c", vet[vet[(*pc)+1]]);
}
void assign(char* vet, int* tam, int* pc)
{
    if(vet[(*pc)+1] > (*tam) - 1)
    {
        if((vet = (char *) realloc(vet, vet[(*pc)+1])) == NULL)
        {
            exit(1);
        } else *tam = vet[(*pc)+1];
    }
    vet[vet[(*pc)+1]] = vet[(*pc)+2];
    *pc+=3;
}
void acumadd(int *acum, char* vet, int* pc)
{
    *acum = (*acum) + vet[vet[(*pc)+1]];
    *pc+=2;
}

void loadacum(int *acum, char* vet, int* pc)
{
    *acum = vet[vet[(*pc)+1]];
    *pc+=2;
}

void storeacum(int* acum, char* vet, int* pc)
{
    vet[vet[(*pc)+1]] = (*acum);
    *pc+=2;
}

void addvaloracum(int* acum, char* vet, int* pc)
{
    *acum = (*acum) + vet[(*pc)+1];
    *pc+=2;
}

void subposacum(int * acum, char* vet, int* pc)
{
    *acum = vet[vet[(*pc)+1]] - (*acum);
    *pc+=2;
}

void subvaloracum(int* acum, char* vet, int* pc)
{
    *acum = (*acum) - vet[(*pc)+1];
    *pc+=2;
}

void jnz(int acum, char* vet, int* pc)
{
    if(acum>=0)
    {
        *pc = vet[(*pc)+1];
    }
}

char* interpretador (char* vet, int* tam)
{
    int pc = 0; 
    int acum = 0;

    while(vet[pc]!=10) // Final do programa
    {
        switch(vet[pc])
        {
            case 0: vet = read(vet, &tam, &pc); break;
            case 1: write(vet, &pc); break;
            case 2: loadacum(&acum, vet, &pc); break;
            case 3: storeacum(&acum, vet, &pc); break;
            case 4: acumadd(&acum, vet, &pc); break;
            case 5: addvaloracum(&acum, vet, &pc); break;
            case 6: subposacum(&acum, vet, &pc); break;
            case 7: subvaloracum(&acum, vet, &pc); break;
            case 8: jnz(acum, vet, &pc); break;
            case 9: assign(vet, &tam, &pc); break;
            
        }
    }


}


int main()
{

    char* vet = NULL;
    int tam = 0;

    vet = carregaPrograma("prog.bin", &tam);

    vet = interpretador(vet, &tam);

    free(vet);

    return 0;
}