/* Beispielprogramm 3.3 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Erzeuger-Verbraucher-Problem: Erzeuger */

#include "prog_3_03.h"

main() {

 int i;                            /* Schleifenzähler */
 int semid;                        /* Nummer der Semaphorgruppe */
 struct sembuf sem_p[2], sem_v[2]; /* P- und V-Operationen */

 /* Zugriff auf die drei Semaphore mit dem Schlüssel 4711,
    die vom Verbraucher generiert wurden (siehe Kommentar dort) */
 semid = semget(4711,3,0777);
 if (semid==-1) {
  printf("Fehler: Semaphorgruppe existiert nicht!");
  exit(-1); }

 /* Vorbereitung zweier P-Operationen
    auf den Semaphoren S_FREI und S_WA */
 sem_p[0].sem_num = S_FREI;
 sem_p[1].sem_num = S_WA;
 sem_p[0].sem_op = sem_p[1].sem_op = -1; 
 sem_p[0].sem_flg = sem_p[1].sem_flg = 0;

 /* Vorbereitung zweier V-Operationen
    auf den Semaphoren S_BELEGT und S_WA */
 sem_v[0].sem_num = S_BELEGT;
 sem_v[1].sem_num = S_WA;
 sem_v[0].sem_op = sem_v[1].sem_op = 1; 
 sem_v[0].sem_flg = sem_v[1].sem_flg = 0;

 /* Erzeugungsvorgänge in der gewünschten Anzahl */

 for (i=0;i<ANZAHL_RUNDEN;i++) {

  /* Daten erzeugen */
  printf("Erzeuger erzeugt\n");
  sleep(1);

  /* Blockierung, wenn der Puffer voll
     oder durch den anderen Prozess gesperrt ist */
  semop(semid,sem_p,2);

  /* Daten schreiben */
  printf("Erzeuger schreibt\n");
  sleep(1);

  /* Inkrementierung der Anzahl der belegten Plätze
     und Freigabe des Puffers */
  semop(semid,sem_v,2);

 }

}