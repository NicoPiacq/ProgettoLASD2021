#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "windows.h"

#define LEN_NOME_DIPENDENTE 12
#define LEN_COGNOME_DIPENDENTE 12
#define LEN_USERID_DIPENDENTE 10
#define LEN_PASSWORD_DIPENDENTE 15

struct dipendente {
    char nome[LEN_NOME_DIPENDENTE];
    char cognome[LEN_COGNOME_DIPENDENTE];
    char userid[LEN_USERID_DIPENDENTE];
};

struct listaTesta {

};

struct listaNodo {

};

struct dipendente accediComeDipendente();
void mostraPaginaDipendente();

void visualizzaStoricoTest();

void visualizzaRichiesteTamponi();

void visualizzaAppuntamentiConfermati();

void aggiungiNuovoAppuntamentoConfermato();
int verificaCodiceFiscale(char[]);

void rimuoviAppuntamentoConfermato();
