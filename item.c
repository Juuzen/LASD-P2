#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "logger.h"

/*  Crea un elemento Item con i parametri in ingresso, e la restituisce. 
 *  Output:
 *  Item newItem = la variabile correttamente inizializzata.
 */
Item item_new (char *itemLabel, int itemWeight, int itemCode) {
    Item newItem;
    logMessage("item_new()", LOG_LEVEL_DEBUG, "Copying string");
    strcpy(newItem.label, itemLabel);
    logMessage("item_new()", LOG_LEVEL_DEBUG, "string copied");
    newItem.weight = itemWeight;
    newItem.code = itemCode;
    return newItem;
}

/*  Fetcha un singolo item dal file catalogo passato in input
 *
 *      WARNING: SI ASPETTA CHE IL FILE SIA GIA' STATO APERTO
 */
Item item_fetchSingleItemFromFile(FILE *file) {
    char c;
    int index = 0;
    char parsedString[MAX_ITEM_LABEL_SIZE];
    int productCode;
    int weight;

    fscanf(file, "%d\t", &productCode);

    do {
        c = fgetc(file);
        parsedString[index] = c;
        index++;
    } while (c != '\t');

    parsedString[index++] = '\0';
    fscanf(file, "%d\n", &weight);
    Item item = item_new(parsedString, weight, productCode);

    return item;
}

/* Stampa su stdout un elemento Item*/
void item_print(Item item) {
    printf("Nome prodotto: %s\n", item.label);
    printf("Codice prodotto: %d\n", item.code);
    printf("Peso per singola unita': %d kg\n", item.weight);
}

