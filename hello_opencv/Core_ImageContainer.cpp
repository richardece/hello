#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv ){
    Mat A, C;                          // creates just the header parts
    A = imread("lena.jpeg", IMREAD_COLOR); // here we'll know the method used (allocate matrix)
    Mat B(A);                              // Use the copy constructor
    C = A;                              // Asignment operator

    Mat D (A, Rect(10, 10, 100, 100) ); // using a rectangle, get s subset (ROI) of matrix A
    Mat E = A(Range::all(), Range(1,3)); // using row and column boundaries
    //until here, all matrices point to matrix A

    //it is also possible to copy matrix
    Mat F = A.clone();
    Mat G;
    A.copyTo(G);

    Mat M(2,2, CV_8UC3, Scalar(0,0,255));   //2x2 matrix
                                            //each element is 8bit, unsigned, 3 channels
                                            //initial value is 0,0,255
    cout << "M = " << endl << " " << M << endl << endl;
    
    int sz[3] = {2,2,2};
    Mat L(3,sz, CV_8UC(1), Scalar::all(0)); //3 dimensions, where the size of each dimension is specified by sz
    //cout << "L = " << endl << " " << L << endl << endl;
    
    M.create(4,4, CV_8UC(2));               //this cannot be used with constructor initialization
                                            // this will just reallocate the memory
    cout << "M = "<< endl << " "  << M << endl << endl;
    
    Mat N = Mat::eye(4, 4, CV_64F);         //diagonal ones
    cout << "N = " << endl << " " << N << endl << endl;
    Mat O = Mat::ones(2, 2, CV_32F);        //all ones
    cout << "O = " << endl << " " << O << endl << endl;
    Mat Z = Mat::zeros(3,3, CV_8UC1);       //all zeroes
    cout << "Z = " << endl << " " << Z << endl << endl;

    Mat K = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);   //3x3 matrix, with this intiial values
    cout << "K = " << endl << " " << K << endl << endl;
    K = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3); //same as above
    cout << "K = " << endl << " " << K << endl << endl;

    Mat R = Mat(3, 2, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255)); //fill up the matrix with random values, range is given
    cout << "R (default) = " << endl <<        R                        << endl << endl;
    cout << "R (python)  = " << endl << format(R, Formatter::FMT_PYTHON) << endl << endl;
    cout << "R (numpy)   = " << endl << format(R, Formatter::FMT_NUMPY ) << endl << endl;   //my preferred output format
    cout << "R (C)       = " << endl << format(R, Formatter::FMT_C     ) << endl << endl;

    waitKey(0);
    return 0;
}