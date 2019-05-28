
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
#define _delay_ 20000

// calibration data --> to fit to vehicle
#define STEER_MIN   -5
#define STEER_START 20
#define STEER_MAX   45
#define PAN_MIN    -70
#define PAN_START   10
#define PAN_MAX    100
#define TILT_MIN     5
#define TILT_START  30
#define TILT_MAX    60


float calc_dc(float ms,float frequency)
{
   return ms*frequency/10;
}

int main(int argc, char** argv) 
{
    // init GPIOs
    wiringPiSetupGpio();               // use GPIO not WPi labels
    pinMode(GPIO_LA, OUTPUT);          // output pin
    pinMode(GPIO_LB, OUTPUT);          
    pinMode(GPIO_RA, OUTPUT);          
    pinMode(GPIO_RB, OUTPUT);          

    // init Servos
    PWMDriver* driver = new PWMDriver(1,0x40);
    driver->reset();
    float frequency = 60.0f;
    float servo_range = 90.0;
    driver->setFrequency(frequency); 
    
    // check calibration data
    if( !(STEER_MIN<STEER_START && STEER_START < STEER_MAX &&  
          PAN_MIN<PAN_START && PAN_START < PAN_MAX &&  
          TILT_MIN<TILT_START && TILT_START < TILT_MAX))    {
        printf("Error: Incorrect calibration data\n");
        return -1;
    }
        
    Servo servo_s(driver, 0, servo_range); // steering on channel 0
    servo_s.calibrate(calc_dc(0.6,frequency), calc_dc(2.34,frequency)); 
    servo_s.setMountingRange(STEER_MIN,STEER_MAX,STEER_START); 

    Servo servo_p(driver, 14, servo_range); // camera pan on channel 14
    servo_p.calibrate(calc_dc(0.6,frequency), calc_dc(2.34,frequency)); 
    servo_p.setMountingRange(PAN_MIN,PAN_MAX,PAN_START); 

    Servo servo_t(driver, 15, servo_range); // camera tilt on channel 15
    servo_t.calibrate(calc_dc(0.6,frequency), calc_dc(2.34,frequency)); 
    servo_t.setMountingRange(TILT_MIN,TILT_MAX,TILT_START); 

    // init DC motors
    DC_Motor motor_l(driver,5,GPIO_LA,GPIO_LB,false);
    DC_Motor motor_r(driver,4,GPIO_RA,GPIO_RB,true);
    
  
#define __test_motors__   
#ifdef __test_motors__   
    uint8_t speed = 50;   
    for (int i = 0; i < 2; i++)
    {
        DC_Motor* pm = NULL;
        if(i == 0) pm = &motor_l;
        else if(i == 1) pm = &motor_r;

        printf("%d: set speed +\n",i);
        pm->setSpeed(speed);
        getchar();
        printf("%d: set speed 0\n",i);
        pm->setSpeed(0);
        getchar();
        printf("%d: set speed -\n",i);
        pm->setSpeed(-speed);
        getchar();
        printf("%d: set speed 0\n",i);
        pm->setSpeed(0);
        getchar();
    }
#endif
	   
#define __test_servos__
#ifdef __test_servos__
    for (int i = 0; i < 3; i++)
    {
        Servo* ps = NULL;
        if(i == 0) ps = &servo_s;
        else if(i == 1) ps = &servo_p;
        else if(i == 2) ps = &servo_t;

        cout << i << ": from " << ps->getPhysPos() << " to " << 
           ps->getPhysMax() << endl;
        for(int i=ps->getPhysPos(); i<=ps->getPhysMax(); i+=1){
           ps->setAngle(i);
           usleep(_delay_);
        }

        // getchar();
        cout << i << ": from " << ps->getPhysPos() << " to " << 
           ps->getPhysMin() << endl;
        for(int i=ps->getPhysPos(); i>=ps->getPhysMin(); i-=1){
           ps->setAngle(i);
           usleep(_delay_);
        }
        // getchar();

        cout << i << ": from " << ps->getPhysPos() << " to " << 
           ps->getPhysStart() << endl;
        for(int i=ps->getPhysPos(); i<=ps->getPhysStart(); i+=1){
           ps->setAngle(i);
           usleep(_delay_);
        }
        // char input = getchar();
        // if(input == 's') break;
    }
 #endif
   
   driver->sleep();
   
  /* struct VC_IFC {
 float speed_l;
 float speed_r;
 float steeringAngle;
 float panAngle;
 float tiltAngle;
 int cmd;
};
   
   if(fork()==0)
   {
   VC_IFC.speed_l = 0.0f;
   VC_IFC.speed_r = 0.0f;
   VC_IFC.steeringAngle = 0.0f;
   VC_IFC.panAngle = 0.0f;
   VC_IFC.tiltAngle= 0.0f;
   VC_IFC.cmd = 1;
   
   
   while(cmd==1)
   {
   pm = &moter_r;
   pm->setSpeed(VC_IFC.speed_r);
   pm = &moter_l;
   pm->setSpeed(VC_IFC.speed_l);
   ps = &servo_s;
   ps->setAngle(VC_IFC.steeringAngle)
   
   }
   }
   else{
   printf("blaaaaaa");
   } */
   
   
   return 0;
}
