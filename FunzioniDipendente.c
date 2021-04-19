#include "HeaderDipendente.h"
#include "HeaderPaziente.h"

struct dipendente accediComeDipendente() {

    FILE *fileListaDipendenti;

    char accessoUserId[LEN_USERID_DIPENDENTE];
    char accessoPassword[LEN_PASSWORD_DIPENDENTE];

    struct dipendente accessoDatiDipendente;

    char userIdPrelevatoDaFile[LEN_USERID_DIPENDENTE];
    char nomePrelevatoDaFile[LEN_NOME_DIPENDENTE];
    char cognomePrelevatoDaFile[LEN_COGNOME_DIPENDENTE];
    char passwordPrelevatoDaFile[LEN_PASSWORD_DIPENDENTE];

    do {
        system("cls");

        printf("Accesso alla Pagina Dipendenti del Laboratorio di Analisi Tamponi Molecolari 'San Nicola'\n\n");
        printf("Inserisci l'User ID: ");
        scanf("%s",accessoUserId);

        printf("\nInserisci la password: ");
        scanf("%s",accessoPassword);

        fileListaDipendenti = fopen("Dati/ListaDipendenti.txt", "r");

        while(fscanf(fileListaDipendenti, "%s %s %s %s\n", userIdPrelevatoDaFile, nomePrelevatoDaFile, cognomePrelevatoDaFile, passwordPrelevatoDaFile) == 4) {
            if(strcmp(accessoUserId, userIdPrelevatoDaFile) == 0 && strcmp(accessoPassword, passwordPrelevatoDaFile) == 0) {
                strcpy(accessoDatiDipendente.userid, userIdPrelevatoDaFile);
                strcpy(accessoDatiDipendente.nome, nomePrelevatoDaFile);
                strcpy(accessoDatiDipendente.cognome, cognomePrelevatoDaFile);

                printf("\nAccesso effettuato!\nAdesso andrai alla pagina principale...");
                fclose(fileListaDipendenti);

                Sleep(3000);

                impostaTitoloConsoleConCF(accessoDatiDipendente.userid);
                return accessoDatiDipendente;
            }
        }

        printf("\nI dati inseriti non sono corretti!\n");
        rewind(fileListaDipendenti);
        system("pause");
    }
    while(1);

}

int verificaCodiceFiscale(char codFiscale[]) {

    FILE *fileListaUtenti;

    fileListaUtenti = fopen("Dati/ListaUtenti.txt", "r");

    int statoRichiesta;

    char codiceFiscalePrelevatoDaFile[LEN_CODICEFISCALE];
    char nomePrelevatoDaFile[LEN_NOME];
    char cognomePrelevatoDaFile[LEN_COGNOME];
    char passwordPrelevatoDaFile[LEN_PASSWORD];

    // VEDIAMO SE PRIMA ESISTE L'UTENTE
    while(fscanf(fileListaUtenti, "%s %s %s %s\n", codiceFiscalePrelevatoDaFile, nomePrelevatoDaFile, cognomePrelevatoDaFile, passwordPrelevatoDaFile) == 4) {
        if(strcmp(codFiscale, codiceFiscalePrelevatoDaFile) == 0) {
            statoRichiesta = 0;
            break;
        }
        else {
            statoRichiesta = 1;
        }
    }

    fclose(fileListaUtenti);

    // VEDIAMO SE HA UN APPUNTAMENTO IN RICHIESTA
    if (controllaSeGiaPrenotato(codFiscale)) {
        statoRichiesta = 2;
    }

    // VEDIAMO SE INVECE HA UN APPUNTAMENTO CONFERMATO
    else if (controllaSeGiaConfermato(codFiscale) == 2) {
        statoRichiesta = 3;
    }

    return statoRichiesta;
}

