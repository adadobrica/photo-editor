// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pixmap.h"
#include "utils.h"
#define F_MAX 256

// creating a clamp function with boundaries for x

double clamp(double x)
{
	if (x < 0)
		x = 0;
	if (x > 255000)
		x = 255000;
	return x;
}

// checking if the input filter is correct

void check_invalid_args_for_apply(int *ok, char *filter)
{
	*ok = 0;

	if (!filter) {
		*ok = -1;
		return;
	}

	if (strcmp(filter, "EDGE") == 0) {
		*ok = 1;
	} else if (strcmp(filter, "BLUR") == 0) {
		*ok = 1;
	} else if (strcmp(filter, "GAUSSIAN_BLUR") == 0) {
		*ok = 1;
	} else if (strcmp(filter, "SHARPEN") == 0) {
		*ok = 1;
	} else {
		int len = strlen(filter), cnt = 0;
		for (int i = 0; i < len; i++)
			if (isalpha(filter[i]) > 0)
				cnt++;
		if (!cnt)
			*ok = -1;
		else
			*ok = 0;
	}
}

// function for multiplying the red pixel with the given kernel

double kernel_red(pixmap *photo_copy, double kernel[3][3], int i, int j)
{
	double red = 0.0;
	red += kernel[0][0] * photo_copy->R[i - 1][j - 1];
	red += kernel[0][1] * photo_copy->R[i - 1][j];
	red += kernel[0][2] * photo_copy->R[i - 1][j + 1];
	red += kernel[1][0] * photo_copy->R[i][j - 1];
	red += kernel[1][1] * photo_copy->R[i][j];
	red += kernel[1][2] * photo_copy->R[i][j + 1];
	red += kernel[2][0] * photo_copy->R[i + 1][j - 1];
	red += kernel[2][1] * photo_copy->R[i + 1][j];
	red += kernel[2][2] * photo_copy->R[i + 1][j + 1];
	red = clamp(red / 10000);
	return red;
}

// function for multiplying the green pixel with the given kernel

double kernel_green(pixmap *photo_copy, double kernel[3][3], int i, int j)
{
	double green = 0.0;
	green += kernel[0][0] * photo_copy->G[i - 1][j - 1];
	green += kernel[0][1] * photo_copy->G[i - 1][j];
	green += kernel[0][2] * photo_copy->G[i - 1][j + 1];
	green += kernel[1][0] * photo_copy->G[i][j - 1];
	green += kernel[1][1] * photo_copy->G[i][j];
	green += kernel[1][2] * photo_copy->G[i][j + 1];
	green += kernel[2][0] * photo_copy->G[i + 1][j - 1];
	green += kernel[2][1] * photo_copy->G[i + 1][j];
	green += kernel[2][2] * photo_copy->G[i + 1][j + 1];
	green = clamp(green / 10000);
	return green;
}

// function for multiplying the blue pixel with the given kernel

double kernel_blue(pixmap *photo_copy, double kernel[3][3], int i, int j)
{
	double blue = 0.0;
	blue += kernel[0][0] * photo_copy->B[i - 1][j - 1];
	blue += kernel[0][1] * photo_copy->B[i - 1][j];
	blue += kernel[0][2] * photo_copy->B[i - 1][j + 1];
	blue += kernel[1][0] * photo_copy->B[i][j - 1];
	blue += kernel[1][1] * photo_copy->B[i][j];
	blue += kernel[1][2] * photo_copy->B[i][j + 1];
	blue += kernel[2][0] * photo_copy->B[i + 1][j - 1];
	blue += kernel[2][1] * photo_copy->B[i + 1][j];
	blue += kernel[2][2] * photo_copy->B[i + 1][j + 1];
	blue = clamp(blue / 10000);
	return blue;
}

// creating a function for each filter

void apply_edge_filter(pixmap *photo, int *applied)
{
	pixmap photo_copy;
	*applied = 0;
	photo_copy = *photo;
	alloc_matrix(photo);

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++) {
			photo->R[i][j] = photo_copy.R[i][j];
			photo->G[i][j] = photo_copy.G[i][j];
			photo->B[i][j] = photo_copy.B[i][j];
		}
	}
	double edge[3][3] = {{-10000, -10000, -10000},
						 {-10000, 80000, -10000},
						 {-10000, -10000, -10000}};

	// assiging each pixel its new value after applying the filter

	for (int i = photo->y1; i < photo->y2; i++) {
		for (int j = photo->x1; j < photo->x2; j++) {
			if (i != 0 && j != 0 && i != photo->height - 1 &&
				j != photo->width - 1) {
				photo->R[i][j] = kernel_red(&photo_copy, edge, i, j);
				photo->G[i][j] = kernel_green(&photo_copy, edge, i, j);
				photo->B[i][j] = kernel_blue(&photo_copy, edge, i, j);
				*applied = 1;
			}
		}
	}
	free_mem_RGB(&photo_copy);
}

