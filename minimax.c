#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubiks.h"
#include "minimax.h"

// Minimax style algo adapted to solving rubiks cube
int minimax(rubiks* cube, int depth, int last_move){

	// Check if solved
	if (check_solved(cube))
		return 1;

	// Check if leaf node
	if (!depth)
		return 0;

	int value;
	void (*move_array[6]) (rubiks* cube, int count) = {U, R, F, D, L, B};

	// Consider all possible moves in HTM
	for (int move = 0; move < 6; move++){

		// Prevent rotating the same face consecutively
		if (move == last_move)
			continue;
		
		// Prevent rotating opposite faces consecutively in both ways
		if (last_move % 3 == move % 3 && move >= 3)
			continue;

		// Consider all possible degrees of rotation
		for (int rotation = 1; rotation < 4; rotation++){

			// Duplicate cube
			rubiks* new_cube = (rubiks*)malloc(sizeof(rubiks));
			memcpy(new_cube, cube, sizeof(rubiks));

			// Perform rotation and maximize
			move_array[move](new_cube, rotation);
			value = minimax(new_cube, depth-1, move);
			free(new_cube);

			// If cube is solved, return
			if (value)
				return 1;
		}
	}
	return value;
}

/*	
 *	Is it more economic to analyze all tree nodes in half turn metric (HTM) or quarter turn metric (QTM)?
 *	The maximum depth of the minimax algorithm will be God's number (https://cube20.org/). 
 *
 *	In HTM, God's number is 20
 *	At each level, 3 moves on each face can be made (R, R2, R')
 *	Beyond the first move, it is prohibited to consecutively turn the same face
 *	i.e. R -/> R, R2, R'
 *	Thus, the total number of positions to run is:
 *	N_{htm} = (3*6) * (3*6 - 3) ^ 19 
 *	
 *	In QTM, God's number is 26
 *	At each level, 2 moves on each face can be made (R, R')
 *	Beyond the first move, it is prohibited to perform the inverse move
 *	i.e. R -/> R', but R -> R is permitted
 *	Thus, the total number of positions to ru is:
 *	N_{qtm} = (2*6) * (2*6 - 1) ^ 25
 *
 *	Which of these numbers is greater?
 *	N_{qtm} / N_{htm} ~= 3258
 *
 *	Thus, there are many less positions to evaluate in HTM, so we use HTM.
 *
 *	(Yes, this was crude. In QTM, after two consecutive R's, there should be no R or R'.
 *	In addition, for QTM and HTM this calculation doesn't account for cutting out 
 *	different permutation orders for turning different faces)
 */
