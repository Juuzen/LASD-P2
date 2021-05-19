//
// Created by backs on 18/05/2021.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "productCatalogue.h"


Item createNewItem(char *itemLabel, int specificWeight){
    Item item;
    strcpy(item.itemLabel, itemLabel);
    item.specificWeight = specificWeight;
    return item;
}

//  In case of failure, should it return NULL or empty list?
PtrCatalogue retrieveItemsFromCatalogueFile(char *catalogueFilename){
    // Sanity check on filename
    if (catalogueFilename == NULL) {
        return NULL;
    }

    //File opening
    FILE *productCatalogue = fopen(catalogueFilename, "r");

    //Product catalogue declaration
    PtrCatalogue tmp = NULL;

    // Sanity check on fileopen
    if (productCatalogue == NULL) {
        return NULL;
    }

    while (feof(productCatalogue) == 0)  {
        char localProductLabel[MAX_ITEM_LABEL_SIZE];
        int localSpecificWeight;
        int scannedElements = fscanf(productCatalogue, "%s\t%d\n", localProductLabel, &localSpecificWeight);

        if (scannedElements == 2) {
            Item genericItem = createNewItem(localProductLabel, localSpecificWeight);
            PtrCatalogue item = createNodeCatalogue(genericItem);
            tmp = insertTail(tmp,item);
        }
    }
    fclose(productCatalogue);

    return tmp;
}

void debugPrint(Item item) {
    printf("Printing item..\n\tLabel: %s\n\tSpecific weight: %d\n\n", item.itemLabel, item.specificWeight);
}

PtrCatalogue createNodeCatalogue(Item item){
    PtrCatalogue tmp = NULL;
    tmp = (Catalogue*)malloc(sizeof(Catalogue));

    if(tmp!=NULL){
        tmp->item = item;
        tmp->next = NULL;
    }

    return tmp;
}

PtrCatalogue insertTail(PtrCatalogue tmp, PtrCatalogue list){
    if(list==NULL) return tmp;
    list->next=insertTail(tmp,list->next);
    return list;
}

void print(PtrCatalogue list){

    while(list!=NULL)
    {
        debugPrint(list->item);
        list = list->next;
    }
}

