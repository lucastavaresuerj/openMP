#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../timer.h"
#define true 1
#define false 0
#define DEBUG true

long int l, c;
long int tamanhoBagagem, passosDados=0, passos, dinheiro;
int **caverna;

long int percorre(int y,int x) {
    int lado = rand() % 4;
    if(passosDados == passos) {
        return 0;
    }
    else {
        
    }
}

int main(int argc, char *argv[]) {
    FILE * pfile;
    long int i, j;
    double inicio, fim;
    GET_TIME(inicio);
    pfile = fopen(argv[1], "r");
    tamanhoBagagem = atoi(argv[2]);
    passos = atoi(argv[3]);
    fscanf(pfile, "%ld %ld", &l, &c);
    caverna = (int**) malloc(l*sizeof(int*));
    srand(time(NULL));
    for(i=0; i<l; i++){
        caverna[i] = (int*) malloc(c*sizeof(int));
    }
    for (i=0;i<l;i++) {
        for(j=0;j<c;j++) {
            fscanf(pfile,"%d", &(caverna[i][j]));
        }
    }
}