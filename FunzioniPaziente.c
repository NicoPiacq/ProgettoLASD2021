#include "HeaderPaziente.h"

// QUESTE TRE FUNZIONI SONO PURAMENTE GRAFICHE E SERVONO PER GUIDARE L'UTENTE NELLA REGISTRAZIONE DEI DATI (E A NON SPORCARE LA CONSOLE)
void mostraMessaggioRegistrazione1() {
    printf("Benvenuto nella pagina di registrazione al Laboratorio di Analisi 'San Nicola' per Tamponi Molecolari COVID-19.\n");
    printf("Ti aiuteremo a registrare le tue informazioni per proseguire nella tua pagina principale.\n");
    printf("\n");
}

void mostraMessaggioRegistrazione2(char codFiscaleMessaggio[]) {
    printf("Benvenuto nella pagina di registrazione al Laboratorio di Analisi 'San Nicola' per Tamponi Molecolari COVID-19.\n");
    printf("Ti aiuteremo a registrare le tue informazioni per proseguire nella tua pagina principale.\n");
    printf("\n");

    printf("Inserire il Codice Fiscale: %s\n\n",codFiscaleMessaggio);
}

void mostraMessaggioRegistrazione3(char codFiscaleMessaggio[], char nomeMessaggio[]) {
    printf("Benvenuto nella pagina di registrazione al Laboratorio di Analisi 'San Nicola' per Tamponi Molecolari COVID-19.\n");
    printf("Ti aiuteremo a registrare le tue informazioni per proseguire nella tua pagina principale.\n");
    printf("\n");

    printf("Inserire il Codice Fiscale: %s\n\n",codFiscaleMessaggio);

    printf("Inserire il Nome: %s\n\n",nomeMessaggio);
}


