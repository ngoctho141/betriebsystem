/* Beispielprogramm 4.6 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Socket-Kommunikation in der UNIX-Domain mit Streams: Client */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main() {

 int client_sock;  /* Deskriptor des eigenen Sockets */
 int error;
 char buffer[256];

 printf("Hier ist der Client:\n");
 struct sockaddr server_addr;
 client_sock = socket(AF_UNIX,SOCK_STREAM,0);
 server_addr.sa_family = AF_UNIX;
 strcpy(server_addr.sa_data,"ServerSocket");
 error = connect(client_sock,&server_addr,sizeof(struct sockaddr));
 if (error == -1) { printf("Keine Verbindung zum Server!\n"); exit(-1); }
 else printf("Verbindung zum Server erfolgreich.");

 /* Uebertragen einer Nachricht an den Server */
 write(client_sock,"Hallo ",7);
 write(client_sock,"Hallo",6);
 /* Lesen der Rueckantwort des Servers */
 read(client_sock,buffer,sizeof(buffer));
 printf("\nClient hat gelesen: %s\n\n",buffer);

 /* Loeschen der Socket */
 unlink("ServerSocket");
}

/* Achtung: ausführbare Datei wird im Debug-Verzeichnis des Severs erzeugt!
            (siehe Build-Settings des Projekts)
*/

