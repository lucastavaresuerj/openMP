#include <stdio.h>
#include "timer.h"
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main() {
    int th_id, nthreads;
    int i,j,x=0;
    #pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        if(th_id == 1){
            for (i=0;i<100000;i++){
                for (j=0;j<100000;j++){
                    x++;
                }
            }
        }

        printf("Hello World from threads %d\n", th_id);
        #pragma omp barrier //<-- master waits until all threads finish before
        if(th_id = 0) {
            nthreads = omp_get_num_threads();
            printf("There are %d threads\n", nthreads);
        }
    }
}