/* QUI C'E' IL CORPO PRINCIPALE PER LA REGISTRAZIONE DELL'UTENTE NEL FILE ListaUtenti.txt

   LA FUNZIONE INNANZITUTTO APRE IL FILE ListaUtenti.txt
   SUCCESSIVAMENTE ALL'UTENTE VIENE RICHIESTO DI INSERIRE RISPETTIVAMENTE: Codice Fiscale, Nome, Cognome
   LA PASSWORD E' GENERATA CASUALMENTE DALLA FUNZIONE "generaCodiceAccesso" E VIENE DATA ALL'UTENTE

   ALLA FINE, VIENE REGISTRATO L'UTENTE SUL FILE E PUO' PROSEGUIRE NELLA SCHERMATA PRINCIPALE.
*/
void registrazionePaziente() {

    struct paziente registrazioneDatiPaziente;

    FILE *fileRegistrazione;

    // Apriamo il file in modalità Solo Lettura
    fileRegistrazione = fopen("Dati/ListaUtenti.txt", "r");

    // Sono variabili temporanee per prelevare i righi nel file e verificare se un codice fiscale è già stato usato
    char stringaPrelevata[LEN_CODICEFISCALE];
    char stringaPrelevata2[LEN_NOME];
    char stringaPrelevata3[LEN_COGNOME];
    int stringaVerificata = 0;

    // Accertiamoci che il File esista, altrimenti va in errore
    if(fileRegistrazione == NULL) {
        printf("ERRORE! Non riesco a trovare il file dei dati utente!");
        exit(-1);
    }

    // Puliamo la console e mostriamo il primo messaggio di Registrazione
    system("cls");
    mostraMessaggioRegistrazione1();

    // Chiediamo all'utente di inserire il Codice Fiscale e verifichiamo che sia esattamente di 16 caratteri, altrimenti richiede nuovamente l'inserimento
    do {
        // La funzione rewind riporta il puntatore di lettura del file alla prima linea
        rewind(fileRegistrazione);
        printf("Inserire il Codice Fiscale: ");
        scanf("%s",registrazioneDatiPaziente.codiceFiscale);

        // Verifichiamo prima la lunghezza del codice fiscale
        if(strlen(registrazioneDatiPaziente.codiceFiscale) != 16) {
            printf("Il Codice Fiscale inserito e' errato.");
            Sleep(3000);
            system("cls");
            mostraMessaggioRegistrazione1();
            continue;
        }

        // Verifichiamo se il codice fiscale inserito è già presente nella lista degli utenti
        while(fscanf(fileRegistrazione, "%s %s %s\n",stringaPrelevata,stringaPrelevata2,stringaPrelevata3) == 3) {
            if(strcmp(stringaPrelevata, registrazioneDatiPaziente.codiceFiscale) == 0) {
                stringaVerificata = 0;
                printf("Il Codice Fiscale inserito e' gia' registrato.");
                Sleep(3000);
                system("cls");
                mostraMessaggioRegistrazione1();
                break;
            }
            else {
                stringaVerificata = 1;
            }
        }
    }
    while( (strlen(registrazioneDatiPaziente.codiceFiscale) == 16) && (stringaVerificata == 0) );

    // Puliamo la console e mostriamo il secondo messaggio di Registrazione
    system("cls");
    mostraMessaggioRegistrazione2(registrazioneDatiPaziente.codiceFiscale);

    // Chiediamo all'utente di inserire il nome e verifichiamo che non superi i 12 caratteri, altrimenti richiede nuovamente l'inserimento
    do {
        printf("Inserire il Nome: ");
        scanf("%s",registrazioneDatiPaziente.nome);

        if(strlen(registrazioneDatiPaziente.nome) > 12) {
            printf("Il nome supera il limite di caratteri.");
            Sleep(3000);
            system("cls");
            mostraMessaggioRegistrazione2(registrazioneDatiPaziente.codiceFiscale);
        }
    }
    while(strlen(registrazioneDatiPaziente.nome) > 12);

    // Puliamo la console e mostriamo il terzo e ultimo messaggio di Registrazione
    system("cls");
    mostraMessaggioRegistrazione3(registrazioneDatiPaziente.codiceFiscale, registrazioneDatiPaziente.nome);

    // Chiediamo all'utente di inserire il cognome e verifichiamo che non superi i 12 caratteri, altrimenti richiede nuovamente l'inserimento
    do {
        printf("Inserire il Cognome: ");
        scanf("%s",registrazioneDatiPaziente.cognome);

        if(strlen(registrazioneDatiPaziente.cognome) > 12) {
            printf("Il cognome supera il limite di caratteri.");
            Sleep(3000);
            system("cls");
            mostraMessaggioRegistrazione3(registrazioneDatiPaziente.codiceFiscale, registrazioneDatiPaziente.nome);
        }
    }
    while(strlen(registrazioneDatiPaziente.cognome) > 12);

    // Chiudiamo il file dalla modalità solo lettura
    fclose(fileRegistrazione);

    // Apriamo nuovamente il file in modalità Append (immediatamente prima dell'EOF)
    fileRegistrazione = fopen("Dati/ListaUtenti.txt", "a");

    // Scriviamo sul file
    fprintf(fileRegistrazione, "%s %s %s\n",registrazioneDatiPaziente.codiceFiscale, registrazioneDatiPaziente.nome, registrazioneDatiPaziente.cognome);

    // Chiudiamo il file
    fclose(fileRegistrazione);

    // Avvisiamo l'utente che la registrazione è completata e che può proseguire nella pagina principale
    printf("\n\n\nREGISTRAZIONE COMPLETATA!\nRicorda di segnarti questo codice di accesso: NULL\n\n\n");
    printf("Premi INVIO per ritornare al menu' principale...");

    getchar();
}



