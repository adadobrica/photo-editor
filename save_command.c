// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "pixmap.h"
#define F_MAX 256

void print_matrix_ascii(pixmap *photo, FILE *fout)
{
	for (int i = 0; i < photo->height; i++) {
		for (int j = 0; j < photo->width; j++)
			if (photo->color == 0) {
				unsigned char x = round(1.0 * photo->g_scale[i][j] / 1000);
				fprintf(fout, "%hhu ", x);
			} else {
				unsigned char x = round(1.0 * photo->R[i][j] / 1000);
				unsigned char y = round(1.0 * photo->G[i][j] / 1000);
				unsigned char z = round(1.0 * photo->B[i][j] / 1000);
				fprintf(fout, "%hhu ", x);
				fprintf(fout, "%hhu ", y);
				fprintf(fout, "%hhu ", z);
			}
		fprintf(fout, "\n");
	}
}

void print_matrix_binary(pixmap *photo, FILE *fout)
{
	for (int i = 0; i < photo->height; i++)
		for (int j = 0; j < photo->width; j++)
			if (photo->color == 0) {
				unsigned char x = round(1.0 * photo->g_scale[i][j] / 1000);
				fwrite(&x, sizeof(char), 1, fout);
			} else {
				unsigned char x = round(1.0 * photo->R[i][j] / 1000);
				unsigned char y = round(1.0 * photo->G[i][j] / 1000);
				unsigned char z = round(1.0 * photo->B[i][j] / 1000);
				fwrite(&x, sizeof(char), 1, fout);
				fwrite(&y, sizeof(char), 1, fout);
				fwrite(&z, sizeof(char), 1, fout);
			}
}

// function to get the arguments to save the file

int get_arguments_save(char *name)
{
	int ascii = 0;
	char args[F_MAX];
	fgets(args, F_MAX, stdin);
	char *p;

	// checking if the argument contains 'ascii'
	// so that the image can be saved as an ascii type

	if (strstr(args, "ascii"))
		ascii = 1;

	p = strtok(args, "\n ");
	strcpy(name, p);

	return ascii;
}

void save_command(pixmap *photo, int ascii, char *name)
{
	// firstly, we open the file as a text file

	FILE *fout = fopen(name, "wt");

	if (ascii == 1) {
		if (photo->color == 0)
			fprintf(fout, "P2\n");
		else
			fprintf(fout, "P3\n");
	} else {
		if (photo->color == 0)
			fprintf(fout, "P5\n");
		else
			fprintf(fout, "P6\n");
	}

	fprintf(fout, "%d %d\n", photo->width, photo->height);
	fprintf(fout, "%d\n", photo->maxval);

	if (ascii == 1) {
		print_matrix_ascii(photo, fout);
		printf("Saved %s\n", name);
		fclose(fout);
	} else {
		// if the image is not to be saved as ascii, we open the binary file
		// and close the text file
		fclose(fout);
		fout = fopen(name, "ab");
		print_matrix_binary(photo, fout);
		printf("Saved %s\n", name);
		fclose(fout);
	}
}
