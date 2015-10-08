#ifndef EYEGUN_H
#define EYEGUN_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <motor.h>
#include <laser.h>

class EyeGun
{
public:
    EyeGun();
    void init();
    void run();
    void inputKeyboard();

    void tempSetFirstMotorVal(int val);
    void tempSetSecondMotorVal(int val);
    void tempSetToggleLaser();

private:
    cv::Mat m_frame;
    Motor m_first_motor;
    Motor m_second_motor;
    Laser m_laser;

    int m_i_fps;
};

#endif // EYEGUN_H