int controllaSeGiaPrenotato(char codFiscale[]) {

    FILE *fileAppuntamentiRichiesti;

    fileAppuntamentiRichiesti = fopen("Dati/AppuntamentiRichiesti.txt", "r");

    if(fileAppuntamentiRichiesti == NULL) {
        printf("ERRORE! Non riesco a trovare il file degli appuntamenti richiesti!");
        exit(-1);
    }

    char stringaCodFiscaleFile[LEN_CODICEFISCALE];
    char stringaSintomiFile[LEN_SINTOMI];

    while(fscanf(fileAppuntamentiRichiesti, "%s %[^\n]%*c",stringaCodFiscaleFile, stringaSintomiFile) == 2) {

        if(strcmp(stringaCodFiscaleFile, codFiscale) == 0) {
            fclose(fileAppuntamentiRichiesti);
            return 1;
        }
    }

    fclose(fileAppuntamentiRichiesti);

    return 0;
}

int controllaSeGiaConfermato(char codFiscale[]) {

    FILE *fileAppuntamentoConfermato;

    char stringaCodFiscaleFile[LEN_CODICEFISCALE];
    char dataTest[LEN_DATATEST];
    char ora_giorno[LEN_GIORNATA];
    char sintomiPaziente[LEN_SINTOMI];

    fileAppuntamentoConfermato = fopen("Dati/AppuntamentiConfermati.txt", "r");

    if(fileAppuntamentoConfermato == NULL) {
        printf("ERRORE! Non riesco a trovare il file degli appuntamenti confermati!\n\n");
        exit(-1);
    }

    while(fscanf(fileAppuntamentoConfermato, "%s %[^;]%*c %s %s", stringaCodFiscaleFile, sintomiPaziente, dataTest, ora_giorno) == 4) {
        if(strcmp(stringaCodFiscaleFile, codFiscale) == 0) {
            fclose(fileAppuntamentoConfermato);
            return 2;
        }
    }

    if(controllaSeGiaPrenotato(codFiscale) == 0) {
        fclose(fileAppuntamentoConfermato);
        return 0;
    } else {
        fclose(fileAppuntamentoConfermato);
        return 1;
    }


    rewind(fileAppuntamentoConfermato);
    fseek(fileAppuntamentoConfermato, 0L, SEEK_END);
    long int dimensioneFile = ftell(fileAppuntamentoConfermato);

    if(dimensioneFile <= 0) {
        fclose(fileAppuntamentoConfermato);
        return 0;
    }

    fclose(fileAppuntamentoConfermato);
    return 3;
}


void visualizzaStatoAppuntamento(char codFiscale[]) {

    FILE *fileAppuntamentiConfermati = fopen("Dati/AppuntamentiConfermati.txt", "r");

    char stringaCodFiscaleFile[LEN_CODICEFISCALE];
    char dataTest[LEN_DATATEST];
    char ora_giorno[LEN_GIORNATA];
    char sintomiPaziente[LEN_SINTOMI];

    int statoRichiesta = controllaSeGiaConfermato(codFiscale);

    switch(statoRichiesta) {
        case 0: {
            printf("\nNon hai richiesto nessun tampone.\nLa preghiamo di usare la funzione apposita per farlo.\n");
            Sleep(4000);
            return;
        }
        case 1: {
            printf("\nLa tua richiesta non e' stata ancora accettata.\nRiprova piu' tardi.\n");
            Sleep(4000);
            return;
        }
        case 2: {
            while(fscanf(fileAppuntamentiConfermati, "%s %[^;]%*c %s %s", stringaCodFiscaleFile, sintomiPaziente, dataTest, ora_giorno) == 4) {
                if(strcmp(stringaCodFiscaleFile, codFiscale) == 0) {
                    printf("\nAppuntamento confermato!\nDevi andare il Giorno %s di %s\n\n", dataTest, ora_giorno);
                    fclose(fileAppuntamentiConfermati);
                    system("pause");
                    return;
                }
            }
        }
    }
}


void aggiornaStatoRichiesta(char codFiscale[]) {

    switch(controllaSeGiaConfermato(codFiscale)) {
        case 0: {
            printf("Non effettuato\n\n");
            break;
        }
        case 1: {
            printf("In conferma\n\n");
            break;
        }
        case 2: {
            printf("Confermato\n\n");
            break;
        }
        default: {
            printf("Errore\n\n");
            break;
        }
    }
}

