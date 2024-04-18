#include <stdio.h>
#include "../libs/libbmp.h"
#include "function.h"

int main(int argc, char* argv[]) {
	bmp_img img;
	bmp_img_init_df(&img, 512, 512);// define o tamanho da imagem
	FILE* file;

	unsigned char byte;
	char binary[9]; // 8 bits + 1 para o caractere nulo
	int opcao;

	drawImg(img);

	// Apresenta o menu de opções
	printf("Escolha uma opção:\n");
	printf("1. Codificar\n");
	printf("2. Decodificar\n");
	printf("0. Sair\n");

	// Captura a entrada do usuário
	printf("Digite o número da opção desejada: ");
	scanf("%d", &opcao);

	while (getchar() != '\n');
	// Verifica a opção escolhida pelo usuário
	switch (opcao) {
		case 1:
			printf("Você escolheu a opção 1.\n\n");
			file = openFile(opcao);
			wread(byte, file, binary, img); // lê os dados de file em binario e converte para .bmp
			printf("Codificado dados com sucesso!\n");
			fclose(file);
			break;
		case 2:
			printf("Você escolheu a opção 2.\n\n");
			file = openFile(opcao);
			rread(img, file); // recupera os dados da imagem 
			printf("Decodificado dados com sucesso!\n");
			fclose(file);
			break;
		case 0:
			printf("Saindo do programa...\n");
			return 0; // Encerra o programa
		default:
			printf("Opção inválida\n");
			break;
	}
	return 0;
}
