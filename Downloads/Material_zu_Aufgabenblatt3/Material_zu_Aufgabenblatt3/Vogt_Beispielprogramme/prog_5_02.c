/* Beispielprogramm 5.2 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Kontaktieren eines WWW-Servers ueber Sockets */

#include <netdb.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 8192

main() {

 int sock;  /* ID der eigenen Socket */
 int error, numbytes, fd;  /* Hilfsvariablen */
 char buffer[BUFSIZE]; /* Zwischenspeicher für eintreffende Daten */
 struct sockaddr_in server_addr;  /* Server-Adresse */
 struct hostent *host; /* zur Verarbeitung einer symbol. Adresse */

 /* Erzeugung einer Stream-Socket in der Internet-Domain */
 sock = socket(AF_INET,SOCK_STREAM,0);

 /* Zusammenstellen der Server-Adresse */
 server_addr.sin_family = AF_INET;
 host = gethostbyname("www.nt.th-koeln.de");
 bcopy(host->h_addr,&server_addr.sin_addr,host->h_length);
 // alternativ: server_addr.sin_addr.s_addr = inet_addr("139.6.10.90");
 server_addr.sin_port = htons(80);

 /* Verbindung der Socket mit der Socket des Servers */
 error = connect(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
 if (error == 0) printf("Mit Server verbunden\n");
 else { printf("Keine Verbindung zum Server!\n"); exit(-1); }

 /*
 struct sockaddr peer;
 int addrlenpeer;
 getpeername(sock, &peer, &addrlenpeer);
 printf("peer: %d\n",peer.sa_data);
 */

 /* Übertragung des HTTP-GET-Befehls */
 numbytes = write(sock,"GET /vogt/index.html HTTP/1.1\n",30);
 // printf("%d Bytes gesendet...\n",numbytes);
 numbytes = write(sock,"Host: www.nt.th-koeln.de\n",25);
 // printf("%d Bytes gesendet...\n",numbytes);
 numbytes = write(sock,"Connection: Close\n\n",19);
 // printf("%d Bytes gesendet...\n",numbytes);

 /* Erzeugung einer lokalen Datei zur Aufnahme der Web-Seite */
 fd = open("webpage.html",O_CREAT|O_WRONLY,0777);
 /* Blockweises Einlesen und Speichern der Seite (vergleiche 4.2.4.5) */
 do {
   numbytes = read(sock,buffer,BUFSIZE);
   printf("%d Bytes empfangen...\n",numbytes);
   write(fd,buffer,numbytes);
 } while (numbytes>0);

 printf("Schliesze Datei.\n");
 close(fd);

}


/* Vorabtest mit telnet:
Installation: sudo apt-get install telnet

telnet www.nt.th-koeln.de 80 >webpage.html
GET /vogt/index.html HTTP/1.1
Host: www.nt.th-koeln.de
Connection: Close
<return>

im Browser:
http://www.nt.th-koeln.de/vogt/index.html

Programm funktioniert aber nicht !!!

*/
