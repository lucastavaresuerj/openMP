#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"
#define true 1
#define false 0
#define DEBUG true

int **matriz;
long int l,c;
long int soma1, soma2, soma3, soma4;

int main(int argc, char *argv[]) {
    int i, j;  
    FILE * pfile;
    pfile = fopen(argv[1], "r");
    fscanf(pfile, "%ld %ld", &l, &c);
    matriz = (int**) malloc(l*sizeof(int*));
    printf("l: %ld, c: %ld\n", l, c);
    
    for(i=0; i<l; i++){
        matriz[i] = (int*) malloc(c*sizeof(int));
    }
    for (i=0;i<l;i++) {
        for(j=0;j<c;j++) {
            fscanf(pfile,"%d", &(matriz[i][j]));
        }
    }
    #pragma omp parallel num_threads(1)
    {
        #pragma omp sections private (i,j)
        {
            
            #pragma omp section // cima, esquerda para direita
            {
                for(i=0; i<l; i++){
                    for(j=0;j<c; j++) {
                        soma1 += matriz[i][j]*matriz[i][j];
                    }
                }

            }
            #pragma omp section // cima, direita para esquerda
            {
                for(i=0; i<l; i++){
                    for(j=0;j<c; j++) {
                        soma2 += matriz[i][c-j-1]*matriz[i][c-j-1];
                    }
                }
            }
            
            #pragma omp section // baixo, esquerda para direita
            {
                for(i=0; i<l; i++){
                    for(j=0;j<c; j++) {
                        soma3 += matriz[l-i-1][j]*matriz[l-i-1][j];
                    }
                }
            }
                     
            #pragma omp section // baixo, direita para esquerda 
            {
                for(i=0; i<l; i++){
                    for(j=0;j<c; j++) {
                        soma4 += matriz[l-i-1][c-j-1]*matriz[l-i-1][c-j-1];
                    }
                }
            }
            
        }
    }
    
    printf("s1 %ld, s2 %ld, s3 %ld, s4 %ld\n", soma1, soma2, soma3, soma4);
}