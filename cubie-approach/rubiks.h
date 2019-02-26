// Rubik's cube struct
typedef struct rubiks_struct{

	// Last move performed
	int last_move;
	// Indexed by number {U, F, R, D, B, L}

	// Corners
	int corner_labels[8];
	int corner_perms[8];
	
	// Edges
	int edge_labels[12];
	int edge_perms[12];

	/*	Corner labels:
	 *	0:	W, G, O
	 *	1:	W, G, R
	 *	2:	W, B, R
	 *	3:	W, B, O
	 *	4:	Y, B, O
	 *	5:	Y, B, R
	 *	6:	Y, G, R
	 *	7:	Y, R, O
	 *	In solved state, entry equals index
	 *
	 *	Corner permutation convention:
	 *	The white/yellow sticker defines the permutation; if it lies on the
	 *	White/yellow face: 	perm = 0	(solved permutation)
	 *	Green/blue face: 	perm = 1
	 *	Red/orange face: 	perm = 2
	 *	
	 *	Edge labels:
	 *	00:	W, G
	 *	01:	W, R
	 *	02:	W, B
	 *	03:	W, O
	 *	04:	G, O
	 *	05:	G, R
	 *	06:	B, R
	 *	07:	B, O
	 *	08:	Y, B
	 *	09:	Y, R
	 *	10:	Y, G
	 *	11:	Y, O
	 *
	 *	Edge permutation convention:
	 *	Proper orientation:		perm = 0	(solved permutation)
	 *	Improper orientation:	perm = 1
	 */

} rubiks;

// Reset all the stickers to solved
void reset_faces(rubiks*);

// Rotate face clockwise
void rotate_CW(rubiks*, int, int[], int[], int[]);

// Rotate white face
void U(rubiks*, int);

// Rotate green face
void F(rubiks*, int);

// Rotate red face
void R(rubiks*, int);

// Rotate yellow face
void D(rubiks*, int);

// Rotate blue face
void B(rubiks*, int);

// Rotate orange face
void L(rubiks*, int);

// Generates a random scramble
void scramble(rubiks*);

// Verify if cube has been solved
int check_solved(rubiks*);

// Swap two ints
void swap(int*, int*);
