#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    int ksize = 5;

    VideoCapture cap(0);

    if(!cap.isOpened()) {
        cout << "Error" << endl;
        return -1;
    }

    while(1) {
        Mat frame;
        Mat blur_frame;
        Mat red_frame;
        Mat gray_frame;
        Mat bord_frame;
        cap >> frame;

        if(frame.empty()) {
            cout << "Frame empty" << endl;
            break;
        }

        blur(frame, blur_frame, Size(ksize, ksize), Point(-1,-1));
        cvtColor(frame, red_frame, COLOR_BGR2HSV);
        inRange(red_frame, Scalar(170, 70, 50), Scalar(180, 255, 255), red_frame);
        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
        bord_frame = gray_frame.clone();
        Canny(gray_frame, bord_frame, 10, 100, 3);

        imshow("Frame", frame);
        imshow("Blur frame", blur_frame);
        imshow("Red frame", red_frame);
        imshow("Canny frame", bord_frame);

        char c=(char)waitKey(25);
        if(c==27)
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
