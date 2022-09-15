#include <stdio.h>

void CarregarArquivo(FILE *arquivo) {
    
    char string[300];
    char ch;
    int i = 1;

    fscanf(arquivo, "%[^\n]", string);
    ch = fgetc(arquivo);

    while(1){
        fscanf(arquivo, "%[^\n]", string);
        ch = fgetc(arquivo);
        if(ch == EOF){
            break;
        }

        printf(string);
        printf("\n");

    }
 
}