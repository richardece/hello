#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
Sobel filter - computes the gradient (first derivative) of image intensity
It ocmputes the horizontal and vertial gradient and then combines them

*/
int main( int argc, char** argv )
{

    cout << "{ksize   k|1|ksize (hit 'K' to increase its value at run time)}\n";
    cout << "{scale   s|1|scale (hit 'S' to increase its value at run time)}\n";
    cout << "{delta   d|0|delta (hit 'D' to increase its value at run time)}\n";

  cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";
  cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values ( ksize will be -1 equal to Scharr function )";

  // First we declare the variables we are going to use
  Mat image,src, src_gray;
  Mat grad;
  const String window_name = "Sobel Demo - Simple Edge Detector";
  int ksize = 1;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  String imageName = "lena.jpg";
  // As usual we load our source image (src)
  samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
  image = imread( samples::findFile( imageName ), IMREAD_COLOR ); // Load an image
  // Check if image is loaded fine
  if( image.empty() )
  {
    printf("Error opening image: %s\n", imageName.c_str());
    return EXIT_FAILURE;
  }

  for (;;)
  {
    // Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

    // Convert the image to grayscale
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    
    // Sobel operator
    Sobel(src_gray, //input image, CV_8U
        grad_x,     //output iamge
        ddepth,     //CV_16S
        1,          //x_order, order of derivative in x direction
        0,          //y_order, order of derivative in y direction
        ksize, 
        scale, 
        delta, 
        BORDER_DEFAULT);
    Sobel(src_gray, 
        grad_y, 
        ddepth, 
        0,          //note that to calculate the gradient in y direction, x_order = 0 and y_order = 1
        1, 
        ksize, 
        scale, 
        delta, 
        BORDER_DEFAULT);
    
    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    //Add both x and y gradients
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    
    imshow(window_name, grad);
    
    char key = (char)waitKey(0);
    if(key == 27)
    {
      return EXIT_SUCCESS;
    }
    if (key == 'k' || key == 'K')
    {
      ksize = ksize < 30 ? ksize+2 : -1;
    }
    if (key == 's' || key == 'S')
    {
      scale++;
    }
    if (key == 'd' || key == 'D')
    {
      delta++;
    }
    if (key == 'r' || key == 'R')
    {
      scale =  1;
      ksize = -1;
      delta =  0;
    }
  }
  return EXIT_SUCCESS;
}
