/* Beispielprogramm 2.9 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Warten auf die Terminierung eines Pthreads durch pthread_join().
   (Unter Linux zu uebersetzen durch cc -pthread prog_2_09.c) */

#include <pthread.h>
#include <stdio.h>

/* Funktion, die der Thread ausfuehren soll */
void *schlafe(void *schlafzeit) {
 int sz = *(int*)schlafzeit;
 static int exitcode = 0;
 printf("Thread schlaeft %d Sekunden\n",sz);
 sleep(sz);  /* Thread blockiert sich eine Zeit lang */
 printf("Thread ist fertig\n");
 pthread_exit(&exitcode);  /* Thread beendet sich */
}

/* Hauptprogramm */
int main(int argc, char *argv[]) {
 int schlafzeit = 2;  /* Schlafzeit des Threads */
 pthread_t thread_id; /* ID des Threads */
 void *status;         /* Rueckkehrstatus des Threads */
 printf("Main erzeugt Thread\n");
 pthread_create(&thread_id, NULL, schlafe, &schlafzeit); 
 printf("Main wartet auf Thread in pthread_join()\n");
 pthread_join(thread_id, &status);
 printf("Main: Thread beendet mit Status %d\n",*(int*)status);
}
