#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubiks.h"
#include "minimax.h"

// The main attraction
int main(){

	// Clear the mind
	system("clear");
	srand(time(NULL));

	// Fresh Yan3
	rubiks* cube = (rubiks*)malloc(sizeof(rubiks));
	reset_faces(cube);
	
	// Scramble it a little
	R(cube, 2);
	U(cube, 3);
	R(cube, 1);
	L(cube, 1);
	D(cube, 3);
	F(cube, 2);

	// Run the minimax solver
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	printf("Minimax says: %d\n", minimax(cube, 7));
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("It took %f seconds to execute \n", cpu_time_used); 

	return 0;
}
