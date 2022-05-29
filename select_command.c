// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pixmap.h"
#include "utils.h"
#define COORD_MAX 40
#define S_MAX 4

// function to swap two integers

void swap(int *x, int *y)
{
	int aux = *x;
	*x = *y;
	*y = aux;
}

// function to check if the argument for selection contains letters

int check_letter(char *check)
{
	int cnt = 0, lett = 0;
	int len = strlen(check);

	for (int i = 0; i < len; i++)
		if (isdigit(check[i]) != 0)
			cnt++;

	if (cnt)
		lett = 0;
	else
		lett = 1;
	return lett;
}

// checking if all of the arguments for selection are valid

void check_arg_sel(pixmap *photo, int *num, int *x1_copy, int *select, int *k)
{
	char coord[COORD_MAX];
	*select = 0;
	int x2_copy, y1_copy, y2_copy;
	*k = -1;

	// reading the coordinates

	fgets(coord, COORD_MAX, stdin);

	int cnt = 0, lett;
	char *p;

	p = strtok(coord, "\n ");
	while (p) {
		// if any of the remaining 3 coordinates have letters
		// there isn't any point in checking further

		lett = check_letter(p);
		if (lett == 1) {
			*k = -1;
			break;
		}
		cnt++;

		// using the atoi function to convert the string argument to type int

		if (cnt == 1)
			y1_copy = atoi(p);
		if (cnt == 2)
			x2_copy = atoi(p);
		if (cnt == 3)
			y2_copy = atoi(p);

		p = strtok(NULL, "\n ");
	}

	if (cnt == 3) {
		if (x2_copy > photo->width || y1_copy > photo->height || y2_copy >
			photo->height || x2_copy < 0 || y1_copy < 0 || y2_copy < 0) {
			printf("Invalid set of coordinates\n");
			*k = 0;
			return;

		} else if (*x1_copy == x2_copy || y1_copy == y2_copy) {
			printf("Invalid set of coordinates\n");
			*k = 0;
			return;
		}

		// if the coordinates are valid, we assign them to the image

		photo->x1 = *x1_copy;
		photo->y1 = y1_copy;
		photo->x2 = x2_copy;
		photo->y2 = y2_copy;

		if (photo->x1 > photo->x2)
			swap(&photo->x1, &photo->x2);

		if (photo->y1 > photo->y2)
			swap(&photo->y1, &photo->y2);

		*select = 1;
		*k = 1;
	}
	*num = cnt;
}

void select_command(pixmap *photo)
{
	int x1_copy, num = 0, ok = -1, lett;
	char check[S_MAX + 1], garbage[100];
	int select = 0;

	scanf("%s", check);
	if (strcmp(check, "ALL") == 0)
		lett = 0;
	else
		lett = check_letter(check);

	// reading the rest of the characters if the coordinates contain letters

	if (lett == 1) {
		fgets(garbage, 99, stdin);
		printf("Invalid command\n");
	} else {
		if (strcmp(check, "ALL") == 0) {
			photo->x1 = 0;
			photo->y1 = 0;
			photo->x2 = photo->width;
			photo->y2 = photo->height;
			printf("Selected ALL\n");
		} else {
			// converting the first character into integer
			// if it's not valid, there's no point in checking the other coord
			x1_copy = atoi(check);
			if (x1_copy > photo->width || x1_copy < 0) {
				fgets(garbage, 99, stdin);
				printf("Invalid set of coordinates\n");
			} else {
				check_arg_sel(photo, &num, &x1_copy, &select, &ok);
				if (num >= 3 && ok) {
					if (select == 1) {
						printf("Selected %d %d", photo->x1, photo->y1);
						printf(" %d %d\n", photo->x2, photo->y2);
					}
				} else if (ok == -1) {
					printf("Invalid command\n");
				}
			}
		}
	}
}
