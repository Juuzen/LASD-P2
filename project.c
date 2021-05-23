#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "driver.h"
#include "authlib.h"
#include "const.h"
#include "productCatalogue.h"

void projectRun() {
    /* Menu di accesso del driver */
    /*
    int loginCheck = doLogin("8000", "qwerty", DRIVER_LOGIN_DB);
    if (loginCheck == 1) {
        printf("EVVAI\n");
        Driver driver;
        int loadCheck = retrieveDriverInfoFromFile("8000", DRIVER_INFO_DB, &driver);
        if (loadCheck == 1) {
            
        }
        else printf("SCUS %d\n", loadCheck);
    }
    else printf("SCUSATE %d\n", loginCheck);
    */

    PtrCatalogue catalogue = retrieveItemsFromCatalogueFile(PRODUCT_CATALOGUE_DB);
    if (catalogue != NULL) print(catalogue);
    else printf("SCUSATE\n");
    /* Fine */
}

