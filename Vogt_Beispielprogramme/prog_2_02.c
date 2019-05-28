/* Beispielprogramm 2.2 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Prozesserzeugung durch fork() */

#include <stdio.h>
#include <stdlib.h>

main() {

 if (fork()==0) {
  /* Code des Sohns (im if-Block) */
  printf("Hier ist der Sohn\n");
  exit(0); /* Wichtig: Terminierung des Sohns! */
 }

 /* Code des Vaters (im Programmteil nach if) */
 printf("Hier ist der Vater\n");
 /* Hier darf exit() fehlen */
}
