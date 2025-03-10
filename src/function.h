// FUNCTION LIBRARY

#ifndef FILE_H
#define FILE_H

// Inclusão de bibliotecas necessárias
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <opencv2/opencv.hpp> // Biblioteca OpenCV para processamento de vídeo e imagens
// #include <opencv4/opencv2/opencv.hpp> // Alternativa para OpenCV 4
#include <filesystem> // Biblioteca para manipulação de arquivos e diretórios
#include <cstdio>
#include "./libs/libbmp.h" // Biblioteca para manipulação de arquivos BMP

// Definições de constantes
#define X 512 // Largura da imagem (em pixels)
#define Y 512 // Altura da imagem (em pixels)
#define R1 255 // Valor do canal vermelho para pixels "1" (branco)
#define G1 255 // Valor do canal verde para pixels "1" (branco)
#define B1 255 // Valor do canal azul para pixels "1" (branco)

#define R0 0 // Valor do canal vermelho para pixels "0" (preto)
#define G0 0 // Valor do canal verde para pixels "0" (preto)
#define B0 0 // Valor do canal azul para pixels "0" (preto)
#define N 9 // Tamanho do array de bits (8 bits + terminador nulo)
#define UM 1 // Valor usado no switch case para codificação
#define DOIS 2 // Valor usado no switch case para decodificação

// Namespaces para simplificar o código
using namespace std;
using namespace cv;

// Definições de caminhos e constantes para arquivos e diretórios
const string outputVideo = "./encodedVideo/"; // Diretório para salvar o vídeo gerado
const string videoFileExtension = "generatedVideo.avi"; // Nome do arquivo de vídeo gerado
const string generatedOutputDir = "./recoveredFiles/"; // Diretório para salvar frames recuperados
const string extension = ".bmp"; // Extensão dos arquivos de imagem BMP
const string encodedPath = "./encodedFiles/"; // Diretório para salvar imagens codificadas
const string decodedPath = "./decodedFiles/"; // Diretório para salvar arquivos decodificados
const string imageFileName = "imagem"; // Nome base dos arquivos de imagem
const int framesPerImage = 1; // Número de frames por imagem (não utilizado atualmente)

// Protótipos de funções

// Função para gerar uma sequência de imagens BMP a partir de um vídeo
void generateBMPSequence(string videoPath);

// Função para gerar um vídeo a partir de imagens BMP
void generateVideo();

// Função para converter um byte em sua representação binária
void byteToBinary(unsigned char byte, char* binary);

// Função para converter uma sequência de bits em um byte
unsigned char bitsToByte(char bits[]);

// Função para ler pixels de uma imagem BMP e extrair dados para um arquivo
void rread(BmpImg& img, string outputPath);

// Função para ler um arquivo byte a byte e codificar os dados em uma imagem BMP
void wread(BmpImg& img, string inputPath);

// Função para desenhar uma imagem BMP (pinta toda a imagem de verde)
void drawImg(BmpImg& img);

// Função para lidar com a entrada do usuário e abrir um arquivo
string openFile(int i);

#endif  // FILE_H