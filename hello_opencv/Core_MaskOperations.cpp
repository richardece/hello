#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv ){
    Mat src, dst;                          // creates just the header parts

    src = imread("lena.jpeg", IMREAD_COLOR); // here we'll know the method used (allocate matrix)
   
    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    imshow( "Input", src );

    //image contrast enhancement kernel
    Mat kernel = (Mat_<char>(3,3) <<  0, -1,  0,
                                   -1,  5, -1,
                                    0, -1,  0);

    double t = (double)getTickCount();
    filter2D( src, dst, src.depth(), kernel );
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "Built-in filter2D time passed in seconds:     " << t << endl;

    imshow( "Output", dst );


    waitKey(0);
    return 0;
}