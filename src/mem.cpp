#include "mem.h"

// unifica a função wread e generateVideo() e faz tudo em memoria
void generateVideo(const string& inputPath) {
    // Cria o diretório de saída se ele não existir
    filesystem::create_directory(outputVideo);
    string outVideo = outputVideo + videoFileExtension;

    // Abre o arquivo de entrada para leitura
    ifstream inFile(inputPath, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada: " << inputPath << endl;
        return;
    }
    // compressão em HuffYUV (FOURCC = "HFYU") → Sem perdas e mais eficiente que FFV1.
    VideoWriter video(outVideo, VideoWriter::fourcc('H', 'F', 'Y', 'U'), 1, Size(X, Y));

    // compressão em FFV1 (FOURCC = "FFV1") → Totalmente sem perdas, mas gera arquivos grandes.
    // VideoWriter video(outVideo, VideoWriter::fourcc('F', 'F', 'V', '1'), 30, Size(X, Y));

    if (!video.isOpened()) {
        cerr << "Erro ao criar o arquivo de vídeo: " << outVideo << endl;
        inFile.close();
        return;
    }

    Mat frame(Y, X, CV_8UC3, Scalar(0, 0, 0)); // Cria um frame preto

    char byte;
    char binary[9]; // Array para armazenar a representação binária de um byte
    int x = 0, y = 0;

    // Lê o arquivo byte a byte e desenha os pixels no frame
    while (inFile.read(&byte, sizeof(char))) {
        byteToBinary(byte, binary);

        for (int i = 0; i < 8; i++) {
            if (x >= X) {
                x = 0;
                y++;
                if (y >= Y) {
                    // Adiciona o frame ao vídeo e reinicia o frame
                    video.write(frame);
                    frame.setTo(Scalar(0, 0, 0)); // Reseta o frame para preto
                    y = 0;
                }
            }

            // Essa forma é mais rapida pois usa acesso direto na memoria.
            uchar* pixel = frame.ptr<uchar>(y) + (x * 3);
            if (binary[i] == '1') {
                // Define o pixel como branco
                // frame.at<Vec3b>(y, x) = Vec3b(B1, G1, R1); 

                pixel[0] = B1;
                pixel[1] = G1;
                pixel[2] = R1;
            } else {
                // Define o pixel como preto
                // frame.at<Vec3b>(y, x) = Vec3b(B0, G0, R0); 

                pixel[0] = B0;
                pixel[1] = G0;
                pixel[2] = R0;
            }
            x++;
        }
    }

    // Adiciona o último frame ao vídeo (se houver dados restantes)
    if (x != 0 || y != 0) {
        video.write(frame);
    }

    // Fecha o arquivo de entrada e o vídeo
    inFile.close();
    video.release();

    cout << "Vídeo criado com sucesso: " << outVideo << endl;
    cout << "Dados codificados com sucesso!" << endl;
}

void processVideoToFile(const string& videoPath, const string& outputPath) {
    // Abre o vídeo
    VideoCapture video(videoPath);
    if (!video.isOpened()) {
        cerr << "Erro ao abrir o vídeo: " << videoPath << endl;
        return;
    }

    // Abre o arquivo de saída
    ofstream outFile(outputPath, ios::binary | ios::app);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída: " << outputPath << endl;
        video.release();
        return;
    }

    int frameNumber = 0;
    Mat frame;
    char bits[N];
    int j = 0;
    unsigned char byte;

    // Processa cada frame do vídeo
    while (video.read(frame)) {
        frameNumber++;

        // Processa os pixels do frame
        for (size_t y = 0; y < frame.rows; y++) {
            for (size_t x = 0; x < frame.cols; x++) {
                Vec3b pixel = frame.at<Vec3b>(y, x);
                unsigned char r = pixel[2]; // Canal vermelho
                unsigned char g = pixel[1]; // Canal verde
                unsigned char b = pixel[0]; // Canal azul

                // Verifica se o pixel é preto ou branco
                if ((r == R0 && g == G0 && b == B0) || (r == R1 && g == G1 && b == B1)) {
                    if (r == 0) {
                        bits[j] = '0';
                    } else {
                        bits[j] = '1';
                    }
                    j++;
                }

                // Quando temos 8 bits, converte para um byte e escreve no arquivo
                if (j == 8) {
                    bits[j] = '\0'; // Adiciona um terminador de string
                    j = 0;
                    byte = bitsToByte(bits);
                    outFile.write(reinterpret_cast< char* >(&byte), sizeof(char));
                }
            }
        }
    }

    // Verifica se há bits restantes não processados
    if (j > 0) {
        while (j < 8) {
            bits[j] = '0';
            j++;
        }
        bits[j] = '\0';
        byte = bitsToByte(bits);
        outFile.write(reinterpret_cast< char* >(&byte), sizeof(char));
    }


    // Fecha o vídeo e o arquivo de saída
    video.release();
    outFile.close();

    cout << "Processamento concluído. Total de frames processados: " << frameNumber << endl;
    cout << "Dados decodificados com sucesso!" << endl;
}

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

// Função para lidar com a entrada do usuário e a abertura do arquivo
string openFile(int i) {
    string keyboard;
    cout << "Digite o caminho do arquivo com a extensao: ";
    cin >> keyboard;
    if (i == DOIS) {
        // Create the output directory if it doesn't exist
        filesystem::create_directory(decodedPath);
        keyboard = decodedPath + keyboard + "";
    }
    return keyboard;
}
