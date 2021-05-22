#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <string>

using namespace cv;

int main ( int argc, char** argv )
{
    // Declare variables
    Mat src, dst;
    Mat kernel;
    Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    const char* window_name = "filter2D Demo";
    const char* imageName = "lena.jpg";

    // Loads an image
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    src = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Load an image
    if( src.empty() )
    {
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default lena.jpg] \n");
        return EXIT_FAILURE;
    }

    // Initialize arguments for the filter
    anchor = Point( -1, -1 );   //indicates center
    delta = 0;
    ddepth = -1;                //negative value indicates depth same as source
    // Loop - Will filter the image with different kernel sizes each 0.5 seconds
    int ind = 0;
    for(;;)
    {
        // Update kernel size for a normalized box filter
        kernel_size = 3 + 2*( ind%5 );  //value in range [3, 11]
        kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
        
        // Apply filter
        filter2D(src, 
            dst, 
            ddepth , 
            kernel, 
            anchor, 
            delta, 
            BORDER_DEFAULT );   //more details in future tutorials
        

        Point org;
        org.x = 10;
        org.y = 100;
        std::string disp = "Kernel size: " + std::to_string(kernel_size);

        putText( dst, 
            disp,   //Text to be displayed
            org,    //Bottom-left corner of the text
            0,      //Font type 0:8
            1.0,    //Font scale from 0.1:5.1
            {0,255,0},  //Color BGR
            2,         //Text thickness 1:10
            8);         //line type
        
        imshow( window_name, dst );


        char c = (char)waitKey(1000);
        // Press 'ESC' to exit the program
        if( c == 27 )
        { break; }
        ind++;
    }
    return EXIT_SUCCESS;
}