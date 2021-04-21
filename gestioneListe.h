#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "DefinizioniGlobali.h"


typedef struct nodoRisultatiTest {
    char codiceFiscale[LEN_CODICEFISCALE];
    char dataTest[LEN_DATATEST];
    char orario[LEN_ORARIOTEST];
    char esito[LEN_ESITO];
    struct nodoRisultatiTest *next;
} nodoRisultati;

typedef struct listaRisultatiTest {
    nodoRisultati *next;
} listaRisultati;


typedef struct arrayAppuntamentiRichiesti {

    char codiceFiscale[LEN_CODICEFISCALE];
    char sintomiPaziente[LEN_SINTOMI];

} AppuntamentiRichiesti;

nodoRisultati *CreaNodoRisultati(char[], char[], char[], char[]);
listaRisultati *CreaTestaRisultati();

void InserimentoInCodaRisultati(listaRisultati *Testa, char[], char[], char[], char[]);
void StampaStoricoDataSpecifica(listaRisultati *Testa, char[]);
void StampaStoricoTutto(listaRisultati *Testa);


void OrdinaArrayAppuntamenti(AppuntamentiRichiesti arrayAppuntamenti[], int dimensioneArray);

void StampaArrayAppuntamenti(AppuntamentiRichiesti arrayAppuntamenti[], int dimensioneArray);
