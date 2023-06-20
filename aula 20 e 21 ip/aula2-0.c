#include <stdio.h>

int main() {
    FILE *meuArq;
    int num;
    float f1;
    if((meuArq = fopen("C:/Users/joao_/Desktop/teste1.bin", "r")) != NULL) {
        
        fread(&num, // Ponteiro para o dado que você deseja gravar
               sizeof(int), // Quantos bytes ocupa um bloco do que você quer gravar (4 bytes)
               1, // Quantidade de elementos a gravar (Vetor)
               meuArq); // Ponteiro do arquivo (Manipulador do arquivo)
        printf("LI %d\n", num);
        fread(&f1, // Ponteiro para o dado que você deseja gravar
               sizeof(float), // Quantos bytes ocupa um bloco do que você quer gravar (4 bytes)
               1, // Quantidade de elementos a gravar (Vetor)
               meuArq);
        printf("LI %.1f\n", f1);
        fclose(meuArq);
        //printf("TUDO NUMA BOA");
    } else printf("NAO FOI POSSIVEL LER");

    return 0;
}
