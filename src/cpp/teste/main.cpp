#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
	VideoCapture video(0);
	Mat img;
	while(true){
		video.read(img);
		imshow("Frame", img);
		waitKey(0);
	}
	return 0;
}