void aggiungiNuovoAppuntamentoConfermato() {

    int statoAppuntamento;
    char codiceFiscalePaziente[LEN_CODICEFISCALE];

    do {
        system("cls");

        printf("Aggiungi un nuovo appuntamento direttamente da qui, senza che il paziente faccia una richiesta.\n");
        printf("Il paziente deve aver registrato il proprio codice fiscale e non deve aver fatto una richiesta.\n\n");
        printf("Inserisci il Codice Fiscale del paziente: ");
        scanf("%s",codiceFiscalePaziente);

        statoAppuntamento = verificaCodiceFiscale(codiceFiscalePaziente);

        switch(statoAppuntamento) {

            // SE L'UTENTE ESISTE E NON HA NESSUN TIPO DI RICHIESTA, SI PROCEDE CON L'INSERIMENTO
            case 0: {

                FILE *fileAppuntamentiConfermati;
                int giornoAppuntamento;
                char orarioAppuntamento[LEN_GIORNATA];

                fileAppuntamentiConfermati = fopen("Dati/AppuntamentiConfermati.txt", "w");

                printf("\nGiorno della prenotazione: ");
                scanf("%d",&giornoAppuntamento);

                printf("\nOra della prenotazione (Mattina/Pomeriggio/Sera): ");
                scanf("%s",orarioAppuntamento);

                fprintf(fileAppuntamentiConfermati, "%s %d %s\n", codiceFiscalePaziente, giornoAppuntamento, orarioAppuntamento);

                fclose(fileAppuntamentiConfermati);

                printf("\n\nAppuntamento inserito correttamente!\nTornerai alla pagina principale in 5 secondi...");
                Sleep(5000);
                return;
            }

            // SE L'UTENTE NON ESISTE ALLORA DARA' ERRORE INESISTENZA
            case 1: {
                printf("\n\nIl codice fiscale inserito non esiste tra i dati utenti registrati!\n");
                Sleep(4000);
                break;
            }

            // SE L'UTENTE HA UN APPUNTAMENTO IN RICHIESTA, SI INVITA L'OPERATORE A CONFERMARLO
            case 2: {
                printf("\n\nIl codice fiscale inserito ha gia' una richiesta inserita.\nSi invita di confermarlo con l'apposita funzione.\n");
                Sleep(4000);
                break;
            }

            // SE L'UTENTE HA GIA' UN APPUNTAMENTO CONFERMATO, VIENE SOLO NOTIFICATO L'OPERATORE
            case 3: {
                printf("\n\nIl codice fiscale inserito ha gia' un appuntamento confermato.\n");
                Sleep(4000);
                break;
            }

            // IN CASO DI ERRORE GENERICO
            default: {
                printf("\n\nErrore nella verifica del codice fiscale!");
                Sleep(3000);
                break;
            }
        }
    }
    while(1);
}

