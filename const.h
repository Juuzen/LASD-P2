#ifndef const_h
#define const_h

/* Used in: productCatalogue.c */
#define MAX_ITEM_LABEL_SIZE 21

/* Used in: authlib.c */
#define MAX_SIZE_USERNAME 12
#define MAX_SIZE_PASSWORD 12

/* Used in: graph.c*/
#define NODELIMIT 20

/* Used in: driver.c */
#define METHOD_TEST "retrieveDriverInfoFromFile()"
#define WRITE_DRIVER_FILE_METHOD "writeDriverInfoToFile()"

/* Used in: logger.c */
#define LOG_FILE "lasdp.log"

#define LOG_LEVEL_INFO "INFO"
#define LOG_LEVEL_DEBUG "DEBUG"
#define LOG_LEVEL_ERROR "ERROR"

/* Used in: project.c */
#define DRIVER_INFO_DB "driverDB.txt"
#define DRIVER_LOGIN_DB "registrazione.txt"
#define PRODUCT_CATALOGUE_DB "catalogue.txt"

#endif 