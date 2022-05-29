// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pixmap.h"
#include "utils.h"

double clamp(double x);
void check_invalid_args_for_apply(int *ok, char *filter);
double kernel_red(pixmap *photo_copy, double kernel[3][3], int i, int j);
double kernel_green(pixmap *photo_copy, double kernel[3][3], int i, int j);
double kernel_blue(pixmap *photo_copy, double kernel[3][3], int i, int j);
void apply_edge_filter(pixmap *photo, int *applied);
void apply_sharpen_filter(pixmap *photo, int *applied);
void apply_blur_filter(pixmap *photo, int *applied);
void apply_gaussian_blur_filter(pixmap *photo, int *applied);
void apply_command(pixmap *photo);
