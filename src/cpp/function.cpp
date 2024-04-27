#include "function.h"

int numPNG = 0;

void generateBMPSequence(string  videoPath) {

    VideoCapture video(videoPath);
    if (!video.isOpened()) {
        cerr << "Error opening video file: " << videoPath << endl;
        return;
    }

    int frameCount = static_cast< int >(video.get(CAP_PROP_FRAME_COUNT));
    int frameNumber = 0;

    // Create the output directory if it doesn't exist
    filesystem::create_directory(generatedJpegOutputDirectory);
    cout << frameCount;
    int x = 0;
    int y = 1;
    while (frameNumber < frameCount) {
    	if(x >= framesPerImage){
    	    x = 0;
    	}
    	if(x == framesPerImage/2){
		Mat frame;
		if (!video.read(frame)) {
		    cerr << "Error reading frame " << frameNumber << " from video." << endl;
		    break;
		}

		string outputName = generatedJpegOutputDirectory + imageFileName + to_string(y) + extension + "";
		if (!imwrite(outputName, frame)) {
		    cerr << "Error saving frame " << frameNumber << " as " + extension + "." << endl;
		}
	y++;
        }
        x++;
        frameNumber++;
    }

    video.release();

    cout << extension + " sequence generated successfully. Total frames: " << frameNumber << endl;
    numPNG = frameNumber;
}


/**
* Reads from the directory of generated PNGs from functions above and stitches
* them together in a video of speficied format, frame rate, etc.
*/
void generateVideo() {
    filesystem::create_directory(outputVideo);
    string outVideo = outputVideo + videoFileExtension + "";
    VideoWriter video(outVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(X, Y));

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
        fileName = "./recoveredFiles/imagem" + to_string(k) + extension;
	cout << "./recoveredFiles/imagem" + to_string(k) + extension << endl;
        // Tenta abrir a próxima imagem gerada
        if (img.read(fileName) != BMP_OK) {
            break;  // Sai do loop se não houver mais imagens
        }
	cout << "teste" << endl;
        // Exemplo de acesso aos pixels da imagem
        for (size_t y = 0; y < Y; y++) {
            for (size_t x = 0; x < X; x++) {
                unsigned char r = img.red_at(x, y);
                unsigned char g = img.green_at(x, y);
                unsigned char b = img.blue_at(x, y);

                if (r <= 255 && r >= 128 && g <= 255 && g >= 128 && b <= 255 && b >= 128) {
                    bits[j] = '1';
                    j++;
                } else {
                    bits[j] = '0';
                    j++;
                }

                // // Se o pixel for preto ou branco, extrai o bit correspondente
                // if ((r == 0 && g == 0 && b == 0) || (r == 250 && g == 250 && b == 250)) {
                //     if (r == 0) {
                //         bits[j] = '0';
                //     } else {
                //         bits[j] = '1';
                //     }
                //     j++;
                // }

                if (j == 8) {
                    bits[j] = '\0'; // Adiciona um terminador de string
                    j = 0;
                    byte = bitsToByte(bits);
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
                    path = encodedPath + imageFileName + to_string(k) + extension + "";
                    img.write(path);
                    numPNG++;
                    y = x = 0;
                    k++;
                }
                if (x == X - 2) {
                    if (y < Y -2){
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
        img.write(path);
        numPNG++;
        file.close();
    } else {
        cerr << "ERRO: arquivo não foi aberto ou não existe" << endl;
    }
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
