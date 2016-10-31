#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
    VideoCapture capture;
    capture.open(0);
    Mat frame;

    Scalar orange_min_1 = Scalar(5,90,90);
    Scalar orange_max_1 = Scalar(160,90,90);

    Scalar orange_min_2 = Scalar(35, 255, 255);
    Scalar orange_max_2 = Scalar(179, 255, 255);

    while(capture.read(frame))
    {
        flip(frame, frame, 1); //1 indicates a rotation around y axis
        Mat hsv_image;
        cvtColor(frame, hsv_image, COLOR_BGR2HSV); //needs to be in HSV format for color thresholding

        //strip things outside range given by lower and upper
        Mat lower_orange_hue_range;
        Mat upper_orange_hue_range;

        //strip pixels not in range given above
        inRange(hsv_image, orange_min_1, orange_min_2, lower_orange_hue_range);
        inRange(hsv_image, orange_max_1, orange_max_2, upper_orange_hue_range);


        //add the two mats generated above
        Mat orange_hue_image;
        addWeighted(lower_orange_hue_range, 1.0, upper_orange_hue_range, 1.0, 0.0, orange_hue_image);
        GaussianBlur(orange_hue_image, orange_hue_image, Size(39,39), 2, 2);

        //show the image
        imshow("Tracking Color Orange", orange_hue_image);

        waitKey(10);

    }
}
