#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define PUFFERKAP 3       /* Kapazit�t des Puffers */
#define ANZAHL_RUNDEN 10  /* Anzahl der Erzeugungs- bzw. Verbrauchsvorg�nge */
#define S_WA     2
