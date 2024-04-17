#include <stdio.h>
#include "../libs/libbmp.h"

void byteToBinary(unsigned char byte, char* binary) {
	int i;
	for (i = 7; i >= 0; --i) {
		binary[7 - i] = (byte & (1 << i)) ? '1' : '0';
	}
	binary[8] = '\0';
}

unsigned char bitsToByte(char bits[]) {
	unsigned char byte = 0;
	int i;
	for (i = 0; i < 8; i++) {
		if (bits[i] == '1') {
			byte |= (1 << (7 - i)); // Definir o bit correspondente em byte
		} else if (bits[i] != '0') {
			// Se o caractere não for '0' nem '1', indicando um erro
			printf("Erro: O array de bits contém caracteres inválidos.\n");
			return 0; // Ou retorne um valor que indique erro
		}
	}
	return byte;
}

// recuperar dado da imagem
void rread(bmp_img img) {
	// Ler a imagem BMP recém-criada
	bmp_img_read(&img, "triangulo.bmp");
	int j = 0;
	printf("\nrecovered data\n");
	char bits[9];
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

int main(int argc, char* argv[])
{
	bmp_img img;
	bmp_img_init_df(&img, 512, 512);// define o tamanho da imagem
	FILE* file;

	unsigned char byte;
	char binary[9]; // 8 bits + 1 para o caractere nulo
	int i;

	// Abrir o arquivo binário para leitura
	file = fopen("arquivo.txt", "rb");
	if (file == NULL) {
		perror("Erro ao abrir o arquivo");
		return 1;
	}

	// pinta a imagem de vermelho
	for (size_t y = 0; y < 512; y++) {
		for (size_t x = 0; x < 512; x++) {
			bmp_pixel_init(&img.img_pixels[y][x], 255, 0, 0);
		}
	}


	wread(byte, file, binary, img); // lê os dados de file em binario e converte para .bmp
	fclose(file);
	rread(img); // recupera os dados da imagem 


	return 0;
}
