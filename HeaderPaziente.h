#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "windows.h"
#include "conio.h"
#include "DefinizioniGlobali.h"


/*
    QUESTO HEADER CONTIENE I PROTOTIPI RIGUARDANTI LA PARTE DEL PAZIENTE DI UN LABORATORIO DI ANALISI
*/

struct paziente {
    char codiceFiscale[LEN_CODICEFISCALE];
    char nome[LEN_NOME];
    char cognome[LEN_COGNOME];
    int haEsito;
};

void mostraPaginaPrincipale(struct paziente);
void aggiornaStatoRichiesta(char[]);

struct paziente accediComePaziente();
void impostaTitoloConsoleConCF(char[]);

void registrazionePaziente();
int generaRandomPassword();

void prenotazioneTampone(char[]);
int controllaSeGiaPrenotato(char[]);
int controllaSeGiaConfermato(char[]);

void visualizzaStatoAppuntamento();
void cancellaRichiestaTampone(char[]);

void visualizzaEsitoTampone();
