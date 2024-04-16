#include <stdio.h>
#include <stdlib.h>

void byteToBinary(unsigned char byte, char *binary) {
    int i;
    for (i = 7; i >= 0; --i) {
        binary[7 - i] = (byte & (1 << i)) ? '1' : '0';
    }
    binary[8] = '\0';
}

int main() {
    FILE *file;
    unsigned char byte;
    char binary[9]; // 8 bits + 1 para o caractere nulo
    int i;

    // Abrir o arquivo binário para leitura
    file = fopen("arquivo.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ler o arquivo byte a byte e imprimir sua representação binária
    while (fread(&byte, sizeof(unsigned char), 1, file) == 1) {
        byteToBinary(byte, binary);
        printf("%s ", binary);
    }

    // Fechar o arquivo
    fclose(file);

    return 0;
}
