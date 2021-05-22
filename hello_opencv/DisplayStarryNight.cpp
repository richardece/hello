//This sample app loads an image from file, displays image in a window and save image in  another file

#include <opencv2/core.hpp>     //Basic building blocks
#include <opencv2/imgcodecs.hpp>//Read write functions
#include <opencv2/highgui.hpp>  //Show image in a window
#include <iostream>
using namespace cv;
int main()
{
    //Search for the file in the same directory as the executable
    std::string image_path = samples::findFile("lena.jpeg");

    //Load the image
    //IMREAD_COLOR:         RGB 8-bit
    //IMREAD_GRAYSCALE:     grayscale
    //IMREAD_GUNCHANGED:    as is
    Mat img = imread(image_path, IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    //Display image in a window
    imshow("Hi there", img);

    // Wait for a keystroke in the window
    int k = waitKey(0); 
    if(k == 's')
    {
        imwrite("starry_night.png", img);
    }
    return 0;
}