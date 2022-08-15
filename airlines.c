#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>




struct al{
    char nome[3];
    int atraso;
};

typedef struct al airline;

void selectionsort(airline v[], int tam);


int main(void){

    FILE *f;
    f = fopen("teste.txt", "r");
    char s[20];
    int i, j, k;
    int lin, col, conta_cias;
    airline *airlines;
    char ch1, ch2;

    int matriz[36][36];

    for(i=0; i<36; i++)
        for(j=0; j<36; j++)
            matriz[i][j] = -1;



    fscanf(f, "%s", s);
    while(fscanf(f, "%s", s) != EOF){
        //fscanf(f, "%s", s);
        //puts(s);
        for(i=0; s[i] != ','; ++i);


        if(isalpha(s[i+1]))
            lin = s[i+1] - 'A';
        else
            lin = s[i+1] - '0' + 26;

        if(isalpha(s[i+2]))
            col = s[i+2] - 'A';
        else
            col = s[i+2] - '0' + 26;

        //printf("\n\n%d %d\n\n", lin,col);



        if(matriz[lin][col] == -1){
            if(s[i+4] == '0')
                matriz[lin][col] = 0;
            else{
                matriz[lin][col] = 1;
            }
        }
        else
            matriz[lin][col] += s[i+4] - '0';

    }
    fclose(f);




/*
    for(i=0; i<36; i++){
        for(j=0; j<36; j++)
            printf("%d ", matriz[i][j]);
        putchar('\n');
    }
*/
    conta_cias = 0;

    for(i=0; i<36; i++)
        for(j=0; j<36; j++)
            if(matriz[i][j] != -1)
                conta_cias++;

    airlines = (airline*) malloc(sizeof(airline) * conta_cias);

    k = 0;
    for(i=0; i<36; i++)
        for(j=0; j<36; j++){
            if(matriz[i][j] != -1){
                airlines[k].atraso = matriz[i][j];

                if(i >= 0 && i <= 25)
                    ch1 = i + 'A';
                else
                    ch1 = i - 26 + '0';

                if(j >= 0 && j <= 25)
                    ch2 = j + 'A';
                else
                    ch2 = j - 26 + '0';


                /*putchar(ch1);
                putchar(ch2);*/

                airlines[k].nome[0] = ch1;
                airlines[k].nome[1] = ch2;
                airlines[k].nome[2] = '\0';

                k++;
            }
        }


        //printf("cias: %d\n", conta_cias);
        for(i=0; i< conta_cias; i++){
            printf("%s, atrasos: %d\n", airlines[i].nome, airlines[i].atraso);
        }

        selectionsort(airlines, conta_cias);


        
        putchar('\n');
        for(i=0; i< conta_cias; i++){
            printf("%s, atrasos: %d\n", airlines[i].nome, airlines[i].atraso);

        }






    //puts(s);

    return 0;
}





void selectionsort(airline v[], int tam){
    int i, j, indice, min;
    airline tmp;

    for(i = 0; i<tam-1; ++i){

        min = v[i].atraso; indice = i;

        for(j=i+1; j<tam; ++j){
            if(v[j].atraso < min){
                min = v[j].atraso;
                indice = j;
            }
        }
        tmp = v[i];
        v[i] = v[indice];
        v[indice] = tmp;
    }
}
