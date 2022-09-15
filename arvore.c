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

void setNode(int pos char chave[], Node node){
    strcpy(root->chave, chave);
    root->pos = pos;
}

char* getNode(Node node){
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
    if(info < getNode(root)){
        if(root->lt == NULL){
            node = newNode();
            setNode(info, node);
            root->lt = node;
            return node;
        }
        else
            return insertNode(info, root->lt);
    }
    else{
        if(root->rt == NULL){
            node = newNode();
            setNode(info, node);
            root->rt = node;
            return node;
        }
        else
            return insertNode(info, root->rt);
    }
}

void showTree(Node root){

    if(root->lt != NULL)
        showTree(root->lt);

    printf("%d ", getNode(root));

    if(root->rt != NULL)
        showTree(root->rt);
}


int main(void){

    Node tree = newNode();
    setNode(5, tree);

    insertNode(2, tree);
    insertNode(-6, tree);
    insertNode(4, tree);

    showTree(tree);

    return 0;
}
