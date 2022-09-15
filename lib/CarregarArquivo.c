#include <stdio.h>
#include <string.h>

void CarregarArquivo(FILE *arquivo, long int *posicao) {
    
    char reino[25], filo[25], classe[25], ordem[25], familia[25], genero[25], especie[150];
    char *chave;
    char string[300];
    char ch;
    int i = 1, linha;

    fscanf(arquivo, "%[^\n]", string);

    while(1){

        posicao[i] = ftell(arquivo);

        fscanf(arquivo, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
               &linha, reino, filo, classe, ordem, familia, genero, especie);
        
        ch = fgetc(arquivo);
        if(ch == EOF){
            break;
        }

        i++;

        chave = strcat(reino, filo);
        chave = strcat(chave, classe);

        printf("%s\n", chave);
        printf("bytes: %d - linha: %d\n", posicao[i], i);
    }
 
}