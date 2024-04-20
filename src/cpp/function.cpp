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
void rread(BmpImg img, FILE* arquivo) {
    int j = 0;
    char bits[N];
    unsigned char byte; // Variável para armazenar o byte convertido
    int k = 1;
    char nome_arquivo[30];

    while (1) {
        sprintf(nome_arquivo, "./encodedFiles/imagem%d.bmp", k);
        // Tenta abrir a próxima imagem gerada
        if (img.read(nome_arquivo) != BMP_OK) {
            break;  // Sai do loop se não houver mais imagens
        }
        // Exemplo de acesso aos pixels da imagem
        for (size_t y = 0; y < Y; y++) {
            for (size_t x = 0; x < X; x++) {
                unsigned char r = img.red_at(x,y);
                unsigned char g = img.green_at(x, y);
                unsigned char b = img.blue_at(x, y);
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
                        return;
                    }
                }
            }
        }
        // Fecha a imagem atual
        // bmp_img_free(&img);
        k++;
    }

}

// Lê um arquivo byte a byte, converte cada byte em uma sequência de bits e desenha uma imagem com base nesses bits
void wread(char byte, FILE* file, char* binary, BmpImg img) {
    int y = 0;
    int x = 0;
    int k = 1;
    char caminho[30];

    // Lê o arquivo byte a byte e converte cada byte em sua representação binária
    while (fread(&byte, sizeof(unsigned char), 1, file) == 1) {
        byteToBinary(byte, binary);
        for (size_t i = 0; i < sizeof(binary); i++) {
            // Limita a quantidade máxima de pixels a 510x510
            if (y == Y - 2) {
                sprintf(caminho, "./encodedFiles/imagem%d.bmp", k);
                img.write(caminho);
                y = 0;
                x = 0;
                k++;
                // exit(0);
            }

            if (x == X - 2) {
                y++;
                x = 0;
            }
            if (binary[i] == '1') {
                img.set_pixel(x , y, 250, 250, 250); // Define o pixel como branco
            } else {
                img.set_pixel(x , y, 0, 0, 0); // Define o pixel como preto
            }
            x++;
        }
    }

    sprintf(caminho, "./encodedFiles/imagem%d.bmp", k);
    img.write(caminho);

    // bmp_img_free(&img);
}

// Pinta toda a imagem de vermelho
void drawImg(BmpImg img) {
    for (size_t y = (Y - 1); y >= 0; y--) {
        for (size_t x = (X - 1); x >= 0; x--) {
            img.set_pixel(x, y, 255, 0, 0); // Define o pixel como vermelho
        }
    }
}

// Função para lidar com a entrada do usuário e a abertura do arquivo
FILE* openFile(int i) {
    FILE* file;
    char entrada[100];
    char entrada2[100];
    printf("Digite o nome do arquivo a ser decodificado com a extensao: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // Remove o caractere de nova linha do final da entrada

    // Abre o arquivo no modo especificado
    if (i == 1) {
        file = fopen(entrada, "rb");
    } else {
        sprintf(entrada2, "./decodedFiles/%s", &entrada);
        file = fopen(entrada2, "wb");
    }

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    return file;
}
