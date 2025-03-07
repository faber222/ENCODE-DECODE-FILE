#include "function.h"

int numPNG = 0;

// não usado
// bool isGrayScale(char r, char g, char b) {
//     // Verifica se os valores RGB estão próximos uns dos outros
//     return (r == g && g == b && b == r);
// }

void generateBMPSequence(string videoPath) {
    VideoCapture video(videoPath);
    if (!video.isOpened()) {
        cerr << "Error opening video file: " << videoPath << endl;
        return;
    }

    int frameCount = static_cast< int >(video.get(CAP_PROP_FRAME_COUNT));
    int frameNumber = 0;

    // Create the output directory if it doesn't exist
    filesystem::create_directory(generatedOutputDir);
    int y = 1;
    while (frameNumber < frameCount) {
        Mat frame;
        if (!video.read(frame)) {
            cerr << "Error reading frame " << frameNumber << " from video." << endl;
            break;
        }

        string outputName = generatedOutputDir + imageFileName + to_string(y) + extension + "";
        if (!imwrite(outputName, frame)) {
            cerr << "Error saving frame " << frameNumber << " as " + extension + "." << endl;
        }
        y++;
        frameNumber++;
    }

    video.release();

    cout << extension + " sequence generated successfully. Total frames: " << frameNumber << endl;
    numPNG = frameNumber;
}

// Exemplo de fluxo de execução :
// 1 - O vídeo é aberto.
// 2 - Para cada frame :
//      O frame é lido.
//      Os pixels são processados para extrair os bits.
//      Os bits são convertidos em bytes e escritos no arquivo de saída.
// 3 - Após processar todos os frames, o vídeo e o arquivo de saída são fechados.
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

