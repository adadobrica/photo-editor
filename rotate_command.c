// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include "pixmap.h"
#include "utils.h"
#include "select_command.h"

// function to check if the selection is square or full

int check_selection(int ok, pixmap *photo)
{
	ok = 0;
	int new_width = photo->x2 - photo->x1;
	int new_height = photo->y2 - photo->y1;
	if (photo->x1 == 0 && photo->y1 == 0 && photo->x2 == photo->width &&
		photo->y2 == photo->height)
		ok = 1;
	else if (new_width == new_height)
		ok = 2;
	return ok;
}

void rotate90_left_all(pixmap *photo)
{
	// creating a copy and swapping the values of the width and height

	pixmap photo_copy = *photo;
	swap(&photo_copy.height, &photo_copy.width);

	// allocating memory for the copy

	alloc_matrix(&photo_copy);

	if (photo->color == 0)
		for (int i = 0; i < photo_copy.height; i++)
			for (int j = 0; j < photo_copy.width; j++)
				photo_copy.g_scale[i][j] =
				photo->g_scale[photo->height - j - 1][i];
	else
		for (int i = 0; i < photo_copy.height; i++)
			for (int j = 0; j < photo_copy.width; j++) {
				photo_copy.R[i][j] = photo->R[photo->height - j - 1][i];
				photo_copy.G[i][j] = photo->G[photo->height - j - 1][i];
				photo_copy.B[i][j] = photo->B[photo->height - j - 1][i];
			}

	if (photo->color == 1)
		free_mem_RGB(photo);
	else
		free_mem_gscale(photo);

	// assigning the new width, height and the rotated elements
	// to the new photo

	*photo = photo_copy;
	photo->x1 = 0;
	photo->y1 = 0;
	photo->x2 = photo->width;
	photo->y2 = photo->height;
}

void rotate90_left_square(pixmap *photo)
{
	// creating a copy of the image and dynamically allocating it

	pixmap photo_copy = *photo;

	alloc_matrix(&photo_copy);

	// deep copy

	for (int i = 0; i < photo->height; i++)
		for (int j = 0; j < photo->width; j++)
			if (photo->color == 0) {
				photo_copy.g_scale[i][j] = photo->g_scale[i][j];
			} else {
				photo_copy.R[i][j] = photo->R[i][j];
				photo_copy.G[i][j] = photo->G[i][j];
				photo_copy.B[i][j] = photo->B[i][j];
			}

	// rotating the square selection of the photo

	for (int i = photo->y1; i < photo->y2; i++)
		for (int j = photo->x1; j < photo->x2; j++) {
			int new_i = i - photo->y1 + photo->x1, new_j = j - photo->x1;
			if (photo->color == 0) {
				photo->g_scale[i][j] =
				photo_copy.g_scale[photo->y2 - 1 - new_j][new_i];
			} else {
				photo->R[i][j] = photo_copy.R[photo->y2 - 1 - new_j][new_i];
				photo->G[i][j] = photo_copy.G[photo->y2 - 1 - new_j][new_i];
				photo->B[i][j] = photo_copy.B[photo->y2 - 1 - new_j][new_i];
			}
		}

	// freeing the memory of the copy image after using it

	if (photo->color == 1)
		free_mem_RGB(&photo_copy);
	else
		free_mem_gscale(&photo_copy);
}

void rotate_command(pixmap *photo)
{
	int angle, ok = 0, new_angle;
	scanf("%d", &angle);
	ok = check_selection(ok, photo);
	if (ok == 0) {
		printf("The selection must be square\n");
	} else {
		// check if the selection is squared
		if (ok == 2) {
			// calculating the complementary angle if it's negative

			if (angle < 0)
				new_angle = 360 + angle;
			else
				new_angle = angle;

			if (new_angle % 360 == 0) {
				printf("Rotated %d\n", angle);
			} else if (new_angle % 360 == 90) {
				rotate90_left_square(photo);
				printf("Rotated %d\n", angle);
			} else if (new_angle % 360 == 180) {
				// rotating twice

				for (int i = 0; i < 2; i++)
					rotate90_left_square(photo);

				printf("Rotated %d\n", angle);
			} else if (new_angle % 360 == 270) {
				// rotating three times

				for (int i = 0; i < 3; i++)
					rotate90_left_square(photo);
				printf("Rotated %d\n", angle);
			} else {
				printf("Unsupported rotation angle\n");
			}
		} else if (ok == 1) { //if the image is fully selected
			if (angle < 0)
				new_angle = 360 + angle;
			else
				new_angle = angle;

			if (new_angle % 360 == 0) {
				printf("Rotated %d\n", angle);
			} else if (new_angle % 360 == 90) {
				rotate90_left_all(photo);
				printf("Rotated %d\n", angle);
			} else if (new_angle % 360 == 180) {
				for (int i = 0; i < 2; i++)
					rotate90_left_all(photo);
				printf("Rotated %d\n", angle);
			} else if (new_angle % 360 == 270) {
				// rotating three times
				for (int i = 0; i < 3; i++)
					rotate90_left_all(photo);
				printf("Rotated %d\n", angle);
			} else {
				printf("Unsupported rotation angle\n");
			}
		}
	}
}
