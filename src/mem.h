#ifndef MEM_H
#define MEM_H

// Inclusão de bibliotecas necessárias
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <opencv2/opencv.hpp> // Biblioteca OpenCV para processamento de vídeo e imagens
// #include <opencv4/opencv2/opencv.hpp> // Alternativa para OpenCV 4
#include <filesystem>
#include <cstdio>

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
const string decodedPath = "./decodedFiles/"; // Diretório para salvar arquivos decodificados

// Função para processar um vídeo e extrair dados diretamente para um arquivo
void processVideoToFile(const string& videoPath, const string& outputPath);

// Função unificada para gerar um vídeo diretamente a partir de um arquivo de entrada
void generateVideo(const string& inputPath);

// Função para converter um byte em sua representação binária
void byteToBinary(unsigned char byte, char* binary);

// Função para converter uma sequência de bits em um byte
unsigned char bitsToByte(char bits[]);

// Função para lidar com a entrada do usuário e abrir um arquivo
string openFile(int i);

#endif  // FILE_H