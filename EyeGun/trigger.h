#ifndef TRIGGER_H
#define TRIGGER_H

#include <wiringPi.h>
#include <iostream>
#include <stdlib.h>

class Trigger
{
public:
    Trigger();
    ~Trigger();
    void setup(int pin);
    bool check();

private:
    int m_i_pin;
};

#endif // TRIGGER_H
