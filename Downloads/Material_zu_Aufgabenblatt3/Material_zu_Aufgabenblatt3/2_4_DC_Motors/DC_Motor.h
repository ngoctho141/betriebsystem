#include <unistd.h>
#include "pwmDriver.h"

using namespace std;
using namespace exploringRPi;

class DC_Motor {
private:
   PWMDriver* m_pwmDriver;   // The pointer to the PCA9685 driver
   int m_channel;            // PWM output channel {4 or 5}
   int m_A;                  // GPIO enable pin A {17 or 27}
   int m_B;                  // GPIO enable pin B {18 or 28}
   int m_speed;              // speed range -100 - +100%
   bool m_reverse;           // rotation in opposite direction 

public:
   DC_Motor(PWMDriver* pwmDriver, int channel, int A, int B, bool reverse);
   virtual ~DC_Motor(){};

   int setSpeed(int speed); // speed range -100 - +100%
   int  getSpeed(void) { return m_speed; }
};

