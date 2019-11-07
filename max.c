#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#define N 100000000

int main() {
    long max_val = 0;
    long i;
    long* vet;
    int T = 4;
    double inicio, fim, fim2, tempo1, tempo2;
    GET_TIME(inicio);
    vet = (long*) malloc(N * sizeof(long));
    #pragma omp parallel for num_threads(T)
    for(i=0; i<N; i++) {
        vet[i] = i;
    }
    vet[100] = 299999999;
    GET_TIME(fim);
    #pragma omp parallel for reduction(max:max_val) num_threads(T) 
    for(i=0;i<N;i++) {
        if(vet[i] > max_val) {
            max_val = vet[i];
        }
    }
    GET_TIME(fim2);
    tempo1 = fim - inicio;
    tempo2 = fim2 -inicio - tempo1;
    printf("\ntempo1: %lf\n",tempo1);
    printf("\ntempo2: %lf\n",tempo2);
    printf("\ntempo total: %lf\n",tempo2+tempo1);
    printf("\nmax_val = %ld\n", max_val);
}