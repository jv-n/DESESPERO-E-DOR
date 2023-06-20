#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{

    char funcao[4];
    int i = 0;
    int idrmv;
    int** mat = NULL;

    while(strcmp(funcao, "END")!=0) // enquanto o usuario não determinar o fim
    {
        scanf(" %s", funcao); // le a string que vai determinar o que o usuario deseja
        if(strcmp(funcao, "NEW") == 0) // o usuario quer alocar um item
        {
            i++;
            mat = (int**) realloc(mat, i*sizeof(int*)); //aloca i linhas a matriz
            mat[i-1] = NULL;
            mat[i-1] = (int*) realloc(mat[i-1], 3*sizeof(int)); // aloca 3 colunas a matriz
            for(int j = 0; j<3; j++)
            {
                scanf("%d", &mat[i-1][j]); // le os 3 elementos (id, qtd e preco) do item e adiciona a matriz
            }
        }

        if(strcmp(funcao, "RM") == 0) // o usuario quer remover um item
        {
            scanf("%d", &idrmv); //o usuario escolhe qual item vai querer remover;
            for(int k = 0; k<i; k++)
            {
                if(mat[k][0] == idrmv) //proucura o item removido;
                {
                    for(int j = 0; j<3; j++)
                    {
                        mat[k][j] = mat[i-1][j];
                    }
                    free(mat[i-1]);
                    i--; // zera o item removido
                }
            }
        }
    }
    
    int flag = 0;
    int temp;

    do{ //bubble sort para ordenar a matriz
        flag = 0;
        for(int k = 1; k<i; k++)
        {
            if(mat[k][0]<mat[k-1][0])
            {
                for(int j = 0; j<3; j++){
                    temp = mat[k][j];
                    mat[k][j] = mat[k-1][j];
                    mat[k-1][j] = temp;
                }
                flag = 1; 
            }
        }
        
    }while(flag == 1);

    printf("\nID\tQTD\tPRECO\n");

    for(int j = 0; j<i; j++)
    {
        for (int k = 0; k<3; k++)
        {
            if(mat[j][0] != 0)// nao imprime itens removidos
            {
                printf("%d\t", mat[j][k]);//imprime a matriz "nota fiscal"
            }
        }
        printf("\n");
    }

    for(int j = 0; j<i; j++)
    {
        free(mat[j]); //libera a matriz
    }
    
    free(mat);

    return 0;
}