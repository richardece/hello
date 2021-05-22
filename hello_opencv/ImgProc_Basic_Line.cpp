#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define w 400

using namespace cv;

void MyEllipse( Mat img, double angle );
void MyFilledCircle( Mat img, Point center );
void MyPolygon( Mat img );
void MyLine( Mat img, Point start, Point end );

int main( void ){
  char atom_window[] = "Drawing 1: Atom";
  char rook_window[] = "Drawing 2: Rook";

  //Create 2 images with black background
  Mat atom_image = Mat::zeros( w, w, CV_8UC3 );
  Mat rook_image = Mat::zeros( w, w, CV_8UC3 );

  //Draw 4 ellipses rotated in different angles 
  MyEllipse( atom_image, 90 );
  MyEllipse( atom_image, 0 );
  MyEllipse( atom_image, 45 );
  MyEllipse( atom_image, -45 );

  //Draw circle with the specified center point
  MyFilledCircle( atom_image, Point( w/2, w/2) );

  //Draw a polygon with shape of a rook from chess
  MyPolygon( rook_image );

  //Draw a giant rectangle at the bottom of the rook
  rectangle( rook_image,
         Point( 0, 7*w/8 ),     //top-left point of the rectangle
         Point( w, w),          //bottom-right point of the ractangle
         Scalar( 0, 255, 255 ), //means yellow
         FILLED,                //filled with the above color
         LINE_8 );

  //Draw lines inside the rectangle
  MyLine( rook_image, Point( 0, 15*w/16 ), Point( w, 15*w/16 ) );
  MyLine( rook_image, Point( w/4, 7*w/8 ), Point( w/4, w ) );
  MyLine( rook_image, Point( w/2, 7*w/8 ), Point( w/2, w ) );
  MyLine( rook_image, Point( 3*w/4, 7*w/8 ), Point( 3*w/4, w ) );

  imshow( atom_window, atom_image );
  moveWindow( atom_window, 0, 200 );
  imshow( rook_window, rook_image );
  moveWindow( rook_window, w, 200 );

  waitKey( 0 );
  return(0);
}
void MyEllipse( Mat img, double angle )
{
  int thickness = 2;
  int lineType = 8;
  ellipse( img,             //display the ellipse in this image
       Point( w/2, w/2 ),   //ellipse center is in this point
       Size( w/4, w/16 ),   //ellipse is enclosed in a box with this size 
       angle,               //ellipse is rotated "angle" degrees
       0,                   //ellipse extends an arc between 0 and 360 degrees
       360,
       Scalar( 255, 0, 0 ), //Color of the ellipse is (255,0,0) which means blue in BGR format
       thickness,           //thickness
       lineType );
}
void MyFilledCircle( Mat img, Point center )
{
  circle( img,              //draw the circle in this image
      center,               //center of the circle
      w/32,                 //radius of the circle
      Scalar( 0, 0, 255 ),  //color of the circle (means red in BGR)
      FILLED,               //Thickeness of -1 means to fill the image
      LINE_8 );
}
void MyPolygon( Mat img )
{
  int lineType = LINE_8;

  //Polygon points
  Point rook_points[1][20];
  rook_points[0][0]  = Point(    w/4,   7*w/8 );
  rook_points[0][1]  = Point(  3*w/4,   7*w/8 );
  rook_points[0][2]  = Point(  3*w/4,  13*w/16 );
  rook_points[0][3]  = Point( 11*w/16, 13*w/16 );
  rook_points[0][4]  = Point( 19*w/32,  3*w/8 );
  rook_points[0][5]  = Point(  3*w/4,   3*w/8 );
  rook_points[0][6]  = Point(  3*w/4,     w/8 );
  rook_points[0][7]  = Point( 26*w/40,    w/8 );
  rook_points[0][8]  = Point( 26*w/40,    w/4 );
  rook_points[0][9]  = Point( 22*w/40,    w/4 );
  rook_points[0][10] = Point( 22*w/40,    w/8 );
  rook_points[0][11] = Point( 18*w/40,    w/8 );
  rook_points[0][12] = Point( 18*w/40,    w/4 );
  rook_points[0][13] = Point( 14*w/40,    w/4 );
  rook_points[0][14] = Point( 14*w/40,    w/8 );
  rook_points[0][15] = Point(    w/4,     w/8 );
  rook_points[0][16] = Point(    w/4,   3*w/8 );
  rook_points[0][17] = Point( 13*w/32,  3*w/8 );
  rook_points[0][18] = Point(  5*w/16, 13*w/16 );
  rook_points[0][19] = Point(    w/4,  13*w/16 );

  const Point* ppt[1] = { rook_points[0] };
  int npt[] = { 20 };

  fillPoly( img,                //Draw polygon on this image
        ppt,                    //vertices of the polygon
        npt,                    //???
        1,                      //???
        Scalar( 255, 255, 255 ),//color (white)
        lineType );
}
void MyLine( Mat img, Point start, Point end )
{
  int thickness = 2;
  int lineType = LINE_8;
  line( img,
    start,              //starting point of the line
    end,                //end point of the line
    Scalar( 0, 0, 0 ),  //means black in BGR
    thickness,
    lineType );
}