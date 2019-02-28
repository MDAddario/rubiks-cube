#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubiks.h"
#include "minimax.h"
#include "bmp_general.h"
#include "bmp_rubiks.h"

// The main attraction
int main(int argc, char* argv[]){

	// Clear the mind
	system("clear");
	srand(time(NULL));

	// Fresh Yan3
	rubiks* cube = (rubiks*)malloc(sizeof(rubiks));
	reset_faces(cube);
	
	// Scramble it a little
	superflip(cube);

	// Run the minimax solver
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	printf("Minimax says: %d\n", minimax(cube, 7, -1));
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("It took %f seconds to execute \n", cpu_time_used); 

	// Print bmp of cube
	bmp_cube_decomposition(cube);

	return 0;
}
