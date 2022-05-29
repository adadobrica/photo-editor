// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "pixmap.h"

int check_type(char *word);
void read_matrix_for_gscale(pixmap *photo, FILE *fin);
void read_matrix_for_RGB(pixmap *photo, FILE *fin);
void read_binary_mat_gscale(pixmap *photo, FILE *fin);
void read_binary_mat_RGB(pixmap *photo, FILE *fin);
void load_text_file(FILE *fin, pixmap *photo, char *f_name);
void load_binary_file(FILE *fin, int *pos, pixmap *photo);
void load_command(char *f_name, pixmap *photo, int *loaded);
