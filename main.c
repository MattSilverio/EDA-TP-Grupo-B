#include <stdio.h>
#include "lib/CarregarArquivo.c"
#include "lib/EmitirRelatorio.c"
#include "lib/FecharAplicacao.c"

int main(){

    char opcao, nomeArquivo[50];
    FILE *arquivo = NULL;

    while(opcao != '3'){

        printf("\n1 - Carregar Arquivo de Dados\n");
        printf("2 - Emitir Relatório\n");
        printf("3 - Fechar Aplicação\n\n");
        
        scanf("%c", &opcao);
        getchar();

        switch(opcao){
            case '1':

                printf("\nInforme o nome do arquivo:");
                scanf("%s", nomeArquivo);
                getchar();

                arquivo = fopen(nomeArquivo, "r");
                if(arquivo == NULL){
                    printf("Ocorreu um erro na abertura do arquivo, tente novamente\n\n");
                    break;
                }

                CarregarArquivo(arquivo);
                fclose(arquivo);
                arquivo = NULL;

                break;

            case '2':

                if(arquivo == NULL){
                    printf("\nArquivo Vazio!!!\n\n");
                    break;
                }

                EmitirRelatorio();
                break;
                
            case '3':
                
                FecharAplicacao();
                break;
        }
    }   

    return 0;
}
