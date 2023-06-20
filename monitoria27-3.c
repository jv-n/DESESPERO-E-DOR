#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    char casa[100];
    int golscasa;
    char visitante[100];
    int golsvisitante;
} partida;

typedef struct{
    char nome[50];
    int pts;
    int pj;
    int vit;
    int emp;
    int derrota;
    int golspro;
    int golscontra;
    int saldogols;
} tabela;

void carregaPartidas(partida** partidas, int* tam)
{
    
    FILE* meuArq;
    partida vet;
    char* aux;
    char num1[5], num2[5];
    char linha[105];

    if((meuArq = fopen("partidas.txt", "r")) != NULL)
    {   
       while(!feof(meuArq))
       {
            fscanf(meuArq, "%100[^\n]\n", linha);
            aux = strstr(linha, "X");
            int j = 0;
            
            while((linha[j]<'0')||(linha[j]>'9')) j++;

            strncpy(vet.casa, linha, j-1);
            vet.casa[j-1]='\0';
            
            int k = 0;

            while(linha[j]!='\0'){
                num1[k] = linha[j];
                j++; k++;
            }
            num1[k] = '\0';
            vet.golscasa = atoi(num1);

            k = 0;
            aux+= 2;
            
            while(aux[k]!=' ')
            {
                num2[k] = aux[k];
                k++;
            }
            
            num2[k] = '\0';
            vet.golsvisitante = atoi(num2);
            k++;
            aux+=k;
            strcpy(vet.visitante, aux);

            (*tam)++;
            (*partidas) = (partida*) realloc((*partidas), (*tam)*sizeof(partida));
            (*partidas)[(*tam)-1] = vet;

            printf("%s", (*partidas)[(*tam)-1].casa);
        }
        
        fclose(meuArq);
        printf("ARQUIVO CARREGADO\n");
    }
    else printf("FALHA AO ABRIR\n");
}

void gerarTabela(partida* partidas, int tam)
{
    tabela* time = NULL;
    int qtdtimes = 0;
    int flag1, flag2;
    for(int i = 0; i<tam; i++)
    {
        flag1 = 0; flag2 = 0;
        for(int k = 0; k<qtdtimes; k++)
        {
            if((strcmp(partidas[i].casa, time[k].nome)) == 0)
            {
                flag1 = 1;
                time[k].pj++;
                time[k].golspro+= partidas[i].golscasa;
                time[k].golscontra+= partidas[i].golsvisitante;
                time[k].saldogols = time[k].golspro - time[k].golscontra;
                if(partidas[i].golscasa>partidas[i].golsvisitante)
                {
                    time[k].pts+=3;
                    time[k].vit++;
                }
                if(partidas[i].golscasa<partidas[i].golsvisitante)
                {
                    time[k].derrota++;
                }
                if(partidas[i].golscasa==partidas[i].golsvisitante)
                {
                    time[k].pts++;
                    time[k].emp++;
                }
            }
            if((strcmp(partidas[i].visitante, time[k].nome)) == 0)
            {
                flag2 = 1;
                time[k].pj++;
                time[k].golspro += partidas[i].golsvisitante;
                time[k].golscontra+= partidas[i].golscasa;
                time[k].saldogols = time[k].golspro - time[k].golscontra;

                if(partidas[i].golscasa<partidas[i].golsvisitante)
                {
                    time[k].pts+=3;
                    time[k].vit++;                    
                }
                if(partidas[i].golscasa>partidas[i].golsvisitante)
                {
                    time[k].derrota++;
                }
                if(partidas[i].golscasa==partidas[i].golsvisitante)
                {
                    time[k].pts++;
                    time[k].emp++;
                }
            }
        }
        if(flag1 == 0)
        {
            qtdtimes++;
            time = (tabela*) realloc(time, qtdtimes*sizeof(tabela));
            strcpy(time[qtdtimes-1].nome, partidas[i].casa);
            time[qtdtimes-1].pj = 1;
            time[qtdtimes-1].golspro = partidas[i].golscasa;
            time[qtdtimes-1].golscontra = partidas[i].golsvisitante;
            time[qtdtimes-1].saldogols = time[qtdtimes-1].golspro - time[qtdtimes-1].golscontra;

            if(partidas[i].golscasa>partidas[i].golsvisitante)
            {
                time[qtdtimes-1].pts = 3;
                time[qtdtimes-1].vit = 1;
            }
            if(partidas[i].golscasa<partidas[i].golsvisitante)
            {
                time[qtdtimes-1].pts = 0;
                time[qtdtimes-1].derrota = 1;
            }
            if(partidas[i].golscasa==partidas[i].golsvisitante)
            {
                time[qtdtimes-1].pts = 1;
                time[qtdtimes-1].emp = 1;
            }
        }
        if(flag2 == 0)
        {
            qtdtimes++;
            time = (tabela*) realloc(time, qtdtimes*sizeof(tabela));
            strcpy(time[qtdtimes-1].nome, partidas[i].visitante);
            time[qtdtimes-1].pj = 1;
            time[qtdtimes-1].golspro = partidas[i].golsvisitante;
            time[qtdtimes-1].golscontra = partidas[i].golscasa;
            time[qtdtimes-1].saldogols = time[qtdtimes-1].golspro - time[qtdtimes-1].golscontra;

            if(partidas[i].golsvisitante>partidas[i].golscasa)
            {
                time[qtdtimes-1].vit = 1;
                time[qtdtimes-1].pts = 3;
            }
            if(partidas[i].golscasa<partidas[i].golsvisitante)
            {
                time[qtdtimes-1].pts = 0;
                time[qtdtimes-1].pj = 1;
                time[qtdtimes-1].derrota = 1;
            }
            if(partidas[i].golscasa==partidas[i].golsvisitante)
            {
                time[qtdtimes-1].pts = 1;
                time[qtdtimes-1].emp = 1;
            }
        }
    }
    int troca = 0;
    tabela temp;
    do
    {
        troca = 0;
        for(int k = 1; k<qtdtimes; k++)
        {
            if(time[k].pts>time[k-1].pts)
            {
                troca = 1;
                temp = time[k-1];
                time[k-1] = time[k];
                time[k] = temp;
            }
            if(time[k].pts == time[k-1].pts)
            {
                if(time[k].saldogols>time[k-1].saldogols)
                {
                    troca = 1;
                    temp = time[k-1];
                    time[k-1] = time[k];
                    time[k] = temp;
                }
            }
        }
    } while (troca!=0);

    for(int k = 0; k<qtdtimes; k++)
    {
        printf("%s %d %d %d %d %d %d %d %d\n", time[k].nome, time[k].pts, time[k].pj, time[k].vit, time[k].emp, time[k].derrota, time[k].golspro, time[k].golscontra, time[k].saldogols);
    }
}

int main()
{
    int option;
    int tam = 0;
    partida* partidas = NULL;
    
    while(option!=3)
    {
        printf("O que queres fazer?\n1...Carregar arquivo\n2...Mostrar a Tabela\n3...Encerrar\n");
        scanf("%d", &option);
        switch(option)
        {
            case 1: carregaPartidas(&partidas, &tam); break;
            case 2: gerarTabela(partidas, tam); break;
            case 3: free(partidas); printf("Encerrado\n"); exit(1); break;
        }
    }

    return 0;
}