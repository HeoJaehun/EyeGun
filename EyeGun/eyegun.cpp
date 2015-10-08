#include "eyegun.h"

EyeGun::EyeGun()
{
    m_i_fps = 60;
}


void EyeGun::init()
{
    m_first_motor.setup(19);  // 13번 핀을 사용하기 위한 설정
    m_first_motor.setup(13);
    m_second_motor.setup(18);
    m_laser.setup(15);

    m_frame = cv::Mat(500, 500, CV_8UC1, cv::Scalar(0));

    cv::namedWindow("EyeGun");
}


void EyeGun::run()
{
    while(1)
    {
        cv::imshow("EyeGun", m_frame);

        this->inputKeyboard();
    }
}


void EyeGun::inputKeyboard()
{
    switch(cv::waitKey(1000/m_i_fps))
    {
    case 27:
        std::cout << "Good Bye" << std::endl;
        exit(0);
        break;
    }
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
