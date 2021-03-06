/* Beispielprogramm 2.5 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Warten auf die Terminierung eines Sohns durch wait() */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> /* for Makro WEXITSTATUS */

int main() {

 int status;

 if (fork()==0) {
  printf("Sohn: Ich schlafe jetzt\n");
  sleep(2);
  printf("Sohn: Ich bin jetzt fertig\n");
  exit(7);
 }

 printf("Vater: Ich warte auf den Sohn\n");
 wait(&status);
 printf("Vater: Sohn ist jetzt fertig\n");
 printf("Vater: status = %d\n",WEXITSTATUS(status));
 return 0;
}

