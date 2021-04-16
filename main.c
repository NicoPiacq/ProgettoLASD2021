/*
    QUESTO E' IL PROGETTO DI LAB. DI ALGORITMI E STRUTTURE DATI
    STUDENTE: PIACQUADDIO NICOLA
    MATRICOLA: N86002904

    SOFTWARE: SISTEMA PER LE PRENOTAZIONI DI UN LABORATORIO DI ANALISI E GESTIONE TAMPONI MOLECOLARI
*/

#include "HeaderPaziente.h"
#include "windows.h"

int main()
{
    int opzione = 0;
    struct paziente datiGeneraliPaziente;

    do {
        SetConsoleTitle("Laboratorio di Analisi");
        opzione = 0;
        system("cls");
        printf("Benvenuto nel Laboratorio di Analisi Tamponi Molecolari 'San Nicola'.\nQuesto software consente la prenotazione di un tampone\ne la verifica dell'esito direttamente da PC!\n");
        printf("\nSe sei un utente gia' registrato:\n");
        printf("1. Accesso per i pazienti\n2. Accesso per i dipendenti\n");
        printf("\n\nNon sei registrato e vuoi effettuare un tampone?\n3. Registrati come nuovo paziente\n\n4. Esci dal programma");

        printf("\n\n\nInserire un'opzione: ");
        scanf("%d",&opzione);

        switch(opzione) {
            case 1: {
                datiGeneraliPaziente = accediComePaziente();
                mostraPaginaPrincipale(datiGeneraliPaziente);
                break;
            }
            case 2: {
                system("cls");
                break;
            }
            case 3: {
                registrazionePaziente();
                break;
            }
            case 4: {
                exit(0);
                break;
            }
            default: {
                printf("\nHai selezionato un'opzione inesistente! Riprova.");
                Sleep(3000);
                break;
            }
        }
    }
    while(1);

}
