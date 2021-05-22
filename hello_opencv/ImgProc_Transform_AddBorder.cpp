#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

// Declare the variables
Mat src, dst;
int top, bottom, left, right;
int borderType = BORDER_CONSTANT;
const char* window_name = "copyMakeBorder Demo";
RNG rng(12345);

/*
Adding border - used by most OpenCV functions when performing convolution.
They will add a border to an image, perform convolution then remove the padding.
There are 2 ways to define padding:
    BORDER_CONSTANT: Pad the image with a constant value (i.e. black or 0)
    BORDER_REPLICATE: The row or column at the very edge of the original is replicated to the extra border.
*/
int main( int argc, char** argv )
{
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");

    const char* imageName = "lena.jpg";
    // Loads an image
    src = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Load an image
    // Check if image is loaded fine
    if( src.empty()) {
        printf(" Error opening image\n");
        return -1;
    }
    // Brief how-to for this program
    printf( "\n \t copyMakeBorder Demo: \n" );
    printf( "\t -------------------- \n" );
    printf( " ** Press 'c' to set the border to a random constant value \n");
    printf( " ** Press 'r' to set the border to be replicated \n");
    printf( " ** Press 'ESC' to exit the program \n");
    namedWindow( window_name, WINDOW_AUTOSIZE );
    
    // Initialize arguments for the filter
    top = (int) (0.05*src.rows); bottom = top;  //5% of rows
    left = (int) (0.05*src.cols); right = left; //5% of columns
    for(;;)
    {
        Scalar value( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );  //Random BGR color
        
        copyMakeBorder( src, 
            dst, 
            top,        //length of border in terms of pixels
            bottom, 
            left, 
            right, 
            borderType, //could be constant or replicate
            value );    //used if bordertype is constant
        
        imshow( window_name, dst );
        
        char c = (char)waitKey(500);
        if( c == 27 )
        { break; }
        else if( c == 'c' )
        { borderType = BORDER_CONSTANT; }
        else if( c == 'r' )
        { borderType = BORDER_REPLICATE; }
    }
    return 0;
}