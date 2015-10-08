#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>

class Motor
{
public:
    Motor();

    void setup(int pin);
    int setValue(int value);    // Value 0~180
    int getValue(){return m_i_value;};
    int addValue(); // Add value ~128
    int dcrValue(); // Decrease value 33~
    void update();

private:
    int m_i_value;
    int m_i_pin;
};

#endif // MOTOR_H
