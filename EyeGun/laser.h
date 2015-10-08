#ifndef LASER_H
#define LASER_H

#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>

class Laser
{
public:
    Laser();
    ~Laser();
    void setup(int pin);
    void on();
    void off();
    void toggle();

private:
    int m_i_switch;
    int m_i_pin;
    bool m_b_toggle;
};

#endif // LASER_H
