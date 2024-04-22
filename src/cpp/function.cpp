#include "function.h"

//
/**
* Generates a sequence of PNGs from a specified video path
*
* @param videoPath the path of the video
*/
void generatePNGSequence(string videoPath) {

    VideoCapture video(videoPath);
    if (!video.isOpened())
    {
        cerr << "Error opening video file: " << videoPath << endl;
        return;
    }

    int frameCount = static_cast< int >(video.get(CAP_PROP_FRAME_COUNT));
    int frameNumber = 0;

    // Create the output directory if it doesn't exist
    filesystem::create_directory(outputDirectory);

    while (frameNumber < frameCount)
    {
        Mat frame;
        if (!video.read(frame))
        {
            cerr << "Error reading frame " << frameNumber << " from video." << endl;
            break;
        }

        string outputName = outputDirectory + to_string(frameNumber) + ".png";
        if (!imwrite(outputName, frame))
        {
            cerr << "Error saving frame " << frameNumber << " as PNG." << endl;
        }

        frameNumber++;
    }

    video.release();

    cout << "PNG sequence generated successfully. Total frames: " << frameNumber << endl;
    numPNG = frameNumber;
}
// 

//
/**
* Reads from the directory of generated PNGs from functions above and stitches
* them together in a video of speficied format, frame rate, etc.
*/
void generateVideo() {
    cv::VideoWriter video(outputVideo, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 30, cv::Size(width, height));

    if (!video.isOpened()) {
        cerr << "Failed to create video file: " << outputVideo << endl;
        return;
    }

    cv::Mat frame;
    for (int i = 0; i < numPNG; i++) {
        string imagePath = directory + to_string(i) + ".png";
        frame = cv::imread(imagePath);

        if (frame.empty())
            break;

        for (int j = 0; j < framesPerImage; j++)
            video.write(frame);
    }

    video.release();
    cout << "Video created successfully: " << outputVideo << endl;
}
// 

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
    while (true) {
        fileName = "./encodedFiles/imagem" + to_string(k) + ".bmp";
        // Tenta abrir a próxima imagem gerada
        if (img.read(fileName) != BMP_OK) {
            break;  // Sai do loop se não houver mais imagens
        }
        // Exemplo de acesso aos pixels da imagem
        for (size_t y = 0; y < Y; y++) {
            for (size_t x = 0; x < X; x++) {
                unsigned char r = img.red_at(x, y);
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
                    // if (!outFile.is_open()) {
                    //     cerr << "Erro ao abrir o arquivo de saída." << endl;
                    //     return;
                    // }
                    outFile.write(reinterpret_cast< char* >(&byte), sizeof(char));
                }
            }
        }
        k++;
    }
    outFile.close();
}

// Lê um arquivo byte a byte, converte cada byte em uma sequência de bits e desenha uma imagem com base nesses bits
void wread(BmpImg& img, string inputPath) {
    fstream file;
    string path;
    int y = 0, x = 0, k = 1;
    char byte;
    char binary[8]; // Tamanho fixo para armazenar a representação binária de um byte

    file.open(inputPath, ios::in | ios::binary);
    if (file.is_open()) {
        // Lê o arquivo byte a byte e converte cada byte em sua representação binária
        while (file.read(&byte, sizeof(char))) {
            byteToBinary(byte, binary);
            for (size_t i = 0; i < 8; i++) {
                // Limita a quantidade máxima de pixels a 510x510
                if (y == Y - 2) {
                    path = "./encodedFiles/imagem" + std::to_string(k) + ".bmp";
                    img.write(path);
                    y = x = 0;
                    k++;
                }
                if (x == X - 2) {
                    y++;
                    x = 0;
                }
                if (binary[i] == '1') {
                    img.set_pixel(x, y, 250, 250, 250); // Define o pixel como branco
                } else {
                    img.set_pixel(x, y, 0, 0, 0); // Define o pixel como preto
                }
                x++;
            }
        }
        path = "./encodedFiles/imagem" + std::to_string(k) + ".bmp";
        img.write(path);
        file.close();
    } else {
        cerr << "ERRO: arquivo não foi aberto ou não existe" << endl;
    }
}

// Pinta toda a imagem de vermelho
void drawImg(BmpImg& img) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            img.set_pixel(x, y, 255, 0, 0); // Define o pixel como vermelho
        }
    }

}

// Função para lidar com a entrada do usuário e a abertura do arquivo
string openFile(int i) {
    string keyboard;
    cout << "Digite o caminho do arquivo com a extensao: ";
    cin >> keyboard;
    if (i == DOIS) {
        keyboard = "./decodedFiles/" + keyboard;
    }
    return keyboard;
}
