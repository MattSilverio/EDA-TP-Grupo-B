#include <stdio.h>
#include <time.h>

typedef struct {
    int airlineId;
    char airlineName[3];
    int flights;    
    int delayedFlights;
    double average;
} AIRLINE;

void selectionsort(AIRLINE *v, int t);

int main() {

    clock_t inicioT = clock();

    FILE *data, *saida;

    char ch, header[67], airline[3], dst[3], ori[3];
    int id, delay, flightId, day, time, length;

    int airlineQtt = 0;
    AIRLINE airlines[18];

    for(int i = 0; i < 18; i++){
        airlines[i].airlineId = 0;
        airlines[i].flights = 0;
        airlines[i].delayedFlights = 0;
    }

    data = fopen("Airlines.csv", "r");
    saida = fopen("saida.csv", "w");

    fscanf(data, "%s", header);

    while(1){

        fscanf(data, "%d,%2[^,],%d,%3[^,],%3[^,],%d,%d,%d,%d", &id, airline, &flightId, ori, dst, &day, &time, &length, &delay);
        id = (airline[0] + airline[1]) * (airline[0] / 2);
        //printf("airlineID %d airlineName %s delayed? %d\n", id, airline, delay);
        
        for(int i = 0; i < 18; i++){
            if(airlines[i].airlineId != 0){
                if(airlines[i].airlineId == id){
                    break;
                }
            } else {
                airlines[i].airlineId = id;
                airlineQtt++;
                strcpy(airlines[i].airlineName, airline);
                //printf("id: %d airline: %s\n", airlines[i].airlineId, airline);
                break;
            }
        }

        for(int i = 0; i < 18; i++){
            if(airlines[i].airlineId == 0){
                break;
            }

            if(airlines[i].airlineId == id){
                airlines[i].flights++;
                if(delay == 1){
                    airlines[i].delayedFlights++;
                }
            }
        }

        ch = fgetc(data);
        if(ch == EOF){
            break;
        }

    }

    clock_t inicioM = clock();

    for(int i = 0; i < 18; i++){
        airlines[i].average = (double) airlines[i].delayedFlights / airlines[i].flights;
        printf("Airline: %s => Flights: %5.d | Delayed: %5.d | Average: %g\n", airlines[i].airlineName, airlines[i].flights, airlines[i].delayedFlights, airlines[i].average);
    }

    clock_t fimM = clock();

    clock_t inicioSS = clock();

    selectionsort(airlines, 18);
    printf("\n");

    clock_t fimSS = clock();

    for(int i = 0; i < 18; i++){
        fprintf(saida, "%s,%f\n", airlines[i].airlineName, airlines[i].average);
    }

    for(int i = 0; i < 18; i++){
        printf("Airline: %s => Flights: %5.d | Delayed: %5.d | Average: %g\n", airlines[i].airlineName, airlines[i].flights, airlines[i].delayedFlights, airlines[i].average);
    }

    fclose(saida);
    fclose(data);
    
    clock_t fimT = clock();

    double tempoT = (double) (fimT - inicioT) / CLOCKS_PER_SEC;
    double tempoM = (double) (fimM - inicioM) / CLOCKS_PER_SEC;
    double tempoSS = (double) (fimSS - inicioSS) / CLOCKS_PER_SEC;

    printf("\nTempo de execução: %fs\nTempo de média: %fs\nTempo de sort: %fs\n",tempoT, tempoM, tempoSS);

    return 0;
}

void selectionsort(AIRLINE v[], int tam){
    int i, j, indice;
    double min;
    AIRLINE tmp;

    for(i = 0; i<tam-1; ++i){

        min = v[i].average; indice = i;

        for(j=i+1; j<tam; ++j){
            if(v[j].average < min){
                min = v[j].average;
                indice = j;
            }
        }
        tmp = v[i];
        v[i] = v[indice];
        v[indice] = tmp;
    }
}