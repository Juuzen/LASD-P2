#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "logger.h"
#include "const.h"

/* Stampa su stdout il banner della società. */
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

/* Mette in pausa l'input, riprende premendo il tasto INVIO. */
void programPause() {
    printf("Premi INVIO per continuare...");
    getchar();
}

/* Pulisce la finestra del terminale (con funzioni OS-based). */
void clearScreen() {
    #ifdef _WIN32
    /* Istruzioni per sistema operativo Windows */
    system("cls");
    // Commentata out perchè sporcava troppo i log
    //logMessage(CLEAR_SCREEN_METHOD, LOG_LEVEL_DEBUG, "Cleared screen");
    #endif

    #ifdef __linux__
    /* Istruzioni per sistema operativo Linux */
    system("clear");
    #endif
}

/* Svuota lo stdin. */
void flushStdin() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/*  Prende da stdin un valore intero compreso tra 0 e maxRange (se questo è specificato).
 *  Output codes: 
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

/*  Prende da stdin una stringa, compresa di whitespace. 
 *  Output:
 *  char *scan = la stringa correttamente letta in ingresso.
 */
char * getString(size_t maxChar) {
    int i = 0;
    char c;
    char * scan = (char *) malloc(maxChar * sizeof(char));
    while (((c = fgetc(stdin)) != EOF) && c != '\n' && i < maxChar) {
        scan[i] = c;
        i++;
    }
    //flushStdin();
    return scan;

}