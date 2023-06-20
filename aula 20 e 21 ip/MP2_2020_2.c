#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{

    char remetente[50];
    char assunto[50];
    char mensagem[200];

} Email;

typedef struct{

    char nome[50];
    char senha[50];
    int qtdRecebidos, qtdEnviados;
    Email *recebidos;
    Email *enviados;

} Usuario;


void cadastrarUsuario(Usuario** usuarios, int *qtd, char *name, char *passw);
void login(Usuario * usuarios, int qtd);
void enviarEmail(char *nomeRemetente, Usuario* usuarios, int qtd);
void verRecebidos(Usuario usuario);
void verEnviados(Usuario usuario);


int main ()
{
    int qtdUsuarios = 0;
    int opcao = -1;
    char nome[50], senha[50];
    Usuario* users = NULL;
    do{
        printf("\n\n----MENU----\n\n");
        printf("1...Cadastrar\n2...Fazer Login\n3...Sair do sistema\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:

            printf("\nDigite o nome do novo usuario: ");
            scanf(" %49[^\n]", nome);
            printf("\nDigite a senha: ");
            scanf(" %49[^\n]", senha);


            cadastrarUsuario(&users, &qtdUsuarios, nome, senha);
            break;
        case 2:

            login(users, qtdUsuarios);
            break;
        case 3:
            break;
        default:
            printf("Opcao invalida. Digite novamente\n");
        }
    } while(opcao!=3);

    for(int i=0; i<qtdUsuarios; i++){
        free(users[i].enviados);
        free(users[i].recebidos);
    }
    free(users);
    return 0;
}

void cadastrarUsuario(Usuario** usuarios, int *qtd, char *name, char *passw)
{
    Usuario* tmp = NULL;
    tmp = (Usuario*) realloc(*usuarios, (*qtd+1)*sizeof(Usuario));

    if(tmp==NULL){
        for(int i=0; i<*qtd; i++){
            free((*usuarios)[i].enviados);
            free((*usuarios)[i].recebidos);
        }
        free(*usuarios);
        printf("Erro alocando memoria\n");
        exit (1);
    }

    (*usuarios) = tmp; //usuarios = &users --> *usuarios = users

    strcpy((*usuarios)[*qtd].nome, name);
    strcpy((*usuarios)[*qtd].senha, passw);

    FILE* arquivo;
    if((arquivo = fopen("users.txt", "a+"))!= NULL)
    {
        fprintf(arquivo, "%s %s\n", (*usuarios)[*qtd].nome, (*usuarios)[*qtd].senha);
    }

    (*usuarios)[*qtd].enviados = NULL;
    (*usuarios)[*qtd].recebidos = NULL;
    (*usuarios)[*qtd].qtdEnviados=0;
    (*usuarios)[*qtd].qtdRecebidos=0;
    (*qtd)++;

    printf("\nUsuario Cadastrado!\n");

}

void login(Usuario *usuarios, int qtd)
{
    int flag = 1, i, index;
    char nome[50], senha[50];
 
    do{
        printf("\nlogin: ");
        scanf(" %49[^\n]", nome);
        printf("\nsenha: ");
        scanf(" %49[^\n]", senha);

        for(i=0; i<qtd && flag; i++){
            if(strcmp(usuarios[i].nome,nome)==0 && strcmp(usuarios[i].senha,senha)==0){
                flag = 0;
                index = i;
            }
        }

        if(flag) printf("\nNome e/ou senha incorretos\nDigite dados validos\n");

    }while(flag);

    printf("\nLogin realizado com sucesso! Digite o que voce quer fazer:");

    int opcao;
    do{
        printf("\n\n1...Enviar email\n2...Ver recebidos\n3...Ver enviados\n4...Sair da conta\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            enviarEmail(nome, usuarios, qtd);
            break;
        case 2:
            verRecebidos(usuarios[index]);
            break;
        case 3:
            verEnviados(usuarios[index]);
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida. Digite novamente\n");
        }
    }while(opcao!=4);

}

void enviarEmail(char *nomeRemetente, Usuario* usuarios, int qtd)
{

    Email novo;
    int iRemet, iDest;
    char destinatario[50];
    strcpy(novo.remetente, nomeRemetente);

    printf("\nDigite o nome do destinatario: ");
    scanf(" %49[^\n]", destinatario);

    printf("\nDigite o assunto: ");
    scanf(" %49[^\n]", novo.assunto);

    printf("\nDigite a mensagem: ");
    scanf(" %199[^\n]", novo.mensagem);

    for(int i=0; i<qtd; i++){
        if(strcmp(usuarios[i].nome, nomeRemetente)==0)
            iRemet = i;
        if(strcmp(usuarios[i].nome,destinatario)==0)
            iDest = i;
    }

    Email* tmp = NULL;
    tmp = realloc(usuarios[iRemet].enviados, (usuarios[iRemet].qtdEnviados+1)*sizeof(Email));

    if(tmp==NULL){
        for(int i=0; i<qtd; i++){
            free(usuarios[i].enviados);
            free(usuarios[i].recebidos);
        }
        free(usuarios);
        printf("Erro na alocacao");
        exit (1);
    }

    usuarios[iRemet].enviados = tmp;
    usuarios[iRemet].enviados[usuarios[iRemet].qtdEnviados] = novo;
    usuarios[iRemet].qtdEnviados++;

    tmp = NULL;
    tmp = realloc(usuarios[iDest].recebidos, (usuarios[iDest].qtdRecebidos+1)*sizeof(Email));
    if(tmp==NULL){
        for(int i=0; i<qtd; i++){
            free(usuarios[i].enviados);
            free(usuarios[i].recebidos);
        }
        free(usuarios);
        printf("Erro na alocacao");
        exit (1);
    }

    usuarios[iDest].recebidos = tmp;
    usuarios[iDest].recebidos[usuarios[iDest].qtdRecebidos] = novo;
    usuarios[iDest].qtdRecebidos++;

}

void verRecebidos(Usuario usuario)
{
    int i = 0;

    if(usuario.qtdRecebidos==0){
        printf("\nSem emails recebidos");
        return;
    }

    i=0;
    while(i != usuario.qtdRecebidos){
        printf("\n\nRemetente: %s", usuario.recebidos[i].remetente);
        printf("\nAssunto: %s", usuario.recebidos[i].assunto);
        printf("\nMensagem: %s", usuario.recebidos[i].mensagem);
        i++;
    }
}

void verEnviados(Usuario usuario)
{
    int i = 0;

    if(usuario.qtdEnviados==0){
        printf("\nSem emails enviados");
        return;
    }

    i=0;
    while(i != usuario.qtdEnviados){
        printf("\n\nRemetente: %s", usuario.enviados[i].remetente);
        printf("\nAssunto: %s", usuario.enviados[i].assunto);
        printf("\nMensagem: %s", usuario.enviados[i].mensagem);
        i++;
    }
}