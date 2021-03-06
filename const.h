#ifndef const_h
#define const_h

/* Used in: order.c */
#define MAX_ORDER_QUANTITY 1000

/* Used in: catalogue.c */
#define MAX_ITEM_LABEL_SIZE 21
#define METHOD_CATALOGUE_RETRIEVE_LIST_FROM_FILE "catalogue_retrieveListFromFile()"
#define METHOD_CATALOGUE_MOCK_FILE "catalogue_mockCatalogueFile()"

/* Used in: auth.c */
#define MAX_SIZE_USERNAME 12
#define MAX_SIZE_PASSWORD 12
#define METHOD_AUTH_LOGIN "auth_login()"
#define METHOD_AUTH_REGISTRATION "auth_register()"
#define METHOD_AUTH_CHECK_USERNAME "auth_checkExistingUsername()"

/* Used in: graph.c*/
#define NODELIMIT 20
#define ISLAND_NUMBER 17

/* Used in: driver.c */
#define METHOD_DRIVER_RETRIEVE_DRIVER_INFO "retrieveDriverInfoFromFile()"
#define METHOD_DRIVER_WRITE_DRIVER_INFO "writeDriverInfoToFile()"
#define METHOD_DRIVER_CALCULATE_TOTAL_WEIGHT "getDriverTotalWeight()"
#define MAX_LENGTH_DRIVER_CODE 10

/* Used in: logger.c */
#define LOG_FILE "i-eats.log"
#define LOG_LEVEL_INFO "INFO"
#define LOG_LEVEL_DEBUG "DEBUG"
#define LOG_LEVEL_ERROR "ERROR"

/* Used in: ui.c */
#define METHOD_REGISTRATION_MENU "registrationMenu()"
#define METHOD_PROJECT_RUN "projectRun()"
#define METHOD_DRIVER_MENU "driverMenu()"
#define METHOD_DRIVER_SHOP_MENU "driverShopMenu()"
#define METHOD_DRIVER_DELIVERY_MENU "driverDeliveryMenu()"
#define METHOD_REMOVE_ITEM_FROM_CART "removeItemFromCart()"
#define METHOD_ADD_ITEM_TO_CART "addItemToCart()"
#define CLEAR_SCREEN_METHOD "clearScreen()"
#define DRIVER_INFO_DB "driver-info.isl"
#define DRIVER_LOGIN_DB "driver-auth-info.isl"
#define PRODUCT_CATALOGUE_DB "items-catalogue.isl"



#endif 