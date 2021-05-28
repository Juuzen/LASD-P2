#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catalogue.h"
#include "item.h"
#include "const.h"
#include "logger.h"

/*  Alloca dinamicamente un nuovo elemento Catalogue. */
Catalogue catalogue_new(Item item){
    Catalogue tmp = NULL;
    tmp = (Catalogue) calloc (1, sizeof(catalogue));
    if(tmp!=NULL){
        tmp->item = item;
        tmp->next = NULL;
    }
    return tmp;
}

/*  Aggiunge un elemento Catalogue in fondo alla lista.
 *  Output:
 *  Catalogue list: la lista correttamente modificata.
 */
Catalogue catalogue_tailInsert (Catalogue catalogue, Catalogue item) {
    logMessage("tailInsert()", LOG_LEVEL_DEBUG, "inserting item in tail");
    if (catalogue == NULL) return item;
    catalogue->next = catalogue_tailInsert(catalogue->next, item);
    return catalogue;
}

/*  Crea una lista di elementi Catalogue leggendo il corrispettivo file.
 *  Output:
 *  NULL: errore (leggere log)
 *  Catalogue list: file letto con successo
 */
Catalogue catalogue_retrieveListFromFile (char *filename) {
    // Sanity check on filename
    if (filename == NULL) {
        logMessage(METHOD_CATALOGUE_RETRIEVE_LIST_FROM_FILE, LOG_LEVEL_ERROR, "Input variable is NULL");
        return NULL;
    }

    //File opening
    FILE *catalogueFile = fopen(filename, "r");

    //Product catalogue declaration
    Catalogue catalogue = NULL;

    // Sanity check on fileopen
    if (catalogueFile == NULL) {
        logMessage(METHOD_CATALOGUE_RETRIEVE_LIST_FROM_FILE, LOG_LEVEL_ERROR, "Error opening product catalogue file");
        catalogue_mockCatalogueFile();
        catalogueFile = fopen(filename, "r");
        if (catalogueFile == NULL) {
            logMessage(METHOD_CATALOGUE_RETRIEVE_LIST_FROM_FILE, LOG_LEVEL_ERROR, "Error opening product catalogue file");
            return NULL;
        }
    }

    while (feof(catalogueFile) == 0)  {
        Item genericItem = item_fetchSingleItemFromFile(catalogueFile);
        Catalogue item = catalogue_new(genericItem);
        catalogue = catalogue_tailInsert(catalogue, item);
        //  Lascio commentata e non elimino per storico e debug
//        char localProductLabel[MAX_ITEM_LABEL_SIZE];
//        int localSpecificWeight, localProductCode;
//        int scannedElements = fscanf(catalogueFile, "%d\t%s\t%d\n", &localProductCode, localProductLabel, &localSpecificWeight);
//
//        if (scannedElements == 3) {
//            Item genericItem = item_new(localProductLabel, localSpecificWeight, localProductCode);
//            Catalogue item = catalogue_new(genericItem);
//            catalogue = catalogue_tailInsert(catalogue, item);
//        }
    }
    fclose(catalogueFile);

    return catalogue;
}

/*  Restituisce, se presente, un elemento Catalogue dalla lista.
 *  Output:
 *  NULL: elemento non trovato
 *  Catalogue item: elemento trovato con successo
 */
Catalogue catalogue_findItem(Catalogue list, int itemCode)
{
    logMessage("findItem()", LOG_LEVEL_DEBUG, "searching for item");
    if (list == NULL) return NULL;
    if (list->item.code == itemCode) return list;
    return catalogue_findItem(list->next, itemCode);
}

/*  Stampa su stdout una lista di elementi Catalogue. */
void catalogue_print (Catalogue list){
    if (list != NULL) {
        item_print(list->item);
        printf("\n");
        catalogue_print(list->next);
    }
}

/*  Dealloca un elemento Catalogue. */
void catalogue_freeNode (Catalogue node) {
    if (node != NULL) {
        node->next = NULL;
        node->item.code = 0;
        node->item.weight = 0;
        memset(node->item.label, '\0', sizeof(node->item.label));
        free(node);
    }
}

/*  Dealloca una lista di elementi Catalogue. */
void catalogue_freeList (Catalogue list) {
    if (list != NULL) {
        catalogue_freeList(list->next);
        catalogue_freeNode(list);
    }
}

/* Crea un mock del file di catalogo nel caso in cui esso non sia presente */
void catalogue_mockCatalogueFile() {
    FILE *catalogueFile = NULL;

    /* Sanity check on file opening and existence */
    catalogueFile = fopen(PRODUCT_CATALOGUE_DB, "r");

    /* In case the file was not found on first try */
    if (catalogueFile != NULL) {
        fclose(catalogueFile);
        return;
    }

    logMessage(METHOD_CATALOGUE_MOCK_FILE, LOG_LEVEL_INFO, "Catalogue db not found - Creating mock one");
    catalogueFile = fopen(PRODUCT_CATALOGUE_DB, "w");

    /* Mock section */
    fprintf(catalogueFile, "%d\t%s\t%d\n", 100, "Patate", 2);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 101, "Pasta", 1);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 102, "Cipolle", 1);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 103, "Birra", 7);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 104, "Vino", 8);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 105, "Pane", 10);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 106, "Patatine", 1);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 107, "Acqua", 12);
    fprintf(catalogueFile, "%d\t%s\t%d\n", 108, "Carne rossa", 1);

    fclose(catalogueFile);
    return;
}