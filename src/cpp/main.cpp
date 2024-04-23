#include "function.h"

int main(int argc, char* argv[]) {
	BmpImg img(X, Y);
	img.init(X, Y); // Inicializa uma imagem BMP com tamanho 512x512
	drawImg(img); // Desenha a imagem inicial
	fstream file;

	unsigned char byte;
	char binary[N]; // Representação binária de 8 bits mais um para o caractere nulo
	int opcao;
	string keyboard;

	cout << "Escolha uma opção:" << endl;
	cout << "1. Codificar" << endl;
	cout << "2. Decodificar" << endl;
	cout << "0. Sair" << endl;
	cout << "Digite o número da opção desejada: ";
	cin >> keyboard;
	opcao = stoi(keyboard);

	// Verifica a opção escolhida pelo usuário
	switch (opcao) {
		case UM:
			cout << "Você escolheu a opção " + to_string(UM) << endl << endl;
			wread(img, openFile(UM));
			cout << "Dados codificados com sucesso!" << endl;
			generateVideo();
			break;
		case DOIS:
			cout << "Você escolheu a opção " + to_string(DOIS) << endl << endl;
			generateBMPSequence(outputVideo);
			rread(img, openFile(DOIS)); // Recupera os dados da imagem BMP
			cout << "Dados decodificados com sucesso!" << endl;
			break;
		case 0:
			cout << "Saindo do programa..." << endl;
			return 0; // Encerra o programa
		default:
			cout << "Opção inválida" << endl;
			break;
	}
	return 0;
}
