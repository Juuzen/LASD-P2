#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void programPause() {
    getchar();
}

void clearScreen() {
    #ifdef _WIN32
    /* Istruzioni per sistema operativo Windows */
    system("cls");
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
        if (maxRange == 0) input = tmp;
        else if ((tmp > 0) && (tmp <= maxRange)) {
            input = tmp;
        }
        else input = 0;
    }
    else input = -1;
    return input;
}

void utilsDebugTest() {
    int input = -1;
    do {
        clearScreen();
        printf("Scegli un numero da 1 a 10: ");
        input = getInt(10);
        if (input <= 0) {
            printf("Scelta sbagliata, riprovare\n");
            programPause();
        }
    } while (input <= 0);

    
    printf("Il numero scelto e': %d\n", input);
}