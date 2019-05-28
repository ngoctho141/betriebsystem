/* Beispielprogramm 4.7 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Socket-Kommunikation in der UNIX-Domain mit Datagrammen: Client */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

main() {

 struct bestellung {   /* fuer die zweite Client-Nachricht */
  char warenname[20];
  int kennziffer;
  float preis;
 } meineBestellung;

 int sock;  /* Deskriptor des Client-Sockets */
 struct sockaddr server_addr;  /* Adresse des Server-Sockets */

 printf("Hier ist der Client:\n");
 /* Erzeugen des Client-Sockets */
 sock = socket(AF_UNIX,SOCK_DGRAM,0);

 /* Senden der ersten Nachricht (ohne Verbindungsaufbau) */
 server_addr.sa_family = AF_UNIX;
 strcpy(server_addr.sa_data,"ServerSocket");
 sendto(sock,"Hallo",6,0,&server_addr,sizeof(struct sockaddr));

 /* Senden der zweiten Nachricht /Grenzen bleiben erhalten) */
 strcpy(meineBestellung.warenname,"USB-Stick");
 meineBestellung.kennziffer = 1234;
 meineBestellung.preis = 9.95;
 sendto(sock,&meineBestellung,sizeof(meineBestellung),
                         0,&server_addr,sizeof(struct sockaddr));

}
