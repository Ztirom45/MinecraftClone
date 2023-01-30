//TODO config stuff w h name
#include <stdlib.h>//memorie options(malloc)
#include <stdio.h> //filestream

#include <png.h>  //calculate png
#include <GL/glut.h> //GLubyte

#include "confing.h"

static GLubyte pixel_array[256][256][4];
static unsigned int pixel_array_w;
static unsigned int pixel_array_h;

void load_row_pointers(){
	//vars:
	FILE *fp = fopen(IMAGE_PATH, "rb");
	char header[8];	   // 8 is the maximum size that can be checked
	
	png_bytep * row_pointers = NULL;
	png_infop info_ptr = NULL;
	png_structp png_ptr = NULL;
	
	int rowbytes = 0;
	
	//read
	fread(header, 1, 8, fp);
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);
	
	//init
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	
	//w h
	pixel_array_w = png_get_image_width(png_ptr, info_ptr);
	pixel_array_h = png_get_image_height(png_ptr, info_ptr);
	printf("w,h:%d %d\n",pixel_array_w,pixel_array_h);
	
	//get pixel
	rowbytes = png_get_rowbytes(png_ptr,info_ptr);
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * pixel_array_h);
	for (int y=0; y<pixel_array_h; y++) 
	{
		row_pointers[y] = (png_byte*) malloc(rowbytes);
	}
	
	png_read_image(png_ptr, row_pointers);
	
	//free(pixel_array);//kp
	int c = 0;
	for (int y=0; y<pixel_array_h; y++) {
		png_byte* row = row_pointers[y];
		for (int x=0; x<pixel_array_w; x++) {
			pixel_array[x][y][0] = *row++;
			pixel_array[x][y][1] = *row++;
			pixel_array[x][y][2] = *row++;
			pixel_array[x][y][3] = *row++;
		}
		
	}
	fclose(fp);
}
