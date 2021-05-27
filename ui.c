#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ui.h"
#include "graph.h"
#include "const.h"
#include "authlib.h"
#include "driver.h"
#include "productCatalogue.h"
#include "orderManagement.h"
#include "utils.h"
#include "logger.h"

/* Entry point del progetto */
void projectRun() {
    int userChoice;
    bool running = true;

    do {
        clearScreen();
        printTitle();
        printf("Benvenuto su I-eats! La piattaforma di delivery piu' famosa di Island!\n");
        printf("Prego, selezionare la propria opzione:\n");
        printf("1. Autenticazione driver\n");
        printf("2. Registrazione nuovo account driver\n");
        printf("3. Uscita dal programma\n\n");
        printf("La tua scelta: ");
        userChoice = getInt(3);

        switch (userChoice) {
        case 1: /* Autenticazione utente */
            authenticationMenu();
            break;
        
        case 2: /* Registrazione nuovo utente */
            registrationMenu();
            break;
        
        case 3: /* Uscita dal programma*/
            clearScreen();
            printTitle();
            printf("Arrivederci da I-eats! Buona giornata :)\n"); 
            running = false;
            break;

        default: /* Caso di default (non dovrebbe mai essere eseguito, data la presenza di getInt */
            logMessage(METHOD_PROJECT_RUN, LOG_LEVEL_ERROR, "Unreachable end");
            printf("Scelta non corretta! Riprovare\n");
            programPause();
        }
    } while (running);
    
}

/* Menu di autenticazione */
void authenticationMenu() {
    int loginCheck, userChoice;
    bool running = true;

    char *driverCode, *driverPassword;
    do {
        clearScreen();
        printTitle();
        printf("Inserisci il tuo codice driver:\n");
        //FIXME: Vedere che succede con stringa vuota e, nel caso, fare in modo che l'utente inserisca la stringa
        driverCode = getString(MAX_SIZE_USERNAME);
        printf("\nInserisci la tua password:\n");
        //FIXME: Vedere che succede con stringa vuota e, nel caso, fare in modo che l'utente inserisca la stringa
        driverPassword = getString(MAX_SIZE_PASSWORD);

        loginCheck = doLogin(driverCode, driverPassword, DRIVER_LOGIN_DB);

        if (loginCheck == 1) {
            Driver driver;
            int driverCheck = retrieveDriverInfoFromFile(driverCode, DRIVER_INFO_DB, &driver);
            if (driverCheck == 1) {
                driver.truckLoad = NULL; //FIXME: Questa cosa deve andare all'inizializzazione del driver
                driverMenu(driver);
            }
            else {
                printf("Non e' stato possibile recuperare le informazioni del driver, riprovare piu' tardi...\n");
                logMessage(METHOD_REGISTRATION_MENU, LOG_LEVEL_ERROR, "Error retrieving driver info");
                
            }
            running = false; // Per evitare che venga ripetuta l'autenticazione dopo essere usciti
        } else { 
            clearScreen();
            printTitle();
            printf("Le credenziali sono errate! Seleziona una opzione:\n");
            printf("1. Ripetere l'autenticazione\n");
            printf("2. Torna indietro\n");
            printf("\nLa tua scelta: ");
            userChoice = getInt(2);
            switch (userChoice){
            case 1: // Non è necessario fare nulla nel caso si voglia ripetere con l'autenticazione
                break;

            case 2:
                running = false;
                clearScreen();
                printTitle();
                printf("Arrivederci!\n");
                programPause();
                break;
            
            default:
                logMessage(METHOD_REGISTRATION_MENU, LOG_LEVEL_ERROR, "Un-considered choice");
                running = false;
                break;
            }
        }

        //TODO: gestire getString in modo che questo passaggio sia ridondante ed è possibile rimuoverlo
        free(driverCode);
        free(driverPassword);
    } while (running);
}