void cancellaRichiestaTampone(char codFiscale[]) {

    switch(controllaSeGiaConfermato(codFiscale)) {
        case 0: {
            printf("\nNessuna richiesta da cancellare.\nDevi prima crearne una.");
            Sleep(4500);
            return;
        }
        case 1: {
            break;
        }
        case 2: {
            printf("\nImpossibile eliminare.\nLa tua richiesta e' stata gia' accettata nel sistema!\n\nSe vuoi cancellare il tuo appuntamento, contatta un dipendente del laboratorio.\n\n\n");
            system("pause");
            return;
        }
        default: {
            printf("\nErrore sconosciuto.\nContattare l'assistenza.");
            Sleep(4000);
            return;
        }
    }

    char opzione;

    do {
        system("cls");

        printf("Eliminando la tua richiesta, dovrai rifarla nuovamente per ottenere un appuntamento al Laboratorio.\n\nPer procedere:\n\nDigita S e premi INVIO per cancellare la richiesta;\nDigita N e premi INVIO per tornare indietro.\n");
        printf("\nScelta: ");
        scanf(" %s",&opzione);

        switch(opzione) {
            case 'S': {
                printf("\n\nOK.\nCancellazione in corso...\n");

                FILE *fileNuovoRichieste;
                FILE *fileVecchioRichieste;

                char stringaCodFiscaleFile[LEN_CODICEFISCALE];
                char stringaSintomiFile[LEN_SINTOMI];

                fileVecchioRichieste = fopen("Dati/AppuntamentiRichiesti.txt", "r");
                if(fileVecchioRichieste == NULL) {
                    printf("\nERRORE! Non riesco ad aprire il file delle richieste (OLD)");
                    exit(-1);
                }

                fileNuovoRichieste = fopen("Dati/TEMP_AppuntamentiRichiesti.txt", "w");
                if(fileNuovoRichieste == NULL) {
                    printf("\nERRORE! Non riesco ad aprire il file delle richieste (NEW)");
                    exit(-1);
                }

                while(fscanf(fileVecchioRichieste, "%s %[^\n]%*c", stringaCodFiscaleFile, stringaSintomiFile) == 2) {

                    if(strcmp(stringaCodFiscaleFile, codFiscale) == 0) {
                        continue;
                    }
                    else {
                        fprintf(fileNuovoRichieste, "%s %s\n", stringaCodFiscaleFile, stringaSintomiFile);
                    }

                }

                fclose(fileNuovoRichieste);
                fclose(fileVecchioRichieste);

                int statoRimozioneFile = remove("Dati/AppuntamentiRichiesti.txt");
                int statoRinominaFile = rename("Dati/TEMP_AppuntamentiRichiesti.txt", "Dati/AppuntamentiRichiesti.txt");

                if(statoRimozioneFile == 0 && statoRinominaFile == 0) {
                    printf("\n\nCancellazione completata!\nTornerai alla pagina principale in 3 secondi...");
                    Sleep(3000);
                    return;
                }
                else {
                    printf("\n\nErrore nella cancellazione (%d)\nContattare l'assistenza del Laboratorio.\n\nINFO: %s\n\n", errno, strerror(errno));
                    system("pause");
                    exit(-1);
                }
            }
            case 'N': {
                printf("\n\nTornerai alla pagina principale in 3 secondi...");
                Sleep(3000);
                return;
            }
            default: {
                printf("\n\nOpzione errata. Riprova con S o N e premi INVIO");
                Sleep(4000);
                break;
            }
        }
    }
    while(1);
}

