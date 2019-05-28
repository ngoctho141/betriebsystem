/* Beispielprogramm 4.5 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Socket-Kommunikation in der Internet-Domain mit Streams: Server */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

 int server_acc_sock;  /* Deskr. des Sockets fuer Verbindungsaufbau */
 int server_comm_sock;
        /* Deskr. des Sockets fuer die Kommunikation mit dem Client */

 struct sockaddr_in server_addr; /* Adresse des Server-Sockets */
 struct sockaddr client_addr;    /* Adresse des Client-Sockets */

 char buffer[256];  /* zur Aufnahme der empfangenen Nachricht */
 unsigned int addr_len; /* Hilfsvariable */

 struct {
    int l_onoff;
    int l_linger;
 } linger;  /* siehe Kommentar unten */

 printf("Hier ist der Server:\n");

 /* Erzeugen eines eigenen Sockets, ueber den Verbindungs-
    aufbauwuensche von Clients entgegengenommen werden */
 server_acc_sock = socket(AF_INET,SOCK_STREAM,0);
 if(server_acc_sock == -1) { printf("Fehler: socket()"); exit(-1); }
 printf("socket() erfolgreich: %d\n", server_acc_sock);

 /* Sicherstellen, dass der Socket am Ende des Serverprogramms
    sofort geschlossen wird */
 linger.l_onoff = 1; /* linger active */
 linger.l_linger = 0; /* how many seconds to linger for */
 setsockopt(server_acc_sock,SOL_SOCKET,SO_LINGER,&linger,sizeof(linger));

 /* Binden einer IP-Adresse und Portnummer an den eigenen Socket */
 server_addr.sin_family = AF_INET;
 // server_addr.sin_addr.s_addr = inet_addr("62.138.238.45");
 server_addr.sin_addr.s_addr = inet_addr("0.0.0.0"); /* lokal */
               /* Hier IP-Adresse in numerischer Form einsetzen */
               /* Adressen in symbolischer Form: siehe 4.2.4.3 */
 server_addr.sin_port = htons(55555);
   /* htons: Umwandlung der Zahl in ein netzweit lesbares Format */
 if(-1 == bind(server_acc_sock,(struct sockaddr *) &server_addr,
          sizeof(struct sockaddr)) )  printf("Fehler: bind()\n");
 else printf("bind() erfolgreich \n");

 /* Einrichten der Warteschlange fuer Verbindungsaufbauwuensche */
 if(-1 == listen(server_acc_sock,1))
   printf("Fehler: listen()\n");
 else printf("listen() erfolgreich \n");

  /* Offene Ports in der Konsole ansehen: sudo netstat -tulpen */

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
}
