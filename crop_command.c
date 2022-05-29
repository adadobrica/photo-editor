// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include "pixmap.h"
#include "utils.h"

void crop_command(pixmap *photo)
{
	// creating a copy of my RGB/grayscale matrices
	// assigning the copy its new height, width and its type and maxvalue

	pixmap photo_copy;
	int new_height = photo->y2 - photo->y1;
	int new_width = photo->x2 - photo->x1;
	photo_copy.height = new_height;
	photo_copy.width = new_width;
	photo_copy.color = photo->color;
	photo_copy.maxval = photo->maxval;
	alloc_matrix(&photo_copy);
	int done = 0;

	for (int i = 0; i < photo_copy.height; i++)
		for (int j = 0; j < photo_copy.width; j++)
			if (photo_copy.color == 1) {
				photo_copy.R[i][j] = photo->R[i + photo->y1][j + photo->x1];
				photo_copy.G[i][j] = photo->G[i + photo->y1][j + photo->x1];
				photo_copy.B[i][j] = photo->B[i + photo->y1][j + photo->x1];
				done = 1;
			} else {
				photo_copy.g_scale[i][j] =
				photo->g_scale[i + photo->y1][j + photo->x1];
				done = 1;
			}

	if (photo_copy.color == 1)
		free_mem_RGB(photo);
	else
		free_mem_gscale(photo);

	*photo = photo_copy;

	if (done == 1)
		printf("Image cropped\n");

	// selecting the new coordinates after the image being cropped

	photo->x1 = 0;
	photo->y1 = 0;
	photo->x2 = new_width;
	photo->y2 = new_height;
}