/**
* Reads from the directory of generated PNGs from functions above and stitches
* them together in a video of speficied format, frame rate, etc.
*/
void generateVideo() {
    filesystem::create_directory(outputVideo);
    string outVideo = outputVideo + videoFileExtension + "";

    // compressão em HuffYUV (FOURCC = "HFYU") → Sem perdas e mais eficiente que FFV1.
    // VideoWriter video(outVideo, VideoWriter::fourcc('H', 'F', 'Y', 'U'), 30, Size(X, Y));

    // compressão em FFV1 (FOURCC = "FFV1") → Totalmente sem perdas, mas gera arquivos grandes.
    VideoWriter video(outVideo, VideoWriter::fourcc('F', 'F', 'V', '1'), 30, Size(X, Y));

    if (!video.isOpened()) {
        cerr << "Failed to create video file: " << outVideo << endl;
        return;
    }

    Mat frame;
    for (int i = 1; i <= numPNG; i++) {
        string imagePath = encodedPath + imageFileName + to_string(i) + extension + "";
        frame = imread(imagePath);
        // descomente para apagar as imagens geradas
        const char* caminho = imagePath.c_str();
        int resultado = remove(caminho);

        if (frame.empty())
            break;

        for (int j = 0; j < framesPerImage; j++)
            video.write(frame);
    }

    video.release();
    cout << "Video created successfully: " << outVideo << endl;
}

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

    // Configura o VideoWriter para criar o vídeo
    VideoWriter video(outVideo, VideoWriter::fourcc('F', 'F', 'V', '1'), 30, Size(X, Y));
    if (!video.isOpened()) {
        cerr << "Erro ao criar o arquivo de vídeo: " << outVideo << endl;
        inFile.close();
        return;
    }

    Mat frame(Y, X, CV_8UC3, Scalar(0, 0, 0)); // Cria um frame preto
    // Mat frame;
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

            if (binary[i] == '1') {
                frame.at<Vec3b>(y, x) = Vec3b(B1, G1, R1); // Define o pixel como branco
            } else {
                frame.at<Vec3b>(y, x) = Vec3b(B0, G0, R0); // Define o pixel como preto
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
void rread(BmpImg& img, string outputPath) {

    int j = 0;
    char bits[N];
    unsigned char byte; // Variável para armazenar o byte convertido
    int k = 1;
    string fileName;

    ofstream outFile(outputPath, ios::binary | ios::app);
    //    ofstream outBinFile("recBin.txt", ios::app);
    while (true) {
        // se descomentar essa e comentar a outra, podemos testar o código na pratica
        fileName = generatedOutputDir + imageFileName + to_string(k) + extension + "";

        // descomente para ler direto das imagens
        // fileName = encodedPath + imageFileName + to_string(k) + extension + "";

        // Tenta abrir a próxima imagem gerada
        if (img.read(fileName) != BMP_OK) {
            cerr << "erro ao ler imagem " + to_string(k) << endl;
            break;  // Sai do loop se não houver mais imagens
        }
        // Exemplo de acesso aos pixels da imagem
        for (size_t y = 0; y < Y; y++) {
            for (size_t x = 0; x < X; x++) {
                unsigned char r = img.red_at(x, y);
                unsigned char g = img.green_at(x, y);
                unsigned char b = img.blue_at(x, y);

                // // Se o pixel for preto ou branco, extrai o bit correspondente
                // if (isGrayScale(r, g, b)) {
                //     if (r <= 128) {
                //         bits[j] = '0';
                //         j++;
                //     } else {
                //         bits[j] = '1';
                //         j++;
                //     }
                // }

                // Uso sem a necessidade de validação da escala cinza
                if ((r == R0 && g == G0 && b == B0) || (r == R1 && g == G1 && b == B1)) {
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
                    outFile.write(reinterpret_cast< char* >(&byte), sizeof(char));
                    //		    outBinFile << bits << endl;
                }
            }
        }
        k++;
    }
    outFile.close();
    //    outBinFile.close();
}

// Lê um arquivo byte a byte, converte cada byte em uma sequência de bits e desenha uma imagem com base nesses bits
void wread(BmpImg& img, string inputPath) {
    fstream file;
    string path;
    int y = 0, x = 0, k = 1;
    char byte;
    char binary[8]; // Tamanho fixo para armazenar a representação binária de um byte
    file.open(inputPath, ios::in | ios::binary);
    //    ofstream outFile("bin.txt", ios::app);
    if (file.is_open()) {
        // Lê o arquivo byte a byte e converte cada byte em sua representação binária
        while (file.read(&byte, sizeof(char))) {
            byteToBinary(byte, binary);
            //	    outFile << binary << endl;
            for (size_t i = 0; i < 8; i++) {
                // Limita a quantidade máxima de pixels a 510x510
                if (y == Y - 2) {
                    path = encodedPath + imageFileName + to_string(k) + extension + "";
                    img.write(path);
                    numPNG++;
                    y = x = 0;
                    k++;
                }
                if (x == X - 2) {
                    if (y < Y - 2) {
                        y++;
                    }
                    x = 0;
                }

                if (binary[i] == '1') {
                    img.set_pixel(x, y, R1, G1, B1); // Define o pixel como branco
                } else {
                    img.set_pixel(x, y, R0, G0, B0); // Define o pixel como preto
                }
                x++;
            }
        }
        path = encodedPath + imageFileName + to_string(k) + extension + "";
        //        outFile << binary << endl;
        img.write(path);
        numPNG++;
        file.close();
    } else {
        cerr << "ERRO: arquivo não foi aberto ou não existe" << endl;
    }
    //	outFile.close();
}

// Pinta toda a imagem de vermelho
void drawImg(BmpImg& img) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            img.set_pixel(x, y, 0, 255, 0); // Define o pixel como verde
        }
    }

}

// Função para lidar com a entrada do usuário e a abertura do arquivo
string openFile(int i) {
    string keyboard;
    cout << "Digite o caminho do arquivo com a extensao: ";
    cin >> keyboard;
    if (i == DOIS) {
        keyboard = decodedPath + keyboard + "";
    }
    return keyboard;
}
