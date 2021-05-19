//
// Created by backs on 20/05/2021.
//

#include "stdio.h"
#include "logger.h"
#include "time.h"

void logMessage(char *method, char *message, int writeOnFile) {
    FILE *logFile = NULL;

    time_t rawTime;
    struct tm *timeInfo;
    char stringTime[80];

    if (writeOnFile == 1 || writeOnFile == 2) {
        logFile = fopen(LOG_FILE, "a");
    }

    time (&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(stringTime, 80, "%Y-%m-%d %H:%M:%S", timeInfo);

    if (writeOnFile == 0) {
        fprintf(stderr, "%s - %s - %s\n", stringTime, method, message);
    } else if (writeOnFile == 1 && logFile != NULL) {
        fprintf(logFile, "%s - %s - %s\n", stringTime, method, message);
    } else if (writeOnFile == 2 && logFile != NULL) {
        fprintf(stderr, "%s - %s - %s\n", stringTime, method, message);
        fprintf(logFile, "%s - %s - %s\n", stringTime, method, message);
    }
}