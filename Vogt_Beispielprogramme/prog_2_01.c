/* Beispielprogramm 2.1 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Drei Funktionen der UNIX/Linux-Programmierschnittstelle */

#include <fcntl.h>  /* Konstantendef. für Dateizugriffe */
#include <stdio.h>  /* Funktionen der Standard-E/A */
#include <string.h> /* Funktionen zur String-Verarbeitung */
#include <stdlib.h> /* Funktion exit() */
#include <errno.h>  /* Funktionen/Variablen zur Fehlerbehandlung */

int main() {

 int fd;   /* Dateideskriptor */
 int err;  /* Zwischenspeicher fuer Fehlermeldung */

 /* Eine Datei namens "myFile" neu erzeugen (O_CREAT)
    und zum Schreiben (O_WRONLY) öffnen.
    Die Rückgabe ist ein int-Wert, der die Datei eindeutig
    identifiziert */

 fd = open("myFile",O_CREAT|O_WRONLY,0600);

 /* Fehlerpruefung */

 if (fd==-1) {
  printf("Fehler Nr. %d\n",errno); /* Fehlernummer ausgeben */
  perror("");                      /* Fehlermeldung ausgeben */
  exit(-1);                        /* Programm beenden */
 }

 /* Den Text "HALLO" in die Datei schreiben */

 err = write(fd,"HALLO",strlen("HALLO"));
 /* Fehlerpruefung */

 if (err==-1) {
  printf("Fehler Nr. %d\n",errno); /* Fehlernummer ausgeben */
  perror("");                      /* Fehlermeldung ausgeben */
  exit(-1);                        /* Programm beenden */
 }

 /* Die Datei wieder schließen */

 err = close(fd);

 /* Fehlerpruefung */

 if (err==-1) {
  printf("Fehler Nr. %d\n",errno); /* Fehlernummer ausgeben */
  perror("");                      /* Fehlermeldung ausgeben */
  exit(-1);                        /* Programm beenden */
 }

}
