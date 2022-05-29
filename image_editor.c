// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "pixmap.h"
#include "utils.h"
#include "load_command.h"
#include "select_command.h"
#include "rotate_command.h"
#include "crop_command.h"
#include "apply_command.h"
#include "save_command.h"
#define S_MAX 4
#define C_MAX 10
#define F_MAX 256
#define COORD_MAX 40

int main(void)
{
	char command[C_MAX], f_name[F_MAX], name[F_MAX], garbage[100];
	int ok = 1, loaded = 0, type;
	pixmap photo;

	while (ok) {
		scanf("%s", command);
		if (strcmp(command, "LOAD") == 0) {
			scanf("%s", f_name);
			load_command(f_name, &photo, &loaded);
		} else if (strcmp(command, "SELECT") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
				fgets(garbage, 99, stdin);
			} else {
				select_command(&photo);
			}
		} else if (strcmp(command, "ROTATE") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
				fgets(garbage, 99, stdin);
			} else {
				rotate_command(&photo);
			}
		} else if (strcmp(command, "CROP") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
				fgets(garbage, 99, stdin);
			} else {
				crop_command(&photo);
			}
		} else if (strcmp(command, "APPLY") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
				fgets(garbage, 99, stdin);
			} else {
				apply_command(&photo);
			}
		} else if (strcmp(command, "SAVE") == 0) {
			if (loaded == 0) {
				printf("No image loaded\n");
				fgets(garbage, 99, stdin);
			} else {
				type = get_arguments_save(name);
				save_command(&photo, type, name);
			}
		} else if (strcmp(command, "EXIT") == 0) {
			ok = 0;
			if (loaded == 0)
				printf("No image loaded\n");
		} else {
			printf("Invalid command\n");
			char garbage[100];
			fgets(garbage, 99, stdin);
		}
	}

	if (loaded == 1) {
		if (photo.color == 1)
			free_mem_RGB(&photo);
		else
			free_mem_gscale(&photo);
	}
	return 0;
}
