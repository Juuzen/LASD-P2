#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "driver.h"
#include "auth.h"
#include "const.h"
#include "logger.h"

/*
 *  MAX_SIZE_USERNAME e MAX_SIZE_PASSWORD vengono usati + 1 
 *  per accomodare il carattere di terminazione '\0'
 */

/*  Effettua il processo di accesso.
 *  Output:
 *  -1  ERRORE: File inesistente
 *  -2  ERRORE: Input non validi
 *   0  ERRORE: Username inesistente
 *   1  Login avvenuto con 
 *   2  ERRORE: Wrong password
 */
int auth_login (char *username, char *password, char *filename) {

    FILE *loginFile = NULL;
    int resultCheck = 0;    //Stores result of check for login, base case for not found username

    // Sanity check su input passati alla funzione
    if (username == NULL || password == NULL || filename == NULL) {
        logMessage(METHOD_AUTH_LOGIN, LOG_LEVEL_ERROR, "Error in input variables");
        return -2;
    }

    loginFile = fopen(filename, "r");

    // Sanity check sull'apertura del file
    if (loginFile == NULL) {
        logMessage(METHOD_AUTH_LOGIN, LOG_LEVEL_ERROR, "Error opening file");
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

/*  Effettua il processo di registrazione.
 *  Output:
 *  -1  ERRORE: File inesistente
 *  -2  ERRORE: Input non validi
 *   1  Registrazione avvenuta con successo
 */
int auth_register (char *username, char *password, char *filename) {
    if (username == NULL || password == NULL || filename == NULL) {
        logMessage(METHOD_AUTH_REGISTRATION, LOG_LEVEL_ERROR, "Error in input variables");
        return -1;
    }

    if (auth_checkExistingUsername(username, filename) == 1) {
        logMessage(METHOD_AUTH_REGISTRATION, LOG_LEVEL_INFO, "Username already exists");
        return -2;
    }

    FILE *registrationFile = NULL;

    registrationFile = fopen(filename, "a+");

    // Sanity check su file nullo
    if (registrationFile == NULL) {
        logMessage(METHOD_AUTH_REGISTRATION, LOG_LEVEL_ERROR, "Error opening auth file");
        return -1;
    }

    fprintf(registrationFile, "%s\t%s\n", username, password);

    fclose(registrationFile);

    return 1;
}

/*  Controlla che non sia presente su file lo stesso username passato in ingresso.
 *  Output:
 *  0  Username non trovato
 *  1  Username trovato con successo
 */
int auth_checkExistingUsername (char *username, char *filename) {

    FILE *registrationFile = NULL;

    if (filename == NULL || username == NULL) {
        logMessage(METHOD_AUTH_CHECK_USERNAME, LOG_LEVEL_ERROR, "Error in input variables");
        return -1;
    }

    registrationFile = fopen(filename, "r");

    if (registrationFile == NULL) {
        logMessage(METHOD_AUTH_CHECK_USERNAME, LOG_LEVEL_ERROR, "Error opening file");
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
