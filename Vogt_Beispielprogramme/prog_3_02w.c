/* Synchronisation durch Semaphore: wechselseitiger Auschluss */

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
 init_array[0] = 1;
 semctl(semid,0,SETALL,init_array);

 /* Vater: Vorbereitung der P- und V-Operationen */
 sem_p.sem_num = 0;  sem_v.sem_num = 0;
 sem_p.sem_op  = -1; sem_v.sem_op  = 1;
 sem_p.sem_flg = 0;   sem_v.sem_flg = 0;

 /* Sohn 1 */
 if (fork()==0) {
  printf("Sohn 1 wird ausgefuehrt\n");
  sleep(3);
  semop(semid,&sem_p,1); /* Blockierung */
  printf("Sohn 1 tritt ein\n");
  sleep(2);
  printf("Sohn 1 verlaesst\n");
  semop(semid,&sem_v,1); /* Entblockierung */
  exit(0);
 }

 /* Sohn 2 */
 if (fork()==0) {
  printf("Sohn 2 wird ausgefuehrt\n");
  sleep(2);
  semop(semid,&sem_p,1); /* Blockierung */
  printf("Sohn 2 tritt ein\n");
  sleep(2);
  printf("Sohn 2 verlaesst\n");
  semop(semid,&sem_v,1); /* Entblockierung */
  exit(0);
 }


 /* Vater: Warten auf die Terminierung der Söhne */
 wait(&status);
 wait(&status);
 /* Vater: Loeschen der Semaphorgruppe */
 semctl(semid,0,IPC_RMID,0);

}
