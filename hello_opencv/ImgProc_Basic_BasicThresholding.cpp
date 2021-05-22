#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using std::cout;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

/*
Thresholding - simplest segmentation method

To differentiate the pixels we are interested in from the rest (which will eventually be rejected), 
    we perform a comparison of each pixel intensity value with respect to a threshold (determined according to the problem to solve).
Once we have separated properly the important pixels, we can set them with a determined 
    value to identify them (i.e. we can assign them a value of 0 (black), 255 (white) or any value that suits your needs).
*/

static void Threshold_Demo( int, void* )
{
    /* 
     0: Binary              - if src(x,y) > thresh, use maxVal; else use 0
     1: Binary Inverted     - if src(x,y) > thresh, use 0; else use maxVal
     2: Threshold Truncated - if src(x,y) > thresh, use thresh; else use src(x,y)
     3: Threshold to Zero   - if src(x,y) > thresh, use src(x,y); else use 0
     4: Threshold to Zero Inverted - if src(x,y) > thresh, use 0; else use src(x,y)
    */
    threshold( src_gray,    //input image
        dst,                //output image
        threshold_value,    //threshold value
        max_binary_value,   //value to be used for binary thresholding operation
        threshold_type );   //one of the thresholding types listed above 
    
    imshow( window_name, dst );
}

int main( int argc, char** argv )
{
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");

    String imageName("stuff.jpg"); // by default

    src = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Load an image
    if (src.empty())
    {
        cout << "Cannot read the image: " << imageName << std::endl;
        return -1;
    }
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray

    namedWindow( window_name, WINDOW_AUTOSIZE ); // Create a window to display results

    createTrackbar( trackbar_type,
                    window_name, &threshold_type,
                    max_type, Threshold_Demo ); // Create a Trackbar to choose type of Threshold
    createTrackbar( trackbar_value,
                    window_name, &threshold_value,
                    max_value, Threshold_Demo ); // Create a Trackbar to choose Threshold value

    Threshold_Demo( 0, 0 ); // Call the function to initialize

    waitKey();
    return 0;
}

