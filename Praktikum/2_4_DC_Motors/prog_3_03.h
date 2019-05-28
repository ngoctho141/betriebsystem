#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define PUFFERKAP 3       /* Kapazität des Puffers */
#define ANZAHL_RUNDEN 10  /* Anzahl der Erzeugungs- bzw. Verbrauchsvorgänge */
#define S_WA     2
