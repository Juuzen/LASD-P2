//
// Created by backs on 18/05/2021.
//

#ifndef LASD_P2_PRODUCTCATALOGUE_H
#define LASD_P2_PRODUCTCATALOGUE_H
#include "const.h"


typedef struct Item {
    char itemLabel[MAX_ITEM_LABEL_SIZE];    //takes in account already the + 1
    int codProduct;
    int specificWeight;
} Item;

typedef struct Catalogue {
    Item item;
    struct Catalogue *next;
} Catalogue;

typedef struct Catalogue* PtrCatalogue;

void freeCatalogueNode(PtrCatalogue node);
void freeCatalogueList(PtrCatalogue list);

Item createNewItem(char *itemLabel, int specificWeight, int codProduct);
PtrCatalogue retrieveItemsFromCatalogueFile(char *catalogueFilename);
PtrCatalogue insertTail(PtrCatalogue catalogue, PtrCatalogue item);
void printItemList(PtrCatalogue list);
PtrCatalogue createNodeCatalogue(Item item);
void printSingleItem(Item item);

#endif //LASD_P2_PRODUCTCATALOGUE_H
