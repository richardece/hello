#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

/*
Hough transform - used to detect straight lines
An edge detection pre-procesisng is desirable.
It detects a line by finding a number of intersections between curves.
If the number of intersections is above some threshold, it is declared as a line 
[Don't fully understand. need to review cartesian and polar coordinate system]
*/
int main(int argc, char** argv)
{
    // Declare the output variables
    Mat dst, cdst, cdstP;
    const char* filename = "sudoku.png";
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    // Loads an image
    Mat src = imread( samples::findFile( filename ), IMREAD_GRAYSCALE );
    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        return -1;
    }
    
    // Edge detection
    Canny(src,  //input image
        dst,    //output image
        50,     //low threshold
        200,    //high threshold
        3);     //kernel size
    
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    
    // Standard Hough Line Transform
    vector<Vec2f> lines; // will hold the results of the detection
    // runs the actual detection
    HoughLines(dst, //input image (actually, this is the output of canny edge detector)
        lines,      //will store the parameter (r, theta) of the detected lines
        1,          //resolution of the parameter r in pixels (use 1 pixel)
        CV_PI/180,  //resolution of the parameter theta on radians (use 1 degree)
        150,        //minimum number of intersections to detect a line
        0, 
        0 ); 
    
    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }
    
    // Probabilistic Line Transform, a more efficient implementation of the standard hough transform
    vector<Vec4i> linesP; // will hold the results of the detection
    // runs the actual detection
    HoughLinesP(dst, 
        linesP, //will store the parameters (x_start, y_start, x_end, y_end) of the detected line
        1, 
        CV_PI/180, 
        50,     //minimum number of intersections to detect a line
        50,     //minimum number of points that can form a line
        10 );   //maximum gap between 2 points ot be considered in one line
 
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }
 
    // Show results
    imshow("Source", src);
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

    // Wait and Exit
    waitKey();
    return 0;
}