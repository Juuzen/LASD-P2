//
// Created by backs on 18/05/2021.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "driver.h"
#include "authlib.h"
#include "const.h"

/*
 *  MAX_SIZE_USERNAME e MAX_SIZE_PASSWORD vengono usati + 1 per accomodare il carattere di terminazione '\0'
 */

/*
 * Error codes:
 *      -1  File inesistente
 *      -2  Input non validi
 *       0  Username inesistente
 *       1  Login successful
 *       2  Wrong password
 */

int doLogin(char *username, char *password, char *filename) {

    FILE *loginFile = NULL;
    int resultCheck = 0;    //Stores result of check for login, base case for not found username

    // Sanity check su input passati alla funzione
    if (username == NULL || password == NULL || filename == NULL) {
        return -2;
    }

    loginFile = fopen(filename, "r");

    // Sanity check sull'apertura del file
    if (loginFile == NULL) {
        return -1;
    }


    while (feof(loginFile) == 0 && resultCheck == 0) {
        char localFetchUsername[MAX_SIZE_USERNAME + 1];
        char localFetchPassword[MAX_SIZE_PASSWORD + 1];
        int fScanfResult = fscanf(loginFile, "%s\t%s\n", localFetchUsername, localFetchPassword);
        if (fScanfResult == 2) {
            int usernameResultCheck = strcasecmp(username, localFetchUsername);
            if (usernameResultCheck == 0) {
                int passwordCheck = strcmp(password, localFetchPassword);
                if (passwordCheck == 0) {
                    resultCheck = 1;    //Login successful
                } else resultCheck = 2; //Wrong password
            }
        }
    }

    fclose(loginFile);

    return resultCheck;
}

int doRegistration(char *username, char *password, int peso, char *filename) {
    if (username == NULL || password == NULL || peso == 0 || filename == NULL) {
        return -1;
    }

    if (checkIfUsernameAlreadyExists(username, filename) == 1) {
        return -2;
    }

    FILE *registrationFile = NULL;

    registrationFile = fopen(filename, "a+");

    // Sanity check su file nullo
    if (registrationFile == NULL) {
        return -1;
    }

    fprintf(registrationFile, "%s\t%s\t%d\n", username, password, peso);

    fclose(registrationFile);

    return 0;
}

//  Returns 1 if username already exists, 0 otherwise
int checkIfUsernameAlreadyExists(char *username, char *filename) {

    FILE *registrationFile = NULL;

    if (filename == NULL || username == NULL) {
        return -1;
    }

    registrationFile = fopen(filename, "r");

    if (registrationFile == NULL) {
        return -1;
    }

    int foundUsername = 0;

    while (feof(registrationFile) == 0 && foundUsername == 0) {
        char scannedUsername[20];
        char scannedPassword[20];
        int scannedElements = fscanf(registrationFile, "%s\t%s\n", scannedUsername, scannedPassword);

        if (scannedElements == 2) {
            if(strcasecmp(scannedUsername, username) == 0) {
                foundUsername = 1;
            }
        }
    }

    fclose(registrationFile);

    return foundUsername;
}
