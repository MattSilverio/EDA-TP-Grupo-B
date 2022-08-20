#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


struct al{
    char nome[3];
    int atraso;
    int total;
    double media;
};

typedef struct al airline;

void selectionsort(airline v[], int tam);
int hash(char ch);
char hash_inverso(int n);

int main(void){

    FILE *f;
    f = fopen("Airlines.csv", "r");
    char s[100];
    int i, j, k;
    int lin, col, conta_cias;
    airline *airlines;
    char ch1, ch2;

    int matriz_atrasos[36][36];
    int matriz_total[36][36];

    for(i=0; i<36; i++)
        for(j=0; j<36; j++){
            matriz_atrasos[i][j] = -1;
            matriz_total[i][j] = 0;
        }


    fscanf(f, "%s", s);
    while(fscanf(f, "%s", s) != EOF){
        //printf(s);
        // encontra a posicao da primeira virgula da linha
        for(i=0; s[i] != ','; ++i);

        lin = hash(s[i+1]);
        col = hash(s[i+2]);

        if(matriz_atrasos[lin][col] == -1){

            //if(s[i+4] == '0')
            if(s[strlen(s)-1] == '0')
                matriz_atrasos[lin][col] = 0;
            else{
                matriz_atrasos[lin][col] = 1;
            }
        }
        else
            matriz_atrasos[lin][col] += s[strlen(s)-1] - '0';

        // contabiliza total de voos da cia
        matriz_total[lin][col]++;

    }
    fclose(f);




/*
    for(i=0; i<36; i++){
        for(j=0; j<36; j++)
            printf("%d ", matriz_total[i][j]);
        putchar('\n');
    }
*/
    conta_cias = 0;

    // contbiliza total de cias
    for(i=0; i<36; i++)
        for(j=0; j<36; j++)
            if(matriz_atrasos[i][j] != -1)
                conta_cias++;

    airlines = (airline*) malloc(sizeof(airline) * conta_cias);

    k = 0;
    for(i=0; i<36; i++)
        for(j=0; j<36; j++){
            if(matriz_atrasos[i][j] != -1){
                airlines[k].atraso = matriz_atrasos[i][j];
                airlines[k].total = matriz_total[i][j];
                airlines[k].media = (double)airlines[k].atraso/airlines[k].total;

                ch1 = hash_inverso(i);
                ch2 = hash_inverso(j);

                airlines[k].nome[0] = ch1;
                airlines[k].nome[1] = ch2;
                airlines[k].nome[2] = '\0';

                k++;
            }
        }

        for(i=0; i< conta_cias; i++){
            printf("%s, atrasos: %d, total: %d, media: %lf\n", airlines[i].nome,
                                                                airlines[i].atraso,
                                                                airlines[i].total,
                                                                airlines[i].media);
        }

        selectionsort(airlines, conta_cias);

        putchar('\n');
        for(i=0; i< conta_cias; i++){
            printf("%s, atrasos: %d, total: %d, media: %lf\n", airlines[i].nome,
                                                                airlines[i].atraso,
                                                                airlines[i].total,
                                                                airlines[i].media);
        }

        f = fopen("saida.csv", "w");
        for(i=0; i< conta_cias; i++)
            fprintf(f, "%s,%lf\n", airlines[i].nome, airlines[i].media);
        fclose(f);



    return 0;
}


void selectionsort(airline v[], int tam){
    int i, j, indice;
    double min;
    airline tmp;

    for(i = 0; i<tam-1; ++i){

        min = v[i].media; indice = i;

        for(j=i+1; j<tam; ++j){
            if(v[j].media < min){
                min = v[j].media;
                indice = j;
            }
        }
        tmp = v[i];
        v[i] = v[indice];
        v[indice] = tmp;
    }
}

int hash(char ch){
    if(isalpha(ch))
        return ch - 'A';
    else
        return ch - '0' + 26;
}

char hash_inverso(int n){
    if(0 <= n && n <= 25)
        return n + 'A';
    else
        return n - 26 + '0';
}
