//
// Created by backs on 20/05/2021.
//

#include "stdio.h"
#include "stdlib.h"
#include "driver.h"
#include "string.h"
#include "logger.h"

#define METHOD_TEST "retrieveDriverInfoFromFile()"
#define WRITE_DRIVER_FILE_METHOD "writeDriverInfoToFile()"

/*
 * NOTE: Driver is not returned from function but instead is returned by reference in the input parameter
 *          Initialize it first or the function will CRASH!!!
 *
 * Error codes:
 *      -100    DRIVER NOT INITIALIZED
 *      -2  Error in file opening
 *      -1  Input null
 *      0   Driver not registered
 */
int retrieveDriverInfoFromFile(char *driverCode, char *filename, Driver *driver) {
    if (driver == NULL) {
        logMessage(METHOD_TEST, LOG_LEVEL_ERROR, "DRIVER NOT INITIALIZED", 1);
        return -100;
    }

    // Sanity check on input
    if (driverCode == NULL || filename == NULL) {
        fprintf(stderr, LOG_LEVEL_ERROR, "retrieveDriverInfoFromFile() - other inputs null\n");
        return -1;
    }

    FILE *driverDatabase = fopen(filename, "r");

    if (driverDatabase == NULL) {
        fprintf(stderr, LOG_LEVEL_ERROR, "retrieveDriverInfoFromFile() - file opening null\n");
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

/* Error codes:
 *      -2  Error in file opening
 *      -1  Filename null
 *       0  Error writing to file
 *       1  Success
 */
int writeDriverInfoToFile(Driver driver, char *filename) {
    if (filename == NULL) {
        logMessage(WRITE_DRIVER_FILE_METHOD, LOG_LEVEL_ERROR, "Filename is null", 0);
        return -1;
    }

    FILE *driverDatabase = fopen(filename, "a");

    if (driverDatabase == NULL) {
        logMessage(WRITE_DRIVER_FILE_METHOD, LOG_LEVEL_ERROR, "Error opening file", 0);
        return -2;
    }

    int printFileResult = fprintf(driverDatabase, LOG_LEVEL_ERROR, "%s\t%d\n", driver.driverCode, driver.truckWeight);

    if (printFileResult < 0) {
        logMessage(WRITE_DRIVER_FILE_METHOD, LOG_LEVEL_ERROR, "Error writing to file", 0);
        return 0;
    }

    fclose(driverDatabase);

    return 1;
}
