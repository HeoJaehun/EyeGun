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
        int screen_width = eg.getScreenWidth();
        float f_temp = (float)x/screen_width;
        int f_input = (int)(f_temp*180);

        eg.tempSetFirstMotorVal(f_input);

        int screen_height = eg.getScreenHeight();
        float s_temp = (float)y/screen_height;
        int s_input = (int)(s_temp*180);

        eg.tempSetSecondMotorVal(s_input);

        std::cout << "Pos : (" << x << ", " << y << ")  input: (" << f_input << ", " << s_input << ")" << std::endl;
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
    eg.quit();

    return 0;
}
