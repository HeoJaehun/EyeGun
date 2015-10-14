#include "trigger.h"

Trigger::Trigger()
{
    if(wiringPiSetupGpio() < 0)
    {
        std::cerr << "Error: WiringPi Setup Fail" << std::endl;
        exit(-1);
    }
}


Trigger::~Trigger()
{

}


void Trigger::setup(int pin)
{
    m_i_pin = pin;
    pinMode(m_i_pin, INPUT);
}

bool Trigger::check()
{
    if(digitalRead(m_i_pin)==LOW)   // Push
        return true;

    else
        return false;
}
