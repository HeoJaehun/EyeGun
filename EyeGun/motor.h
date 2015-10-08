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
    void update();
    int setValue(int value);    // Value 0~180
    int getValue(){return m_i_value;};
    int addValue(); // Add value ~128
    int dcrValue(); // Decrease value 33~
    int setLimit(int low, int high);


private:
    int m_i_value;
    int m_i_pin;
    int m_i_low_limit;
    int m_i_high_limit;
};

#endif // MOTOR_H
