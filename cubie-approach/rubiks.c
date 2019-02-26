#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"

// Reset all the stickers to solved
void reset_faces(rubiks* cube){

	cube->last_move = -1;

	for (int i = 0; i < 8; i++){
		cube->corner_labels[i] = i;
		cube->corner_perms[i] = 0;
	}

	for (int i = 0; i < 12; i++){
		cube->edge_labels[i] = i;
		cube->edge_perms[i] = 0;
	}
	return;
}

// Rotate face clockwise
void rotate_CW(rubiks* cube, int rot, int c[], int cp[], int e[]){

	// Number of rotations
	for (int i = 0; i < rot; i++){

		// Swap cubies
		for (int k = 0; k < 3; k++){

			swap(cube->corner_labels + c[k], cube->corner_labels + c[k+1]);
			swap(cube->corner_perms + c[k], cube->corner_perms + c[k+1]);

			swap(cube->edge_labels + e[k], cube->edge_labels + e[k+1]);
			swap(cube->edge_perms + e[k], cube->edge_perms + e[k+1]);
		}

		// Manage permutations
		for (int k = 0; k < 4; k++){

			if (cube->corner_perms[c[k]] == cp[0])
				cube->corner_perms[c[k]] = cp[1];
			else if (cube->corner_perms[c[k]] == cp[1])
				cube->corner_perms[c[k]] = cp[0];

			cube->edge_perms[e[k]] = !(cube->edge_perms[e[k]]);
		}
	}
	return;
}

/*	Permutation argument:
 *
 *	When rotating a face, the corner permutation only changes
 *	if the permutation orientation does not face the same way
 *	as the face (i.e., when rotating the white face, if the white
 *	sticker is facing with the white face, the permutation does not
 *	change, but if it faces green or red, it swaps).
 *
 *	For edge permutations, these always change. If an edge returns
 *	to its original position after an even number of moves, it will
 *	be in the same permutation. If it returns after an odd number of
 *	moves, it will be reversed.
 */


// Rotate white face
void U(rubiks* cube, int rot){

	// Corner indices ccw on face
	int c[] = {0, 1, 2, 3};
	// Corner perms swapping
	int cp[] = {1, 2};
	// Edge indices ccw on face
	int e[] = {0, 1, 2, 3};

	// Rotate
	rotate_CW(cube, rot, c, cp, e);
	return;
}

// Rotate green face
void F(rubiks* cube, int rot){

	// Corner indices ccw on face
	int c[] = {7, 6, 1, 0};
	// Corner perms swapping
	int cp[] = {0, 2};
	// Edge indices ccw on face
	int e[] = {0, 4, 10, 5};

	// Rotate
	rotate_CW(cube, rot, c, cp, e);
	return;
}

// Rotate red face
void R(rubiks* cube, int rot){

	// Corner indices ccw on face
	int c[] = {6, 5, 2, 1};
	// Corner perms swapping
	int cp[] = {0, 1};
	// Edge indices ccw on face
	int e[] = {1, 5, 9, 6};

	// Rotate
	rotate_CW(cube, rot, c, cp, e);
	return;
}

// Rotate yellow face
void D(rubiks* cube, int rot){

	// Corner indices ccw on face
	int c[] = {4, 5, 6, 7};
	// Corner perms swapping
	int cp[] = {1, 2};
	// Edge indices ccw on face
	int e[] = {8, 9, 10, 11};

	// Rotate
	rotate_CW(cube, rot, c, cp, e);
	return;
}

// Rotate blue face
void B(rubiks* cube, int rot){

	// Corner indices ccw on face
	int c[] = {5, 4, 3, 2};
	// Corner perms swapping
	int cp[] = {0, 2};
	// Edge indices ccw on face
	int e[] = {2, 6, 8, 7};

	// Rotate
	rotate_CW(cube, rot, c, cp, e);
	return;
}

// Rotate orange face
void L(rubiks* cube, int rot){

	// Corner indices ccw on face
	int c[] = {0, 3, 4, 7};
	// Corner perms swapping
	int cp[] = {0, 1};
	// Edge indices ccw on face
	int e[] = {3, 7, 11, 4};

	// Rotate
	rotate_CW(cube, rot, c, cp, e);
	return;
}

// Generates a random scramble
void scramble(rubiks* cube){

	reset_faces(cube);

	void (*move_array[6]) (rubiks* cube, int rot) = {U, F, R, D, B, L};
	char move_prefix[6] = {'U', 'F', 'R', 'D', 'B', 'L'};
	char move_suffix[3] = {'\0', '2', '\''};

	int move, rotation;

	printf("Scramble: ");
	for (int i = 0; i < 15; i++){

		// Determine face to rotate
		do{
		move = rand() % 6;
		} while (move == cube->last_move);
		cube->last_move = move;

		// Determine times to rotate
		rotation = rand() % 3 + 1;

		// Rotate
		move_array[move](cube, rotation);
		printf("%c%c ", move_prefix[move], move_suffix[rotation-1]);
	}
	printf("\n");
	return;
}

// Verify if cube has been solved
int check_solved(rubiks* cube){

	for (int i = 0; i < 8; i++){
		if (cube->corner_labels[i] != i)
			return 0;
		if (cube->corner_perms[i] != 0)
			return 0;
	}

	for (int i = 0; i < 12; i++){
		if (cube->edge_labels[i] != i)
			return 0;
		if (cube->edge_perms[i] != 0)
			return 0;
	}

	return 1;
}

// Swap two integers
void swap(int* a, int* b){

	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}
