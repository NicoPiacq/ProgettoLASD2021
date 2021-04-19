#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "windows.h"
#include "conio.h"

#define LEN_CODICEFISCALE 17
#define LEN_NOME 12
#define LEN_COGNOME 12
#define LEN_PASSWORD 15
#define LEN_SINTOMI 128
#define LEN_GIORNATA 11
#define LEN_TITOLOCONSOLE 100


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

void visualizzaStatoAppuntamento();
void cancellaRichiestaTampone(char[]);

void visualizzaEsitoTampone();