void mostraPaginaPrincipale(struct paziente datiPazienteHomepage) {

    int opzione = 0;

    do {
        system("cls");

        printf("Benvenuto Pagina Principale del Laboratorio di Analisi 'San Nicola'\n\n");
        printf("*************DATI UTENTE*************\n\n\t%s %s\n Codice Fiscale: %s\n Stato richiesta: ", datiPazienteHomepage.nome, datiPazienteHomepage.cognome, datiPazienteHomepage.codiceFiscale);
        aggiornaStatoRichiesta(datiPazienteHomepage.codiceFiscale);
        printf("*************************************");
        printf("\n\nEcco cosa puoi fare: \n\n");

        if(datiPazienteHomepage.haEsito == 1) {
            printf("1. Prenota un tampone\n2. Visualizza lo stato della richiesta di un tampone\n3. Cancella la richiesta\n4. Visualizza esito tampone\n5. Esegui il logout");
        }
        else {
            printf("1. Prenota un tampone\n2. Visualizza lo stato della richiesta di un tampone\n3. Cancella la richiesta\n4. Esegui il logout");
        }


        printf("\n\nScegliere un'opzione: ");
        scanf("%d",&opzione);

        switch(opzione) {
            case 1: {
                int statoRichiesta = controllaSeGiaConfermato(datiPazienteHomepage.codiceFiscale);

                if (statoRichiesta == 0) {
                    prenotazioneTampone(datiPazienteHomepage.codiceFiscale);
                    break;
                }
                else if (statoRichiesta == 1) {
                    printf("\nHai gia' effettuato una richiesta di prenotazione!\nVisualizza o cancella la richiesta dalla pagina principale.");
                    Sleep(4500);
                    break;
                }
                else if (statoRichiesta == 2) {
                    printf("\nLa tua richiesta e' stata accettata!\nVisualizza la data e l'ora dell'appuntamento scegliendo l'opzione 2.");
                    Sleep(4500);
                    break;
                }
            }
            case 2: {
                visualizzaStatoAppuntamento(datiPazienteHomepage.codiceFiscale);
                break;
            }
            case 3: {
                cancellaRichiestaTampone(datiPazienteHomepage.codiceFiscale);
                break;
            }
            case 4: {
                if(datiPazienteHomepage.haEsito == 1) {
                    printf("\nI tamponi non sono ancora disponibili...");
                    Sleep(3000);
                }
                else {
                    return;
                }
                break;
            }
            case 5: {
                if(datiPazienteHomepage.haEsito == 0) {
                    printf("Hai scelto un'opzione non disponibile");
                    Sleep(3000);
                    opzione = 0;
                }
                else {
                    return;
                }
                break;
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




void impostaTitoloConsoleConCF(char codice[]) {
    char titolo[LEN_TITOLOCONSOLE];

    if(strlen(codice) > 10) {
        strcpy(titolo, "Laboratorio di Analisi - Accesso effettuato come: ");
        strcat(titolo, codice);
    }
    else {
        strcpy(titolo, "Laboratorio di Analisi - Accesso effettuato come: DIP-");
        strcat(titolo, codice);
    }

    SetConsoleTitle(titolo);
}

struct paziente accediComePaziente() {

    FILE *fileListaUtenti;

    char accessoCodiceFiscale[LEN_CODICEFISCALE];
    char accessoPassword[LEN_PASSWORD];

    struct paziente accessoDatiPaziente;

    char codiceFiscalePrelevatoDaFile[LEN_CODICEFISCALE];
    char nomePrelevatoDaFile[LEN_NOME];
    char cognomePrelevatoDaFile[LEN_COGNOME];
    char passwordPrelevatoDaFile[LEN_PASSWORD];

    do {
        system("cls");

        printf("Accesso alla Pagina Principale del Laboratorio di Analisi Tamponi Molecolari 'San Nicola'\n\n");
        printf("Inserisci il Codice Fiscale: ");
        scanf("%s",accessoCodiceFiscale);

        printf("\nInserisci la password: ");
        scanf("%s",accessoPassword);

        fileListaUtenti = fopen("Dati/ListaUtenti.txt", "r");

        while(fscanf(fileListaUtenti, "%s %s %s %s\n", codiceFiscalePrelevatoDaFile, nomePrelevatoDaFile, cognomePrelevatoDaFile, passwordPrelevatoDaFile) == 4) {
            if(strcmp(accessoCodiceFiscale, codiceFiscalePrelevatoDaFile) == 0 && strcmp(accessoPassword, passwordPrelevatoDaFile) == 0) {
                strcpy(accessoDatiPaziente.codiceFiscale, codiceFiscalePrelevatoDaFile);
                strcpy(accessoDatiPaziente.nome, nomePrelevatoDaFile);
                strcpy(accessoDatiPaziente.cognome, cognomePrelevatoDaFile);

                accessoDatiPaziente.haEsito = 0;

                printf("\nAccesso effettuato!\nAdesso andrai alla pagina principale...");
                fclose(fileListaUtenti);

                Sleep(3000);

                impostaTitoloConsoleConCF(accessoDatiPaziente.codiceFiscale);
                return accessoDatiPaziente;
            }
        }

        printf("\nI dati inseriti non sono corretti!\n");
        rewind(fileListaUtenti);
        system("pause");
    }
    while(1);
}




void mostraMessaggioPrenotazione1(char codFiscale[]) {
    system("cls");
    printf("Puoi prenotare un tampone da qui, devi specificare solo se presenti dei sintomi.\n");
    printf("Prima di proseguire, confermi che %s ",codFiscale);
}

void mostraMessaggioPrenotazione2(char codFiscale[]) {
    system("cls");
    printf("Puoi prenotare un tampone da qui, devi specificare solo se presenti dei sintomi.\n");
    printf("Prima di proseguire, confermi che %s e' il tuo Codice Fiscale? (S/N): S",codFiscale);
}

void prenotazioneTampone(char codFiscale[]) {

    char sintomiPaziente[LEN_SINTOMI];
    char opzione;

    FILE *fileAppuntamentiRichiesti;

    do {

        mostraMessaggioPrenotazione1(codFiscale);
        printf("e' il tuo Codice Fiscale? (S/N): ");
        scanf(" %c",&opzione);

        switch(opzione) {

            case 'N': {
                printf("\n\nEsegui il logout dalla pagina principale,\ned effettua l'accesso con il Codice Fiscale corretto.");
                Sleep(4000);
                return;
            }

            case 'S': {

                fileAppuntamentiRichiesti = fopen("Dati/AppuntamentiRichiesti.txt", "a");
                if(fileAppuntamentiRichiesti == NULL) {
                    printf("ERRORE NELL'APERTURA DEL FILE!");
                    exit(-1);
                }

                do {

                    mostraMessaggioPrenotazione2(codFiscale);

                    printf("\nHai dei sintomi? (S/N): ");
                    scanf(" %c",&opzione);

                    switch(opzione) {

                        case 'S': {
                            printf("\nChe sintomi hai?:\n");
                            scanf(" %[^\n]%*c",sintomiPaziente);
                            printf("\n");
                            fprintf(fileAppuntamentiRichiesti, "%s %s;\n",codFiscale, sintomiPaziente);
                            break;
                        }

                        case 'N': {
                            printf("\nSarai registrato come asintomatico!\nTieni conto che gli asintomatici hanno meno priorita'.");
                            fprintf(fileAppuntamentiRichiesti, "%s Asintomatico;\n", codFiscale);
                            break;
                        }

                        default: {
                            printf("\nOpzione errata.");
                            Sleep(2000);
                            continue;
                        }

                    }

                    fclose(fileAppuntamentiRichiesti);
                    printf("\n\nAppuntamento richiesto con successo.\nPotrai visualizzare la richiesta effettuata tramite la pagina principale oppure,\ncancellare la richiesta prima che questa viene confermata.\n\n");
                    Sleep(3000);

                    system("pause");
                    return;
                }
                while(1);
            }
        default: {
            printf("Opzione errata.");
            Sleep(3000);
            break;
            }
        }
    }
    while(1);
}
