#include "DefinizioniGlobali.h"

// STRUTTURA DATI PER VISUALIZZARE I TEST EFFETTUATI
typedef struct nodoRisultatiTest {
    char codiceFiscale[LEN_CODICEFISCALE];
    char dataTest[LEN_DATATEST];
    char orario[LEN_ORARIOTEST];
    char sintomi[LEN_SINTOMI];
    char esito[LEN_ESITO];
    struct nodoRisultatiTest *next;
} nodoRisultati;

// STRUTTURA DATI PER I RISULTATI
typedef struct listaRisultatiTest {
    nodoRisultati *next;
} listaRisultati;

// STRUTTURA DATI (USATA COME ARRAY) PER ORDINARE I PAZIENTI SINTOMATICI E ASINTOMATICI
typedef struct arrayAppuntamentiRichiesti {

    char codiceFiscale[LEN_CODICEFISCALE];
    char sintomiPaziente[LEN_SINTOMI];

} AppuntamentiRichiesti;

// CREA UN NODO PER I RISULTATI - IN INPUT CODICE FISCALE, DATA DEL TEST, ORARIO, ESITO
nodoRisultati *CreaNodoRisultati(char[], char[], char[], char[]);

// CREA LA TESTA PER I RISULTATI
listaRisultati *CreaTestaRisultati();

// INSERISCE IN CODA ALLA LISTA I RISULTATI - IN INPUT: TESTA DELLA LISTA, CODICE FISCALE, DATA DEL TEST, ORARIO, ESITO
void InserimentoInCodaRisultati(listaRisultati *Testa, char[], char[], char[], char[]);

// STAMPA A VIDEO I TEST EFFETTUATI IN UNA DATA SPECIFICA - IN INPUT: TESTA DELLA LISTA, DATA DEL TEST
void StampaStoricoDataSpecifica(listaRisultati *Testa, char[]);

// STAMPA A VIDEO TUTTA LA LISTA, PRECEDENTEMENTE CARICATA CON LE INFORMAZIONI DAL FILE "STORICOTEST.TXT"
void StampaStoricoTutto(listaRisultati *Testa);

// ORDINA L'ARRAY DEGLI APPUNTAMENTI IN BASE AI SINTOMATICI E ASINTOMATICI
void OrdinaArrayAppuntamenti(AppuntamentiRichiesti arrayAppuntamenti[], int dimensioneArray);

// STAMPA A VIDEO GLI APPUNTAMENTI SALVATI IN "APPUNTAMENTICONFERMATI.TXT"
void StampaArrayAppuntamenti(AppuntamentiRichiesti arrayAppuntamenti[], int dimensioneArray);

// INSERISCE IN CODA GLI APPUNTAMENTI DOVE POI ASSEGNARE L'ESITO - IN INPUT: TESTA DELLA LISTA, CODICE FISCALE, NOME, COGNOME, SINTOMI
void InserimentoInCodaAppuntamento(listaRisultati *Testa, char[], char[], char[], char[]);

// ASSEGNA L'ESITO AL NODO ATTUALE
void AssegnaEsito(listaRisultati *Testa);

// SCRIVE SU DUE FILE L'ESITO DEL TAMPONE - IN INPUT: TESTA DELLA LISTA CON GLI ESITI, IL PUNTATORE AL FILE STORICOTEST, IL PUNTATORE AL FILE ESITI DA VISUALIZZARE
void ScriviSuFileEsito(listaRisultati *Testa, FILE *fileOutputStorico, FILE *fileOutputEsito);
