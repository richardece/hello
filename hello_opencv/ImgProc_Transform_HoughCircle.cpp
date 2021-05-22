#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

/*
Hough Circle transform - roughly simu=ilar to Hough line transform.
Instead of finding 2 parameters (r, theta), 
it looks for 3 parameters (x_center, y_center, r)
*/
int main(int argc, char** argv)
{
    const char* filename = "smarties.png";
    // Loads an image
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    Mat src = imread( samples::findFile( filename ), IMREAD_COLOR );
    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        return EXIT_FAILURE;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //Blur the image to avoid false circle detection
    medianBlur(gray, gray, 5);
    
    vector<Vec3f> circles;
    HoughCircles(gray, //input image (grayscale)
        circles,        //will store the parameter (x_center, y_center, r) of the detected circles
        HOUGH_GRADIENT, //detection method (currently, this is the only method)
        1,              //inverse ratio of resolution
        gray.rows/16,   // minimum distance between detected centers (change this value to detect circles with different distances to each other)
        100,            //upper threshold of the internal canny edge detector
        30,             //threshold for center detection
        1,              //minimum radius to be detected
        30              //maximum radius ot be detected
    );
    
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // draw circle center into the src
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // draw circle outline into the src
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }

    imshow("detected circles", src);
    
    waitKey();
    return EXIT_SUCCESS;
}