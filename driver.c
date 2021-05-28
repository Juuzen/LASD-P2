#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver.h"
#include "logger.h"
#include "const.h"



/*  Recupera le informazioni della struttura Driver da file, se presenti.
 *  NOTA: la struttura Driver viene passata per riferimento, per cui la funzione necessita di una 
 *  variabile correttamente inizializzata.
 *
 *  Output:
 *  -100    ERRORE: variabile driver non inizializzata
 *  -2      ERRORE: apertura file non corretta
 *  -1      ERRORE: input non corretti
 *  0       ERRORE: informazioni struttura Driver non presenti
 *  1       Informazioni struttura Driver trovati ed assegnati con successo
 */
int driver_readInfo (char *driverCode, char *filename, Driver *driver) {
    if (driver == NULL) {
        logMessage(METHOD_DRIVER_RETRIEVE_DRIVER_INFO, LOG_LEVEL_ERROR, "Error on driver - not initialized");
        return -100;
    }

    // Sanity check on input
    if (driverCode == NULL || filename == NULL) {
        logMessage(METHOD_DRIVER_RETRIEVE_DRIVER_INFO, LOG_LEVEL_ERROR, "Error in input variables");
        return -1;
    }

    FILE *driverDatabase = fopen(filename, "r");

    if (driverDatabase == NULL) {
        logMessage(METHOD_DRIVER_RETRIEVE_DRIVER_INFO, LOG_LEVEL_ERROR, "Error in opening file");
        return -2;
    }

    int foundDriver = 0;

    while (feof(driverDatabase) == 0 && foundDriver == 0) {
        char localDriverCode[MAX_LENGTH_DRIVER_CODE];
        int truckWeight;

        int scannedItemsFromFscanf = fscanf(driverDatabase, "%s\t%d\n", localDriverCode, &truckWeight);

        if (scannedItemsFromFscanf == 2) {
            if (strcmp(localDriverCode, driverCode) == 0) {
                strcpy(driver->driverCode, localDriverCode);
                driver->truckWeight = truckWeight;
                foundDriver = 1;
            }
        }
    }

    fclose(driverDatabase);

    return foundDriver;
}

/*  Scrive su file le informazioni di una struttua Driver passata in input.
 *  Output:
 *  -2  ERRORE: apertura file non riuscita
 *  -1  ERRORE: nome file non corretto
 *   0  ERRORE: scrittura su file non riuscita
 *   1  Scrittura su file completata con successo
 */
int driver_writeInfo (Driver driver, char *filename) {
    if (filename == NULL) {
        logMessage(METHOD_DRIVER_WRITE_DRIVER_INFO, LOG_LEVEL_ERROR, "Filename is null");
        return -1;
    }

    FILE *driverDatabase = fopen(filename, "a");

    if (driverDatabase == NULL) {
        logMessage(METHOD_DRIVER_WRITE_DRIVER_INFO, LOG_LEVEL_ERROR, "Error opening file");
        return -2;
    }

    int printFileResult = fprintf(driverDatabase, "%s\t%d\n", driver.driverCode, driver.truckWeight);

    if (printFileResult < 0) {
        logMessage(METHOD_DRIVER_WRITE_DRIVER_INFO, LOG_LEVEL_ERROR, "Error writing to file");
        return 0;
    }

    fclose(driverDatabase);

    return 1;
}

/*  Calcola il peso totale del camion più gli Item al suo interno.
 *  Output:
 *  int totalWeight: il peso totale correttamente calcolato.
 */
int driver_getTotalWeight(Driver driver) {
    if (driver.truckLoad == NULL) return driver.truckWeight;
    else return driver.truckWeight + order_getTotalWeight(driver.truckLoad); 
}