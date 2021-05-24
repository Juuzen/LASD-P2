#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ui.h"
#include "const.h"
#include "authlib.h"
#include "driver.h"
#include "productCatalogue.h"
#include "orderManagement.h"
#include "utils.h"

/* Entry point del progetto */
void mainMenu() {
    int userChoice;
    bool running = true;

    do {
        clearScreen();
        printf("Benvenuto, selezionare il servizio richiesto:\n");
        printf("1. AUTENTICAZIONE\n");
        printf("2. REGISTRAZIONE\n");
        printf("3. USCITA DAL PROGRAMMA\n\n");
        printf("La tua scelta: ");
        userChoice = getInt(3);

        switch (userChoice) {
        case 1: // autenticazione
            authenticationMenu();
            break;
        
        case 2: // registrazione
            registrationMenu();
            break;
        
        case 3: // uscita dal programma
            printf("Ok ciao arrivederci\n"); //TODO: Abbellire il testo
            running = false;
            break;

        default: // errore
            //TODO: chiamare logger
            printf("Scelta non corretta! Riprovare\n");
            programPause();
        }
    } while (running);
    
}

/* Menu di autenticazione*/
void authenticationMenu() {
    int loginCheck, userChoice;
    bool running = true;

    char username[MAX_SIZE_USERNAME];
    char password[MAX_SIZE_PASSWORD];
    do {
        clearScreen();
        printf("Inserisci username:\n");
        scanf("%s", username); //TODO: Input pulito
        printf("\nInserisci password:\n");
        scanf("%s", password); //TODO: Input pulito

        loginCheck = doLogin(username, password, DRIVER_LOGIN_DB);

        if (loginCheck == 1) {
            Driver driver;
            int driverCheck = retrieveDriverInfoFromFile(username, DRIVER_INFO_DB, &driver);
            if (driverCheck == 1) {
                driver.truckLoad = NULL; //FIXME: Questa cosa deve andare all'inizializzazione del driver
                driverMenu(driver);
            }
            else {
                printf("Non e' stato possibile recuperare le informazioni del driver, riprovare piu' tardi...\n");
                //TODO: Chiamare logger
                
            }
            running = false; // Per evitare che venga ripetuta l'autenticazione dopo essere usciti
        } else { 
            printf("Le credenziali sono errate! Seleziona una opzione:\n");
            printf("1. RIPETERE L'AUTENTICAZIONE\n");
            printf("2. TORNA INDIETRO\n\n");
            printf("La tua scelta: ");
            userChoice = getInt(2);
            switch (userChoice){
            case 1: // Non è necessario fare nulla nel caso si voglia ripetere con l'autenticazione
                break;
            
            default:
                //FIXME: Fare distinguo tra caso 2 e caso di errore?
                running = false;
                break;
            }
        }
    } while (running);
}

/* Menu di registrazione */
void registrationMenu() {
    int weight, registrationCheck, userChoice;
    char username[MAX_SIZE_USERNAME];
    char password[MAX_SIZE_PASSWORD];
    bool running = true;

    do {
        clearScreen();
        printf("Inserisci username:\n");
        scanf("%s", username); // TODO: Input pulito
        printf("Inserisci password:\n");
        scanf("%s", password); // TODO: Input pulito

        registrationCheck = doRegistration(username, password, DRIVER_LOGIN_DB);
        switch (registrationCheck) {
            case -2:
                //TODO: Aggiungere logger
                printf("L'username e' gia' presente nel sistema!\n");
                printf("Selezionare una opzione:\n");
                printf("1. RIPETERE LA REGISTRAZIONE\n");
                printf("2. TORNA INDIETRO\n\n");
                printf("La tua scelta: ");
                userChoice = getInt(2);
                switch (userChoice) {
                case 1: // Non è necessario fare nulla nel caso si voglia ripetere con l'autenticazione
                    break;
                
                default:
                    //FIXME: Fare distinguo tra caso 2 e caso di errore?
                    running = false;
                    break;
                }
                break;
            
            // Problema di accesso ai file interni
            case -1:
                //TODO: Aggiungere logger
                printf("Non e' possibile proseguire con la registrazione. Riprovare piu' tardi.\n");
                running = false;
                //TODO: Funzione di pausa
                break;

            // Registrazione avvenuta con successo, si procede con il salvataggio dei dati del driver
            case 1:
                printf("Inserisci il peso del tuo veicolo per le consegne:\n");
                scanf("%d", &weight); //TODO: Input pulito

                //TODO: Questa struct driver è un po' ridondante, rimuoverla?
                Driver driver;
                strcpy(driver.driverCode, username);
                driver.truckWeight = weight;

                writeDriverInfoToFile(driver, DRIVER_INFO_DB);
                printf("Registrazione completata con successo! Ora puo' tornare al menu principale.\n");
                programPause();
                running = false;
                break;

            default:
            //The user shouldn't be here
            //TODO: Chiamare logger
                running = false;
        }
    } while (running);
}

