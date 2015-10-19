#include "eyegun.h"

EyeGun::EyeGun()
{
    m_i_fps = 60;
    m_i_screen_width = 500;
    m_i_screen_height = 500;
}


void EyeGun::init()
{
    m_motor_H.setup(PIN_MOTOR_H);
    m_motor_H.setLimit(60, 120);
    m_motor_H.setValue(90);
    m_motor_H.update();

    m_motor_V.setup(19);    // 13번 핀을 사용하기 위한 설정
    m_motor_V.setup(PIN_MOTOR_V);
    m_motor_V.setLimit(50, 130);
    m_motor_V.setValue(90);
    m_motor_V.update();

    m_laser.setup(PIN_LASER);
    m_button_led.setup(PIN_BUTTON_LED);

    m_head_switch.setup(PIN_HEADSWITCH);
    m_button.setup(PIN_BUTTON);

    m_calibrator.init();
    m_v_points.clear();
    m_v_angles.clear();

    eyeAngle angle;
    angle.thetaH = 60;
    angle.thetaV = 60;
    m_v_angles.push_back(angle);
    angle.thetaH = 120;
    angle.thetaV = 120;
    m_v_angles.push_back(angle);

    m_e_status = WAIT_MODE;

    m_frame = cv::Mat(m_i_screen_height, m_i_screen_width, CV_8UC1, cv::Scalar(0));

    cv::namedWindow("EyeGun");
}


void EyeGun::wait()
{
    if(m_head_switch.check())
    {
        m_e_status = CALIBRATE_MODE;
        m_button_led.on();
        m_laser.on();
        return;
    }
}


void EyeGun::calib()
{

    /*
     *첫번째 점(왼쪽 상단) 데이터 입력
     */
    m_motor_H.setValue(m_v_angles[0].thetaH);   // 모터 위치 조정
    m_motor_H.update();
    m_motor_V.setValue(m_v_angles[0].thetaV);   // 모터 위치 조정
    m_motor_V.update();

    m_b_wait_for_calib = true; // 데이터가 들오올 때 까지 기다림
    while(m_b_wait_for_calib)
    {

#ifdef DEBUG
        cv::imshow("EyeGun", m_frame);
#endif

        this->inputKeyboard();
        this->checkHeadSwitch();
    }
    // 모터가 향한 곳의 데이터 입력
    m_calibrator.setData(m_point, Point2f(0, 0));   // P1(0, 0)

#ifdef DEBUG
    std::cout << "Done: point 1" << std::endl;
#endif


    /*
     *두번째 점(오른쪽 상단) 데이터 입력
     */
    m_motor_H.setValue(m_v_angles[1].thetaH);   // 모터 위치 조정
    m_motor_H.update();
    m_motor_V.setValue(m_v_angles[0].thetaV);   // 모터 위치 조정
    m_motor_V.update();

    m_b_wait_for_calib = true; // 데이터가 들오올 때 까지 기다림
    while(m_b_wait_for_calib)
    {
        cv::imshow("EyeGun", m_frame);

        this->inputKeyboard();
        this->checkHeadSwitch();
    }
    // 모터가 향한 곳의 데이터 입력
    m_calibrator.setData(m_point, Point2f(2.0/sqrt(3), 0));

#ifdef DEBUG
    std::cout << "Done: point 2" << std::endl;
#endif

    /*
     *세번째 점(오른쪽 하단) 데이터 입력
     */
    m_motor_H.setValue(m_v_angles[1].thetaH);   // 모터 위치 조정
    m_motor_H.update();
    m_motor_V.setValue(m_v_angles[1].thetaV);   // 모터 위치 조정
    m_motor_V.update();

    m_b_wait_for_calib = true; // 데이터가 들오올 때 까지 기다림
    while(m_b_wait_for_calib)
    {
        cv::imshow("EyeGun", m_frame);

        this->inputKeyboard();

        this->checkHeadSwitch();
    }
    // 모터가 향한 곳의 데이터 입력
    m_calibrator.setData(m_point, Point2f(2.0/sqrt(3), 2.0/sqrt(3)));

#ifdef DEBUG
    std::cout << "Done: point 3" << std::endl;
#endif


    /*
     *네번째 점(왼쪽 하단) 데이터 입력
     */
    m_motor_H.setValue(m_v_angles[0].thetaH);   // 모터 위치 조정
    m_motor_H.update();
    m_motor_V.setValue(m_v_angles[1].thetaV);   // 모터 위치 조정
    m_motor_V.update();

    m_b_wait_for_calib = true; // 데이터가 들오올 때 까지 기다림
    while(m_b_wait_for_calib)
    {
        cv::imshow("EyeGun", m_frame);

        this->inputKeyboard();

        this->checkHeadSwitch();
    }
    // 모터가 향한 곳의 데이터 입력
    m_calibrator.setData(m_point, Point2f(0, 2.0/sqrt(3)));

#ifdef DEBUG
    std::cout << "Done: point 4" << std::endl;
#endif


    if (m_calibrator.getCondition())
    {
        m_calibrator.calculate();
        m_e_status = RUN_MODE;

        m_motor_H.setValue(90);   // 모터 위치 조정
        m_motor_H.update();
        m_motor_V.setValue(90);   // 모터 위치 조정
        m_motor_V.update();
    }

    return;
}


void EyeGun::run()
{

#ifdef DEBUG
    cv::imshow("EyeGun", m_frame);
#endif

    m_angle = m_calibrator.calib(m_point);

    cout << "H: " << m_angle.thetaH << "   V: " << m_angle.thetaV << endl;

    m_motor_H.setValue(m_angle.thetaH);
    m_motor_H.update();
    m_motor_V.setValue(m_angle.thetaV);
    m_motor_V.update();

    this->inputKeyboard();
    this->checkHeadSwitch();
}


void EyeGun::restart()
{
    m_e_status = WAIT_MODE;
    m_b_wait_for_calib = false;
    m_laser.off();
    m_button_led.off();

    m_motor_H.setValue(90);
    m_motor_H.update();
    m_motor_V.setValue(90);
    m_motor_V.update();

    if(m_calibrator.getCondition())
        m_calibrator.init();
}


void EyeGun::quit()
{
    m_motor_V.setValue(90);
    m_motor_V.update();
    m_motor_H.setValue(90);
    m_motor_H.update();

    std::cout << "Good Bye" << std::endl;
}


void EyeGun::inputKeyboard()
{
    switch(cv::waitKey(1000/m_i_fps))
    {
    case 27:
        this->restart();
        m_b_wait_for_calib = false;
        m_e_status = GOODBYE;
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


void EyeGun::checkHeadSwitch()
{
    if(m_head_switch.check() == false)
        this->restart();
}


void EyeGun::tempSetFirstMotorVal(int val)
{
    m_motor_V.setValue(val);
    m_motor_V.update();
}


void EyeGun::tempSetSecondMotorVal(int val)
{
    m_motor_H.setValue(val);
    m_motor_H.update();
}


void EyeGun::tempSetToggleLaser()
{
    m_laser.toggle();
}


void EyeGun::tempSetPoint(int x, int y)
{
    m_point.x = x;
    m_point.y = y;

    std::cout << "Input: (" << x << ", " << y << ")" << std::endl;
    m_b_wait_for_calib = false;
}
