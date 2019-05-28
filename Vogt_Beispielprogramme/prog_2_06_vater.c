/* Beispielprogramm 2.6 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Programm des Vaters:
   Erzeugt einen Sohn und laesst ihn dann durch excev() ein Programm in einer anderen Datei ausfuehren. */

/* mit Korrekturen gegenüber dem Programmtext im Buch */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

 int err, status;
 char *parameter[3];

 parameter[0] = new char[10];
 parameter[1] = new char[10];
 parameter[2] = new char[10];

 strcpy(parameter[0],"programm");
 strcpy(parameter[1],"1. Parameter");
 strcpy(parameter[2],"2. Parameter");

 if (fork()==0) {
  /* Aufruf einer Maschinenprogramm-Datei */
  err = execv("sohn",parameter);
  printf("Fehler: Rueckkehr aus execv(), Rueckgabe = %d\n",err);
  exit(err);                /* Rückkehr nur im Fehlerfall! */
 }

 wait(&status);
 printf("Fehlererkennung im Vater: Sohn beendet, status = %d\n",status);
}
