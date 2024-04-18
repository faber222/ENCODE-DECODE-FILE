#include <stdio.h>

int main() {
    FILE *arquivo_original, *arquivo_binario;
    char buffer[1024];
    size_t bytes_lidos;

    // Abrir o arquivo original para leitura em modo binário
    arquivo_original = fopen("arquivo.txt", "rb");
    if (arquivo_original == NULL) {
        perror("Erro ao abrir o arquivo original");
        return 1;
    }

    // Abrir o arquivo binário para escrita em modo binário
    arquivo_binario = fopen("arquivo.bin", "wb");
    if (arquivo_binario == NULL) {
        perror("Erro ao criar o arquivo binário");
        fclose(arquivo_original);
        return 1;
    }

    // Ler os dados do arquivo original e escrevê-los no arquivo binário
    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arquivo_original)) > 0) {
        fwrite(buffer, 1, bytes_lidos, arquivo_binario);
    }

    // Fechar os arquivos
    fclose(arquivo_original);
    fclose(arquivo_binario);

    printf("Arquivo convertido com sucesso para binário.\n");

    return 0;
}
