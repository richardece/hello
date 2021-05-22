#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold(int, void*)
{
    //blur the image to eliminate the noise
    blur( src_gray, detected_edges, Size(3,3) );

    Canny( detected_edges,  //input image
        detected_edges,     //output image, same as input
        lowThreshold,       //low threshold, coming from the trackbar
        lowThreshold*ratio, //high threshold, recommended to be 2 or 3x low threshold
        kernel_size );
    
    //create a black image
    dst = Scalar::all(0);
    
    //at this point, detected_edges is a black image with white edge contours
    //copyTo function will copy the src into dst, using the detected_edges as filter.
    //The detected_edges has black background with white edges.
    //copyTo function will copy (from src to dst) only if the corresponding pixel in detected_edges is non-zero. 
    //Essentially, the result will be a black image, but the edges from the original image, and not white
    src.copyTo( dst, detected_edges);

    imshow( window_name, dst );
}

/*
Canny edge detector - 

This SW generates a mask (bright lines representing the edges in  a black background),
then applies the mask on the original image
*/
int main( int argc, char** argv )
{
  samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
  src = imread( samples::findFile( "fruits.jpg" ), IMREAD_COLOR ); // Load an image
  if( src.empty() )
  {
    std::cout << "Could not open or find the image!\n" << std::endl;
    return -1;
  }

  dst.create( src.size(), src.type() );

  //convert to greyscale
  cvtColor( src, src_gray, COLOR_BGR2GRAY );

  //create trackbar to adjust the low  threshold
  namedWindow( window_name, WINDOW_AUTOSIZE );

  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  
  CannyThreshold(0, 0);

  waitKey(0);
  return 0;
}