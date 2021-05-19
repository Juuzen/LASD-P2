#include <stdio.h>
#include "productCatalogue.h"

int main() {

    PtrCatalogue catalogue = NULL;

    catalogue = retrieveItemsFromCatalogueFile("catalogue.txt");

    return 0;
}