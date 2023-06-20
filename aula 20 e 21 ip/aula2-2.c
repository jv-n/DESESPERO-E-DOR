#include <stdio.h>

typedef struct {
    int parteInt;
    float parteReal;
} IntReal;

int main() {
    
    FILE *meuArq;
    IntReal num[] = {{ 125, 345.56}, {54, 123.33}};
    if((meuArq = fopen("/Users/joao_/Desktop/teste5.bin", "r")) != NULL) {
        
        fread(num, // Ponteiro para o dado que você deseja gravar
               sizeof(IntReal), // Quantos bytes ocupa um bloco do que você quer gravar (4 bytes)
               2, // Quantidade de elementos a gravar (Vetor)
               meuArq);
        for (int i = 0; i<2; i++)
        {
            printf("vet[%d] = %d e %.1f\n", i+1, num[i].parteInt, num[i].parteReal);
        }
        fclose(meuArq);
    } else printf("DEU MERDA");
    return 0;
}