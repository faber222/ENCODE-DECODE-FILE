#include "function.h"

int main(int argc, char* argv[]) {
	bmp_img img;
	bmp_img_init_df(&img, X, Y); // Inicializa uma imagem BMP com tamanho 512x512
	FILE* file;

	unsigned char byte;
	char binary[N]; // Representação binária de 8 bits mais um para o caractere nulo
	int opcao;

	drawImg(img); // Desenha a imagem inicial

	// Apresenta o menu de opções para o usuário
	printf("Escolha uma opção:\n");
	printf("1. Codificar\n");
	printf("2. Decodificar\n");
	printf("0. Sair\n");

	// Captura a entrada do usuário
	printf("Digite o número da opção desejada: ");
	scanf("%d", &opcao);

	while (getchar() != '\n'); // Limpa o buffer do teclado

	// Verifica a opção escolhida pelo usuário
	switch (opcao) {
		case 1:
			printf("Você escolheu a opção 1.\n\n");
			file = openFile(opcao); // Abre o arquivo de entrada para codificação
			wread(byte, file, binary, img); // Lê os dados do arquivo em binário e os converte para o formato BMP
			printf("Dados codificados com sucesso!\n");
			fclose(file); // Fecha o arquivo de entrada
			break;
		case 2:
			printf("Você escolheu a opção 2.\n\n");
			file = openFile(opcao); // Abre o arquivo de entrada para decodificação
			rread(img, file); // Recupera os dados da imagem BMP
			printf("Dados decodificados com sucesso!\n");
			fclose(file); // Fecha o arquivo de entrada
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