void apply_sharpen_filter(pixmap *photo, int *applied)
{
	pixmap photo_copy;
	*applied = 0;
	photo_copy = *photo;
	alloc_matrix(photo);
	double sharpen[3][3] = {{0, -10000, 0},
							{-10000, 50000, -10000},
							{0, -10000, 0}};

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++) {
			photo->R[i][j] = photo_copy.R[i][j];
			photo->G[i][j] = photo_copy.G[i][j];
			photo->B[i][j] = photo_copy.B[i][j];
		}
	}

	for (int i = photo->y1; i < photo->y2; i++) {
		for (int j = photo->x1; j < photo->x2; j++) {
			if (i != 0 && j != 0 && i != photo->height - 1 &&
				j != photo->width - 1) {
				photo->R[i][j] = kernel_red(&photo_copy, sharpen, i, j);
				photo->G[i][j] = kernel_green(&photo_copy, sharpen, i, j);
				photo->B[i][j] = kernel_blue(&photo_copy, sharpen, i, j);
				*applied = 1;
			}
		}
	}
	free_mem_RGB(&photo_copy);
}

void apply_blur_filter(pixmap *photo, int *applied)
{
	pixmap photo_copy;
	*applied = 0;
	photo_copy = *photo;
	alloc_matrix(photo);
	double b = 1111;
	double blur[3][3] = {{b, b, b}, {b, b, b}, {b, b, b}};

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++) {
			photo->R[i][j] = photo_copy.R[i][j];
			photo->G[i][j] = photo_copy.G[i][j];
			photo->B[i][j] = photo_copy.B[i][j];
		}
	}

	for (int i = photo->y1; i < photo->y2; i++) {
		for (int j = photo->x1; j < photo->x2; j++) {
			if (i != 0 && j != 0 && i != photo->height - 1 &&
				j != photo->width - 1) {
				photo->R[i][j] = kernel_red(&photo_copy, blur, i, j);
				photo->G[i][j] = kernel_green(&photo_copy, blur, i, j);
				photo->B[i][j] = kernel_blue(&photo_copy, blur, i, j);
				*applied = 1;
			}
		}
	}

	free_mem_RGB(&photo_copy);
}

void apply_gaussian_blur_filter(pixmap *photo, int *applied)
{
	pixmap photo_copy;
	*applied = 0;
	photo_copy = *photo;
	alloc_matrix(photo);
	double g = 625, g2 = 1250;
	double g_blur[3][3] = {{g, g2, g}, {g2, 4.0 * g, g2}, {g, g2, g}};

	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++) {
			photo->R[i][j] = photo_copy.R[i][j];
			photo->G[i][j] = photo_copy.G[i][j];
			photo->B[i][j] = photo_copy.B[i][j];
		}
	}

	for (int i = photo->y1; i < photo->y2; i++) {
		for (int j = photo->x1; j < photo->x2; j++) {
			if (i != 0 && j != 0 && i != photo->height - 1 &&
				j != photo->width - 1) {
				photo->R[i][j] = kernel_red(&photo_copy, g_blur, i, j);
				photo->G[i][j] = kernel_green(&photo_copy, g_blur, i, j);
				photo->B[i][j] = kernel_blue(&photo_copy, g_blur, i, j);
				*applied = 1;
			}
		}
	}
	free_mem_RGB(&photo_copy);
}

void apply_command(pixmap *photo)
{
	int applied;
	char filter[F_MAX], filter_copy[F_MAX], *ptr;
	int ok;

	// reading the filter name

	fgets(filter, F_MAX - 1, stdin);
	ptr = strtok(filter + 1, "\n ");
	if (ptr)
		strcpy(filter_copy, ptr);
	check_invalid_args_for_apply(&ok, filter_copy);
	if (ok == 1 && photo->color == 1) { // the apply argument is valid
		if (strcmp(filter_copy, "EDGE") == 0) {
			apply_edge_filter(photo, &applied);
			if (applied == 1)
				printf("APPLY %s done\n", filter_copy);
		} else if (strcmp(filter_copy, "SHARPEN") == 0) {
			apply_sharpen_filter(photo, &applied);
			if (applied == 1)
				printf("APPLY %s done\n", filter_copy);
		} else if (strcmp(filter_copy, "BLUR") == 0) {
			apply_blur_filter(photo, &applied);
			if (applied == 1)
				printf("APPLY %s done\n", filter_copy);
		} else if (strcmp(filter_copy, "GAUSSIAN_BLUR") == 0) {
			apply_gaussian_blur_filter(photo, &applied);
			if (applied == 1)
				printf("APPLY %s done\n", filter_copy);
		}
	} else if (ok == -1) {
		printf("Invalid command\n");
	} else if (ok == 0) {
		printf("APPLY parameter invalid\n");
	} else if (photo->color == 0) { // if the loaded image is grayscale
		printf("Easy, Charlie Chaplin\n");
	}
}
