#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "windows.h"
#include "conio.h"

/*
    QUESTO HEADER CONTIENE I PROTOTIPI RIGUARDANTI LA PARTE DEL PAZIENTE DI UN LABORATORIO DI ANALISI
*/

struct paziente {
    char codiceFiscale[17];
    char nome[12];
    char cognome[12];
    char password[10];
    int haEsito;
};

void mostraPaginaPrincipale(struct paziente);

struct paziente accediComePaziente();
void impostaTitoloConsoleConCF(char[]);

void registrazionePaziente();
int generaRandomPassword();

void prenotazioneTampone(char[]);
int controllaSeGiaPrenotato(char[]);

void visualizzaStatoAppuntamento();
void cancellaRichiestaAppuntamento();

void visualizzaEsitoTampone();
