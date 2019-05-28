/* Beispielprogramm 4.3 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Kommunikation ueber unbenannte Pipes */

#include <stdio.h>
#include <stdlib.h>

main() {

 char buffer[20];     /* Puffer zum Datenempfang */
 int fda[2], fdb[2];  /* Deskriptoren fuer Leseenden (fdx[0]) */
                      /* und Schreibenden (fdx[1]) der Pipes */
 pipe(fda); /* Erzeugung zweier unbenannter Pipes; Speichern der */
 pipe(fdb); /* Deskriptoren fuer Lese-/Schreibenden in fda und fdb */

 if (fork()==0) {
  /* Sohn: sendet Stringnachricht und empfaengt Rueckantwort */
  close(fda[0]);  /* nicht benoetigte Lese- und */
  close(fdb[1]);  /* Schreibdeskriptoren schlieﬂen */
  /* 6 Bytes in Pipe A schreiben (5 Zeichen + Ende-Zeichen \0) */
  write(fda[1],"HALLO",6);
  /* Rueckantwort aus Pipe B lesen und ausgeben */
  read(fdb[0],buffer,20);
  printf("\nSohn liest %s aus der Pipe B\n\n",buffer);
  exit(0);
 }

 /* Vater: empfaengt Stringnachricht und sendet Rueckantwort */
 close(fda[1]);  /* nicht benoetigte Lese- und */
 close(fdb[0]);  /* Schreibdeskriptoren schlieﬂen */
 /* String aus Pipe A lesen und ausgeben */
 read(fda[0],buffer,20);
 printf("\nVater liest %s aus der Pipe A\n\n",buffer);
 /* Rueckantwort in Pipe B schreiben */
 write(fdb[1],"HALLO ZURUECK",14);
}
