#include <stdio.h>

void CarregarArquivo(FILE *arquivo, long int *posicao) {
    
    char string[300];
    char ch;
    int i = 0;

    fscanf(arquivo, "%[^\n]", string);
    ch = fgetc(arquivo);
    posicao[i] = ftell(arquivo);
    i++;

    while(1){
        fscanf(arquivo, "%[^\n]", string);
        ch = fgetc(arquivo);
        if(ch == EOF){
            break;
        }

        posicao[i] = ftell(arquivo);

        printf("bytes: %d - linha: %d\n", posicao[i], i);
        printf("%s\n", string);
        i++;
    }
 
}