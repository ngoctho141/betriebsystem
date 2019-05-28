/* Beispielprogramm 4.2 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Kommunikation ueber benannte Pipes: Empfaenger */

#include <fcntl.h>
#include <stdio.h>

main() {

 char buffer[6];  /* Speicher fuer die empfangenen Daten */

 int fd;  /* Deskriptor fuer die Pipe */
 const char* pipe_file = "../../../PIPE_2"; /* Pipe mit Pfad */

 printf("Oeffne Pipe zum Lesen\n");
 fd=open(pipe_file,O_RDONLY);  /* Oeffnen der Pipe zum Lesen */
 if(!fd) {
    printf("Oeffnen der Pipe gescheitert!");
    return 0;
 }


 printf("Lese 6 Zeichen\n");
 read(fd,buffer,6);  /* Lesen von 6 Zeichen aus der Pipe */

 printf("Gelese Zeichen: %s\n",buffer);  /* Ausgabe hier: HALLO */

 unlink("PIPE_2");  /* Loeschen der Pipe */

}
