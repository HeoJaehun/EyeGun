#include "motor.h"

Motor::Motor()
{

}

void Motor::setup(int pin)
{
    if(wiringPiSetupGpio() < 0)
    {
        std::cerr << "Error: WiringPi Setup Fail" << std::endl;
        exit(-1);
    }

    m_i_pin = pin;
    pinMode(m_i_pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(400);
    pwmSetRange(1024);
}

int Motor::setValue(int value)
{   
    if(value > 180)
    {
        std::cerr << "ERR: Value is too big! ~180" << std::endl;
        return 1;
    }
    else if(value < 0)
    {
        std::cerr << "ERR: Value is too small! 0~" << std::endl;
        return 1;
    }

    float temp;
    temp = (float)value/180.0;
    m_i_value = (int)(95 - temp * 95) + 33;
    return 0;
}

int Motor::addValue()
{
    m_i_value++;
    return m_i_value;
}

int Motor::dcrValue()
{
    m_i_value--;
    return m_i_value;
}

void Motor::update()
{
    pwmWrite(m_i_pin, m_i_value);
}
