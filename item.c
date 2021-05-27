#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "logger.h"

Item item_new (char *itemLabel, int itemWeight, int itemCode) {
    Item item;
    logMessage("item_new()", LOG_LEVEL_DEBUG, "Copying string");
    strcpy(item.label, itemLabel);
    logMessage("item_new()", LOG_LEVEL_DEBUG, "string copied");
    item.weight = itemWeight;
    item.code = itemCode;
    return item;
}

void item_print(Item item) {
    printf("Nome prodotto: %s\n", item.label);
    printf("Codice prodotto: %d\n", item.code);
    printf("Peso per singola unita': %d kg\n", item.weight);
}