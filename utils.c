// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include "pixmap.h"

void alloc_matrix(pixmap *photo)
{
	if (photo->color == 0) {
		photo->g_scale = calloc(photo->height, sizeof(int *));
		if (!photo->g_scale)
			exit(-1);
		for (int i = 0; i < photo->height; i++)
			photo->g_scale[i] = calloc(photo->width, sizeof(int));
	} else {
		// dynamically allocating for the R scale
		photo->R = calloc(photo->height, sizeof(int *));
		if (!photo->R)
			exit(-1);
		for (int i = 0; i < photo->height; i++)
			photo->R[i] = calloc(photo->width, sizeof(int));

		// dynamically allocating for the G scale

		photo->G = calloc(photo->height, sizeof(int *));
		if (!photo->G)
			exit(-1);
		for (int i = 0; i < photo->height; i++)
			photo->G[i] = calloc(photo->width, sizeof(int));

		// dynamically allocating for the B scale

		photo->B = calloc(photo->height, sizeof(int *));
		if (!photo->B)
			exit(-1);
		for (int i = 0; i < photo->height; i++)
			photo->B[i] = calloc(photo->width, sizeof(int));
	}
}

// function to free the memory of the grayscale photo

void free_mem_gscale(pixmap *photo)
{
	for (int i = 0; i < photo->height; i++)
		free(photo->g_scale[i]);
	free(photo->g_scale);
}

// function to free the memory of the RGB photo

void free_mem_RGB(pixmap *photo)
{
	for (int i = 0; i < photo->height; i++) {
		free(photo->R[i]);
		free(photo->G[i]);
		free(photo->B[i]);
	}
	free(photo->R);
	free(photo->G);
	free(photo->B);
}
