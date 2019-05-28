/* Beispielprogramm 2.6 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Programm des Sohns:
   Wird aus dem Programm in prog_2_06_vater.c aufgerufen.

   Dazu muss das Maschinenprogramm, das durch Uebersetzung dieses Programms entsteht,
   in der Datei 'sohn' stehen
   - Uebersetzung also durch 'cc -o sohn prog_2_06_sohn.c' */

#include <stdio.h>
#include <stdlib.h>

main(int argc, char *argv[]) {

 int i;
 printf("Sohnprogramm:\n");
 for (i=0;i<argc;i++)  /* Ausgabe der erhaltenen Parameter */
  printf(" Parameter %d: %s\n",i,argv[i]);
 exit(0);

}
