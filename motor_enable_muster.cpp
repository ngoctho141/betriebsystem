// Do not optimize this code using -O3 as it will remove the delay hack
#include <unistd.h>
#include <wiringPi.h>
#include <iostream>
using namespace std;
#define LED_GPIO_LA  17                   // this is GPIO17, pin 11
#define LED_GPIO_LB  18                   // this is GPIO18, pin 12
#define LED_GPIO_RA  27                   // this is GPIO27, pin 13
#define LED_GPIO_RB  22                   // this is GPIO22, pin 15

#define _delay_ 100000

int motor_left(int speed)
{
	if(speed>100 || speed<-100) return -1;
	if(speed==0)
	{
        digitalWrite(LED_GPIO_LA,HIGH);
		digitalWrite(LED_GPIO_LB,HIGH);
        

	}
	else if(speed>0)
	{
		digitalWrite(LED_GPIO_LA,HIGH);
		digitalWrite(LED_GPIO_LB,LOW);
        
	} 
	else if(speed<0)
	{
        digitalWrite(LED_GPIO_LA,LOW);
		digitalWrite(LED_GPIO_LB,HIGH);
        
	} 
	return 0;
}

int motor_right(int speed)
{
	if(speed>100 || speed<-100) return -1;
	if(speed==0)
	{
       
        digitalWrite(LED_GPIO_RA,HIGH);
		digitalWrite(LED_GPIO_RB,HIGH);	

	}
	else if(speed>0)
	{
		
        digitalWrite(LED_GPIO_RA,HIGH);
		digitalWrite(LED_GPIO_RB,LOW);
	} 
	else if(speed<0)
	{
      
        digitalWrite(LED_GPIO_RA,LOW);
		digitalWrite(LED_GPIO_RB,HIGH);
	} 
	return 0;
}

		
int main() {
   wiringPiSetupGpio();                // use GPIO not WPi labels
   cout << "Starting toggle of DC motor enable signals" << endl;
   cout << "Press CTRL+C to quit..." << endl;
   pinMode(LED_GPIO_LA, OUTPUT);          // output pin
   pinMode(LED_GPIO_LB, OUTPUT);          
   pinMode(LED_GPIO_RA, OUTPUT);          
   pinMode(LED_GPIO_RB, OUTPUT);          

   while(1) {                          // loop forever fore sequence { 0 --> 50 --> -50 --> 0 for both motors }
      usleep(_delay_);				
      motor_left(0);
      motor_right(0);

      usleep(_delay_);
      motor_left(50);
      motor_right(50);
      usleep(_delay_);
      motor_left(0);
      motor_right(0);
      usleep(_delay_);
      motor_left(-50);
      motor_right(-50);
      
	  // ...
   }
   return 0;                           // program will not reach here
}

