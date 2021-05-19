#include <stdio.h>
#include "productCatalogue.h"

int main() {

    PtrCatalogue catalogue = NULL;

    catalogue = retrieveItemsFromCatalogueFile("catalogue.txt");
    if(catalogue==NULL){
        printf("errore");
    }

    print(catalogue);

    return 0;
}