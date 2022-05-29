// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "pixmap.h"
#include "utils.h"
#include "select_command.h"

int check_selection(int ok, pixmap * photo);
void rotate90_left_all(pixmap *photo);
void rotate90_left_square(pixmap *photo);
void rotate_command(pixmap *photo);
