//#ifndef ARVORE_H
//define ARVORE_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


struct _node{
    int pos;
    char chave[51];
    struct _node * lt;
    struct _node * rt;
};

typedef struct _node * Node;


void showTree(Node root);
Node CarregarArquivo(FILE *arquivo, long int *posicao);
Node newNode(void);
void destrucNode(Node node);
void setNode(int pos, char chave[], Node node);
char* getChave(Node node);
Node insertNode(int pos, char chave[], Node root);
void freeTree(Node node);


char reino[25], filo[25], classe[25], ordem[25], familia[25], genero[25], especie[150];

void EmitirRelatorio(FILE *f, long int *posicao, Node arvore) {


    char s[301];
    int linha;

    if(arvore->lt != NULL)
        EmitirRelatorio(f, posicao, arvore->lt);


    fseek(f, posicao[arvore->pos], SEEK_SET);
    fscanf(f, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           &linha, reino, filo, classe, ordem, familia, genero, especie);

    printf("linha: %d, reino %s, filo %s, classe %s, ordem %s, familia %s, genero %s, especie %s\n",
        linha, reino, filo, classe, ordem, familia, genero, especie);


    if(arvore->rt != NULL)
        EmitirRelatorio(f, posicao, arvore->rt);

}


    Node CarregarArquivo(FILE *arquivo, long int *posicao) {

    char reino[25], filo[25], classe[25], ordem[25], familia[25], genero[25], especie[150];
    char *chave;
    char string[300];
    char ch;
    int i = 1, linha;
    Node arvore;

    fscanf(arquivo, "%[^\n]", string);

    arvore = newNode();
    if(arvore == NULL)
        return NULL;


    // leitura da primeira linha de registro e criacao da raiz da arvore
    posicao[1] = ftell(arquivo);

    fscanf(arquivo, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           &linha, reino, filo, classe, ordem, familia, genero, especie);

    chave = strcat(reino, filo);
    chave = strcat(chave, classe);

    setNode(i, chave, arvore);

    i++;

    ch = fgetc(arquivo);
    if(ch == EOF){
        return arvore;
    }


    while(1){

        posicao[i] = ftell(arquivo);

        fscanf(arquivo, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
               &linha, reino, filo, classe, ordem, familia, genero, especie);

        ch = fgetc(arquivo);
        if(ch == EOF){
            break;
        }

        chave = strcat(reino, filo);
        chave = strcat(chave, classe);

        insertNode(i, chave, arvore);

        i++;
    }

    return arvore;
}






Node newNode(void){
    Node node = malloc(sizeof(struct _node));
    if(node == NULL)
        return NULL;

    node->chave[0] = '\0';
    node->lt = node->rt = NULL;
    return node;
}


void destrucNode(Node node){
    free(node);
}

void setNode(int pos, char chave[], Node node){
    strcpy(node->chave, chave);
    node->pos = pos;
}

char* getChave(Node node){
    return node->chave;
}

Node insertNode(int pos, char chave[], Node root){
    Node node;
    if(root == NULL){
        node = newNode();
        setNode(pos, chave, node);
        return node;
    }

    // strcmp
    if(strcmp(chave, getChave(root)) < 0){
        if(root->lt == NULL){
            node = newNode();
            setNode(pos, chave, node);
            root->lt = node;
            return node;
        }
        else
            return insertNode(pos, chave, root->lt);
    }
    else{
        if(root->rt == NULL){
            node = newNode();
            setNode(pos, chave, node);
            root->rt = node;
            return node;
        }
        else
            return insertNode(pos, chave, root->rt);
    }
}

void showTree(Node root){

    if(root->lt != NULL)
        showTree(root->lt);

    printf("%d %s \n", root->pos, getChave(root));

    if(root->rt != NULL)
        showTree(root->rt);
}


void freeTree(Node node){
    if(node == NULL)
        return;

    if(node->lt != NULL)
        freeTree(node->lt);

    if(node->rt != NULL)
        freeTree(node->rt);
    free(node);
}


int main(){

    char opcao, nomeArquivo[50];
    FILE *arquivo = NULL;
    long int posicao[962];
    Node arvore = NULL;


    while(opcao != '3'){

        printf("\n1 - Carregar Arquivo de Dados\n");
        printf("2 - Emitir Relatório\n");
        printf("3 - Fechar Aplicação\n\n");

        scanf("%c", &opcao);
        getchar();

        switch(opcao){
            case '1':
                freeTree(arvore);
                printf("\nInforme o nome do arquivo:");
                scanf("%s", nomeArquivo);
                getchar();

                arquivo = fopen(nomeArquivo, "r");
                if(arquivo == NULL){
                    printf("Ocorreu um erro na abertura do arquivo, tente novamente\n\n");
                    break;
                }

                arvore = CarregarArquivo(arquivo, posicao);
                break;

            case '2':
                if(arquivo == NULL){
                    printf("\nArquivo Vazio!!!\n\n");
                    break;
                }

                EmitirRelatorio(arquivo, posicao, arvore);
                break;

            case '3':
                if(arquivo != NULL)
                    fclose(arquivo);
                freeTree(arvore);
                return 0;
        }
    }

    return 0;
}
