#include "laser.h"

Laser::Laser()
{
    if(wiringPiSetupGpio() < 0)
    {
        std::cerr << "Error: WiringPi Setup Fail" << std::endl;
        exit(-1);
    }
}

Laser::~Laser()
{
    off();
}

void Laser::setup(int pin)
{
    m_i_pin = pin;
    pinMode(m_i_pin, OUTPUT);
    m_b_toggle = false;
}

void Laser::on()
{
    digitalWrite(m_i_pin, HIGH);
}

void Laser::off()
{
    digitalWrite(m_i_pin, LOW);
}

void Laser::toggle()
{
    if (m_b_toggle == false)
    {
        on();
        m_b_toggle = true;
    }
    else
    {
        off();
        m_b_toggle = false;
    }
}
