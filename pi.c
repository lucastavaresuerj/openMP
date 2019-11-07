#include <stdio.h>
#include "timer.h"

int main() {
    static long num_steps = 100000;
    double step;
    int i;
    double x, pi, sum = 0.0;
    double tempo, fim, inicio;
    const int T = 2;
    step = 1.0/(double) num_steps;
    GET_TIME(inicio);
    for (i=0; i<num_steps; i++) {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0 + x*x);
    }
    pi = step * sum;
    GET_TIME(fim);
    tempo = fim -  inicio;
    printf("Tempo: %.8lf\n",tempo);
    printf("\n\nPI: %.14lf\n", pi);
}