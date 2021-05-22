#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
Mat src, dst;
int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;
const char* window_name = "Morphology Transformations Demo";
void Morphology_Operations( int, void* );

/*
Morphology - set of image processing operations that process image based on predefined kernel.

More morphology operations
1. Opening
    - obtained by erosion of image (dark areas grow big, bright areas get thinner),
     followed by dilation (bright areas grow again)
    - useful for removing small bright objects in a dark foreground
2. Closing
    - obtained by dilation followed erosion
    - usefult for removing small dark regions in a bright foreground 
3. Morphological Gradient
    - difference between dilation and erosion
    - usefultfor finding hte outline of an image
4. Top Hat
    - difference between input image and its opening
5. Black Hat
    - difference between closing of an image and its input image
*/
int main( int argc, char** argv )
{
  samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");

  src = imread( samples::findFile( "baboon.jpg" ), IMREAD_COLOR );
  if (src.empty())
  {
    std::cout << "Could not open or find the image!\n" << std::endl;
    return EXIT_FAILURE;
  }

  namedWindow( window_name, WINDOW_AUTOSIZE ); // Create window
  
  createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", 
    window_name, 
    &morph_operator, 
    max_operator, 
    Morphology_Operations );
  createTrackbar( "Element:\n 0: Rect - 1: Cross - 2: Ellipse", 
    window_name,
    &morph_elem, 
    max_elem,
     Morphology_Operations );
  createTrackbar( "Kernel size:\n 2n +1", 
    window_name,
    &morph_size, max_kernel_size,
    Morphology_Operations );
  
  Morphology_Operations( 0, 0 );
  waitKey(0);
  return 0;
}

void Morphology_Operations( int, void* )
{
  // Since MORPH_X : 2,3,4,5 and 6
  int operation = morph_operator + 2;
  Mat element = getStructuringElement( morph_elem, 
    Size( 2*morph_size + 1, 2*morph_size+1 ), 
    Point( morph_size, morph_size ) );

  morphologyEx( src,    //input image
    dst,                //output image
    operation,          //type of morphology operation
    element );          //kernel

    /*
    Opening:    MORPH_OPEN : 2
    Closing:    MORPH_CLOSE: 3
    Gradient:   MORPH_GRADIENT: 4
    Top Hat:    MORPH_TOPHAT: 5
    Black Hat:  MORPH_BLACKHAT: 6
    */

  imshow( window_name, dst );
}