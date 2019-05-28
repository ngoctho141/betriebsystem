/* Beispielprogramm 4.6 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Socket-Kommunikation in der UNIX-Domain mit Streams: Server */

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

 int server_acc_sock;  /* Deskr. des Sockets fuer Verbindungsaufbau */
 int server_comm_sock;
        /* Deskr. des Sockets fuer die Kommunikation mit dem Client */

 struct sockaddr server_addr, client_addr;

 char buffer[256];  /* zur Aufnahme der empfangenen Nachricht */
 unsigned int addr_len; /* Hilfsvariable */

 printf("Hier ist der Server:\n");

 server_acc_sock = socket(AF_UNIX,SOCK_STREAM,0);
 if(server_acc_sock == -1) { printf("Fehler: socket()"); exit(-1); }
 printf("socket() erfolgreich: %d\n", server_acc_sock);

 server_addr.sa_family = AF_UNIX;
 strcpy(server_addr.sa_data,"ServerSocket");

 if(-1 == bind(server_acc_sock,&server_addr,sizeof(struct sockaddr)))
    printf("Fehler: bind()\n");
 else printf("bind() erfolgreich \n");

 /* Einrichten der Warteschlange fuer Verbindungsaufbauwuensche */
 if(-1 == listen(server_acc_sock,1))
   printf("Fehler: listen()\n");
 else printf("listen() erfolgreich \n");

 /* Warten, bis ein Verbindungsaufbauwunsch eintrifft, und
    Akzeptieren dieses Wunschs. Ab dann "steht" die Verbindung */
 addr_len = sizeof(client_addr);
 server_comm_sock = accept(server_acc_sock,&client_addr,&addr_len);
 if(server_comm_sock == -1) printf("Fehler: accept()\n");
 else printf("accept() erfolgreich\n");

 /* Entgegennehmen einer Nachricht des Clients */
 read(server_comm_sock,buffer,sizeof(buffer));
 printf("\nServer hat gelesen: %s\n\n",buffer);

 /* Senden einer Rueckmeldung */
 write(server_comm_sock,"Nachricht ist angekommen",25);

 /* Schlieﬂen der Sockets */
 close(server_acc_sock);
 close(server_comm_sock);

 /* Loeschen der Socket */
 unlink("ServerSocket");
}


