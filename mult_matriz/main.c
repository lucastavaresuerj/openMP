#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"

struct matriz {
    long int l;
    long int c;
    float **mat;
};

int main(int argc, char *argv[]) {
    FILE *pfileA, *pfileB, *pfileR;
    long int i,j,k,sum;
    struct matriz matA, matB, matR;
    double inicio, fim;
    GET_TIME(inicio);
    pfileA = fopen(argv[1], "r");
    pfileB = fopen(argv[2], "r");
    pfileR = fopen(argv[3], "w");

    fscanf(pfileA, "%ld %ld", &matA.l, &matA.c);
    matA.mat = (float**) malloc(matA.l*sizeof(float*));
    fscanf(pfileB, "%ld %ld", &matB.l, &matB.c);
    matB.mat = (float**) malloc(matB.l*sizeof(float*));
    matR.mat = (float**) malloc(matA.l*sizeof(float*));

    //#pragma omp parallel for private(i)
    for (i=0;i<matA.l;i++){
        matA.mat[i] = (float*) malloc(matA.c*sizeof(float));
    }
    //#pragma omp parallel for private(i)
    for (i=0;i<matB.l;i++){
        matB.mat[i] = (float*) malloc(matB.c*sizeof(float));
    }
    for (i=0;i<matA.l;i++){
        matR.mat[i] = (float*) calloc(matB.c,sizeof(float));
    }
    
    #pragma omp parallel sections private(i,j)
    {
        #pragma omp section
        {
            for (i=0;i<matA.l;i++) {
                for(j=0;j<matA.c;j++) {
                    fscanf(pfileA,"%f", &(matA.mat[i][j]));
                }
            }
        }
        #pragma omp section
        {
            for (i=0;i<matB.l;i++) {
                for(j=0;j<matB.c;j++) {
                    fscanf(pfileB,"%f", &(matB.mat[i][j]));
                }
            }
        }
    }
    
    #pragma omp parallel for private (i,j,k)
    for (k=0;k<matA.c;k++){
        for(i=0;i<matA.l;i++){
            for(j=0;j<matB.c;j++){
                matR.mat[i][j] += matA.mat[i][k] * matB.mat[k][j];
            }
        }
    }

    
    for(i=0;i<matA.l;i++) {
        for(j=0;j<matB.c;j++) {
            fprintf(pfileR,"%.2f ", matR.mat[i][j]);
        }
        fprintf(pfileR,"\n");
    }
    
    GET_TIME(fim);
    printf("tempo: %.8lf\n", fim-inicio);
}