//DONT READ FILE IN PARALLEL, IT IS WAY WORST 
#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"

int main(int argc, char *argv[]) {
    FILE* pfile;
    int T=1;
    long int sizeOfVet, i;
    int* bigVet;
    double tempo, inicio, fim;
    GET_TIME(inicio); 
    pfile = fopen (argv[1],"r");
    fscanf(pfile, "%ld", &sizeOfVet);
    bigVet = (int*) malloc(sizeOfVet*sizeof(int));
    #pragma omp parallel for num_threads(T) private (i)
    for(i=0;i<sizeOfVet;i++) {
        fscanf(pfile, "%d", &(bigVet[i]));
    }
    GET_TIME(fim);
    printf("tempo: %.4lf\n", fim-inicio);
}