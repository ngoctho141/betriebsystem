/* Beispielprogramm 4.3 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Kommunikation ueber unbenannte Pipes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int wertspeicher = 0;

struct objectData {
    float r;
    float pan_angle;
};

 int fda[2];  /* Deskriptoren fuer Leseenden (fdx[0]) */
              /* und Schreibenden (fdx[1]) der Pipes */

/* Funktion, die von einem Thread ausgeführt werden soll */
void *sender(void *p) {
     printf("Hier ist der Sender\n");
     printf("Mein Funktionsparameter: %ld\n", *(long *)p);
     printf("Meine PID: %d\n",getpid());

    struct objectData data;
    ssize_t ret = 0;

    printf("Sender: beginne schleife\n");
    for(int i = 0; i < 10; i++)
    {
        // usleep(1000);
        data.r = i*1.1;
        data.pan_angle = i*1.7;
        printf("Schreibe %d",i);
        ret = write(fda[1],&data,sizeof(struct objectData));
        if(ret<=0)   printf("write returned %d \n",ret);
    }

    // Sende Signal zum Beenden
    data.r = -1;
    ret = write(fda[1],&data,sizeof(struct objectData));
    if(ret<=0)   printf("write returned %d \n",ret);
    
    printf("Sender ist fertig\n");  
    printf("Sender beendet sich\n");
    pthread_exit(NULL);  /* beendet den Thread */
}

/* Funktion, die von einem Thread ausgeführt werden soll */
void *empfaenger(void *p) {
     printf("Hier ist der Empfaenger\n");
     printf("Mein Funktionsparameter: %ld\n", *(long *)p);
     printf("Meine PID: %d\n",getpid());

    struct objectData data;
    ssize_t ret = 0;

    printf("Empfaenger: beginne Schleife\n");
    for(int i = 0; i < 20; i++)
    {
        // usleep(100);
        data.r = i*1.1;
        data.pan_angle = i*1.7;
        printf("Schreibe %d",i);
        /* read blockiert bis nächste Botschaft kommt, wenn keine mehr
         * kommt, dann wird endlos gewartet*/
        ret = read(fda[0],&data,sizeof(struct objectData));
        if(ret<=0)   printf("read returned %d \n",ret);
        else {
            if(data.r>=0) printf("\empfangen: %.3f %.3f\n",data.r, data.pan_angle);
            else break;
        }
    }
    printf("Empfaenger ist fertig\n");  
    printf("Empfaenger beendet sich\n");
    pthread_exit(NULL);  /* beendet den Thread */
 }
   
 

int main() {
     printf("PID des Hauptprogramms: %d\n",getpid());
     printf("Wertspeicher: %d\n\n",wertspeicher);

     pthread_t th1, th2;   /* IDs der neu erzeugten Threads  */
     long param1, param2;  /* Parameter zur Übergabe an die Threads */
     int err;              /* Fehlercode von pthread_create() */
     void *status;         /* Rückgabeparameter von pthread_join */

     pipe(fda); /* Erzeugung zweier unbenannter Pipes; Speichern der */

     
     /* Erzeugung eines Threads */
     printf("Erzeuge den ersten Thread\n");
     param1 = 1111;
     err = pthread_create(&th1, NULL, sender, &param1);
        /* 1. Parameter: Rückgabewert = ID des neuen Threads
           2. Parameter: Attribute (hier: Standardattribute)
           3. Parameter: Funktion, die der Thread ausführen soll
           4. Parameter: Parameter für die Funktion  */
     if (err!=0) {
      printf("Fehler bei der Erzeugung des ersten Threads\n");
      exit(-1);
     }
     printf("Thread-ID %lu\n\n",th1);

     /* Erzeugung eines zweiten Threads */
     printf("Erzeuge den zweiten Thread\n");
     param2 = 2222;
     err = pthread_create(&th2, NULL, empfaenger, &param2);
     if (err!=0) {
          printf("Fehler bei der Erzeugung des zweiten Threads\n");
          exit(-1);
     }
    printf("Thread-ID %lu\n\n",th2);

    printf("Hauptprozess wartet auf Threads\n");
    pthread_join(th1,&status);
    pthread_join(th2,&status);

    close(fda[0]);
    close(fda[1]);
    printf("Hauptprozess beendet\n");
        
    return 0;
}
