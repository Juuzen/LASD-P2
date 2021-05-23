//
// Created by gianl on 21/05/2021.
//

#include "UI.h"
#include "authlib.h"
#include "driver.h"
#include "stdlib.h"
#include "stdio.h"
#include "productCatalogue.h"
#include "orderManagement.h"
#include "string.h"


void mainMenu() {

    char username[20];
    char password[20];
    FILE *fp = NULL;
    int check,peso,exitcode = 1;
    char selection;
    PtrOrder order = NULL;
    PtrCatalogue catalogue = NULL;
    int selection2,selection3,truckTotalWeight = 0;

    printf("Benvenuto, selezionare il servizio richiesto\n1 per autentificazione\n2 per registrazione\nPremere qualsiasi tasto per uscire...\n");
    scanf("%c", &selection);

    switch (selection) {
        case '1':
            // open autentication
            printf("Inserisci username:\n");
            scanf("%s", username);
            printf("\nInserisci password:\n");
            scanf("%s", password);

            check = doLogin(username, password, "registrazione.txt");

            if (check != 1) {
                printf("Autentificazione fallita\nPrego riprovare");

            } else {
                printf("\nBenvenuto %s!\nSelezionare il servizio richiesto\n1 per visualizzare l'elenco dei prodotti disponibili\n0 per uscire\n",
                       username);
                scanf("%d", &selection2);

                while (selection2 < 0 || selection2 > 1) {
                    printf("\nSelezione non valida!\nPrego riprovare\n");
                    printf("1 per visualizzare l'elenco dei prodotti disponibili\n2 per boh\nPremere qualsiasi tasto per uscire\n");
                    scanf("%d", &selection2);
                }

                if (selection2 == 1) {

                    openShopList();

                    printf("\nVuoi aggiungere prodotti al carrello?\n1 per procedere\n2 per uscire\n");
                    scanf("%d",&selection3);

                    while(selection3<1 || selection3>2){
                        printf("\nSelezione non valida!\nPrego riprovare\n");
                        printf("\nVuoi aggiungere prodotti al carrello?\n1 per continuare\n2 per uscire\n");
                        scanf("%d",&selection3);
                    }

                    if(selection3 == 1){

                        catalogue = retrieveItemsFromCatalogueFile("catalogue.txt");

                        while(exitcode!=0) {

                            PtrOrder single = NULL;
                            single = addToCart(catalogue);

                            order = insertOrderOnEnd(order, single);
                            printf("\nVuoi continuare?\n1 per continuare\n0 per chiudere il carrello\n");
                            scanf("%d",&exitcode);

                        }

                        printf("\n*** RIEPILOGO ORDINI ***\n\n");
                        printOrderList(order);
                        printf("\n*** PESO TOTALE ORDINE ***\n");

                        truckTotalWeight = truckTotalWeight + calculateOrderWeight(order);
                        printf("\npeso netto : %d",truckTotalWeight);
                        truckTotalWeight = truckTotalWeight + recoverTruckWeight(username);
                        printf("\npeso lordo : %d", truckTotalWeight);


                    }else{
                        printf("\nArrivederci!\n");
                        system("PAUSE");
                        exit(0);
                    }

                    break;

                    case '2':
                        // Open registration section
                        printf("Inserisci username:\n");
                    scanf("%s", username);
                    printf("\nInserisci password:\n");
                    scanf("%s", password);
                    printf("Inserisci il peso del tuo veicolo per le consegne:\n");
                    scanf("%d", &peso);

                    doRegistration(username, password, peso, "registrazione.txt");

                    Driver driver;
                    strcpy(driver.driverCode,username);
                    driver.truckWeight = peso;

                    writeDriverInfoToFile(driver,"driverDB.txt");

                    fclose(fp);

                    printf("\nGrazie, la sua registrazione e' stata effettuata con successo\nOra puo' accedere al suo account\n");
                    break;

                    default:
                        printf("Arrivederci\n");
                        system("PAUSE");
                        exit(0);

                }else{
                    printf("\nGrazie e arrivederci!\n");
                    system(("PAUSE"));
                    exit(0);
                }

            }
    }
}

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