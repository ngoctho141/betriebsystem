#include <wiringPi.h>
#include <iostream>
#include "DC_Motor.h"

DC_Motor::DC_Motor(PWMDriver* pwmDriver, int channel, int A, int B,
    bool reverse): m_pwmDriver(pwmDriver),m_channel(channel),
    m_A(A),m_B(B),m_reverse(reverse)
{
}

int DC_Motor::setSpeed(int speed)
{
    if(speed>100 || speed<-100 || m_pwmDriver==0) return -1;
    if(speed==0)
    {
        // ...
    }
    else if(speed>0)
    {
        if(!m_reverse) {digitalWrite(m_A,LOW);digitalWrite(m_B,HIGH);}
        else {digitalWrite(m_A,HIGH);digitalWrite(m_B,LOW);}
        m_pwmDriver->setOutput(m_channel,speed);
    } 
    else if(speed<0)
    {
        // ...
    }
    return 0;
}

