// FUNCTION LIBRARY

#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <cstdio>
#include "./libs/libbmp.h"


#define X 512 // largura da imagem
#define Y 512 // altura da imagem
#define R1 255
#define G1 255
#define B1 255

#define R0 0
#define G0 0
#define B0 0
#define N 9 // tamanho do byte
#define UM 1 // valor usado no switch case para codificacao
#define DOIS 2 // valor usado no switch case para decodificacao

using namespace std;
using namespace cv;

const string outputVideo = "./encodedFiles/output.mp4";
const string directory = "encodedFiles/";
const string outputDirectory = "encodedFiles/";
const int framesPerImage = 1;

void generateBMPSequence(string videoPath);

void generateVideo();

void byteToBinary(unsigned char byte, char* binary);

unsigned char bitsToByte(char bits[]);

void rread(BmpImg& img, string outputPath);

void wread(BmpImg& img, string inputPath);

void drawImg(BmpImg& img);

string openFile(int i);

#endif  // FILE_H