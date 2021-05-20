//
// Created by backs on 20/05/2021.
//

#ifndef LASD_P2_LOGGER_H
#define LASD_P2_LOGGER_H

#define LOG_FILE "lasdp.log"

#define LOG_LEVEL_INFO "INFO"
#define LOG_LEVEL_DEBUG "DEBUG"
#define LOG_LEVEL_ERROR "ERROR"

/*
 * USAGE GUIDE:
 *      Theoretically, every header should have a definition in the style of
 *      #DEFINE [METHOD]_METHOD_NAME "METHOD NAME" to use as first paramenter
 *      second parameter is the log message
 *      third parameter is the expected behaviour
 *          0 - Writes only on stderr
 *          1 - Writes only on file
 *          2 - Writes both on stderr or file
 */
void logMessage(char *method, char *logLevel, char *message, int writeOnFile);

#endif //LASD_P2_LOGGER_H
