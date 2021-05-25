//
// Created by backs on 20/05/2021.
//

#include "stdio.h"
#include "logger.h"
#include "time.h"
#include "string.h"
#include "const.h"

/*
 * Usage:
 *      method -> method name defined in const.h
 *      log level -> constant defined in const.h, choose between INFO, DEBUG or ERROR
 *      message -> custom message
 */
void logMessage(char *method, char *logLevel, char *message) {
    FILE *logFile = NULL;

    time_t rawTime;
    struct tm *timeInfo;
    char stringTime[80];

    logFile = fopen(LOG_FILE, "a");

    time (&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(stringTime, 80, "%Y-%m-%d %H:%M:%S", timeInfo);

    fprintf(logFile, "%s - %s - %s - %s\n", stringTime, logLevel, method, message);

    fclose(logFile);
}