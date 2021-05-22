#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

/*
Remapping - process of taking pixels from one place of the image and placing  them
    in another position in a new image (like flipping, reducing picture, etc)
*/
void update_map( int &ind, Mat &map_x, Mat &map_y );
int main(int argc, const char** argv)
{
    std::string filename = "chicky_512.png";
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    Mat src = imread( samples::findFile( filename ), IMREAD_COLOR );
    if (src.empty())
    {
        std::cout << "Cannot read image: " << filename << std::endl;
        return -1;
    }
    Mat dst(src.size(), src.type());
    Mat map_x(src.size(), CV_32FC1);
    Mat map_y(src.size(), CV_32FC1);
    const char* remap_window = "Remap demo";
    namedWindow( remap_window, WINDOW_AUTOSIZE );

    int ind = 0;
    for(;;)
    {
        update_map(ind, map_x, map_y);
        
        remap( src,     //input image
            dst,        //output image
            map_x,      //mapping function in hte x direction
            map_y, 
            INTER_LINEAR, //interpolation to be used for non-integer pixels
            BORDER_CONSTANT, 
            Scalar(0, 0, 0) );
        
        imshow( remap_window, dst );
        
        char c = (char)waitKey( 1000 );
        if( c == 27 )
        { break;}
    }
    return 0;
}
void update_map( int &ind, Mat &map_x, Mat &map_y )
{
    for( int i = 0; i < map_x.rows; i++ )
    {
        for( int j = 0; j < map_x.cols; j++ )
        {
            switch( ind )
            {
            //Reduce picture to half its size and display it in the middle
            case 0:
                if( j > map_x.cols*0.25 && j < map_x.cols*0.75 && i > map_x.rows*0.25 && i < map_x.rows*0.75 )
                {
                    map_x.at<float>(i, j) = 2*( j - map_x.cols*0.25f ) + 0.5f;
                    map_y.at<float>(i, j) = 2*( i - map_x.rows*0.25f ) + 0.5f;
                }
                else
                {
                    map_x.at<float>(i, j) = 0;
                    map_y.at<float>(i, j) = 0;
                }
                break;

            //Turn the image upside down
            case 1:
                map_x.at<float>(i, j) = (float)j;
                map_y.at<float>(i, j) = (float)(map_x.rows - i);
                break;

            //Flip the image left to right
            case 2:
                map_x.at<float>(i, j) = (float)(map_x.cols - j);
                map_y.at<float>(i, j) = (float)i;
                break;

            //Combination of case 1 and 2
            case 3:
                map_x.at<float>(i, j) = (float)(map_x.cols - j);
                map_y.at<float>(i, j) = (float)(map_x.rows - i);
                break;
            default:
                break;
            } // end of switch
        }
    }
    ind = (ind+1) % 4;
}