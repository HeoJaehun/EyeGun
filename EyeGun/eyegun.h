#ifndef EYEGUN_H
#define EYEGUN_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <motor.h>
#include <laser.h>
#include <trigger.h>
#include <eyeguncalibrator.hpp>

#define PIN_MOTOR_H 18
#define PIN_MOTOR_V 13
#define PIN_LASER  15
#define PIN_BUTTON 10
#define PIN_BUTTON_LED 12
#define PIN_HEADSWITCH 25

#define DEBUG


enum status {WAIT_MODE, RUN_MODE, CALIBRATE_MODE, GOODBYE};

class EyeGun
{
public:
    EyeGun();
    void init();
    void wait();
    void calib();
    void run();
    void restart();
    void quit();

    void inputKeyboard();
    int getScreenWidth();
    int getScreenHeight();
    enum status getStatus(){return m_e_status;};
    void checkHeadSwitch();

    void tempSetFirstMotorVal(int val);
    void tempSetSecondMotorVal(int val);
    void tempSetToggleLaser();
    void tempSetPoint(int x, int y);

private:
    cv::Mat m_frame;
    Motor m_motor_V;
    Motor m_motor_H;
    Laser m_laser;
    Laser m_button_led;
    Trigger m_head_switch;
    Trigger m_button;
    EyeGunCalibrator m_calibrator;

    int m_i_fps;
    int m_i_screen_width;
    int m_i_screen_height;

    bool m_b_wait_for_calib;

    vector<Point2f> m_v_points;
    vector<eyeAngle> m_v_angles;
    Point2f m_point;
    eyeAngle m_angle;
    enum status m_e_status;
};

#endif // EYEGUN_H
