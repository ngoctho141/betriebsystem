/* Beispielprogramm 4.5 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Socket-Kommunikation in der Internet-Domain mit Streams: Client */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

main() {

 int client_sock;  /* Deskriptor des eigenen Sockets */
 struct sockaddr_in server_addr;  /* Adresse des Server-Socket */

 char buffer[256];  /* zur Aufnahme der empfangenen Rueckantwort */
 int error;  /* Hilfsvariable */

 printf("Hier ist der Client:\n");
 /* Erzeugung eines eigenen Sockets */
 client_sock = socket(AF_INET,SOCK_STREAM,0);

 /* Zusammenstellen der Adresse des Server-Sockets */
 server_addr.sin_family = AF_INET;
 // server_addr.sin_addr.s_addr = inet_addr("62.138.238.45");
 server_addr.sin_addr.s_addr = inet_addr("0.0.0.0"); /* lokal */
               /* Hier IP-Adresse in numerischer Form einsetzen */
               /* Adressen in symbolischer Form: siehe 4.2.4.3 */
 server_addr.sin_port = htons(55555);

 /* Verbinden des eigenen Sockets mit dem Server-Socket */
 error = connect(client_sock,(struct sockaddr *) &server_addr,sizeof(struct sockaddr));
 if (error == -1) { printf("Keine Verbindung zum Server!\n"); exit(-1); }
 else printf("Verbindung zum Server erfolgreich.");

 /* Uebertragen einer Nachricht an den Server */
 write(client_sock,"Hallo",6);


 /* Lesen der Rueckantwort des Servers */
 read(client_sock,buffer,sizeof(buffer));
 printf("\nClient hat gelesen: %s\n\n",buffer);

}
