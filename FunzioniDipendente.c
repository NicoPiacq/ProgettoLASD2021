#include "HeaderDipendente.h"
#include "HeaderPaziente.h"
#include "gestioneListe.h"
#include "gestioneDate.h"

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

void visualizzaStoricoTest() {

    // INIZIAMO AD APRIRE IL FILE DA DOVE LEGGERE GLI ESITI
    FILE *fileEsitoTest;
    fileEsitoTest = fopen("Dati/StoricoTest.txt", "r");

    // DICHIARIAMO LA TESTA DELLA LISTA
    listaRisultati * testaListaRisultati;

    // VERIFICHIAMO PRIMA SE SONO PRESENTI DEI TEST: SE IL FILE HA DIMENSIONE 0 BYTE, USCIRA' DALLA FUNZIONE STAMPANDO UN ERRORE IN CONSOLE.
    fseek(fileEsitoTest, 0L, SEEK_END);
    long int dimensioneFile = ftell(fileEsitoTest);

    if(dimensioneFile <= 0) {
        printf("\nImpossibile proseguire!\nLo storico dei test e' vuoto.");
        fclose(fileEsitoTest);
        Sleep(4500);
        return;
    }

    // SE IL FILE CONTIENE (PRESUMENDO CORRETTO) TEST EFFETTUATI ALLORA LI RICOPIEREMO IN UNA LISTA SEMPLICE

    // PRIMA PERO' "RIAVVIAMO" IL PUNTATORE DEL FILE E RIPORTIAMOLO ALLA PRIMA POSIZIONE
    rewind(fileEsitoTest);

    // INIZIALIZZIAMO LA TESTA
    testaListaRisultati = CreaTestaRisultati();

    // CREIAMO LE VARIABILI DOVE ASSEGNARE LE STRINGHE LETTE DAL FILE
    char codiceFiscalePrelevatoDaFile[LEN_CODICEFISCALE];
    char dataTestPrelevatoDaFile[LEN_DATATEST];
    char orarioTestPrelevatoDaFile[LEN_ORARIOTEST];
    char esitoTestPrelevatoDaFile[LEN_ESITO];

    // CREIAMO I NODI E INSERIAMOLI DIRETTAMENTE IN CODA
    while(fscanf(fileEsitoTest, "%s %s %s %s", codiceFiscalePrelevatoDaFile, dataTestPrelevatoDaFile, orarioTestPrelevatoDaFile, esitoTestPrelevatoDaFile) == 4) {
            InserimentoInCodaRisultati(testaListaRisultati, codiceFiscalePrelevatoDaFile, dataTestPrelevatoDaFile, orarioTestPrelevatoDaFile, esitoTestPrelevatoDaFile);
    }

    // CHIUDIAMO IL FILE DATO CHE SERVE UNA SOLA LETTURA (USIAMO, APPUNTO, LE LISTE PER EVITARE DI LEGGERE PIU' VOLTE IL FILE)
    fclose(fileEsitoTest);

    int opzione;
    char dataTest[LEN_DATATEST];

    do {
        system("cls");

        printf("Questo strumento permette di visualizzare lo storico dei Test effettuati.\nIn base alle esigenze, si possono scegliere due modalita' di scansione.\n\n");

        printf("Modalita' di scansione disponibili:\n1. Visualizza lo storico in una data specifica\n2. Visualizza tutto lo storico\n\n3. Ritorna indietro\n\n");
        printf("Scegliere l'opzione: ");
        scanf("%d",&opzione);

        switch(opzione) {
            case 1: {
                printf("\nInserire la data: ");
                scanf("%s",dataTest);

                StampaStoricoDataSpecifica(testaListaRisultati, dataTest);

                printf("\n\n");
                system("pause");

                return;
            }
            case 2: {
                StampaStoricoTutto(testaListaRisultati);

                printf("\n\n");
                system("pause");

                break;
            }
            case 3: {
                return;
            }
            default: {
                printf("\n\nOpzione non esistente.");
                opzione = 0;
                break;
            }
        }
    }
    while(1);
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
                char giornoAppuntamento[LEN_DATATEST];
                char orarioAppuntamento[LEN_GIORNATA];
                char sintomiPaziente[LEN_SINTOMI];

                fileAppuntamentiConfermati = fopen("Dati/AppuntamentiConfermati.txt", "w");

                printf("\nGiorno della prenotazione: ");
                scanf("%s", giornoAppuntamento);

                printf("\nOra della prenotazione (Mattina/Pomeriggio/Sera): ");
                scanf("%s", orarioAppuntamento);

                fprintf(fileAppuntamentiConfermati, "%s %s; %s %s\n", codiceFiscalePaziente, sintomiPaziente, giornoAppuntamento, orarioAppuntamento);

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


        printf("1. Visualizza storico Test effettuati\n2. Visualizza e conferma richieste appuntamenti\n3. Visualizza appuntamenti fissati\n4. Aggiungi appuntamento\n5. Cancella appuntamento\n6. Logout e conferma la giornata");


        printf("\n\nScegliere un'opzione: ");
        scanf("%d",&opzione);

        switch(opzione) {
            case 1: {
                visualizzaStoricoTest();
                break;
            }
            case 2: {
                visualizzaRichiesteTamponi();
                break;
            }
            case 3: {
                visualizzaAppuntamentiConfermati();
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

void ConfermaAppuntamentiRichiesti(AppuntamentiRichiesti arrayAppuntamenti[], int dimensioneArray) {

    FILE *fileAppuntamentiConfermati = fopen("Dati/AppuntamentiConfermati.txt", "a");

    int indice = 0;
    int indiceGiornata = 0;
    char dataGiornaliera[LEN_DATATEST];
    char ultimaDataTest[LEN_DATATEST];

    strcpy(dataGiornaliera, RecuperaDataGiornalieraDaConfigurazione());
    strcpy(ultimaDataTest, AssegnaGiornataTest());

    FILE *fileConfigurazione = fopen("Dati/FileConfigurazione.txt", "r");
    fseek(fileConfigurazione, 72, SEEK_SET);
    fscanf(fileConfigurazione, "%d", &indiceGiornata);
    fclose(fileConfigurazione);

    for(indice = 0; indice < dimensioneArray; indice++) {

        fprintf(fileAppuntamentiConfermati, "%s %s %s %s\n", arrayAppuntamenti[indice].codiceFiscale, arrayAppuntamenti[indice].sintomiPaziente, AssegnaGiornataTest(), AssegnaOrarioTest(indiceGiornata));

        if(indiceGiornata == 5) {
            IncrementaGiornataTest();
            indiceGiornata = 0;
        }
        else
            indiceGiornata++;
    }

    FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");
    fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %s\n", dataGiornaliera);
    fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %s\n", ultimaDataTest);
    fprintf(fileConfigurazioneNuovo, "dataSlot= %d", indiceGiornata);

    fclose(fileConfigurazioneNuovo);
    fclose(fileAppuntamentiConfermati);

}

void visualizzaAppuntamentiConfermati() {

    FILE *fileAppuntamentiConfermati;
    fileAppuntamentiConfermati = fopen("Dati/AppuntamentiConfermati.txt", "r");

    if(fileAppuntamentiConfermati == NULL) {
        printf("\n\nErrore nell'apertura del file AppuntamentiConfermati.txt!\nVerifica che sia presente nella cartella Dati\n\n");
        exit(-1);
    }

    // VERIFICHIAMO PRIMA SE SONO PRESENTI APPUNTAMENTI: SE IL FILE HA DIMENSIONE 0 BYTE, USCIRA' DALLA FUNZIONE STAMPANDO UN ERRORE IN CONSOLE.
    fseek(fileAppuntamentiConfermati, 0L, SEEK_END);
    long int dimensioneFile = ftell(fileAppuntamentiConfermati);

    // CONTROLLIAMO LA DIMENSIONE DEL FILE
    if(dimensioneFile <= 0) {
        printf("\nNon c'e' nessun appuntamento confermato!");
        fclose(fileAppuntamentiConfermati);
        Sleep(4000);
        return;
    }
    else {
        rewind(fileAppuntamentiConfermati);
    }

    char stringaCodFiscaleFile[LEN_CODICEFISCALE];
    char sintomiPaziente[LEN_SINTOMI];
    char dataTest[LEN_DATATEST];
    char ora_giorno[LEN_ORARIOTEST];

    system("cls");
    printf("Appuntamenti confermati:\n\n");

    printf("|=================================================|\n\n");

    while(fscanf(fileAppuntamentiConfermati, "%s %[^;]%*c %s %s", stringaCodFiscaleFile, sintomiPaziente, dataTest, ora_giorno) == 4) {
        printf("CF: %s\tSINTOMI: %s\nDATA: %s\tORARIO: %s\n\n", stringaCodFiscaleFile, sintomiPaziente, dataTest, ora_giorno);
        printf("|=================================================|\n\n");
    }

    fclose(fileAppuntamentiConfermati);

    system("pause");

}

void visualizzaRichiesteTamponi() {

    FILE *fileAppuntamentiRichiesti;
    fileAppuntamentiRichiesti = fopen("Dati/AppuntamentiRichiesti.txt", "r");


    // VERIFICHIAMO PRIMA SE SONO PRESENTI APPUNTAMENTI: SE IL FILE HA DIMENSIONE 0 BYTE, USCIRA' DALLA FUNZIONE STAMPANDO UN ERRORE IN CONSOLE.
    fseek(fileAppuntamentiRichiesti, 0L, SEEK_END);
    long int dimensioneFile = ftell(fileAppuntamentiRichiesti);

    // CONTROLLIAMO LA DIMENSIONE DEL FILE
    if(dimensioneFile <= 0) {
        printf("\nNon c'e' nessun appuntamento richiesto da confermare!");
        fclose(fileAppuntamentiRichiesti);
        Sleep(4000);
        return;
    }
    else {
        rewind(fileAppuntamentiRichiesti);
    }

    system("cls");
    printf("Gli appuntamenti richiesti visualizzati qui saranno automaticamente confermati!\n\n");

    char stringaCodFiscaleFile[LEN_CODICEFISCALE];
    char stringaSintomiFile[LEN_SINTOMI];

    int numeroAppuntamenti = 0;
    int indice = 0;

    while(fscanf(fileAppuntamentiRichiesti, "%s %[^\n]%*c", stringaCodFiscaleFile, stringaSintomiFile) == 2) {
            numeroAppuntamenti++;
    }

    AppuntamentiRichiesti appuntamentiRichiesti[numeroAppuntamenti];
    rewind(fileAppuntamentiRichiesti);

    while(fscanf(fileAppuntamentiRichiesti, "%s %[^\n]%*c", stringaCodFiscaleFile, stringaSintomiFile) == 2) {
            strcpy(appuntamentiRichiesti[indice].codiceFiscale, stringaCodFiscaleFile);
            strcpy(appuntamentiRichiesti[indice].sintomiPaziente, stringaSintomiFile);
            indice++;
    }

    OrdinaArrayAppuntamenti(appuntamentiRichiesti, numeroAppuntamenti);

    StampaArrayAppuntamenti(appuntamentiRichiesti, numeroAppuntamenti-1);

    ConfermaAppuntamentiRichiesti(appuntamentiRichiesti, numeroAppuntamenti);

    fclose(fileAppuntamentiRichiesti);

    IncrementaGiornataTest();

    remove("Dati/AppuntamentiRichiesti.txt");

    fileAppuntamentiRichiesti = fopen("Dati/AppuntamentiRichiesti.txt", "w");
    fclose(fileAppuntamentiRichiesti);

    printf("\n\nGli appuntamenti qui visualizzati sono stati automaticamente confermati!\n\n");

    system("pause");

}

void LogoutChiusuraGiornata() {

    FILE *fileAppuntamentiConfermati = fopen("Dati/AppuntamentiConfermati.txt", "r");

    // VERIFICHIAMO PRIMA SE SONO PRESENTI APPUNTAMENTI: SE IL FILE HA DIMENSIONE 0 BYTE, USCIRA' DALLA FUNZIONE STAMPANDO UN ERRORE IN CONSOLE.
    fseek(fileAppuntamentiConfermati, 0L, SEEK_END);
    long int dimensioneFile = ftell(fileAppuntamentiConfermati);

    // CONTROLLIAMO LA DIMENSIONE DEL FILE
    if(dimensioneFile <= 0) {
        printf("\nLa lista appuntamenti e' vuota.\nSi passa al giorno successivo...n\n");
        fclose(fileAppuntamentiConfermati);
        Sleep(3000);
        return;
    }
    else {
        rewind(fileAppuntamentiConfermati);
    }

    FILE *fileEsitiTest = fopen("Dati/EsitiTest.txt", "a");
    FILE *fileStoricoTest = fopen("Dati/StoricoTest.txt", "a");
    FILE *fileAppuntamentiConfermatiTEMP = fopen("Dati/TEMPAppuntamentiConfermati.txt", "w");

    listaRisultati * testaListaAppuntamenti;
    testaListaAppuntamenti = CreaTestaRisultati();

    char stringaCodFiscaleFile[LEN_CODICEFISCALE];
    char sintomiPaziente[LEN_SINTOMI];
    char dataTest[LEN_DATATEST];
    char ora_giorno[LEN_ORARIOTEST];

    int appuntamentoVerificato = 0;

    while(fscanf(fileAppuntamentiConfermati, "%s %[^;]%*c %s %s", stringaCodFiscaleFile, sintomiPaziente, dataTest, ora_giorno) == 4) {
        if(strcmp(RecuperaDataGiornalieraDaConfigurazione(), dataTest) == 0) {
            InserimentoInCodaAppuntamento(testaListaAppuntamenti, stringaCodFiscaleFile, dataTest, ora_giorno, sintomiPaziente);
            appuntamentoVerificato = 1;
        }
        else {
            fprintf(fileAppuntamentiConfermatiTEMP, "%s %s; %s %s\n", stringaCodFiscaleFile, sintomiPaziente, dataTest, ora_giorno);
        }
    }

    fclose(fileAppuntamentiConfermati);
    fclose(fileAppuntamentiConfermatiTEMP);

    remove("Dati/AppuntamentiConfermati.txt");
    rename("Dati/TEMPAppuntamentiConfermati.txt", "Dati/AppuntamentiConfermati.txt");

    if(appuntamentoVerificato == 1) {
        AssegnaEsito(testaListaAppuntamenti);
        ScriviSuFileEsito(testaListaAppuntamenti, fileStoricoTest, fileEsitiTest);
        printf("\nSono stati effettuati tutti gli appuntamenti di oggi: %s\n", RecuperaDataGiornalieraDaConfigurazione());
    }
    else {
        printf("\nNon e' stato fatto nessun tampone oggi %s!\n", RecuperaDataGiornalieraDaConfigurazione());
    }

    fclose(fileEsitiTest);
    fclose(fileStoricoTest);

    printf("\n\n");

    system("pause");
}
