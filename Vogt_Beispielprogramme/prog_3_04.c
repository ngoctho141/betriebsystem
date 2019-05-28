/* Beispielprogramm 3.4 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Erzeuger-Verbraucher-Problem mit Pthreads, Mutex und Bedingungsvariablen */

#include <pthread.h>
#include <stdio.h>

#define PUFFERKAP 3       /* Kapazitaet des Ringpuffers */
#define ERZZEIT 1         /* Dauer des Erzeugens (Sek.) */
#define VBRZEIT 3         /* Dauer des Verbrauchens (Sek.) */
#define GESAMTLAUFZEIT 30 /* Gesamtlaufzeit des Programms (Sek.) */

pthread_mutex_t mutex;               /* Mutex fuer den wechselseitigen
                                        Ausschlussder Pufferzugriffe */
pthread_cond_t cond_voll, cond_leer; /* Bedingungsvariablen zur Blockade
                                        bei vollem bzw. leerem Puffer */
int puffer[PUFFERKAP+1],
    lese_index=0, schreib_index=0;   /* Puffer mit Lese- u. Schreibindex */
int hilf;                            /* Hilfsvariable zur Speicherung des
                                        gelesenen Werts */

/* Funktion zur zyklischen Erhoehung eines Indexwerts */

void incr_index(int *index) {
 *index = (*index+1)%(PUFFERKAP+1);
    /* Die Modulooperation % setzt den Index auf 0 zurück,
       wenn er das Pufferende überschritten hat. */
}

/* Funktionen zur Pruefung der Wartebedingungen */

int puffer_voll() {
 return ((schreib_index+1)%(PUFFERKAP+1))==lese_index; }

int puffer_leer() {
 return schreib_index==lese_index; }

/* Funktion, die der Erzeuger-Thread ausführt:
   Der Erzeuger schreibt die Folge 10, 20, ... in den Puffer. */

void *erzeuger_loop(void *p) {
 int wert = 10;
 while (1) {
  wert += 10; /* Erzeugung des naechsten zu schreibenden Werts */
  sleep(ERZZEIT);  /* Verzoegerung um die gewuenschte Zeit */
  pthread_mutex_lock(&mutex); /* Belegung des Puffers */
  while (puffer_voll())          /* Prüfung Wartebedingung ... */
   pthread_cond_wait(&cond_voll,&mutex); /* ... und ggf. Blockade */
  puffer[schreib_index] = wert;    /* Schreiben des Werts */
  incr_index(&schreib_index);      /* Erhoehung Schreibindex */
  printf("geschrieben: %d\n",wert);   /* Ausgabe des geschriebenen Werts */
  pthread_cond_signal(&cond_leer); /* Signalisierung des Verbrauchers */
  pthread_mutex_unlock(&mutex);    /* Freigabe des Puffers */
 }
}

/* Funktion, die der Verbraucher-Thread ausfuehrt:
   Der Verbraucher liest Werte aus dem Puffer und gibt sie aus. */

void *verbraucher_loop(void *p) {
 while (1) {
  pthread_mutex_lock(&mutex); /* Belegung des Puffers */
  while (puffer_leer())          /* Pruefung Wartebedingung ... */
   pthread_cond_wait(&cond_leer,&mutex); /* ... und ggf. Blockade */
  hilf = puffer[lese_index];       /* Lesen des Werts */
  incr_index(&lese_index);         /* Erhoehung des Leseindex */
  pthread_cond_signal(&cond_voll); /* Signalisierung Erzeuger */
  pthread_mutex_unlock(&mutex);    /* Freigabe des Puffers */
  printf("                  gelesen: %d\n",hilf);  /* Ausgabe des gelesenen Werts */
  sleep(VBRZEIT);  /* Verzoegerung um die gewuenschte Zeit */
 }
}

/* Hauptprogramm zum Starten und Beenden des Ablaufs */

int main(int argc, char *argv[]) {

 pthread_t erzeuger, verbraucher; /* Erzeuger- und Verbraucher-Thread */
 pthread_mutex_t mutex;           /* Mutex fuer wechselseitigen Ausschluss */
 pthread_mutex_init(&mutex, NULL);     /* Initialisierung des Mutex */
 pthread_cond_init(&cond_voll, NULL);  /* und der Bedingungs- */
 pthread_cond_init(&cond_leer, NULL);  /* variablen */

 /* Start der Threads */
 pthread_create(&erzeuger, NULL, erzeuger_loop, NULL); /* link option: -pthread */
 pthread_create(&verbraucher, NULL, verbraucher_loop, NULL);

 /* Warten für die gewuenschte Laufzeit */
 sleep(GESAMTLAUFZEIT);

 /* Stoppen der Threads, Loeschen von Mutex und Bedingungsvariablen */
 printf("main loop: stop threads ...");
 pthread_cancel(erzeuger);
 pthread_cancel(verbraucher);
 printf("... threads stopped");
 pthread_mutex_destroy(&mutex);
 pthread_cond_destroy(&cond_voll);
 pthread_cond_destroy(&cond_leer);
}
