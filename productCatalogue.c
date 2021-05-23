//
// Created by backs on 18/05/2021.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "productCatalogue.h"


Item createNewItem(char *itemLabel, int specificWeight, int codProduct){
    Item item;
    strcpy(item.itemLabel, itemLabel);
    item.specificWeight = specificWeight;
    item.codProduct = codProduct;
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
        int localSpecificWeight, localProductCode;
        int scannedElements = fscanf(productCatalogue, "%d\t%s\t%d\n", &localProductCode, localProductLabel, &localSpecificWeight);

        if (scannedElements == 3) {
            Item genericItem = createNewItem(localProductLabel, localSpecificWeight, localProductCode);
            PtrCatalogue item = createNodeCatalogue(genericItem);
            tmp = insertTail(tmp,item);
        }
    }
    fclose(productCatalogue);

    return tmp;
}

void debugPrint(Item item) {
    printf("\n\tCode:%d\n\tLabel: %s\n\tSpecific weight: %d\n", item.codProduct, item.itemLabel, item.specificWeight);
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

    printf("Product List...\n");
    while(list!=NULL){
        debugPrint(list->item);
        list = list->next;
    }
}

void openShopList(){

    PtrCatalogue catalogue = NULL;
    catalogue = retrieveItemsFromCatalogueFile("catalogue.txt");

    print(catalogue);
}

