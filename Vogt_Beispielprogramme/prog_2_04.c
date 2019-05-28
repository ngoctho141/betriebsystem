/* Beispielprogramm 2.4 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Prozesserzeugung durch fork():
   Zugriff auf PID und PPID von Vater und Sohn */

#include <stdio.h>
#include <stdlib.h>

main() {

 int sohn_pid;

 if ((sohn_pid=fork())==0) {
  printf("Sohn: Eigene PID ist %d\n",getpid());
  printf("Sohn: Vater-PID ist %d\n",getppid());
  exit(0);
 }

 sleep(1);  /* Vaterausgabe soll nach der Sohnausgabe
               kommen */
 printf("Vater: Eigene PID ist %d\n",getpid());
 printf("Vater: Sohn-PID ist %d\n",sohn_pid);

}
