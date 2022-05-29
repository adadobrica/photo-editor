// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "pixmap.h"
#define S_MAX 4

// checking if the photo is binary or ascii

int check_type(char *word)
{
	// 0 -> binary
	// 1 -> text

	int ok;
	if (strcmp(word, "P2") == 0 || strcmp(word, "P3") == 0)
		ok = 1;
	else if (strcmp(word, "P5") == 0 || strcmp(word, "P6") == 0)
		ok = 0;
	return ok;
}

// reading the grayscale photo in ascii

void read_matrix_for_gscale(pixmap *photo, FILE *fin)
{
	for (int i = 0; i < photo->height; i++)
		for (int j = 0; j < photo->width; j++) {
			fscanf(fin, "%d", &photo->g_scale[i][j]);
			photo->g_scale[i][j] *= 1000;
		}
}

// reading the RGB photo in ascii

void read_matrix_for_RGB(pixmap *photo, FILE *fin)
{
	for (int i = 0; i < photo->height; i++)
		for (int j = 0; j < photo->width; j++) {
			fscanf(fin, "%d", &photo->R[i][j]);
			fscanf(fin, "%d", &photo->G[i][j]);
			fscanf(fin, "%d", &photo->B[i][j]);
			photo->R[i][j] *= 1000;
			photo->G[i][j] *= 1000;
			photo->B[i][j] *= 1000;
		}
}

// reading the grayscale photo in binary

void read_binary_mat_gscale(pixmap *photo, FILE *fin)
{
	for (int i = 0; i < photo->height; i++)
		for (int j = 0; j < photo->width; j++) {
			fread(&photo->g_scale[i][j], sizeof(char), 1, fin);
			photo->g_scale[i][j] *= 1000;
		}
}

// reading the RGB photo in binary

void read_binary_mat_RGB(pixmap *photo, FILE *fin)
{
	for (int i = 0; i < photo->height; i++)
		for (int j = 0; j < photo->width; j++) {
			fread(&photo->R[i][j], sizeof(char), 1, fin);
			fread(&photo->G[i][j], sizeof(char), 1, fin);
			fread(&photo->B[i][j], sizeof(char), 1, fin);
			photo->R[i][j] *= 1000;
			photo->G[i][j] *= 1000;
			photo->B[i][j] *= 1000;
		}
}

// function to load into memory the ascii file

void load_text_file(FILE *fin, pixmap *photo, char *f_name)
{
	alloc_matrix(photo); // allocating memory for the image

	// reading either the RGB or grayscale image according to its type

	if (photo->color == 1)
		read_matrix_for_RGB(photo, fin);
	else
		read_matrix_for_gscale(photo, fin);

	printf("Loaded %s\n", f_name);
}

// function to load into memory the binary file

void load_binary_file(FILE *fin, int *pos, pixmap *photo)
{
	// using fseek to find the position where the ascii characters stopped
	// so that we can read the binary characters

	fseek(fin, *pos + 1, SEEK_SET);

	alloc_matrix(photo);

	if (photo->color == 1)
		read_binary_mat_RGB(photo, fin);
	else
		read_binary_mat_gscale(photo, fin);
}

void load_command(char *f_name, pixmap *photo, int *loaded)
{
	char m_word[S_MAX];

	// if the image is already loaded, we free it from memory

	if (*loaded == 1 && photo->color == 1)
		free_mem_RGB(photo);
	else if (*loaded == 1 && photo->color == 0)
		free_mem_gscale(photo);

	// opening a text file

	FILE *fin = fopen(f_name, "rt");

	if (!fin) {
		*loaded = 0;
		fprintf(stdout, "Failed to load %s\n", f_name);
		return;
	}

	// photo->color = 0 -> grayscale
	// photo->color = 1 -> RBG

	fscanf(fin, "%s", m_word);

	strcpy(photo->magic_word, m_word);

	if (strcmp(m_word, "P2") == 0 || strcmp(m_word, "P5") == 0)
		photo->color = 0;
	if (strcmp(m_word, "P3") == 0 || strcmp(m_word, "P6") == 0)
		photo->color = 1;

	fscanf(fin, "%d%d%d", &photo->width, &photo->height, &photo->maxval);

	int ok = check_type(m_word);
	int position = ftell(fin);

	if (ok == 1) {
		load_text_file(fin, photo, f_name);
		// selecting the entire image after loading it
		photo->x1 = 0;
		photo->y1 = 0;
		photo->x2 = photo->width;
		photo->y2 = photo->height;
		fclose(fin);
	} else if (ok == 0) {
		fclose(fin);
		fin = fopen(f_name, "rb");

		if (!fin) {
			fprintf(stdout, "Failed to load %s\n", f_name);
			return;
		}
		fprintf(stdout, "Loaded %s\n", f_name);
		load_binary_file(fin, &position, photo);
		photo->x1 = 0;
		photo->y1 = 0;
		photo->x2 = photo->width;
		photo->y2 = photo->height;
		fclose(fin);
	} else {
		printf("Cannot load %s", f_name);
	}

	*loaded = 1;
}
