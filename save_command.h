#pragma once
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "pixmap.h"

void print_matrix_ascii(pixmap * photo, FILE * fout);
void print_matrix_binary(pixmap *photo, FILE *fout);
int get_arguments_save(char *name);
void save_command(pixmap *photo, int ascii, char *name);
