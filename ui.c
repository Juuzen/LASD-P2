#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ui.h"
#include "authlib.h"
#include "driver.h"
#include "productCatalogue.h"
#include "orderManagement.h"

void mainMenu() {
    int userChoice = -1;

    do {
        //TODO: Pulizia schermo
        printf("Benvenuto, selezionare il servizio richiesto:\n");
        printf("1. AUTENTICAZIONE\n");
        printf("2. REGISTRAZIONE\n");
        printf("3. USCITA DAL PROGRAMMA\n\n");
        printf("La tua scelta: ");
        scanf("%i", &userChoice); //TODO: input pulito

        switch (userChoice) {
        case 1:
            authenticationMenu();
            break;
        
        case 2:
            registrationMenu();
            break;
        
        case 3:
            printf("Ok ciao arrivederci\n");
            break;

        default:
            printf("Scelta non corretta! Riprovare\n");
        }
    } while (userChoice == -1);
    
}

void registrationMenu() {
    int weight, registrationCheck;
    bool running = true;

    do {
        char username[MAX_SIZE_USERNAME];
        char password[MAX_SIZE_PASSWORD];
        printf("Inserisci username:\n");
        scanf("%s", username); // TODO: Input pulito
        printf("\nInserisci password:\n");
        scanf("%s", password); // TODO: Input pulito

        registrationCheck = doRegistration(username, password, DRIVER_LOGIN_DB);
        switch (registrationCheck) {
            case -2:
                //TODO: Aggiungere logger
                printf("L'username e' gia' presente nel sistema! Riprovare con un nuovo username?\n");
                //TODO: Chiedere se vuole riprovare
                //TODO: Funzione di pausa
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

                Driver driver;
                strcpy(driver.driverCode, username);
                driver.truckWeight = weight;

                writeDriverInfoToFile(driver, DRIVER_INFO_DB);
                printf("Registrazione completata con successo! Ora puo' tornare al menu principale.\n");
                running = false;
                break;

            default:
            //The user shouldn't be here
            //TODO: Chiamare logger
                running = false;
        }
    } while (running);
}

PtrOrder addToCart(PtrCatalogue catalogue){

    int productCode;
    int quantity;

    printf("\nInserisci il codice del prodotto desiderato:\n");
    scanf("%d",&productCode);


    while(productCode<111 || productCode>121){
        printf("\nProdotto non disponibile\n");
        printf("\nInserisci il codice del prodotto desiderato:\n");
        scanf("%d",&productCode);
    }

    printf("\nIn che quantita'?\n");
    scanf("%d",&quantity);

    PtrCatalogue find = NULL;
    find = findElement(catalogue,productCode);

    PtrOrder singleElement = NULL;
    singleElement = createNewOrder(find->item,quantity);

    return singleElement;

}

void showCartInfo(Driver driver, PtrOrder cart) {
    printf("\n*** RIEPILOGO ORDINI ***\n\n");
    printOrderList(cart);
    printf("\n*** PESO TOTALE ORDINE ***\n");

    int cartWeight = calculateOrderWeight(cart);
    printf("\npeso netto : %d", cartWeight);
    printf("\npeso lordo : %d", cartWeight + driver.truckWeight);
}

void driverShopMenu(Driver driver) {
    bool running = true;
    int userChoice = -1;

    PtrCatalogue catalogue = NULL;
    PtrOrder cart = NULL; // richiamare il carrello del driver
    do {
        //TODO: pulizia schermo
        openShopList();

        printf("Seleziona un'opzione:\n");
        printf("1. AGGIUNGI UN PRODOTTO AL CARRELLO\n");
        printf("2. VISUALIZZARE CARRELLO\n");
        printf("3. RIMUOVERE UN PRODOTTO DAL CARRELLO\n"); // da fare?
        printf("4. CONFERMARE L'ORDINE\n\n");
        printf("La tua scelta: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                catalogue = retrieveItemsFromCatalogueFile("catalogue.txt");
                do {
                    //Racchiudere tutto in un unica funzione?
                    PtrOrder item = NULL;
                    item = addToCart(catalogue);
                    cart = insertOrderOnEnd(cart, item);
                    printf("Articolo inserito! Seleziona un'opzione:\n");
                    printf("1. AGGIUNGI UN NUOVO PRODOTTO\n");
                    printf("2. TORNA INDIETRO\n\n");
                    printf("La tua scelta: ");
                    scanf("%d", &userChoice); //TODO: input pulito
                    switch (userChoice) {
                    case 1:
                        userChoice = -1; //FIXME: togliere questa istruzione tampone
                        break;
                    
                    // non è necessario fare nulla per il caso 2
                    default:
                        break;
                    }
                } while (userChoice == -1);
                //funzione di aggiunta al carrello
                userChoice = 1; //FIXME: rimuovere questa istruzione tampone
                break;

            case 2:
                showCartInfo(driver, cart);
                break;

            case 3:
                //funzione di rimozione del prodotto dal carrello
                break;

            case 4:
                //salvataggio ordine
                running = false;
                break;

            default:
                //TODO: chiamare logger
                printf("Non e' possibile procedere alle operazioni del carrello, riprovare piu' tardi.\n");
                //TODO: funzione di pausa
                running = false;
        }
    } while (running);
}

//TODO: da fare
void driverDeliveryMenu() {

}

void driverMenu(Driver driver) {
    int userChoice = -1;
    do {
        //TODO: Pulizia schermo
        printf("Benvenuto, driver %s!\n", driver.driverCode);
        printf("Seleziona il servizio che vuoi richiedere:\n");
        printf("1. EFFETTUARE LA SPESA\n");
        printf("2. EFFETTUARE UNA CONSEGNA\n");
        printf("3. EFFETTUARE LOGOUT\n\n");
        printf("La tua scelta: ");
        scanf("%d", &userChoice); // TODO: Input pulito

        switch (userChoice){
        case 1:
            driverShopMenu(driver);
            break;
        
        case 2:
            driverDeliveryMenu();
            break;
        
        case 3:
            printf("Grazie mille arrivederci\n");
            break;

        default:
            printf("Scelta sbagliata! Riprovare\n");
            userChoice = -1; //TODO: rimuovere questa patchaid
        }
    } while (userChoice == -1);
}

void authenticationMenu() {
    int loginCheck;
    bool running = true;
    char username[MAX_SIZE_USERNAME];
    char password[MAX_SIZE_PASSWORD];

    do {
        printf("Inserisci username:\n");
        scanf("%s", username); //TODO: Input pulito
        printf("\nInserisci password:\n");
        scanf("%s", password); //TODO: Input pulito

        loginCheck = doLogin(username, password, DRIVER_LOGIN_DB);

        if (loginCheck == 1) {
            Driver driver; //FIXME: sostituire con il recupero dei dati del driver
            driverMenu(driver);
        } else { 
            printf("Le credenziali sono errate! Prego riprovare...\n");
            //TODO: Chiedere se voler uscire oppure no
            //TODO: Funzione di pausa
        }
    } while (running);
}


// le informazioni del driver non dovrebbero già essere disponibili?
/*
int recoverTruckWeight(char *username){
    char localFetchUsername[MAX_ITEM_LABEL_SIZE];
    int localFetchTruckWeight;
    FILE *fp = fopen("driverDB.txt","r");

    int fScanfResult = fscanf(fp, "%s\t%d\n", localFetchUsername, &localFetchTruckWeight);
    if (fScanfResult == 2) {
        int usernameResultCheck = strcasecmp(username, localFetchUsername);
        if (usernameResultCheck == 0) {
            return localFetchTruckWeight;
        }
    }
}
*/