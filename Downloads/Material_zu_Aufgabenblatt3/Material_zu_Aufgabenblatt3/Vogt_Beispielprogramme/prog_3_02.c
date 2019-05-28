/* Beispielprogramm 3.2 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Synchronisation durch Semaphore: Reihenfolgebedingung */

#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

main() {

 int semid;                    /* Nummer der Semaphorgruppe */
 unsigned short init_array[1]; /* Anfangswert des Semaphors */
 struct sembuf sem_p, sem_v;   /* P- und V-Operationen */
 int status;                   /* Rueckgabevariable für wait() */

 /* Vater: Erzeugung und Initialisierung eines Semaphors */
 semid = semget(IPC_PRIVATE,1,IPC_CREAT|0777);
 init_array[0] = 0;
 semctl(semid,0,SETALL,init_array);

 /* Vater: Vorbereitung der P- und V-Operationen */
 sem_p.sem_num = 0;  sem_v.sem_num = 0;
 sem_p.sem_op  = -1; sem_v.sem_op  = 1;
 sem_p.sem_flg = 0;   sem_v.sem_flg = 0;
 
 /* Sohn 1: Vorgänger */
 if (fork()==0) {
  printf("Vorgaenger wird ausgefuehrt\n");
  sleep(2);
  printf("Vorgaenger endet\n");
  semop(semid,&sem_v,1); /* Entblockierung des Nachfolgers */
  exit(0);
 }

 /* Sohn 2: Nachfolger */
 if (fork()==0) {
  printf("Nachfolger wartet\n");
  semop(semid,&sem_p,1); /* Warten auf den Vorgänger */
  printf("Nachfolger wird ausgefuehrt\n");
  exit(0);
 }

 /* Vater: Warten auf die Terminierung der Söhne */
 wait(&status);
 wait(&status);
 /* Vater: Loeschen der Semaphorgruppe */
 semctl(semid,0,IPC_RMID,0);

}