/* Beispielprogramm 2.8 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Erzeugen und Ausfuehren von Pthreads.
   (Unter Linux zu uebersetzen durch cc -pthread prog_2_08.c) */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* globale Variable, die für alle Threads zugreifbar ist */
int wertspeicher = 0;

/* Funktion, die von einem Thread ausgeführt werden soll */
void *ausgabe(void *p) {
 printf("Hier ist ein Thread\n");
 printf("Mein Funktionsparameter: %ld\n", *(long *)p);
 printf("Meine PID: %d\n",getpid());
 wertspeicher++;  /* erhöht die gemeinsame globale Variable */
 printf("Wertspeicher: %d\n\n",wertspeicher);
 pthread_exit(NULL);  /* beendet den Thread */
}

/* Hauptprogramm */
int main(int argc, char *argv[]) {

 pthread_t th1, th2;   /* IDs der neu erzeugten Threads  */
 long param1, param2;  /* Parameter zur Übergabe an die Threads */
 int err;              /* Fehlercode von pthread_create() */
 void *status;         /* Rückgabeparameter von pthread_join */

 printf("PID des Hauptprogramms: %d\n",getpid());
 printf("Wertspeicher: %d\n\n",wertspeicher);

 /* Erzeugung eines Threads */
 printf("Erzeuge den ersten Thread\n");
 param1 = 1111;
 err = pthread_create(&th1, NULL, ausgabe, &param1);
    /* 1. Parameter: Rückgabewert = ID des neuen Threads
       2. Parameter: Attribute (hier: Standardattribute)
       3. Parameter: Funktion, die der Thread ausführen soll
       4. Parameter: Parameter für die Funktion  */
 if (err!=0) {
  printf("Fehler bei der Erzeugung des ersten Threads\n");
  exit(-1);
 }
 printf("Thread-ID %lu\n\n",th1);

 /* Erzeugung eines zweiten Threads */
 printf("Erzeuge den zweiten Thread\n");
 param2 = 2222;
 err = pthread_create(&th2, NULL, ausgabe, &param2);
 if (err!=0) {
  printf("Fehler bei der Erzeugung des zweiten Threads\n");
  exit(-1);
 }
 printf("Thread-ID %lu\n\n",th2);

 pthread_join(th1,&status);
 pthread_join(th2,&status);

 printf("Programm beendet\n");

}
