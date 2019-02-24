#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "bmp_general.h"
#include "bmp_rubiks.h"

// Prepare rubik's cube background
void bmp_set_bgd(unsigned char*** pixel_array){

	// Set background to white
	for (int row = 0; row < 455; row++)
		for (int col = 0; col < 605; col++)
			for (int color = 0; color < 3; color++)
				pixel_array[row][col][color] = 255;

	// Black bars
	for (int col = 0; col < 605; col++)
		for (int row = 150; row < 305; row++)
			if (row % 50 < 5 || col % 50 < 5)
				for (int color = 0; color < 3; color++)
					pixel_array[row][col][color] = 0;

	for (int col = 150; col < 305; col++)
		for (int row = 0; row < 455; row++)
			if (row % 50 < 5 || col % 50 < 5)
				for (int color = 0; color < 3; color++)
					pixel_array[row][col][color] = 0;
	return;
}

// Color the 9 stickers on one face of the cube
void bmp_color_face(int top, int left, char** cube_face, unsigned char*** pixel_array){

	int* color_palet;
	int color_red[3] 	= {  0,   0, 255};
	int color_blue[3] 	= {255,   0,   0};
	int color_green[3] 	= {  0, 255,   0};
	int color_white[3] 	= {255, 255, 255};
	int color_orange[3] = {  2, 129, 255};
	int color_yellow[3] = {  0, 255, 255};

	// Color all 9 stickers
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++){

			// Sticker selection
			if (cube_face[i][j] == 'w')
				color_palet = color_white;
			else if (cube_face[i][j] == 'y')
				color_palet = color_yellow;
			else if (cube_face[i][j] == 'b')
				color_palet = color_blue;
			else if (cube_face[i][j] == 'g')
				color_palet = color_green;
			else if (cube_face[i][j] == 'r')
				color_palet = color_red;
			else if (cube_face[i][j] == 'o')
				color_palet = color_orange;

			// Color in the stickers
			for (int col = (left + j*50); col < (left + j*50 + 45); col++)
				for (int row = (top + i*50); row < (top + i*50 + 45); row++)
					for (int color = 0; color < 3; color++)
						pixel_array[row][col][color] = color_palet[color];
		}
	return;
}

// Output cube decomposition image
void bmp_cube_decomposition(rubiks* cube){

	char* filename_original = "template.bmp";
	char* filename_output = "output_cube.bmp";

	// Open image
	unsigned char*		header_data;
	unsigned int		header_size, width, height, num_colors;
	unsigned char*** 	pixel_array = NULL;
	
	pixel_array = bmp_to_3D_array(filename_original,	&header_data,
									&header_size,		&width,
									&height,			&num_colors);

	if (pixel_array == NULL){
		printf("Error: bmp_to_3D_array failed for file %s.\n", filename_original);
		return;
	}

	// Setup rubik's cube background
	bmp_set_bgd(pixel_array);

	// Color faces, rotate to appropriate orientation
	bmp_color_face(  5, 155, rotate(cube->B_array, 1), pixel_array);
	bmp_color_face(155, 155, rotate(cube->W_array, 0), pixel_array);
	bmp_color_face(155,   5, rotate(cube->O_array, 2), pixel_array);
	bmp_color_face(305, 155, rotate(cube->G_array, 2), pixel_array);
	bmp_color_face(155, 305, rotate(cube->R_array, 3), pixel_array);
	bmp_color_face(155, 455, rotate(cube->Y_array, 1), pixel_array);

	// Output bmp
	bmp_from_3D_array(filename_output,	header_data,	header_size, pixel_array,
						width,			height,			num_colors);

	return;
}
