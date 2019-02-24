#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "minimax.h"

// Minimax style algo adapted to solving rubiks cube
int minimax(rubiks* cube, int depth){

	// Check if solved
	if (check_solved(cube))
		return 1;

	// Check if leaf node
	if (!depth)
		return 0;

	int value, old_last_move;
	void (*move_array[6]) (rubiks* cube, int count) = {R, U, L, B, D, F};

	// Consider all possible moves
	for (int move = 0; move < 6; move++){

		// Prevent rotating the same face consecutively
		if (move == cube->last_move)
			continue;

		old_last_move = cube->last_move;

		// Consider all possible degrees of rotation
		for (int rotation = 1; rotation < 4; rotation++){

			// Perform rotation
			move_array[move](cube, rotation);
			cube->last_move = move;

			// Find some way to avoid:
			//		- Rotating opposite faces consecutively in both ways
			//				ex: BAN ONE OF U, D or D, U
			//		Potentially pair up move_array by index in mod 3?

			// Run minimax
			value = minimax(cube, depth-1);
			
			// Rollback move
			move_array[move](cube, 4 - rotation);
			cube->last_move = old_last_move;

			// If cube is solved, return
			if (value)
				return 1;
		}
	}
	return value;
}
