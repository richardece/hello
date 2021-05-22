#include <stdio.h>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

int main(int argc, char** argv ){

    //Brightness
    //the histogram is shifted left or right
    //Shifting to right means brighter image
    
    //Contrast
    //The histogram is either compressed (low contrast) or expanded (high contrast)
    //Compressed histogram means the pixel values got almost same value, so its difficult to distinguish the lines

    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");

    double alpha = 3.0; /*< Simple contrast control     [1.00   - 3.00] */
    int beta = 0;       /*< Simple brightness control   [0      - 100]  */
    Mat src;
    Mat dst = Mat::zeros( src.size(), src.type() );

    src = imread( samples::findFile("lena.jpg"), IMREAD_GRAYSCALE );

    //dst = a*src + b
    src.convertTo(dst, -1, alpha, beta);

    imshow("Original Image", src);
    imshow("New Image", dst);

    //display histogram
    //Quite complicated code based on the book

    waitKey(0);
    return 0;
}