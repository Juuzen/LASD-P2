//
// Created by backs on 18/05/2021.
//

#ifndef LASD_P2_PRODUCTCATALOGUE_H
#define LASD_P2_PRODUCTCATALOGUE_H

#define MAX_ITEM_LABEL_SIZE 21

typedef struct Item {
    char itemLabel[MAX_ITEM_LABEL_SIZE];    //takes in account already the + 1
    int specificWeight;
} Item;

typedef struct Catalogue {
    Item item;
    struct Catalogue *next;
} Catalogue;

typedef struct Catalogue* PtrCatalogue;

Item createNewItem(char *itemLabel, int specificWeight);
PtrCatalogue retrieveItemsFromCatalogueFile(char *catalogueFilename);

#endif //LASD_P2_PRODUCTCATALOGUE_H