void rimuoviAppuntamentoConfermato() {

    // INIZIAMO AD APRIRE IL FILE DA DOVE COPIARE GLI APPUNTAMENTI
    FILE *fileAppuntamentiConfermatiVecchio;
    fileAppuntamentiConfermatiVecchio = fopen("Dati/AppuntamentiConfermati.txt", "r");

    // VERIFICHIAMO PRIMA SE SONO PRESENTI APPUNTAMENTI: SE IL FILE HA DIMENSIONE 0 BYTE, USCIRA' DALLA FUNZIONE STAMPANDO UN ERRORE IN CONSOLE.
    fseek(fileAppuntamentiConfermatiVecchio, 0L, SEEK_END);
    long int dimensioneFile = ftell(fileAppuntamentiConfermatiVecchio);

    // CONTROLLIAMO LA DIMENSIONE DEL FILE
    if(dimensioneFile <= 0) {
        printf("\nNon c'e' nessuna richiesta che si puo' eliminare.");
        fclose(fileAppuntamentiConfermatiVecchio);
        Sleep(4000);
        return;
    }

    // QUESTA VARIABILE SERVIRA' PER INDICARE CHE TIPOLOGIA DI RICHIESTA HA L'UTENTE.
    // 0: NESSUN APPUNTAMENTO - 1: UTENTE NON ESISTE - 2: UTENTE HA UNA RICHIESTA IN ATTESA - 3: UTENTE HA UNA RICHIESTA CONFERMATA
    int statoAppuntamento;

    char codiceFiscalePaziente[LEN_CODICEFISCALE];

    do {
        system("cls");

        printf("Rimuovi un appuntamento confermato.\n");
        printf("Dev'essere inserito il codice fiscale del paziente e che quest'ultimo abbia un appuntamento confermato.\n\n");
        printf("Inserisci il Codice Fiscale del paziente: ");
        scanf("%s",codiceFiscalePaziente);

        // VERIFICHIAMO CHE TIPO DI RICHIESTA HA IL CODICE FISCALE INSERITO
        statoAppuntamento = verificaCodiceFiscale(codiceFiscalePaziente);

        switch(statoAppuntamento) {

            // L'UTENTE NON HA NESSUN TIPO DI APPUNTAMENTO RICHIESTO
            case 0: {
                printf("\n\nIl codice fiscale inserito non ha effettuato nessuna richiesta di appuntamento.\n");
                Sleep(4000);
                break;
            }

            // SE L'UTENTE NON ESISTE ALLORA DARA' ERRORE INESISTENZA
            case 1: {
                printf("\n\nIl codice fiscale inserito non esiste tra i dati utenti registrati!\n");
                Sleep(4000);
                break;
            }

            // SE L'UTENTE HA UN APPUNTAMENTO IN RICHIESTA, SI INVITA L'OPERATORE A CONFERMARLO
            case 2: {
                printf("\n\nIl codice fiscale inserito ha ancora in richiesta di conferma il suo appuntamento.\n");
                Sleep(4000);
                break;
            }

            // SE L'UTENTE HA GIA' UN APPUNTAMENTO CONFERMATO, VIENE SOLO NOTIFICATO L'OPERATORE
            case 3: {

                // DICHIARIAMO LA VARIABILE PER IL FILE NUOVO
                FILE *fileAppuntamentiConfermatiNuovo;

                // VARIABILI DOVE CONSERVARE I RISULTATI DEL FSCANF
                int giornoPrelevatoDaFile;
                char orarioAppuntamentoPrelevatoDaFile[LEN_GIORNATA];
                char stringaCodFiscaleDaFile[LEN_CODICEFISCALE];

                // "CREIAMO" IL NUOVO FILE CON SUFFISSO TEMP
                fileAppuntamentiConfermatiNuovo = fopen("Dati/TEMPAppuntamentiConfermati.txt", "w");


                // LEGGIAMO DAL VECCHIO FILE RIGO PER RIGO OGNI INFORMAZIONE
                while(fscanf(fileAppuntamentiConfermatiVecchio, "%s %d %s", stringaCodFiscaleDaFile, &giornoPrelevatoDaFile, orarioAppuntamentoPrelevatoDaFile) == 3) {

                    // VERIFICHIAMO IL RIGO DA NON RICOPIARE NEL NUOVO FILE
                    if(strcmp(stringaCodFiscaleDaFile, codiceFiscalePaziente) == 0) {
                        continue;
                    }
                    else {
                        // SE L'IF NON E' RISPETTATO, VENGONO RICOPIATE LE ALTRE INFORMAZIONI TRANNE QUELLE DEL CODICE FISCALE INSERITO
                        fprintf(fileAppuntamentiConfermatiNuovo, "%s %d %s\n", stringaCodFiscaleDaFile, giornoPrelevatoDaFile, orarioAppuntamentoPrelevatoDaFile);
                    }

                }

                // CHIUDIAMO I FILE
                fclose(fileAppuntamentiConfermatiVecchio);
                fclose(fileAppuntamentiConfermatiNuovo);

                // CANCELLIAMO IL VECCHIO FILE
                remove("Dati/AppuntamentiConfermati.txt");
                // RINOMINIAMO IL FILE TEMP
                rename("Dati/TEMPAppuntamentiConfermati.txt", "Dati/AppuntamentiConfermati.txt");

                printf("\n\nAppuntamento rimosso correttamente!\nTornerai alla pagina principale in 5 secondi...");
                Sleep(5000);
                return;
            }

            // IN CASO DI ERRORE GENERICO
            default: {
                printf("\n\nErrore nella verifica del codice fiscale!");
                Sleep(3000);
                break;
            }
        }
    }
    while(1);


}

void mostraPaginaDipendente(struct dipendente datiDipendente) {

int opzione = 0;

    do {
        system("cls");

        printf("Pagina Dipendenti del Laboratorio di Analisi 'San Nicola'\n\n");
        printf("*************DATI DIPENDENTE*************\n\n\t%s %s\n\tUSER ID: %s\n\n", datiDipendente.nome, datiDipendente.cognome, datiDipendente.userid);
        printf("*****************************************");
        printf("\n\nEcco cosa puoi fare: \n\n");


        printf("1. Visualizza storico Test effettuati\n2. Visualizza richieste appuntamenti\n3. Visualizza appuntamenti fissati\n4. Aggiungi appuntamento\n5. Cancella appuntamento\n6. Esegui il logout");


        printf("\n\nScegliere un'opzione: ");
        scanf("%d",&opzione);

        switch(opzione) {
            case 1: {

                break;
            }
            case 2: {

                break;
            }
            case 3: {

                break;
            }
            case 4: {

                aggiungiNuovoAppuntamentoConfermato();
                break;
            }
            case 5: {

                rimuoviAppuntamentoConfermato();
                break;
            }
            case 6: {
                return;
            }
            default: {
                printf("Hai scelto un'opzione non disponibile");
                Sleep(3000);
                break;
            }
        }
    }
    while(1);

}
