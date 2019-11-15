#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    FILE* pfile;
    int sizeOfNumber, sizeDigits, i;
    long int sizeOfVector;
    //long int* vet;
    sizeDigits = 1;
    sizeOfVector = atoi(argv[1]);
    sizeOfNumber = atoi(argv[2]);
    for(i=0;i<sizeOfNumber;i++) {
        sizeDigits = 10*sizeDigits;
    }
    srand(time(NULL));
    pfile = fopen(argv[3], "w");
    fprintf(pfile, "%ld\n", sizeOfVector);
    for (i=0; i<sizeOfVector; i++) {
        fprintf(pfile, "%d ", rand() % sizeDigits);
    }
}