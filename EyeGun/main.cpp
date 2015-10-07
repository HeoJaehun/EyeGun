#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>

int main()
{
    cv::Mat src;
    cv::VideoCapture cap;

    cap.open(0);

    if(!cap.isOpened())
    {
        std::cout << "ERR: Cannot open Camera" << std::endl;
        exit(1);
    }

    cv::namedWindow("EyeGun");

    src = cv::Mat(480, 640, CV_8UC3);

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    while(1)
    {
        cap >> src;
        cv::cvtColor(src, src, CV_BGR2GRAY);
        cv::imshow("EyeGun", src);

        switch(cv::waitKey(1000/60))
        {
        case 27:
            std::cout << "GoodBye!!!" << std::endl;
            exit(0);
            break;
        }
    }
    return 0;
}
