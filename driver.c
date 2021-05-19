//
// Created by backs on 20/05/2021.
//

#include "stdio.h"
#include "stdlib.h"
#include "driver.h"
#include "string.h"

/*
 * NOTE: Driver is not returned from function but instead is returned by reference in the input parameter
 *          Initialize it first or the function will CRASH!!!
 *
 * Error codes:
 *      -100    DRIVER NOT INITIALIZED
 *      -1  Input null
 *      0   Driver not registered
 */
int retrieveDriverInfoFromFile(char *driverCode, char *filename, Driver *driver) {
    if (driver == NULL) {
        fprintf(stderr, "ERROR: DRIVER IS NULL. I TOLD YOU, FOOL\n");
        return -100;
    }

    // Sanity check on input
    if (driverCode == NULL || filename == NULL) {
        fprintf(stderr, "retrieveDriverInfoFromFile() - other inputs null\n");
        return -1;
    }

    FILE *driverDatabase = fopen(filename, "r");

    if (driverDatabase == NULL) {
        fprintf(stderr, "retrieveDriverInfoFromFile() - file opening null\n");
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
