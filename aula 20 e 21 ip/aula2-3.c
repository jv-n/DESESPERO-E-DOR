#include <stdio.h>

typedef struct {
    int parteInt;
    float parteReal;
} IntReal;

int main() {
    
    FILE *meuArq;
    IntReal num;
    if((meuArq = fopen("/Users/joao_/Desktop/teste5.bin", "r")) != NULL) {
        
        fseek(meuArq, sizeof(IntReal), SEEK_SET);
        fread(&num, // Ponteiro para o dado que você deseja gravar
               sizeof(IntReal), // Quantos bytes ocupa um bloco do que você quer gravar (4 bytes)
               1, // Quantidade de elementos a gravar (Vetor)
               meuArq);
        //for (int i = 0; i<2; i++)
        //{
            printf("vet = %d e %.1f\n", num.parteInt, num.parteReal);
        //}
        fclose(meuArq);
        printf("CERTINHOS");
    } else printf("DEU MERDA");
    return 0;
}