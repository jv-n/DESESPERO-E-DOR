#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int valor;
    int estado;

} Jazigo;

typedef struct 
{
    Jazigo* jazigos;
    int ocupados;

} Cemiterio;

int hash(int id, int andar);
void add(Cemiterio cemiterio[], int k, int j, int id);
//int remove(int** cemiterio, int andar, int jazigo);
//int qry(int** cemiterio, int andar, int jazigo);
void sort(Cemiterio cemiterio[], int k, int inicio, int fim);


int main()
{
    int andar = 13; 
    int jazigo = 0;
    int id;
    int andares_cheios = 0;
    char input[11] = "GO";

    scanf("%d %d", &andar, &jazigo);

    Cemiterio* cemiterio = (Cemiterio*) malloc(andar*sizeof(Cemiterio));

    for(int j = 0; j<andar; j++)
    {
        cemiterio[j].ocupados = 0;
        cemiterio[j].jazigos = (Jazigo*) malloc(jazigo*sizeof(Jazigo));
        for(int m = 0; m<jazigo; m++)
        {
            cemiterio[j].jazigos[m].valor = 0;
            cemiterio[j].jazigos[m].estado = 0;
        }
    }

    while(strcmp(input, "END")!=0)
    {
        scanf(" %10[^\n]", input);

        if(strcmp(input, "END")!=0)
        {
            int i = 0;
            char function[4];
            strncpy(function, input, 4);
            char* aux = strstr(input, " ");
            id = atoi(aux);

            if(strcmp(function, "ADD") == 0)
            {
                int k = hash(id, andar);
                andares_cheios = 0;
                while(cemiterio[k].ocupados == jazigo)
                {
                    andares_cheios++;
                    if(andares_cheios == andar)
                    {
                        int* temp = (int*) malloc((andar*jazigo)*sizeof(int));
                        int val = 0;
                        for(int a = 0; a<andar; a++)
                        {
                            for(int b = 0; b<jazigo; b++)
                            {
                                if(cemiterio[a].jazigos[b].estado != 2 && cemiterio[a].jazigos[b].estado!= 0)
                                {
                                    temp[val] = cemiterio[a].jazigos[b].valor;
                                    val++;
                                }
                            }
                        }
                        andar = (2*andar)+1;
                        cemiterio = (Cemiterio*) malloc(cemiterio, andar*sizeof(Cemiterio));
                        for(int j = 0; j<andar; j++)
                        {
                            cemiterio[j].ocupados = 0;
                            cemiterio[j].jazigos = (Jazigo*) malloc(jazigo*sizeof(Jazigo));
                            for(int m = 0; m<jazigo; m++)
                            {
                                cemiterio[j].jazigos[m].valor = 0;
                                cemiterio[j].jazigos[m].estado = 0;
                            }
                        }

                        for(int j = 0; j<val; j++)
                        {
                            int l = hash(temp[j], andar);
                            while(cemiterio[l].ocupados == jazigo)
                            {
                                l++;
                                l = hash(l, andar);
                            }
                            for(int b = 0; b<jazigo; b++)
                            {
                                if(cemiterio[l].jazigos[b].estado == 0)
                                {
                                    add(cemiterio, l, b, id);
                                    cemiterio[l].ocupados++;
                                    break;
                                }      
                            }
                        }
                    }
                    k++;
                    k = hash(k, andar);
                }

                for(int j = 0; j<jazigo; j++)
                {
                    if(cemiterio[k].jazigos[j].estado == 0)
                    {
                        add(cemiterio, k, j, id);
                        cemiterio[k].ocupados++;
                        break;
                    }                    
                }
                
            }
            else if(strcmp(function, "REM") == 0)
            {
                //binary search and print
            }
            else if(strcmp(function, "QRY") == 0)
            {
                //binary search and print
            }         
        }

    }

    return 0;
}

int hash(int id, int andar)
{
    int key;
    key = id%andar;
    return key;
}

void sort(Cemiterio cemiterio[], int k, int inicio, int fim)
{
    if(fim - inicio>1)
    {
        int pivot = partition(cemiterio, k, inicio, fim);
        sort(cemiterio, k, inicio, pivot);
        sort(cemiterio, k, (pivot+1), fim);
    }
}

void add(Cemiterio cemiterio[], int k, int j, int id)
{
    cemiterio[k].jazigos[j].valor = id;
    cemiterio[k].jazigos[j].estado = 1;
    sort(cemiterio, k, 0, j);
}

int partition(Cemiterio cemiterio[], int k, int inicio, int fim)
{
    int p = (inicio + fim)/2;
    int temp =  cemiterio[k].jazigos[p].valor;
    cemiterio[k].jazigos[p].valor = cemiterio[k].jazigos[inicio].valor;
    cemiterio[k].jazigos[inicio].valor = temp;
    int i = inicio; int j = fim-1;
    while(i<=j)
    {
        while(i<fim && cemiterio[k].jazigos[i].valor<=cemiterio[k].jazigos[inicio].valor)
        {
            i++;
        }
        while(cemiterio[k].jazigos[j].valor>cemiterio[k].jazigos[inicio].valor)
        {
            j--;
        }
        if(i<j)
        {
            int temp2 =  cemiterio[k].jazigos[i].valor;
            cemiterio[k].jazigos[i].valor = cemiterio[k].jazigos[j].valor;
            cemiterio[k].jazigos[j].valor = temp;
        }
    }
    return j;
}

