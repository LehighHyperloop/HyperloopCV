#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void createAlert();

const int TAPE_THRESHOLD = 1000;

int main()
{
    VideoCapture capture;
    capture.open(0);
    Mat frame;

    //currently tracks only on brightness ranged 220-255, might be wise to limit hue
    //range as well to take out false positives. Also will need to tweak 220-255 range most likely
    Scalar brightness_min = Scalar(0,0,220);
    Scalar brightness_max = Scalar(255,255,255); //Hue, Saturation, Value (Brightness)

    int pixelCount;

    while(capture.read(frame))
    {
        flip(frame, frame, 1); //1 indicates a rotation around y axis
        Mat hsv_image;
        cvtColor(frame, hsv_image, COLOR_BGR2HSV); //needs to be in HSV format for color thresholding

        Mat result;

        //strip pixels not in brightness range given above
        inRange(hsv_image, brightness_min, brightness_max, result);

        //add the two mats generated above
        GaussianBlur(result, result, Size(39,39), 2, 2);

        pixelCount = countNonZero(result);

        //check how much brightness is detected, alert if over a certain threshold
        //might replace with a check for a rectangle if needed later
        if (pixelCount > TAPE_THRESHOLD)
        {
            createAlert();
        }

        //show the image
        imshow("Tracking Color Orange", result);

        waitKey(10);

    }
}

//noop for now, will eventually be set up to send a signal in some way or another
void createAlert()
{

}
