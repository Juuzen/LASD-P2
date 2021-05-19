//
// Created by backs on 18/05/2021.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "productCatalogue.h"


Item createNewItem(char *itemLabel, int specificWeight) {
    Item item;
    strcpy(item.itemLabel, itemLabel);
    item.specificWeight = specificWeight;
    return item;
}

