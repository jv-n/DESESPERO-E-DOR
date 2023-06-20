#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    float pReal;
    float pImag;

}Complexo;

void empilhe(Complexo **cPilha, Complexo umC, int *tPilha)
{
    (*tPilha)++;
    (*cPilha) = (Complexo*) realloc((*cPilha), (*tPilha)*sizeof(Complexo));
    if((*cPilha) == NULL) 
    {
        printf("Erro de Alocação\n"); 
        free(*cPilha); 
        exit(1);
    }
    (*cPilha)[(*tPilha)-1] = umC;
    printf("%.1f %.1fi empilhados\n",umC.pReal, umC.pImag);
}

Complexo desempilhe(Complexo **cPilha, int *tPilha)
{
    Complexo topo;
    if((*tPilha)!=0)
    {
        (*tPilha)--;
        topo = (*cPilha)[(*tPilha)];
        (*cPilha) = (Complexo*) realloc ((*cPilha), (*tPilha)*sizeof(Complexo));
        if((*cPilha) == NULL && ((*tPilha)!=0))
        {
            printf("ERRO DE ALOCACAO\n");
        }
    }
    else 
    {
        topo.pImag = 0; topo.pReal = 0;
    }
    return topo;
}

Complexo topo(Complexo **cPilha, int tPilha)
{
    Complexo top;
    if((*cPilha)!=NULL){
    top = (*cPilha)[tPilha-1];
    }
    else 
    {
        top.pImag = 0; 
        top.pReal = 0;
    }
    return top;
}

int pilhaVazia(Complexo *cPilha, int tPilha)
{
    int schrodinger = 0;
    if((cPilha == NULL) || tPilha == 0 )
    {
        schrodinger = 1;
    }
    
    return schrodinger;
}
void salvePilha(Complexo* cPilha, int tPilha)
{
    FILE* arq;
    arq = fopen("pilha.bin", "w");
    if (arq == NULL) printf("ERRO AO ABRIR\n");

    fwrite(&tPilha, sizeof(int), 1, arq);
    fwrite(cPilha, sizeof(Complexo), tPilha, arq);
    fclose(arq);
    printf("deu tudo ok!\n");
}

Complexo* recuperaPilha(int *tPilha)
{
    FILE* arq;
    Complexo* read = NULL;
    arq = fopen("pilha.bin", "r");
    if (arq == NULL) printf("ERRO AO ABRIR O ARQUIVO\n");

    fread(tPilha, sizeof(int), 1, arq);

    read = (Complexo*) malloc((*tPilha)*sizeof(Complexo));
    if(read == NULL) 
    {
        printf("Erro de Alocação"); 
        free(read); 
        exit(1);
    }
    
    fread(read, sizeof(Complexo), *tPilha, arq);

    fclose(arq);

    return read;
}

int main()
{
    Complexo* cPilha = NULL;
    Complexo* recuperado = NULL;
    Complexo umC;
    int tPilha = 0;
    int opcao = 1;
    Complexo retorno;

    while(opcao != 0){
        
        printf("ESCOLHA SUA OPCAO:\n1...Empilhe um imag\n2...Desempilhe um imag\n3...Quem eh seu Topo\n4...Checar se esta vazia\n5...Salve a pilha\n6...Recupere a pilha\n7...ENCERROU\n");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1: printf("digite seu complexo: "); scanf("%f %f", &umC.pReal, &umC.pImag); empilhe(&cPilha, umC, &tPilha); break;
            case 2: retorno = desempilhe(&cPilha, &tPilha); if(retorno.pImag!=0 && retorno.pReal!=0) printf("%.1f %.1fi foram tirados\n", retorno.pReal, retorno.pImag); else printf("Nao da pra desempilhar\n"); break;
            case 3: retorno = topo(&cPilha, tPilha); if(retorno.pImag!=0 && retorno.pReal!=0) printf("%.1f %.1fi esta no topo\n", retorno.pReal, retorno.pImag); else printf("Sua pilha esta vazia, nao ha topo\n"); break;
            case 4: if(pilhaVazia(cPilha, tPilha)) printf("Tudo certo com a pilha inicial\n"); else printf("TEMO CONTEUDO\n"); break;
            case 5: salvePilha(cPilha, tPilha); break;
            case 6: recuperado = recuperaPilha(&tPilha); if(cPilha!=NULL) printf("Pilha recuperada!\n"); else printf("ERRO AO RECUPERAR!!!\n"); break;
            case 7: printf("TCHAU TCHAU\n"); free(cPilha); exit(1); break;
            case 9: if((topo(&cPilha, tPilha).pImag == topo(&recuperado, tPilha).pImag) && (topo(&cPilha, tPilha).pReal == topo(&recuperado, tPilha).pReal) ) printf("Iguais\n"); else printf("Diferentes\n"); break;
            default: printf("Opcao Invalida!!!\n "); break;
        }
    }

    return 0;
}