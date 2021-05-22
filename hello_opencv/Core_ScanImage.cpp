#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv ){
    Mat I, J;                          // creates just the header parts

    I = imread("lena.jpeg", IMREAD_COLOR); // here we'll know the method used (allocate matrix)
   
    int divideWith = 10;
    uchar table[256];
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * (i/divideWith));

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];

    double t = (double)getTickCount();  //for time profiling
    LUT(I, lookUpTable, J);
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "Times passed in seconds: " << t << endl;

    //write output image J to file
    imwrite("lena_LUT.jpeg", J);


    Mat R = Mat(3, 2, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255)); //fill up the matrix with random values, range is given
    cout << "R (default) = " << endl <<        R                        << endl << endl;
    cout << "R (python)  = " << endl << format(R, Formatter::FMT_PYTHON) << endl << endl;
    cout << "R (numpy)   = " << endl << format(R, Formatter::FMT_NUMPY ) << endl << endl;   //my preferred output format
    cout << "R (C)       = " << endl << format(R, Formatter::FMT_C     ) << endl << endl;

    waitKey(0);
    return 0;
}