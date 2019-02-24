#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_general.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset)
{
  unsigned char *img_data=NULL;
  
  // Open provided file 
  FILE *bmpfile = fopen(bmp_filename, "rb" );
  
  if(bmpfile == NULL){
    printf( "BMP file could not be opened.\n" );
    return NULL;
  }
  
  // Determine file size
  fseek(bmpfile, 2, SEEK_SET);
  fread(data_size, 1, sizeof(unsigned int), bmpfile);
  
  // Allocate memory
  img_data = (unsigned char*)malloc(*data_size * sizeof(char));
  
  if(img_data == NULL){
    printf("Memory could not be allocated.\n");
    return NULL;
  }
  
  // Rewind file pointer and read BMP contents
  rewind(bmpfile);

  if(fread(img_data, 1, *data_size, bmpfile) != *data_size){
    printf("I was unable to read the requested %d bytes.\n", *data_size);
    return NULL;
  }
  fclose(bmpfile);
  
  // Read header values
  *data_offset = *(unsigned int*)(img_data+10);
  *width = *(unsigned int*)(img_data+18);
  *height = *(unsigned int*)(img_data+22);
  *bits_per_pixel = *(unsigned short*)(img_data+28);
  
  // Compute padding
  *padding = *width % 4;

  return img_data;  
}

void 
bmp_close( unsigned char **img_data )
{
  
  // Free memory and set to null
  free(*img_data);
  *img_data = NULL;
}


/* FUNCTION: bmp_to_3D_array */
unsigned char*** 
bmp_to_3D_array( char *input_bmp_filename,   unsigned char** header_data, 
                 unsigned int* header_size,  unsigned int *width, 
                 unsigned int* height,       unsigned int* num_colors      ){

  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned char* img_data    = NULL;
  img_data = bmp_open( input_bmp_filename, width, height, &bits_per_pixel, &padding, &data_size, header_size ); 
  
  if( img_data == NULL ){ 
    printf( "Error: bmp_open returned NULL. Returning from bmp_to_3D_array without attempting changes.\n" ); 
    return NULL; 
  }

  *num_colors = bits_per_pixel/8;
  unsigned char*** pixel_array = (unsigned char***)malloc( sizeof(unsigned char**) * (*height));
  if( pixel_array == NULL ){
    printf( "Error: bmp_to_3D_array failed to allocate memory for image of height %d.\n", (*height) );
    return NULL;
  }
  
  for( int row=0; row<*height; row++ ){
    pixel_array[row] = (unsigned char**)malloc( sizeof(unsigned char*) * (*width) );
    for( int col=0; col<*width; col++ ){
      pixel_array[row][col] = (unsigned char*)malloc( sizeof(unsigned char) * (*num_colors) );
    }
  }
   
  unsigned char *pixel_data_ptr = img_data + (*header_size);
  int row_bytes = (*num_colors) * (*width) + padding;

  for( int row=0; row<*height; row++ )
    for( int col=0; col<*width; col++ )
      for( int color=0; color<*num_colors; color++ )
        pixel_array[*height-row-1][col][color] = pixel_data_ptr[row*row_bytes + col*bits_per_pixel/8 + color ];
  
 
  *header_data = (unsigned char*)malloc( *header_size );
  memcpy( *header_data, img_data, *header_size );
  
  bmp_close( &img_data );

  return pixel_array;
}

/* FUNCTION: 3D_array_to_bmp */
int 
bmp_from_3D_array( char* output_filename,   unsigned char* header_data,
                   int header_size,         unsigned char*** pixel_data,
                   int width, int height,   int num_colors                  )
{
  FILE *out_fp = fopen( output_filename, "wb" );
  if( out_fp == NULL ){
    printf( "Error: bmp_from_3D_array could not open file %s for writing.\n", output_filename );
    return -1;
  }
  
  int padding = ( 4 - (width * num_colors) % 4) % 4;
  int row_size = width*num_colors+padding;
  int raw_pixel_size = header_size + height*row_size;
  unsigned char* raw_pixels = (unsigned char*)malloc( raw_pixel_size );
  
  for( int row=0; row<height; row++ ){
    for( int col=0; col<width; col++ ){
      for( int color=0; color<num_colors; color++ ){
        raw_pixels[row*row_size + col*num_colors + color] = pixel_data[height-row-1][col][color];
      }
    }
  }
  
  fwrite( header_data, 1, header_size, out_fp );
  fwrite( raw_pixels, 1,  raw_pixel_size, out_fp );
  fclose( out_fp );
  
  return 0; 
} 
