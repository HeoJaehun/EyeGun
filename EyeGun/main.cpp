#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <motor.h>
#include <laser.h>

cv::Mat frame;
Motor f_motor;
Motor s_motor;
Laser f_laser;

static void onMouse(int event, int x, int y, int, void*)
{
    if(event == cv::EVENT_MOUSEMOVE)
    {
        float f_temp = (float)x/500.0;
        int f_input = (int)(f_temp*180);
        f_motor.setValue(f_input);
        f_motor.update();

        float s_temp = (float)y/500.0;
        int s_input = (int)(s_temp*180);
        s_motor.setValue(s_input);
        s_motor.update();


        //std::cout << "Pos : (" << x << ", " << y << ")  input: (" << f_input << ", " << s_input << ")" << std::endl;
    }

    if(event == cv::EVENT_LBUTTONDOWN)
    f_laser.toggle();
}


int main()
{
    f_motor.setup(19);
    f_motor.setup(13);
    s_motor.setup(18);
    f_laser.setup(15);

    frame = cv::Mat(500, 500, CV_8UC1, cv::Scalar(0));

    cv::namedWindow("EyeGun");
    cv::setMouseCallback("EyeGun", onMouse, 0);

    while(1)
    {
        cv::imshow("EyeGun", frame);

        switch(cv::waitKey(1000/60))
        {
        case 27:
            std::cout << "Good Bye" << std::endl;
            exit(0);
            break;
        }
    }

    return 0;
}
