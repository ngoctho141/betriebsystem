/* Beispielprogramm 4.6 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Socket-Kommunikation in der UNIX-Domain mit Datagrammen: Server */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>

int main() {
 char buffer[256];  /* zur Aufnahme der ersten Client-Nachricht */

 struct bestellung {   /* zur Aufnahme */
  char warenname[20];  /* der zweiten Client-Nachricht */
  int kennziffer;
  float preis;
 } clientBestellung;

 int sock;  /* Deskriptor des Server-Sockets */
 struct sockaddr server_addr;  /* Adresse des Server-Sockets */

 printf("Hier ist der Server:\n");

 /* Erzeugen eines Sockets, ueber die Nachrichten
    von Clients entgegengenommen werden */
 sock = socket(AF_UNIX,SOCK_DGRAM,0);
 if(sock == -1) { printf("Fehler: socket()"); exit(-1); }
 printf("socket() erfolgreich: %d\n", sock);

 /* Anbinden eines Namens (= einer lokalen Adresse) an den Socket */
 server_addr.sa_family = AF_UNIX;
 strcpy(server_addr.sa_data,"ServerSocket");
 if(-1 == bind(sock,&server_addr,sizeof(struct sockaddr)))
    printf("Fehler: bind()\n");
 else printf("bind() erfolgreich \n");

 /* Lesen der ersten Nachricht des Clients */
 recvfrom(sock,buffer,sizeof(buffer),0,0,0);
 printf("\nGelesen: %s\n\n",buffer);

 /* Lesen der zweiten Nachricht des Clients */
 recvfrom(sock,&clientBestellung,sizeof(clientBestellung),0,0,0);
 printf("Gelesen:\n");
 printf("  Warenname: %s\n",clientBestellung.warenname);
 printf("  Kennziffer: %d\n",clientBestellung.kennziffer);
 printf("  Preis: %.2f\n",clientBestellung.preis);

 /* Schlieﬂen und Loeschen des Sockets */
 close(sock);
 unlink("ServerSocket");
}
