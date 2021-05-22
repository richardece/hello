#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 1000;
int MAX_KERNEL_LENGTH = 31;
Mat src; Mat dst;
char window_name[] = "Smoothing Demo";
int display_caption( const char* caption );
int display_dst( int delay );

//Shows different algorithms for filtering/smoothing images
int main( int argc, char ** argv )
{
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");

    namedWindow( window_name, WINDOW_AUTOSIZE );
    src = imread( samples::findFile( "lena.jpg" ), IMREAD_COLOR );
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if( display_caption( "Original Image" ) != 0 )
    {
        return 0;
    }
    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
    {
        return 0;
    }

    if( display_caption( "Homogeneous Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        //Normalized blur filter, the simplest filter
        //Each output pixel is the mean of its kernel neighbors 
        blur( src,          //source image
            dst,            //destination image
            Size( i, i ),   //size of kernel
            Point(-1,-1) ); //Indicates where the anchor point (the pixel evaluated) 
                            //is located with respect to the neighborhood. 
                            //If there is a negative value, then the center of the kernel is considered the anchor point
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }

    if( display_caption( "Gaussian Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        //Pixel located in the middle would have the largest weight
        //The weight of its neighbors decreases as the spatial distance between them and the center pixel increases.
        GaussianBlur( src, //source image
            dst,            //destination image
            Size( i, i ),   //size of kernel, must be odd and positive
            0,              //standard deviation in x. 0 means SD is calculated using kernel size
            0 );            //standard deviation in y. 0 means SD is calculated using kernel size

        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }

    if( display_caption( "Median Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        //Uses the meadian of its neighboring pixels
        medianBlur ( src, //source image
            dst,           //destination image
            i );            //size of the kernel
                            //kernel is square, so only one number is needed
                            //size must be odd number
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }

    if( display_caption( "Bilateral Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        //Similar to gaussian filter
        //but avoids smoothing out the edgesmake -j6

        bilateralFilter ( src, //source image
            dst,                //destination image
            i,                  //diameter of each pixel neighborhood
            i*2,                //standard deviation in the color space
            i/2 );              //standard deviation in the coordinate space (in pixel)
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    display_caption( "Done!" );
    return 0;
}
int display_caption( const char* caption )
{
    dst = Mat::zeros( src.size(), src.type() );
    putText( dst, caption,
             Point( src.cols/4, src.rows/2),
             FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );
    return display_dst(DELAY_CAPTION);
}

int display_dst( int delay )
{
    imshow( window_name, dst );
    int c = waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
}


