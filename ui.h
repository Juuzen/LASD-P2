#ifndef LASD_P2_UI_H
#define LASD_P2_UI_H
#include "order.h"
#include "catalogue.h"
#include "driver.h"

/* ----- Funzioni di interfaccia grafica ----- */
void projectRun();
void ui_authenticationMenu();
void ui_registrationMenu();

void ui_driverMenu(Driver driver);

void ui_shopMenu(Driver* driver);
Order ui_addCartItemMenu(Order cart, Catalogue catalogue);
Order ui_removeCartItemMenu(Order cart);
void ui_showCartInfoMenu(Driver driver, Order cart);
void ui_showDriverInfoMenu(Driver driver);

void ui_deliveryMenu(Driver driver);

/* ----- Funzioni di appoggio ----- */
Order ui_addItemToCart(Order cart, Catalogue catalogue);
Order ui_removeItemFromCart(Order cart);

#endif //LASD_P2_UI_H

