#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <ctype.h>

void captured(char c[16]);

void Board(char b[8][8]);

void showBoard(char b[8][8],char captureW[],char captureB[]);

#endif