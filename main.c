#include <stdio.h>
#include "lib/CarregarArquivo.c"
#include "lib/EmitirRelatorio.c"
#include "lib/FecharAplicação.c"


int main(){

    char opcao;

    while(opcao != '3'){

        printf("\n\n1 - Carregar Arquivo de Dados\n");
        printf("2 - Emitir Relatório\n");
        printf("3 - Sair da Aplicação\n\n");
        
        scanf("%c", &opcao);
        getchar();

        switch(opcao){
            case '1':
                CarregarArquivo();
                break;

            case '2':
                EmitirRelatorio();
                break;
                
            case '3':
                FecharAplicacao();
                break;
        }
    }   

    return 0;
}