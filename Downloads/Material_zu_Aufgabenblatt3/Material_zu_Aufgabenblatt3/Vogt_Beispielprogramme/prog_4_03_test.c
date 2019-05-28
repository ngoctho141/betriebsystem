/* Beispielprogramm 4.3 aus                           */
/* C. Vogt, Nebenlaeufige Programmierung, Hanser 2012 */

/* Kommunikation ueber unbenannte Pipes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    struct objectData {
        float r;
        float pan_angle;
    };

    struct objectData data;
    int fda[2];  /* Deskriptoren fuer Leseenden (fdx[0]) */
                      /* und Schreibenden (fdx[1]) der Pipes */
    pipe(fda); /* Erzeugung zweier unbenannter Pipes; Speichern der */

    if (fork()==0) {
        /* Sohn: sendet Stringnachricht und empfaengt Rueckantwort */
        close(fda[0]);  /* nicht benoetigte Lese- und */

        for(int i = 1; i < 20; i++)
        {
            usleep(10000);
            data.r = i*1.1;
            data.pan_angle = i*1.7;
            write(fda[1],&data,sizeof(struct objectData));
        }
        
        close(fda[1]);
        printf("Ende des Sohns\n");
        exit(0);
    }

    /* Vater: empfaengt Stringnachricht und sendet Rueckantwort */
    close(fda[1]);  /* nicht benoetigte Lese- und */

    int terminated = 0;
    ssize_t ret = 0;
    for(;!terminated;)
    {
        ret = read(fda[0],&data,sizeof(struct objectData));
        if(ret == 0) { 
            // printf("read returned %d - terminate Vater\n",ret);
            terminated = 1; 
        }
        else printf("\nVater liest aus der Pipe: %.3f %.3f\n",
            data.r,data.pan_angle);
    }

    close(fda[0]);
    printf("Ende des Vaters\n");
    
    // pthread_join(vcdec_thread_id,&status_vcdec_thread);

    return 0;
}