/* Menu di registrazione */
void registrationMenu() {
    int weight, registrationCheck, userChoice;
    char *driverCode, *driverPassword;
    bool running = true;

    do {
        clearScreen();
        printTitle();
        printf("Inserisci username:\n");
        //FIXME: Vedere che succede con stringa vuota e, nel caso, fare in modo che l'utente inserisca la stringa
        driverCode = getString(MAX_SIZE_USERNAME);
        printf("\nInserisci password:\n");
        //FIXME: Vedere che succede con stringa vuota e, nel caso, fare in modo che l'utente inserisca la stringa
        driverPassword = getString(MAX_SIZE_PASSWORD);

        registrationCheck = doRegistration(driverCode, driverPassword, DRIVER_LOGIN_DB);
        switch (registrationCheck) {
            case -2:
                clearScreen();
                printTitle();
                printf("Questo codice driver e' gia' presente nel sistema!\n");
                printf("Selezionare una opzione:\n");
                printf("1. Ripetere la registrazione con un nuovo codice driver\n");
                printf("2. Torna indietro\n\n");
                printf("La tua scelta: ");
                userChoice = getInt(2);
                switch (userChoice) {
                case 1: /* Non è necessario fare nulla nel caso si voglia ripetere l'autenticazione */
                    break;

                    case 2:
                        clearScreen();
                        printTitle();
                        printf("Arrivederci!\n");
                        programPause();
                        running = false;
                
                default:
                    logMessage(METHOD_REGISTRATION_MENU, LOG_LEVEL_ERROR, "Unattended case");
                    running = false;
                    break;
                }
                break;
            
            // Problema di accesso ai file interni
            case -1:
                logMessage(METHOD_REGISTRATION_MENU, LOG_LEVEL_ERROR, "Error during registration of driver");
                clearScreen();
                printTitle();
                printf("Non e' possibile proseguire con la registrazione. Riprovare piu' tardi.\n");
                programPause();
                running = false;
                break;

            // Registrazione avvenuta con successo, si procede con il salvataggio dei dati del driver
            case 1:
                do {
                    printf("\nInserisci il peso del tuo veicolo per le consegne (in kg):\n");
                    weight = getInt(0);
                    if (weight <= 0) {
                        printf("Il peso del camion deve essere un valore positivo! Riprova.\n");
                        programPause();
                    }
                } while (weight <= 0);

                Driver driver;
                strcpy(driver.driverCode, driverCode);
                driver.truckWeight = weight;

                writeDriverInfoToFile(driver, DRIVER_INFO_DB);
                printf("Registrazione completata con successo! Ora puo' tornare al menu principale.\n");
                running = false;
                programPause();
                break;

            default:
                logMessage(METHOD_REGISTRATION_MENU, LOG_LEVEL_ERROR, "unreachable end");
                printf("Vi e' stato un errore nella registrazione. Tornerai al menu principale.\n");
                programPause();
                running = false;
        }
    
        //TODO: Trovare un modo di gestire getString in modo da rendere superfluo questo passaggio e rimuoverlo
        free(driverCode);
        free(driverPassword);
    } while (running);
}

/* Menu personale del driver */
void driverMenu(Driver driver) {
    int userChoice;
    bool running = true; 

    do {
        clearScreen();
        printTitle();
        printf("Benvenuto, driver %s!\n", driver.driverCode);
        printf("Seleziona il servizio che vuoi richiedere:\n");
        printf("1. Effettuare la spesa\n");
        printf("2. Effettuare una consegna\n");
        printf("3. Visualizza informazioni account\n");
        printf("4. Effettuare la disconnessione\n\n");
        printf("La tua scelta: ");
        userChoice = getInt(4);

        switch (userChoice){
        case 1:
            driverShopMenu(&driver);
            break;
        
        case 2:
            driverDeliveryMenu(driver);
            break;
        
        case 3:
            showDriverInfoMenu(driver);
            break;

        case 4:
            running = false;
            clearScreen();
            printTitle();
            printf("Arrivederci, %s!\n", driver.driverCode);
            programPause();
            break;

        default:
            printf("Vi e' stato un errore nella lettura dell'input, verrai disconnesso.\n");
            logMessage(METHOD_DRIVER_MENU, LOG_LEVEL_ERROR, "Unreachable end");
            running = false;
            programPause();
        }
    } while (running);
}

