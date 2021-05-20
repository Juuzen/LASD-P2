#include <stdio.h>
#include "productCatalogue.h"
#include "driver.h"
#include "logger.h"

int main() {
    Driver driver;
    int foundDriver = retrieveDriverInfoFromFile("A12", "driverdb.txt", &driver);
    printf("%d\n", foundDriver);
    return 0;
}