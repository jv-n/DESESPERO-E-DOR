#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nome[100];
    int pts, pj, vit, emp, der, gp, gc, sg;
}Time;

typedef struct{
    char time_de_casa[100];
    char visitante[100];
    int gols_de_casa;
    int gols_visitante;
} Partida;

void carregarPartidas(Partida **partidas, int *total_partidas){
    FILE *arq;
    char nome_arquivo[100] = "partidas.txt";
    arq = fopen(nome_arquivo, "r");
    if(arq==NULL) printf("erro ao abrir o arquivo\n");

    char linha[105];//String com uma linha inteira do arquivo
    char num1[5], num2[5]; //Strings com o numero de gols
    char *ponteiro_aux; //Vamos armazenar a string até o X nesse ponteiro de caracter

    Partida partida_atual;

    while(!feof(arq)){

        fscanf(arq, "%100[^\n]\n",linha);
        ponteiro_aux = strstr(linha, "X"); //Esse ponteiro aponta para a posição onde X está
        int cont=0;
        while((linha[cont]<'0')||(linha[cont]>'9')) cont++; //Ao final do while, cont armazena a posição onde tem a quantidade de gols

        strncpy(partida_atual.time_de_casa, linha, cont-1); //Ele vai colocar o nome do time da casa como sendo a string do primeiro time (tudo até chegar um número)
        partida_atual.time_de_casa[cont-1]='\0';
        
        int i = 0;
        while(linha[cont]!='\0'){
            num1[i] = linha[cont];
            cont++; i++;
        }
        num1[i] = '\0';
        partida_atual.gols_de_casa = atoi(num1); //atoi aceita um ponteiro de char (o que pode ser uma string) e transforma em int
        
        
        ponteiro_aux += 2; //ele vai pra posição onde tem a quantidade de gols do vistante (X 'numero', por isso que somei mais dois)
        i=0;
        while(ponteiro_aux[i]!=' '){
            num2[i] = ponteiro_aux[i];
            i++;
        }
        num2[i]='\0';
        partida_atual.gols_visitante = atoi(num2);
        i++; //i estava no espaço entre o numero de gols do visitante e o nome do time, então somando 1 a ele vamos para a posição da primeira letra do visitante


        ponteiro_aux+=i;
        strcpy(partida_atual.visitante, ponteiro_aux);

        //passamos o vetor de partidas como ponteiro duplo, então para acessar o ponteiro em si precisamos fazer *partidas
        (*total_partidas)++;
        (*partidas) = (Partida *) realloc((*partidas), (*total_partidas)*sizeof(Partida));
        (*partidas)[(*total_partidas)-1] = partida_atual;
    }
    fclose(arq);//Não se esqueçam de usar o fclose depois que para de ler os dados!!!!!
}

