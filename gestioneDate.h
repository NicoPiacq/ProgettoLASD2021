#include "DefinizioniGlobali.h"

// ASSEGNA L'ORARIO DEL TEST - IN INPUT: L'INDICE PER L'ORARIO (0 E 1: MATTINA - 2 E 3: POMERIGGIO - 4 E 5: SERA)
char * AssegnaOrarioTest(int);

// ASSEGNA LA GIORNATA DEL TEST
char * AssegnaGiornataTest();

// INCREMENTA LA DATA DELLA VOCE "ultimaDataRegistrata" IN "FILECONFIGURAZIONE.TXT"
void IncrementaGiornataTest();

// INCREMENTA LA DATA DELLA VOCE "dataGiornaliera" IN "FILECONFIGURAZIONE.TXT"
void IncrementaGiornata();

// LEGGE LA DATA GIORNALIERA DAL FILE "FILECONFIGURAZIONE.TXT"
char * RecuperaDataGiornalieraDaConfigurazione();
