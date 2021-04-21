#include "gestioneListe.h"

nodoRisultati *CreaNodoRisultati(char codFiscale[], char dataTest[], char orarioTest[], char esitoTest[]) {

	nodoRisultati * tmp = (nodoRisultati *) malloc(sizeof(nodoRisultati));

	// VERIFICHIAMO CHE TMP E' STATO CORRETTAMENTE CREATO
	if (!tmp)
		return NULL; // TMP NON CREATO CORRETTAMENTE.
	else {
		tmp->next = NULL;
		strcpy(tmp->codiceFiscale, codFiscale);
		strcpy(tmp->dataTest, dataTest);
		strcpy(tmp->orario, orarioTest);
		strcpy(tmp->esito, esitoTest);
	}

	return tmp;
}

listaRisultati *CreaTestaRisultati() {

	listaRisultati * TestaTemp = NULL;
	TestaTemp = (listaRisultati *)malloc(sizeof (listaRisultati));

	if(TestaTemp) {
		TestaTemp->next = NULL;
	}
	else
		return NULL;

	return TestaTemp;

}

void InserimentoInCodaRisultati(listaRisultati *Testa, char codFiscale[], char dataTest[], char orarioTest[], char esitoTest[]) {
	nodoRisultati *temp = NULL;
	nodoRisultati *Ricerca = Testa->next;

	// Verifichiamo se la lista è vuota
	if (!Testa->next) {
		temp = CreaNodoRisultati(codFiscale, dataTest, orarioTest, esitoTest);

		if(temp) {
			Testa->next = temp;
			return;
		}
	}
	// Se non lo è, aggiungiamo in coda il risultato del test scansionato dal file.
	else {
		temp = CreaNodoRisultati(codFiscale, dataTest, orarioTest, esitoTest);

		while(Ricerca->next) {
			Ricerca = Ricerca->next;
		}

		Ricerca->next = temp;
	}

	return;
}

void StampaStoricoDataSpecifica(listaRisultati *Testa, char data[]) {
    system("cls");
    printf("Storico test: \n\n");
	nodoRisultati * Ricerca = Testa->next;

	while(Ricerca != NULL && Ricerca->next != NULL) {
        if(strcmp(data, Ricerca->dataTest) == 0) {
            printf("| ====================== %s ====================== |\n|\n", Ricerca->dataTest);
            printf("| \t\tCF: %-38s |\n| \t\tORARIO: %-34s |\n| \t\tESITO: %-35s |\n|\n", Ricerca->codiceFiscale, Ricerca->orario, Ricerca->esito);
        }
        Ricerca = Ricerca->next;
	}

	if(Ricerca->next == NULL && strcmp(data, Ricerca->dataTest) == 0) {
        printf("| ====================== %s ====================== |\n|\n", Ricerca->dataTest);
		printf("| \t\tCF: %-38s |\n| \t\tORARIO: %-34s |\n| \t\tESITO: %-35s |\n|\n", Ricerca->codiceFiscale, Ricerca->orario, Ricerca->esito);
        printf("| ======================================================== |\n");
	}
	else {
        printf("| ======================================================== |\n");
	}

	return;
}

void StampaStoricoTutto(listaRisultati *Testa) {
    system("cls");
    printf("Storico test: \n\n");
	nodoRisultati * Ricerca = Testa->next;

	while(Ricerca != NULL && Ricerca->next != NULL) {
        printf("| ====================== %s ====================== |\n|\n", Ricerca->dataTest);
        printf("| \t\tCF: %-38s |\n| \t\tORARIO: %-34s |\n| \t\tESITO: %-35s |\n|\n", Ricerca->codiceFiscale, Ricerca->orario, Ricerca->esito);
        Ricerca = Ricerca->next;
	}

	if(Ricerca->next == NULL) {
        printf("| ====================== %s ====================== |\n|\n", Ricerca->dataTest);
		printf("| \t\tCF: %-38s |\n| \t\tORARIO: %-34s |\n| \t\tESITO: %-35s |\n|\n", Ricerca->codiceFiscale, Ricerca->orario, Ricerca->esito);
        printf("| ======================================================== |\n");
	}

	return;
}


void OrdinaArraySintomatici(AppuntamentiRichiesti arrayTemp[], int dimensioneArray) {

    int lunghezzaSintomiTemp;
    AppuntamentiRichiesti appuntamentoTemp;
    int secondoIndice = 0;

    if(dimensioneArray > 1) {

        OrdinaArraySintomatici(arrayTemp, dimensioneArray-1);

        lunghezzaSintomiTemp = strlen(arrayTemp[dimensioneArray-1].sintomiPaziente);
        appuntamentoTemp = arrayTemp[dimensioneArray-1];

        secondoIndice = dimensioneArray-2;

        while (secondoIndice >= 0 && strlen(arrayTemp[secondoIndice].sintomiPaziente) < lunghezzaSintomiTemp) {
            arrayTemp[secondoIndice + 1] = arrayTemp[secondoIndice];
            secondoIndice = secondoIndice-1;
        }

        arrayTemp[secondoIndice + 1] = appuntamentoTemp;
    }

    return;

}

void OrdinaArrayAppuntamenti(AppuntamentiRichiesti arrayAppuntamenti[], int dimensioneArray) {

    int numeroAsintomatici = 0;
    int numeroSintomatici = 0;
    int indice1 = 0;
    int indice2 = 0;

    for(indice1 = 0; indice1 < dimensioneArray; indice1++) {
        if(strcmp(arrayAppuntamenti[indice1].sintomiPaziente, "Asintomatico") == 0) {
            numeroAsintomatici++;
        }
    }

    numeroSintomatici = dimensioneArray - numeroAsintomatici;

    AppuntamentiRichiesti arrayAsintomatici[numeroAsintomatici];
    AppuntamentiRichiesti arraySintomatici[numeroSintomatici];

    indice1 = 0;

    for(indice2 = 0; indice2 < dimensioneArray; indice2++) {
        if(strcmp(arrayAppuntamenti[indice2].sintomiPaziente, "Asintomatico") == 0) {
            arrayAsintomatici[indice1] = arrayAppuntamenti[indice2];
            indice1++;
        }
    }

    indice1 = 0;

    for(indice2 = 0; indice2 < dimensioneArray; indice2++) {
        if(strcmp(arrayAppuntamenti[indice2].sintomiPaziente, "Asintomatico") != 0) {
            arraySintomatici[indice1] = arrayAppuntamenti[indice2];
            indice1++;
        }
    }

    OrdinaArraySintomatici(arraySintomatici, dimensioneArray-numeroAsintomatici);

    for(indice1 = 0; indice1 < numeroSintomatici; indice1++) {
        arrayAppuntamenti[indice1] = arraySintomatici[indice1];
    }

    indice2 = indice1;
    indice1 = 0;

    for(indice2 = indice2; indice2 < dimensioneArray; indice2++) {
        arrayAppuntamenti[indice2] = arrayAsintomatici[indice1];
        indice1++;
    }
}
