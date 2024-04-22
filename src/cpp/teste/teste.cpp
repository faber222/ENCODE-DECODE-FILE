#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    Mat imagem;
    imagem = imread(argv[1], IMREAD_GRAYSCALE);
    namedWindow("Minha Imagem", WINDOW_NORMAL);
    resizeWindow("Minha Imagem", 600, 600);
    imshow("Minha Imagem", imagem);
    waitKey(0);
}