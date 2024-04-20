// FUNCTION LIBRARY

#ifndef FILE_H
#define FILE_H
#define X 512
#define Y 512
#define N 9

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "./libs/libbmp.h"

using namespace std;

void byteToBinary(unsigned char byte, char* binary);

unsigned char bitsToByte(char bits[]);

void rread(BmpImg img, FILE* arquivo);

void wread(char byte, FILE* file, char* binary, BmpImg img);

void drawImg(BmpImg img);

FILE* openFile(int i);

#endif  // FILE_H