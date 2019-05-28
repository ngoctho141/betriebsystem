/* Beispielprogramm 3.3 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Erzeuger-Verbraucher-Problem: Verbraucher */

#include "prog_3_03.h"

main() {

 int i;                            /* Schleifenzähler */
 int semid;                        /* Nummer der Semaphorgruppe */
 unsigned short init_array[3];     /* Anfangswerte der Semaphore */
 struct sembuf sem_p[2], sem_v[2]; /* P- und V-Operationen */

 /* Erzeugung von drei Semaphoren mit dem Schlüssel 4711:
    Semaphor 0 (= S_BELEGT) zählt die Anzahl belegter Plätze,
                            soll bei leerem Puffer blockieren
    Semaphor 1 (= S_FREI)   zählt die Anzahl freier Plätze,
                            soll bei vollem Puffer blockieren
    Semaphor 2 (= S_WA)
            soll den Pufferzugriff wechselseitig ausschließen */
 semid = semget(4711,3,IPC_CREAT|0777);

 /* Initialisierung der Semaphore */
 init_array[S_BELEGT] = 0;
 init_array[S_FREI] = PUFFERKAP;
 init_array[S_WA] = 1;
 semctl(semid,0,SETALL,init_array);

 /* Vorbereitung zweier P-Operationen
    auf den Semaphoren S_BELEGT und S_WA */
 sem_p[0].sem_num = S_BELEGT;
 sem_p[1].sem_num = S_WA;
 sem_p[0].sem_op = sem_p[1].sem_op = -1;
 sem_p[0].sem_flg = sem_p[1].sem_flg = 0;

 /* Vorbereitung zweier V-Operationen
    auf den Semaphoren S_FREI und S_WA */
 sem_v[0].sem_num = S_FREI;
 sem_v[1].sem_num = S_WA;
 sem_v[0].sem_op = sem_v[1].sem_op = 1;
 sem_v[0].sem_flg = sem_v[1].sem_flg = 0;

 /* Verbrauchsvorgänge in der gewünschten Anzahl */

 for (i=0;i<ANZAHL_RUNDEN;i++) {

  /* Blockierung, wenn der Puffer leer
     oder durch den anderen Prozess gesperrt ist */
  semop(semid,sem_p,2);

  /* Daten aus Puffer lesen */
  sleep(1);
  printf("Verbraucher liest\n");

  /* Inkrementierung der Anzahl der freien Plätze
     und Freigabe des Puffers */
  semop(semid,sem_v,2);

  /* Daten verbrauchen */
  printf("Verbraucher verbraucht\n");
  sleep(5);

 }
 /* Löschung der Semaphore */
 semctl(semid,0,IPC_RMID,0);
}

