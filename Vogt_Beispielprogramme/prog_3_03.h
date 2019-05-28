#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define PUFFERKAP 3       /* Kapazität des Puffers */
#define ANZAHL_RUNDEN 10  /* Anzahl der Erzeugungs- bzw. Verbrauchsvorgänge */
#define S_BELEGT 0        /* Symbolische Namen für die Sem.nummern innerhalb */
#define S_FREI   1        /* der Gruppe (vergleiche Beispiel in 3.3.2.3 und siehe unten) */
#define S_WA     2