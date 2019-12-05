#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"
#define true 1
#define false 0
#define DEBUG true

enum lados {ESQUERDA, CIMA, DIREITA, BAIXO, NENHUM} lado;
long int l, c;
long int tamanhoBagagem, passosDados=0, passos, dinheiro;
int **caverna;

int ladoMaximo(int y, int x){
    enum lados ladoASeguir = NENHUM;
    int maximoArredor = 0;
    if( (y%c != 0) ){ // testa para a ESQUERDA
        if (maximoArredor < caverna[y][x-1]){
            maximoArredor = caverna[y][x-1];
            ladoASeguir = ESQUERDA;
        }
    } 
    if ((y%c != l-1) ){ // testa para a DIREITA
        if (maximoArredor < caverna[y][x+1] ) {
            maximoArredor = caverna[y][x+1];
            ladoASeguir = DIREITA;
        }
    }
    if ((x%l != 0) ){ // testa para CIMA
        if (maximoArredor < caverna[y-1][x] ){
            maximoArredor = caverna[y-1][x-1];
            ladoASeguir = CIMA;
        }
    }
    if ((x%l != c-1) ){ // testa para BAIXO
        if (maximoArredor < caverna[y+1][x] ) {
            maximoArredor = caverna[y+1][x];
            ladoASeguir = BAIXO;
        }
    }
    if(maximoArredor == 0){
        ladoASeguir = NENHUM;
    }
    #if DEBUG
        printf("lado maximo: %d -  redor: %d ", ladoASeguir, maximoArredor);
    #endif
    return ladoASeguir;
}

long int percorre(int y, int x){
    int contaLados, coleta;
    enum lados proxLd;
    if(passosDados == passos) {
        return 0;
    }
    else{
        for(contaLados = 0; contaLados<4; contaLados++){
            proxLd = ladoMaximo(y, x);
            #if DEBUG
                printf("proxLd: %d - ", proxLd);
            #endif
            switch (proxLd) {
                case ESQUERDA:
                    passosDados++;
                    #if DEBUG
                        printf("tesouro: %d\n", caverna[y][x-1]);
                    #endif
                    coleta = caverna[y][x-1];
                    caverna[y][x-1] = 0;
                    return coleta + percorre(y, x+1);
                break;
                case CIMA:
                    passosDados++;
                    #if DEBUG
                        printf("tesouro: %d\n", caverna[y+1][x]);
                    #endif
                    coleta = caverna[y+1][x];
                    caverna[y+1][x] = 0;
                    return coleta + percorre(y+1,x);
                break;
                case DIREITA:
                    passosDados++;
                    #if DEBUG
                        printf("tesouro: %d\n", caverna[y][x+1]);
                    #endif
                    coleta = caverna[y][x+1];
                    caverna[y][x+1] = 0;
                    return coleta + percorre(y,x-1);
                break;
                case BAIXO:
                    passosDados++;
                    #if DEBUG
                        printf("tesouro: %d\n", caverna[y+1][x]);
                    #endif
                    coleta = caverna[y+1][x];
                    caverna[y+1][x] = 0;
                    return coleta + percorre(y,x+1);
                break;
                case NENHUM:
                    #if DEBUG
                        printf("nada \n");
                    #endif
                    return 0;
                break;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE * pfile;
    long int i, j;
    double inicio, fim;
    struct localizacao {
        int x;
        int y;
    } local, proximoLocal;
    local.x = 0;
    local.y = 0;
    GET_TIME(inicio);
    pfile = fopen(argv[1], "r");
    tamanhoBagagem = atoi(argv[2]);
    passos = atoi(argv[3]);
    fscanf(pfile, "%ld %ld", &l, &c);
    caverna = (int**) malloc(l*sizeof(int*));
    for(i=0; i<l; i++){
        caverna[i] = (int*) malloc(c*sizeof(int));
    }
    for (i=0;i<l;i++) {
        for(j=0;j<c;j++) {
            fscanf(pfile,"%d", &(caverna[i][j]));
        }
    }
    #if DEBUG
        printf("ca[2][3] = %d\n", caverna[2][3]);
        printf("l: %ld - c: %ld\n", l,c);
    #endif
    dinheiro = percorre(2, 3);
    /*
    while(passosDados < passos) {
        passosDados++;
        maximoArredor = 0;
        #if DEBUG
            printf("lado = %d\n", lado);
        #endif
        if( (local.y%l != 0) ){ // testa para a ESQUERDA
            if (maximoArredor < caverna[local.y-1][local.x]   {
                maximoArredor = caverna[local.y-1][local.x];
                //lado = DIREITA; // se ele foi para a ESQUERDA, entao depois nao pode ir para a DIREITA :)
                lado = ESQUERDA; 
                proximoLocal.y = local.y - 1;
                proximoLocal.x = local.x;
            }
            else if((maximoArredor == 0) && (caverna[local.y-1][local.x] == 0)){

            }
        } 
        if ((local.y%l != l-1) ){ // testa para a DIREITA
            //arredores[1] = caverna[local.y+1][local.x];
            if (maximoArredor < caverna[local.y+1][local.x] || ( (maximoArredor == 0) && (caverna[local.y+1][local.x] == 0)) ) {
                maximoArredor = caverna[local.y+1][local.x];
                lado = ESQUERDA;
                proximoLocal.y = local.y + 1;
                proximoLocal.x = local.x;
            }
        }
        if ((local.x%c != 0) ){ // testa para CIMA
            //arredores[2] = caverna[local.y][local.x-1];
            if (maximoArredor < caverna[local.y][local.x-1] || ( (maximoArredor == 0) && (caverna[local.y][local.x-1] == 0)) ){
                maximoArredor = caverna[local.y][local.x-1];
                lado = BAIXO;
                proximoLocal.y = local.y;
                proximoLocal.x = local.x - 1;
            }
        }
        if ((local.x%c != c-1) ){ // testa para BAIXO
            //arredores[3] = caverna[local.y][local.x+1];
            if (maximoArredor < caverna[local.y][local.x+1] || ( (maximoArredor == 0) && (caverna[local.y][local.x+1] == 0)) ) {
                maximoArredor = caverna[local.y][local.x+1];
                lado = CIMA;
                proximoLocal.y = local.y;
                proximoLocal.x = local.x + 1;
            }
        }
        local = proximoLocal;
        #if DEBUG
            printf("direcao: %d %d  ", local.y, local.x);
            printf("encontrado: %d\n", caverna[local.y][local.x]);
        #endif
        dinheiro += caverna[local.y][local.x];
        caverna[local.y][local.x] = 0;
    }
    */
    #if DEBUG
        printf("\n");
        for(i=0; i<l; i++){
            for(j=0; j<c; j++){
                printf("%d ", caverna[i][j]);
            }
            printf("\n");
        }
    #endif
    printf("dinheiro aculumado: %ld\n", dinheiro);
}