#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <eyegun.h>

EyeGun eg;

// temp
static void onMouse(int event, int x, int y, int, void*)
{
    if(event == cv::EVENT_MOUSEMOVE)
    {
        float f_temp = (float)x/500.0;
        int f_input = (int)(f_temp*180);
        eg.tempSetFirstMotorVal(f_input);

        float s_temp = (float)y/500.0;
        int s_input = (int)(s_temp*180);
        eg.tempSetSecondMotorVal(s_input);

        //std::cout << "Pos : (" << x << ", " << y << ")  input: (" << f_input << ", " << s_input << ")" << std::endl;
    }

    if(event == cv::EVENT_LBUTTONDOWN)
        eg.tempSetToggleLaser();
}

int main()
{
    eg.init();

    // temp
    cv::setMouseCallback("EyeGun", onMouse, 0);

    eg.run();

    return 0;
}
