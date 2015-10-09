#ifndef EYEGUN_H
#define EYEGUN_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <motor.h>
#include <laser.h>
#include <eyeguncalibrator.hpp>
enum status {RUN_MODE, CALIBRATE_MODE};

class EyeGun
{
public:
    EyeGun();
    void init();
    void calibrate();
    void run();
    void quit();
    void inputKeyboard();
    int getScreenWidth();
    int getScreenHeight();
    enum status getStatus(){return m_e_status;};

    void tempSetFirstMotorVal(int val);
    void tempSetSecondMotorVal(int val);
    void tempSetToggleLaser();
    void tempSetPoint(int x, int y);

private:
    cv::Mat m_frame;
    Motor m_motor_V;
    Motor m_motor_H;
    Laser m_laser;
    EyeGunCalibrator m_calibrator;

    int m_i_fps;
    int m_i_screen_width;
    int m_i_screen_height;

    bool m_b_run;
    bool m_b_wait;

    vector<eyeGunVector> m_v_points;
    vector<eyeGunAngle> m_v_angles;
    eyeGunVector m_point;
    eyeGunAngle m_angle;

    enum status m_e_status;
};

#endif // EYEGUN_H
