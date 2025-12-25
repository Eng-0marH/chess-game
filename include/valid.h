#ifndef VALID_H
#define VALID_H

#include <stdlib.h>
#include <ctype.h>

int Bishop(char B[8][8], int row1, int column1, int row2, int column2);

int Pawn(char B[8][8], int row1, int column1, int row2, int column2);

int Promotion(char b[8][8],int r1,int c1,int r2,int c2,char turn);

int Rook(char B[8][8], int row1, int column1, int row2, int column2);

int Queen(char B[8][8], int row1, int column1, int row2, int column2);

int Knight(char B[8][8], int row1, int column1, int row2, int column2);

int King(char B[8][8], int row1, int column1, int row2, int column2);

int whitecastle(char b[8][8],int r2,int c2);

int blackcastle(char b[8][8],int r2,int c2);

int isValid(char b[8][8],int r1,int c1,int r2,int c2,char prom,char turn,int *validprom);

#endif