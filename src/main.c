#include <stdio.h>
#include "../libs/libbmp.h"

void byteToBinary(unsigned char byte, char* binary) {
	int i;
	for (i = 7; i >= 0; --i) {
		binary[7 - i] = (byte & (1 << i)) ? '1' : '0'; // movimenta o numero 1, n casas para a esquerda e faz um AND com o byte, se verdadeiro, bynary recebe 1, se falso 0
	}
	binary[8] = '\0';
}

unsigned char bitsToByte(char bits[]) {
	unsigned char byte = 0;
	int i;

	for (i = 0; i < 8; i++) {
		if (bits[i] == '1') {
			byte |= (1 << (7 - i)); // Definir o bit como 1
		} else if (bits[i] == '0') {
			// Definir o bit como 0
			byte &= ~(1 << (7 - i)); // Inverter o bit correspondente
		} else {
			// Caractere inválido
			printf("Erro: O array de bits contém caracteres inválidos.\n");
			return 0; // Ou retorne um valor que indique erro
		}
	}

	return byte;
}

// recuperar dado da imagem
void rread(bmp_img img, FILE* arquivo) {
	// Ler a imagem BMP recém-criada
	bmp_img_read(&img, "triangulo.bmp");
	int j = 0;
	printf("\nrecovered data\n");
	char bits[9];
	unsigned char byte; // Variável para armazenar o byte convertido

	// Exemplo de acesso aos pixels da imagem
	for (size_t y = 0; y < 512; y++) {
		for (size_t x = 0; x < 512; x++) {
			unsigned char r = img.img_pixels[y][x].red;
			unsigned char g = img.img_pixels[y][x].green;
			unsigned char b = img.img_pixels[y][x].blue;
			// printf("Pixel (%zu,%zu): R=%u, G=%u, B=%u\n", y, x, r, g, b);
			// Se o pixel for preto ou branco, imprimir seus dados
			if ((r == 0 && g == 0 && b == 0) || (r == 250 && g == 250 && b == 250)) {
				if (r == 0) {
					bits[j] = '0';
				} else {
					bits[j] = '1';
				}
				j++;
			}
			
			if (j == 8) {
				bits[j] = '\0'; // Adiciona terminador de string
				printf("%s\n", bits);
				j = 0;
				byte = bitsToByte(bits);
				// Escrever o byte no arquivo
				if (fwrite(&byte, sizeof(char), 1, arquivo) != 1) {
					printf("Erro: Falha ao escrever o byte no arquivo.\n");
					fclose(arquivo);
					return 1;
				}
			}
		}
	}
	
	printf("\n");
}

void wread(char byte, FILE* file, char* binary, bmp_img img) {
	int y = 0;
	int x = 0;
	// Ler o arquivo byte a byte e imprimir sua representação binária
	while (fread(&byte, sizeof(unsigned char), 1, file) == 1) {
		byteToBinary(byte, binary);
		printf("%s \n", binary);
		for (size_t i = 0; i < sizeof(binary); i++)
		{
			if (y == 510)
			{
				exit(0);
			}

			if (x == 510)
			{
				y++;
				x = 0;
			}
			if (binary[i] == '1')
			{
				bmp_pixel_init(&img.img_pixels[y][x], 250, 250, 250);
			} else
			{
				bmp_pixel_init(&img.img_pixels[y][x], 0, 0, 0);
			}
			x++;
		}
	}
	// Fechar o arquivo

	bmp_img_write(&img, "triangulo.bmp");
	bmp_img_free(&img);
}

void drawImg(bmp_img img) {
	// pinta a imagem de vermelho
	for (size_t y = 0; y < 512; y++) {
		for (size_t x = 0; x < 512; x++) {
			bmp_pixel_init(&img.img_pixels[y][x], 255, 0, 0);
		}
	}
}

int main(int argc, char* argv[]) {
	bmp_img img;
	bmp_img_init_df(&img, 512, 512);// define o tamanho da imagem
	FILE* file;

	unsigned char byte;
	char binary[9]; // 8 bits + 1 para o caractere nulo
	int i;
	int opcao;
	char entrada[1000]; // Array para armazenar a entrada do usuário

	drawImg(img);

	// Apresenta o menu de opções
	printf("Escolha uma opção:\n");
	printf("1. Criar imagem bmp\n");
	printf("2. Recuperar dados da imagem\n");
	printf("0. Sair\n");

	// Captura a entrada do usuário
	printf("Digite o número da opção desejada: ");
	scanf("%d", &opcao);

	while (getchar() != '\n');
	// Verifica a opção escolhida pelo usuário
	switch (opcao) {
		case 1:
			printf("Você escolheu a opção 1.\n");
			printf("Digite o nome do arquivo\n");
			// Captura a entrada do usuário até que o usuário pressione Enter
			fgets(entrada, sizeof(entrada), stdin);
			entrada[strcspn(entrada, "\n")] = '\0';
			// Abrir o arquivo binário para leitura
			file = fopen(&entrada, "rb");
			if (file == NULL) {
				perror("Erro ao abrir o arquivo");
				return 1;
			}
			wread(byte, file, binary, img); // lê os dados de file em binario e converte para .bmp
			fclose(file);
			break;
		case 2:
			printf("Você escolheu a opção 2.\n");
			printf("Digite o nome do arquivo\n");
			// Captura a entrada do usuário até que o usuário pressione Enter
			fgets(entrada, sizeof(entrada), stdin);
			entrada[strcspn(entrada, "\n")] = '\0';
			// Abrir o arquivo binário para leitura
			file = fopen(&entrada, "wb");
			if (file == NULL) {
				perror("Erro ao abrir o arquivo");
				return 1;
			}
			rread(img, file); // recupera os dados da imagem 
			fclose(file);
			break;
		case 0:
			printf("Saindo do programa...\n");
			return 0; // Encerra o programa
		default:
			printf("Opção inválida\n");
			break;
	}

	// wread(byte, file, binary, img); // lê os dados de file em binario e converte para .bmp
	// fclose(file);
	// rread(img); // recupera os dados da imagem 

	return 0;
}
