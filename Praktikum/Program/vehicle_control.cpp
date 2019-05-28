
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
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>

//#include "prog_3_03.h"

using namespace std;
using namespace exploringRPi;

#define GPIO_LA  17                   // this is GPIO17, pin 11
#define GPIO_LB  18                   // this is GPIO18, pin 12
#define GPIO_RA  27                   // this is GPIO27, pin 13
#define GPIO_RB  22                   // this is GPIO22, pin 15
#define GPIO_23  23                   // this is GPIO23, pin 16

#define _delay_ 20000

// calibration data --> to fit to vehicle
#define STEER_MIN   -20
#define STEER_START 5
#define STEER_MAX   25
#define PAN_MIN    -70
#define PAN_START   10
#define PAN_MAX    100
#define TILT_MIN     5
#define TILT_START  30
#define TILT_MAX    60
#define KEY_SM 4790 //key fuer shared memory prozess
//#define IPC_CREAT 5555

typedef struct VC_IFC {
float speed_l;
 float speed_r;
 float steeringAngle;
 float panAngle;
 float tiltAngle;
 int cmd;
 
} VC_IFC;

float calc_dc(float ms,float frequency)
{
   return ms*frequency/10;
}

int main(int argc, char** argv) 

{

// int i;                            /* Schleifenzähler */
 int semid;                        /* Nummer der Semaphorgruppe */
 struct sembuf sem_p, sem_v; /* P- und V-Operationen */
 
 
  /* Zugriff auf die drei Semaphore mit dem Schlüssel 4711,
    die vom Verbraucher generiert wurden (siehe Kommentar dort) */
 semid = semget(4711,1,IPC_CREAT|0777);
 if (semid==-1) {
  printf("Fehler: Semaphorgruppe existiert nicht!");
  exit(-1); }
semctl(semid, 0, SETVAL, 1);
 /* Vorbereitung zweier P-Operationen
    auf den Semaphoren S_FREI und S_WA */
 sem_p.sem_num = 0;
 sem_p.sem_op =  -1; 
 sem_p.sem_flg =  0;

 /* Vorbereitung zweier V-Operationen
    auf den Semaphoren S_BELEGT und S_WA */
 sem_v.sem_num = 0;
 sem_v.sem_op =  1; 
 sem_v.sem_flg =  0;
 

int shmid;
VC_IFC * shmptr ;
int ix;
VC_IFC zwisch;
int i;
int status;



//create shared memory
shmid = shmget(IPC_PRIVATE, sizeof(VC_IFC), IPC_CREAT|0777);

    // init GPIOs
    wiringPiSetupGpio();               // use GPIO not WPi labels
    pinMode(GPIO_LA, OUTPUT);          // output pin
    pinMode(GPIO_LB, OUTPUT);          
    pinMode(GPIO_RA, OUTPUT);          
    pinMode(GPIO_RB, OUTPUT); 
    pinMode(GPIO_23, OUTPUT);          

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
    DC_Motor motor_r(driver,4,GPIO_RA,GPIO_RB,false);
    
    
    
    
  
/*#define __test_motors__   
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
        if(i == 0) ps = &servo_s
;
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
   */
   
   

   

    sem_p.sem_num = 0; 
    sem_v.sem_num = 0;
     sem_p.sem_op = -1; 
     sem_v.sem_op = 1; 
     sem_p.sem_flg = 0;
      sem_v.sem_flg = 0;
   

if(fork()==0)
   {


 
   ix = 0;
   
   
   shmptr = (VC_IFC *) shmat(shmid,0,0) ;
   
   semop(semid, &sem_p, 1);
   
   shmptr->speed_l = 0.0f;
   shmptr->speed_r = 0.0f;
   shmptr->steeringAngle = 0.0f;
   shmptr->panAngle = 0.0f;
   shmptr->tiltAngle= 0.0f;
   //shmptr->cycle = 1;
   shmptr->cmd = 1;
   
   
   semop(semid, &sem_v, 1);
   int t = 1 ;
   
   
   //if(fork()==0)
   //{
   
   
   while(shmptr->cmd==1)
   {
   
   
   
   
   semop(semid, &sem_p, 1); //eintreten
   motor_l.setSpeed(shmptr->speed_l);
   motor_r.setSpeed(shmptr->speed_r);
   servo_s.setAngle(shmptr->steeringAngle);
   servo_t.setAngle(shmptr->tiltAngle);
   servo_p.setAngle(shmptr->panAngle);
   
   semop(semid, &sem_v, 1); //Entblockierung des Vorgängers
   
   digitalWrite(GPIO_23,t);
   t = (t + 1) % 2;
   //printf("dere");
    sleep(0.5);
    
    
    
    
    
   }
   exit(0);
   
   }
   else{
   printf("blaaaaaa");
   }
   
   
   if(fork()==0)
   {
   
  
   
   ix = 0;
  shmptr = (VC_IFC *) shmat(shmid,0,0) ;
    for(int a = 0; a < 100; a++)
    {
    sleep(1);
    
     semop(semid,&sem_p,1); 
     
    shmptr->speed_l = 0;
   // printf("%d", a );
   shmptr->speed_r = 0;
   //shmptr->steeringAngle = a;
   //shmptr->panAngle = a;
   //shmptr->tiltAngle= a;
    
    semop(semid, &sem_v, 1); //Entblockierung des Vorgängers
    
    }
    //shmptr->cmd = 0;
    
    exit(0);
    
   }
   
   wait(&status);
   wait(&status);
   
   shmctl(shmid,IPC_RMID,0);
   driver->sleep();
   return 0;
}
