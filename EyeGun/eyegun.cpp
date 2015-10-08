#include "eyegun.h"

EyeGun::EyeGun()
{
    m_b_run = true;
    m_i_fps = 60;
    m_i_screen_width = 500;
    m_i_screen_height = 500;
}


void EyeGun::init()
{
    m_first_motor.setup(19);  // 13번 핀을 사용하기 위한 설정
    m_first_motor.setup(13);
    m_first_motor.setLimit(50, 130);
    m_first_motor.setValue(90);
    m_first_motor.update();

    m_second_motor.setup(18);
    m_second_motor.setLimit(70, 128);
    m_second_motor.setValue(90);
    m_second_motor.update();

    m_laser.setup(15);

    m_frame = cv::Mat(m_i_screen_height, m_i_screen_width, CV_8UC1, cv::Scalar(0));

    cv::namedWindow("EyeGun");
}


void EyeGun::run()
{
    while(m_b_run)
    {
        cv::imshow("EyeGun", m_frame);

        this->inputKeyboard();
    }
}


void EyeGun::quit()
{
    m_first_motor.setValue(90);
    m_first_motor.update();
    m_second_motor.setValue(90);
    m_second_motor.update();

    std::cout << "Good Bye" << std::endl;
}


void EyeGun::inputKeyboard()
{
    switch(cv::waitKey(1000/m_i_fps))
    {
    case 27:
        m_b_run = false;
        break;
    }
}


int EyeGun::getScreenWidth()
{
    return m_i_screen_width;
}


int EyeGun::getScreenHeight()
{
    return m_i_screen_height;
}


void EyeGun::tempSetFirstMotorVal(int val)
{
    m_first_motor.setValue(val);
    m_first_motor.update();
}


void EyeGun::tempSetSecondMotorVal(int val)
{
    m_second_motor.setValue(val);
    m_second_motor.update();
}


void EyeGun::tempSetToggleLaser()
{
    m_laser.toggle();
}
