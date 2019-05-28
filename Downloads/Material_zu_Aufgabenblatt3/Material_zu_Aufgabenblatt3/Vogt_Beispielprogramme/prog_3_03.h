#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define PUFFERKAP 3       /* Kapazit�t des Puffers */
#define ANZAHL_RUNDEN 10  /* Anzahl der Erzeugungs- bzw. Verbrauchsvorg�nge */
#define S_BELEGT 0        /* Symbolische Namen f�r die Sem.nummern innerhalb */
#define S_FREI   1        /* der Gruppe (vergleiche Beispiel in 3.3.2.3 und siehe unten) */
#define S_WA     2