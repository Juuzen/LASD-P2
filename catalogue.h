#ifndef LASD_P2_CATALOGUE_H
#define LASD_P2_CATALOGUE_H
#include "item.h"
#include "const.h"


typedef struct catalogue {
    Item item;
    struct catalogue *next;
} catalogue;

typedef struct catalogue* Catalogue;

Catalogue catalogue_new (Item item);
Catalogue catalogue_tailInsert (Catalogue catalogue, Catalogue item);
Catalogue catalogue_retrieveListFromFile (char *filename);
Catalogue catalogue_findItem (Catalogue list, int itemCode);
void catalogue_print (Catalogue list);
void catalogue_freeNode (Catalogue node);
void catalogue_freeList (Catalogue list);
void catalogue_mockCatalogueFile();
Item parseItemResilient(FILE *file);


#endif //LASD_P2_PRODUCTCATALOGUE_H
