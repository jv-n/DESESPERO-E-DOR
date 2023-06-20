#include <stdio.h>

int main() {
    
    FILE *meuArq;
    int vet[5];
    if((meuArq = fopen("/Users/joao_/Desktop/teste3.bin", "r")) != NULL) {
        
        fread(vet, // Ponteiro para o dado que você deseja gravar
               sizeof(int), // Quantos bytes ocupa um bloco do que você quer gravar (4 bytes)
               5, // Quantidade de elementos a gravar (Vetor)
               meuArq); // Ponteiro do arquivo (Manipulador do arquivo)
        for(int i=0; i<5; i++)
        {
            printf("Li vet[%d] = %d\n", i+1, vet[i]);
        }
        fclose(meuArq);
        //printf("TUDO NUMA BAO");
        
    }else printf("NADA BEM");

    return 0;
}