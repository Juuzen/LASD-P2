#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item item_new (char *itemLabel, int itemWeight, int itemCode) {
    Item item;
    strcpy(item.label, itemLabel);
    item.weight = itemWeight;
    item.code = itemCode;
    return item;
}

void item_print(Item item) {
    printf("Nome prodotto: %s\n", item.label);
    printf("Codice prodotto: %d\n", item.code);
    printf("Peso per singola unita': %d kg\n\n", item.weight);
}