//
// Created by backs on 20/05/2021.
//

#include "stdio.h"
#include "stdlib.h"
#include "driver.h"
#include "string.h"
#include "logger.h"
#include "const.h"



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

/* Error codes:
 *      -2  Error in file opening
 *      -1  Filename null
 *       0  Error writing to file
 *       1  Success
 */
int writeDriverInfoToFile(Driver driver, char *filename) {
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

int getDriverTotalWeight(Driver driver) {
    if (driver.truckLoad == NULL) return driver.truckWeight;
    else return driver.truckWeight + calculateOrderWeight(driver.truckLoad); 
}