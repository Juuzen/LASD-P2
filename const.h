#ifndef const_h
#define const_h

/* Used in: productCatalogue.c */
#define MAX_ITEM_LABEL_SIZE 21
#define METHOD_CATALOGUE_RETRIEVE_ITEM_FROM_FILE "retrieveItemsFromCatalogueFile()"

/* Used in: authlib.c */
#define MAX_SIZE_USERNAME 12
#define MAX_SIZE_PASSWORD 12
#define METHOD_AUTH_DO_LOGIN "doLogin()"
#define METHOD_AUTH_DO_REGISTRATION "doRegistration()"
#define METHOD_AUTH_CHECK_USERNAME "checkIfUsernameAlreadyExists()"

/* Used in: graph.c*/
#define NODELIMIT 20
#define ISLAND_NUMBER 17

/* Used in: driver.c */
#define METHOD_DRIVER_RETRIEVE_DRIVER_INFO "retrieveDriverInfoFromFile()"
#define METHOD_DRIVER_WRITE_DRIVER_INFO "writeDriverInfoToFile()"
#define METHOD_DRIVER_CALCULATE_TOTAL_WEIGHT "getDriverTotalWeight()"
#define MAX_LENGTH_DRIVER_CODE 10

/* Used in: logger.c */
#define LOG_FILE "lasdp.log"

/* Used in: ui.c */
#define METHOD_REGISTRATION_MENU "registrationMenu()"
#define METHOD_PROJECT_RUN "projectRun()"
#define METHOD_DRIVER_MENU "driverMenu()"
#define METHOD_DRIVER_SHOP_MENU "driverShopMenu()"

#define LOG_LEVEL_INFO "INFO"
#define LOG_LEVEL_DEBUG "DEBUG"
#define LOG_LEVEL_ERROR "ERROR"

/* Used in: project.c */
#define DRIVER_INFO_DB "driver-info.isl"
#define DRIVER_LOGIN_DB "driver-auth-info.isl"
#define PRODUCT_CATALOGUE_DB "items-catalogue.isl"

#define CLEAR_SCREEN_METHOD "clearScreen()"

#endif 