/* Menu di gestione del carrello */
void driverShopMenu(Driver* driver) {
    bool running = true;
    int userChoice = -1;

    PtrCatalogue catalogue = retrieveItemsFromCatalogueFile(PRODUCT_CATALOGUE_DB);
    PtrOrder cart = NULL; 
    
    do {
        clearScreen();
        printTitle();
        printf("Seleziona un'opzione:\n");
        printf("1. Aggiungere un prodotto al carrello\n");
        printf("2. Rimuovere un prodotto dal carrello\n");
        printf("3. Visualizzare il carrello attuale\n");
        printf("4. Conferma l'ordine, e carica il carrello sul camion\n");
        printf("5. Annulla l'ordine e torna indietro\n");
        printf("\nLa tua scelta: ");
        userChoice = getInt(5);

        switch (userChoice) {
            case 1: /* Aggiunta di un prodotto al carrello */
                cart = addCartItemMenu(cart, catalogue);
                break;

            case 2: /* Rimozione di un prodotto dal carrello */
                cart = removeCartItemMenu(cart);
                break;

            case 3: /* Visualizza lo stato del carrello */
                showCartInfoMenu((*driver), cart);
                break;

            case 4: /* Finalizzazione ordine, aggiunta al carico del camion */
                if (cart != NULL) {
                    (*driver).truckLoad = mergeLists((*driver).truckLoad, cart);
                    printf("Carrello caricato con successo nel camion!\n");
                }
                else printf("Il carrello era vuoto, per cui non vi sono state modifiche al camion!\n");
                programPause();
                running = false;
                break;

            case 5: /* Annullamento ordine */
                printf("Nessuna modifica e' stata effettuata!\n");
                programPause();
                running = false;
                break;

            default: /* Errore */
                logMessage(METHOD_DRIVER_SHOP_MENU, LOG_LEVEL_ERROR, "unreachable end");
                printf("Errore nella gestione dell'input. Tornerai ora al menu precedente.\n");
                running = false;
                programPause();
        }
    } while (running);

    /* Liberazione dell'heap */
    freeCatalogueList(catalogue);
    freeOrderList(cart);
}

/* Menu di aggiunga elemento al carrello */
PtrOrder addCartItemMenu(PtrOrder cart, PtrCatalogue catalogue) {
    int userChoice;
    bool running = true;
                    
    do {
        cart = addItemToCart(cart, catalogue);
        printf("Articolo inserito! Seleziona un'opzione:\n");
        printf("1. Aggiungi un nuovo prodotto al carrello\n");
        printf("2. Torna indietro\n\n");
        printf("La tua scelta: ");
        userChoice = getInt(2);
        switch (userChoice) {
            case 1:
                break;
                    
            case 2:
                running = false;
                break;

            default:
                logMessage("addCartItemMenu()", LOG_LEVEL_ERROR, "unreachable end");
                running = false;
                break;
        }
    } while (running);

    return cart;
}

/* Menu di rimozione elemento dal carrello */
PtrOrder removeCartItemMenu(PtrOrder cart) {
    int userChoice;
    bool running = true;
    
    do {
        clearScreen();
        printTitle();
        if (cart == NULL) {
            running = false;
            printf("Il carrello e' vuoto! Non puoi rimuovere prodotti.\n");
            programPause();
        }

        else {
            cart = removeItemFromCart(cart);

            printf("Articolo rimosso! Seleziona un'opzione:\n");
            printf("1. Rimuovi un altro prodotto\n");
            printf("2. Torna indietro\n");
            printf("\nLa tua scelta: ");
            userChoice = getInt(2);

            switch (userChoice) {
                case 1: /* In questo caso non è necessario fare nulla */
                    break;
                        

                case 2:
                    running = false;
                    break;

                default:
                    logMessage("removeCartItemMenu()", LOG_LEVEL_ERROR, "unreachable end");
                    running = false;
                    break;
            }
        }
    } while (running);

    return cart;
}

