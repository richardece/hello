#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
Affine transformation - expressed in a form of matrix multiplication (linear transformation)
    followed by vector addition (translation)
Used to perform:
    1. rotation (linear transformation)
    2. translation (vector addition)
    3. scale operation (linear transformation)
*/
int main( int argc, char** argv )
{
    samples::addSamplesDataSearchPath("/home/richard/Downloads/opencv-master/samples/data");
    Mat src = imread( samples::findFile( "lena.jpg" ) );
    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        return -1;
    }

    //1. We need 2 sets of 3 points to derive the affine transform relation.
    Point2f srcTri[3];
    srcTri[0] = Point2f( 0.f, 0.f );
    srcTri[1] = Point2f( src.cols - 1.f, 0.f );
    srcTri[2] = Point2f( 0.f, src.rows - 1.f );

    Point2f dstTri[3];
    dstTri[0] = Point2f( 0.f, src.rows*0.33f );
    dstTri[1] = Point2f( src.cols*0.85f, src.rows*0.25f );
    dstTri[2] = Point2f( src.cols*0.15f, src.rows*0.7f );

    //2. Compute the affine transform
    Mat warp_mat = getAffineTransform( srcTri, dstTri );
    
    //3. Apply the affine transform to the src image
    Mat warp_dst = Mat::zeros( src.rows, src.cols, src.type() );
    warpAffine( src,    //input image
        warp_dst,       //output image
        warp_mat,       //Affine transform
        warp_dst.size() );  //desired size of the output image

    //Will be used for rotation
    Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
    double angle = -50.0;
    double scale = 0.6;

    //4. Generate the rotation matrix, will return a 2x3 matrix
    Mat rot_mat = getRotationMatrix2D( center,  //center to which the image wil rotate
                                        angle,  //angle to be rotated, positive angle is counter clockwise
                                        scale );//scale factor
                                        
    //5. Apply the rotation matrix to output of previous transformation                                    
    Mat warp_rotate_dst;
    warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );

    imshow( "Source image", src );
    imshow( "Warp", warp_dst );
    imshow( "Warp + Rotate", warp_rotate_dst );
    
    waitKey();
    return 0;
}



