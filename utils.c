#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "logger.h"
#include "const.h"

void printTitle() {
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("'####::::::::::'########::::'###::::'########::'######::\n");
    printf(". ##::::::::::: ##.....::::'## ##:::... ##..::'##... ##:\n");
    printf(": ##::::::::::: ##::::::::'##:. ##::::: ##:::: ##:::..::\n");
    printf(": ##::'#######: ######:::'##:::. ##:::: ##::::. ######::\n");
    printf(": ##::........: ##...:::: #########:::: ##:::::..... ##:\n");
    printf(": ##::::::::::: ##::::::: ##.... ##:::: ##::::'##::: ##:\n");
    printf("'####:::::::::: ########: ##:::: ##:::: ##::::. ######::\n");
    printf("....:::::::::::........::..:::::..:::::..::::::......:::\n");
    printf("\n\n");
}

void programPause() {
    printf("Premi INVIO per continuare...");
    getchar();
}

void clearScreen() {
    #ifdef _WIN32
    /* Istruzioni per sistema operativo Windows */
    system("cls");
    logMessage(CLEAR_SCREEN_METHOD, LOG_LEVEL_DEBUG, "Cleared screen");
    #endif

    #ifdef __linux__
    /* Istruzioni per sistema operativo Linux */
    system("clear");
    #endif
}

void flushStdin() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/* Output codes: 
 *  -1: error in reading from input (bad input)
 *   0: out of bounds input
 *  1+: input read successfully (range (0; maxRange])
 */
int getInt(int maxRange) {
    int tmp, input, scanfCheck;

    scanfCheck = (scanf("%d", &tmp));
    flushStdin();
    if (scanfCheck == 1) {
        if (maxRange == 0) {
            if (tmp > 0) input = tmp;
            else input = 0;
        }
        else if ((tmp > 0) && (tmp <= maxRange)) {
            input = tmp;
        }
        else input = 0;
    }
    else input = -1;
    return input;
}

char * getString(int maxChar) {
    int i = 0;
    char c;
    char * scan = (char *) calloc(1, maxChar * sizeof(char));
    while (((c = fgetc(stdin)) != EOF) && c != '\n' && i < maxChar) {
        scan[i] = c;
        i++;
    }
    //flushStdin();
    return scan;

}