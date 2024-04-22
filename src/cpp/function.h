// FUNCTION LIBRARY

#ifndef FILE_H
#define FILE_H
#define X 512 // largura da imagem
#define Y 512 // altura da imagem
#define N 9 // tamanho do byte
#define UM 1 // valor usado no switch case para codificacao
#define DOIS 2 // valor usado no switch case para decodificacao

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <opencv2/opencv.hpp>

#include "./libs/libbmp.h"

using namespace std;
using namespace cv;

void byteToBinary(unsigned char byte, char* binary);

unsigned char bitsToByte(char bits[]);

void rread(BmpImg& img, string outputPath);

void wread(BmpImg& img, string inputPath);

void drawImg(BmpImg& img);

string openFile(int i);

#endif  // FILE_H