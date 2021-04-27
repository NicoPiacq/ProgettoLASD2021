#include "gestioneDate.h"

char* AssegnaOrarioTest(int n) {

    switch(n) {
        case 0:
        case 1:
            return "Mattina";
        case 2:
        case 3:
            return "Pomeriggio";
        case 4:
        case 5:
            return "Sera";
    }

    return "Mattina";
}

char* AssegnaGiornataTest() {

    char * data;
    data = malloc(sizeof(char) * LEN_DATATEST);

    FILE *fileConfigurazione = fopen("Dati/FileConfigurazione.txt", "r");

    fseek(fileConfigurazione, 51, SEEK_SET);
    fscanf(fileConfigurazione, "%s", data);

    fclose(fileConfigurazione);
    return data;
}

void IncrementaGiornataTest() {

    char dataAttuale[5];
    char dataGiornaliera[LEN_DATATEST];
    int giorno, mese, anno;
    int ultimoSlot;

    FILE *fileConfigurazione = fopen("Dati/FileConfigurazione.txt", "r");

    fseek(fileConfigurazione, 51, SEEK_SET);
    fscanf(fileConfigurazione, "%[^/]%*c", dataAttuale);
    giorno = atoi(dataAttuale);

    fseek(fileConfigurazione, 54, SEEK_SET);
    fscanf(fileConfigurazione, "%[^/]%*c", dataAttuale);
    mese = atoi(dataAttuale);

    fseek(fileConfigurazione, 57, SEEK_SET);
    fscanf(fileConfigurazione, "%[^/n]%*c", dataAttuale);
    anno = atoi(dataAttuale);

    fseek(fileConfigurazione, 17, SEEK_SET);
    fscanf(fileConfigurazione, "%s", dataGiornaliera);

    fseek(fileConfigurazione, 72, SEEK_SET);
    fscanf(fileConfigurazione, "%d", &ultimoSlot);

    fclose(fileConfigurazione);

    if(giorno == 30 && (mese == 11 || mese == 4 || mese == 6 || mese == 9) ) {
        giorno = 1;
        mese++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);


        fclose(fileConfigurazioneNuovo);
        return;
    }

    if(giorno == 31 && (mese == 1 || mese == 3 || mese == 5 || mese == 7 || mese == 10) ) {
        giorno = 1;
        mese++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

        fclose(fileConfigurazioneNuovo);
        return;
    }

    if(giorno == 31 && mese == 12) {
        giorno = 1;
        mese = 1;
        anno++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

        fclose(fileConfigurazioneNuovo);
        return;
    }

    if(giorno == 28 && mese == 2) {
        giorno = 1;
        mese++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

        fclose(fileConfigurazioneNuovo);
        return;
    }

    giorno++;

    remove("Dati/FileConfigurazione.txt");
    FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

    fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %s\n", dataGiornaliera);
    fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %02d/%02d/%04d\n", giorno, mese, anno);
    fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

    fclose(fileConfigurazioneNuovo);
    return;
}

void IncrementaGiornata() {

    char dataAttuale[6];
    char dataGiornaliera[LEN_DATATEST];
    int giorno, mese, anno;
    int ultimoSlot;

    FILE *fileConfigurazione = fopen("Dati/FileConfigurazione.txt", "r");

    fseek(fileConfigurazione, 17, SEEK_SET);
    fscanf(fileConfigurazione, "%[^/]%*c", dataAttuale);
    giorno = atoi(dataAttuale);

    fseek(fileConfigurazione, 20, SEEK_SET);
    fscanf(fileConfigurazione, "%[^/]%*c", dataAttuale);
    mese = atoi(dataAttuale);

    fseek(fileConfigurazione, 23, SEEK_SET);
    fscanf(fileConfigurazione, "%[^/n]%*c", dataAttuale);
    anno = atoi(dataAttuale);

    fseek(fileConfigurazione, 51, SEEK_SET);
    fscanf(fileConfigurazione, "%s", dataGiornaliera);

    fseek(fileConfigurazione, 72, SEEK_SET);
    fscanf(fileConfigurazione, "%d", &ultimoSlot);

    fclose(fileConfigurazione);

    if(giorno == 30 && (mese == 11 || mese == 4 || mese == 6 || mese == 9) ) {
        giorno = 1;
        mese++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

        fclose(fileConfigurazioneNuovo);
        return;
    }

    if(giorno == 31 && (mese == 1 || mese == 3 || mese == 5 || mese == 7 || mese == 10) ) {
        giorno = 1;
        mese++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

        fclose(fileConfigurazioneNuovo);
        return;
    }

    if(giorno == 31 && mese == 12) {
        giorno = 1;
        mese = 1;
        anno++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

        fclose(fileConfigurazioneNuovo);
        return;
    }

    if(giorno == 28 && mese == 2) {
        giorno = 1;
        mese++;

        remove("Dati/FileConfigurazione.txt");
        FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");

        fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %02d/%02d/%04d\n", giorno, mese, anno);
        fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %s\n", dataGiornaliera);
        fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

        fclose(fileConfigurazioneNuovo);
        return;
    }

    giorno++;

    remove("Dati/FileConfigurazione.txt");
    FILE *fileConfigurazioneNuovo = fopen("Dati/FileConfigurazione.txt", "w");


    fprintf(fileConfigurazioneNuovo, "dataGiornaliera= %02d/%02d/%04d\n", giorno, mese, anno);
    fprintf(fileConfigurazioneNuovo, "dataUltimaRegistrata= %s\n", dataGiornaliera);
    fprintf(fileConfigurazioneNuovo, "dataSlot= %d",ultimoSlot);

    fclose(fileConfigurazioneNuovo);
    return;
}

char * RecuperaDataGiornalieraDaConfigurazione() {

    char * data;
    data = malloc(sizeof(char) * LEN_DATATEST);

    FILE *fileConfigurazione = fopen("Dati/FileConfigurazione.txt", "r");

    fseek(fileConfigurazione, 17, SEEK_SET);
    fscanf(fileConfigurazione, "%s", data);

    return data;
}
