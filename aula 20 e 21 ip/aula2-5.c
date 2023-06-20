#include <stdio.h>
#include <stdlib.h>

int main()
{

    FILE*meuArq;
    int* vet = NULL;
    int i = 0;
    if((meuArq = fopen("/Users/joao_/Desktop/vetor.bin", "r")) != NULL)
    {
        fread(&i, sizeof(int), 1, meuArq);
        vet = (int*) realloc (vet, sizeof(int)*i);
        if(vet == NULL)
        {
            exit(1);
        }
        fread(vet, sizeof(int), i, meuArq);
        for(int k = 0; k<i; k++)
        {
            printf("vet[%d] = %d\n", k+1, vet[k]);
        }
        fclose(meuArq);
        free(vet);
    }
    return 0;
}