/* Beispielprogramm 4.1 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Kommunikation ueber Shared Memory */

#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define PUFFERKAP 3      /* Kapazität des Puffers */
#define ANZAHL_RUNDEN 10 /* Anzahl der Erzeugungs- bzw. Verbrauchsvorgänge */

main() {

 int shmid;      /* Nummer des Shared-Memory-Segments */
 float *shmptr;  /* Pointer auf das Segment */
 int ix;         /* Lese- bzw. Schreibindex im Segment */
 float zwisch;   /* Zwischenspeicher */
 int i;          /* Schleifenzähler */
 int status;     /* Rückgabeparameter für wait() */

 int semid;                        /* Nummer der Semaphorgruppe zur Synchronisation */
 struct sembuf sem_p[2], sem_v[2]; /* P- und V-Operationen */
 unsigned short init_array[3];     /* Anfangswerte der Semaphore */

 /* Erzeugung des Shared-Memory-Segments */
 shmid = shmget(IPC_PRIVATE,PUFFERKAP*sizeof(float),IPC_CREAT|0777);

 /* Erzeugung und Vorbereitung der Semaphore */
 semid = semget(IPC_PRIVATE,3,IPC_CREAT|0777);
 init_array[0] = 0;   /* S_BELEGT==0: zählt # belegten Plätze, blockiert bei leerem Puffer  */
 init_array[1] = PUFFERKAP; /* S_FREI==1: zählt # freien Plätze, blockiert bei vollem Puffer */
 init_array[2] = 1;    /* S_WA==2: soll Pufferzugriff wechselseitig ausschließen */
 semctl(semid,0,SETALL,init_array);
 sem_p[0].sem_op = sem_p[1].sem_op = -1;
 sem_p[0].sem_flg = sem_p[1].sem_flg = 0;
 sem_v[0].sem_op = sem_v[1].sem_op = 1;
 sem_v[0].sem_flg = sem_v[1].sem_flg = 0;

 /* Verbraucher-Prozess */
 if (fork()==0) {
  ix = 0;  /* Leseindex auf Segmentanfang setzen */
  shmptr = (float *) shmat(shmid,0,0); /* Pointer auf Segment */
  for (i=0;i<ANZAHL_RUNDEN;i++) {
   /* Blockierung, solange Puffer leer ist oder durch anderen Prozess
      benutzt wird */
   sem_p[0].sem_num = 0; sem_p[1].sem_num = 2;
   semop(semid,sem_p,2);

   zwisch = *(shmptr+ix); /* Lesen aus der ix-ten Segmentpos.  */
   ix = (ix+1)%PUFFERKAP; /* Weiterschalten des Index */
   printf("Index: %d\n",ix);
   printf("Gelesen: %f\n",zwisch);

   sem_v[0].sem_num = 1; sem_v[1].sem_num = 2;
   semop(semid,sem_v,2);
  }
  exit(0);
 }

 /* Erzeuger-Prozess */
 if (fork()==0) {
  ix = 0;  /* Schreibindex auf Segmentanfang setzen */
  shmptr = (float *) shmat(shmid,0,0); /* Pointer auf Segment */
  for (i=0;i<ANZAHL_RUNDEN;i++) {
   zwisch = 0.5*i;  /* zu schreibender Wert (im Prinzip beliebig) */
   /* Blockierung, solange Puffer voll ist oder durch anderen Prozess
      benutzt wird */
   sem_p[0].sem_num = 1; sem_p[1].sem_num = 2;
   semop(semid,sem_p,2);

   *(shmptr+ix) = zwisch; /* Schreiben an die ix-te Segmentpos. */
   ix = (ix+1)%PUFFERKAP; /* Zyklisches Weiterschalten des Index */

   sem_v[0].sem_num = 0; sem_v[1].sem_num = 2;
   semop(semid,sem_v,2);
  }
  exit(0);
 }

 /* Warten auf das Ende von Erzeuger und Verbraucher */
 wait(&status);
 wait(&status);

 /* Löschung des Shared-Memory-Segments und der Semaphorgruppe */
 shmctl(shmid,IPC_RMID,0);
 semctl(semid,IPC_RMID,0);

}
