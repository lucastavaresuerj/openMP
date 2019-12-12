#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

char ** tabuleiro;
char ** novoTabuleiro;
char ** antigoTabuleiro;
long tamanho, passos;

int contaVizinhos(long y, long x){
    int soma = 0;
    for(long vy=y-1; vy<=y+1; vy++){
        for(long vx=x-1; vx<=x+1; vx++){
            soma += tabuleiro[vy][vx];
        }
    }
    (tabuleiro[y][x] == 1 ) ? soma-- : soma;
    return soma;
}

void jogo(){
    int vizinhos = 0;
    long l, c;
    #pragma omp parallel for private(l,c)
    for(l=1; l<=tamanho; l++){
        for(c=1; c<=tamanho; c++){
            vizinhos = contaVizinhos(l,c);
            if(vizinhos < 2) {
                novoTabuleiro[l][c] = 0;
            } 
            else if(vizinhos == 3){
                novoTabuleiro[l][c] = 1;
            }
            else if (vizinhos > 3){
                novoTabuleiro[l][c] = 0;
            }
            else {
                novoTabuleiro[l][c] = tabuleiro[l][c];
            } 
        }
    }
}

void printTabuleiro(char ** tab){
    for(int i=0; i<tamanho; i++){
        printf("-");
    }
    printf("\n"); 
    for(int i=1; i<=tamanho; i++){
        for(int j=1; j<=tamanho; j++){
            printf("%c", tab[i][j] == 1 ? 'x' : ' ');
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]){
    FILE *pfTabuleiro;
    char scan;
    char lineBreack;
    pfTabuleiro = fopen(argv[1], "r");
    fscanf(pfTabuleiro, "%ld %ld%c", &tamanho, &passos, &lineBreack);
    tabuleiro = (char **) malloc((tamanho+2)*sizeof(char *));
    novoTabuleiro = (char **) malloc((tamanho+2)*sizeof(char *));
    antigoTabuleiro = (char **) malloc((tamanho+2)*sizeof(char *));
    for(int i=0; i<tamanho+2; i++){
        tabuleiro[i] = (char*) calloc((tamanho+2),sizeof(char));
        novoTabuleiro[i] = (char*) calloc((tamanho+2),sizeof(char));
        antigoTabuleiro[i] = (char*) calloc((tamanho+2),sizeof(char));
    }
    for(int i=1; i<=tamanho; i++){
        for(int j=1; j<=tamanho; j++){
            fscanf(pfTabuleiro, "%c", &scan);
            //printf("[%d][%d] = %d\n", i, j, (scan == 'x'));
            tabuleiro[i][j] = (scan == 'x');
        }
    }
    //passos = 0;
    //contaVizinhos(2, 3);
    for(long p = 0; p<passos; p++){
        jogo();
        antigoTabuleiro = tabuleiro;
        tabuleiro = novoTabuleiro;
        novoTabuleiro = antigoTabuleiro;
        #if DEBUG 
            printTabuleiro(tabuleiro);
        #endif
    }
    printTabuleiro(tabuleiro);
}