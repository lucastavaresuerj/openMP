
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#define T 4 // num threads
//#define DEBUG 1
#define TIME 1
typedef unsigned char cell_t; 

/* read a file into the life board */
void read_file (FILE * f, cell_t ** board, int size) {
	int	i, j;
	char	*s = (char *) malloc(size+10);
	char c;
	for (j=0; j<size; j++) {
		/* get a string */
		fgets (s, size+10,f);
		/* copy the string to the life board */
		for (i=0; i<size; i++)
		{
		 	//c=fgetc(f);
			//putchar(c);
			board[i][j] = s[i] == 'x';
		}
		//fscanf(f,"\n");
	}
}

/* print the life board */
void print (cell_t ** board, int size) {
	int	i, j;
	/* for each row */
	for (j=0; j<size; j++) {
		/* print each column position... */
		for (i=0; i<size; i++) 
			printf ("%c", board[i][j] ? 'x' : ' ');
		/* followed by a carriage return */
		printf ("\n");
	}
}

cell_t ** allocate_board (int size) {
	cell_t ** board = (cell_t **) malloc(sizeof(cell_t*)*size);
	int	i;
	for (i=0; i<size; i++)
		board[i] = (cell_t *) malloc(sizeof(cell_t)*size);
	return board;
}

void free_board (cell_t ** board, int size) {
	int     i;
	for (i=0; i<size; i++)
			free(board[i]);
	free(board);
}


/* return the number of on cells adjacent to the i,j cell */
int adjacent_to (cell_t ** board, int size, int i, int j) {
	int	k, l, count=0;
	
	int sk = (i>0) ? i-1 : i;
	int ek = (i+1 < size) ? i+1 : i;
	int sl = (j>0) ? j-1 : j;
        int el = (j+1 < size) ? j+1 : j;

	for (k=sk; k<=ek; k++)
		for (l=sl; l<=el; l++)
			count+=board[k][l];
	count-=board[i][j];
	
	return count;
}

void play (cell_t ** board, cell_t ** newboard, int size) {
	int	i, j, a;
	/* for each cell, apply the rules of Life */
    #pragma omp parallel for private(i,j) num_threads(T)
	for (i=0; i<size; i++)
		for (j=0; j<size; j++) {
			a = adjacent_to (board, size, i, j);
			if (a == 2) newboard[i][j] = board[i][j];
			if (a == 3) newboard[i][j] = 1;
			if (a < 2) newboard[i][j] = 0;
			if (a > 3) newboard[i][j] = 0;
		}
}


int main () {
	int size, steps;
	FILE    *f;
  	f = stdin;
    #if TIME
        double inicio, fim, tempo;
        GET_TIME(inicio);
    #endif
	fscanf(f,"%d %d", &size, &steps);
	cell_t ** prev = allocate_board (size);
	read_file (f, prev,size);
	fclose(f);
	cell_t ** next = allocate_board (size);
	cell_t ** tmp;
	int i,j;
	#ifdef DEBUG
	printf("Initial \n");
	print(prev,size);
	printf("----------\n");
	#endif

	for (i=0; i<steps; i++) {
		play (prev,next,size);
		#ifdef DEBUG
			printf("%d ----------\n", i);
			print (next,size);
		#endif
		tmp = next;
		next = prev;
		prev = tmp;
	}
	print (prev,size);
	free_board(prev,size);
	free_board(next,size);
    #if TIME
        GET_TIME(fim);
        tempo = fim - inicio;
        printf("tempo: %.3f\n", tempo);
    #endif
}
