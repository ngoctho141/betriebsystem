/* Beispielprogramm 2.3 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Prozesserzeugung durch fork():
   Das Programm demonstriert, dass Vater und Sohn jeweils eigene Speicherbereiche haben. */

#include <stdio.h>
#include <stdlib.h>

main() {

 int i = 1;

  if (fork()==0) {
   printf("i im Sohn: %d\n",i);   /* Ausgabe: 1 */
   i = 2;
   printf("i im Sohn: %d\n",i);   /* Ausgabe: 2 */
   exit(0);
 }

 sleep(2); /* Vater blockiert für 2 Sekunden */
 printf("i im Vater: %d\n",i);    /* Ausgabe: 1 */

} 