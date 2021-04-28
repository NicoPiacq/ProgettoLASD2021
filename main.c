/*
    QUESTO E' IL PROGETTO DI LAB. DI ALGORITMI E STRUTTURE DATI
    STUDENTE: PIACQUADDIO NICOLA
    MATRICOLA: N86002904

    SOFTWARE: SISTEMA PER LE PRENOTAZIONI DI UN LABORATORIO DI ANALISI E GESTIONE TAMPONI MOLECOLARI
*/

#include "HeaderPaziente.h"
#include "HeaderDipendente.h"
#include "gestioneDate.h"

int main() {

    // VARIABILE PER SCEGLIERE L'OPZIONE DI ACCESSO AL SISTEMA
    int opzione = 0;

    do {

        // DIAMO LE PRIME STAMPE IN CONSOLE
        SetConsoleTitle("Laboratorio di Analisi");
        opzione = 0;
        system("cls");

        printf("Benvenuto nel Laboratorio di Analisi Tamponi Molecolari 'San Nicola'.\nQuesto software consente la prenotazione di un tampone\ne la verifica dell'esito direttamente da PC!\n");
        printf("\nSe sei un utente gia' registrato:\n");
        printf("1. Accesso per i pazienti\n2. Accesso per i dipendenti\n");
        printf("\n\nNon sei registrato e vuoi effettuare un tampone?\n3. Registrati come nuovo paziente\n\n4. Esci dal programma");

        // CHIEDIAMO ALL'UTENTE DI SCEGLIERE UN'OPZIONE: 1/2 ACCESSO - 3 REGISTRAZIONE - 4 USCITA
        printf("\n\n\nInserire un'opzione: ");
        scanf("%d",&opzione);

        switch(opzione) {
            case 1: {
                // RICHIAMA PRIMA LA PAGINA DI LOGIN PER IL PAZIENTE (CF E PSW) E POI MOSTRA LA PAGINA PRINCIPALE PER IL PAZIENTE
                mostraPaginaPrincipale(accediComePaziente());
                break;

            }
            case 2: {
                // RICHIAMA PRIMA LA PAGINA DI LOGIN PER IL DIPENDENTE (USERID E PSW) E POI MOSTRA LA PAGINA PRINCIPALE PER IL DIPENDENTE. ALL'USCITA DELLA FUNZIONE, EFFETTUA IL LOGOUT (ASSEGNANDO GLI ESITI) E INCREMENTA LA DATA GIORNALIERA
                mostraPaginaDipendente(accediComeDipendente());
                LogoutChiusuraGiornata();
                break;
            }
            case 3: {
                // RICHIAMA LA PAGINA DI REGISTRAZIONE DATI DI UN NUOVO PAZIENTE
                registrazionePaziente();
                break;

            }
            case 4: {
                // ESCE DAL PROGRAMMA DEFINITIVAMENTE
                return 0;

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
