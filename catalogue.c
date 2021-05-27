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
        return NULL;
    }

    while (feof(catalogueFile) == 0)  {
        char localProductLabel[MAX_ITEM_LABEL_SIZE];
        int localSpecificWeight, localProductCode;
        int scannedElements = fscanf(catalogueFile, "%d\t%s\t%d\n", &localProductCode, localProductLabel, &localSpecificWeight);

        if (scannedElements == 3) {
            Item genericItem = item_new(localProductLabel, localSpecificWeight, localProductCode);
            Catalogue item = catalogue_new(genericItem);
            catalogue = catalogue_tailInsert(catalogue, item);
        }
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
    if (list == NULL) return NULL;
    if (list->item.code == itemCode) return list;
    return catalogue_findItem(list->next, itemCode);
}

/*  Stampa su stdout una lista di elementi Catalogue. */
void catalogue_print (Catalogue list){
    if (list != NULL) {
        item_print(list->item);
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