/* Menu di visualizzazione informazioni carrello */
void showCartInfoMenu(Driver driver, PtrOrder cart) {
    clearScreen();
    printTitle();
    printf("*** RIEPILOGO ORDINI ***\n");
    printf("Prodotti aggiunti al carrello:\n");
    printOrderList(cart);

    if (driver.truckLoad != NULL) {
        printf("\nProdotti gia' caricati:\n");
        printOrderList(driver.truckLoad);
    }
    printf("\n");

    printf("\n*** PESO TOTALE ORDINE ***\n\n");

    int cartWeight = calculateOrderWeight(cart);
    int truckWeight = getDriverTotalWeight(driver);
    printf("Peso del carrello: %d\n", cartWeight);
    printf("Peso totale (provvisorio): %d\n", cartWeight + truckWeight); 
    programPause();
}

/* Menu per mostrare le info attuali del driver */
void showDriverInfoMenu(Driver driver) {
    clearScreen();
    printTitle();
    printf("Username driver: %s\n", driver.driverCode);
    printf("Peso del camion: %d\n", driver.truckWeight);
    if (driver.truckLoad != NULL) {
        printf("Elementi caricati nel camion:\n");
        printOrderList(driver.truckLoad);
        printf("Peso totale del camion: %d\n", getDriverTotalWeight(driver));
    }
    programPause();
}

/* Funzione di supporto per aggiungere un prodotto al carrello */
PtrOrder addItemToCart(PtrOrder cart, PtrCatalogue catalogue) {
    int productCode;
    int productQuantity;

    PtrCatalogue catalogueItem = NULL;
    PtrOrder orderItem = NULL;
    bool itemFound = false;
    do {
        clearScreen();
        printTitle();
        printf("Gli elementi nel catalogo di questo periodo sono:\n");
        printItemList(catalogue);
        printf("Inserisci il codice del prodotto desiderato:\n");
        productCode = getInt(0);
        catalogueItem = findElement(catalogue, productCode);
        if (catalogueItem == NULL) {
            printf("Il codice inserito non corrisponde a nessun prodotto in lista. Riprova!\n");
            programPause();            
        }
        
        else itemFound = true;
    } while (!itemFound);

    do {
        printf("Inserisci la quantita' di prodotto da inserire nel carrello:\n");
        productQuantity = getInt(0);
        if (productQuantity < 1) {
            printf("La quantita' deve essere un numero positivo. Riprova!\n");
            programPause();
        } 
    } while (productQuantity < 1);

    orderItem = createNewOrder(catalogueItem->item, productQuantity);

    cart = insertOrderMergeOrEnd(cart, orderItem);
    return cart;
}

/* Funzione di supporto per rimuovere un prodotto dal carrello */
PtrOrder removeItemFromCart(PtrOrder cart) {
    if (cart != NULL) {
        bool itemFound = false;
        int userChoice;
        do {
            clearScreen();
            printTitle();
            printf("Il tuo carrello al momento contiene:\n");
            printOrderList(cart);
            printf("Inserisci il codice prodotto dell'elemento da rimuovere: ");
            userChoice = getInt(0);

            itemFound = findOrder(cart, userChoice);
            if (!itemFound) {
                printf("Il codice inserito non corrisponde a nessun elemento nel carrello! Riprova.\n");
                programPause();
            }
        } while (!itemFound);
    
        cart = removeOrder(cart, userChoice);
    }

    return cart;
}

