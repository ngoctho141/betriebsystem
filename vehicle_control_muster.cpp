
/*
 * Mit Applikation kümmert sich um die periodische Ansteuerung aller
 * Servo- und DC-Motoren. Wir werden diesen Prozess später noch erweitern
 */

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
#include <wiringPi.h>
#include "Servo.h"
#include "DC_Motor.h"

using namespace std;
using namespace exploringRPi;

#define GPIO_LA  17                   // this is GPIO17, pin 11
#define GPIO_LB  18                   // this is GPIO18, pin 12
#define GPIO_RA  27                   // this is GPIO27, pin 13
#define GPIO_RB  22                   // this is GPIO22, pin 15
#define _delay_ 100000


float calc_dc(float ms,float frequency)
{
   return ms*frequency/10;
}

int main(int argc, char** argv) 
{
    // init GPIOs
    wiringPiSetupGpio();                // use GPIO not WPi labels
    pinMode(GPIO_LA, OUTPUT);           // output pin
    // ...

    // init Servos
    PWMDriver *driver = new PWMDriver(1,0x40);
    driver->reset();
    float frequency = 60.0f;
    float servo_range = 90.0;
    driver->setFrequency(frequency); 

    Servo servo_s(driver, 0, servo_range); // servo for steering
    servo_s.calibrate(calc_dc(0.6,frequency), calc_dc(2.34,frequency)); 
    servo_s.setMountingRange(/*.. insert calibration data here: min/max/start ....*/); // steering on 0

    Servo servo_p(driver, 14, servo_range); // servo for camera pan
    servo_p.calibrate(calc_dc(0.6,frequency), calc_dc(2.34,frequency)); 
    servo_p.setMountingRange(/*.. insert calibration data here: min/max/start ....*/); // camera pan motor on 14

    Servo servo_t(driver, 15, servo_range); // servo for camera tilt
    servo_t.calibrate(calc_dc(0.6,frequency), calc_dc(2.34,frequency)); 
    servo_t.setMountingRange(/*.. insert calibration data here: min/max/start ....*/); // camera tilt motor on 15

    // init DC motors
    DC_Motor motor_l(driver,4,GPIO_LA,GPIO_LB,false);
    DC_Motor motor_r(driver,5,GPIO_RA,GPIO_RB,true);
   
#define __test_motors__   
#ifdef __test_motors__   
    float speed= 100;
	// do for motor_l und motor_r ...
    for (int i = 0; i < 2; i++)
    {
		// ...setSpeed(speed)
        getchar();

        // ...setSpeed(0)
        getchar();

		// ...setSpeed(-speed)
        getchar();
		
		// ...setSpeed(0)
		getchar();
    }
#endif
	   
#define __test_servos__
#ifdef __test_servos__
	// do for all servos ...
    for (int i = 0; i < 3; i++)
    {
        // ramp form start to max position:
		cout << "from " << ...getPhysPos() << " to " << ...getPhysMax() << endl;
		for(int i=...getPhysPos(); i<=...getPhysMax(); i+=1){
           ...setAngle(i);
           usleep(10000);
        }

        // ramp form max to min position:
		// ...

        // ramp form min to start position:
		// ...
    }
 #endif
   
   driver->sleep();
   return 0;
}
