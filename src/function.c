#include "function.h"

// Converte um byte em sua representação binária
void byteToBinary(unsigned char byte, char* binary) {
    int i;
    for (i = 7; i >= 0; --i) {
        binary[7 - i] = (byte & (1 << i)) ? '1' : '0'; // Desloca o número 1 'i' casas para a esquerda e faz um AND com o byte; se verdadeiro, binary recebe '1', senão, '0'
    }
    binary[8] = '\0'; // Adiciona um terminador de string ao final do array
}

// Converte uma sequência de bits em um byte
unsigned char bitsToByte(char bits[]) {
    unsigned char byte = 0;
    int i;

    for (i = 0; i < 8; i++) {
        if (bits[i] == '1') {
            byte |= (1 << (7 - i)); // Define o bit como '1'
        } else if (bits[i] == '0') {
            byte &= ~(1 << (7 - i)); // Define o bit como '0' (inverte o bit correspondente)
        } else {
            printf("Erro: O array de bits contém caracteres inválidos.\n");
            return 0; // Retorna um valor que indica erro em caso de caracteres inválidos
        }
    }
    return byte;
}

// Lê os pixels de uma imagem BMP e extrai os dados para formar um byte, escrevendo esse byte em um arquivo
void rread(bmp_img img, FILE* arquivo) {
    int j = 0;
    char bits[N];
    unsigned char byte; // Variável para armazenar o byte convertido

    // Lê a imagem BMP fornecida
    bmp_img_read(&img, "./assets/imagem.bmp");

    // Exemplo de acesso aos pixels da imagem
    for (size_t y = 0; y < Y; y++) {
        for (size_t x = 0; x < X; x++) {
            unsigned char r = img.img_pixels[y][x].red;
            unsigned char g = img.img_pixels[y][x].green;
            unsigned char b = img.img_pixels[y][x].blue;
            // Se o pixel for preto ou branco, extrai o bit correspondente
            if ((r == 0 && g == 0 && b == 0) || (r == 250 && g == 250 && b == 250)) {
                if (r == 0) {
                    bits[j] = '0';
                } else {
                    bits[j] = '1';
                }
                j++;
            }

            if (j == 8) {
                bits[j] = '\0'; // Adiciona um terminador de string
                j = 0;
                byte = bitsToByte(bits);
                // Escreve o byte no arquivo
                if (fwrite(&byte, sizeof(char), 1, arquivo) != 1) {
                    printf("Erro: Falha ao escrever o byte no arquivo.\n");
                    fclose(arquivo);
                    return 1;
                }
            }
        }
    }
}

// Lê um arquivo byte a byte, converte cada byte em uma sequência de bits e desenha uma imagem com base nesses bits
void wread(char byte, FILE* file, char* binary, bmp_img img) {
    int y = 0;
    int x = 0;
    // Lê o arquivo byte a byte e converte cada byte em sua representação binária
    while (fread(&byte, sizeof(unsigned char), 1, file) == 1) {
        byteToBinary(byte, binary);
        for (size_t i = 0; i < sizeof(binary); i++) {
            // Limita a quantidade máxima de pixels a 510x510
            if (y == Y - 2) {
                exit(0);
            }

            if (x == X - 2) {
                y++;
                x = 0;
            }
            if (binary[i] == '1') {
                bmp_pixel_init(&img.img_pixels[y][x], 250, 250, 250); // Define o pixel como branco
            } else {
                bmp_pixel_init(&img.img_pixels[y][x], 0, 0, 0); // Define o pixel como preto
            }
            x++;
        }
    }
    // Escreve a imagem BMP resultante no arquivo
    bmp_img_write(&img, "./assets/imagem.bmp");
    bmp_img_free(&img);
}

// Pinta toda a imagem de vermelho
void drawImg(bmp_img img) {
    for (size_t y = 0; y < Y; y++) {
        for (size_t x = 0; x < X; x++) {
            bmp_pixel_init(&img.img_pixels[y][x], 255, 0, 0); // Define o pixel como vermelho
        }
    }
}

// Função para lidar com a entrada do usuário e a abertura do arquivo
FILE* openFile(int i) {
    FILE* file;
    char entrada[100];
    printf("Digite o caminho do arquivo com a extensao: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // Remove o caractere de nova linha do final da entrada

    // Abre o arquivo no modo especificado
    if (i == 1) {
        file = fopen(&entrada, "rb");
    } else {
        file = fopen(&entrada, "wb");
    }

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    return file;
}
