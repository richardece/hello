#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    Mat src = imread( samples::findFile( "lena.jpg" ), IMREAD_COLOR );
    if( src.empty() )
    {
        return EXIT_FAILURE;
    }

    //1. Split the src into BGR planes
    vector<Mat> bgr_planes;
    split( src, bgr_planes );

    //2. Calculate histogram per plane
    int histSize = 256;     //number of bins for the histogram [0:255]
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], //source array
        1,      //number of source array
        0,      //channel to be measured. This example is just the intensity, so we just write 0
        Mat(),  //mask to be used in on the source array (zeroes indicating pixels to be ignored). not defined here, so not used
        r_hist, //where the histogram will be stored
        1,      //histogram dimension
        &histSize,  //number of bins per used dimension
        &histRange, //range of values to ne measured per dimension
        uniform,    //bin sizes are the same
        accumulate );   //histogram is cleared at the beginning
    
    //3. Create an image to display the histogram
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    
    //4. Normalize the histogram so that its values fall in the range indicated by the function parameters
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist,   //input array
        r_hist,         //output array
        0,              //lower limit to normalize the values of r_hist
        histImage.rows, //upper limit
        NORM_MINMAX,    //type of normalization
        -1,             //indicates that the output normalized array will be same type as input
        Mat() );        //optional mask

    //5. Display the histogram
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }

    imshow("Source image", src );
    imshow("calcHist Demo", histImage );

    waitKey();
    return EXIT_SUCCESS;
}