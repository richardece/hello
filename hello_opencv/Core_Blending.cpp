#include <stdio.h>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

int main(int argc, char** argv ){
                        
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");

    double alpha = 0.75; double beta; double input;
    Mat src1, src2, dst;

    //Both sources must have same sizes
    src1 = imread( samples::findFile("LinuxLogo.jpg") );
    src2 = imread( samples::findFile("WindowsLogo.jpg") );   

    //dst = a*src1 + b*src2 + gamma
    //gamma = 0.0 in the example
    beta = ( 1.0 - alpha );
    addWeighted( src1, alpha, src2, beta, 0.0, dst);
    imshow( "Linear Blend", dst );

    waitKey(0);
    return 0;
}