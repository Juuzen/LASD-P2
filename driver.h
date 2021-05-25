//
// Created by backs on 19/05/2021.
//

#ifndef LASD_P2_DRIVER_H
#define LASD_P2_DRIVER_H
#include "const.h"
#include "orderManagement.h"


typedef struct Driver {
    char driverCode[MAX_LENGTH_DRIVER_CODE];
    int truckWeight;
    PtrOrder truckLoad;
} Driver;

int retrieveDriverInfoFromFile(char *driverCode, char *filename, Driver *driver);    //Retrieves stored informations for driver
int writeDriverInfoToFile(Driver driver, char *filename);   // Stores information after registration to be used after signup in authlib.c
int getDriverTotalWeight(Driver driver);

#endif //LASD_P2_DRIVER_H
