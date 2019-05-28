/* Beispielprogramm 4.4 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Erzeuger-Verbraucher-System mit Message Queues */

#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define __PRIO__

#ifndef __PRIO__
main() {

 int msqid, verbr_id, i, status;

 struct bestellung {  /* Typ fuer Bestellungen */
  long mtype;
  char warenname[20];
  int kennziffer;
  float preis;
 };

 /* Vater: Erzeugt die Message Queue */
 msqid = msgget(IPC_PRIVATE,IPC_CREAT|0777);

 /* Erzeuger: Schickt in Sekundenabstaenden 5 Bestellungen ab */
 if (fork()==0) {
  struct bestellung meineBestellung;
  for (i=0;i<5;i++) {
   meineBestellung.mtype = 1;
   strcpy(meineBestellung.warenname,"USB-Stick");
   meineBestellung.kennziffer = 4711;
   meineBestellung.preis = 9.95;
   msgsnd(msqid,&meineBestellung,
            sizeof(meineBestellung)-sizeof(long),0);
   sleep(1); /* Verzoegerung bis zum naechsten Senden */
  }
  exit(0);
 }

 /* Verbraucher: Nimmt beliebig viele Bestellungen entgegen */
 if ((verbr_id=fork())==0) {
  struct bestellung deineBestellung;
  while(1) {
   msgrcv(msqid,&deineBestellung,
                      sizeof(deineBestellung)-sizeof(long),0,0);
   printf("Gelesen: %s %d %f\n",
                    deineBestellung.warenname,
                    deineBestellung.kennziffer,
                    deineBestellung.preis);
  }
 }

 /* Vater: Raeumt auf */
 wait(&status);             /* Warten auf Ende des Erzeugers */
 kill(verbr_id,SIGKILL);    /* Terminieren des Verbrauchers */
 msgctl(msqid,IPC_RMID,0);  /* Loeschen der Message Queue */

}

#else

main() {

 int msqid, verbr_id, i, status;

 struct bestellung {  /* Typ fuer Bestellungen */
  long mtype;
  char warenname[20];
  int kennziffer;
  float preis;
 };

 /* Vater: Erzeugt die Message Queue */
 msqid = msgget(IPC_PRIVATE,IPC_CREAT|0777);

 /* Erzeuger: Schickt in Sekundenabstaenden 5 Bestellungen ab */
 if (fork()==0) {
  struct bestellung meineBestellung;
  for (i=0;i<5;i++) {
   meineBestellung.mtype = 1;
   strcpy(meineBestellung.warenname,"USB-Stick");
   meineBestellung.kennziffer = 4711;
   meineBestellung.preis = 9.95;
   msgsnd(msqid,&meineBestellung,
            sizeof(meineBestellung)-sizeof(long),0);
   meineBestellung.mtype = 2;
   msgsnd(msqid,&meineBestellung,
            sizeof(meineBestellung)-sizeof(long),0);
   sleep(1); /* Verzoegerung bis zum naechsten Senden */
  }
  exit(0);
 }

 /* Verbraucher: Nimmt beliebig viele Bestellungen entgegen */
 if ((verbr_id=fork())==0) {
  struct bestellung deineBestellung;
  while(1) {
   if(msgrcv(msqid,&deineBestellung, sizeof(deineBestellung)-sizeof(long),2,IPC_NOWAIT) ==-1 )
      msgrcv(msqid,&deineBestellung, sizeof(deineBestellung)-sizeof(long),0,0);
   printf("Gelesen: %d %s %d %f\n", deineBestellung.mtype, deineBestellung.warenname,
      deineBestellung.kennziffer, deineBestellung.preis);
  }
 }

 /* Vater: Raeumt auf */
 wait(&status);             /* Warten auf Ende des Erzeugers */
 kill(verbr_id,SIGKILL);    /* Terminieren des Verbrauchers */
 msgctl(msqid,IPC_RMID,0);  /* Loeschen der Message Queue */

}


#endif
