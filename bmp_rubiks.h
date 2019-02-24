// Prepare rubik's cube background
void bmp_set_bgd(unsigned char***);

// Color the 9 stickers on one face of the cube
void bmp_color_face(int, int, char**, unsigned char***);

// Output cube decomposition image
void bmp_cube_decomposition(rubiks*);
