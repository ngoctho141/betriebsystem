/* Beispielprogramm 3.1 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Synchronisation durch Signale: kill() und pause() */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Signal Handler */

void sighand() {
 printf("Signal ist eingetroffen\n");
}

/* Hauptprogramm */

main() {
 int sohn_pid;
 /* Bindung des Signal Handlers sighand() an
    das Signal SIGUSR1, Details siehe [Linux] */
 struct sigaction sigact;
 sigact.sa_handler = sighand;
 sigemptyset(&sigact.sa_mask);
 sigact.sa_flags = 0;
 sigaction(SIGUSR1,&sigact,0);

 if ((sohn_pid=fork())==0) {
  printf("Sohn wartet auf Signal\n");
  pause();
  printf("Sohn terminiert\n");
  exit(0);
 }

 printf("Vater tut zunächst etwas anderes\n");
 sleep(2);
 printf("Vater schickt Signal an Sohn\n\n");
 kill(sohn_pid,SIGUSR1);
}
