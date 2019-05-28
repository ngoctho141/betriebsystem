/* Beispielprogramm 2.7 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Terminieren eines anderen Prozesses durch kill() */

#include <signal.h>
#include <stdio.h>

main() {

    int sohn_pid, i=0;

    if ((sohn_pid=fork())==0) {
        /* Endlosschleife des Sohns */
        while (1) {
            printf(" Sohn iteration %d ",i++);
        }
     }

    sleep(2);
    /* Der Vater beendet den Sohn */
    kill(sohn_pid,SIGKILL);
    /* ohne dieses Signal läuft Sohn unendlich */
}
