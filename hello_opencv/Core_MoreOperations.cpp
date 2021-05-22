#include <stdio.h>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;
int main(int argc, char** argv ){
    Mat img1, img2;                          
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    img1 = imread( samples::findFile("LinuxLogo.jpg"), IMREAD_GRAYSCALE); 
   
    Scalar intensity1 = img1.at<uchar>(Point(10, 20)); //Accessing pixel intensity at x,y 

    img2 = imread("lena.jpeg", IMREAD_COLOR);          
    Vec3b intensity2 = img2.at<Vec3b>(20, 10);    //Accessing pixel intensity of y,x from 3-channel image
    uchar blue  = intensity2.val[0];              //Notice that pixel values are arranged as BGR
    uchar green = intensity2.val[1];
    uchar red   = intensity2.val[2];

    //Primitive operations
    Mat img = imread("LinuxLogo.jpg", IMREAD_GRAYSCALE);
    Rect r(10, 10, 100, 100);   //Selecting a region of interest
    Mat smallImg = img(r);

    img = Scalar(0);            //make a black image from an existing greyscale image

    Mat img_color = imread("lena.jpeg", IMREAD_COLOR); 
    Mat grey;
    cvtColor(img_color, grey, COLOR_BGR2GRAY);    //convert color image to greyscale

    Mat src = imread("lena.jpeg", IMREAD_GRAYSCALE);
    Mat dst;
    src.convertTo(dst, CV_32F); //convert 8UC1 to 32FC1

    waitKey(0);
    return 0;
}