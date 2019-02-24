#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"

// Reset all the stickers to solved
void reset_faces(rubiks* cube){

	cube->last_move = -1;
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++){
		cube->W_array[i][j] = 'w';
		cube->Y_array[i][j] = 'y';
		cube->R_array[i][j] = 'r';
		cube->O_array[i][j] = 'o';
		cube->B_array[i][j] = 'b';
		cube->G_array[i][j] = 'g';
		}
	return;
}

/*
 * IMPORTANT CUBE CONVENTION FOR THIS SCRIPT
 * Clockwise surface arrow arrangement
 * Up points Back points Right points Up
 * Front points Down points Left points Front
 */

// Swap two values
void swap(char* a, char* b){

	char temp = *a;
	*a = *b;
	*b = temp;
	return;
}

// Rotate 3x3 array without affecting original
char** rotate(char (*cube_face)[3], int count){

	// Allocate space for new array
	char** output = (char**)malloc(3*sizeof(char*));
	for (int i = 0; i < 3; i++)
		output[i] = (char*)malloc(3*sizeof(char));

	// Populate new array
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			output[i][j] = cube_face[i][j];

	// Rotate new array
	for (int i = 0; i < count; i++){

		// Cycle edges
		swap(output[0]+1, output[1]+0);
		swap(output[1]+0, output[2]+1);
		swap(output[2]+1, output[1]+2);

		// Cycle corners
		swap(output[0]+0, output[2]+0);
		swap(output[2]+0, output[2]+2);
		swap(output[2]+2, output[0]+2);
	}
	return output;
}

// Rotate the front face clockwise
void rotate_CW(char(*front)[3], char(*top)[3], char(*right)[3], char(*bottom)[3], char(*left)[3]){

	swap(right[0]+0, bottom[2]+2);
	swap(right[0]+1, bottom[2]+1);
	swap(right[0]+2, bottom[2]+0);

	swap(top[0]+2, right[0]+0);
	swap(top[1]+2, right[0]+1);
	swap(top[2]+2, right[0]+2);

	swap(left[2]+0, top[0]+2);
	swap(left[1]+0, top[1]+2);
	swap(left[0]+0, top[2]+2);

	swap(front[0]+1, front[1]+0);
	swap(front[1]+0, front[2]+1);
	swap(front[2]+1, front[1]+2);

	swap(front[0]+0, front[2]+0);
	swap(front[2]+0, front[2]+2);
	swap(front[2]+2, front[0]+2);

	return;
}

// Rotate red face
void R(rubiks* cube, int count){
	for (int i = 0; i < count; i++)
		rotate_CW(cube->R_array, cube->W_array, cube->B_array, cube->Y_array, cube->G_array);
	return;
}

// Rotate white face
void U(rubiks* cube, int count){
	for (int i = 0; i < count; i++)
		rotate_CW(cube->W_array, cube->B_array, cube->R_array, cube->G_array, cube->O_array);
	return;
}

// Rotate orange face
void L(rubiks* cube, int count){
	for (int i = 0; i < count; i++)
		rotate_CW(cube->O_array, cube->G_array, cube->Y_array, cube->B_array, cube->W_array);
	return;
}

// Rotate blue face
void B(rubiks* cube, int count){
	for (int i = 0; i < count; i++)
		rotate_CW(cube->B_array, cube->R_array, cube->W_array, cube->O_array, cube->Y_array);
	return;
}

// Rotate yellow face
void D(rubiks* cube, int count){
	for (int i = 0; i < count; i++)
		rotate_CW(cube->Y_array, cube->O_array, cube->G_array, cube->R_array, cube->B_array);
	return;
}

// Rotate green face
void F(rubiks* cube, int count){
	for (int i = 0; i < count; i++)
		rotate_CW(cube->G_array, cube->Y_array, cube->O_array, cube->W_array, cube->R_array);
	return;
}

// Generates a random scramble
void scramble(rubiks* cube){

	void (*move_array[6]) (rubiks* cube, int count) = {R, U, L, B, D, F};
	char move_prefix[6] = {'R', 'U', 'L', 'B', 'D', 'F'};
	char move_suffix[3] = {'\0', '2', '\''};

	int move, rotation;
	int last_move = -1;

	printf("Scramble: ");
	for (int i = 0; i < 15; i++){

		// Determine face to rotate
		do{
		move = rand() % 6;
		} while (move == last_move);

		// Determine times to rotate
		rotation = rand() % 3 + 1;

		// Print output
		move_array[move](cube, rotation);

		printf("%c%c ", move_prefix[move], move_suffix[rotation-1]);
	}
	printf("\n");
	return;
}

// Verify if cube has been solved
int check_solved(rubiks* cube){

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++){

			if (cube->W_array[i][j] != 'w')
				return 0;
			if (cube->Y_array[i][j] != 'y')
				return 0;
			if (cube->B_array[i][j] != 'b')
				return 0;
			if (cube->G_array[i][j] != 'g')
				return 0;
			if (cube->R_array[i][j] != 'r')
				return 0;
			if (cube->O_array[i][j] != 'o')
				return 0;
		}
	return 1;
}
