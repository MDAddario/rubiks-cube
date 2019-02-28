// Rubik's cube struct
typedef struct rubiks_struct{

	int last_move;
	char W_array[3][3];		// White
	char Y_array[3][3];		// Yellow
	char R_array[3][3];		// Red
	char O_array[3][3];		// Orange
	char B_array[3][3];		// Blue
	char G_array[3][3];		// Green

} rubiks;

// Reset all the stickers to solved
void reset_faces(rubiks*);

// Swap two chars
void swap(char*, char*);

// Rotate 3x3 array without affecting original
char** rotate(char(*)[3], int);

// Rotate the front face clockwise
void rotate_CW(char(*)[3], char(*)[3], char(*)[3], char(*)[3], char(*)[3]);

// Rotate red face
void R(rubiks*, int);

// Rotate white face
void U(rubiks*, int);

// Rotate orange face
void L(rubiks*, int);

// Rotate blue face
void B(rubiks*, int);

// Rotate yellow face
void D(rubiks*, int);

// Rotate green face
void F(rubiks*, int);

// Generates a random scramble
void scramble(rubiks*);

// Verify if cube has been solved
int check_solved(rubiks*);

// Enforce 20 move solve requirement
void superflip(rubiks*);