/* Menu personale del driver */
void driverMenu(Driver driver) {
    int userChoice;
    bool running = true; 

    do {
        clearScreen();
        printf("Benvenuto, driver %s!\n", driver.driverCode);
        printf("Seleziona il servizio che vuoi richiedere:\n");
        printf("1. EFFETTUARE LA SPESA\n");
        printf("2. EFFETTUARE UNA CONSEGNA\n");
        printf("3. EFFETTUARE LOGOUT\n\n");
        printf("La tua scelta: ");
        userChoice = getInt(3);

        switch (userChoice){
        case 1:
            driverShopMenu(&driver);
            break;
        
        case 2:
            //driverDeliveryMenu(driver);
            printf("Funzione non ancora disponibile!\n");
            programPause();
            break;
        
        case 3:
            printf("Grazie mille arrivederci\n"); //TODO: Abbellire il testo
            programPause();
            running = false;
            break;

        default:
            printf("Scelta sbagliata! Riprovare\n"); //TODO: Abbellire il testo
            programPause();
            //TODO: chiamare logger
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
        printf("Seleziona un'opzione:\n");
        printf("1. AGGIUNGI UN PRODOTTO AL CARRELLO\n");
        printf("2. VISUALIZZARE CARRELLO\n");
        printf("3. RIMUOVERE UN PRODOTTO DAL CARRELLO\n"); // da fare?
        printf("4. CONFERMARE L'ORDINE\n");
        printf("5. ANNULLARE L'ORDINE\n");
        printf("\n");
        printf("La tua scelta: ");
        userChoice = getInt(5);

        switch (userChoice) {
            case 1: // aggiunta di un prodotto al carrello
                do {
                    //Racchiudere tutto in un unica funzione?
                    cart = addToCart(cart, catalogue);

                    printf("Articolo inserito! Seleziona un'opzione:\n");
                    printf("1. AGGIUNGI UN NUOVO PRODOTTO\n");
                    printf("2. TORNA INDIETRO\n\n");
                    printf("La tua scelta: ");
                    userChoice = getInt(2);
                    switch (userChoice) {
                    case 1:
                        userChoice = -1; //FIXME: togliere questa istruzione tampone
                        break;
                    
                    // non è necessario fare nulla per il caso 2
                    default:
                        break;
                    }
                } while (userChoice == -1);
                break;

            case 2: // stato del carrello
                showCartInfo((*driver), cart);
                programPause();
                break;

            case 3: // rimozione di un prodotto dal carrello
                printf("Funzione non ancora implementata!\n");
                programPause();
                break;

            case 4: //salvataggio ordine
                (*driver).truckLoad = mergeLists((*driver).truckLoad, cart);
                freeOrderList(cart);
                printf("Carrello caricato con successo nel camion!\n");
                programPause();
                running = false;
                break;

            case 5: //annullamento ordine
                freeOrderList(cart);
                printf("Nessuna modifica e' stata effettuata!\n");
                programPause();
                running = false;
                break;

            default:
                //TODO: chiamare logger
                printf("Non e' possibile procedere alle operazioni del carrello, riprovare piu' tardi.\n");
                programPause();
                running = false;
        }
    } while (running);
}

/* Funzione di supporto per aggiungere un prodotto al carrello */
PtrOrder addToCart(PtrOrder cart, PtrCatalogue catalogue) {
    int productCode;
    int productQuantity;

    PtrCatalogue catalogueItem = NULL;
    PtrOrder orderItem = NULL;
    bool itemFound = false;
    do {
        clearScreen();
        print(catalogue);
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
        clearScreen();
        printf("Inserisci la quantita':\n");
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

/* Funzione di supporto per mostrare il carrello */
void showCartInfo(Driver driver, PtrOrder cart) {
    clearScreen();
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
    printf("Premere INVIO per tornare indietro.");
}

/* Menu di gestione delle consegne */
void driverDeliveryMenu(Driver driver) {
    //TODO: da fare
}
