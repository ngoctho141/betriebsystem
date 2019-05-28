/* Beispielprogramm 4.2 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Kommunikation ueber benannte Pipes: Sender */

#include <stdio.h>
#include <fcntl.h>

main() {

 int fd;  /* Deskriptor fuer die Pipe */
 const char* pipe_file = "../../../PIPE_2"; /* Pipe mit Pfad */

 printf("Erzeuge Pipe\n");
 mkfifo(pipe_file,0666);  /* Erzeugung der benannten Pipe mit Lese-
                             und Schreibrechte*/

 printf("Oeffne Pipe zum Schreiben\n");
 fd=open(pipe_file,O_WRONLY);  /* Oeffnen der Pipe zum Schreiben */

 printf("Schreibe 'HALLO'\n");
 write(fd,"HAL",3); /* Schreiben zweier Zeichenfolgen */
 write(fd,"LO",3);  /* in die Pipe (inkl. Stringendezeichen \0) */

 printf("Programmende Sender\n");

}
