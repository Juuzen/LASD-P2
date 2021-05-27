#ifndef LASD_P2_DRIVER_H
#define LASD_P2_DRIVER_H
#include "const.h"
#include "order.h"

typedef struct Driver {
    char driverCode[MAX_LENGTH_DRIVER_CODE];
    int truckWeight;
    Order truckLoad;
} Driver;

int driver_readInfo (char *driverCode, char *filename, Driver *driver);
int driver_writeInfo (Driver driver, char *filename);
int driver_getTotalWeight (Driver driver);

#endif //LASD_P2_DRIVER_H