void geraTabela(Partida *partidas, int totalPartidas){
    Time *tabela=NULL;
    int qtd_times=0, flagCasa, flagVisitante;

    for(int i=0;i<totalPartidas;i++){
        flagCasa=0;//Essa flag vai indicar se o time da casa já existia na tabela ou não
        flagVisitante=0;//Essa flag vai indicar se o time visitante já existia na tabela ou não

        for(int j=0;j<qtd_times;j++){
            if(strcmp(partidas[i].time_de_casa, tabela[j].nome)==0){ //Testa se o time da casa já tinha sido adicionado na tabela antes e atualiza os valores
                tabela[j].gc += partidas[i].gols_de_casa;
                tabela[j].sg += partidas[i].gols_visitante;
                tabela[j].gp = tabela[j].gc + tabela[j].sg;
                tabela[j].pj++;

                if(partidas[i].gols_de_casa>partidas[i].gols_visitante){
                    tabela[j].vit++;
                    tabela[j].pts+=3;
                }
                else if(partidas[i].gols_de_casa==partidas[i].gols_visitante){
                    tabela[j].emp++;
                    tabela[j].pts+=1;
                } 
                else if(partidas[i].gols_de_casa<partidas[i].gols_visitante) tabela[j].der++;
                flagCasa=1; //Quer dizer que o time já tinha sido adicionado à tabela anteriormente
            }
            if(strcmp(partidas[i].visitante, tabela[j].nome)==0){//Testa se o time visitante já tinha sido adicionado na tabela antes e atualiza os valores
                tabela[j].gc += partidas[i].gols_visitante;
                tabela[j].sg += partidas[i].gols_de_casa;
                tabela[j].gp = tabela[j].gc + tabela[j].sg;
                tabela[j].pj++;

                if(partidas[i].gols_visitante>partidas[i].gols_de_casa){
                    tabela[j].vit++;
                    tabela[j].pts+=3;
                }
                else if(partidas[i].gols_visitante==partidas[i].gols_de_casa){
                    tabela[j].emp++;
                    tabela[j].pts+=1;
                } 
                else if(partidas[i].gols_visitante<partidas[i].gols_de_casa) tabela[j].der++;
                flagVisitante=1; //Quer dizer que o time já tinha sido adicionado à tabela anteriormente
            }
        }

        Time atual;
        if(flagCasa==0){
            strcpy(atual.nome, partidas[i].time_de_casa);
            atual.pj=1;
            atual.gc = partidas[i].gols_de_casa;
            atual.sg = partidas[i].gols_visitante;
            atual.gp = atual.gc + atual.sg;
            if(partidas[i].gols_de_casa>partidas[i].gols_visitante){
                atual.vit=1;
                atual.pts=3;
            }
            else if(partidas[i].gols_de_casa==partidas[i].gols_visitante){
                atual.emp=1;
                atual.pts=1;
            } 
            else if(partidas[i].gols_de_casa<partidas[i].gols_visitante){
                atual.der=1;
                atual.pts=0;
            }
            qtd_times++;
            tabela = (Time *) realloc(tabela, qtd_times*(sizeof(Time)));
            tabela[qtd_times-1] = atual;
        }
        if(flagVisitante==0){
            strcpy(atual.nome, partidas[i].visitante);
            atual.pj=1;
            atual.gc = partidas[i].gols_visitante;
            atual.sg = partidas[i].gols_de_casa;
            atual.gp = atual.gc + atual.sg;
            if(partidas[i].gols_visitante>partidas[i].gols_de_casa){
                atual.vit=1;
                atual.emp=0;
                atual.der=0;
                atual.pts=3;
            }
            else if(partidas[i].gols_visitante==partidas[i].gols_de_casa){
                atual.emp=1;
                atual.der=0;
                atual.vit=0;
                atual.pts=1;
            } 
            else if(partidas[i].gols_visitante<partidas[i].gols_de_casa){
                atual.der=1;
                atual.vit=0;
                atual.emp=0;
                atual.pts=0;
            }
            qtd_times++;
            tabela = (Time *) realloc(tabela, qtd_times*(sizeof(Time)));
            tabela[qtd_times-1] = atual;
        }
    } //Aqui acabamos de somar todos os times na tabela

    //Bubble sort
    Time temp;
    for(int i=0;i<qtd_times-1;i++){
        for(int j=1;j<qtd_times;j++){
            if(tabela[j].pts>tabela[j-1].pts){
                temp = tabela[j];
                tabela[j] = tabela[j-1];
                tabela[j-1] = temp;
            }
            if(tabela[j].pts==tabela[j-1].pts){//Caso os pontos sejam iguais
                if(tabela[j].gc>tabela[j-1].gc){//Comparamos por quantidade de gols feitos
                    temp = tabela[j];
                    tabela[j] = tabela[j-1];
                    tabela[j-1] = temp;
                }
            }
        }
    }

    for(int i=0;i<qtd_times;i++){
        printf("%s %d %d %d %d %d %d %d %d\n", tabela[i].nome, tabela[i].pts, tabela[i].pj, tabela[i].vit, tabela[i].emp, tabela[i].der, tabela[i].gp, tabela[i]. gc, tabela[i].sg);
    }
}

int main(){
    int total_partidas=0, flag=0, comando, leitura=0;
    Partida *partidas = NULL; //vetor que vai armazenar todas as partidas e temos que inicializar ele como NULL para usar o realloc posteriormente

    while(flag==0){
        printf("Escolha uma opção:\n");
        printf("1. Carregar partidas\n2. Imprimir tabelas\n3. Sair\n");
        scanf("%d", &comando);

        switch(comando){
            case 1:
                if(leitura==0){ //Na questão ele diz que a leitura só deve ser feita 1 vez
                    leitura = 1;
                    carregarPartidas(&partidas, &total_partidas);
                }
                break;

            case 2:
                geraTabela(partidas, total_partidas);
                break;

            case 3:
                printf("Saindo do programa, tchauu :)\n");
                flag = 1;
                break;

            default:
                printf("Opção invalida!\nEscolha outra");

        }
    } 
    return 0;
}