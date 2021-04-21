#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "windows.h"

#include "DefinizioniGlobali.h"

enum esitoTest {
    POSITIVO,
    NEGATIVO
};

enum orarioTest {
    MATTINA,
    POMERIGGIO,
    SERA
};

struct dipendente {
    char nome[LEN_NOME_DIPENDENTE];
    char cognome[LEN_COGNOME_DIPENDENTE];
    char userid[LEN_USERID_DIPENDENTE];
};

struct dipendente accediComeDipendente();
void mostraPaginaDipendente();

void visualizzaStoricoTest();
void stampaStorico();

void visualizzaRichiesteTamponi();

void visualizzaAppuntamentiConfermati();

void aggiungiNuovoAppuntamentoConfermato();
int verificaCodiceFiscale(char[]);

void rimuoviAppuntamentoConfermato();
