#include <stdio.h>
#include <string.h>

int main()
{
    FILE*meuArq;
    char nome[50] = "Joao Victor";
    if((meuArq = fopen("/Users/joao_/Desktop/teste6.bin", "w")) != NULL)
    {
        fwrite(nome, sizeof(char), strlen(nome), meuArq);
        printf("tamanho = %lld\n", strlen(nome));
        fclose(meuArq);
        printf("deu tudo ok!\n");
    } else printf("OQUE HOUVE????\n");

    return 0;
}