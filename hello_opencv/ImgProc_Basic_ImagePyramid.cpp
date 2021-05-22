#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
const char* window_name = "Pyramids Demo";

/*
Image Pyramid - a collection of images from a single original image that are successively downsampled.
Gaussian pyramid - each layer is one quarter of its predecessor
To downsample, remove even-numbered row and column.
To upsample, upsize the image by inserting 0-filled even row and column.
Gaussian kernel is used in both.

*/
int main( int argc, char** argv )
{
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");

    cout << "\n Zoom In-Out demo \n "
            "------------------  \n"
            " * [i] -> Zoom in   \n"
            " * [o] -> Zoom out  \n"
            " * [ESC] -> Close program \n" << endl;
    const char* filename = argc >=2 ? argv[1] : "chicky_512.png";
    // Loads an image
    Mat src = imread( samples::findFile( "chicky_512.png" ) );
    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        return EXIT_FAILURE;
    }

    for(;;)
    {
        imshow( window_name, src );

        char c = (char)waitKey(0);

        if( c == 27 ){ 
            break; 
        } else if( c == 'i' ) { 
            pyrUp( src,     //current image
                src,        //destination image
                Size( src.cols*2, src.rows*2 ) );   //destination size (double if upsampling)
            printf( "** Zoom In: Image x 2 \n" );
        } else if( c == 'o' ) { 
            pyrDown( src, 
                src, 
                Size( src.cols/2, src.rows/2 ) );
            printf( "** Zoom Out: Image / 2 \n" );
        }
    }
    return EXIT_SUCCESS;
}