/* Menu di gestione delle consegne */
void driverDeliveryMenu(Driver driver) {
    int userChoice;
    bool running = true, scenarioChosen = false, repeating = true;

    int startIslandIndex, endIslandIndex, truckWeight;
    Graph archipelago = NULL;
    Edge deliveryPath = NULL;

    do {
        while (!scenarioChosen) {
            clearScreen();
            printTitle();
            printf("Seleziona uno scenario:\n");
            printf("1. Ponti resistenti, tutte le isole sono collegate tra di loro\n");
            printf("2. Tutte le isole sono collegate tra di loro, ma alcuni ponti sono instabili\n");
            printf("3. Alcuni ponti sono instabili, e non tutte le isole sono collegate tra di loro\n");
            printf("\nLa tua scelta: ");
            userChoice = getInt(3);

            /* Carichiamo l'arcipelago corretto */
            switch (userChoice) {
                case 1:
                    archipelago = graph_createSampleGraph1();
                    scenarioChosen = true;
                    break;
                
                case 2:
                    archipelago = graph_createSampleGraph2();
                    scenarioChosen = true;
                    break;
                
                case 3:
                    archipelago = graph_createSampleGraph3();
                    scenarioChosen = true;
                    break;

                default:
                    logMessage("driverDeliveryMenu()", LOG_LEVEL_ERROR, "unreachable end");
                    printf("Scelta sbagliata! Riprovare.\n");
                    programPause();
            }
        }

        clearScreen();
        printTitle();
        /* Prendiamo l'input per l'isola di partenza */
        do {
            printf("Seleziona l'isola di partenza (da 1 a %d): ", ISLAND_NUMBER);
            startIslandIndex = getInt(ISLAND_NUMBER);
            /* getInt restituisce -1 / 0 se l'input inserito non è corretto */
            if (startIslandIndex <= 0) {
                printf("Scelta non corretta! Riprovare.\n");
                programPause();
            }
        } while (startIslandIndex <= 0);
        /* A questo punto decrementiamo startIslandIndex per poterlo utilizzare correttamente nell'algoritmo */
        startIslandIndex--;

        clearScreen();
        printTitle();
        /* Prendiamo l'input per l'isola di arrivo */
        do {
            printf("Seleziona l'isola di arrivo (da 1 a %d): ", ISLAND_NUMBER);
            endIslandIndex = getInt(ISLAND_NUMBER);
            /* getInt restituisce -1 / 0 se l'input inserito non è corretto */
            if (endIslandIndex <= 0) {
                printf("Scelta non corretta! Riprovare.\n");
                programPause();
            }
        } while (endIslandIndex <= 0);
        /* A questo punto decrementiamo endIslandIndex per poterlo utilizzare correttamente nell'algoritmo */
        endIslandIndex--;

        /* Calcoliamo il peso totale del camion */
        truckWeight = getDriverTotalWeight(driver);
        
        /* Calcoliamo, se esiste, un percorso dall'isola di partenza all'isola di arrivo */
        deliveryPath = graph_findShortestPath(archipelago, startIslandIndex, endIslandIndex, truckWeight);

        if (deliveryPath == NULL) {
            printf("Mi dispiace, non esiste un percorso che vada da %d a %d.\n", startIslandIndex+1, endIslandIndex+1);
            programPause();
        }
        else {
            printf("Per arrivare da %d a %d, puoi effettuare questo percorso:\n", startIslandIndex+1, endIslandIndex+1);
            edge_printPath(deliveryPath, 1);
            programPause();
        }

        /* A questo punto diamo la scelta all'utente se continuare o meno */
        do {
            clearScreen();
            printTitle();
            printf("Prego, selezionare un'opzione:\n");
            printf("1. Calcolare un nuovo percorso di consegna\n");
            printf("2. Cambiare tipologia di scenario\n");
            printf("3. Tornare al menu principale\n");
            printf("\nLa tua scelta: ");
            userChoice = getInt(3);

            switch (userChoice)
            {
            case 1: /* Verrà ripetuto il ciclo, escludendo la selezione dello scenario */
                repeating = false;
                scenarioChosen = true; 

                /* Liberiamo la memoria heap */
                edge_freeList(deliveryPath);
                break;
            
            case 2: /* Verrà ripetuto il ciclo interamente */
                repeating = false;
                scenarioChosen = false;
                
                /* Liberiamo la memoria heap */
                graph_free(archipelago);
                edge_freeList(deliveryPath);
                break;

            case 3: /* Il ciclo verrà interrotto */
                repeating = false;
                running = false;

                /* Liberiamo la memoria heap */
                graph_free(archipelago);
                edge_freeList(deliveryPath);

                printf("Ora tornerai al menu principale.\n");
                programPause();
                break;

            default:
                logMessage("driverDeliveryMenu()", LOG_LEVEL_ERROR, "unreachable end");
                printf("Scelta non corretta! Riprovare.\n");
                programPause();
                break;
            }
        } while (repeating);
    } while (running);
}





