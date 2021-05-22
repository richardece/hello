
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
Histogram - graphical representation of hte intensity distribution of an image
Histogram equalization - method that improves the contrast of an image by strething the intensity range
*/
int main( int argc, char** argv )
{
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    Mat src = imread( samples::findFile( "lena.jpg" ), IMREAD_COLOR );

    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        return -1;
    }

    //Convert to grayscale
    cvtColor( src, src, COLOR_BGR2GRAY );

    //Equalize histogram
    Mat dst;
    equalizeHist( src, dst );

    //Show output
    imshow( "Source image", src );
    imshow( "Equalized Image", dst );

    waitKey();
    return 0;
}