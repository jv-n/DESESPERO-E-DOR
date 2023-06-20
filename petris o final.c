#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int val;
    struct node *next;
} node;

typedef struct lista{
    struct node *pilha;
    struct lista *next;
} lista;

node* stacktop(node** new, node** cur)
{
    (*new)->next = (*cur);
    (*cur) = (*new);
    return (*cur);
}

node* stackpop(node** cur)
{
    (*cur) = (*cur)->next;
    return (*cur);
}

node* stackcopy(node** cur_source, node** cur_dest)
{
    (*cur_dest) = (*cur_source); 
    return (*cur_dest);
}

lista* list_new_insert(node** new, lista** cur_lista)
{
    node* head_pilha;
    head_pilha = (node*) malloc(sizeof(node));
    head_pilha->next = NULL;

    node* cur_pilha = head_pilha;
    stacktop(&new, &cur_pilha);

    cur_pilha->next = (*cur_lista)->next;
    (*cur_lista)->next = cur_pilha;

    return (*cur_lista);
}

lista* list_delete (lista** cur_lista)
{
    lista* pointer;
    pointer = (*cur_lista)->next;
    (*cur_lista)->next = pointer->next;
    free(pointer);
    return (*cur_lista);
}

void pilha_ops(lista** cur_lista, node** new, int* j)
{
    if((*cur_lista)->pilha->val!=(*new)->val)
    {
        stacktop(&new, &(*cur_lista)->pilha);
    } else if((*cur_lista)->pilha->next != NULL && (*cur_lista)->pilha->val == (*new)->val)
    {
        stackpop(&(*cur_lista)->pilha);
        if((*cur_lista)->pilha->next == NULL)
        {
            (*j)--;
            list_delete (&cur_lista);
        }
    }
}

int main()
{
    char controle[5] = "GO";
    int partidas;

    lista* head;
    head = (lista*) malloc(sizeof(lista));   //lista de pilhas
    head->next = NULL;

    scanf("%d\n", &partidas);
    
    int i = 0;
    int j = 0;
    int x;

    while(i<partidas)
    {
        lista* cur_lista = head;
        strcpy(controle, "GO");
        j = 0; //numero de pilhas na partida
        while(strcmp(controle, "END")!= 0)
        {
            scanf(" %4[^\n]", controle);
            node* new = (node*) malloc(sizeof(node));
            
            if(strcmp(controle, "END")!= 0)
            {
                x = atoi(controle);
                char* aux = strstr(controle, " ");
                new->val = atoi(aux);

                if(x==j+1)
                {
                    j++;
                   list_new_insert(&new, &cur_lista);  
                }
                else if(x==0)
                {
                    j++;
                }
                else if (x<j && x>0)
                {
                    cur_lista = head;
                    int k = 0;
                    while(k<x)
                    {
                        cur_lista->next++;
                        k++;
                    }
                    pilha_ops(&cur_lista, &new, &j);
                    while(cur_lista->next!=NULL) cur_lista->next++;
                }
            }
            if(strcmp(controle, "END") == 0)
            {
                printf("caso %d:", i);
                if(cur_lista!=NULL)
                {
                    cur_lista = head->next;
                    while(cur_lista->next!=NULL)
                    {
                        printf(" %d", cur_lista->pilha->val);
                        cur_lista->next++;
                    }
                    printf("\n");
                    free(cur_lista);
                } else printf("\n");
            }
        }

        i++;
    }


    
    return 0;
}