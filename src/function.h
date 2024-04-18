// FUNCTION LIBRARY

#ifndef FILE_H
#define FILE_H
#define X 512
#define Y 512
#define N 9

#include <stdio.h>
#include "../libs/libbmp.h"

void byteToBinary(unsigned char byte, char* binary);

unsigned char bitsToByte(char bits[]);

void rread(bmp_img img, FILE* arquivo);

void wread(char byte, FILE* file, char* binary, bmp_img img);

void drawImg(bmp_img img);

FILE* openFile(int i);

#endif  // FILE_H