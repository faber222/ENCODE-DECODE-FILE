#include "mem.h"

int main(int argc, char* argv[]) {

    int opcao;
    string keyboard;

    cout << "Escolha uma opção:" << endl;
    cout << "1. Codificar" << endl;
    cout << "2. Decodificar" << endl;
    cout << "0. Sair" << endl;
    cout << "Digite o número da opção desejada: ";
    cin >> keyboard;
    opcao = stoi(keyboard);

    switch (opcao) {
        case UM:
            cout << "Você escolheu a opção " + to_string(UM) << endl << endl;
            generateVideo(openFile(UM)); // Cria o vídeo diretamente a partir do arquivo de entrada
            break;

        case DOIS:
            cout << "Você escolheu a opção " + to_string(DOIS) << endl << endl;
            processVideoToFile(outputVideo + videoFileExtension, openFile(DOIS));
            break;
        case 0:
            cout << "Saindo do programa..." << endl;
            return 0;
        default:
            cout << "Opção inválida" << endl;
            break;
    }
    return 0;
}
