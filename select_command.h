// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pixmap.h"
#include "utils.h"

void swap(int *x, int *y);
int check_letter(char *check);
void check_arg_sel(pixmap *photo, int *num, int *x1_copy, int *select, int *k);
void select_command(pixmap *photo);
