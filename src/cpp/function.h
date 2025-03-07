// FUNCTION LIBRARY

#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <opencv2/opencv.hpp>
// #include <opencv4/opencv2/opencv.hpp>
#include <filesystem>
#include <cstdio>
#include "./libs/libbmp.h"


#define X 1920 // largura da imagem
#define Y 1080 // altura da imagem
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

const string outputVideo = "./encodedVideo/";
const string videoFileExtension = "generatedVideo.avi";
const string generatedOutputDir = "./recoveredFiles/";
const string extension = ".bmp";
const string encodedPath = "./encodedFiles/";
const string decodedPath = "./decodedFiles/";
const string imageFileName = "imagem";
const int framesPerImage = 1;

bool isGrayScale(char r, char g, char b);

void generateBMPSequence(string videoPath);

vector<Mat> generateBMPSequenceInMemory(string videoPath);

// void generateBMPTeste(string videoPath);

// void generateVideoTeste();

void generateVideo();

void byteToBinary(unsigned char byte, char* binary);

unsigned char bitsToByte(char bits[]);

void rread(BmpImg& img, string outputPath);

// void rread(Mat& img, const Mat& inputFrame, string outputPath);

void wread(BmpImg& img, string inputPath);

void drawImg(BmpImg& img);

string openFile(int i);

#endif  // FILE_H
