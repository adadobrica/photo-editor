// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#pragma once
#define S_MAX 4

typedef struct {
	unsigned int **g_scale;
	unsigned int **R, **G, **B;
	int width, height, color, x1, x2, y1, y2;
	int maxval;
	char magic_word[S_MAX];
} pixmap;
